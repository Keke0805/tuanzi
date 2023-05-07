#ifndef HTTP_H
#define HTTP_H
#include  "lvgl/src/misc/lv_log.h"
#include  "lvgl/src/custom/cjson/cJSON.h"
#include  "../appmsg/appmsg.h"
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "hv/requests.h"
#include  "hv/hthread.h"
#include  "hv/base64.h"
#include  "hv/md5.h"
#include  "hv/mqtt_client.h"
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <iostream>
#include  "azure_iot.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#include  "minizip/Zip.h"
#endif

#define HTTP_ACTIVE                 "http://vphoto.waophoto.com/apiv2/device/device_active"
#define HTTP_LOGIN                  "http://vphoto.waophoto.com/apiv2/device/signin"
#define HTTP_IOT                    "http://vphoto.waophoto.com/apiv2/iot/registDevice"
#define HTTP_BINDBYEMAIL            "http://vphoto.waophoto.com/apiv2/device/deviceBindByEmail"
#define HTTP_GETCONNECTIONCODE		"http://vphoto.waophoto.com/apiv2/device/deviceGetConnectionCode?"
#define HTTP_GETDEVICEUSER			"http://vphoto.waophoto.com/apiv2/device/device_user?"
#define HTTP_RESTORFACTORY          "http://vphoto.waophoto.com/apiv2/device/restoreFactory?"
#define HTTP_CITYLIST				"http://vphoto.waophoto.com/apiv2/weatherredirect/getCityList?"
#define HTTP_CITYIDWEATHER			"http://vphoto.waophoto.com/apiv2/weatherredirect/city_id?"
#define HTTP_CITYLATLON      		"http://vphoto.waophoto.com/apiv2/weatherredirect/lat_lon?"
enum {
    MSG_NEWUSER = 0,
    MSG_UNBINDUSER,
    MSG_IMAGE,
    MSG_VIDEO,
    MSG_USERNAME,
    MSG_USERPROLIMG,
    MSG_DELUSER,
    MSG_GETDEVICELOG,
    MSG_MQTT_MAX
};
typedef uint32_t mqtt_msg_t;

enum {
    FILE_STOP = 0,
    FILE_START,
    FILE_DOWNING,
    FILE_MAX
};
typedef uint32_t file_down_t;

typedef struct
{
    char name[64];
    char data[1024];
}parameter_info_t;

typedef struct weather_info
{
    int week;
    float temp;
    float temp_max;
    float temp_min;
    int humidity;
    int id;
    float speed;
    char weinfo[128];
    char icon[24];
}weather_info_t;

typedef struct citylist_info
{
    double lat;
    double lon;
    char name[64];
    char qualifiedName[64];
}citylist_info_t;

typedef std::function<void(myMsg)> MsgCallBack ;
class Http  : public LvcppTimerTask
{
public:
    Http(void);
	~Http(void);
    void Http_set_cityName(char *name);
    void Http_active_init(void);
    void Http_get_weather(void);
    void get_cur_weather(void *info);
    void get_first_weather(void *info);
    void get_second_weather(void *info);
    void get_three_weather(void *info);
    void Http_dev_regist(void);
    void set_msg_type(msg_type_e type);
    void Http_get_network_time(void);
    void Http_get_weather_info(void);
    void Http_set_weather_info(int type);
	void set_TimeZone(int zone);
	void set_TimeZoneStatus(int type);
    void get_devCod(void);
    void set_dev_factory(void);
    void get_dev_user(void);
	void _dev_BindByEmail(char *emailData);
    void iot_clean_userInfo(void);
    void TimerCB(lv_timer_t * tmr);
    azureIot *AzureIotStart =NULL;
    citylist_info_t *citylistInfo =NULL;
    weather_info_t weatherInfoCur;
    weather_info_t weatherInfoFirst;
    weather_info_t weatherInfoSecond;
    weather_info_t weatherInfoThree;
	file_down_t downStatus =FILE_STOP;
    int active_status =-1;
    bool active_ok =false;
	char downFilePatch[128]={0};
    char downPatch[128]={0};
    char serialAddress[34]={0};
    char macAddress[48]={0};
    char nickName[64]={0};
    char companyName[32]={0};
    char devId[24]={0};
    char accessToken[64]={0};
    char devCode[24]={0};
    char EmailData[32]={0};
    char mqtt_name[64]={0};
    char mqtt_passd[64]={0};
    char fcmToken[256]={0};
    char cityName[64]={0};
	char tempBuff[24]={0};
	char latDataBuff[24]={0};
	char lonDataBuff[24]={0};
	char curCityName[64]={0};
    double latData=0;
    double lonData=0;
    int cityId=0;
    int httpActiveType =0;
    int httpActiveTypeNum =0;
    int httpLoginType =0;
    int httpLoginTypeNum =0;
	int IotType =0;
	int IotTypeNum =0;
	int devCodeType =0;
	int devCodeTypeNum =0;
	int devFactoryType =0;
	int devFactoryTypeNum =0;
    int devUserType =0;
    int devUserTypeNum =0;
	int devEmailType =0;
    int devEmailTypeNum =0;
    int httpcityListType =0;
    int httpcityListTypeNum =0;
    int weatherInfoType =0;
    int weatherInfoTypeNum =0;
    int downfileTypeNum =0;
	int TimeZone =8;
    int ZoneState =1;
    
private:
    int Http_dev_active(char *nickname,char *uuid);
    int Http_dev_active_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData);
    int Http_dev_login(char *deviceId,char *fcmToken,char *cpyName,char *extraInfo);
    int Http_dev_login_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData);
    int Http_dev_cod(char *deviceId);
    int Http_dev_cod_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData);
    int Http_dev_user(char *deviceId);
    int Http_dev_user_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData);
    int Http_dev_BindByEmail(char *emailData,char *deviceId);
	int Http_dev_BindByEmail_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData);
	int Http_dev_factory(char *deviceId);
    int Http_dev_factory_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData);
    int Http_dev_iot_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData);
    int Http_weather_start(char *url,char *devId,char *timeTp,char *sign);
    int Http_dev_weather(int weathertype);
    int Http_weather_citylist_start(char *url,char *devId,char *timeTp,char *sign);
    int Http_dev_citylist_weather(void);
    int Http_get_file_start(char *url);
    bool get_wifi_status(void);
	void Http_downFile(void);
    static void iot_redata(const unsigned char* buff, size_t len);
    static void iot_remov_userInfo(char *name);
	static int iot_status_userInfo(char *name);
    static void iot_newUser(cJSON *json);
    static void iot_unbindUser(cJSON *json);
    static void iot_imageUp(cJSON *json);
    static void iot_videoUp(cJSON *json);
    static void iot_updateUserName(cJSON *json);
    static void updateUserProImg(cJSON *json);
    static void deleteDeviceUser(cJSON *json);
    msg_type_e msgType =UI_LAUNCHER;
    int deviceId =0;
    int loginTime =0;
    int loginHttpState =0;
};

#endif // HTTP_H
