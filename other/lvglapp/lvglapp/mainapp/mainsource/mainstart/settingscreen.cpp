#include "settingscreen.h"
#include "stbimage/va_image.h"

#if (QTSIM_PLATFORM==0)
#ifdef __cplusplus
extern "C" {
#endif
#include  "mainstart/hotplugdetect/common/applib/applib.h"
#include  "mainstart/hotplugdetect/common/applib/app_config.h"
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif

const char* list_button[SETTING_LIST_ITEM] = {"网络连接","编号设置","亮度调节","清除信息","语言设置","版本信息"};
SettingScreen* setopt=nullptr;

SettingScreen::SettingScreen(lv_obj_t* parent)
{
    setopt = this;
    mscreen = new LvcppScreen(parent);
    mscreen->set_bg_color(lv_color_white(),LV_OPA_100);
    mparent = mscreen->get_screen();
    bg = parse_image_from_file("./resource/image/ui/bg.png");
    mscreen->showlogo((char*)bg, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    initial();
}


SettingScreen::~SettingScreen()
{
    if(settingview != nullptr)
    {
        delete settingview;
        settingview = nullptr;
    }
}


void SettingScreen::initial()
{
    if(set_tip == nullptr)
    {
        set_tip = new LvcppLabel(mparent);
        set_tip->set_pos(275,60);
        set_tip->set_size(480,65);
        set_tip->set_txt("设置");
        set_tip->txt_font_size(40,0);
        set_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        set_tip->set_main_border(3,lv_color_hex(0xffffff),LV_OPA_10);
        set_tip->txt_color(lv_color_white(),0);
        set_tip->set_style_bg_color(lv_color_white(),LV_OPA_10,0);
    }
    setting_window();
}
void SettingScreen::setting_window()
{
    if(settingview == nullptr)
    {
        settingview = new LvcppList(mparent);
        settingview->set_size(480,350);
        settingview->set_pos(275,125);
        //settingview->align(LV_ALIGN_TOP_MID,0,100);
        settingview->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        settingview->set_main_pad_all(0);
        settingview->set_main_border_width(0);
        settingview->set_main_radius(0);
        settingview->set_main_shadow_width(0);
        settingview->set_main_border(1,lv_color_hex(0xffffff),LV_OPA_20);
        settingview->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
        settingview->switch_select_state(0, lv_color_hex(0x000000), lv_color_hex(0x000000));
     }
    memset(&btnlist,0,sizeof(btn_list_t));
     for(int i= 0;i < SETTING_LIST_ITEM;i++)
    {
        if(btnlist.item[i] == nullptr)
        {
            btnlist.item[i] = new medialist(settingview->myobj);
            btnlist.item[i]->set_txt(list_button[i]);
            //LV_LOG_USER("list_button[i]=%s",list_button[i]);
            btnlist.item[i]->txt_list->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
        }
        settingview->set_select_state(0,lv_color_hex(0xff00ff));
    }
}

void SettingScreen::languagescreen_creat(void)
{
    if(languagesereen == nullptr)
    {
        languagesereen = new setlanguagescreen(mparent,bg);
    }
    languagesereen->sendcb(languagesereen_cb);
}
void SettingScreen::languagesereen_cb(void)
{
    if(setopt->languagesereen != nullptr)
    {
        delete setopt->languagesereen;
        setopt->languagesereen = NULL;
    }
}

void SettingScreen::version_creat(void)
{
    if(setversionscreen == nullptr)
    {
        setversionscreen = new setversion(mparent);
    }
    setversionscreen->sendcb(setversionscreen_cb);
}

void SettingScreen::setversionscreen_cb(void)
{
    if(setopt->setversionscreen != nullptr)
    {
        delete setopt->setversionscreen;
        setopt->setversionscreen = NULL;
    }
}

void SettingScreen::networkscreen_creat(void)
{
    if(networkscreen == nullptr)
    {
        networkscreen = new SettingNet(mparent);
    }
    networkscreen->sendcb(networkscreen_cb);
}

void SettingScreen::networkscreen_cb(void)
{
    if(setopt->networkscreen != nullptr)
    {
        delete setopt->networkscreen;
        setopt->networkscreen = NULL;
    }
}

void SettingScreen::briscreen_creat(void)
{
    if(briscreen == nullptr)
    {
        briscreen = new setbrighscreen(mparent,bg);
    }
    briscreen->sendcb(briscreen_cb);
}

void SettingScreen::briscreen_cb(void)
{
    if(setopt->briscreen != nullptr)
    {
        delete setopt->briscreen;
        setopt->briscreen = NULL;
    }
}


void SettingScreen::numscreen_creat(void)
{
    if(numscreen == nullptr)
    {
        numscreen = new setnumberscreen(mparent,bg);
    }
    numscreen->sendcb(numscreen_cb);
}

void SettingScreen::numscreen_cb(void)
{
    if(setopt->numscreen != nullptr)
    {
        delete setopt->numscreen;
        setopt->numscreen = NULL;
    }
}

void SettingScreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    SettingScreen* opt = (SettingScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);


    if(target==opt->btnlist.item[0]->txt_list->myobj)//网络
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->networkscreen_creat();
        }
    }
    else if(target==opt->btnlist.item[1]->txt_list->myobj)//编号
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->numscreen_creat();
        }
    }
    else if(target==opt->btnlist.item[2]->txt_list->myobj)//亮度
    {

        if(event->code == LV_EVENT_CLICKED)
        {
            opt->briscreen_creat();
        }
    }
    else if(target==opt->btnlist.item[3]->txt_list->myobj)//清除
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->zp_param_clear();
        }
    }
    else if(target==opt->btnlist.item[4]->txt_list->myobj)//语言
    {

        if(event->code == LV_EVENT_CLICKED)
        {
            opt->languagescreen_creat();
        }
    }
    else if(target==opt->btnlist.item[5]->txt_list->myobj)//版本
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->version_creat();
        }
    }
}

void SettingScreen::deinitial()
{


}

void SettingScreen::zp_param_clear(void)
{
    memset(&g_CanvasInfo,0,sizeof(zpc_canvas_param_t));
    g_CanvasInfo.clear_flag = 0;
    strcpy(g_CanvasInfo.username, "姓名");
    strcpy(g_CanvasInfo.company, "单位");
    strcpy(g_CanvasInfo.duty, "职务");
    strcpy(g_CanvasInfo.other, "");

    strcpy(g_CanvasInfo.layout.BgColor, "FF0000");
    strcpy(g_CanvasInfo.layout.BgImg, "");
    for(int i=0;i<MAX_DETAIL_NUM;i++)
    {
        if(i==0)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "username");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=200;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=200;
            g_CanvasInfo.layout.detail[i].TextSize=200;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "fac000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=2;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=50;
            g_CanvasInfo.layout.detail[i].TextType=2;
        }
        else if(i==1)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "company");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=0;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=80;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
        else if(i==2)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "duty");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=500;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=100;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=3;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
        else if(i==3)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "other");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=500;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=100;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
    }
    #if QTSIM_PLATFORM==0
    msg_apps_t msg;
    memset(&msg,0,sizeof(msg_apps_t));
    msg.type = MSG_UPDATE_CANVAS;
    SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
    #endif
}


