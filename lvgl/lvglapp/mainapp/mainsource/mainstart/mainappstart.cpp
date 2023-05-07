#include "mainappstart.h"
#include "common/common.h"
#include "math.h"
#include <locale>
#include <codecvt>
#include <iconv.h>

#include "lv_drivers/indev/sunxi_key.h"

using namespace LVGLOPTAPI;
MainAPPStart* Mainopt=nullptr;
static int volume_tmp = 80;
static int microphone_tmp = 80;
static int backlight_tmp = 320;
static int light_tmp = 1;

int cur_play_type = 0;  // 0 = image  1==video
int prepare_play_type = 0;  // 0 = image  1==video

enum
{
    ENCODER_ENTER=28,
    ENCODER_LEFT=105,
    ENCODER_RIGHT=106,
};

void MainAPPStart::decode_dev_callback(uint32_t key_type,uint32_t key_value, lv_indev_state_t state)
{
    //LV_LOG_USER("input info:(%d, %d, %d)\n", key_type, key_value,state);
    if(key_value==ENCODER_ENTER)
    {
        if(state==LV_INDEV_STATE_PRESSED)
        {
            LvcppEvent::send_event(Mainopt->btn_win->myobj,LV_EVENT_CLICKED,Mainopt);
        }
    }
    else if(key_value==ENCODER_LEFT)
    {
        if(state==LV_INDEV_STATE_PRESSED)
        {
            LvcppEvent::send_event(Mainopt->btn_left->myobj,LV_EVENT_CLICKED,Mainopt);
        }
    }
    else if(key_value==ENCODER_RIGHT)
    {
        if(state==LV_INDEV_STATE_PRESSED)
        {
            LvcppEvent::send_event(Mainopt->btn_right->myobj,LV_EVENT_CLICKED,Mainopt);
        }
    }
}

bool MainAPPStart::send_packet(unsigned char data_type, unsigned char data_len, unsigned char* data_buf)
{
    BYTE sendbuf[1024];
    int send_size=0;
    int index = 0;
    memset(sendbuf,0,sizeof(sendbuf));

    sendbuf[0]=PACKRT_HEAD;
    sendbuf[1]=data_type;
    sendbuf[2]=data_len;
    index += 3;
    for(int i = 0; i < int(data_len); i++)
    {
        sendbuf[index+i] = data_buf[i];
        index++;
    }
    sendbuf[index]=PACKRT_TAIL;
    send_size = index+1;
    return BLE_Uart->send(sendbuf,send_size);
}

bool MainAPPStart::send_init_finish_packet(void)
{
    BYTE sendbuf[1024];
    int send_size=0;
    memset(sendbuf,0,sizeof(sendbuf));

    sendbuf[0]=PACKRT_HEAD;
    sendbuf[1]=PACKRT_CMD_DISP_INIT;
    sendbuf[2]=PACKRT_CMD_DISP_INIT;
    sendbuf[3]=0x04;
    sendbuf[4]=0x55;
    sendbuf[5]=0x66;
    sendbuf[6]=0x55;
    sendbuf[7]=0x66;
    sendbuf[8]=(sendbuf[1]^sendbuf[2])^sendbuf[3];
    sendbuf[9]=PACKRT_TAIL;
    send_size += 10;
    return BLE_Uart->send(sendbuf,send_size);
}


bool MainAPPStart::send_volume_control_packet(unsigned char data)
{
    BYTE sendbuf[1024];
    int send_size=0;
    memset(sendbuf,0,sizeof(sendbuf));

    sendbuf[0]=PACKRT_HEAD;
    sendbuf[1]=PACKRT_CMD_VOLUME;
    sendbuf[2]=0x01;
    sendbuf[3]=0x01;
    sendbuf[4]=data;
    sendbuf[5]=(sendbuf[1]^sendbuf[2])^sendbuf[3];
    sendbuf[6]=PACKRT_TAIL;
    send_size += 7;
    return BLE_Uart->send(sendbuf,send_size);
}

bool MainAPPStart::send_microphone_volume_control_packet(unsigned char data)
{
    BYTE sendbuf[1024];
    int send_size=0;
    memset(sendbuf,0,sizeof(sendbuf));

    sendbuf[0]=PACKRT_HEAD;
    sendbuf[1]=PACKRT_CMD_MICROPHONE;
    sendbuf[2]=0x01;
    sendbuf[3]=0x01;
    sendbuf[4]=data;
    sendbuf[5]=(sendbuf[1]^sendbuf[2])^sendbuf[3];
    sendbuf[6]=PACKRT_TAIL;
    send_size += 7;
    return BLE_Uart->send(sendbuf,send_size);
}

bool MainAPPStart::send_microphone_EQ_control_packet(unsigned char data)
{
    BYTE sendbuf[1024];
    int send_size=0;
    memset(sendbuf,0,sizeof(sendbuf));

    sendbuf[0]=PACKRT_HEAD;
    sendbuf[1]=PACKRT_CMD_MICROPHONE;
    sendbuf[2]=0x02;
    sendbuf[3]=0x01;
    sendbuf[4]=data;
    sendbuf[5]=(sendbuf[1]^sendbuf[2])^sendbuf[3];
    sendbuf[6]=PACKRT_TAIL;
    send_size += 7;
    return BLE_Uart->send(sendbuf,send_size);
}

bool MainAPPStart::send_rgb_light_control_packet(unsigned char data)
{
    BYTE sendbuf[1024];
    int send_size=0;
    memset(sendbuf,0,sizeof(sendbuf));

    sendbuf[0]=PACKRT_HEAD;
    sendbuf[1]=PACKRT_CMD_RGB_LIGHT;
    sendbuf[2]=data;
    sendbuf[3]=0x00;
    sendbuf[4]=(sendbuf[1]^sendbuf[2])^sendbuf[3];
    sendbuf[5]=PACKRT_TAIL;
    send_size += 6;
    return BLE_Uart->send(sendbuf,send_size);
}


void MainAPPStart::uart_recv_callback(const unsigned char* rcv_buf, int len)
{
    /*string lyrics;
    memset(&lyrics,0,sizeof(lyrics));*/

    /*printf("Recv_packet[");
    for (int i = 0; i < len; ++i)
    {
        printf("%02x ", rcv_buf[i]);
    }
    printf("]\n");*/

    Mainopt->uart_receive_proc(rcv_buf,len);
    /*
    memcpy(&Mainopt->parse_buf[Mainopt->read_len], rcv_buf, len);
    Mainopt->read_len += len;

    if(Mainopt->read_len>0)
    {
        Mainopt->parse_packet(Mainopt->parse_buf, Mainopt->read_len, &Mainopt->recPacket);
    }
    if(Mainopt->recPacket.find_cmd==1 && Mainopt->recPacket.finish)
    {
        if(Mainopt->recPacket.packetInvalid==0)
        {
            Mainopt->packet_frame_data_parse(Mainopt->recPacket.data_type,Mainopt->recPacket.data_len,Mainopt->recPacket.data_buf);
            memset(&Mainopt->recPacket, 0, sizeof(Amozol_packet_t));
            memset(Mainopt->parse_buf, 0, sizeof(Mainopt->parse_buf));
            Mainopt->read_len = 0;
        }
        else
        {
            memset(&Mainopt->recPacket, 0, sizeof(Amozol_packet_t));
            memset(Mainopt->parse_buf, 0, sizeof(Mainopt->parse_buf));
            Mainopt->read_len = 0;
            LV_LOG_USER("Invalid packet");
        }
    }*/
    /*
    if(!lyrics.empty())
    {
        Mainopt->lyrics_record(lyrics);
    }*/
}

void MainAPPStart::packet_frame_data_parse(unsigned char data_type, unsigned int data_len, unsigned char* data_buf)
{
    LV_LOG_USER("data_type =%d | data_len=%d | data_buf =%s",data_type,data_len,data_buf);
}

void MainAPPStart::parse_packet(unsigned char *buf, int bufsize, Amozol_packet_t *recPacket)
{
    int i=0;
    int data_len=0;

    if(buf==NULL||recPacket==NULL)
    return;
    memset(recPacket, 0, sizeof(Amozol_packet_t));
    for(i=0;i<bufsize;i++)
    {
        if(recPacket->find_cmd==0)
        {
            if(buf[i]==0xFA)
            {
                recPacket->find_cmd=1;
                recPacket->idx = 0;
                continue;
            }
        }
        else if(recPacket->find_cmd==1)
        {
            if(recPacket->idx==0)
            {
                recPacket->data_type=buf[i];
            }
            else if(recPacket->idx==1)
            {
                recPacket->data_len=buf[i];
                data_len = recPacket->data_len;
            }
            else
            {
                if(recPacket->rec_len<data_len)
                {
                    recPacket->data_buf[recPacket->rec_len] = buf[i];
                    recPacket->rec_len++;
                }
                else
                {
                    if(recPacket->idx == data_len+2)//check
                    {
                        if(buf[i]==0xF5)
                        {
                            recPacket->finish=1;
                            recPacket->packetInvalid=0;
                            break;
                        }
                        else
                        {
                            recPacket->packetInvalid=1;
                            break;
                        }
                    }
                    else
                    {
                        recPacket->packetInvalid=1;
                        recPacket->finish=1;
                        break;
                    }
                }
            }
            recPacket->idx++;
        }
    }
}

void MainAPPStart::ui_txt_decede(void)
{
    int index=0;
    LvcppMemory::memset(txtlist,0,sizeof(txtlist));

    txtlist[index] = (char *)"Timer";
    index++;

    txtlist[index] = (char *)"Version";
    index++;

    txtlist[index] = (char *)"User";
    index++;

    txtlist[index] = (char *)"Language";
    index++;

    txtlist[index] = (char *)"Wifi";
    index++;

    txtlist[index] = (char *)"Bluetooth";
    index++;

    txtlist[index] = (char *)"Radio";
    index++;

    txtlist[index] = (char *)"Sounds";
    index++;

    txtlist[index] = (char *)"Volume";
    index++;

    txtlist[index] = (char *)"Setting";
    index++;

    txtlist[index] = (char *)"Microphone";
    index++;

    txtlist[index] = (char *)"Brightness";
    index++;

    txtlist[index] = (char *)"Dynamic";
    index++;

    txtlist[index] = (char *)"Static";
    index++;

    txtlist[index] = (char *)"Light";
    index++;
    txtlist[index] = (char *)"Clock";
    index++;
    txtlist[index] = (char *)"Alarm";
    index++;
}
void MainAPPStart::ui_image_decode(void)
{
    int index=0;
    LvcppMemory::memset(&imagelist,0,sizeof(imagelist_t));
    TIMER_ZHIZHEN_PNG=(void*)parse_image_from_file((char*)TIMER_ZHIZHEN_PNG_PATH);
    TIMER_PNG=(void*)parse_image_from_file((char*)TIMER_PNG_PATH);
    MAIN_MENU_TIMER_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_TIMER_B_PNG_PATH);
    MAIN_MENU_TIMER_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_TIMER_S_PNG_PATH);
    MAIN_MENU_BACKGROUND_BUTTERFLIES_JPG=(void*)parse_image_from_file((char*)MAIN_MENU_BUTTERFILES_JPG_PATH);
    MAIN_MENU_BACKGROUND_CHRISTMAS_JPG=(void*)parse_image_from_file((char*)MAIN_MENU_CHRISTMAS_JPG_PATH);
    imagelist.big[index]= MAIN_MENU_TIMER_B_PNG;
    imagelist.small[index]= MAIN_MENU_TIMER_S_PNG;
    index++;

    MAIN_MENU_VERSION_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_VERSION_B_PNG_PATH);
    MAIN_MENU_VERSION_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_VERSION_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_VERSION_B_PNG;
    imagelist.small[index]= MAIN_MENU_VERSION_S_PNG;
    index++;

    MAIN_MENU_USER_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_USER_B_PNG_PATH);
    MAIN_MENU_USER_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_USER_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_USER_B_PNG;
    imagelist.small[index]= MAIN_MENU_USER_S_PNG;
    index++;

    MAIN_MENU_LANGUAGE_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_LANGUAGE_B_PNG_PATH);
    MAIN_MENU_LANGUAGE_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_LANGUAGE_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_LANGUAGE_B_PNG;
    imagelist.small[index]= MAIN_MENU_LANGUAGE_S_PNG;
    index++;

    MAIN_MENU_WIFI_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_WIFI_B_PNG_PATH);
    MAIN_MENU_WIFI_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_WIFI_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_WIFI_B_PNG;
    imagelist.small[index]= MAIN_MENU_WIFI_S_PNG;
    index++;

    MAIN_MENU_BLUETOOTH_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_BLUETOOTH_B_PNG_PATH);
    MAIN_MENU_BLUETOOTH_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_BLUETOOTH_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_BLUETOOTH_B_PNG;
    imagelist.small[index]= MAIN_MENU_BLUETOOTH_S_PNG;
    index++;

    MAIN_MENU_NET_RADIO_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_NET_RADIO_B_PNG_PATH);
    MAIN_MENU_NET_RADIO_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_NET_RADIO_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_NET_RADIO_B_PNG;
    imagelist.small[index]= MAIN_MENU_NET_RADIO_S_PNG;
    index++;

    MAIN_MENU_SOUNDS_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_SOUNDS_B_PNG_PATH);
    MAIN_MENU_SOUNDS_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_SOUNDS_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_SOUNDS_B_PNG;
    imagelist.small[index]= MAIN_MENU_SOUNDS_S_PNG;
    index++;

    MAIN_MENU_VOLUME_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_VOLUME_B_PNG_PATH);
    MAIN_MENU_VOLUME_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_VOLUME_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_VOLUME_B_PNG;
    imagelist.small[index]= MAIN_MENU_VOLUME_S_PNG;
    index++;

    MAIN_MENU_EQ_SETTING_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_EQ_SETTING_B_PNG_PATH);
    MAIN_MENU_EQ_SETTING_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_EQ_SETTING_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_EQ_SETTING_B_PNG;
    imagelist.small[index]= MAIN_MENU_EQ_SETTING_S_PNG;
    index++;

    MAIN_MENU_MICROPHONE_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_MICROPHONE_B_PNG_PATH);
    MAIN_MENU_MICROPHONE_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_MICROPHONE_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_MICROPHONE_B_PNG;
    imagelist.small[index]= MAIN_MENU_MICROPHONE_S_PNG;
    index++;

    MAIN_MENU_BRIGHTNESS_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_BRIGHTNESS_B_PNG_PATH);
    MAIN_MENU_BRIGHTNESS_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_BRIGHTNESS_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_BRIGHTNESS_B_PNG;
    imagelist.small[index]= MAIN_MENU_BRIGHTNESS_S_PNG;
    index++;

    MAIN_MENU_DYNAMIC_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_DYNAMIC_B_PNG_PATH);
    MAIN_MENU_DYNAMIC_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_DYNAMIC_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_DYNAMIC_B_PNG;
    imagelist.small[index]= MAIN_MENU_DYNAMIC_S_PNG;
    index++;

    MAIN_MENU_STATIC_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_STATIC_B_PNG_PATH);
    MAIN_MENU_STATIC_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_STATIC_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_STATIC_B_PNG;
    imagelist.small[index]= MAIN_MENU_STATIC_S_PNG;
    index++;

    MAIN_MENU_LIGHT_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_LIGHT_B_PNG_PATH);
    MAIN_MENU_LIGHT_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_LIGHT_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_LIGHT_B_PNG;
    imagelist.small[index]= MAIN_MENU_LIGHT_S_PNG;
    index++;

    MAIN_MENU_CLOCK_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_CLOCK_B_PNG_PATH);
    MAIN_MENU_CLOCK_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_CLOCK_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_CLOCK_B_PNG;
    imagelist.small[index]= MAIN_MENU_CLOCK_S_PNG;
    index++;

    MAIN_MENU_ALARM_B_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_ALARM_B_PNG_PATH);
    MAIN_MENU_ALARM_S_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_ALARM_S_PNG_PATH);
    imagelist.big[index]= MAIN_MENU_ALARM_B_PNG;
    imagelist.small[index]= MAIN_MENU_ALARM_S_PNG;
    index++;
}

void MainAPPStart::ui_image_free(void)
{
    if(MAIN_MENU_ALARM_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_ALARM_B_PNG);
        MAIN_MENU_ALARM_B_PNG =NULL;
    }
    if(MAIN_MENU_ALARM_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_ALARM_S_PNG);
        MAIN_MENU_ALARM_S_PNG =NULL;
    }

    if(MAIN_MENU_BLUETOOTH_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_BLUETOOTH_B_PNG);
        MAIN_MENU_BLUETOOTH_B_PNG =NULL;
    }
    if(MAIN_MENU_BLUETOOTH_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_BLUETOOTH_S_PNG);
        MAIN_MENU_BLUETOOTH_S_PNG =NULL;
    }

    if(MAIN_MENU_BRIGHTNESS_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_BRIGHTNESS_B_PNG);
        MAIN_MENU_BRIGHTNESS_B_PNG =NULL;
    }
    if(MAIN_MENU_BRIGHTNESS_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_BRIGHTNESS_S_PNG);
        MAIN_MENU_BRIGHTNESS_S_PNG =NULL;
    }

    if(MAIN_MENU_CLOCK_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_CLOCK_B_PNG);
        MAIN_MENU_CLOCK_B_PNG =NULL;
    }
    if(MAIN_MENU_CLOCK_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_CLOCK_S_PNG);
        MAIN_MENU_CLOCK_S_PNG =NULL;
    }

    if(MAIN_MENU_DYNAMIC_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_DYNAMIC_B_PNG);
        MAIN_MENU_DYNAMIC_B_PNG =NULL;
    }
    if(MAIN_MENU_DYNAMIC_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_DYNAMIC_S_PNG);
        MAIN_MENU_DYNAMIC_S_PNG =NULL;
    }

    if(MAIN_MENU_EQ_SETTING_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_EQ_SETTING_B_PNG);
        MAIN_MENU_EQ_SETTING_B_PNG =NULL;
    }
    if(MAIN_MENU_EQ_SETTING_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_EQ_SETTING_S_PNG);
        MAIN_MENU_EQ_SETTING_S_PNG =NULL;
    }

    if(MAIN_MENU_LANGUAGE_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_LANGUAGE_B_PNG);
        MAIN_MENU_LANGUAGE_B_PNG =NULL;
    }
    if(MAIN_MENU_LANGUAGE_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_LANGUAGE_S_PNG);
        MAIN_MENU_LANGUAGE_S_PNG =NULL;
    }

    if(MAIN_MENU_LIGHT_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_LIGHT_B_PNG);
        MAIN_MENU_LIGHT_B_PNG =NULL;
    }
    if(MAIN_MENU_LIGHT_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_LIGHT_S_PNG);
        MAIN_MENU_LIGHT_S_PNG =NULL;
    }

    if(MAIN_MENU_MICROPHONE_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_MICROPHONE_B_PNG);
        MAIN_MENU_MICROPHONE_B_PNG =NULL;
    }
    if(MAIN_MENU_MICROPHONE_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_MICROPHONE_S_PNG);
        MAIN_MENU_MICROPHONE_S_PNG =NULL;
    }

    if(MAIN_MENU_NET_RADIO_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_NET_RADIO_B_PNG);
        MAIN_MENU_NET_RADIO_B_PNG =NULL;
    }
    if(MAIN_MENU_NET_RADIO_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_NET_RADIO_S_PNG);
        MAIN_MENU_NET_RADIO_S_PNG =NULL;
    }

    if(MAIN_MENU_SOUNDS_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_SOUNDS_B_PNG);
        MAIN_MENU_SOUNDS_B_PNG =NULL;
    }
    if(MAIN_MENU_SOUNDS_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_SOUNDS_S_PNG);
        MAIN_MENU_SOUNDS_S_PNG =NULL;
    }

    if(MAIN_MENU_STATIC_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_STATIC_B_PNG);
        MAIN_MENU_STATIC_B_PNG =NULL;
    }
    if(MAIN_MENU_STATIC_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_STATIC_S_PNG);
        MAIN_MENU_STATIC_S_PNG =NULL;
    }

    if(MAIN_MENU_TIMER_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_TIMER_B_PNG);
        MAIN_MENU_TIMER_B_PNG =NULL;
    }
    if(MAIN_MENU_TIMER_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_TIMER_S_PNG);
        MAIN_MENU_TIMER_S_PNG =NULL;
    }
    if(MAIN_MENU_USER_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_USER_B_PNG);
        MAIN_MENU_USER_B_PNG =NULL;
    }
    if(MAIN_MENU_USER_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_USER_S_PNG);
        MAIN_MENU_USER_S_PNG =NULL;
    }

    if(MAIN_MENU_VERSION_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_VERSION_B_PNG);
        MAIN_MENU_VERSION_B_PNG =NULL;
    }
    if(MAIN_MENU_VERSION_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_VERSION_S_PNG);
        MAIN_MENU_VERSION_S_PNG =NULL;
    }

    if(MAIN_MENU_VOLUME_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_VOLUME_B_PNG);
        MAIN_MENU_VOLUME_B_PNG =NULL;
    }
    if(MAIN_MENU_VOLUME_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_VOLUME_S_PNG);
        MAIN_MENU_VOLUME_S_PNG =NULL;
    }

    if(MAIN_MENU_WIFI_B_PNG !=NULL)
    {
        free_image(MAIN_MENU_WIFI_B_PNG);
        MAIN_MENU_WIFI_B_PNG =NULL;
    }
    if(MAIN_MENU_WIFI_S_PNG !=NULL)
    {
        free_image(MAIN_MENU_WIFI_S_PNG);
        MAIN_MENU_WIFI_S_PNG =NULL;
    }
    LvcppMemory::memset(imagelist.big,0,sizeof(imagelist.big));
    LvcppMemory::memset(imagelist.small,0,sizeof(imagelist.small));
    LvcppMemory::memset(&imagelist,0,sizeof(imagelist_t));
}

static void set_zoom(void* img, int32_t v)
{
    lv_img_set_zoom((lv_obj_t *)img,v);
}

static void set_angle(void* img, int32_t v)
{
    lv_img_set_angle((lv_obj_t *)img, v);//img类型不匹配，要强转类型
}
MainAPPStart::MainAPPStart(LvcppMainScreen* parent)
{
    ui_image_decode();
    Mainopt = this;
    m_screen = parent;
    m_parent = m_screen->get_obj();
    m_screen->background_color(lv_color_white());
    m_screen->transparent(true);
    m_screen->showlogo(MAIN_MENU_BACKGROUND_BUTTERFLIES_JPG,SCREEN_HOR_SIZE,SCREEN_VER_SIZE,0);
    timer=new LvcppLabel(m_parent);
    timer->set_txt("");
    timer->set_size(170,167);
    timer->align(LV_ALIGN_CENTER,0,0);
    timer->set_main_bg_img_src(TIMER_PNG);
    timer->set_main_bg_color(lv_color_black(),LV_OPA_0);
    anim_number=new LvcppLabel(m_parent);
    anim_number->align(LV_ALIGN_CENTER,0,0);
    anim_number->set_txt("");
    anim_number->set_main_bg_color(lv_color_black(),LV_OPA_0);
    anim_number->add_event_cb(btn_event_hander,LV_EVENT_FOCUSED,this);

    anim=new LvcppRotateAnimimg(m_parent);
    anim->set_animimg_src(TIMER_ZHIZHEN_PNG);
    anim->align(LV_ALIGN_CENTER,0,0);
    anim->set_main_bg_color(lv_color_black(),LV_OPA_0);
    anim->set_exec_cb(set_angle);
    anim->set_values(0,3600);
    anim->set_time(60000);
    anim->set_repeat_count(LV_ANIM_REPEAT_INFINITE);
    anim->start();
    //anim->set_playback_time(1000);
    //anim->set_exec_cb(set_zoom);
    //anim->set_values(100,100);

    #if 0
    image=new LvcppImage(m_parent);
    image->align(LV_ALIGN_CENTER,0,0);
    image->set_main_bg_img_src(TIMER_ZHIZHEN_PNG);
    image->set_main_bg_color(lv_color_black(),LV_OPA_0);
    image->add_event_cb(ratate_image_event,)
    #endif
    initial();
    wallpaper_initial();
    maintimer = startTimer(400,this);
}


//tip:new() must to do delete
MainAPPStart::~MainAPPStart(void)
{
    ui_image_free();
}

//User starts here
void MainAPPStart::initial(void)
{
    ui_image_decode();
    //m_screen->showlogo(BG_JPG, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    ui_txt_decede();
    btn_callback_simulator();

    lvgl_scroll_anim();
    maintimer = startTimer(20,this);

    BLE_Uart = new UartContext();
    if(BLE_Uart->openUart(UART_DEV,115200))
    {
        LV_LOG_USER("openUart success!\n");
        BLE_Uart->addReadHook(uart_recv_callback);
        pthread_attr_t pthread_attr;
        pthread_t pthread;
        pthread_attr_init(&pthread_attr);
        pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED);
        pthread_attr_setscope(&pthread_attr, PTHREAD_SCOPE_SYSTEM);

        int result = pthread_create(&pthread, &pthread_attr, uart_start, Mainopt);
        pthread_attr_destroy(&pthread_attr);
        if (result != 0)
        {
            LV_LOG_USER("pthread_create fail!\n");
        }
    }
    #if QTSIM_PLATFORM==0
    keydev_register_hook(decode_dev_callback);
    va_display_lcd_set_backlight(backlight_tmp/8);
    #endif
}

void MainAPPStart::draw_point(void)
{
    memset(point,0,sizeof(point));
    int X = (int)(sqrt(abs((ARC_RADIUS-CONT_LEN)*(ARC_RADIUS-CONT_LEN))/2));
    int Y = (int)(sqrt(abs((ARC_RADIUS-CONT_LEN)*(ARC_RADIUS-CONT_LEN))/2));
    //LV_LOG_USER("Center of the circle:X=%d,Y=%d",X,Y);
    for(int i=0;i<ARC_LENTH+1;i++)
    {
        point[i].x =X+(int)(sqrt(ARC_RADIUS*ARC_RADIUS-X*X))-(int)((float)ARC_RADIUS*cos(PI/180.0f*(90.0f*1.0f/((float)ARC_LENTH))*(float)i));
        point[i].y =-Y+(int)((float)ARC_RADIUS*(float)sin(PI/180.0f*(90.0f*1.0f/((float)ARC_LENTH))*(float)i))-60;
    }
    /*
    LvcppLine* line = new LvcppLine(cont->myobj);
    line->set_points(point,ARC_LENTH);
    lv_obj_set_style_line_color(line->myobj,lv_color_white(),0);
    */
    memset(point_list,0,sizeof(point_list));
    for(int j=0;j< MAIN_MENU_NUM;j++)
    {
        if(j==0)
        {
            point_list[j].x = point[(int)(abs(0))].x;
            point_list[j].y =point[(int)abs(0)].y;
        }
        else if(j==MAIN_MENU_NUM-1)
        {
            point_list[j].x = point[(int)(abs(ARC_LENTH))].x;
            point_list[j].y =point[(int)(abs(ARC_LENTH))].y;
        }
        else if(j<MAIN_MENU_NUM/2)
        {
            point_list[j].x = point[(int)abs(ARC_LENTH/(MAIN_MENU_NUM-1)*j)-(POINT_OFFSET)].x;
            point_list[j].y =point[(int)abs(ARC_LENTH/(MAIN_MENU_NUM-1)*j)-(POINT_OFFSET)].y;
        }
        else if(j>MAIN_MENU_NUM/2)
        {
            point_list[j].x = point[(int)abs(ARC_LENTH/(MAIN_MENU_NUM-1)*j)+(POINT_OFFSET)].x;
            point_list[j].y =point[(int)abs(ARC_LENTH/(MAIN_MENU_NUM-1)*j)+(POINT_OFFSET)].y;
        }
        else
        {
            point_list[j].x = point[(int)abs(ARC_LENTH/(MAIN_MENU_NUM-1)*j)].x-20;
            point_list[j].y =point[(int)abs(ARC_LENTH/(MAIN_MENU_NUM-1)*j)].y-20;
        }
        scroll_len = (int)(ARC_LENTH/(MAIN_MENU_NUM-1));
        //point_list[j].x = //X+(int)(sqrt(ARC_RADIUS*ARC_RADIUS-X*X))-(int)(ARC_RADIUS*cos(PI/180*(90*1.0f/(MAIN_MENU_NUM-1))*j));
        //point_list[j].y = //-Y+(int)(ARC_RADIUS*sin(PI/180*(90*1.0f/(MAIN_MENU_NUM-1))*j))-60;
        //LV_LOG_USER("x[%d]=%d,y[%d]=%d",j,point_list[j].x,j,point_list[j].y);
    }
}


void MainAPPStart::lvgl_scroll_anim(void)
{
    cont = new LvcppScreen(m_parent);
    cont->set_style_radius(0,0);
    cont->set_size(CONT_LEN, CONT_LEN);
    cont->align(LV_ALIGN_TOP_RIGHT,0,0);
    cont->set_style_bg_color(lv_color_hex(0xff0000),LV_OPA_0,0);
    cont->set_style_clip_corner(true, 0);
    cont->set_scrollbar_mode( LV_SCROLLBAR_MODE_OFF);
    cont->set_style_pad_row(0,0);
    cont->set_style_pad_column(0,0);
    cont->set_style_pad_all(0,0);

    current_function=new LvcppLabel(cont->myobj);
    current_function->set_txt(txtlist[mid_image]);
    current_function->txt_font_size(20,0);
    current_function->set_size(200,30);
    current_function->txt_align(LV_TEXT_ALIGN_RIGHT);
    current_function->txt_color(lv_color_white(),0);
    draw_point();

    memset(menulist,0,sizeof(menulist));
    for(int i = 0; i < MAIN_MENU_NUM; i++) {
        menulist[i] = new LvcppButton(cont->myobj);
        menulist[i]->set_style_pad_all(0,0);
        menulist[i]->set_style_bg_color(lv_color_white(),LV_OPA_0,0);
        if(i==MAIN_MENU_NUM/2)
        {
            menulist[i]->set_size(100,100);
            menulist[i]->set_main_bg_img_src(imagelist.big[i]);
            menulist[i]->set_pos(point_list[i].x,point_list[i].y);
            current_function->align_to(menulist[i]->myobj,LV_ALIGN_OUT_BOTTOM_RIGHT,-10,10);
        }
        else
        {
            menulist[i]->set_size(60,60);
            menulist[i]->set_pos(point_list[i].x,point_list[i].y);
            menulist[i]->set_main_bg_img_src(imagelist.small[i]);
        }
    }
}


void MainAPPStart::btn_callback_simulator(void)
{
    char index[32]={0};
    btn_win = new LvcppButton(lv_layer_top());
    btn_win->set_size(lv_pct(10),lv_pct(10));
    btn_win->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_50);
    btn_win->set_main_border(3,lv_color_hex(0xffffff),LV_OPA_70);
    btn_win->add_event_cb(btn_event_hander,LV_EVENT_ALL,this);
    btn_win->txt_font_size(16,0);
    btn_win->txt_color(lv_color_white());
    btn_win->txt_align(LV_ALIGN_TOP_MID,0,0);
    btn_win->add_txt("Enter");

    btn_left = new LvcppButton(btn_win->myobj);
    btn_left->set_size(lv_pct(40),lv_pct(60));
    btn_left->align(LV_ALIGN_LEFT_MID,0,0);
    btn_left->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_50);
    btn_left->add_txt(LV_SYMBOL_PREV);
    btn_left->txt_center();
    btn_left->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);

    btn_right = new LvcppButton(btn_win->myobj);
    btn_right->set_size(lv_pct(40),lv_pct(60));
    btn_right->align(LV_ALIGN_RIGHT_MID,0,0);
    btn_right->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_50);
    btn_right->add_txt(LV_SYMBOL_NEXT);
    btn_right->txt_center();
    btn_right->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);

    #if QTSIM_PLATFORM==0
    btn_win->show(false);
    #endif
    /*
    lyrics_win = new LvcppLabel(lv_layer_top());
    lyrics_win->set_size(lv_pct(80),lv_pct(20));
    lyrics_win->align(LV_ALIGN_BOTTOM_MID,0,0);
    lyrics_win->set_txt("");
    lyrics_win->txt_long_mode(LV_LABEL_LONG_SCROLL);

    lyrics_before = new LvcppLabel(lyrics_win->myobj);
    lyrics_before->set_size(lv_pct(100),lv_pct(50));
    lyrics_before->align(LV_ALIGN_TOP_MID,0,0);
    lyrics_before->set_txt("");
    lyrics_before->txt_font_size(80,2);
    lyrics_before->txt_color(lv_color_white(),0);
    lyrics_before->txt_long_mode(LV_LABEL_LONG_SCROLL);

    lyrics_after = new LvcppLabel(lyrics_win->myobj);
    lyrics_after->set_size(lv_pct(100),lv_pct(50));
    lyrics_after->align(LV_ALIGN_BOTTOM_MID,0,0);
    lyrics_after->set_txt("");
    lyrics_after->txt_font_size(80,2);
    lyrics_after->txt_color(lv_color_white(),0);
    lyrics_after->txt_long_mode(LV_LABEL_LONG_SCROLL);
    lyrics_after->txt_align(LV_TEXT_ALIGN_RIGHT);*/

    sub_lyrics = new Lyrics(m_parent);
}

void MainAPPStart::lyrics_record(std::string lyrice)
{
    lyrics_queue.push(lyrice);
    if(lyrics_queue.size() > QUEUE_LENGTH){
        if(!lyrics_queue.empty())
        {
            lyrics_queue.pop();
        }
    }
    if(lyrics_queue.size()==QUEUE_LENGTH)
    {
        lyrics_before->set_txt(lyrics_queue.front().c_str());
        lyrics_after->set_txt(lyrics_queue.back().c_str());
    }
    else
    {
        if(lyrics_queue.empty())
        {
            lyrics_before->set_txt("");
            lyrics_after->set_txt("");
        }
        else
        {
            lyrics_before->set_txt(lyrics_queue.back().c_str());
            lyrics_after->set_txt("");
        }
    }
}

void MainAPPStart::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    MainAPPStart* opt = (MainAPPStart*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(opt->scroll_flag!=0)
    {
        return;
    }

    if(opt->cur_page==-1)
    {
        opt->hide_time=0;
        if(opt->hide_flag)
        {
            opt->cont->show(true);
            opt->hide_flag=false;
            return;
        }
        if(target==opt->btn_win->myobj)
        {
            if(event->code==LV_EVENT_PRESSING)
            {
                lv_obj_t* obj = lv_event_get_target(event);
                lv_indev_t* indev = lv_indev_get_act();
                lv_point_t vect;
                lv_indev_get_vect(indev, &vect);
                lv_coord_t x = lv_obj_get_x(obj) + vect.x;
                lv_coord_t y = lv_obj_get_y(obj) + vect.y;
                lv_obj_set_pos(obj, x, y);
            }
            else if(event->code==LV_EVENT_CLICKED)  //enter
            {
                opt->subwindow_create();
                opt->cur_page=opt->mid_image;
            }
        }
        else if(target==opt->btn_left->myobj)  //LEFT
        {
            if(event->code==LV_EVENT_CLICKED)
            {
                int mid=0,new_image=0;

                mid=(opt->cur_head+MAIN_MENU_NUM/2)%(MAIN_MENU_NUM);

                if((opt->cur_index+MAIN_MENU_NUM/2)<0)
                {
                    if((opt->cur_index+MAIN_MENU_NUM/2)%MENU_IMAGE_NUM==0)
                        opt->mid_image=0;
                    else
                        opt->mid_image=MENU_IMAGE_NUM+((opt->cur_index+MAIN_MENU_NUM/2)%(MENU_IMAGE_NUM));
                }
                else
                {
                    opt->mid_image = (opt->cur_index+MAIN_MENU_NUM/2)%MENU_IMAGE_NUM;
                }

                opt->menulist[mid]->set_main_bg_img_src(opt->imagelist.small[opt->mid_image]);
                opt->menulist[mid]->set_size(60,60);

                opt->scroll_flag--;
                opt->cur_index--;

                if((opt->cur_index)<0)
                {
                    if((opt->cur_index)%MENU_IMAGE_NUM==0)
                        new_image=0;
                    else
                        new_image=MENU_IMAGE_NUM+((opt->cur_index)%(MENU_IMAGE_NUM));
                }
                else
                {
                    new_image = (opt->cur_index)%MENU_IMAGE_NUM;
                }
                opt->menulist[opt->cur_tail]->set_main_bg_img_src(opt->imagelist.small[new_image]);
            }
        }
        else if(target==opt->btn_right->myobj) //RIGHT
        {
            if(event->code==LV_EVENT_CLICKED)
            {
                int mid=0,new_image=0;

                mid=(opt->cur_head+MAIN_MENU_NUM/2)%(MAIN_MENU_NUM);

                if((opt->cur_index+MAIN_MENU_NUM/2)<0)
                {
                    if((opt->cur_index+MAIN_MENU_NUM/2)%MENU_IMAGE_NUM==0)
                        opt->mid_image=0;
                    else
                        opt->mid_image=MENU_IMAGE_NUM+((opt->cur_index+MAIN_MENU_NUM/2)%(MENU_IMAGE_NUM));
                }
                else
                {
                    opt->mid_image = (opt->cur_index+MAIN_MENU_NUM/2)%MENU_IMAGE_NUM;
                }
                opt->menulist[mid]->set_main_bg_img_src(opt->imagelist.small[opt->mid_image]);
                opt->menulist[mid]->set_size(60,60);

                opt->scroll_flag++;
                opt->cur_index++;

                if((opt->cur_index+MAIN_MENU_NUM-1)<0)
                {
                    if((opt->cur_index+MAIN_MENU_NUM-1)%MENU_IMAGE_NUM==0)
                        new_image=0;
                    else
                        new_image=MENU_IMAGE_NUM+((opt->cur_index+MAIN_MENU_NUM-1)%(MENU_IMAGE_NUM));
                }
                else
                {
                    new_image = (opt->cur_index+MAIN_MENU_NUM-1)%MENU_IMAGE_NUM;
                }
                opt->menulist[opt->cur_head]->set_main_bg_img_src(opt->imagelist.small[new_image]);
            }
        }
    }
    else
    {
        //subwindow event
        switch (opt->cur_page) {
        case 1:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        case 3:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        case 2:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        case 4:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;

                        //opt->sub_user->kb_callback();
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        case 5:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        case 6:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        case 7:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                         opt->sub_sound->switch_cartoon_left();
                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->sub_sound->switch_cartoon_right();
                    }
                }
            }
            break;
        case 8:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        if(0<=volume_tmp&&volume_tmp <= 320)
                        {
                            char value_tmp[10];
                            volume_tmp = volume_tmp - 8;
                            sprintf(value_tmp,"%d",volume_tmp/8);
                            opt->sub_volume_value->VOLUME_VALUE->set_txt(value_tmp);
                        }
                        if(volume_tmp < 0)
                        {
                            volume_tmp = 0;
                            opt->sub_volume_value->VOLUME_VALUE->set_txt("0");
                        }
                        if(volume_tmp > 320)
                        {
                            volume_tmp = 320;
                            opt->sub_volume_value->VOLUME_VALUE->set_txt("40");
                        }
                        opt->send_volume_control_packet((unsigned char)(volume_tmp/8));
                       // opt->sub_volume_value->down_volume(volume_tmp);
                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        if(0<=volume_tmp&&volume_tmp <= 320)
                        {
                            char value_tmp[10];
                            volume_tmp = volume_tmp + 8;
                            sprintf(value_tmp,"%d",volume_tmp/8);
                            opt->sub_volume_value->VOLUME_VALUE->set_txt(value_tmp);
                        }
                        if(volume_tmp < 0)
                        {
                            volume_tmp = 0;
                            opt->sub_volume_value->VOLUME_VALUE->set_txt("0");
                        }
                        if(volume_tmp > 320)
                        {
                            volume_tmp = 320;
                            opt->sub_volume_value->VOLUME_VALUE->set_txt("40");
                        }
                        opt->send_volume_control_packet((unsigned char)(volume_tmp/8));
                        //opt->sub_volume_value->up_volume(volume_tmp);
                    }
                }
            }
            break;
        case 9:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->sub_eq->switch_cartoon_left();
                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->sub_eq->switch_cartoon_right();
                    }
                }
            }
            break;
        case 10:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        if(0<=microphone_tmp&&microphone_tmp <= 320)
                        {
                            microphone_tmp = microphone_tmp - 8;
                        }
                        if(microphone_tmp < 0)
                        {
                            microphone_tmp = 0;
                        }
                        if(microphone_tmp > 320)
                        {
                            microphone_tmp = 320;
                        }
                        opt->send_microphone_EQ_control_packet((unsigned char)(microphone_tmp%3+1));
                        opt->sub_micphone->update_volume(microphone_tmp);
                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        if(0<=microphone_tmp&&microphone_tmp <= 320)
                        {
                            microphone_tmp = microphone_tmp + 8;
                        }
                        if(microphone_tmp < 0)
                        {
                            microphone_tmp = 0;
                        }
                        if(microphone_tmp > 320)
                        {
                            microphone_tmp = 320;
                        }
                        opt->send_microphone_EQ_control_packet((unsigned char)(microphone_tmp%3+1));
                        opt->sub_micphone->update_volume(microphone_tmp);
                    }
                }
            }
            break;
        case 11:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        if(0<=backlight_tmp&&backlight_tmp <= 320)
                        {
                            backlight_tmp = backlight_tmp - 8;
                        }
                        if(backlight_tmp < 0)
                        {
                            backlight_tmp = 0;
                        }
                        if(backlight_tmp > 320)
                        {
                            backlight_tmp = 320;
                        }
                        #if QTSIM_PLATFORM==0
                        va_display_lcd_set_backlight(backlight_tmp/8);
                        #endif
                        opt->sub_light->update_light(backlight_tmp);
                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        if(event->code==LV_EVENT_CLICKED)
                        {
                            if(0<=backlight_tmp&&backlight_tmp <= 320)
                            {
                                backlight_tmp = backlight_tmp + 4;
                            }
                            if(backlight_tmp < 0)
                            {
                                backlight_tmp = 0;
                            }
                            if(backlight_tmp > 320)
                            {
                                backlight_tmp = 320;
                            }
                            #if QTSIM_PLATFORM==0
                            va_display_lcd_set_backlight(backlight_tmp/8);
                            #endif
                            opt->sub_light->update_light(backlight_tmp);
                        }
                    }
                }
            }
            break;
        case 12:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->sub_dynamic->switch_cartoon_left();
                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->sub_dynamic->switch_cartoon_right();
                    }
                }
            }
            break;
        case 13:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->sub_statical->switch_cartoon_left();
                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->sub_statical->switch_cartoon_right();
                    }
                }
            }
            break;
        case 14:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->sub_brightness->switch_cartoon_left();
                        light_tmp--;
                        if(light_tmp<=0)
                        {
                            light_tmp=3;
                        }
                        opt->send_rgb_light_control_packet((unsigned char)(light_tmp));
                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        light_tmp++;
                        if(light_tmp>3)
                        {
                            light_tmp=1;
                        }
                        opt->sub_brightness->switch_cartoon_right();
                        opt->send_rgb_light_control_packet((unsigned char)(light_tmp));
                    }
                }
            }
            break;
        case 15:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        case 16:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        case 0:
            {
                if(target==opt->btn_win->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {
                        opt->subwindow_destroy();
                        opt->cur_page=-1;
                    }
                }
                else if(target==opt->btn_left->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
                else if(target==opt->btn_right->myobj)
                {
                    if(event->code==LV_EVENT_CLICKED)
                    {

                    }
                }
            }
            break;
        default:
            opt->cur_page=-1;
            break;
        }
    }
}

void* MainAPPStart::uart_start(void *arg)
{
    MainAPPStart* opt = (MainAPPStart*)arg;
    opt->send_init_finish_packet();
    while(1)
    {
        if(opt->BLE_Uart->isOpen())
        {
            opt->BLE_Uart->ReadData();
        }
        usleep(50000);
    }
}

//loop run(must achieve)
void MainAPPStart::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    //倒计时初始值--由用户数据传入--user->data
    static int count = 0;//static variable once assign
    if(scroll_flag!=0)
    {
        if(scroll_flag>0)
        {
            count++;
            scroll_anim_exe(count);
            if(count>=ANIM_STEP)
            {
                //anim finish
                imagelist_update();
                count = 0;
                scroll_flag--;
            }
        }
        else
        {
            count++;
            scroll_anim_exe(count);
            if(count>=ANIM_STEP)
            {
                //anim finish
                imagelist_update();
                count = 0;
                scroll_flag++;
            }
        }
    }
    if(!hide_flag)
    {
        hide_time++;
        if(hide_time>200)
        {
            cont->show(false);
            LV_LOG_USER("MAIN WINDOW HIDE");
            hide_flag=true;
            hide_time=0;
        }
    }   
}


#if 0
void MainAPPStart::TimerCB(lv_timer_t * tmr)
{
        LV_UNUSED(tmr);
        //倒计时初始值--由用户数据传入--user->data
        static int count = 60;//static variable once assign
        char timenumber[60];
        int current_time=0;
        sprintf(timenumber,"%d",count);
        count--;
        if(count>=0)
        {   anim_number->set_txt(timenumber);
            //image->set_angle()

        }
                if(count<0)
            {
            lv_timer_del((lv_timer_t *)timer);
            }

}
#endif



void MainAPPStart::scroll_anim_exe(int step)
{
    int step_len=(int)(scroll_len/ANIM_STEP);
    int cnt = 0;

    if(scroll_flag>0)
    {
        for(int i = 0; i < MAIN_MENU_NUM; i++)
        {
            if(i!=cur_head)
            {
                if((i-cur_head)%(MAIN_MENU_NUM)<0)
                {
                    if((i-cur_head)%MAIN_MENU_NUM==0)
                        cnt=0;
                    else
                        cnt=MAIN_MENU_NUM+((i-cur_head)%(MAIN_MENU_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(MAIN_MENU_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(ARC_LENTH/(MAIN_MENU_NUM-1)*cnt)-step_len*step)].x,point[(int)(abs(ARC_LENTH/(MAIN_MENU_NUM-1)*cnt)-step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(ARC_LENTH))].x,point[(int)(abs(ARC_LENTH))].y);
            }
        }
    }
    else if(scroll_flag<0)
    {
        for(int i = 0; i < MAIN_MENU_NUM; i++)
        {
            if(i!=cur_tail)
            {
                if((i-cur_head)%(MAIN_MENU_NUM)<0)
                {
                    if((i-cur_head)%MAIN_MENU_NUM==0)
                        cnt=0;
                    else
                        cnt=MAIN_MENU_NUM+((i-cur_head)%(MAIN_MENU_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(MAIN_MENU_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(ARC_LENTH/(MAIN_MENU_NUM-1)*abs(cnt))+step_len*step)].x,point[(int)(abs(ARC_LENTH/(MAIN_MENU_NUM-1)*abs(cnt))+step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(0))].x,point[(int)(abs(0))].y);
            }
        }
    }
}

void MainAPPStart::imagelist_update(void)
{
    int cnt=0,mid=0;
    if(cur_index<0)
    {
        if(cur_index%MAIN_MENU_NUM==0)
            cur_head=0;
        else
            cur_head=MAIN_MENU_NUM+(cur_index%(MAIN_MENU_NUM));
    }
    else
    {
        cur_head=cur_index%(MAIN_MENU_NUM);
    }

    mid=(cur_head+MAIN_MENU_NUM/2)%(MAIN_MENU_NUM);
    cur_tail=(cur_head+MAIN_MENU_NUM-1)%(MAIN_MENU_NUM);
    //LV_LOG_USER("cur_head=%d",cur_head);
    //LV_LOG_USER("cur_tail=%d",cur_tail);

    if((cur_index+MAIN_MENU_NUM/2)<0)
    {
        if((cur_index+MAIN_MENU_NUM/2)%MENU_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=MENU_IMAGE_NUM+((cur_index+MAIN_MENU_NUM/2)%(MENU_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+MAIN_MENU_NUM/2)%MENU_IMAGE_NUM;
    }

    //update list
    for(int i = 0; i < MAIN_MENU_NUM; i++)
    {
        if((i-cur_head)%(MAIN_MENU_NUM)<0)
        {
            if((i-cur_head)%MAIN_MENU_NUM==0)
                cnt=0;
            else
                cnt=MAIN_MENU_NUM+((i-cur_head)%(MAIN_MENU_NUM));
        }
        else
        {
            cnt = (i-cur_head)%(MAIN_MENU_NUM);
        }

        if(i==mid)
        {
            menulist[i]->set_size(100,100);
            menulist[i]->set_pos(point_list[MAIN_MENU_NUM/2].x,point_list[MAIN_MENU_NUM/2].y);
            menulist[i]->set_main_bg_img_src(imagelist.big[mid_image]);
            if(current_function != NULL)
            {
                current_function->set_txt(txtlist[mid_image]);
            }
        }
        else
        {
            menulist[i]->set_size(60,60);
            menulist[i]->set_pos(point_list[cnt].x,point_list[cnt].y);
        }
    }
}

void MainAPPStart::subwindow_create(void)
{
    switch (mid_image) {
    case 1:
        {
            if(sub_version==nullptr)
            {
                sub_version = new Version(m_parent);
                sub_version->sendcb(sub_callback);
            }
        }
        break;

    case 2:
        {
            if(sub_user==nullptr)
            {
                sub_user = new User(m_parent);
                sub_user->sendcb(sub_callback);
            }
        }
        break;
    case 3:
        {
            if(sub_language==nullptr)
            {
                sub_language = new Language(m_parent);
            }
        }
        break;
    case 4:
        {
            if(sub_wifi==nullptr)
            {
                sub_wifi = new Wifi(m_parent);
                sub_wifi->sendcb(sub_callback);
            }
        }
        break;
    case 5:
        {
            if(sub_bluetooth==nullptr)
            {
                sub_bluetooth = new Bluetooth(m_parent);
                 sub_bluetooth->sendcb(sub_callback);
            }
        }
        break;
    case 6:
        {
            if(sub_radio==nullptr)
            {
                sub_radio = new Net_radio(m_parent);
            }
        }
        break;
    case 7:
        {
            if(sub_sound==nullptr)
            {
                sub_sound = new Sounds(m_parent);
            }
        }
        break;
    case 8:
        {
            if(sub_volume_value==nullptr)
            {
                sub_volume_value = new Microphone(m_parent);
                char value_tmp[10];
                sprintf(value_tmp,"%d",volume_tmp/8);
                //sub_micphone->VOLUME_VALUE->set_txt(value_tmp);
                sub_volume_value->initial(volume_tmp,value_tmp);
            }
        }
        break;
    case 9:
        {
            if(sub_eq==nullptr)
            {
                sub_eq = new EQ_setting(m_parent);
            }
        }
        break;
    case 10:
        {
            if(sub_micphone==nullptr)
            {
                #if QTSIM_PLATFORM==0
                keydev_register_hook(NULL);
                #endif
                sub_micphone = new Volume(m_parent);
                char value_tmp[16];
                sprintf(value_tmp,"%d",microphone_tmp/8);
                sub_micphone->initial(microphone_tmp,value_tmp);
                sub_micphone->sendcb(sub_callback);
            }
        }
        break;
    case 11:
        {
            if(sub_light==nullptr)
            {
                sub_light = new Light(m_parent);
                char value_tmp[16];
                sprintf(value_tmp,"%d",backlight_tmp/8);
                sub_light->initial(backlight_tmp,value_tmp);
            }
        }
        break;
    case 12:
        {
            if(sub_dynamic==nullptr)
            {
                sub_dynamic = new Dynamic(m_parent);
                prepare_play_type = 1;
                if(cur_play_type != prepare_play_type)
                {
                    image_player_deinitial();
                }
                sub_dynamic->wallpaper_initial(cur_play_type);
                cur_play_type = prepare_play_type;
            }
        }
        break;
    case 13:
        {
            if(sub_statical==nullptr)
            {
                sub_statical = new Statical(m_parent);
                prepare_play_type = 0;
                if(cur_play_type != prepare_play_type)
                {
                    media_player_deinitial();
                }
                sub_statical->wallpaper_initial(cur_play_type);
                cur_play_type = prepare_play_type;
            }
        }
        break;
    case 14:
        {
            if(sub_brightness==nullptr)
            {
                sub_brightness = new Brightness(m_parent);
            }
        }
        break;
    case 15:
        {
            if(sub_clock==nullptr)
            {
                sub_clock = new Clock(m_parent);
                sub_clock->sendcb(sub_callback);
            }
        }
        break;

    case 16:
        {
            if(sub_alarm==nullptr)
            {
                         #if QTSIM_PLATFORM==0
                        keydev_register_hook(NULL);
                        #endif
                sub_alarm = new Alarm(m_parent);
                sub_alarm->sendcb(sub_callback);
            }
        }
        break;
    case 0:
        {
            if(sub_timer==nullptr)
            {
                #if QTSIM_PLATFORM==0
                keydev_register_hook(NULL);
                #endif
                sub_timer = new Timer(m_parent);
                sub_timer->sendcb(sub_callback);
            }
        }
        break;

    default:
        break;
    }
    sub_lyrics->show(false);
    cont->show(false);
}


void MainAPPStart::subwindow_destroy(void)
{
    switch (mid_image) {
    case 1:
        {
            if(sub_version!=nullptr)
            {
                delete sub_version;
                sub_version = nullptr;
            }
        }
        break;
    case 2:
        {
            if(sub_user!=nullptr)
            {
                delete sub_user;
                sub_user = nullptr;
            }
        }
        break;
    case 3:
        {
            if(sub_language!=nullptr)
            {
                delete sub_language;
                sub_language = nullptr;
            }
        }
        break;
    case 4:
        {
            if(sub_wifi!=nullptr)
            {
                delete sub_wifi;
                sub_wifi = nullptr;
            }
        }
        break;
    case 5:
        {
            if(sub_bluetooth!=nullptr)
            {
                delete sub_bluetooth;
                sub_bluetooth = nullptr;
            }
        }
        break;
    case 6:
        {
            if(sub_radio!=nullptr)
            {
                delete sub_radio;
                sub_radio = nullptr;
            }
        }
        break;
    case 7:
        {
            if(sub_sound!=nullptr)
            {
                delete sub_sound;
                sub_sound = nullptr;
            }
        }
        break;
    case 8:
        {
            if(sub_volume_value!=nullptr)
            {
                delete sub_volume_value;
                sub_volume_value = nullptr;
            }
        }
        break;
    case 9:
        {
            if(sub_eq!=nullptr)
            {
                delete sub_eq;
                sub_eq = nullptr;
            }
        }
        break;
    case 10:
        {
            if(sub_micphone!=nullptr)
            {
                delete sub_micphone;
                sub_micphone = nullptr;
            }
        }
        break;
    case 11:
        {
            if(sub_light!=nullptr)
            {
                delete sub_light;
                sub_light = nullptr;
            }
        }
        break;
    case 12:
        {
            if(sub_dynamic!=nullptr)
            {
                delete sub_dynamic;
                sub_dynamic = nullptr;
            }
        }
        break;
    case 13:
        {
            if(sub_statical!=nullptr)
            {
                delete sub_statical;
                sub_statical = nullptr;
            }
        }
        break;
    case 14:
        {
            if(sub_brightness!=nullptr)
            {
                delete sub_brightness;
                sub_brightness = nullptr;
            }
        }
        break;
    case 15:
        {
            if(sub_clock!=nullptr)
            {
                delete sub_clock;
                sub_clock = nullptr;
            }
        }
        break;
    case 16:
        {
            if(sub_alarm!=nullptr)
            {
                delete sub_alarm;
                sub_alarm = nullptr;
            }
        }
        break;
    case 0:
        {
            if(sub_timer!=nullptr)
            {
                delete sub_timer;
                sub_timer = nullptr;
            }
        }
        break;
    default:
        break;
    }
    sub_lyrics->show(true);
    cont->show(true);
    hide_time=0;
    hide_flag=false;
}

void MainAPPStart::sub_callback(void)
{
    Mainopt->subwindow_destroy();
    #if QTSIM_PLATFORM==0
    keydev_register_hook(decode_dev_callback);
    #endif
    Mainopt->cur_page=-1;
}

void MainAPPStart::media_player_initial(void)
{
    //video play
    #if QTSIM_PLATFORM==0
    player_ui_t* player_ui = media_get_player_data();
    tplayer_init(player_ui->tplayer, CEDARX_PLAYER);
    usleep(30000);
    #endif
}

void MainAPPStart::media_player_deinitial(void)
{
    #if QTSIM_PLATFORM==0
    player_ui_t *player_ui = media_get_player_data();
    tplayer_exit(player_ui->tplayer);
    #endif
}

void MainAPPStart::media_player_to_play(char* url)
{
    #if QTSIM_PLATFORM==0
    player_ui_t* player_ui = media_get_player_data();
    tplayer_play_url(player_ui->tplayer, url);
    tplayer_play(player_ui->tplayer);
    tplayer_volume(player_ui->tplayer,0);
    tplayer_set_looping(player_ui->tplayer, true);
    #endif
}

void MainAPPStart::image_player_initial(void)
{
    //photo play
    #if QTSIM_PLATFORM==0
    image_init();
    #endif
}

void MainAPPStart::image_player_deinitial(void)
{
    #if QTSIM_PLATFORM==0
    image_exit();
    #endif
}

void MainAPPStart::image_player_to_play(char* path)
{
    #if QTSIM_PLATFORM==0
    image_disp_cache_enable(1);
    image_show(path, IMAGE_SHOW_MODE_NORMAL);
    image_disp_cache_enable(0);
    #endif
}


void MainAPPStart::wallpaper_initial(void)
{
    image_player_initial();
    image_player_to_play("/mnt/UDISK/wallpaper/static/Butterflies-neon-light.jpg");
    cur_play_type = 0;  // 0 = image  1==video
    prepare_play_type = 0;  // 0 = image  1==video
}






void MainAPPStart::parse_msg(unsigned char *buf, int bufsize)
{
    int i=0;

    if(buf==NULL)
            return;

    for(i=0;i<bufsize;i++)
    {
        if(find_cmd == 0)
        {

            if(buf[i] == 0xfa && buf[i+1] == 0x01)
            {
                find_cmd=1;
                data_idx = 0;
                i=i+1;
            }
        }
        else if(find_cmd==1)
        {
            if(buf[i] != 0xf5)
            {
                rec_cmdbuf[data_idx++]=buf[i];
            }
            else
            {
                finish = 1;
                find_cmd=0;
            }
        }
    }

}

int MainAPPStart::uart_receive_proc(const unsigned char *rcv_buf, int len)
{
    if(len>(int)sizeof(parse_buff))
       return -1;

    memcpy(&parse_buff[read_lenth], rcv_buf, len);
    read_lenth += len;

    if(read_lenth > 1)
    {
        parse_msg(parse_buff, read_lenth);
    }

    if(finish == 1)
    {
        finish = 0;
        /*printf("rec_cmdbuf[");
        for (int i = 0; i < len; ++i)
        {
            printf("%02x ", rec_cmdbuf[i]);
        }
        printf("]\n");*/

        //LV_LOG_USER("Lyrice ->>  %s <<-",rec_cmdbuf);
        sub_lyrics->switch_cartoon_down((char*)rec_cmdbuf);
        memset(parse_buff, 0, sizeof(parse_buff));
        memset(rec_cmdbuf, 0, sizeof(rec_cmdbuf));
        read_lenth = 0;
    }

    return 0;
}




