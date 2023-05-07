#include "azure_iot.h"
#include <stdio.h>
#include <stdlib.h>

#include "azureiot/iothub.h"
#include "azureiot/iothub_device_client_ll.h"
#include "azureiot/iothub_client_options.h"
#include "azureiot/iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "azureiot/iothubtransportmqtt.h"
azureIot *azureIotmsg =NULL;
// Uncomment this define to use Asynchronous ACK of cloud-to-device messages.
// #define USE_C2D_ASYNC_ACK

// Most applications should leave USE_C2D_ASYNC_ACK undefined.
// The default sample behavior is easier for the application to manage and meets the vast majority of application scenarios.
// The pattern sampled when USE_C2D_ASYNC_ACK is defined should be used when the application does
// not want to immediately acknowledge receipt of the message to Azure IoT Hub during the callback. It wants
// instead to defer the acknowledgement until a later time with a call to IoTHubDeviceClient_LL_SendMessageDisposition.
#ifdef _UCHIP_T113
#ifdef USE_C2D_ASYNC_ACK
#include "azure_c_shared_utility/singlylinkedlist.h"

static SINGLYLINKEDLIST_HANDLE g_cloudMessages;

// `ack_and_remove_message` is a function that is executed by `singlylinkedlist_remove_if` for each list element.
// In this implementation it is used to send a delayed acknowledgement of receipt to Azure IoT Hub for each message.
static bool ack_and_remove_message(const void* item, const void* match_context, bool* continue_processing)
{
    IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle = (IOTHUB_DEVICE_CLIENT_LL_HANDLE)match_context;
    IOTHUB_MESSAGE_HANDLE message = (IOTHUB_MESSAGE_HANDLE)item;

    const char* messageId;
    if ((messageId = IoTHubMessage_GetMessageId(message)) == NULL)
    {
        messageId = "<unavailable>";
    }

    (void)printf("Sending ACK for cloud message (Message ID: %s)\r\n", messageId);

    // If using AMQP protocol, this function results in sending a MESSAGE DISPOSITION (ACCEPTED) for the given cloud-to-device message.
    // If using MQTT protocol, a PUBACK is sent for the cloud-to-device message (only) if `IOTHUBMESSAGE_ACCEPTED` is used.
    // If using HTTP protocol no delayed acknowledgement is sent for the cloud-to-device message, as this protocol does not support that.
    // Independent of the protocol used, this function MUST be called by the user application if using delayed acknowledgement of
    // cloud-to-device messages, as it will free the memory allocated for each of those messages received.
    if (IoTHubDeviceClient_LL_SendMessageDisposition(device_ll_handle, message, IOTHUBMESSAGE_ACCEPTED) != IOTHUB_CLIENT_OK)
    {
        (void)printf("ERROR: IoTHubDeviceClient_LL_SendMessageDisposition..........FAILED!\r\n");
    }

    // Setting `continue_processing` to true informs `singlylinkedlist_remove_if` to continue iterating
    // through all the remaining items in the `g_cloudMessages` list.
    *continue_processing = true;

    // Returning true informs `singlylinkedlist_remove_if` to effectively remove the current list node (`item`).
    return true;
}

static void acknowledge_cloud_messages(IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle)
{
    // The following function performs a conditional removal of items from a singly-linked list.
    // It can be used to perform one or more actions (through `ack_and_remove_message`) over each list item before removing them.
    // In this case, `ack_and_remove_message` sends an acknowledgement to Azure IoT Hub for each cloud-to-device message
    // previously received and still stored in the `g_cloudMessages` list.
    // This implementation also guarantees the cloud-to-device messages are acknowledged
    // in the order they have been received by the Azure IoT Hub.
    (void)singlylinkedlist_remove_if(g_cloudMessages, ack_and_remove_message, device_ll_handle);
}
#endif

static IOTHUBMESSAGE_DISPOSITION_RESULT receive_msg_callback(IOTHUB_MESSAGE_HANDLE message, void* user_context)
{
    (void)user_context;
    const char* messageId;
    const char* correlationId;

    // Message properties
    if ((messageId = IoTHubMessage_GetMessageId(message)) == NULL)
    {
        messageId = "<unavailable>";
    }

    if ((correlationId = IoTHubMessage_GetCorrelationId(message)) == NULL)
    {
        correlationId = "<unavailable>";
    }

    IOTHUBMESSAGE_CONTENT_TYPE content_type = IoTHubMessage_GetContentType(message);
    if (content_type == IOTHUBMESSAGE_BYTEARRAY)
    {
        const unsigned char* buff_msg;
        size_t buff_len;

        if (IoTHubMessage_GetByteArray(message, &buff_msg, &buff_len) != IOTHUB_MESSAGE_OK)
        {
            printf("Failure retrieving byte array message\r\n");
        }
        else
        {
            //LV_LOG_USER("Received Binary message\r\nMessage ID: %s\r\n Correlation ID: %s\r\n Data: <<<%.*s>>> & Size=%d\r\n", messageId, correlationId, (int)buff_len, buff_msg, (int)buff_len);
            azureIotmsg->mHook(buff_msg,buff_len);
        }
    }
    else
    {
        const char* string_msg = IoTHubMessage_GetString(message);
        if (string_msg == NULL)
        {
            printf("Failure retrieving byte array message\r\n");
        }
        else
        {
            //LV_LOG_USER("Received String Message\r\nMessage ID: %s\r\n Correlation ID: %s\r\n Data: <<<%s>>>\r\n", messageId, correlationId, string_msg);
            azureIotmsg->mHook((unsigned char*)string_msg,(size_t)strlen(string_msg));
        }
    }
    const char* property_value = "property_value";
    const char* property_key = IoTHubMessage_GetProperty(message, property_value);
    if (property_key != NULL)
    {
        LV_LOG_USER("\r\nMessage Properties:\r\n");
        LV_LOG_USER("\tKey: %s Value: %s\r\n", property_value, property_key);
    }
#ifdef USE_C2D_ASYNC_ACK
    // For a delayed acknowledgement of the cloud-to-device message, we must save the message first.
    // The `g_cloudMessages` list is used to save incoming cloud-to-device messages.
    // An user application would then process these messages according to the user application logic,
    // and finally send an acknowledgement to the Azure IoT Hub for each by calling `IoTHubDeviceClient_LL_SendMessageDisposition`.
    // When using convenience-layer or module clients of this SDK the respective `*_SendMessageDisposition` functions shall be used.
    (void)singlylinkedlist_add(g_cloudMessages, message);

    // Returning IOTHUBMESSAGE_ASYNC_ACK means that the SDK will NOT acknowledge receipt the
    // C2D message to the service.  The application itself is responsible for this.  See ack_and_remove_message() in the sample
    // to see how to do this.
    return IOTHUBMESSAGE_ASYNC_ACK;
#else
    // Returning IOTHUBMESSAGE_ACCEPTED causes the SDK to acknowledge receipt of the message to
    // the service.  The application does not need to take further action to ACK at this point.
    return IOTHUBMESSAGE_ACCEPTED;
#endif
}
#endif
static void *aiot_main(void *fcmToken)
{
    char *connectionString =(char *)fcmToken;
	IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;
    size_t messages_count = 0;
    bool traceOn = true;
	bool urlDecodeOn = true;
	
#ifdef _UCHIP_T113
#ifdef USE_C2D_ASYNC_ACK
        g_cloudMessages = singlylinkedlist_create();
#endif

    // Used to initialize IoTHub SDK subsystem
    IoTHub_Init();

    // Create the iothub handle here
    device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
    if (device_ll_handle == NULL)
    {
        LV_LOG_USER("Failure creating IotHub device. Hint: Check your connection string.\r\n");
    }
    else
    {
        // Set any option that are necessary.
        // For available options please see the iothub_sdk_options.md documentation 
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_LOG_TRACE, &traceOn);
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_AUTO_URL_ENCODE_DECODE, &urlDecodeOn);

        if (IoTHubDeviceClient_LL_SetMessageCallback(device_ll_handle, receive_msg_callback, &messages_count) != IOTHUB_CLIENT_OK)
        {
            LV_LOG_USER("ERROR: IoTHubClient_LL_SetMessageCallback..........FAILED!\r\n");
        }
        else
        {
            LV_LOG_USER("iot successfully connected !!!\r\n");
            while(1)
            {
                IoTHubDeviceClient_LL_DoWork(device_ll_handle);
#ifdef USE_C2D_ASYNC_ACK
                // If using delayed acknowledgement of cloud-to-device messages, this function serves as an example of
                // how to do so for all the previously received messages still present in the list used by this sample.
                acknowledge_cloud_messages(device_ll_handle);
#endif
                ThreadAPI_Sleep(10);
            }
        }

        // Clean up the iothub sdk handle
        IoTHubDeviceClient_LL_Destroy(device_ll_handle);
    }
    // Free all the sdk subsystem
    IoTHub_Deinit();

#ifdef USE_C2D_ASYNC_ACK
    singlylinkedlist_destroy(g_cloudMessages);
#endif
#endif
    LV_LOG_USER("*****aiot_main end !!!******");
    return NULL;
}

azureIot::azureIot(void)
{
    int err;
    pthread_attr_t attr;
    azureIotmsg =this;
#ifdef _UCHIP_T113
    read_string_type_param(WEATHER_SCENE, FCMTOKEN, fcmToken,sizeof(fcmToken));
#endif
    err = pthread_attr_init(&attr);
    if(err != 0)
    {
        LV_LOG_USER("\n pthread_attr_init err \n");
        return ;
    }
    err = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    if(err == 0)
    {
        pthread_t tid = -1;
        if(0 > pthread_create(&tid, &attr,&aiot_main, (void *)fcmToken))
        {
            LV_LOG_USER("\ncreate http_activation_server fail!\n");
        }
    }
    pthread_attr_destroy(&attr);
}

azureIot::~azureIot(void)
{

}

void azureIot::addReadHook(void (*hook)(const unsigned char*, size_t))
{
    mHook = hook;
}
