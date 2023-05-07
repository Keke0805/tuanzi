#ifndef CUSTOMER_CONFIG_H
#define CUSTOMER_CONFIG_H

//screen_size
#define   SCREEN_HOR_SIZE  1024
#define   SCREEN_VER_SIZE  600

#define   CANVAS_HOR_SIZE  512
#define   CANVAS_VER_SIZE  300

#define MAX_DATA_LENGTH               1024
#define MAX_DETAIL_NUM                4
#define MAX_DETAIL_DATA_LENGTH        32

#define SERVER_PORT 8008

#define MSG_CLIENT_IN     1   // 有客户端连接
#define MSG_CLIENT_OUT    2   // 有客户端断开
#define MSG_CLIENT_MSG    3   // 客户端发送来的消息


//config path
#define LVGL_BG_IMAGE_PATH		"S:/resource/image/bg/"

#define APP_GLOBAL_CFG			"./GlobalSetting.cfg"

#define IDCARD_PATH		"./resource/image/idcard/idcard.bmp"

#define TEMP_PATH		"./resource/image/bg/temp.png"

#define FONT_PATH		"./resource/font/temp.ttf"

#define USB_COPY_FONT_PATH		"./resource/"
#define USB_COPY_IMAGE_PATH		"./resource/image/"

#define USB_FONT_PATH		"./resource/font"
#define USB_IMAGE_PATH		"./resource/image/bg"

#define APP_BAT_CAPATITY_FILE   "/sys/class/power_supply/cw-bat/capacity"
#define APP_POWER_STATE_FILE    "/sys/class/power_supply/ats3609-usb/device/power_state"

//image
#define BG_PNG  "S:/resource/image/ui/bg.png"
#define GO_BACK  "S:/resource/image/ui/go_back.png"
#define PAGE_BUTTON  "S:/resource/image/ui/page_button.png"
#define INCARD_BUTTON  "S:/resource/image/ui/idcard.png"
#define PAINT_TEXT_BG_BUTTON  "S:/resource/image/ui/paint_text_bg.png"
#define TIME_BUTTON  "S:/resource/image/ui/time.png"
#define WIFI_BUTTON  "S:/resource/image/ui/wifi.png"
#define FH_AX_BUTTON  "S:/resource/image/ui/fh_ax.png"
#define FH_BUTTON  "S:/resource/image/ui/fh.png"
#define BOX_BUTTON  "S:/resource/image/ui/box.png"

//num
#define PNG_0  "S:/resource/image/num/0.png"
#define PNG_1  "S:/resource/image/num/1.png"
#define PNG_2  "S:/resource/image/num/2.png"
#define PNG_3  "S:/resource/image/num/3.png"
#define PNG_4  "S:/resource/image/num/4.png"
#define PNG_5  "S:/resource/image/num/5.png"
#define PNG_6  "S:/resource/image/num/6.png"
#define PNG_7  "S:/resource/image/num/7.png"
#define PNG_8  "S:/resource/image/num/8.png"
#define PNG_9  "S:/resource/image/num/9.png"
#define SPACE_PNG  "S:/resource/image/num/space.png"
#define DOT_PNG  "S:/resource/image/num/dot.png"

//speech
#define ON_PNG  "S:/resource/image/speech/ON.png"
#define OFF_PNG  "S:/resource/image/speech/OFF.png"
#define RESRT_PNG  "S:/resource/image/speech/reset.png"
#define TIME_PNG  "S:/resource/image/speech/time.png"
#define TIMEH_PNG  "S:/resource/image/speech/timeh.png"

//single
#define ATTENDANCE_PNG  "S:/resource/image/single/attendance.png"
#define ATTENDANCEH_PNG  "S:/resource/image/single/attendanceH.png"

#define BALLOT_PNG  "S:/resource/image/single/ballot.png"
#define BALLOTH_PNG  "S:/resource/image/single/ballotH.png"

#define MEETING_PNG  "S:/resource/image/single/meeting.png"
#define MEETINGH_PNG  "S:/resource/image/single/meetingH.png"

#define MESSAGE_PNG  "S:/resource/image/single/message.png"
#define MESSAGEH_PNG  "S:/resource/image/single/messageH.png"

#define RENAME_PNG  "S:/resource/image/single/rename.png"
#define RENAMEH_PNG  "S:/resource/image/single/renameH.png"

#define SERVICE_PNG  "S:/resource/image/single/service.png"
#define SERVICEH_PNG  "S:/resource/image/single/serviceH.png"

#define SETTING_PNG  "S:/resource/image/single/setting.png"
#define SETTINGH_PNG  "S:/resource/image/single/settingH.png"

#define SPEECH_PNG  "S:/resource/image/single/speech.png"
#define SPEECHH_PNG  "S:/resource/image/single/speechH.png"

//photo
#define TEA_PNG  "S:/resource/image/service/tea.png"

#define PAPER_PNG  "S:/resource/image/service/paper_and_pen.png"

#define MICROPHOME_PNG  "S:/resource/image/service/microphone.png"

#define WAITER_PNG  "S:/resource/image/service/waiter.png"

#define REQUESTS_PNG  "S:/resource/image/service/Other_requests.png"

//meeting
#define AGENDA_PNG  "S:/resource/image/meeting/Agenda.png"
#define AGENDAH_PNG  "S:/resource/image/meeting/Agendah.png"

#define CONTENT_PNG  "S:/resource/image/meeting/Content.png"
#define CONTENTH_PNG  "S:/resource/image/meeting/Contenth.png"

//photo
#define S_1_PNG  "1.png"
#define S_2_PNG  "2.png"
#define S_3_PNG  "3.png"
#define S_4_PNG  "4.png"
#define S_5_PNG  "5.png"

#define B_1_PNG  "1.png"
#define B_2_PNG  "2.png"
#define B_3_PNG  "3.png"
#define B_4_PNG  "4.png"
#define B_5_PNG  "5.png"

//duty sign
#define DUTY_SIGN_TMP    "S:/resource/image/ui/duty_bg.png"

#define IAMGE_JIAO_TMP   "S:/resource/image/ui/image_jiao.png"
#define FONT_JIAO_TMP    "S:/resource/image/ui/font_jiao.png"
#define TYPE_JIAO_TMP    "S:/resource/image/ui/type_jiao.png"

typedef struct detail_param_s
{
    char ElementNo[MAX_DETAIL_DATA_LENGTH]; //ElementNo
    int ElePointX;                         //ElePointX
    int ElePointY;                         //ElePointY
    int EleWidth;                       //EleWidth
    int EleHeight;                      //EleHeight
    int TextSize;                       //TextSize
    char TextColor[MAX_DETAIL_DATA_LENGTH]; //TextColor
    char TextFont[MAX_DETAIL_DATA_LENGTH];  //TextFont
    int HorizontalAlign;                //HorizontalAlign
    int TextLineSpace;                  //TextLineSpace
    int TextLetterSpace;                //TextLetterSpace
    int TextType;                       //TextType
}detail_param_t;

typedef struct layout_param_s
{
    char BgColor[MAX_DATA_LENGTH];//BackgroundColor
    char BgImg[MAX_DATA_LENGTH];//BackgroundImage
    detail_param_t detail[MAX_DETAIL_NUM];
}layout_param_t;

typedef struct zpc_param_s
{
    int clear_flag;
    char username[MAX_DATA_LENGTH];//username
    char company[MAX_DATA_LENGTH];//company
    char duty[MAX_DATA_LENGTH];//duty
    char other[MAX_DATA_LENGTH];//other
    layout_param_t layout;
}zpc_canvas_param_t;

extern zpc_canvas_param_t g_CanvasInfo;
extern zpc_canvas_param_t g_RenameInfo;
extern zpc_canvas_param_t g_RenameSaveInfo;
#endif // CUSTOMER_CONFIG_H
