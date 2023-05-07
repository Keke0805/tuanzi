#ifndef CONFIGCUSTOM_H
#define CONFIGCUSTOM_H

#define ZONE_INFO   "./resource/image/zone_list.cfg"
//color
#define  WHITE_COLOR          0xffffff      //白色
#define  LIGHTBLUE_COLOR      0x80ff        //淡蓝色

#define  DEVICE_FAME_COLOR      lv_color_hex(0x00736c)    //深青
#define  TABLE_SETTING_COLOR      lv_color_hex(0x00a0ea)  //天蓝
#define  GAS_FRAME_COLOR    lv_color_hex(0x82ccc9)        //淡绿
#define  GAS_BTN_COLOR      lv_color_hex(0x0168b7)        //灰蓝
#define  CABINET_FRAME_COLOR    lv_color_hex(0x546fb4)    //蓝色
#define  CABINET_ARROW_COLOR    lv_color_hex(0xffff00)    //深黄
#define  START_BTN_COLOR    lv_color_hex(0x014886)        //深蓝
#define  MENU_BTN_COLOR    lv_color_hex(0xbbbbbb)         //灰色

//CALENDAR
#define DAY_SUN       (1 << 0)
#define DAY_MON       (1 << 1)
#define DAY_TUES      (1 << 2)
#define DAY_WED       (1 << 3)
#define DAY_THUR      (1 << 4)
#define DAY_FRI       (1 << 5)
#define DAY_SAT       (1 << 6)
#define WDAY_EN       (1 << 7)
#define DAY_WORK      (DAY_MON|DAY_TUES|DAY_WED|DAY_THUR|DAY_FRI)
#define DAY_WEND      (DAY_SAT|DAY_SUN)
#define DAY_ALL       (DAY_WORK|DAY_WEND)
//msg callback to mainwindow gui
#define  MODULE_MAIN            1
#define  MODULE_GAS             2
#define  MODULE_FAN             3
#define  MODULE_OVEN            4
#define  MODULE_CABINET         5
#define  MODULE_MENU            6
#define  MODULE_SYSTEMSETTING   7
#define  MODULE_WEATHERINFO     8
#define  MODULE_PHOTO           9
#define  MODULE_VIDEO           10
#define  MODULE_MUSIC           11
#define  MODULE_CALENDAR        12

#define  MSGTYPE_CMD        1
#define  MSGTYPE_DATA       2
#define  MSGTYPE_SYNC       3
#define  MSGTYPE_HOME       4
#define  MSGTYPE_RERURN     5
#define  MSGTYPE_NEXTSCENE  6
#define  MSGTYPE_COMEBACK   7
#define  MSGTYPE_UPDATA     8

#define  CMD_MODULE_ENTER   1
#define  CMD_MODULE_EXIT    2
#define  MAIN_LIST_MAX      15
#define  PHOTOLIST_MAX      5
#define  PHOTODEC_MAX      	20
#define  FILE_LIST_MAX      6000
#define  VIDEOLIST_MAX      4
#define  VIDEODEC_MAX       21
#define  CITY_LIST_MAX      15
#define  CLOCK_LIST_MAX     9
#define  VOL_MAX     		10
#define  SETTIN_LIST_MAX    6
#define  USER_LIST_MAX      10

#define  LISTSCENE      "list"
#define  PLYINGSCENE    "plying"


typedef struct _lv_ui_inof_t
{
    int x;
    int y;
    int w;
    int h;
    int userdata;
    void *ui_patch;
} lv_ui_inof_t;

typedef struct _lv_slider_inof_t
{
    int x;
    int y;
    int w;
    int h;
    int minInde;
    int maxInde;
    int Inde;
    int userdata;
    void  *bg_patch;
    void  *curbg_patch;
    void  *cur_patch;
} lv_slider_inof_t;

typedef struct _lv_str_inof_t {
    int x;
    int y;
    int w;
    int h;
    int str_color;
    char *str_buff;
} lv_str_inof_t;

typedef enum {
    HEAD_ICON = 0,
    HEAD_ICON_RETURN,
    HEAD_ICON_SORT,
    HEAD_ICON_COPY,
    HEAD_ICON_DEL,
    HEAD_ICON_CHECK,
    HEAD_ICON_BALCK,
    HEAD_ICON_PLAYING,
    HEAD_ICON_PREV,
    HEAD_ICON_NEXT,
    HEAD_ICON_MODE,
    HEAD_ICON_MAX
}head_icon_t;

typedef enum {
    LIST_ICON = 0,
    LIST_ICON_PLAY,
    LIST_ICON_VOLA,
    LIST_ICON_VOLB,
    LIST_ICON_MAX
}list_icon_t;


#endif // CONFIGCUSTOM_H
