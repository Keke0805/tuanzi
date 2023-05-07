#ifndef MAINAPPSTART_H
#define MAINAPPSTART_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "packet.h"

#include   <iostream>
#include   <vector>
#include   <queue>

#define QUEUE_LENGTH  10

//uart
#include "machine/UartContext.h"

//subwindow
#include  "subwindow/sounds.h"
#include  "subwindow/bluetooth.h"
#include  "subwindow/wifi.h"
#include  "subwindow/version.h"
#include  "subwindow/user.h"
#include  "subwindow/kbscreen.h"
#include  "subwindow/language.h"
#include  "subwindow/eq_setting.h"
#include  "subwindow/net_radio.h"
#include  "subwindow/volume.h"
#include  "subwindow/light.h"
#include  "subwindow/dynamic.h"
#include  "subwindow/statical.h"
#include  "subwindow/brightness.h"
#include  "subwindow/clock.h"
#include  "subwindow/alarm.h"
#include  "subwindow/timer.h"
#include  "subwindow/microphone.h"
#include  "subwindow/lyrics.h"

typedef struct {
        int find_cmd;                       //是否收到帧头
        int finish;                         //是否收到完整一帧数据
        int idx;                            //结点
        int rec_len;                        //已经收到的字节数//有可能一次收不完一个命令帧

        unsigned char data_type;            //命令类型
        unsigned int data_len;              //数据内容总字节数
        unsigned char data_buf[1024];       //数据内容缓冲;
        unsigned char checksum;				//数据位数校验
        unsigned char packetInvalid;
}Amozol_packet_t;

typedef struct
{
    void* big[MENU_IMAGE_NUM];
    void* small[MENU_IMAGE_NUM];
}imagelist_t;

class MainAPPStart : public LvcppTimerTask
{
public:
    MainAPPStart(LvcppMainScreen* parent = nullptr);
    ~MainAPPStart(void);

protected:
    void ui_image_decode(void);
    void ui_image_free(void);
    void ui_txt_decede(void);

    imagelist_t imagelist;

    char*  txtlist[MENU_IMAGE_NUM];
    void*  MAIN_MENU_ALARM_B_PNG = NULL;
    void*  MAIN_MENU_ALARM_S_PNG = NULL;
    void*  MAIN_MENU_BLUETOOTH_B_PNG = NULL;
    void*  MAIN_MENU_BLUETOOTH_S_PNG = NULL;
    void*  MAIN_MENU_BRIGHTNESS_B_PNG = NULL;
    void*  MAIN_MENU_BRIGHTNESS_S_PNG = NULL;
    void*  MAIN_MENU_CLOCK_B_PNG = NULL;
    void*  MAIN_MENU_CLOCK_S_PNG = NULL;
    void*  MAIN_MENU_DYNAMIC_B_PNG = NULL;
    void*  MAIN_MENU_DYNAMIC_S_PNG = NULL;
    void*  MAIN_MENU_EQ_SETTING_B_PNG = NULL;
    void*  MAIN_MENU_EQ_SETTING_S_PNG = NULL;
    void*  MAIN_MENU_LANGUAGE_B_PNG = NULL;
    void*  MAIN_MENU_LANGUAGE_S_PNG = NULL;
    void*  MAIN_MENU_LIGHT_B_PNG = NULL;
    void*  MAIN_MENU_LIGHT_S_PNG = NULL;
    void*  MAIN_MENU_MICROPHONE_B_PNG = NULL;
    void*  MAIN_MENU_MICROPHONE_S_PNG = NULL;
    void*  MAIN_MENU_NET_RADIO_B_PNG = NULL;
    void*  MAIN_MENU_NET_RADIO_S_PNG = NULL;
    void*  MAIN_MENU_SOUNDS_B_PNG = NULL;
    void*  MAIN_MENU_SOUNDS_S_PNG = NULL;
    void*  MAIN_MENU_STATIC_B_PNG = NULL;
    void*  MAIN_MENU_STATIC_S_PNG = NULL;
    void*  MAIN_MENU_TIMER_B_PNG = NULL;
    void*  MAIN_MENU_TIMER_S_PNG = NULL;
    void*  MAIN_MENU_USER_B_PNG = NULL;
    void*  MAIN_MENU_USER_S_PNG = NULL;
    void*  MAIN_MENU_VERSION_B_PNG = NULL;
    void*  MAIN_MENU_VERSION_S_PNG = NULL;
    void*  MAIN_MENU_VOLUME_B_PNG = NULL;
    void*  MAIN_MENU_VOLUME_S_PNG = NULL;
    void*  MAIN_MENU_WIFI_B_PNG = NULL;
    void*  MAIN_MENU_WIFI_S_PNG = NULL;
    void*  MAIN_MENU_ALARM_1_PNG=NULL;
    void*  MAIN_MENU_ALARM_2_PNG=NULL;
private:
    void initial(void);

    LvcppMainScreen* m_screen;
    lv_obj_t* m_parent;

    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);

    int hide_time = 0;
    bool hide_flag = false;
    int cur_page=-1;
    Language* sub_language = nullptr;
    Version* sub_version = nullptr;
    Wifi* sub_wifi = nullptr;
    User* sub_user = nullptr;
    Bluetooth* sub_bluetooth=nullptr;
    Net_radio* sub_radio=nullptr;
    Sounds* sub_sound=nullptr;
    EQ_setting* sub_eq=nullptr;
    Volume* sub_micphone=nullptr;
    Light* sub_light=nullptr;
    Dynamic* sub_dynamic=nullptr;
    Statical* sub_statical=nullptr;
    Brightness* sub_brightness=nullptr;
    Clock* sub_clock=nullptr;
    Alarm* sub_alarm=nullptr;
    Timer* sub_timer=nullptr;
    Microphone* sub_volume_value=nullptr;
    void subwindow_create(void);
    void subwindow_destroy(void);

    int scroll_flag=0;
    int cur_index=0;
    int cur_head=0;
    int cur_tail=MAIN_MENU_NUM-1;
    int mid_image=MAIN_MENU_NUM/2;
    int scroll_len=0;
    LvcppLabel *alarm1=nullptr;
    LvcppLabel *time=nullptr;
    LvcppLabel *time2=nullptr;
    LvcppLabel *time3=nullptr;
    LvcppButton* btn_win=nullptr;
    LvcppButton* btn_left= nullptr;
    LvcppButton* btn_right= nullptr;

    lv_point_t point[ARC_LENTH+1];
    lv_point_t point_list[MAIN_MENU_NUM];
    LvcppScreen* cont = nullptr;
    LvcppLabel*current_function=nullptr;
    LvcppButton* menulist[MAIN_MENU_NUM];
    void draw_point(void);
    void lvgl_scroll_anim(void);
    void imagelist_update(void);
    void scroll_anim_exe(int step);

    void btn_callback_simulator(void);
    static void update_time(lv_event_t *event);
    static void btn_event_hander(lv_event_t *event);
    static void decode_dev_callback(uint32_t key_type,uint32_t key_value, lv_indev_state_t state);

    //lyrics
    std::queue<std::string> lyrics_queue;

    LvcppLabel* lyrics_win=nullptr;
    LvcppLabel* lyrics_before=nullptr;
    LvcppLabel* lyrics_after=nullptr;
    void lyrics_record(std::string lyrice);

    Lyrics* sub_lyrics = nullptr;

    //uart
	UartContext* BLE_Uart = nullptr;
    int read_len = 0;                   //已经读到数据长度
    unsigned char parse_buf[1024] ;
    Amozol_packet_t recPacket;
	static void* uart_start(void *arg);
	static void uart_recv_callback(const unsigned char* buf, int len);

    //parse
    void parse_packet(unsigned char *buf, int bufsize, Amozol_packet_t *recPacket);
    void packet_frame_data_parse(unsigned char data_type, unsigned int data_len, unsigned char* data_buf);
    bool send_packet(unsigned char data_type, unsigned char data_len, unsigned char* data_buf);

    //init
    bool send_init_finish_packet(void);
    bool send_open_device_packet(void);
    bool send_open_bluetooth_packet(void);

    //control
    bool send_device_control_packet(unsigned char cmd_type);
    bool send_bluetooth_control_packet(unsigned char cmd_type);

    bool send_rgb_light_control_packet(unsigned char cmd_type);
    bool send_microphone_control_packet(unsigned char cmd_type);
    bool send_volume_control_packet(unsigned char cmd_type);


    //player
    void wallpaper_initial(void);

    void media_player_initial(void);
    void media_player_deinitial(void);
    void media_player_to_play(char* url);

    void image_player_initial(void);
    void image_player_deinitial(void);
    void image_player_to_play(char* path);



    //parse

    int find_cmd = 0;
    int idx = 0;
    unsigned char rec_cmdbuf[1024];
    unsigned char parse_buff[1024];

    int data_idx = 0;
    int finish = 0;
    int read_lenth = 0;

    void parse_msg(unsigned char *buf, int bufsize);
    int uart_receive_proc(const unsigned char *rcv_buf, int len);

    int utf8_to_unicode(unsigned char* pInput, char* ppOutput);

};

#endif // MAINAPPSTART_H
