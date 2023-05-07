#include "renamescreen.h"
#include "mainstart/zpclient/zpclient.h"
#include "stbimage/va_image.h"
#include <math.h>
#include "lv_drivers/indev/evdev.h"

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

#define FILE_PATH_LONG 		1024

using namespace LVGLIMAGE;
using namespace LVGLOPTAPI;

zpc_canvas_param_t g_RenameInfo;

zpc_canvas_param_t g_RenameSaveInfo;

RenameScreen* renameopt=nullptr;
RenamebottomScreen* renamebottomopt= nullptr;
RenameheadScreen * renameheadopt= nullptr;
RenameinputScreen *renameinpuopt= nullptr;
RenamefontsetScreen * renamfontsetwinopt = nullptr;
RenameeffectScreen *renameeffectopt = nullptr;
RenamecolorScreen *color_setopt = nullptr;
RenamebgcolorScreen *bg_color_setopt = nullptr;
RenameboxtScreen *renameboxopt = nullptr;
static void* idcard= nullptr;
static void* idcard_big= nullptr;
static pthread_mutex_t decodelock;
static int state = 0;
static int param_state = 3;
static int param_state_hide = 0;
static int company_state_hide = 0;
static int duty_state_hide = 0;
//static int color_tmp = 0;
 static  int tmp_view = 0;
 static int color_tmp = 0;

 static int key_right_tmp = 0;
 enum
 {
     MOUSE_KEY_LEFT = 272,
     MOUSE_KEY_RIGHT = 273,
 };

 static void evdev_callback(uint32_t key_type,uint32_t key_value, lv_indev_state_t state)
 {
     //LV_LOG_USER("evdev_callback:(%d, %d, %d)\n", key_type, key_value, (int)state);
     if(key_type == MOUSE_KEY_LEFT)
     {
     }
     else if(key_type == MOUSE_KEY_RIGHT)
     {
         //LV_LOG_USER("!!!!!!!!!!!!!!!!key_right_tmp =%d !!!!!!!!!!!!!!!",key_right_tmp);
        if(key_right_tmp == 1)
        {
            if(renameopt->re_box == NULL)
            {
                //LV_LOG_USER("!!!!!!!!!!!!!!!!Rename_box_create!!!!!!!!!!!!!!!");
                renameopt->Rename_box_create();
            }
            else
            {
                //LV_LOG_USER("!!!!!!!!!!!!!!!!!!Rename_box_show!!!!!!!!!!!!!!");
                renameboxopt->mscreen->show(true);
            }
        }
     }
 }


#if (QTSIM_PLATFORM==0)
void RenameScreen::idcard_sys_proc(msg_apps_t *msg)
{
    switch(msg->type)
    {

        case MSG_UPDATE_IDCARD:
        {
            LV_LOG_USER("!!!! MSG_UPDATE_IDCARD !!!!\n");
            renameopt->sync_flag = 1;
            break;
        }
        case MSG_UPDATE_CANVAS:
        {
            LV_LOG_USER("!!!! MSG_UPDATE_CANVAS !!!!\n");
            renameopt->sync_flag = 1;
            break;
        }
        case MSG_ADD_FONT:
        {
            LV_LOG_USER("!!!! MSG_ADD_FONT !!!!\n");
            renameopt->font_flag = 1;
            break;
        }
        case MSG_ADD_TEMP:
        {
            LV_LOG_USER("!!!! MSG_ADD_TEMP !!!!\n");
            renameopt->temp_flag = 1;
            break;
        }
        default:
        break;
    }
}

#endif

void RenameScreen::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;//static variable once assign
    if(sync_flag)
    {
        zp_param_sync();
        sync_flag = 0;
    }
    if(font_flag)
    {
        if(access(FONT_PATH,F_OK)==0)
        {
            if(renameeffectopt->change_refont_style->get_option_cnt()<10)
            {
                renameeffectopt->change_refont_style->add_option("用户",9);
            }
        }
        font_flag = 0;
        sync_flag = 1;
    }
    if(temp_flag)
    {
        if(access(TEMP_PATH,F_OK)==0)
        {
            if(renamebottomopt->select_photo_bg->get_option_cnt()<7)
            {
                renamebottomopt->select_photo_bg->add_option("temp.png",6);
            }
        }
        temp_flag = 0;
        sync_flag = 1;
    }
}

RenameScreen::RenameScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(lv_scr_act());
    //mscreen->set_bg_color(lv_color_hex(0x222222),LV_OPA_40);
    mparent = mscreen->get_screen();
    renameopt = this;
    initial();
    evdev_register_hook(evdev_callback);
    #if (QTSIM_PLATFORM==0)
    SSTAR_RegisterApplib(APP_NAME_IDCARD, idcard_sys_proc);
    #endif
    renametimer = startTimer(50,this);
}

RenameScreen::~RenameScreen()
{
    #if (QTSIM_PLATFORM==0)
    SSTAR_UnRegisterApplib(APP_NAME_IDCARD, idcard_sys_proc);
    #endif
    if(font_size != nullptr)
    {
        delete font_size;
        font_size = NULL;
    }
    if(rgb_color1 != nullptr)
    {
        delete rgb_color1;
        rgb_color1 = NULL;
    }
    if(rgb_color2 != nullptr)
    {
        delete rgb_color2;
        rgb_color2 = NULL;
    }
    if(rgb_color3 != nullptr)
    {
        delete rgb_color3;
        rgb_color3 = NULL;
    }
    if(rgb_bg_color1 != nullptr)
    {
        delete rgb_bg_color1;
        rgb_bg_color1 = NULL;
    }
    if(rgb_bg_color2 != nullptr)
    {
        delete rgb_bg_color2;
        rgb_bg_color2 = NULL;
    }
    if(rgb_bg_color3 != nullptr)
    {
        delete rgb_bg_color3;
        rgb_bg_color3 = NULL;
    }
    if(refont_style != nullptr)
    {
        delete refont_style;
        refont_style = NULL;
    }
    if(refont_size_style != nullptr)
    {
        delete refont_size_style;
        refont_size_style = NULL;
    }
    if(font_size_tip != nullptr)
    {
        delete font_size_tip;
        font_size_tip = NULL;
    }
    if(switch_object != nullptr)
    {
        delete switch_object;
        switch_object = NULL;
    }
    if(rgb_color_tip != nullptr)
    {
        delete rgb_color_tip;
        rgb_color_tip = NULL;
    }
    if(switch_object != nullptr)
    {
        delete switch_object;
        switch_object = NULL;
    }
    if(x != nullptr)
    {
        delete x;
        x = NULL;
    }
    if(y != nullptr)
    {
        delete y;
        y = NULL;
    }
    if(wide != nullptr)
    {
        delete wide;
        wide = NULL;
    }
    if(usre_param != nullptr)
    {
        delete usre_param;
        usre_param = NULL;
    }
    if(show_preview != nullptr)
    {
        delete show_preview;
        show_preview = NULL;
    }
    if(mscreen != nullptr)
    {
        delete mscreen;
        mscreen = NULL;
    }
}

void RenameScreen::RenameInfo_param_initial(void)
{
    memset(&g_RenameInfo,0,sizeof(zpc_canvas_param_t));
    g_RenameInfo.clear_flag = 0;
    strcpy(g_RenameInfo.username, "姓名");
    strcpy(g_RenameInfo.company, "单位");
    strcpy(g_RenameInfo.duty, "职务");
    strcpy(g_RenameInfo.other, "");

    strcpy(g_RenameInfo.layout.BgColor, "FF0000");
    strcpy(g_RenameInfo.layout.BgImg, "");
    for(int i=0;i<MAX_DETAIL_NUM;i++)
    {
        if(i==0)
        {
            strcpy(g_RenameInfo.layout.detail[i].ElementNo, "username");
            g_RenameInfo.layout.detail[i].ElePointX=0;
            g_RenameInfo.layout.detail[i].ElePointY=200;
            g_RenameInfo.layout.detail[i].EleWidth=1024;
            g_RenameInfo.layout.detail[i].EleHeight=200;
            g_RenameInfo.layout.detail[i].TextSize=200;
            strcpy(g_RenameInfo.layout.detail[i].TextColor, "fac000");
            strcpy(g_RenameInfo.layout.detail[i].TextFont, "楷体");
            g_RenameInfo.layout.detail[i].HorizontalAlign=2;
            g_RenameInfo.layout.detail[i].TextLineSpace=0;
            g_RenameInfo.layout.detail[i].TextLetterSpace=50;
            g_RenameInfo.layout.detail[i].TextType=2;
        }
        else if(i==1)
        {
            strcpy(g_RenameInfo.layout.detail[i].ElementNo, "company");
            g_RenameInfo.layout.detail[i].ElePointX=0;
            g_RenameInfo.layout.detail[i].ElePointY=0;
            g_RenameInfo.layout.detail[i].EleWidth=1024;
            g_RenameInfo.layout.detail[i].EleHeight=80;
            g_RenameInfo.layout.detail[i].TextSize=80;
            strcpy(g_RenameInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_RenameInfo.layout.detail[i].TextFont, "楷体");
            g_RenameInfo.layout.detail[i].HorizontalAlign=1;
            g_RenameInfo.layout.detail[i].TextLineSpace=0;
            g_RenameInfo.layout.detail[i].TextLetterSpace=5;
            g_RenameInfo.layout.detail[i].TextType=0;
        }
        else if(i==2)
        {
            strcpy(g_RenameInfo.layout.detail[i].ElementNo, "duty");
            g_RenameInfo.layout.detail[i].ElePointX=0;
            g_RenameInfo.layout.detail[i].ElePointY=500;
            g_RenameInfo.layout.detail[i].EleWidth=1024;
            g_RenameInfo.layout.detail[i].EleHeight=100;
            g_RenameInfo.layout.detail[i].TextSize=80;
            strcpy(g_RenameInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_RenameInfo.layout.detail[i].TextFont, "楷体");
            g_RenameInfo.layout.detail[i].HorizontalAlign=3;
            g_RenameInfo.layout.detail[i].TextLineSpace=0;
            g_RenameInfo.layout.detail[i].TextLetterSpace=5;
            g_RenameInfo.layout.detail[i].TextType=0;
        }
        else if(i==3)
        {
            strcpy(g_RenameInfo.layout.detail[i].ElementNo, "other");
            g_RenameInfo.layout.detail[i].ElePointX=0;
            g_RenameInfo.layout.detail[i].ElePointY=500;
            g_RenameInfo.layout.detail[i].EleWidth=1024;
            g_RenameInfo.layout.detail[i].EleHeight=100;
            g_RenameInfo.layout.detail[i].TextSize=80;
            strcpy(g_RenameInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_RenameInfo.layout.detail[i].TextFont, "楷体");
            g_RenameInfo.layout.detail[i].HorizontalAlign=1;
            g_RenameInfo.layout.detail[i].TextLineSpace=0;
            g_RenameInfo.layout.detail[i].TextLetterSpace=5;
            g_RenameInfo.layout.detail[i].TextType=0;
        }
    }
    //memset(&g_RenameSaveInfo,0,sizeof(zpc_canvas_param_t));
    //memcpy(&g_RenameSaveInfo,&g_RenameInfo,sizeof(zpc_canvas_param_t));
    font_initial();
}


void RenameScreen::zp_param_sync(void)
{
    //LV_LOG_USER("---------------------------------");
    memset(&g_RenameInfo,0,sizeof(zpc_canvas_param_t));

    memcpy(&g_RenameInfo,&g_CanvasInfo,sizeof(zpc_canvas_param_t));
    //renameopt->font_reset();
    //LV_LOG_USER("---------------------------------");
    renameopt->font_initial_zp();
    char font_font_bet[16];
    sprintf(font_font_bet,"%d",g_RenameInfo.layout.detail[3].TextLetterSpace);
    renameeffectopt->font_between->set_txt(font_font_bet);
    renameheadopt->usre_duty_label->set_style_text_letter_space(g_RenameInfo.layout.detail[2].TextLetterSpace*680/1024,0);
    renameheadopt->usre_duty_label->txt_align(g_RenameInfo.layout.detail[2].HorizontalAlign);
    renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
    renameheadopt->usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX*680/1024,g_RenameInfo.layout.detail[2].ElePointY*680/1024);
    renameheadopt->usre_duty_label->set_size(g_RenameInfo.layout.detail[2].EleWidth*680/1024,g_RenameInfo.layout.detail[2].EleHeight*680/1024);

    renameheadopt->usre_company_label->set_style_text_letter_space(g_RenameInfo.layout.detail[1].TextLetterSpace*680/1024,0);
    renameheadopt->usre_company_label->txt_align(g_RenameInfo.layout.detail[1].HorizontalAlign);
    renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);
    renameheadopt->usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX*680/1024,g_RenameInfo.layout.detail[1].ElePointY*680/1024);
    renameheadopt->usre_company_label->set_size(g_RenameInfo.layout.detail[1].EleWidth*680/1024,g_RenameInfo.layout.detail[1].EleHeight*680/1024);//*1024/680

    renameheadopt->usre_param_label->set_style_text_letter_space(g_RenameInfo.layout.detail[0].TextLetterSpace*680/1024,0);
    renameheadopt->usre_param_label->txt_align(g_RenameInfo.layout.detail[0].HorizontalAlign);
    renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
    renameheadopt->usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX*680/1024,g_RenameInfo.layout.detail[0].ElePointY*680/1024);
    renameheadopt->usre_param_label->set_size(g_RenameInfo.layout.detail[0].EleWidth*680/1024,g_RenameInfo.layout.detail[0].EleHeight*680/1024);
    //LV_LOG_USER("---------------------------------");

    param_state_hide = 0;
    company_state_hide = 0;
    duty_state_hide = 0;
    param_state = 3;
    //LV_LOG_USER("aaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    renameinpuopt->clean_flag_dropdwon();

    renameeffectopt->change_font_size_and_between_auto(1,3);
    renameeffectopt->change_font_size_and_between_auto(2,3);
    renameeffectopt->change_font_size_and_between_auto(3,3);

    //update
    uint8_t color[3]={0};
    color_setopt->hexStringToByte(color,g_RenameInfo.layout.BgColor,strlen(g_RenameInfo.layout.BgColor));
    renamebottomopt->select_rgb_bg->set_main_bg_color(lv_color_make(color[0],color[1],color[2]),LV_OPA_100);//单色
    renameheadopt->mscreen->set_main_bg_color(lv_color_make(color[0],color[1],color[2]),LV_OPA_100);

    if(strcmp(g_RenameInfo.layout.BgImg,S_1_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(0);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,S_2_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(1);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,S_3_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(2);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,S_4_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(3);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,S_5_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(4);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,"temp.png")==0)
    {
        renamebottomopt->select_photo_bg->set_selected(6);//底图
    }
    else
    {
        renamebottomopt->select_photo_bg->set_selected(5);//底图
    }
    //LV_LOG_USER("---------------------------------");
    if(strcmp(g_RenameInfo.layout.BgImg,"未使用")!=0 && strlen(g_RenameInfo.layout.BgImg)!=0)
    {
        pthread_mutex_lock(&decodelock);
        if(idcard!=nullptr)
        {
            free_image(idcard);
            idcard = nullptr;
        }

        char imgPath[FILE_PATH_LONG];
        memset(imgPath,0,FILE_PATH_LONG);
        sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,g_RenameInfo.layout.BgImg);
        idcard = resize_image(imgPath,680,400);
        pthread_mutex_unlock(&decodelock);

        renameheadopt->mscreen->set_main_bg_img_src(idcard);
        renamebottomopt->select_rgb_bg->set_main_bg_img_src(DUTY_SIGN_TMP);
        if(idcard_big!=nullptr)
        {
            free_image(idcard_big);
            idcard_big = nullptr;
        }
    }
    else
    {

        renamebottomopt->select_rgb_bg->set_main_bg_img_src(NULL);
        renameheadopt->mscreen->set_main_bg_img_src(NULL);
        if(idcard!=nullptr)
        {
            free_image(idcard);
            idcard = nullptr;
        }
    }
    //LV_LOG_USER("---------------------------------");
    renameheadopt->usre_param_label->show(true);
    renameheadopt->usre_param_label->txt_color(renameopt->label_dsc0.color,0);
    renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);

    renameheadopt->usre_company_label->show(true);
    renameheadopt->usre_company_label->txt_color(renameopt->label_dsc1.color,0);
    renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);

    renameheadopt->usre_duty_label->show(true);
    renameheadopt->usre_duty_label->txt_color(renameopt->label_dsc2.color,0);
    renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_100);


    renameinpuopt->usre_param->set_main_bg_img_src(NULL);
    renameinpuopt->usre_param->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);

    renameinpuopt->usre_company->set_main_bg_img_src(NULL);
    renameinpuopt->usre_company->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);

    renameinpuopt->usre_duty->set_main_bg_img_src(NULL);
    renameinpuopt->usre_duty->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);

    renameinpuopt->input_pos_update();
    renameinpuopt->show_input_param(1);
    renameinpuopt->show_input_param(2);
    renameinpuopt->show_input_param(3);
    renameheadopt->param_change(param_state);
    color_setopt->get_rgb_vlaue(param_state);

    renameinpuopt->rename_button->clicked_enable(false);
    renameinpuopt->font_w_up->clicked_enable(false);
    renameinpuopt->font_W_down->clicked_enable(false);
    renameinpuopt->font_x_up->clicked_enable(false);
    renameinpuopt->font_x_down->clicked_enable(false);
    renameinpuopt->font_y_up->clicked_enable(false);
    renameinpuopt->font_y_down->clicked_enable(false);
    renameinpuopt->font_h_up->clicked_enable(false);
    renameinpuopt->font_h_down->clicked_enable(false);
    renameeffectopt->font_size_up->clicked_enable(false);
    renameeffectopt->font_size_down->clicked_enable(false);
    renameeffectopt->font_between_up->clicked_enable(false);
    renameeffectopt->font_between_down->clicked_enable(false);
    //LV_LOG_USER("---------------------------------");
}

void RenameScreen::initial()
{
    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }

    /*
    if(cbuf == nullptr)
    {
        cbuf = create_canvas();
    }*/


    //TextArea_initial();
    //dropdown_initial();
    //label_initial();
    //switch_object_get_int();
    RenameInfo_param_initial();
    Rename_head_Screen_create();
    //repaint_canvas();
    Rename_bottom_Screen_create();
    Rename_input_Screen_create();
    Rename_effect_Screen_create();

    if(renameopt->re_color == NULL)
    {
        //LV_LOG_USER("new color");
        renameopt->Rename_color_Screen();
        color_setopt->mscreen->show(false);
    }
    if(renameopt->bg_color == NULL)
    {
        //LV_LOG_USER("new color");
        renameopt->Rename_bg_color_Screen();
        bg_color_setopt->mscreen->show(false);
    }
    renamfontsetwinopt->zp_param_clear();

}

void RenameScreen::TextArea_initial()
{
    if(show_preview == nullptr)
    {
        show_preview = new LvcppButton(mparent);
        show_preview->set_pos(870,500);
        show_preview->set_size(100,50);
        show_preview->add_txt("确认");
        show_preview->txt_font_size(25,0);
        show_preview->txt_align(LV_ALIGN_CENTER,0,0);
        show_preview->set_style_text_font(myfont->font(),0);
        show_preview->set_main_radius(10);
        show_preview->txt_color(lv_color_black());
        show_preview->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        show_preview->set_main_bg_color(lv_color_white(),LV_OPA_60);
        show_preview->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_size == nullptr)
    {
        font_size = new LvcppButton(mparent);
        font_size->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_size->set_pos(775,180);
        font_size->set_size(100,50);
        font_size->add_txt("200");
        font_size->set_main_radius(10);
        font_size->txt_center();
        font_size->txt_color(lv_color_black());
        font_size->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        font_size->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //font_size->set_accepted_chars("0123456789");
        font_size->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_space_between == nullptr)
    {
        font_space_between = new LvcppButton(mparent);
        font_space_between->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_space_between->set_pos(550,180);
        font_space_between->set_size(100,50);
        font_space_between->add_txt("50");
        font_space_between->txt_center();
        font_space_between->set_main_radius(10);
        font_space_between->txt_color(lv_color_black());
        font_space_between->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        font_space_between->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //font_size->set_accepted_chars("0123456789");
        font_space_between->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_line_between == nullptr)
    {
        font_line_between = new LvcppButton(mparent);
        font_line_between->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_line_between->set_pos(660,180);
        font_line_between->set_size(100,50);
        font_line_between->add_txt("0");
        font_line_between->txt_center();
        font_line_between->set_main_radius(10);
        font_line_between->txt_color(lv_color_black());
        font_line_between->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        font_line_between->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //font_size->set_accepted_chars("0123456789");
        font_line_between->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(usre_param == nullptr)
    {
        usre_param = new LvcppButton(mparent);
        usre_param->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        usre_param->set_pos(660,10);
        usre_param->set_size(350,50);
        usre_param->add_txt("姓名");
        usre_param->txt_center();
        usre_param->set_main_radius(10);
        usre_param->txt_color(lv_color_black());
        usre_param->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        usre_param->set_main_bg_color(lv_color_white(),LV_OPA_60);
        usre_param->set_style_text_font(myfont->font(),0);
        usre_param->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(wide == nullptr)
    {
        wide = new LvcppButton(mparent);
        wide->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        wide->set_pos(775,95);
        wide->set_size(100,50);
        wide->add_txt("1024");
        wide->set_main_radius(10);
        wide->txt_center();
        wide->txt_color(lv_color_black());
        wide->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        wide->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //wide->set_accepted_chars("0123456789");
        wide->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(x == nullptr)
    {
        x = new LvcppButton(mparent);
        x->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        x->set_pos(550,95);
        x->set_size(100,50);
        x->add_txt("0");
        x->txt_center();
        x->set_main_radius(10);
        x->txt_color(lv_color_black());
        x->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        x->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //x->set_accepted_chars("0123456789");
        x->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(y == nullptr)
    {
        y = new LvcppButton(mparent);
        y->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        y->set_pos(660,95);
        y->set_size(100,50);
        y->add_txt("200");
        y->txt_center();
        y->set_main_radius(10);
        y->txt_color(lv_color_black());
        y->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        y->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //y->set_accepted_chars("0123456789");
        y->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(h == nullptr)
    {
        h = new LvcppButton(mparent);
        h->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        h->set_pos(890,95);
        h->set_size(100,50);
        h->add_txt("80");
        h->txt_center();
        h->set_main_radius(10);
        h->txt_color(lv_color_black());
        h->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        h->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //y->set_accepted_chars("0123456789");
        h->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(rgb_color1 == nullptr)
    {
        rgb_color1 = new LvcppButton(mparent);
        rgb_color1->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        rgb_color1->set_pos(80,350);
        rgb_color1->set_size(100,50);
        rgb_color1->add_txt("0");
        rgb_color1->txt_center();
        rgb_color1->set_main_radius(10);
        rgb_color1->txt_color(lv_color_hex(0x000000));
        rgb_color1->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        rgb_color1->set_main_bg_color(lv_color_white(),LV_OPA_60);
        rgb_color1->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(rgb_color2 == nullptr)
    {
        rgb_color2 = new LvcppButton(mparent);
        rgb_color2->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        rgb_color2->align_to(rgb_color1->myobj,LV_ALIGN_OUT_RIGHT_TOP,5,0);
        rgb_color2->set_size(100,50);
        rgb_color2->txt_center();
        rgb_color2->set_main_radius(10);
        rgb_color2->txt_color(lv_color_hex(0x000000));
        rgb_color2->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        rgb_color2->set_main_bg_color(lv_color_white(),LV_OPA_60);
        rgb_color2->add_txt("0");
        rgb_color2->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(rgb_color3 == nullptr)
    {
        rgb_color3 = new LvcppButton(mparent);
        rgb_color3->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        rgb_color3->align_to(rgb_color2->myobj,LV_ALIGN_OUT_RIGHT_TOP,5,0);
        rgb_color3->set_size(100,50);
        rgb_color3->txt_center();
        rgb_color3->set_main_radius(10);
        rgb_color3->txt_color(lv_color_hex(0x000000));
        rgb_color3->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        rgb_color3->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //rgb_color3->set_accepted_chars("0123456789");
        rgb_color3->add_txt("0");
        rgb_color3->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

    if(rgb_bg_color1 == nullptr)
    {
        rgb_bg_color1 = new LvcppButton(mparent);
        rgb_bg_color1->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        rgb_bg_color1->align_to(rgb_color1->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,50);
        rgb_bg_color1->set_size(100,50);
        rgb_bg_color1->txt_center();
        rgb_bg_color1->set_main_radius(10);
        rgb_bg_color1->txt_color(lv_color_hex(0x000000));
        rgb_bg_color1->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        rgb_bg_color1->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //rgb_bg_color1->set_accepted_chars("0123456789");
        rgb_bg_color1->add_txt("255");
        rgb_bg_color1->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(rgb_bg_color2 == nullptr)
    {
        rgb_bg_color2 = new LvcppButton(mparent);
        rgb_bg_color2->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        rgb_bg_color2->align_to(rgb_bg_color1->myobj,LV_ALIGN_OUT_RIGHT_TOP,5,0);
        rgb_bg_color2->set_size(100,50);
        rgb_bg_color2->txt_center();
        rgb_bg_color2->set_main_radius(10);
        rgb_bg_color2->txt_color(lv_color_hex(0x000000));
        rgb_bg_color2->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        rgb_bg_color2->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //rgb_bg_color2->set_accepted_chars("0123456789");
        rgb_bg_color2->add_txt("0");
        rgb_bg_color2->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(rgb_bg_color3 == nullptr)
    {
        rgb_bg_color3 = new LvcppButton(mparent);
        rgb_bg_color3->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        rgb_bg_color3->align_to(rgb_bg_color2->myobj,LV_ALIGN_OUT_RIGHT_TOP,5,0);
        rgb_bg_color3->set_size(100,50);
        rgb_bg_color3->txt_center();
        rgb_bg_color3->set_main_radius(10);
        rgb_bg_color3->txt_color(lv_color_hex(0x000000));
        rgb_bg_color3->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        rgb_bg_color3->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //rgb_bg_color3->set_accepted_chars("0123456789");
        rgb_bg_color3->add_txt("0");
        rgb_bg_color3->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
}

void RenameScreen::dropdown_initial()
{
    if(refont_style == nullptr)
    {
        refont_style =new LvcppDropdown(mparent);
        refont_style->set_pos(550,270);
        refont_style->set_size(100,50);
        refont_style->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(refont_style->get_list(),myfont->font(),0);
        refont_style->set_options("黑体\n楷体\n魏体\n宋体\n隶书\n标宋\n中宋\n等宽\n微软雅黑");
        refont_style->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        refont_style->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //lv_obj_set_style_text_align(refont_style,LV_TEXT_ALIGN_CENTER,LV_PART_MAIN);
        refont_style->set_selected(1);
        refont_style->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }

    if(font_alignment == nullptr)
    {
        font_alignment =new LvcppDropdown(mparent);
        font_alignment->set_pos(890,180);
        font_alignment->set_size(100,50);
        font_alignment->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(font_alignment->get_list(),myfont->font(),0);
        font_alignment->set_options("默认\n左对齐\n居中\n右对齐");
        font_alignment->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        font_alignment->set_main_bg_color(lv_color_white(),LV_OPA_60);
        //lv_obj_set_style_text_align(refont_style,LV_TEXT_ALIGN_CENTER,LV_PART_MAIN);
        font_alignment->set_selected(2);
        font_alignment->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }

    if(refont_size_style == nullptr)
    {
        refont_size_style =new LvcppDropdown(mparent);
        refont_size_style->set_pos(660,270);
        refont_size_style->set_size(80,50);
        refont_size_style->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(refont_size_style->get_list(),myfont->font(),0);
        refont_size_style->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        refont_size_style->set_main_bg_color(lv_color_white(),LV_OPA_60);
        refont_size_style->set_options("正常\n斜体\n粗体");
        refont_size_style->set_selected(2);
        refont_size_style->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }


    if(switch_object == nullptr)
    {
        switch_object =new LvcppDropdown(mparent);
        switch_object->set_pos(550,10);
        switch_object->set_size(100,50);
        switch_object->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(switch_object->get_list(),myfont->font(),0);
        switch_object->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        switch_object->set_main_bg_color(lv_color_white(),LV_OPA_60);
        switch_object->set_options("用户名:\n单位:\n职务:");
        switch_object->set_selected(0);
        switch_object->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }
    if(s_font_color == nullptr)
    {
        s_font_color =new LvcppDropdown(mparent);
        s_font_color->align_to(canvas->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,100,10);
        s_font_color->set_size(80,50);
        s_font_color->set_pos(750,270);
        s_font_color->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(s_font_color->get_list(),myfont->font(),0);
        s_font_color->set_options("红色\n黑色\n白色\n蓝色\n绿色\n黄色\n紫红\n灰色\n粉色");
        lv_obj_set_height(s_font_color->get_list(),3);
        s_font_color->set_dir(LV_DIR_BOTTOM);
        s_font_color->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        s_font_color->set_main_bg_color(lv_color_white(),LV_OPA_60);
        s_font_color->set_selected(1);
        s_font_color->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }
    if(s_bg_color == nullptr)
    {
        s_bg_color =new LvcppDropdown(mparent);
        s_bg_color->set_pos(835,270);
        s_bg_color->set_size(80,50);
        s_bg_color->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(s_bg_color->get_list(),myfont->font(),0);
        s_bg_color->set_options("红色\n黑色\n白色\n蓝色\n绿色\n黄色\n紫红\n灰色\n粉色");
        s_bg_color->set_dir(LV_DIR_BOTTOM);
        s_bg_color->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        s_bg_color->set_main_bg_color(lv_color_white(),LV_OPA_60);
        s_bg_color->set_selected(0);
        s_bg_color->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }
    if(bg_img == nullptr)
    {
        bg_img =new LvcppDropdown(mparent);
        bg_img->set_pos(920,270);
        bg_img->set_size(80,50);
        bg_img->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(bg_img->get_list(),myfont->font(),0);
        bg_img->set_options("1.png\n2.png\n3.png\n4.png\n5.png\nTemp\n 无");
        bg_img->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
        bg_img->set_main_bg_color(lv_color_white(),LV_OPA_60);
        bg_img->set_selected(7);
        bg_img->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }
}
void RenameScreen::label_initial()
{
    if(font_size_tip == nullptr)
    {
        font_size_tip = new LvcppLabel(mparent);
        //font_size_tip->set_pos(910,240);
        font_size_tip->set_size(580,120);
        font_size_tip->align_to(font_size->myobj,LV_ALIGN_OUT_TOP_MID,265,90);
        font_size_tip->set_style_text_font(myfont->font(),0);
        font_size_tip->set_txt("字号");
    }

    if(x_tip == nullptr)
    {
        x_tip = new LvcppLabel(mparent);
        x_tip->align_to(x->myobj,LV_ALIGN_OUT_TOP_LEFT,0,-2);
        x_tip->set_size(100,120);
        x_tip->set_style_text_font(myfont->font(),0);
        x_tip->set_txt("左边距");
        x_tip->txt_align(LV_TEXT_ALIGN_CENTER);
    }
    if(y_tip == nullptr)
    {
        y_tip = new LvcppLabel(mparent);
        y_tip->align_to(y->myobj,LV_ALIGN_OUT_TOP_LEFT,0,-2);
        y_tip->set_size(100,120);
        y_tip->set_style_text_font(myfont->font(),0);
        y_tip->set_txt("上边距");
        y_tip->txt_align(LV_TEXT_ALIGN_CENTER);
    }
    if(w_tip == nullptr)
    {
        w_tip = new LvcppLabel(mparent);
        w_tip->align_to(wide->myobj,LV_ALIGN_OUT_TOP_MID,10,-2);
        w_tip->set_size(100,120);
        w_tip->set_style_text_font(myfont->font(),0);
        w_tip->set_txt("宽");
    }
    if(object_name_tip == nullptr)
    {
        object_name_tip = new LvcppLabel(mparent);
        object_name_tip->set_size(100,120);
        object_name_tip->align_to(refont_size_style->myobj,LV_ALIGN_OUT_TOP_MID,25,90);
        object_name_tip->set_style_text_font(myfont->font(),0);
        object_name_tip->set_txt("字体");
    }
    if(rgb_color_tip == nullptr)
    {
        rgb_color_tip = new LvcppLabel(mparent);
        rgb_color_tip->set_size(100,100);
        rgb_color_tip->align_to(rgb_color2->myobj,LV_ALIGN_OUT_TOP_MID,10,70);
        rgb_color_tip->set_style_text_font(myfont->font(),0);
        rgb_color_tip->set_txt("RGB字色");
    }

    if(rgb_bg_color_tip == nullptr)
    {
        rgb_bg_color_tip = new LvcppLabel(mparent);
        rgb_bg_color_tip->align_to(rgb_bg_color2->myobj,LV_ALIGN_OUT_TOP_MID,-30,-2);
        rgb_bg_color_tip->set_size(125,100);
        rgb_bg_color_tip->set_style_text_font(myfont->font(),0);
        rgb_bg_color_tip->set_txt("RGB背景色");
    }
    if(manual_bg_color_tip == nullptr)
    {
        manual_bg_color_tip = new LvcppLabel(mparent);
        manual_bg_color_tip->align_to(s_font_color->myobj,LV_ALIGN_OUT_TOP_MID,0,-2);
        manual_bg_color_tip->set_size(100,100);
        manual_bg_color_tip->set_style_text_font(myfont->font(),0);
        manual_bg_color_tip->set_txt("字色");
    }
    if(manual_font_color_tip == nullptr)
    {
        manual_font_color_tip = new LvcppLabel(mparent);
        manual_font_color_tip->set_size(100,100);
        manual_font_color_tip->align_to(s_bg_color->myobj,LV_ALIGN_OUT_TOP_MID,15,70);
        manual_font_color_tip->set_style_text_font(myfont->font(),0);
        manual_font_color_tip->set_txt("背景色");
    }

    if(manual_font_tip == nullptr)
    {
        manual_font_tip = new LvcppLabel(mparent);
        manual_font_tip->set_pos(565,150);
        manual_font_tip->set_size(100,100);
        manual_font_tip->set_style_text_font(myfont->font(),0);
        manual_font_tip->set_txt("字间距");
    }

    if(manual_line_tip == nullptr)
    {
        manual_line_tip = new LvcppLabel(mparent);
        manual_line_tip->set_pos(675,150);
        manual_line_tip->set_size(600,100);
        manual_line_tip->set_style_text_font(myfont->font(),0);
        manual_line_tip->set_txt("行间距");
    }
    if(manual_aglin_tip == nullptr)
    {
        manual_aglin_tip = new LvcppLabel(mparent);
        manual_aglin_tip->set_pos(890,150);
        manual_aglin_tip->set_size(100,100);
        manual_aglin_tip->set_style_text_font(myfont->font(),0);
        manual_aglin_tip->set_txt("对齐方式");
    }
    if(manual_photo_tip == nullptr)
    {
        manual_photo_tip = new LvcppLabel(mparent);
        manual_photo_tip->set_pos(130,470);
        manual_photo_tip->set_size(100,100);
        manual_photo_tip->align_to(bg_img->myobj,LV_ALIGN_OUT_TOP_MID,15,70);
        manual_photo_tip->set_style_text_font(myfont->font(),0);
        manual_photo_tip->set_txt("背景图");
    }
    if(manual_h_tip == nullptr)
    {
        manual_h_tip = new LvcppLabel(mparent);
        manual_h_tip->align_to(h->myobj,LV_ALIGN_OUT_TOP_MID,10,-2);
        manual_h_tip->set_size(100,100);
        manual_h_tip->set_style_text_font(myfont->font(),0);
        manual_h_tip->set_txt("高");
    }
    if(font_tp == nullptr)
    {
        font_tp = new LvcppLabel(mparent);
        font_tp->align_to(refont_style->myobj,LV_ALIGN_OUT_TOP_MID,-25,-2);
        font_tp->set_size(100,100);
        font_tp->set_style_text_font(myfont->font(),0);
        font_tp->set_txt("字体类型");
    }
}



void RenameScreen::change_bg_rgb_color()
{
    //LV_LOG_USER("rgb_bg_color1 =%s",rgb_bg_color1->get_txt());
    //LV_LOG_USER("rgb_bg_color2 =%s",rgb_bg_color2->get_txt());
    //LV_LOG_USER("rgb_bg_color3 =%s",rgb_bg_color3->get_txt());
    int color1  =atoi(rgb_bg_color1->get_txt());
    int color2  =atoi(rgb_bg_color2->get_txt());
    int color3  =atoi(rgb_bg_color3->get_txt());
    sprintf(g_RenameInfo.layout.BgColor,"%02x%02x%02x",color1,color2,color3);
    //sprintf(g_RenameInfo.layout.BgColor,"%02x%02x%02x",color1,color2,color3);
    repaint_canvas();
}

void RenameScreen::change_rgb_color(int type)
{
    //LV_LOG_USER("rgb_color1 =%s",rgb_color1->get_txt());
    //LV_LOG_USER("rgb_color2 =%s",rgb_color2->get_txt());
    //LV_LOG_USER("rgb_color3 =%s",rgb_color3->get_txt());
    int color1  =atoi(rgb_color1->get_txt());
    int color2  =atoi(rgb_color2->get_txt());
    int color3  =atoi(rgb_color3->get_txt());
    //LV_LOG_USER("type =%d",type);
    sprintf(g_RenameInfo.layout.detail[type].TextColor,"%02x%02x%02x",color1,color2,color3 );
    //LV_LOG_USER("TextColor = %s",g_RenameInfo.layout.detail[type].TextColor);
    //sprintf(g_RenameInfo.layout.detail[type].TextColor,"%02x%02x%02x",color1,color2,color3 );
    repaint_canvas();
}

void RenameScreen::change_font_name(int tpye)
{
    //LV_LOG_USER("tpye = %d",tpye);
    refont_style->get_selected_str(g_RenameInfo.layout.detail[tpye].TextFont,sizeof(g_RenameInfo.layout.detail[tpye].TextFont));
    repaint_canvas();
}

void RenameScreen::change_size(int type)//refont_style->get_selected();
{
    int size=atoi( font_size->get_txt());
    //LV_LOG_USER("size =%d",size);
    g_RenameInfo.layout.detail[type].TextSize = size;
    repaint_canvas();
}

void RenameScreen::change_size_style(int type)
{
    g_RenameInfo.layout.detail[type].TextType = refont_size_style->get_selected();
    repaint_canvas();
}
void RenameScreen::change_x_y_h_w(int type)
{
    //LV_LOG_USER("xxxxxxxxx");
    g_RenameInfo.layout.detail[type].ElePointX = atoi(x->get_txt());
    g_RenameInfo.layout.detail[type].ElePointY = atoi(y->get_txt());
    g_RenameInfo.layout.detail[type].EleWidth =  atoi(wide->get_txt());
    g_RenameInfo.layout.detail[type].EleHeight =  atoi(h->get_txt());
    repaint_canvas();
}

void RenameScreen::change_font_space_between(int type)
{
    g_RenameInfo.layout.detail[type].TextLetterSpace = atoi(font_space_between->get_txt());
    repaint_canvas();
}

void RenameScreen::change_font_line_between(int type)
{
    //LV_LOG_USER("line = %s",font_line_between->get_txt());
    g_RenameInfo.layout.detail[type].TextLineSpace = atoi(font_line_between->get_txt());
    repaint_canvas();
}


void RenameScreen::change_font_aglin_preview(int type)
{
    //char * f_alignment;
    //font_alignment->get_selected_str(f_alignment,sizeof(g_RenameInfo.layout.detail[type].HorizontalAlign));
    //LV_LOG_USER("get_selected = %d",font_alignment->get_selected());
    g_RenameInfo.layout.detail[type].HorizontalAlign = font_alignment->get_selected();
    repaint_canvas();
}

void RenameScreen::change_usre_param(int type)
{
    if(type == 0)
    {
        strcpy(g_RenameInfo.username,usre_param->get_txt());
    }
    if(type == 1)
    {
        strcpy(g_RenameInfo.company,usre_param->get_txt());
    }
    if(type == 2)
    {
        strcpy(g_RenameInfo.duty,usre_param->get_txt());
    }
    repaint_canvas();
}
void RenameScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenameScreen* opt = (RenameScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->rgb_color1->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(4);
        }
        opt->show_text_tmp = 1;
        opt->input_kb->input_box->set_text(opt->rgb_color1->get_txt());
        opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
    }
    else if(target==opt->rgb_color2->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(4);
        }
        opt->show_text_tmp = 2;
        opt->input_kb->input_box->set_text(opt->rgb_color2->get_txt());
        opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
    }
    else if(target==opt->rgb_color3->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(4);
        }
        opt->show_text_tmp = 3;
        opt->input_kb->input_box->set_text(opt->rgb_color3->get_txt());
        opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
    }
    else if(target==opt->rgb_bg_color1->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(4);
            opt->show_text_tmp = 4;
            opt->input_kb->input_box->set_text(opt->rgb_bg_color1->get_txt());
            //opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }
    else if(target==opt->rgb_bg_color2->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(4);
            opt->show_text_tmp = 5;
            opt->input_kb->input_box->set_text(opt->rgb_bg_color2->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }
    else if(target==opt->rgb_bg_color3->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(4);
            opt->show_text_tmp = 6;
            opt->input_kb->input_box->set_text(opt->rgb_bg_color3->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }

    else if(target==opt->switch_object->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            opt->switch_object_get_int();
        }
    }

    else if(target==opt->font_size->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(1);
            opt->show_text_tmp = 7;
            opt->input_kb->input_box->set_text(opt->font_size->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }

    else if(target==opt->refont_size_style->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            //LV_LOG_USER("change_size_style");
            opt->change_size_style(opt->type);
        }
    }

    else if(target==opt->refont_style->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            //LV_LOG_USER("refont_style");
            opt->change_font_name(opt->type);
        }
    }

    else if(target==opt->usre_param->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            //LV_LOG_USER("usre_name");
            opt->input_kb->initial(3);
            opt->show_text_tmp = 11;
            opt->input_kb->input_box->set_text(opt->usre_param->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }
    else if(target==opt->h->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(1);
            opt->show_text_tmp = 14;
            opt->input_kb->input_box->set_text(opt->h->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }
    else if(target==opt->wide->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(1);
            opt->show_text_tmp = 8;
            opt->input_kb->input_box->set_text(opt->wide->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }

    else if(target==opt->x->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(1);
            opt->show_text_tmp = 9;
            opt->input_kb->input_box->set_text(opt->x->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }


    else if(target==opt->y->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(1);
            opt->show_text_tmp = 10;
            opt->input_kb->input_box->set_text(opt->y->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }
    else if(target == opt->font_space_between->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(1);
            opt->show_text_tmp = 12;
            opt->input_kb->input_box->set_text(opt->font_space_between->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }
    else if(target == opt->font_line_between->myobj)
    {
        if(opt->input_kb == nullptr)
        {
            opt->kb_create();
        }
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->input_kb->initial(1);
            opt->show_text_tmp = 13;
            opt->input_kb->input_box->set_text(opt->font_line_between->get_txt());
            opt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }
    else if(target == opt->font_alignment->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            opt->change_font_aglin_preview(opt->type);
        }
    }
    else if(target == opt->show_preview->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->to_show_preview();
            return;
        }
    }
    else if(target == opt->s_bg_color->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            opt->manual_bg_color();
        }
    }

    else if(target==opt->s_font_color->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            opt->manual_font_color(opt->type);
        }
    }
    else if(target == opt->bg_img->myobj)
    {
        //LV_LOG_USER("bg_img->myobj");
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            //LV_LOG_USER("set_bg_img");
            opt->set_bg_img();
        }
    }
}

void RenameScreen::set_bg_img(void)
{
    bg_img->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
    if(strcmp(g_RenameInfo.layout.BgImg,"无")!=0)
    {
        if(strcmp(g_RenameInfo.layout.BgImg,"Temp")==0)
        {
            memset(g_RenameInfo.layout.BgImg,0,sizeof(g_RenameInfo.layout.BgImg));
            strcpy(g_RenameInfo.layout.BgImg,"temp.png");
        }
        else
        {
            bg_img->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
        }
    }
    else
    {
        memset(g_RenameInfo.layout.BgImg,0,sizeof(g_RenameInfo.layout.BgImg));
    }
    repaint_canvas();
}

void RenameScreen::manual_bg_color(void)
{
    //LV_LOG_USER("000000000000");
    //LV_LOG_USER("bg_color->get_selected() = %d",s_bg_color->get_selected());
    if(s_bg_color->get_selected() == 0)
    {
        rgb_bg_color1->add_txt("255");
        rgb_bg_color2->add_txt("0");
        rgb_bg_color3->add_txt("0");
    }
    else if(s_bg_color->get_selected() == 1)
    {
        rgb_bg_color1->add_txt("0");
        rgb_bg_color2->add_txt("0");
        rgb_bg_color3->add_txt("0");
    }
    else if(s_bg_color->get_selected() == 2)
    {
        rgb_bg_color1->add_txt("255");
        rgb_bg_color2->add_txt("255");
        rgb_bg_color3->add_txt("255");
    }
    else if(s_bg_color->get_selected() == 3)
    {
        rgb_bg_color1->add_txt("0");
        rgb_bg_color2->add_txt("0");
        rgb_bg_color3->add_txt("255");
    }
    else if(s_bg_color->get_selected() == 4)
    {
        rgb_bg_color1->add_txt("0");
        rgb_bg_color2->add_txt("255");
        rgb_bg_color3->add_txt("0");
    }
    else if(s_bg_color->get_selected() == 5)
    {
        rgb_bg_color1->add_txt("255");
        rgb_bg_color2->add_txt("255");
        rgb_bg_color3->add_txt("0");
    }
    else if(s_bg_color->get_selected() == 6)
    {
        rgb_bg_color1->add_txt("255");
        rgb_bg_color2->add_txt("0");
        rgb_bg_color3->add_txt("255");
    }
    else if(s_bg_color->get_selected() == 7)
    {
        rgb_bg_color1->add_txt("128");
        rgb_bg_color2->add_txt("128");
        rgb_bg_color3->add_txt("128");
    }
    else if(s_bg_color->get_selected() == 8)
    {
        rgb_bg_color1->add_txt("255");
        rgb_bg_color2->add_txt("90");
        rgb_bg_color3->add_txt("90");
    }
     change_bg_rgb_color();
}
void RenameScreen::manual_font_color(int type)
{
    //LV_LOG_USER("000000000000");
    //LV_LOG_USER("font_color->get_selected() = %d",s_font_color->get_selected());
    if(s_font_color->get_selected() == 1)
    {
        rgb_color1->add_txt("0");
        rgb_color2->add_txt("0");
        rgb_color3->add_txt("0");
    }
    else if(s_font_color->get_selected() == 0)
    {
        rgb_color1->add_txt("255");
        rgb_color2->add_txt("0");
        rgb_color3->add_txt("0");
    }
    else if(s_font_color->get_selected() == 2)
    {
        rgb_color1->add_txt("255");
        rgb_color2->add_txt("255");
        rgb_color3->add_txt("255");
    }
    if(s_font_color->get_selected() == 3)
    {
        rgb_color1->add_txt("0");
        rgb_color2->add_txt("0");
        rgb_color3->add_txt("255");
    }
    else if(s_font_color->get_selected() == 4)
    {
        rgb_color1->add_txt("0");
        rgb_color2->add_txt("255");
        rgb_color3->add_txt("0");
    }
    else if(s_font_color->get_selected() == 5)
    {
        rgb_color1->add_txt("255");
        rgb_color2->add_txt("255");
        rgb_color3->add_txt("0");
    }
    else if(s_font_color->get_selected() == 6)
    {
        rgb_color1->add_txt("255");
        rgb_color2->add_txt("0");
        rgb_color3->add_txt("255");
    }
    else if(s_font_color->get_selected() == 7)
    {
        rgb_color1->add_txt("128");
        rgb_color2->add_txt("128");
        rgb_color3->add_txt("128");
    }
    else if(s_font_color->get_selected() == 8)
    {
        rgb_color1->add_txt("255");
        rgb_color2->add_txt("90");
        rgb_color3->add_txt("90");
    }
    change_rgb_color(type);
}

void RenameScreen::to_show_preview(void)
{/*
    #if (QTSIM_PLATFORM==0)
    msg_apps_t msg;
    memset(&msg,0,sizeof(msg_apps_t));
    msg.type = MSG_UPDATE_CANVAS;
    SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
    #endif*/
}

void RenameScreen::get_kbinput_text(void)
{
    //LV_LOG_USER("show_text_tmp =%d",show_text_tmp);
    if(show_text_tmp == 1)
    {
        rgb_color1->add_txt(input_kb->input_box->get_text());
        change_rgb_color(type);
    }
    else if(show_text_tmp == 2)
    {
        rgb_color2->add_txt(input_kb->input_box->get_text());
        change_rgb_color(type);
    }
    else if(show_text_tmp == 3)
    {
        rgb_color3->add_txt(input_kb->input_box->get_text());
        change_rgb_color(type);
    }
    else if(show_text_tmp == 4)
    {
        rgb_bg_color1->add_txt(input_kb->input_box->get_text());
        change_bg_rgb_color();
    }
    else if(show_text_tmp == 5)
    {
        rgb_bg_color2->add_txt(input_kb->input_box->get_text());
        change_bg_rgb_color();
    }
    else if(show_text_tmp == 6)
    {
        rgb_bg_color3->add_txt(input_kb->input_box->get_text());
        change_bg_rgb_color();
    }
    else if(show_text_tmp == 7)
    {
        font_size->add_txt(input_kb->input_box->get_text());
        change_size(type);
    }
    else if(show_text_tmp == 8)
    {
        wide->add_txt(input_kb->input_box->get_text());
        change_x_y_h_w(type);
    }
    else if(show_text_tmp == 9)
    {
        x->add_txt(input_kb->input_box->get_text());
        change_x_y_h_w(type);
    }
    else if(show_text_tmp == 10)
    {
        y->add_txt(input_kb->input_box->get_text());
        change_x_y_h_w(type);
    }
    else if(show_text_tmp == 11)
    {
        usre_param->add_txt(input_kb->input_box->get_text());
        change_usre_param(type);
    }
    else if(show_text_tmp == 12)
    {
        font_space_between->add_txt(input_kb->input_box->get_text());
        change_font_space_between(type);
    }
    else if(show_text_tmp == 13)
    {
        font_line_between->add_txt(input_kb->input_box->get_text());
        change_font_line_between(type);
    }
    else if(show_text_tmp == 14)
    {
        h->add_txt(input_kb->input_box->get_text());
        change_x_y_h_w(type);
    }



}

void RenameScreen::Rename_head_Screen_create(void)
{
    if(re_head == nullptr)
    {
        re_head = new RenameheadScreen(mparent);
    }
}


void RenameScreen::Rename_bottom_Screen_create(void)
{
    if(re_bottom == nullptr)
    {
        re_bottom = new RenamebottomScreen(mparent);
    }
}

void RenameScreen::Rename_input_Screen_create(void)
{
    if(re_input == nullptr)
    {
        re_input = new RenameinputScreen(mparent);
    }
}

void RenameScreen::Rename_box_create(void)
{
    if(re_box == nullptr)
    {
        re_box = new RenameboxtScreen(mparent);
    }
}

void RenameScreen::Rename_effect_Screen_create(void)
{
    if(re_effect == nullptr)
    {
        re_effect = new RenameeffectScreen(mparent);
    }
}

void RenameScreen::Rename_color_Screen(void)
{
    if(re_color == nullptr)
    {
        re_color = new RenamecolorScreen(mparent);
    }
}

void RenameScreen::Rename_bg_color_Screen(void)
{
    if(bg_color == nullptr)
    {
        bg_color = new RenamebgcolorScreen(mparent);
    }
}

void RenameScreen::Rename_fontset_Screen(void)
{
    if(re_fontset == nullptr)
    {
        re_fontset = new RenamefontsetScreen(mparent);
    }
}



void RenameScreen::kb_create(void)
{
    if(input_kb == nullptr)
    {
        input_kb = new kbscreen(mparent);
        input_kb->sendcb(kb_cb);
    }
}


void RenameScreen::kb_cb(void)
{
    renameopt->get_kbinput_text();
    if(renameopt->input_kb != nullptr)
    {
        delete renameopt->input_kb;
        renameopt->input_kb = NULL;
    }
}


void RenameScreen::sendcb(void (*callback)(void))
{
    re_callback=callback;
}





void RenameScreen::switch_object_get_int()
{
    if(switch_object->get_selected()== 0)
    {
        type = 0;//名字
        //刷新
        char x_t[128];
        char y_t[128];
        char wide_t[128];
        char h_t[128];
        char font_space_between_t[128];
        char font_line_between_t[128];
        char font_size_t[128];

        snprintf(x_t,sizeof(x_t),"%d",g_RenameInfo.layout.detail[0].ElePointX);
        snprintf(y_t,sizeof(y_t),"%d",g_RenameInfo.layout.detail[0].ElePointY);
        snprintf(wide_t,sizeof(wide_t),"%d",g_RenameInfo.layout.detail[0].EleWidth);
        snprintf(h_t,sizeof(h_t),"%d",g_RenameInfo.layout.detail[0].EleHeight);
        snprintf(font_space_between_t,sizeof(font_space_between_t),"%d",g_RenameInfo.layout.detail[0].TextLetterSpace);
        snprintf(font_line_between_t,sizeof(font_line_between_t),"%d",g_RenameInfo.layout.detail[0].TextLineSpace);
        snprintf(font_size_t,sizeof(font_size_t),"%d",g_RenameInfo.layout.detail[0].TextSize);

        x->add_txt(x_t);
        y->add_txt(y_t);
        wide->add_txt(wide_t);
        h->add_txt(h_t);
        font_space_between->add_txt(font_space_between_t);
        font_line_between->add_txt(font_line_between_t);
        font_size->add_txt(font_size_t);
        usre_param->add_txt(g_RenameInfo.username);

        uint8_t color[3]={0};
        char color1[5];
        char color2[5];
        char color3[5];
        hexStringToByte(color,g_RenameInfo.layout.detail[0].TextColor,strlen(g_RenameInfo.layout.detail[0].TextColor));//文本颜色
        label_dsc0.color = lv_color_make(color[0],color[1],color[2]);

        snprintf(color1,sizeof(color1),"%d",color[0]);
        snprintf(color2,sizeof(color2),"%d",color[1]);
        snprintf(color3,sizeof(color3),"%d",color[2]);

        //LV_LOG_USER("color1 = %s",color1);
        //LV_LOG_USER("color2 = %s",color2);
        //LV_LOG_USER("color3 = %s",color3);
        rgb_color1->add_txt(color1);
        rgb_color2->add_txt(color2);
        rgb_color3->add_txt(color3);

        //对齐方式
        //LV_LOG_USER("change HorizontalAlign");
        if(g_RenameInfo.layout.detail[0].HorizontalAlign == 0)
        {
            font_alignment->set_selected(0);
        }
        else if(g_RenameInfo.layout.detail[0].HorizontalAlign == 1)
        {
            font_alignment->set_selected(1);
        }
        else if(g_RenameInfo.layout.detail[0].HorizontalAlign == 2)
        {
            font_alignment->set_selected(2);
        }
        else if(g_RenameInfo.layout.detail[0].HorizontalAlign == 3)
        {
            font_alignment->set_selected(3);
        }

        //样式 粗体 斜体
        //LV_LOG_USER("change TextType");
        if(g_RenameInfo.layout.detail[0].TextType == 0)
        {
            refont_size_style->set_selected(0);
        }
        else if(g_RenameInfo.layout.detail[0].TextType == 1)
        {
            refont_size_style->set_selected(1);
        }
        else if(g_RenameInfo.layout.detail[0].TextType == 2)
        {
            refont_size_style->set_selected(2);
        }


        //字形 宋体
        //LV_LOG_USER("change TextFont");
        if(strcmp(g_RenameInfo.layout.detail[0].TextFont, "黑体") == 0)
        {
            refont_style->set_selected(0);
        }
        else if(strcmp(g_RenameInfo.layout.detail[0].TextFont, "楷体") == 0)
        {
            refont_style->set_selected(1);
        }
        else if(strcmp(g_RenameInfo.layout.detail[0].TextFont, "魏体") == 0)
        {
            refont_style->set_selected(2);
        }
        else if(strcmp(g_RenameInfo.layout.detail[0].TextFont, "宋体") == 0)
        {
            refont_style->set_selected(3);
        }
        else if(strcmp(g_RenameInfo.layout.detail[0].TextFont, "隶书") == 0)
        {
            refont_style->set_selected(4);
        }
    }
    else if(switch_object->get_selected()==1)
    {
        type = 1;//单位
        char x_t[128];
        char y_t[128];
        char wide_t[128];
        char h_t[128];
        char font_space_between_t[128];
        char font_line_between_t[128];
        char font_size_t[128];
        snprintf(x_t,sizeof(x_t),"%d",g_RenameInfo.layout.detail[1].ElePointX);
        snprintf(y_t,sizeof(y_t),"%d",g_RenameInfo.layout.detail[1].ElePointY);
        snprintf(wide_t,sizeof(wide_t),"%d",g_RenameInfo.layout.detail[1].EleWidth);
        snprintf(h_t,sizeof(h_t),"%d",g_RenameInfo.layout.detail[1].EleHeight);
        snprintf(font_space_between_t,sizeof(font_space_between_t),"%d",g_RenameInfo.layout.detail[1].TextLetterSpace);
        snprintf(font_line_between_t,sizeof(font_line_between_t),"%d",g_RenameInfo.layout.detail[1].TextLineSpace);
        snprintf(font_size_t,sizeof(font_size_t),"%d",g_RenameInfo.layout.detail[1].TextSize);

        x->add_txt(x_t);
        y->add_txt(y_t);
        wide->add_txt(wide_t);
        h->add_txt(h_t);
        font_space_between->add_txt(font_space_between_t);
        font_line_between->add_txt(font_line_between_t);
        font_size->add_txt(font_size_t);
        usre_param->add_txt(g_RenameInfo.username);
        usre_param->add_txt(g_RenameInfo.company);

        uint8_t color[3]={0};
        char color1[5];
        char color2[5];
        char color3[5];
        hexStringToByte(color,g_RenameInfo.layout.detail[1].TextColor,strlen(g_RenameInfo.layout.detail[1].TextColor));//文本颜色
        label_dsc0.color = lv_color_make(color[0],color[1],color[2]);

        snprintf(color1,sizeof(color1),"%d",color[0]);
        snprintf(color2,sizeof(color2),"%d",color[1]);
        snprintf(color3,sizeof(color3),"%d",color[2]);

        //LV_LOG_USER("color1 = %s",color1);
        //LV_LOG_USER("color2 = %s",color2);
        //LV_LOG_USER("color3 = %s",color3);
        rgb_color1->add_txt(color1);
        rgb_color2->add_txt(color2);
        rgb_color3->add_txt(color3);

        //对齐方式
        //LV_LOG_USER("change HorizontalAlign");
        if(g_RenameInfo.layout.detail[1].HorizontalAlign == 0)
        {
            font_alignment->set_selected(0);
        }
        else if(g_RenameInfo.layout.detail[1].HorizontalAlign == 1)
        {
            font_alignment->set_selected(1);
        }
        else if(g_RenameInfo.layout.detail[1].HorizontalAlign == 2)
        {
            font_alignment->set_selected(2);
        }
        else if(g_RenameInfo.layout.detail[1].HorizontalAlign == 3)
        {
            font_alignment->set_selected(3);
        }

        //样式 粗体 斜体
        //LV_LOG_USER("change TextType");
        if(g_RenameInfo.layout.detail[1].TextType == 0)
        {
            refont_size_style->set_selected(0);
        }
        else if(g_RenameInfo.layout.detail[1].TextType == 1)
        {
            refont_size_style->set_selected(1);
        }
        else if(g_RenameInfo.layout.detail[1].TextType == 2)
        {
            refont_size_style->set_selected(2);
        }


        //字形 宋体
        //LV_LOG_USER("change TextFont");
        if(strcmp(g_RenameInfo.layout.detail[1].TextFont, "黑体") == 0)
        {
            refont_style->set_selected(0);
        }
        else if(strcmp(g_RenameInfo.layout.detail[1].TextFont, "楷体") == 0)
        {
            refont_style->set_selected(1);
        }
        else if(strcmp(g_RenameInfo.layout.detail[1].TextFont, "魏体") == 0)
        {
            refont_style->set_selected(2);
        }
        else if(strcmp(g_RenameInfo.layout.detail[1].TextFont, "宋体") == 0)
        {
            refont_style->set_selected(3);
        }
        else if(strcmp(g_RenameInfo.layout.detail[1].TextFont, "隶书") == 0)
        {
            refont_style->set_selected(4);
        }
    }
    else if(switch_object->get_selected()==2)
    {
        type = 2;//职务
        char x_t[10];
        char y_t[10];
        char wide_t[10];
        char h_t[10];
        char font_space_between_t[10];
        char font_line_between_t[10];
        char font_size_t[10];
        snprintf(x_t,sizeof(x_t),"%d",g_RenameInfo.layout.detail[2].ElePointX);
        snprintf(y_t,sizeof(y_t),"%d",g_RenameInfo.layout.detail[2].ElePointY);
        snprintf(wide_t,sizeof(wide_t),"%d",g_RenameInfo.layout.detail[2].EleWidth);
        snprintf(h_t,sizeof(h_t),"%d",g_RenameInfo.layout.detail[2].EleHeight);
        snprintf(font_space_between_t,sizeof(font_space_between_t),"%d",g_RenameInfo.layout.detail[2].TextLetterSpace);
        snprintf(font_line_between_t,sizeof(font_line_between_t),"%d",g_RenameInfo.layout.detail[2].TextLineSpace);
        snprintf(font_size_t,sizeof(font_size_t),"%d",g_RenameInfo.layout.detail[2].TextSize);

        x->add_txt(x_t);
        y->add_txt(y_t);
        wide->add_txt(wide_t);
        h->add_txt(h_t);
        font_space_between->add_txt(font_space_between_t);
        font_line_between->add_txt(font_line_between_t);
        font_size->add_txt(font_size_t);
        usre_param->add_txt(g_RenameInfo.duty);

        uint8_t color[3]={0};
        char color1[5];
        char color2[5];
        char color3[5];
        hexStringToByte(color,g_RenameInfo.layout.detail[2].TextColor,strlen(g_RenameInfo.layout.detail[2].TextColor));//文本颜色
        label_dsc0.color = lv_color_make(color[0],color[1],color[2]);

        snprintf(color1,sizeof(color1),"%d",color[0]);
        snprintf(color2,sizeof(color2),"%d",color[1]);
        snprintf(color3,sizeof(color3),"%d",color[2]);

        //LV_LOG_USER("color1 = %s",color1);
        //LV_LOG_USER("color1 = %s",color2);
        //LV_LOG_USER("color1 = %s",color3);
        rgb_color1->add_txt(color1);
        rgb_color2->add_txt(color2);
        rgb_color3->add_txt(color3);

        //对齐方式
        //LV_LOG_USER("change HorizontalAlign");
        if(g_RenameInfo.layout.detail[2].HorizontalAlign == 0)
        {
            font_alignment->set_selected(0);
        }
        else if(g_RenameInfo.layout.detail[2].HorizontalAlign == 1)
        {
            font_alignment->set_selected(1);
        }
        else if(g_RenameInfo.layout.detail[2].HorizontalAlign == 2)
        {
            font_alignment->set_selected(2);
        }
        else if(g_RenameInfo.layout.detail[2].HorizontalAlign == 3)
        {
            font_alignment->set_selected(3);
        }

        //样式 粗体 斜体
        //LV_LOG_USER("change TextType");
        if(g_RenameInfo.layout.detail[2].TextType == 0)
        {
            refont_size_style->set_selected(0);
        }
        else if(g_RenameInfo.layout.detail[2].TextType == 1)
        {
            refont_size_style->set_selected(1);
        }
        else if(g_RenameInfo.layout.detail[2].TextType == 2)
        {
            refont_size_style->set_selected(2);
        }


        //字形 宋体
        //LV_LOG_USER("change TextFont");
        if(strcmp(g_RenameInfo.layout.detail[2].TextFont, "黑体") == 0)
        {
            refont_style->set_selected(0);
        }
        else if(strcmp(g_RenameInfo.layout.detail[2].TextFont, "楷体") == 0)
        {
            refont_style->set_selected(1);
        }
        else if(strcmp(g_RenameInfo.layout.detail[2].TextFont, "魏体") == 0)
        {
            refont_style->set_selected(2);
        }
        else if(strcmp(g_RenameInfo.layout.detail[2].TextFont, "宋体") == 0)
        {
            refont_style->set_selected(3);
        }
        else if(strcmp(g_RenameInfo.layout.detail[2].TextFont, "隶书") == 0)
        {
            refont_style->set_selected(4);
        }
    }
    else
    {
        //LV_LOG_USER("switch erro");
    }
    //LV_LOG_USER("type=%d",type);

}

void RenameScreen::deinitial()
{


}

void RenameScreen::font_initial_zp()
{
    uint8_t color[3]={0};
    if(myfont0)
    {
        lv_ft_font_destroy(myfont0);
        myfont0 = nullptr;
    }

    //username
    static lv_ft_info_t ft_font0;
    font_scan_file_path(g_RenameInfo.layout.detail[0].TextFont,&ft_font0.name);
    ft_font0.weight = g_RenameInfo.layout.detail[0].TextSize*680/1024;//字号
    ft_font0.style = g_RenameInfo.layout.detail[0].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font0);
    myfont0 =ft_font0.font;

    lv_draw_label_dsc_init(&label_dsc0);//初始化文本
    label_dsc0.font = myfont0;
    label_dsc0.align = g_RenameInfo.layout.detail[0].HorizontalAlign;
    label_dsc0.line_space = g_RenameInfo.layout.detail[0].TextLineSpace;
    label_dsc0.letter_space = g_RenameInfo.layout.detail[0].TextLetterSpace;
    hexStringToByte(color,g_RenameInfo.layout.detail[0].TextColor,strlen(g_RenameInfo.layout.detail[0].TextColor));//文本颜色
    label_dsc0.color = lv_color_make(color[0],color[1],color[2]);

    if(myfont1)
    {
        lv_ft_font_destroy(myfont1);
        myfont1 = nullptr;
    }
    //company
    static lv_ft_info_t ft_font1;
    font_scan_file_path(g_RenameInfo.layout.detail[1].TextFont,&ft_font1.name);
    ft_font1.weight = g_RenameInfo.layout.detail[1].TextSize*680/1024;//字号
    ft_font1.style = g_RenameInfo.layout.detail[1].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font1);
    myfont1 =ft_font1.font;

    lv_draw_label_dsc_init(&label_dsc1);//初始化文本
    label_dsc1.font = myfont1;

    label_dsc1.align = g_RenameInfo.layout.detail[1].HorizontalAlign;
    label_dsc1.line_space = g_RenameInfo.layout.detail[1].TextLineSpace;
    label_dsc1.letter_space = g_RenameInfo.layout.detail[1].TextLetterSpace;
    hexStringToByte(color,g_RenameInfo.layout.detail[1].TextColor,strlen(g_RenameInfo.layout.detail[1].TextColor));//文本颜色
    label_dsc1.color = lv_color_make(color[0],color[1],color[2]);

    if(myfont2)
    {
        lv_ft_font_destroy(myfont2);
        myfont2 = nullptr;
    }

    //duty
    static lv_ft_info_t ft_font2;
    font_scan_file_path(g_RenameInfo.layout.detail[2].TextFont,&ft_font2.name);
    ft_font2.weight = g_RenameInfo.layout.detail[2].TextSize*680/1024;//字号
    ft_font2.style = g_RenameInfo.layout.detail[2].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font2);
    myfont2 =ft_font2.font;

    lv_draw_label_dsc_init(&label_dsc2);//初始化文本
    label_dsc2.font = myfont2;
    label_dsc2.align = g_RenameInfo.layout.detail[2].HorizontalAlign;
    label_dsc2.line_space = g_RenameInfo.layout.detail[2].TextLineSpace;
    label_dsc2.letter_space = g_RenameInfo.layout.detail[2].TextLetterSpace;
    hexStringToByte(color,g_RenameInfo.layout.detail[2].TextColor,strlen(g_RenameInfo.layout.detail[2].TextColor));//文本颜色
    label_dsc2.color = lv_color_make(color[0],color[1],color[2]);
}

void RenameScreen::font_initial1()
{
    if(myfont0)
    {
        lv_ft_font_destroy(myfont0);
        myfont0 = nullptr;
    }


    //username
    static lv_ft_info_t ft_font0;
    font_scan_file_path(g_RenameInfo.layout.detail[0].TextFont,&ft_font0.name);
    ft_font0.weight = g_RenameInfo.layout.detail[0].TextSize*680/1024;//字号
    ft_font0.style = g_RenameInfo.layout.detail[0].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font0);
    myfont0 =ft_font0.font;

    lv_draw_label_dsc_init(&label_dsc0);//初始化文本
    label_dsc0.font = myfont0;
    label_dsc0.align = g_RenameInfo.layout.detail[0].HorizontalAlign;
    label_dsc0.line_space = g_RenameInfo.layout.detail[0].TextLineSpace;
    label_dsc0.letter_space = g_RenameInfo.layout.detail[0].TextLetterSpace;
}

void RenameScreen::font_initial3()
{

    if(myfont2)
    {
        lv_ft_font_destroy(myfont2);
        myfont2 = nullptr;
    }

    //duty
    static lv_ft_info_t ft_font2;
    font_scan_file_path(g_RenameInfo.layout.detail[2].TextFont,&ft_font2.name);
    ft_font2.weight = g_RenameInfo.layout.detail[2].TextSize*680/1024;//字号
    ft_font2.style = g_RenameInfo.layout.detail[2].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font2);
    myfont2 =ft_font2.font;

    lv_draw_label_dsc_init(&label_dsc2);//初始化文本
    label_dsc2.font = myfont2;
    label_dsc2.align = g_RenameInfo.layout.detail[2].HorizontalAlign;
    label_dsc2.line_space = g_RenameInfo.layout.detail[2].TextLineSpace;
    label_dsc2.letter_space = g_RenameInfo.layout.detail[2].TextLetterSpace;

}

void RenameScreen::font_initial2()
{
    if(myfont1)
    {
        lv_ft_font_destroy(myfont1);
        myfont1 = nullptr;
    }
    //company
    static lv_ft_info_t ft_font1;
    font_scan_file_path(g_RenameInfo.layout.detail[1].TextFont,&ft_font1.name);
    ft_font1.weight = g_RenameInfo.layout.detail[1].TextSize*680/1024;//字号
    ft_font1.style = g_RenameInfo.layout.detail[1].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font1);
    myfont1 =ft_font1.font;

    lv_draw_label_dsc_init(&label_dsc1);//初始化文本
    label_dsc1.font = myfont1;

    label_dsc1.align = g_RenameInfo.layout.detail[1].HorizontalAlign;
    label_dsc1.line_space = g_RenameInfo.layout.detail[1].TextLineSpace;
    label_dsc1.letter_space = g_RenameInfo.layout.detail[1].TextLetterSpace;
}
void RenameScreen::font_initial()
{
    uint8_t color[3]={0};
    //username
    static lv_ft_info_t ft_font0;
    font_scan_file_path(g_RenameInfo.layout.detail[0].TextFont,&ft_font0.name);
    ft_font0.weight = g_RenameInfo.layout.detail[0].TextSize*680/1024;//字号
    ft_font0.style = g_RenameInfo.layout.detail[0].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font0);
    myfont0 =ft_font0.font;

    lv_draw_label_dsc_init(&label_dsc0);//初始化文本
    label_dsc0.font = myfont0;
    label_dsc0.align = g_RenameInfo.layout.detail[0].HorizontalAlign;
    label_dsc0.line_space = g_RenameInfo.layout.detail[0].TextLineSpace;
    label_dsc0.letter_space = g_RenameInfo.layout.detail[0].TextLetterSpace;

    hexStringToByte(color,g_RenameInfo.layout.detail[0].TextColor,strlen(g_RenameInfo.layout.detail[0].TextColor));//文本颜色
    label_dsc0.color = lv_color_make(color[0],color[1],color[2]);



    //duty
    static lv_ft_info_t ft_font2;
    font_scan_file_path(g_RenameInfo.layout.detail[2].TextFont,&ft_font2.name);
    ft_font2.weight = g_RenameInfo.layout.detail[2].TextSize*680/1024;//字号
    ft_font2.style = g_RenameInfo.layout.detail[2].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font2);
    myfont2 =ft_font2.font;

    lv_draw_label_dsc_init(&label_dsc2);//初始化文本
    label_dsc2.font = myfont2;
    label_dsc2.align = g_RenameInfo.layout.detail[2].HorizontalAlign;
    label_dsc2.line_space = g_RenameInfo.layout.detail[2].TextLineSpace;
    label_dsc2.letter_space = g_RenameInfo.layout.detail[2].TextLetterSpace;

    hexStringToByte(color,g_RenameInfo.layout.detail[2].TextColor,strlen(g_RenameInfo.layout.detail[2].TextColor));//文本颜色
    label_dsc2.color = lv_color_make(color[0],color[1],color[2]);

    //company
    static lv_ft_info_t ft_font1;
    font_scan_file_path(g_RenameInfo.layout.detail[1].TextFont,&ft_font1.name);
    ft_font1.weight = g_RenameInfo.layout.detail[1].TextSize*680/1024;//字号
    ft_font1.style = g_RenameInfo.layout.detail[1].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font1);
    myfont1 =ft_font1.font;

    lv_draw_label_dsc_init(&label_dsc1);//初始化文本
    label_dsc1.font = myfont1;

    label_dsc1.align = g_RenameInfo.layout.detail[1].HorizontalAlign;
    label_dsc1.line_space = g_RenameInfo.layout.detail[1].TextLineSpace;
    label_dsc1.letter_space = g_RenameInfo.layout.detail[1].TextLetterSpace;

    hexStringToByte(color,g_RenameInfo.layout.detail[1].TextColor,strlen(g_RenameInfo.layout.detail[1].TextColor));//文本颜色
    label_dsc1.color = lv_color_make(color[0],color[1],color[2]);
}

void RenameScreen::font_destroy(void)
{
    if(myfont0)
    {
        lv_ft_font_destroy(myfont0);
        myfont0 = nullptr;
    }
    if(myfont1)
    {
        lv_ft_font_destroy(myfont1);
        myfont1 = nullptr;
    }
    if(myfont2)
    {
        lv_ft_font_destroy(myfont2);
        myfont2 = nullptr;
    }
}

void RenameScreen::font_reset(void)
{
    font_destroy();
    font_initial();
}


lv_color_t* RenameScreen::create_canvas(void)
{
    static lv_color_t buf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_HOR_SIZE, CANVAS_VER_SIZE)];//分配buf存放画板数据
    if(canvas==nullptr)
    {
        canvas =new LvcppCanvas(mparent);
    }
    canvas->set_size(CANVAS_HOR_SIZE,CANVAS_VER_SIZE);
    canvas->set_buffer(buf, CANVAS_HOR_SIZE, CANVAS_VER_SIZE, LV_IMG_CF_TRUE_COLOR);//设置画板空间
    canvas->align(LV_ALIGN_TOP_LEFT, 0, 0);//画板居左对齐显示
    canvas->fill_bg(lv_color_hex(0xff0000), LV_OPA_COVER);//画板默认背景色
    lv_draw_img_dsc_init(&img_draw_dsc);
    font_initial();
    return buf;
}

void RenameScreen::repaint_canvas(void)
{
    uint8_t color[3]={0};
    char imgPath[FILE_PATH_LONG]={0};
    if(renameheadopt->mscreen)
    {
        font_reset();
        hexStringToByte(color,g_RenameInfo.layout.BgColor,strlen(g_RenameInfo.layout.BgColor));
        memset(imgPath,0,FILE_PATH_LONG);
        sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,g_RenameInfo.layout.BgImg);
        if(strlen(g_RenameInfo.layout.BgImg)>0 && access(imgPath,F_OK) == 0)
        {
            pthread_mutex_lock(&decodelock);
            if(idcard!=nullptr)
            {
                free_image(idcard);
                idcard = nullptr;
            }
            idcard = resize_image(imgPath,680,400);
            pthread_mutex_unlock(&decodelock);
            //renameheadopt->mscreen->set_main_bg_img_src();//画板背景图
        }
        else
        {
            renameheadopt->mscreen->set_main_bg_color(lv_color_make(color[0],color[1],color[2]), LV_OPA_COVER);//画板背景色
        }

        renameheadopt->usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX*680/1024,g_RenameInfo.layout.detail[2].ElePointY*400/600); //  *680/1024
        renameheadopt->usre_duty_label->set_size(g_RenameInfo.layout.detail[2].EleWidth*680/1024,g_RenameInfo.layout.detail[2].EleHeight*400/600);

        renameheadopt->usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX*680/1024,g_RenameInfo.layout.detail[1].ElePointY*400/600);
        renameheadopt->usre_company_label->set_size(g_RenameInfo.layout.detail[1].EleWidth*680/1024,g_RenameInfo.layout.detail[1].EleHeight*400/600);

        renameheadopt->usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX*680/1024,g_RenameInfo.layout.detail[0].ElePointY*400/600);
        renameheadopt->usre_param_label->set_size(g_RenameInfo.layout.detail[0].EleWidth*680/1024,g_RenameInfo.layout.detail[0].EleHeight*400/600);

    }
}

void RenameScreen::clear_canvas(void)
{
    repaint_canvas();
}

void RenameScreen::delete_canvas(void)
{
    if(canvas)
    {
        delete canvas;
        canvas = nullptr;
    }
    font_destroy();
}


void RenameScreen::font_scan_file_path(char* name,const char** font)
{
    char path[1024];
    if(strcmp(name,"黑体")==0)
    {
        *font = "./resource/font/HeiTi.ttf";
    }
    else if(strcmp(name,"楷体")==0)
    {
        *font = "./resource/font/FZKT.ttf";
    }
    else if(strcmp(name,"魏体")==0)
    {
        *font = "./resource/font/HWXW.ttf";
    }
    else if(strcmp(name,"宋体")==0)
    {
        *font = "./resource/font/HWZS.ttf";
    }
    else if(strcmp(name,"隶书")==0)
    {
        *font = "./resource/font/LS.ttf";
    }
    else if(strcmp(name,"标宋")==0)
    {
        *font = "./resource/font/BiaoSong.ttf";
    }
    else if(strcmp(name,"中宋")==0)
    {
        *font = "./resource/font/ZhongSong.ttf";
    }
    else if(strcmp(name,"等宽")==0)
    {
        *font = "./resource/font/Deng.ttf";
    }
    else if(strcmp(name,"微软雅黑")==0)
    {
        *font = "./resource/font/WRYH.ttf";
    }
    else
    {
        if(name && strlen(name)>0)
        {
            memset(path,0,sizeof(path));
            //LV_LOG_USER("name=%s",name);
            sprintf(path,"./resource/font/temp.ttf");
            if(access(path,F_OK) == 0)
            {
                *(font) = path;
            }
            else
            {
                *font = "./resource/font/FZKT.ttf";
            }
        }
        else
        {
            *font = "./resource/font/FZKT.ttf";
        }
    }
}

uint8_t RenameScreen::toByte(char c)
{
    unsigned char value = 0;

    if (c >= '0' && c <= '9')
        value = c - '0';
    else if (c >= 'A' && c <= 'Z')
        value = c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        value = c - 'a' + 10;

    return value;
}

void RenameScreen::hexStringToByte(uint8_t *dstByte,const char *srcHexString ,int len)
{
    int index;

    for (int i = 0; i < len; i++){
        index = i * 2;
        dstByte[i] = ((toByte(srcHexString[index]))<<4) | toByte(srcHexString[index+1]);
    }
}

void RenameScreen::BgraToRgb(uint8_t *bgraData,int width,int height,uint8_t*rgbData)
{
    uint8_t bgrData[width*height*3];
    memset(bgrData,0,sizeof(bgrData));
    for(int i=0,j=0; j<width * height*4; i+=3,j+=4)
    {
        bgrData[i] = bgraData[j];
        bgrData[i+1] = bgraData[j+1];
        bgrData[i+2] = bgraData[j+2];
    }
    for(int n=0,m=0; n < width * height; n++,m+=3){
        uint8_t b_value = bgrData[m];
        uint8_t g_value = bgrData[m+1];
        uint8_t r_value = bgrData[m+2];
        *rgbData++ = r_value;
        *rgbData++ = g_value;
        *rgbData++ = b_value;
      }
}

//左上
RenameheadScreen::RenameheadScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    //mscreen->set_bg_color(lv_color_hex(0x00FFFF),LV_OPA_40);
    mscreen->set_size(680,400);
    mscreen->set_pos(5,5);
    //mparent = mscreen->get_screen();
    //mscreen->set_bg_color(lv_color_hex(0xFF0000),LV_OPA_100);
    mscreen->add_flag(LV_OBJ_FLAG_CLICKABLE);
    mscreen->add_flag(LV_OBJ_FLAG_CHECKABLE);
    mscreen->clear_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLLABLE);
    mscreen->set_style_clip_corner(true,0);
    mscreen->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    //mscreen->add_event_cb(textarea_event_hander,LV_EVENT_DOUBLE_CLICKED,this);
    mparent = mscreen->myobj;
    renameheadopt = this;
    initial();
}

RenameheadScreen::~RenameheadScreen()
{

}


void RenameheadScreen::initial()
{

    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }
    renameopt->font_reset();
    //renameopt->repaint_canvas();
    if(usre_param_label == nullptr)
    {
        usre_param_label = new LvcppLabel(mparent);
        usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);
        usre_param_label->set_size(g_RenameInfo.layout.detail[0].EleWidth,g_RenameInfo.layout.detail[0].EleHeight);
        usre_param_label->set_style_text_letter_space(g_RenameInfo.layout.detail[0].TextLetterSpace,0);
        usre_param_label->txt_align(g_RenameInfo.layout.detail[0].HorizontalAlign);
        usre_param_label->set_txt(g_RenameInfo.username);
        usre_param_label->set_style_text_font(renameopt->myfont0,0);
        usre_param_label->txt_color(renameopt->label_dsc0.color,0);
        usre_param_label->add_flag(LV_OBJ_FLAG_CLICKABLE);
        usre_param_label->clear_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
        usre_param_label->clear_flag(LV_OBJ_FLAG_SCROLLABLE);
        usre_param_label->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        usre_param_label->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_VER);
        usre_param_label->set_style_clip_corner(true,0);
        usre_param_label->set_main_pad_all(0);
        usre_param_label->set_style_text_line_space(0,0);
        usre_param_label->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        usre_param_label->add_event_cb(textarea_event_hander,LV_EVENT_PRESSED,this);
        usre_param_label->add_event_cb(textarea_event_hander,LV_EVENT_DOUBLE_CLICKED,this);
        usre_param_label->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(usre_company_label == nullptr)
    {
        usre_company_label = new LvcppLabel(mparent);
        usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX*680/1024,g_RenameInfo.layout.detail[1].ElePointY);
        usre_company_label->set_size(g_RenameInfo.layout.detail[1].EleWidth,g_RenameInfo.layout.detail[1].EleHeight);
        usre_company_label->set_style_text_letter_space(g_RenameInfo.layout.detail[1].TextLetterSpace,0);
        usre_company_label->txt_align(g_RenameInfo.layout.detail[1].HorizontalAlign);
        usre_company_label->set_txt(g_RenameInfo.company);
        usre_company_label->set_style_text_font(renameopt->myfont1,0);
        usre_company_label->txt_color(renameopt->label_dsc1.color,0);
        usre_company_label->add_flag(LV_OBJ_FLAG_CLICKABLE);
        usre_company_label->clear_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
        usre_company_label->clear_flag(LV_OBJ_FLAG_SCROLLABLE);
        usre_company_label->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        usre_company_label->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_VER);
        usre_company_label->set_style_clip_corner(true,0);
        usre_company_label->set_main_pad_all(0);
        usre_company_label->set_style_text_line_space(0,0);
        usre_company_label->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        usre_company_label->add_event_cb(textarea_event_hander,LV_EVENT_PRESSED,this);
        usre_company_label->add_event_cb(textarea_event_hander,LV_EVENT_DOUBLE_CLICKED,this);
        usre_company_label->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);

    }
    if(usre_duty_label == nullptr)
    {
        usre_duty_label = new LvcppLabel(mparent);
        usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY);
        usre_duty_label->set_size(g_RenameInfo.layout.detail[2].EleWidth,g_RenameInfo.layout.detail[2].EleHeight);
        usre_duty_label->set_style_text_letter_space(g_RenameInfo.layout.detail[2].TextLetterSpace,0);
        usre_duty_label->txt_align(g_RenameInfo.layout.detail[2].HorizontalAlign);
        usre_duty_label->set_txt(g_RenameInfo.duty);
        usre_duty_label->set_style_text_font(renameopt->myfont2,0);
        usre_duty_label->txt_color(renameopt->label_dsc2.color,0);
        usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_100);
        usre_duty_label->add_flag(LV_OBJ_FLAG_CLICKABLE);
        usre_duty_label->clear_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
        usre_duty_label->clear_flag(LV_OBJ_FLAG_SCROLLABLE);
        usre_duty_label->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        usre_duty_label->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_VER);
        usre_duty_label->set_style_clip_corner(true,0);
        usre_duty_label->set_main_pad_all(0);
        usre_duty_label->set_style_text_line_space(0,0);
        usre_duty_label->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        usre_duty_label->add_event_cb(textarea_event_hander,LV_EVENT_PRESSED,this);
        usre_duty_label->add_event_cb(textarea_event_hander,LV_EVENT_DOUBLE_CLICKED,this);
        usre_duty_label->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
}
void RenameheadScreen::label_bg_change(int r,int g ,int b)
{
    mscreen->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);
}

void RenameheadScreen::Parameter_reduction(void)
{
    char x_tmp[10]={0};
    char y_tmp[10]={0};
    char w_tmp[10];
    char h_tmp[10];
    char TextLetterSpace_tmp[10];
    char TextSize_tmp[10];

    char x_tmp1[10]={0};
    char y_tmp1[10]={0};
    char w_tmp1[10];
    char h_tmp1[10];
    char TextLetterSpace_tmp1[10];
    char TextSize_tmp1[10];


    char x_tmp2[10]={0};
    char y_tmp2[10]={0};
    char w_tmp2[10];
    char h_tmp2[10];
    char TextLetterSpace_tmp2[10];
    char TextSize_tmp2[10];


    //LV_LOG_USER("00000000000000  %d %d",g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);
    //LV_LOG_USER("11111111111111  %d %d",g_RenameInfo.layout.detail[1].ElePointX,g_RenameInfo.layout.detail[1].ElePointY);
    //LV_LOG_USER("22222222222222  %d %d",g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY);

    g_RenameInfo.layout.detail[0].ElePointX = g_RenameInfo.layout.detail[0].ElePointX;///1.66
    g_RenameInfo.layout.detail[0].ElePointY = g_RenameInfo.layout.detail[0].ElePointY;
    g_RenameInfo.layout.detail[0].EleWidth = g_RenameInfo.layout.detail[0].EleWidth;//*600/1024
    g_RenameInfo.layout.detail[0].EleHeight = g_RenameInfo.layout.detail[0].EleHeight;//*450/1024
    g_RenameInfo.layout.detail[0].TextSize  = g_RenameInfo.layout.detail[0].TextSize;
    g_RenameInfo.layout.detail[0].TextLetterSpace = g_RenameInfo.layout.detail[0].TextLetterSpace;

    g_RenameInfo.layout.detail[1].ElePointX = g_RenameInfo.layout.detail[1].ElePointX;
    g_RenameInfo.layout.detail[1].ElePointY = g_RenameInfo.layout.detail[1].ElePointY;
    g_RenameInfo.layout.detail[1].EleWidth = g_RenameInfo.layout.detail[1].EleWidth;//*600/1024
    g_RenameInfo.layout.detail[1].EleHeight = g_RenameInfo.layout.detail[1].EleHeight;//*450/1024
    g_RenameInfo.layout.detail[1].TextSize  = g_RenameInfo.layout.detail[1].TextSize;
    g_RenameInfo.layout.detail[1].TextLetterSpace = g_RenameInfo.layout.detail[1].TextLetterSpace;

    g_RenameInfo.layout.detail[2].ElePointX = g_RenameInfo.layout.detail[2].ElePointX;
    g_RenameInfo.layout.detail[2].ElePointY = g_RenameInfo.layout.detail[2].ElePointY;
    g_RenameInfo.layout.detail[2].EleWidth = g_RenameInfo.layout.detail[2].EleWidth;//*600/1024
    g_RenameInfo.layout.detail[2].EleHeight = g_RenameInfo.layout.detail[2].EleHeight;//*450/1024
    g_RenameInfo.layout.detail[2].TextSize  = g_RenameInfo.layout.detail[2].TextSize;
    g_RenameInfo.layout.detail[2].TextLetterSpace = g_RenameInfo.layout.detail[2].TextLetterSpace;

    renameopt->font_reset();

    //LV_LOG_USER("00000000000000  %d %d",g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);
    //LV_LOG_USER("11111111111111  %d %d",g_RenameInfo.layout.detail[1].ElePointX,g_RenameInfo.layout.detail[1].ElePointY);
    //LV_LOG_USER("22222222222222  %d %d",g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY);

    sprintf(x_tmp,"%d",g_RenameInfo.layout.detail[0].ElePointX);
    sprintf(y_tmp,"%d",g_RenameInfo.layout.detail[0].ElePointY);
    sprintf(w_tmp,"%d",g_RenameInfo.layout.detail[0].EleWidth);
    sprintf(h_tmp,"%d",g_RenameInfo.layout.detail[0].EleHeight);
    sprintf(TextSize_tmp,"%d",g_RenameInfo.layout.detail[0].TextSize);
    sprintf(TextLetterSpace_tmp,"%d",g_RenameInfo.layout.detail[0].TextLetterSpace);

    sprintf(x_tmp1,"%d",g_RenameInfo.layout.detail[1].ElePointX);
    sprintf(y_tmp1,"%d",g_RenameInfo.layout.detail[1].ElePointY);
    sprintf(w_tmp1,"%d",g_RenameInfo.layout.detail[1].EleWidth);
    sprintf(h_tmp1,"%d",g_RenameInfo.layout.detail[1].EleHeight);
    sprintf(TextSize_tmp1,"%d",g_RenameInfo.layout.detail[1].TextSize);
    sprintf(TextLetterSpace_tmp1,"%d",g_RenameInfo.layout.detail[1].TextLetterSpace);

    sprintf(x_tmp2,"%d",g_RenameInfo.layout.detail[2].ElePointX);
    sprintf(y_tmp2,"%d",g_RenameInfo.layout.detail[2].ElePointY);
    sprintf(w_tmp2,"%d",g_RenameInfo.layout.detail[2].EleWidth);
    sprintf(h_tmp2,"%d",g_RenameInfo.layout.detail[2].EleHeight);
    sprintf(TextSize_tmp2,"%d",g_RenameInfo.layout.detail[2].TextSize);
    sprintf(TextLetterSpace_tmp2,"%d",g_RenameInfo.layout.detail[2].TextLetterSpace);

    if(param_state == 1)
    {
        //LV_LOG_USER(" x_tmp =  %s y_tmp = %s",x_tmp, y_tmp);
        renameinpuopt->font_x->set_txt(x_tmp);
        renameinpuopt->font_y->set_txt(y_tmp);
        renameinpuopt->font_w->set_txt(w_tmp);
        renameinpuopt->font_h->set_txt(h_tmp);
        renameeffectopt->font_between->set_txt(TextLetterSpace_tmp);
        renameeffectopt->font_size->set_txt(TextSize_tmp);
    }
    else if(param_state == 2)
    {
        //LV_LOG_USER(" x_tmp =  %s y_tmp = %s",x_tmp, y_tmp);
        renameinpuopt->font_x->set_txt(x_tmp1);
        renameinpuopt->font_y->set_txt(y_tmp1);
        renameinpuopt->font_w->set_txt(w_tmp1);
        renameinpuopt->font_h->set_txt(h_tmp1);
        renameeffectopt->font_between->set_txt(TextLetterSpace_tmp1);
        renameeffectopt->font_size->set_txt(TextSize_tmp1);
    }
    else if(param_state == 3)
    {
        //LV_LOG_USER(" x_tmp =  %s y_tmp = %s",x_tmp, y_tmp);
        renameinpuopt->font_x->set_txt(x_tmp2);
        renameinpuopt->font_y->set_txt(y_tmp2);
        renameinpuopt->font_w->set_txt(w_tmp2);
        renameinpuopt->font_h->set_txt(h_tmp2);
        renameeffectopt->font_between->set_txt(TextLetterSpace_tmp2);
        renameeffectopt->font_size->set_txt(TextSize_tmp2);
    }
    renameheadopt->usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX*680/1024,g_RenameInfo.layout.detail[0].ElePointY*400/600);
    renameheadopt->usre_param_label->set_size(g_RenameInfo.layout.detail[0].EleWidth*680/1024,g_RenameInfo.layout.detail[0].EleHeight*680/1024);
    renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
    renameheadopt->usre_param_label->set_style_text_letter_space(g_RenameInfo.layout.detail[0].TextLetterSpace*680/1024,0);

    renameheadopt->usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX*680/1024,g_RenameInfo.layout.detail[1].ElePointY*400/600);
    renameheadopt->usre_company_label->set_size(g_RenameInfo.layout.detail[1].EleWidth*680/1024,g_RenameInfo.layout.detail[1].EleHeight*680/1024);
    renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);
    renameheadopt->usre_company_label->set_style_text_letter_space(g_RenameInfo.layout.detail[1].TextLetterSpace*680/1024,0);

    renameheadopt->usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX*680/1024,g_RenameInfo.layout.detail[2].ElePointY*400/600);
    renameheadopt->usre_duty_label->set_size(g_RenameInfo.layout.detail[2].EleWidth*680/1024,g_RenameInfo.layout.detail[2].EleHeight*680/1024);
    renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
    renameheadopt->usre_duty_label->set_style_text_letter_space(g_RenameInfo.layout.detail[2].TextLetterSpace*680/1024,0);
}


void RenameheadScreen::param_change(int param)
{
    //LV_LOG_USER("!!!!!!!!!!!!!!param_change!!!!!!!!!!!!!!!!!!!!");

    //char font_type[128];
    //static lv_ft_info_t ft_font0;


    //LV_LOG_USER("TextFont0 = %s,TextFont1 = %s,TextFont2 = %s",g_RenameInfo.layout.detail[0].TextFont,g_RenameInfo.layout.detail[1].TextFont,g_RenameInfo.layout.detail[2].TextFont);
    if(param_state == 1)
    {
        //刷新
        char x_t[128];
        char y_t[128];
        char wide_t[128];
        char h_t[128];
        char font_space_between_t[128];
        char font_size_t[128];
        //LV_LOG_USER("000000000");
        snprintf(x_t,sizeof(x_t),"%d",g_RenameInfo.layout.detail[0].ElePointX);
        snprintf(y_t,sizeof(y_t),"%d",g_RenameInfo.layout.detail[0].ElePointY);
        snprintf(wide_t,sizeof(wide_t),"%d",g_RenameInfo.layout.detail[0].EleWidth);
        snprintf(h_t,sizeof(h_t),"%d",g_RenameInfo.layout.detail[0].EleHeight);
        snprintf(font_space_between_t,sizeof(font_space_between_t),"%d",g_RenameInfo.layout.detail[0].TextLetterSpace);
        snprintf(font_size_t,sizeof(font_size_t),"%d",g_RenameInfo.layout.detail[0].TextSize);

        renameinpuopt->font_x->set_txt(x_t);
        renameinpuopt->font_y->set_txt(y_t);
        renameinpuopt->font_w->set_txt(wide_t);
        renameinpuopt->font_h->set_txt(h_t);
        renameeffectopt->font_size->set_txt(font_size_t);
        renameeffectopt->font_between->set_txt(font_space_between_t);
        //renameeffectopt->change_refont_style->get_selected_str(g_RenameInfo.layout.detail[0].TextFont,sizeof(g_RenameInfo.layout.detail[0].TextFont));
    }
    else if(param_state == 2)
    {
        //刷新
        char x_t[128];
        char y_t[128];
        char wide_t[128];
        char h_t[128];
        char font_space_between_t[128];
        char font_size_t[128];
        //LV_LOG_USER("1111111");
        snprintf(x_t,sizeof(x_t),"%d",g_RenameInfo.layout.detail[1].ElePointX);
        snprintf(y_t,sizeof(y_t),"%d",g_RenameInfo.layout.detail[1].ElePointY);
        snprintf(wide_t,sizeof(wide_t),"%d",g_RenameInfo.layout.detail[1].EleWidth);
        snprintf(h_t,sizeof(h_t),"%d",g_RenameInfo.layout.detail[1].EleHeight);
        snprintf(font_space_between_t,sizeof(font_space_between_t),"%d",g_RenameInfo.layout.detail[1].TextLetterSpace);
        snprintf(font_size_t,sizeof(font_size_t),"%d",g_RenameInfo.layout.detail[1].TextSize);

        renameinpuopt->font_x->set_txt(x_t);
        renameinpuopt->font_y->set_txt(y_t);
        renameinpuopt->font_w->set_txt(wide_t);
        renameinpuopt->font_h->set_txt(h_t);
        renameeffectopt->font_size->set_txt(font_size_t);
        renameeffectopt->font_between->set_txt(font_space_between_t);

        //renameeffectopt->change_refont_style->get_selected_str(g_RenameInfo.layout.detail[1].TextFont,sizeof(g_RenameInfo.layout.detail[1].TextFont));
    }
    else if(param_state == 3)
    {
        //刷新
        char x_t[128];
        char y_t[128];
        char wide_t[128];
        char h_t[128];
        char font_space_between_t[128];
        char font_size_t[128];
        //LV_LOG_USER("22222222");
        snprintf(x_t,sizeof(x_t),"%d",g_RenameInfo.layout.detail[2].ElePointX);
        snprintf(y_t,sizeof(y_t),"%d",g_RenameInfo.layout.detail[2].ElePointY);
        snprintf(wide_t,sizeof(wide_t),"%d",g_RenameInfo.layout.detail[2].EleWidth);
        snprintf(h_t,sizeof(h_t),"%d",g_RenameInfo.layout.detail[2].EleHeight);
        snprintf(font_space_between_t,sizeof(font_space_between_t),"%d",g_RenameInfo.layout.detail[2].TextLetterSpace);
        snprintf(font_size_t,sizeof(font_size_t),"%d",g_RenameInfo.layout.detail[2].TextSize);

        renameinpuopt->font_x->set_txt(x_t);
        renameinpuopt->font_y->set_txt(y_t);
        renameinpuopt->font_w->set_txt(wide_t);
        renameinpuopt->font_h->set_txt(h_t);
        renameeffectopt->font_size->set_txt(font_size_t);
        renameeffectopt->font_between->set_txt(font_space_between_t);

        //renameeffectopt->change_refont_style->get_selected_str(g_RenameInfo.layout.detail[2].TextFont,sizeof(g_RenameInfo.layout.detail[2].TextFont));
    }

    //LV_LOG_USER("TextFont = %s,TextSize = %d",g_RenameInfo.layout.detail[param_state-1].TextFont,g_RenameInfo.layout.detail[param_state-1].TextSize);
    //renameopt->font_reset();
    //LV_LOG_USER("TextFont = %s,TextSize = %d",g_RenameInfo.layout.detail[param_state-1].TextFont,g_RenameInfo.layout.detail[param_state-1].TextSize);
    //LV_LOG_USER("x_t =%s,y_t=%s,param = %d",x_t,y_t,param);



    //对齐方式
    ////LV_LOG_USER("HorizontalAlign = %d",g_RenameInfo.layout.detail[param-1].HorizontalAlign);
    //LV_LOG_USER("HorizontalAlign0 = %d,HorizontalAlign1 = %d,HorizontalAlign2 = %d",g_RenameInfo.layout.detail[0].HorizontalAlign,g_RenameInfo.layout.detail[1].HorizontalAlign,g_RenameInfo.layout.detail[2].HorizontalAlign);
    if(g_RenameInfo.layout.detail[param_state-1].HorizontalAlign == 0)
    {
        renameeffectopt->change_font_alignment->set_selected(0);
    }
    else if(g_RenameInfo.layout.detail[param_state-1].HorizontalAlign == 1)
    {
        renameeffectopt->change_font_alignment->set_selected(0);
    }
    else if(g_RenameInfo.layout.detail[param_state-1].HorizontalAlign == 2)
    {
        renameeffectopt->change_font_alignment->set_selected(1);
    }
    else if(g_RenameInfo.layout.detail[param_state-1].HorizontalAlign == 3)
    {
        renameeffectopt->change_font_alignment->set_selected(2);
    }

    //样式 粗体 斜体
    ////LV_LOG_USER("TextType = %d",g_RenameInfo.layout.detail[param-1].TextType);
    //LV_LOG_USER("TextType0 = %d,TextType1 = %d,TextType2 = %d",g_RenameInfo.layout.detail[0].TextType,g_RenameInfo.layout.detail[1].TextType,g_RenameInfo.layout.detail[2].TextType);
    if(g_RenameInfo.layout.detail[param_state-1].TextType == 0)
    {
        renameeffectopt->change_refont_form->set_selected(0);
    }
    else if(g_RenameInfo.layout.detail[param_state-1].TextType == 1)
    {
        renameeffectopt->change_refont_form->set_selected(1);
    }
    else if(g_RenameInfo.layout.detail[param_state-1].TextType == 2)
    {
        renameeffectopt->change_refont_form->set_selected(2);
    }


    //字形 宋体
    ////LV_LOG_USER("TextFont = %s",g_RenameInfo.layout.detail[param-1].TextFont);

    //LV_LOG_USER("TextFont0 = %s,TextFont1 = %s,TextFont2 = %s",g_RenameInfo.layout.detail[0].TextFont,g_RenameInfo.layout.detail[1].TextFont,g_RenameInfo.layout.detail[2].TextFont);
    if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "黑体") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(0);
    }
    else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "楷体") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(1);
    }
    else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "魏体") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(2);
    }
    else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "宋体") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(3);
    }
    else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "隶书") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(4);
    }
    else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "标宋") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(5);
    }
    else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "中宋") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(6);
    }

    else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "等宽") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(7);
    }
    else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "微软雅黑") == 0)
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(8);
    }
    else
    {
        //LV_LOG_USER("/////////");
        renameeffectopt->change_refont_style->set_selected(9);
    }



    if(renameopt->re_fontset != NULL)
    {
        char x_t1[128];
        char y_t1[128];
        char wide_t1[128];
        char h_t1[128];
        char font_space_between_t1[128];
        //char font_line_between_t1[128];
        char font_size_t1[128];
        //LV_LOG_USER("ElePointX = %d ,ElePointY =%d ",g_RenameInfo.layout.detail[param-1].ElePointX,g_RenameInfo.layout.detail[param-1].ElePointY);
        snprintf(x_t1,sizeof(x_t1),"%d",g_RenameInfo.layout.detail[param-1].ElePointX);
        snprintf(y_t1,sizeof(y_t1),"%d",g_RenameInfo.layout.detail[param-1].ElePointY);
        snprintf(wide_t1,sizeof(wide_t1),"%d",g_RenameInfo.layout.detail[param-1].EleWidth);
        snprintf(h_t1,sizeof(h_t1),"%d",g_RenameInfo.layout.detail[param-1].EleHeight);
        snprintf(font_space_between_t1,sizeof(font_space_between_t1),"%d",g_RenameInfo.layout.detail[param-1].TextLetterSpace);
        //snprintf(font_line_between_t1,sizeof(font_line_between_t1),"%d",g_RenameInfo.layout.detail[param-1].TextLineSpace);
        snprintf(font_size_t1,sizeof(font_size_t1),"%d",g_RenameInfo.layout.detail[param-1].TextSize);
        //renamfontsetwinopt->change_refont_style->get_selected_str(g_RenameInfo.layout.detail[param_state-1].TextFont,sizeof(g_RenameInfo.layout.detail[param_state-1].TextFont));
        //renameopt->font_reset();
        //LV_LOG_USER("!!!!!!!!!!!!!!!!!!!!!!TextFont!!!!!!!!!!!!!!!!!!!! = %s",g_RenameInfo.layout.detail[param_state-1].TextFont);

        if(renameopt->re_fontset != NULL)
        {
            renamfontsetwinopt->font_x->set_txt(x_t1);
            renamfontsetwinopt->font_y->set_txt(y_t1);
            renamfontsetwinopt->font_w->set_txt(wide_t1);
            renamfontsetwinopt->font_h->set_txt(h_t1);
            renamfontsetwinopt->font_size->set_txt(font_size_t1);
            renamfontsetwinopt->font_between->set_txt(font_space_between_t1);
            //对齐方式
            //LV_LOG_USER("sss HorizontalAlign0 = %d",g_RenameInfo.layout.detail[0].HorizontalAlign);
            //LV_LOG_USER("sss HorizontalAlign1 = %d",g_RenameInfo.layout.detail[1].HorizontalAlign);
            //LV_LOG_USER("sss HorizontalAlign2 = %d",g_RenameInfo.layout.detail[2].HorizontalAlign);
            if(g_RenameInfo.layout.detail[param-1].HorizontalAlign == 0)
            {
                renamfontsetwinopt->change_font_alignment->set_selected(0);
            }
            else if(g_RenameInfo.layout.detail[param-1].HorizontalAlign == 1)
            {
                renamfontsetwinopt->change_font_alignment->set_selected(0);
            }
            else if(g_RenameInfo.layout.detail[param-1].HorizontalAlign == 2)
            {
                renamfontsetwinopt->change_font_alignment->set_selected(1);
            }
            else if(g_RenameInfo.layout.detail[param-1].HorizontalAlign == 3)
            {
                renamfontsetwinopt->change_font_alignment->set_selected(2);
            }

            //样式 粗体 斜体
            //LV_LOG_USER("sss TextType0 = %d",g_RenameInfo.layout.detail[0].TextType);
            //LV_LOG_USER("sss TextType1 = %d",g_RenameInfo.layout.detail[1].TextType);
            //LV_LOG_USER("sss TextType2 = %d",g_RenameInfo.layout.detail[2].TextType);
            if(g_RenameInfo.layout.detail[param-1].TextType == 0)
            {
                renamfontsetwinopt->change_refont_form->set_selected(0);
            }
            else if(g_RenameInfo.layout.detail[param-1].TextType == 1)
            {
                renamfontsetwinopt->change_refont_form->set_selected(1);
            }
            else if(g_RenameInfo.layout.detail[param-1].TextType == 2)
            {
                renamfontsetwinopt->change_refont_form->set_selected(2);
            }


            //字形 宋体
            //LV_LOG_USER(" sss TextFont0 = %s",g_RenameInfo.layout.detail[0].TextFont);
            //LV_LOG_USER(" sss TextFont1 = %s",g_RenameInfo.layout.detail[1].TextFont);
            //LV_LOG_USER(" sss TextFont2 = %s",g_RenameInfo.layout.detail[2].TextFont);

            if(strcmp(g_RenameInfo.layout.detail[param-1].TextFont, "黑体") == 0)
            {
                renamfontsetwinopt->change_refont_style->set_selected(0);
            }
            else if(strcmp(g_RenameInfo.layout.detail[param-1].TextFont, "楷体") == 0)
            {
                renamfontsetwinopt->change_refont_style->set_selected(1);
            }
            else if(strcmp(g_RenameInfo.layout.detail[param-1].TextFont, "魏体") == 0)
            {
                renamfontsetwinopt->change_refont_style->set_selected(2);
            }
            else if(strcmp(g_RenameInfo.layout.detail[param-1].TextFont, "宋体") == 0)
            {
                renamfontsetwinopt->change_refont_style->set_selected(3);
            }
            else if(strcmp(g_RenameInfo.layout.detail[param-1].TextFont, "隶书") == 0)
            {
                renamfontsetwinopt->change_refont_style->set_selected(4);
            }
            else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "标宋") == 0)
            {
                //LV_LOG_USER("/////////");
                renamfontsetwinopt->change_refont_style->set_selected(5);
            }
            else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "中宋") == 0)
            {
                //LV_LOG_USER("/////////");
                renamfontsetwinopt->change_refont_style->set_selected(6);
            }

            else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "等宽") == 0)
            {
                //LV_LOG_USER("/////////");
                renamfontsetwinopt->change_refont_style->set_selected(7);
            }
            else if(strcmp(g_RenameInfo.layout.detail[param_state-1].TextFont, "微软雅黑") == 0)
            {
                //LV_LOG_USER("/////////");
                renamfontsetwinopt->change_refont_style->set_selected(8);
            }
            else
            {
                //LV_LOG_USER("/////////");
                renamfontsetwinopt->change_refont_style->set_selected(9);
            }
        }


    }
    renameeffectopt->change_font_size_and_between_auto(param_state,0);
    //LV_LOG_USER("!!!TextFont = %s,TextSize = %d",g_RenameInfo.layout.detail[param_state-1].TextFont,g_RenameInfo.layout.detail[param_state-1].TextSize);
}

void RenameheadScreen::kb_create(void)
{
    if(input_kb == nullptr)
    {
        input_kb = new kbscreen(mparent);
        input_kb->sendcb(kb_cb);
    }
}


void RenameheadScreen::kb_cb(void)
{
    renameheadopt->get_kbinput_text();
    if(renameheadopt->input_kb != nullptr)
    {
        delete renameheadopt->input_kb;
        renameheadopt->input_kb = NULL;
    }
}

void RenameheadScreen::get_kbinput_text(void)
{
    renameinpuopt->rename_button->add_txt(input_kb->input_box->get_text());
    if(param_state == 1)
    {
        //LV_LOG_USER("g_RenameInfo.username");
        strcpy(g_RenameInfo.username,renameinpuopt->rename_button->get_txt());
        usre_param_label->set_txt(g_RenameInfo.username);
    }
    if(param_state == 2)
    {
        //LV_LOG_USER("g_RenameInfo.company");
        strcpy(g_RenameInfo.company,renameinpuopt->rename_button->get_txt());
        usre_company_label->set_txt(g_RenameInfo.company);
    }
    if(param_state == 3)
    {
        //LV_LOG_USER("g_RenameInfo.duty");
        strcpy(g_RenameInfo.duty,renameinpuopt->rename_button->get_txt());
        usre_duty_label->set_txt(g_RenameInfo.duty);
    }
    renameeffectopt->change_font_size_and_between_auto(param_state,0);
}
void RenameheadScreen::pos_update(void)
{
    //LV_LOG_USER("param_state= %d",param_state);
    lv_point_t x_point;
    LvcppIndev::get_indev_point(&x_point);

    if(param_state == 1)
    {
        renameheadopt->usre_param_label->set_pos(x_point.x,x_point.y);
    }
    else if(param_state == 2)
    {
         renameheadopt->usre_company_label->set_pos(x_point.x,x_point.y);
    }
    else if(param_state == 3)
    {
        renameheadopt->usre_duty_label->set_pos(x_point.x,x_point.y);
    }
    char x_tmp[10];
    char y_tmp[10];
    sprintf(x_tmp,"%d",x_point.x);
    sprintf(y_tmp,"%d",x_point.y);
    //renameopt->font_reset();
    g_RenameInfo.layout.detail[param_state-1].ElePointX = x_point.x;
    g_RenameInfo.layout.detail[param_state-1].ElePointY = x_point.y;
    renameinpuopt->font_x->set_txt(x_tmp);
    renameinpuopt->font_y->set_txt(y_tmp);
    if(renameopt->re_fontset != NULL)
    {
        renamfontsetwinopt->font_x->set_txt(x_tmp);
        renamfontsetwinopt->font_y->set_txt(y_tmp);
    }
}

void RenameheadScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenameheadScreen* opt = (RenameheadScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==renameheadopt->usre_param_label->myobj&& param_state_hide != 1)
    {
        if(event->code == LV_EVENT_PRESSING && param_state == 1)
        {
            param_state = 1;
            lv_obj_t* obj = lv_event_get_target(event); //获取事件产生的对象
            lv_indev_t* indev = lv_indev_get_act();  //获取活动界面输入设备
            lv_point_t vect;
            lv_indev_get_vect(indev, &vect); //获取vect point

            lv_point_t cur_point;
            lv_indev_get_point(indev, &cur_point);
            //LV_LOG_USER("cur_point_x = %d,cur_point_y = %d",cur_point.x,cur_point.y);
            if(cur_point.x<=5 || cur_point.x>=685 ||cur_point.y<=5 ||cur_point.y>=405)
            {
                return;
            }
            lv_coord_t x = lv_obj_get_x(obj) + vect.x; //计算x
            lv_coord_t y = lv_obj_get_y(obj) + vect.y; // 计算y

            lv_obj_set_pos(obj, x, y); //移动对象到x,y

            //LV_LOG_USER("x = %d,y = %d",renameheadopt->usre_param_label->pos_x(),renameheadopt->usre_param_label->pos_y());
            char x_tmp[10];
            char y_tmp[10];
            sprintf(x_tmp,"%d",renameheadopt->usre_param_label->pos_x()*1024/680);
            sprintf(y_tmp,"%d",renameheadopt->usre_param_label->pos_y()*600/400);
            renameinpuopt->font_x->set_txt(x_tmp);
            renameinpuopt->font_y->set_txt(y_tmp);
            //renameopt->font_reset();

            g_RenameInfo.layout.detail[param_state-1].ElePointX = renameheadopt->usre_param_label->pos_x()*1024/680;
            g_RenameInfo.layout.detail[param_state-1].ElePointY = renameheadopt->usre_param_label->pos_y()*600/400;

            if(renameopt->re_fontset != NULL)
            {
                renamfontsetwinopt->font_x->set_txt(x_tmp);
                renamfontsetwinopt->font_y->set_txt(y_tmp);
            }

        }
        else if(event->code == LV_EVENT_PRESSED && param_state == 1)
        {
            param_state = 1;
            renameheadopt->mscreen->move_foreground();
        }
        else if(event->code == LV_EVENT_CLICKED)
        {
            param_state = 1;
            renameinpuopt->update_flag_dropdwon();

            //LV_LOG_USER("TextFont0 = %s,TextFont1 = %s,TextFont2 = %s",g_RenameInfo.layout.detail[0].TextFont,g_RenameInfo.layout.detail[1].TextFont,g_RenameInfo.layout.detail[2].TextFont);
            renameinpuopt->show_input_param(param_state);
            //LV_LOG_USER("TextFont0 = %s,TextFont1 = %s,TextFont2 = %s",g_RenameInfo.layout.detail[0].TextFont,g_RenameInfo.layout.detail[1].TextFont,g_RenameInfo.layout.detail[2].TextFont);
            renameheadopt->param_change(param_state);
            color_setopt->get_rgb_vlaue(param_state);

            renameinpuopt->usre_param->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
            renameinpuopt->usre_company->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            //LV_LOG_USER("llllllllllllllllllllllll");
            renameinpuopt->usre_duty->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);


            //LV_LOG_USER("llllllllllllllllllllllll");
            renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            //LV_LOG_USER("llllllllllllllllllllllll");
            renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_100);
            renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);


            //LV_LOG_USER("clicked");
        }
        else if(event->code == LV_EVENT_DOUBLE_CLICKED && param_state == 1)
        {
            param_state = 1;
            if(renameheadopt->input_kb == nullptr)
            {
                renameheadopt->kb_create();
            }
            renameheadopt->input_kb->initial(3);
            renameheadopt->input_kb->input_box->set_text(renameheadopt->usre_param_label->get_txt());
            renameheadopt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }

    }


    else if(target==renameheadopt->usre_company_label->myobj&& company_state_hide != 1)
    {
        if(event->code == LV_EVENT_PRESSING && param_state == 2)
        {
            param_state = 2;
            lv_obj_t* obj = lv_event_get_target(event); //获取事件产生的对象
            lv_indev_t* indev = lv_indev_get_act();  //获取活动界面输入设备
            lv_point_t vect;
            lv_indev_get_vect(indev, &vect); //获取vect point

            lv_point_t cur_point;
            lv_indev_get_point(indev, &cur_point);
            //LV_LOG_USER("cur_point_x = %d,cur_point_y = %d",cur_point.x,cur_point.y);
            if(cur_point.x<=5 || cur_point.x>=685 ||cur_point.y<=5 ||cur_point.y>=405)
            {
                return;
            }
            lv_coord_t x = lv_obj_get_x(obj) + vect.x; //计算x
            lv_coord_t y = lv_obj_get_y(obj) + vect.y; // 计算y
            lv_obj_set_pos(obj, x, y); //移动对象到x,y

            //LV_LOG_USER("x = %d,y = %d",renameheadopt->usre_company_label->pos_x(),renameheadopt->usre_company_label->pos_y());
            char x_tmp[10];
            char y_tmp[10];
            sprintf(x_tmp,"%d",renameheadopt->usre_company_label->pos_x()*1024/680);
            sprintf(y_tmp,"%d",renameheadopt->usre_company_label->pos_y()*600/400);
            //renameopt->font_reset();
            g_RenameInfo.layout.detail[param_state-1].ElePointX = renameheadopt->usre_company_label->pos_x()*1024/680;
            g_RenameInfo.layout.detail[param_state-1].ElePointY = renameheadopt->usre_company_label->pos_y()*600/400;
            renameinpuopt->font_x->set_txt(x_tmp);
            renameinpuopt->font_y->set_txt(y_tmp);
            if(renameopt->re_fontset != NULL)
            {
                renamfontsetwinopt->font_x->set_txt(x_tmp);
                renamfontsetwinopt->font_y->set_txt(y_tmp);
            }
        }
        else if(event->code == LV_EVENT_PRESSED && param_state == 2)
        {
            param_state = 2;
            renameheadopt->mscreen->move_foreground();
        }
        else if(event->code == LV_EVENT_CLICKED)
        {
            param_state = 2;
            renameinpuopt->update_flag_dropdwon();


            //LV_LOG_USER("TextFont0 = %s,TextFont1 = %s,TextFont2 = %s",g_RenameInfo.layout.detail[0].TextFont,g_RenameInfo.layout.detail[1].TextFont,g_RenameInfo.layout.detail[2].TextFont);
            renameinpuopt->show_input_param(param_state);
            //LV_LOG_USER("TextFont0 = %s,TextFont1 = %s,TextFont2 = %s",g_RenameInfo.layout.detail[0].TextFont,g_RenameInfo.layout.detail[1].TextFont,g_RenameInfo.layout.detail[2].TextFont);
            renameheadopt->param_change(param_state);
            color_setopt->get_rgb_vlaue(param_state);

            renameinpuopt->usre_param->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            renameinpuopt->usre_company->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
            //LV_LOG_USER("llllllllllllllllllllllll");
            renameinpuopt->usre_duty->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            //LV_LOG_USER("llllllllllllllllllllllll");
            renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            //LV_LOG_USER("llllllllllllllllllllllll");
            renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_100);
            //LV_LOG_USER("clicked");
        }
        else if(event->code == LV_EVENT_DOUBLE_CLICKED && param_state == 2)
        {
            param_state = 2;
            if(renameheadopt->input_kb == nullptr)
            {
                renameheadopt->kb_create();
            }
            //LV_LOG_USER("usre_name");
            renameheadopt->input_kb->initial(3);
            //renameheadopt->show_text_tmp = 11;
            renameheadopt->input_kb->input_box->set_text(renameheadopt->usre_company_label->get_txt());
            renameheadopt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }

    }


    else  if(target==renameheadopt->usre_duty_label->myobj && duty_state_hide != 1)
    {


        if(event->code == LV_EVENT_PRESSING && param_state == 3)
        {
            param_state = 3;
            lv_obj_t* obj = lv_event_get_target(event); //获取事件产生的对象
            lv_indev_t* indev = lv_indev_get_act();  //获取活动界面输入设备
            lv_point_t vect;
            lv_indev_get_vect(indev, &vect); //获取vect point

            lv_point_t cur_point;
            lv_indev_get_point(indev, &cur_point);
            //LV_LOG_USER("cur_point_x = %d,cur_point_y = %d",cur_point.x,cur_point.y);
            if(cur_point.x<=5 || cur_point.x>=685 ||cur_point.y<=5 ||cur_point.y>=405)
            {
                return;
            }
            lv_coord_t x = lv_obj_get_x(obj) + vect.x; //计算x
            lv_coord_t y = lv_obj_get_y(obj) + vect.y; // 计算y
            lv_obj_set_pos(obj, x, y); //移动对象到x,y

            //LV_LOG_USER("x = %d,y = %d",renameheadopt->usre_duty_label->pos_x(),renameheadopt->usre_company_label->pos_y());
            char x_tmp[10];
            char y_tmp[10];
            sprintf(x_tmp,"%d",renameheadopt->usre_duty_label->pos_x()*1024/680);//*1024/680
            sprintf(y_tmp,"%d",renameheadopt->usre_duty_label->pos_y()*600/400);

            //renameopt->font_reset();
            g_RenameInfo.layout.detail[param_state-1].ElePointX = renameheadopt->usre_duty_label->pos_x()*1024/680;
            g_RenameInfo.layout.detail[param_state-1].ElePointY = renameheadopt->usre_duty_label->pos_y()*600/400;
            renameinpuopt->font_x->set_txt(x_tmp);
            renameinpuopt->font_y->set_txt(y_tmp);
            if(renameopt->re_fontset != NULL)
            {
                renamfontsetwinopt->font_x->set_txt(x_tmp);
                renamfontsetwinopt->font_y->set_txt(y_tmp);
            }
        }
        else if(event->code == LV_EVENT_PRESSED && param_state == 3)
        {
            param_state = 3;
            renameheadopt->mscreen->move_foreground();
        }
        else if(event->code == LV_EVENT_CLICKED)
        {
            param_state = 3;
            renameinpuopt->update_flag_dropdwon();

            //LV_LOG_USER("TextFont0 = %s,TextFont1 = %s,TextFont2 = %s",g_RenameInfo.layout.detail[0].TextFont,g_RenameInfo.layout.detail[1].TextFont,g_RenameInfo.layout.detail[2].TextFont);
            renameinpuopt->show_input_param(param_state);
            //LV_LOG_USER("TextFont0 = %s,TextFont1 = %s,TextFont2 = %s",g_RenameInfo.layout.detail[0].TextFont,g_RenameInfo.layout.detail[1].TextFont,g_RenameInfo.layout.detail[2].TextFont);

            renameheadopt->param_change(param_state);
            color_setopt->get_rgb_vlaue(param_state);

            renameinpuopt->usre_param->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            renameinpuopt->usre_company->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            renameinpuopt->usre_duty->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
            renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_100);
            renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);

            //LV_LOG_USER("clicked");
        }
        else if(event->code == LV_EVENT_DOUBLE_CLICKED && param_state == 3)
        {
            param_state = 3;
            if(renameheadopt->input_kb == nullptr)
            {
                renameheadopt->kb_create();
            }
            //LV_LOG_USER("usre_name");
            renameheadopt->input_kb->initial(3);
            //renameheadopt->show_text_tmp = 11;
            renameheadopt->input_kb->input_box->set_text(renameheadopt->usre_duty_label->get_txt());
            renameheadopt->input_kb->input_box->set_cursor_pos(opt->input_kb->input_box->get_cursor_pos());
        }
    }
    /*
    else if(target == renameheadopt->mscreen->myobj)
    {
        if(event->code == LV_EVENT_DOUBLE_CLICKED )
        {


            if(renameopt->re_color == NULL)
            {
                //LV_LOG_USER("new color");
            }
            else
            {
                //LV_LOG_USER("show color");
                //color_setopt->mscreen->show(true);
            }


            if(renameopt->re_fontset == NULL && key_right_tmp == 1)
            {
                //LV_LOG_USER("new font");
                renameopt->Rename_fontset_Screen();
            }
            else
            {
                //LV_LOG_USER("show font");
                if(key_right_tmp == 1)
                    renamfontsetwinopt->mscreen->show(true);
            }


#if QTSIM_PLATFORM
            if(renameopt->re_box == NULL && key_right_tmp == 1)
            {
                //LV_LOG_USER("new font");
                renameopt->Rename_box_create();
            }
            else
            {
                //LV_LOG_USER("show font");
                if(key_right_tmp == 1)
                    renameboxopt->mscreen->show(true);
            }
#endif

        }

    }*/

}

//左下
RenamebottomScreen::RenamebottomScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    //mscreen->set_bg_color(lv_color_hex(0x777777),LV_OPA_40);
    mscreen->set_size(680,280);
    mscreen->set_pos(0,420);
    mparent = mscreen->get_screen();
    renamebottomopt = this;
    initial();
}

RenamebottomScreen::~RenamebottomScreen()
{
    if(function_tip !=NULL)
    {
        delete  function_tip;
        function_tip = NULL;
    }
    if(rename_line !=NULL)
    {
        delete  rename_line;
        rename_line = NULL;
    }
    if(color_tip !=NULL)
    {
        delete  color_tip;
        color_tip = NULL;
    }
    if(photo_tip !=NULL)
    {
        delete  photo_tip;
        photo_tip = NULL;
    }
    /*
    if(change_pos !=NULL)
    {
        delete  change_pos;
        change_pos = NULL;
    }*/
    if(select_photo_bg !=NULL)
    {
        delete  select_photo_bg;
        select_photo_bg = NULL;
    }
    if(select_rgb_bg !=NULL)
    {
        delete  select_rgb_bg;
        select_rgb_bg = NULL;
    }
    if(mscreen !=NULL)
    {
        delete  mscreen;
        mscreen = NULL;
    }
}

void RenamebottomScreen::initial()
{
    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }
    if(function_tip ==nullptr)
    {
        function_tip = new LvcppLabel(mparent);
        function_tip->set_pos(15,20);
        function_tip->set_size(240,100);
        function_tip->set_style_text_font(myfont->font(),0);
        function_tip->txt_font_size(40,0);
        function_tip->set_txt("背景颜色设置");
    }/*
    if(change_pos == NULL)
    {
        change_pos = new LvcppButton(mparent);
        change_pos->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        change_pos->align_to(function_tip->myobj,LV_ALIGN_RIGHT_MID,210,-45);
        change_pos->set_size(180,44);
        change_pos->add_txt("位置选择");
        change_pos->txt_size(180,44,LV_LABEL_LONG_WRAP);
        change_pos->set_style_text_font(myfont->font(),0);
        change_pos->txt_center();
        change_pos->set_main_radius(10);
        change_pos->txt_color(lv_color_black());    
        change_pos->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        change_pos->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }*/
    if(rename_line == NULL)
    {
        rename_line = new LvcppLabel(mparent);
        rename_line->set_txt("");
        rename_line->set_pos(15,70);
        rename_line->set_size(620,2);
        rename_line->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
    }
    if(color_tip == NULL)
    {
        color_tip = new LvcppLabel(mparent);
        color_tip->set_txt("单色");
        color_tip->set_pos(40,115);
        color_tip->set_size(240,100);
        color_tip->set_style_text_font(myfont->font(),0);
        color_tip->txt_font_size(30,0);

    }
    if(photo_tip == NULL)
    {
        photo_tip = new LvcppLabel(mparent);
        photo_tip->set_txt("图片");
        photo_tip->align_to(color_tip->myobj,LV_ALIGN_RIGHT_MID,0,-35);
        photo_tip->set_size(240,100);
        photo_tip->set_style_text_font(myfont->font(),0);
        photo_tip->txt_font_size(30,0);
    }
    if(select_photo_bg == NULL)
    {
        select_photo_bg =new LvcppDropdown(mparent);
        select_photo_bg->align_to(photo_tip->myobj,LV_ALIGN_RIGHT_MID,-20,-43);
        select_photo_bg->set_size(265,55);
        select_photo_bg->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(select_photo_bg->get_list(),myfont->font(),0);
        lv_obj_set_scrollbar_mode(select_photo_bg->get_list(),LV_SCROLLBAR_MODE_OFF);
        select_photo_bg->set_options("1.png\n2.png\n3.png\n4.png\n5.png\n未使用");
        select_photo_bg->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_0);
        select_photo_bg->set_main_bg_img_src(IAMGE_JIAO_TMP);
        select_photo_bg->set_style_radius(0,0);
        select_photo_bg->txt_align(LV_TEXT_ALIGN_CENTER);
        select_photo_bg->set_selected(5);
        select_photo_bg->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        select_photo_bg->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);

        if(access(TEMP_PATH,F_OK)==0)
        {
            renamebottomopt->select_photo_bg->add_option("temp.png",6);
        }
    }
    if(select_rgb_bg == NULL)
    {
        /*
        select_rgb_bg =new LvcppDropdown(mparent);
        select_rgb_bg->align_to(color_tip->myobj,LV_ALIGN_RIGHT_MID,-20,-40);
        select_rgb_bg->set_size(120,55);
        select_rgb_bg->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(select_rgb_bg->get_list(),myfont->font(),0);
        select_rgb_bg->set_options("红色\n白色\n蓝色\n绿色\n黄色\n紫红\n粉色\n无");
        select_rgb_bg->set_dir(LV_DIR_BOTTOM);
        select_rgb_bg->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        select_rgb_bg->set_selected(0);
        select_rgb_bg->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        select_rgb_bg->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        */

        select_rgb_bg =new LvcppButton(mparent);
        select_rgb_bg->align_to(color_tip->myobj,LV_ALIGN_RIGHT_MID,-140,-60);
        select_rgb_bg->set_size(100,46);
        select_rgb_bg->set_main_bg_color(lv_color_hex(0xFF0000),LV_OPA_100);
        select_rgb_bg->set_main_border(2,lv_color_black(),LV_OPA_20);
        select_rgb_bg->set_main_radius(0);
        select_rgb_bg->add_txt("");
        select_rgb_bg->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        //select_rgb_bg->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }

}


void RenamebottomScreen::manual_bg_color(void)
{
    //LV_LOG_USER("000000000000");
    ////LV_LOG_USER("bg_color->get_selected() = %d",s_bg_color->get_selected());
    /*
    if(select_rgb_bg->get_selected() == 0)
    {
        renameheadopt->label_bg_change(255,0,0);
    }
    else if(select_rgb_bg->get_selected() == 1)
    {
        renameheadopt->label_bg_change(255,255,255);
    }
    else if(select_rgb_bg->get_selected() == 2)
    {
        renameheadopt->label_bg_change(0,0,255);
    }
    else if(select_rgb_bg->get_selected() == 3)
    {
        renameheadopt->label_bg_change(0,255,0);
    }
    else if(select_rgb_bg->get_selected() == 4)
    {
        renameheadopt->label_bg_change(255,255,0);
    }
    else if(select_rgb_bg->get_selected() == 5)
    {
        renameheadopt->label_bg_change(255,0,255);
    }
    else if(select_rgb_bg->get_selected() == 6)
    {
        renameheadopt->label_bg_change(255,90,90);
    }*/
}

void RenamebottomScreen::set_bg_img(void)
{
    //LV_LOG_USER("########################select_photo_bg->get_selected() = %d###################",select_photo_bg->get_selected());

    char imgPath[FILE_PATH_LONG]={0};
    select_photo_bg->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
    if(strcmp(g_RenameInfo.layout.BgImg,"未使用")!=0 && strlen(g_RenameInfo.layout.BgImg)!=0)
    {
        if(renamebottomopt->select_photo_bg->get_selected() != 5)
        {
            renamebottomopt->select_photo_bg->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
            memset(imgPath,0,FILE_PATH_LONG);
            pthread_mutex_lock(&decodelock);
            if(renamebottomopt->select_photo_bg->get_selected() == 0)
            {
                sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_1_PNG);
            }
            else if(renamebottomopt->select_photo_bg->get_selected() == 1)
            {
                sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_2_PNG);
            }
            else if(renamebottomopt->select_photo_bg->get_selected() == 2)
            {
                sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_3_PNG);
            }
            else if(renamebottomopt->select_photo_bg->get_selected() == 3)
            {
                sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_4_PNG);
            }
            else if(renamebottomopt->select_photo_bg->get_selected() == 4)
            {
                sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_5_PNG);
            }
            else
            {
                sprintf(imgPath,"%s",TEMP_PATH);
            }

            if(idcard!=nullptr)
            {
                free_image(idcard);
                idcard = nullptr;
            }

            idcard = resize_image(imgPath,680,400);

            pthread_mutex_unlock(&decodelock);
            /*
			if(select_rgb_bg->get_selected() != 9)
	        {
	            color_tmp = select_rgb_bg->get_selected();
	        }

			select_rgb_bg->set_selected(10);
            */
            //LV_LOG_USER("!!!!!!!!!!!!!!!!!imgPath =%s",imgPath);
            renameheadopt->mscreen->set_main_bg_img_src(idcard);
            select_rgb_bg->set_main_bg_img_src(DUTY_SIGN_TMP);
            if(idcard_big!=nullptr)
            {
                free_image(idcard_big);
                idcard_big = nullptr;
            }
        }
        else
        {
            select_rgb_bg->set_main_bg_img_src(NULL);
        }
    }
    else
    {
        memset(g_RenameInfo.layout.BgImg,0,sizeof(g_RenameInfo.layout.BgImg));
        renamebottomopt->select_photo_bg->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
        if(select_photo_bg->get_selected() == 5)
        {
            //LV_LOG_USER("//////color_tmp = %d//////",color_tmp);

            //select_rgb_bg->set_selected(color_tmp);
            renameheadopt->mscreen->set_main_bg_img_src(NULL);
            if(idcard!=nullptr)
            {
                free_image(idcard);
                idcard = nullptr;
            }
            if(idcard_big!=nullptr)
            {
                free_image(idcard_big);
                idcard_big = nullptr;
            }
            select_rgb_bg->set_main_bg_img_src(NULL);
        }
    }
    //LV_LOG_USER("//////select_rgb_bg->get_selected = %d//////",select_rgb_bg->get_selected());

/*
    char imgPath[FILE_PATH_LONG]={0};
    select_photo_bg->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
    if(strcmp(g_RenameInfo.layout.BgImg,"未使用")!=0)
    {
        select_photo_bg->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
        //color_tmp = select_rgb_bg->get_selected();
        select_rgb_bg->set_selected(10);


        memset(imgPath,0,FILE_PATH_LONG);
        sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,g_RenameInfo.layout.BgImg);
        pthread_mutex_lock(&decodelock);
        if(idcard!=nullptr)
        {
            free_image(idcard);
            idcard = nullptr;
        }
        idcard = parse_image_from_file(imgPath);
        pthread_mutex_unlock(&decodelock);
        //LV_LOG_USER("!!!!!!!!!!!!!!!!!imgPath =%s",imgPath);
        renameheadopt->mscreen->set_src(idcard);
        renameheadopt->mscreen->set_zoom(256);
    }
    else
    {

        memset(g_RenameInfo.layout.BgImg,0,sizeof(g_RenameInfo.layout.BgImg));
        renameheadopt->mscreen->set_src(NULL);
        renameheadopt->mscreen->set_main_bg_color(lv_color_make(255,255,0),LV_OPA_100);
        //select_photo_bg->get_selected_str(NULL,sizeof(g_RenameInfo.layout.BgImg));
        //select_rgb_bg->set_selected(1);
        if(idcard!=nullptr)
        {
            free_image(idcard);
            idcard = nullptr;
        }
    }
*/
}


void RenamebottomScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenamebottomScreen* opt = (RenamebottomScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==renamebottomopt->select_rgb_bg->myobj)
    {
        /*
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            //renamebottomopt->manual_bg_color();
            //opt->select_photo_bg->set_selected(5);
        }*/
        if(event->code == LV_EVENT_CLICKED)
        {
            bg_color_setopt->mscreen->show(true);
            bg_color_setopt->mscreen->move_foreground();

            color_setopt->mscreen->show(false);
        }
    }
    else if(target==renamebottomopt->select_photo_bg->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            renamebottomopt->set_bg_img();
        }
        else if(event->code == LV_EVENT_CLICKED)
        {
            if(access(TEMP_PATH,F_OK)==0)
            {
                if(renamebottomopt->select_photo_bg->get_option_cnt()<7)
                {
                    renamebottomopt->select_photo_bg->add_option("temp.png",6);
                }
            }
        }
    }

    else if(target == renamebottomopt->change_pos->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            /*
            key_right_tmp = 1;
            //LV_LOG_USER("!!!!!!!!!!!!!!!!!change_pos!!!!!!!!!!!!!!!!!!!");
            tmp_view = 1;
            renameheadopt->mscreen->set_size(1024,600);//0.66
            renameheadopt->mscreen->set_pos(0,0);//0.66
            renameheadopt->mscreen->move_foreground();
            */

            /*
            if(renameopt->re_color == NULL)
            {
                //LV_LOG_USER("new color");
                renameopt->Rename_color_Screen();
                color_setopt->mscreen->show(false);
            }
            else
            {
                //LV_LOG_USER("show color");
                //color_setopt->mscreen->show(true);
                //renamfontsetwinopt->parameter_amplifier();
            }


            if(renameopt->re_fontset == NULL)
            {
                //LV_LOG_USER("new font");

                renameopt->Rename_fontset_Screen();
                //renamfontsetwinopt->parameter_amplifier();
            }
            else
            {
                //LV_LOG_USER("show font");

                renamfontsetwinopt->mscreen->show(true);
                //renamfontsetwinopt->parameter_amplifier();
            }
*/
            /*

            renamfontsetwinopt->parameter_amplifier();
            char x_tmp[10];
            char y_tmp[10];
            char s_tmp[10];
            //LV_LOG_USER("param_state-1 = %d",param_state-1);
            //LV_LOG_USER("big**************   x = %d, y = %d  ************************",g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);
            //LV_LOG_USER("big**************   x = %d, y = %d  ************************",g_RenameInfo.layout.detail[1].ElePointX,g_RenameInfo.layout.detail[1].ElePointY);
            //LV_LOG_USER("big**************   x = %d, y = %d  ************************",g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY);
            snprintf(x_tmp,sizeof(x_tmp),"%d",g_RenameInfo.layout.detail[param_state-1].ElePointX);
            snprintf(y_tmp,sizeof(y_tmp),"%d",g_RenameInfo.layout.detail[param_state-1].ElePointY);
            snprintf(s_tmp,sizeof(s_tmp),"%d",g_RenameInfo.layout.detail[param_state-1].TextSize);
            //LV_LOG_USER("big/////   x = %s, y = %s  //////",x_tmp,y_tmp);
            renamfontsetwinopt->font_x->set_txt(x_tmp);
            renamfontsetwinopt->font_y->set_txt(y_tmp);
            renamfontsetwinopt->font_size->set_txt(s_tmp);


            char imgPath[FILE_PATH_LONG]={0};
            //LV_LOG_USER("renamebottomopt->select_photo_bg->get_selected() = %d",renamebottomopt->select_photo_bg->get_selected());
            if(renamebottomopt->select_photo_bg->get_selected() != 6)
            {
                renamebottomopt->select_photo_bg->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
                memset(imgPath,0,FILE_PATH_LONG);
                pthread_mutex_lock(&decodelock);
                if(renamebottomopt->select_photo_bg->get_selected() == 0)
                {
                    sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,B_1_PNG);

                }
                else if(renamebottomopt->select_photo_bg->get_selected() == 1)
                {
                    sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,B_2_PNG);
                }
                else if(renamebottomopt->select_photo_bg->get_selected() == 2)
                {
                    sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,B_3_PNG);
                }
                else if(renamebottomopt->select_photo_bg->get_selected() == 3)
                {
                    sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,B_4_PNG);
                }
                else if(renamebottomopt->select_photo_bg->get_selected() == 4)
                {
                    sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,B_5_PNG);
                }

                if(idcard_big!=nullptr)
                {
                    free_image(idcard_big);
                    idcard_big = nullptr;
                }

                idcard_big = parse_image_from_file(imgPath);
                pthread_mutex_unlock(&decodelock);
                //LV_LOG_USER("!!!!!!!!!!!!!!!!!imgPath =%s",imgPath);
                renameheadopt->mscreen->set_main_bg_img_src(idcard_big);
                if(idcard!=nullptr)
                {
                    free_image(idcard);
                    idcard = nullptr;
                }

            }*/
        }
    }

}


//右上

RenameinputScreen::RenameinputScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    //mscreen->set_bg_color(lv_color_hex(0xFFFF00),LV_OPA_40);
    mscreen->set_size(590,255);
    mscreen->set_pos(690,0);
    mparent = mscreen->get_screen();
    renameinpuopt = this;
    initial();
}

RenameinputScreen::~RenameinputScreen()
{
    if(usre_company !=NULL)
    {
        delete  usre_company;
        usre_company = NULL;
    }
    if(usre_param !=NULL)
    {
        delete  usre_param;
        usre_param = NULL;
    }
    if(usre_duty !=NULL)
    {
        delete  usre_duty;
        usre_duty = NULL;
    }
    if(rename_line !=NULL)
    {
        delete  rename_line;
        rename_line = NULL;
    }
    if(font_w_tip !=NULL)
    {
        delete  font_w_tip;
        font_w_tip = NULL;
    }
    if(font_W_down !=NULL)
    {
        delete  font_W_down;
        font_W_down = NULL;
    }
    if(font_w !=NULL)
    {
        delete  font_w;
        font_w = NULL;
    }
    if(font_w_up !=NULL)
    {
        delete  font_w_up;
        font_w_up = NULL;
    }
    if(font_h_tip !=NULL)
    {
        delete  font_h_tip;
        font_h_tip = NULL;
    }
    if(font_h_down !=NULL)
    {
        delete  font_h_down;
        font_h_down = NULL;
    }
    if(font_h !=NULL)
    {
        delete  font_h;
        font_h = NULL;
    }
    if(font_h_up !=NULL)
    {
        delete  font_h_up;
        font_h_up = NULL;
    }
    if(font_x_tip !=NULL)
    {
        delete  font_x_tip;
        font_x_tip = NULL;
    }
    if(font_x_down !=NULL)
    {
        delete  font_x_down;
        font_x_down = NULL;
    }
    if(font_x_up !=NULL)
    {
        delete  font_x_up;
        font_x_up = NULL;
    }
    if(font_x !=NULL)
    {
        delete  font_x;
        font_x = NULL;
    }
    if(font_y !=NULL)
    {
        delete  font_y;
        font_y = NULL;
    }
    if(font_y_up !=NULL)
    {
        delete  font_y_up;
        font_y_up = NULL;
    }
    if(font_y_down !=NULL)
    {
        delete  font_y_down;
        font_y_down = NULL;
    }
    if(font_y_tip !=NULL)
    {
        delete  font_y_tip;
        font_y_tip = NULL;
    }
    if(rename_line1 !=NULL)
    {
        delete  rename_line1;
        rename_line1 = NULL;
    }
    if(rename_button !=NULL)
    {
        delete  rename_button;
        rename_button = NULL;
    }
    if(mscreen !=NULL)
    {
        delete  mscreen;
        mscreen = NULL;
    }
}

void RenameinputScreen::font_change_style(int type)
{
    g_RenameInfo.layout.detail[type-1].ElePointX = atoi(renameinpuopt->font_x->get_txt());
    g_RenameInfo.layout.detail[type-1].ElePointY = atoi(renameinpuopt->font_y->get_txt());
    //LV_LOG_USER("g_RenameInfo.layout.detail[type-1].ElePointY = %d",g_RenameInfo.layout.detail[type-1].ElePointY);
    g_RenameInfo.layout.detail[type-1].EleWidth =  atoi(renameinpuopt->font_w->get_txt());
    g_RenameInfo.layout.detail[type-1].EleHeight =  atoi(renameinpuopt->font_h->get_txt());


    //renameopt->font_reset();
    if(type == 1)
    {
        //LV_LOG_USER("X = %d,Y = %d",g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);
        if(key_right_tmp == 1)
        {
            renameheadopt->usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);//*480*600
        }
        else
        {
            renameheadopt->usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX*680/1024,g_RenameInfo.layout.detail[0].ElePointY*400/600);//*480*600
        }
        renameheadopt->usre_param_label->set_size(g_RenameInfo.layout.detail[0].EleWidth*680/1024,g_RenameInfo.layout.detail[0].EleHeight*680/1024);
    }
    else if(type == 2)
    {
        //LV_LOG_USER("X = %d,Y = %d",g_RenameInfo.layout.detail[1].ElePointX,g_RenameInfo.layout.detail[1].ElePointY);
        if(key_right_tmp == 1)
        {
            renameheadopt->usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX,g_RenameInfo.layout.detail[1].ElePointY);//*480*600
        }
        else
        {
            renameheadopt->usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX*680/1024,g_RenameInfo.layout.detail[1].ElePointY*400/600);//*480*600
        }
        renameheadopt->usre_company_label->set_size(g_RenameInfo.layout.detail[1].EleWidth*680/1024,g_RenameInfo.layout.detail[1].EleHeight*680/1024);
    }
    else if(type == 3)
    {
        if(key_right_tmp == 1)
        {
            renameheadopt->usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY);//*480*600
        }
        else
        {
            renameheadopt->usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX*680/1024,g_RenameInfo.layout.detail[2].ElePointY*400/600);//*480*600
        }
        renameheadopt->usre_duty_label->set_size(g_RenameInfo.layout.detail[2].EleWidth*680/1024,g_RenameInfo.layout.detail[2].EleHeight*680/1024);
    }
}


void RenameinputScreen::initial()
{
    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }
    //第一排
    if(usre_company == nullptr)
    {
        usre_company = new LvcppButton(mparent);
        usre_company->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        usre_company->set_pos(12,25);
        usre_company->set_size(100,46);
        usre_company->add_txt("单位");
        usre_company->txt_center();
        usre_company->set_main_radius(10);
        usre_company->txt_color(lv_color_black());
        usre_company->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        usre_company->set_style_text_font(myfont->font(),0);
        usre_company->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        usre_company->add_event_cb(textarea_event_hander,LV_EVENT_DOUBLE_CLICKED,this);
    }
    if(usre_param == nullptr)
    {
        usre_param = new LvcppButton(mparent);
        usre_param->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        usre_param->align_to(usre_company->myobj,LV_ALIGN_RIGHT_MID,20,-18);
        usre_param->set_size(100,46);
        usre_param->add_txt("姓名");
        usre_param->txt_center();
        usre_param->set_main_radius(10);
        usre_param->txt_color(lv_color_black());
        usre_param->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        usre_param->set_style_text_font(myfont->font(),0);
        usre_param->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(usre_duty == nullptr)
    {
        usre_duty = new LvcppButton(mparent);
        usre_duty->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        usre_duty->align_to(usre_param->myobj,LV_ALIGN_RIGHT_MID,20,-18);
        usre_duty->set_size(100,46);
        usre_duty->add_txt("职务");
        usre_duty->txt_center();
        usre_duty->set_main_radius(10);
        usre_duty->txt_color(lv_color_black());
        usre_duty->set_style_text_font(myfont->font(),0);
        usre_duty->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
        //usre_duty->set_main_bg_img_src(DUTY_SIGN_TMP);
        usre_duty->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(rename_line == NULL)
    {
        rename_line = new LvcppLabel(mparent);
        rename_line->set_txt("");
        rename_line->set_pos(15,146);
        rename_line->set_size(310,2);
        rename_line->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
    }
    if(rename_line1 == NULL)
    {
        rename_line1 = new LvcppLabel(mparent);
        rename_line1->set_txt("");
        rename_line1->set_pos(15,250);
        rename_line1->set_size(310,2);
        rename_line1->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
    }
    if(rename_button == nullptr)
    {
        rename_button = new LvcppButton(mparent);
        rename_button->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        rename_button->set_pos(15,105);
        rename_button->set_size(310,35);
        rename_button->add_txt("职务");
        rename_button->txt_center();
        rename_button->set_main_radius(10);
        rename_button->txt_color(lv_color_black());
        rename_button->set_style_text_font(myfont->font(),0);
        rename_button->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_0);
        rename_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    //第二排
    if(font_w_tip == NULL)
    {
        font_w_tip = new LvcppLabel(mparent);
        font_w_tip->set_txt("宽");
        font_w_tip->set_pos(15,167);
        font_w_tip->set_size(20,25);
        font_w_tip->set_style_text_font(myfont->font(),0);
        font_w_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_W_down == nullptr)
    {
        font_W_down = new LvcppButton(mparent);
        font_W_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_W_down->align_to(font_w_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_W_down->set_size(26,35);
        font_W_down->add_txt("-");
        font_W_down->txt_center();
        font_W_down->txt_color(lv_color_black());
        font_W_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_W_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_W_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_W_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_w == NULL)
    {
        font_w = new LvcppLabel(mparent);
        font_w->set_txt("1024");
        font_w->align_to(font_W_down->myobj,LV_ALIGN_RIGHT_MID,59,-4);
        font_w->set_size(70,35);
        font_w->set_style_text_font(myfont->font(),0);
        font_w->txt_align(LV_TEXT_ALIGN_CENTER);
        font_w->txt_color(lv_color_white(),0);
        font_w->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_w_up == NULL)
    {
        font_w_up = new LvcppButton(mparent);
        font_w_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_w_up->align_to(font_w->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_w_up->set_size(26,35);
        font_w_up->add_txt("+");
        font_w_up->txt_center();
        font_w_up->txt_color(lv_color_black());
        font_w_up->set_style_text_font(myfont->font(),0);
        font_w_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_w_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_w_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_w_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_h_tip == NULL)
    {
        font_h_tip = new LvcppLabel(mparent);
        font_h_tip->set_txt("高");
        font_h_tip->set_pos(175,167);
        font_h_tip->set_size(20,25);
        font_h_tip->set_style_text_font(myfont->font(),0);
        font_h_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_h_down == NULL)
    {
        font_h_down = new LvcppButton(mparent);
        font_h_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_h_down->align_to(font_h_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_h_down->set_size(26,35);
        font_h_down->add_txt("-");
        font_h_down->txt_center();
        font_h_down->txt_color(lv_color_black());
        font_h_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_h_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_h_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_h_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_h == NULL)
    {
        font_h = new LvcppLabel(mparent);
        font_h->set_txt("150");
        font_h->align_to(font_h_down->myobj,LV_ALIGN_RIGHT_MID,44,-4);
        font_h->set_size(70,35);
        font_h->set_style_text_font(myfont->font(),0);
        font_h->txt_align(LV_TEXT_ALIGN_CENTER);
        font_h->txt_color(lv_color_white(),0);
        font_h->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_h_up == NULL)
    {
        font_h_up = new LvcppButton(mparent);
        font_h_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_h_up->align_to(font_h->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_h_up->set_size(26,35);
        font_h_up->add_txt("+");
        font_h_up->txt_center();
        font_h_up->txt_color(lv_color_black());
        font_h_up->set_style_text_font(myfont->font(),0);
        font_h_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_h_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_h_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_h_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_x_tip == NULL)
    {
        font_x_tip = new LvcppLabel(mparent);
        font_x_tip->set_txt("X");
        font_x_tip->set_pos(15,213);
        font_x_tip->set_size(20,25);
        font_x_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_x_tip->set_style_text_font(myfont->font(),0);
        font_x_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_x_down == NULL)
    {
        font_x_down = new LvcppButton(mparent);
        font_x_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_x_down->align_to(font_x_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_x_down->set_size(26,35);
        font_x_down->add_txt("-");
        font_x_down->txt_center();
        font_x_down->txt_color(lv_color_black());
        font_x_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_x_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_x_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_x_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_x == NULL)
    {
        font_x = new LvcppLabel(mparent);
        font_x->set_txt("0");
        font_x->align_to(font_x_down->myobj,LV_ALIGN_RIGHT_MID,20,-4);
        font_x->set_size(70,35);
        font_x->set_style_text_font(myfont->font(),0);
        font_x->txt_align(LV_TEXT_ALIGN_CENTER);
        font_x->txt_color(lv_color_white(),0);
        font_x->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_x_up == NULL)
    {
        font_x_up = new LvcppButton(mparent);
        font_x_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_x_up->align_to(font_x->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_x_up->set_size(26,35);
        font_x_up->add_txt("+");
        font_x_up->txt_center();
        font_x_up->txt_color(lv_color_black());
        font_x_up->set_style_text_font(myfont->font(),0);
        font_x_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_x_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_x_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_x_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_y_tip == NULL)
    {
        font_y_tip = new LvcppLabel(mparent);
        font_y_tip->set_txt("Y");
        font_y_tip->set_pos(175,213);
        font_y_tip->set_size(20,25);
        font_y_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_y_tip->set_style_text_font(myfont->font(),0);
        font_y_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_y_down == NULL)
    {
        font_y_down = new LvcppButton(mparent);
        font_y_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_y_down->align_to(font_y_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_y_down->set_size(26,35);
        font_y_down->add_txt("-");
        font_y_down->txt_center();
        font_y_down->txt_color(lv_color_black());
        font_y_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_y_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_y_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_y_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_y == NULL)
    {
        font_y = new LvcppLabel(mparent);
        font_y->set_txt("500");
        font_y->align_to(font_y_down->myobj,LV_ALIGN_RIGHT_MID,50,-4);
        font_y->set_size(70,35);
        font_y->set_style_text_font(myfont->font(),0);
        font_y->txt_align(LV_TEXT_ALIGN_CENTER);
        font_y->txt_color(lv_color_white(),0);
        font_y->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_y_up == NULL)
    {
        font_y_up = new LvcppButton(mparent);
        font_y_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_y_up->align_to(font_y->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_y_up->set_size(26,35);
        font_y_up->add_txt("+");
        font_y_up->txt_center();
        font_y_up->txt_color(lv_color_black());
        font_y_up->set_style_text_font(myfont->font(),0);
        font_y_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_y_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_y_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_y_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
}
void RenameinputScreen::show_input_param(int state)
{
    //renameopt->font_reset();
    if(state == 1)
    {
        //LV_LOG_USER("g_RenameInfo.username =%s",g_RenameInfo.username);
        //LV_LOG_USER("!!!!!!!!!!!!!state = 1");
        rename_button->add_txt(g_RenameInfo.username);
        renameheadopt->usre_param_label->set_txt(g_RenameInfo.username);
    }
    else if(state == 2)
    {
        //LV_LOG_USER("g_RenameInfo.company =%s",g_RenameInfo.company);
        //LV_LOG_USER("!!!!!!!!!!!!!state = 2");
        rename_button->add_txt(g_RenameInfo.company);
        renameheadopt->usre_company_label->set_txt(g_RenameInfo.company);
    }
    else if(state == 3)
    {
        //LV_LOG_USER("g_RenameInfo.duty =%s",g_RenameInfo.duty);
        //LV_LOG_USER("!!!!!!!!!!!!!state = 3");
        rename_button->add_txt(g_RenameInfo.duty);
        renameheadopt->usre_duty_label->set_txt(g_RenameInfo.duty);
    }
    clean_flag_dropdwon();
}
void RenameinputScreen::update_flag_dropdwon(void)
{
    //LV_LOG_USER("update_flag_dropdwon");
    renameeffectopt->change_refont_style->clicked_enable(false);
    renameeffectopt->change_font_alignment->clicked_enable(false);
    renameeffectopt->change_refont_form->clicked_enable(false);
    renameeffectopt->change_font_color->clicked_enable(false);
    //renamebottomopt->select_rgb_bg->clicked_enable(false);

    if(renameopt->re_fontset != NULL)
    {
        renamfontsetwinopt->change_refont_style->clicked_enable(false);
        renamfontsetwinopt->change_font_alignment->clicked_enable(false);
        renamfontsetwinopt->change_refont_form->clicked_enable(false);
        renamfontsetwinopt->change_refont_style->clicked_enable(false);
    }
}
void RenameinputScreen::clean_flag_dropdwon(void)
{
    //LV_LOG_USER("param_state_hide = %d,company_state_hide = %d,duty_state_hide = %d",param_state_hide,company_state_hide,duty_state_hide);
    //LV_LOG_USER("param_state = %d",param_state);
    if(param_state_hide == 1 && param_state == 1)
    {
        renameeffectopt->change_refont_style->clicked_enable(true);
        renameeffectopt->change_font_alignment->clicked_enable(true);
        renameeffectopt->change_refont_form->clicked_enable(true);
        renameeffectopt->change_font_color->clicked_enable(true);
        //renamebottomopt->select_rgb_bg->clicked_enable(true);
        //renamebottomopt->select_photo_bg->clicked_enable(true);
        if(renameopt->re_fontset != NULL)
        {
            renamfontsetwinopt->change_refont_style->clicked_enable(true);
            renamfontsetwinopt->change_font_alignment->clicked_enable(true);
            renamfontsetwinopt->change_refont_form->clicked_enable(true);
            renamfontsetwinopt->change_refont_style->clicked_enable(true);
        }

        renameinpuopt->rename_button->clicked_enable(true);
        renameinpuopt->font_w_up->clicked_enable(true);
        renameinpuopt->font_W_down->clicked_enable(true);
        renameinpuopt->font_x_up->clicked_enable(true);
        renameinpuopt->font_x_down->clicked_enable(true);
        renameinpuopt->font_y_up->clicked_enable(true);
        renameinpuopt->font_y_down->clicked_enable(true);
        renameinpuopt->font_h_up->clicked_enable(true);
        renameinpuopt->font_h_down->clicked_enable(true);
        renameeffectopt->font_size_up->clicked_enable(true);
        renameeffectopt->font_size_down->clicked_enable(true);
        renameeffectopt->font_between_up->clicked_enable(true);
        renameeffectopt->font_between_down->clicked_enable(true);

    }
    else if(company_state_hide == 1 && param_state == 2)
    {
        renameeffectopt->change_refont_style->clicked_enable(true);
        renameeffectopt->change_font_alignment->clicked_enable(true);
        renameeffectopt->change_refont_form->clicked_enable(true);
        renameeffectopt->change_font_color->clicked_enable(true);
        //renamebottomopt->select_rgb_bg->clicked_enable(true);
        //renamebottomopt->select_photo_bg->clicked_enable(true);
        if(renameopt->re_fontset != NULL)
        {
            renamfontsetwinopt->change_refont_style->clicked_enable(true);
            renamfontsetwinopt->change_font_alignment->clicked_enable(true);
            renamfontsetwinopt->change_refont_form->clicked_enable(true);
            renamfontsetwinopt->change_refont_style->clicked_enable(true);
        }

        renameinpuopt->rename_button->clicked_enable(true);
        renameinpuopt->font_w_up->clicked_enable(true);
        renameinpuopt->font_W_down->clicked_enable(true);
        renameinpuopt->font_x_up->clicked_enable(true);
        renameinpuopt->font_x_down->clicked_enable(true);
        renameinpuopt->font_y_up->clicked_enable(true);
        renameinpuopt->font_y_down->clicked_enable(true);
        renameinpuopt->font_h_up->clicked_enable(true);
        renameinpuopt->font_h_down->clicked_enable(true);
        renameeffectopt->font_size_up->clicked_enable(true);
        renameeffectopt->font_size_down->clicked_enable(true);
        renameeffectopt->font_between_up->clicked_enable(true);
        renameeffectopt->font_between_down->clicked_enable(true);
    }
    else if(duty_state_hide == 1 && param_state == 3)
    {
        renameeffectopt->change_font_alignment->clicked_enable(true);
        renameeffectopt->change_refont_form->clicked_enable(true);
        renameeffectopt->change_refont_style->clicked_enable(true);
        renameeffectopt->change_font_color->clicked_enable(true);
        //renamebottomopt->select_rgb_bg->clicked_enable(true);
        //renamebottomopt->select_photo_bg->clicked_enable(true);
        if(renameopt->re_fontset != NULL)
        {
            renamfontsetwinopt->change_refont_style->clicked_enable(true);
            renamfontsetwinopt->change_font_alignment->clicked_enable(true);
            renamfontsetwinopt->change_refont_form->clicked_enable(true);
            renamfontsetwinopt->change_refont_style->clicked_enable(true);
        }

        renameinpuopt->rename_button->clicked_enable(true);
        renameinpuopt->font_w_up->clicked_enable(true);
        renameinpuopt->font_W_down->clicked_enable(true);
        renameinpuopt->font_x_up->clicked_enable(true);
        renameinpuopt->font_x_down->clicked_enable(true);
        renameinpuopt->font_y_up->clicked_enable(true);
        renameinpuopt->font_y_down->clicked_enable(true);
        renameinpuopt->font_h_up->clicked_enable(true);
        renameinpuopt->font_h_down->clicked_enable(true);
        renameeffectopt->font_size_up->clicked_enable(true);
        renameeffectopt->font_size_down->clicked_enable(true);
        renameeffectopt->font_between_up->clicked_enable(true);
        renameeffectopt->font_between_down->clicked_enable(true);
    }
    else
    {
        //renamebottomopt->select_photo_bg->clicked_enable(false);
        renameeffectopt->change_font_alignment->clicked_enable(false);
        renameeffectopt->change_refont_form->clicked_enable(false);
        renameeffectopt->change_refont_style->clicked_enable(false);
        renameeffectopt->change_font_color->clicked_enable(false);
        //renamebottomopt->select_rgb_bg->clicked_enable(false);

        if(renameopt->re_fontset != NULL)
        {
            renamfontsetwinopt->change_refont_style->clicked_enable(false);
            renamfontsetwinopt->change_font_alignment->clicked_enable(false);
            renamfontsetwinopt->change_refont_form->clicked_enable(false);
            renamfontsetwinopt->change_refont_style->clicked_enable(false);
        }

        renameinpuopt->rename_button->clicked_enable(false);
        renameinpuopt->font_w_up->clicked_enable(false);
        renameinpuopt->font_W_down->clicked_enable(false);
        renameinpuopt->font_x_up->clicked_enable(false);
        renameinpuopt->font_x_down->clicked_enable(false);
        renameinpuopt->font_y_up->clicked_enable(false);
        renameinpuopt->font_y_down->clicked_enable(false);
        renameinpuopt->font_h_up->clicked_enable(false);
        renameinpuopt->font_h_down->clicked_enable(false);
        renameeffectopt->font_size_up->clicked_enable(false);
        renameeffectopt->font_size_down->clicked_enable(false);
        renameeffectopt->font_between_up->clicked_enable(false);
        renameeffectopt->font_between_down->clicked_enable(false);
    }
}

void RenameinputScreen::input_pos_update(void)
{
    char x_tmp[10];
    char y_tmp[10];

    //renameopt->font_reset();
    sprintf(x_tmp,"%d",g_RenameInfo.layout.detail[param_state-1].ElePointX*680/1024);
    sprintf(y_tmp,"%d",g_RenameInfo.layout.detail[param_state-1].ElePointY*400/600);
    renameinpuopt->font_x->set_txt(x_tmp);
    renameinpuopt->font_y->set_txt(y_tmp);
    if(renameopt->re_fontset != NULL)
    {
        renamfontsetwinopt->font_x->set_txt(x_tmp);
        renamfontsetwinopt->font_y->set_txt(y_tmp);
    }
}

void RenameinputScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenameinputScreen* opt = (RenameinputScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target == renameinpuopt->usre_param->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            renameinpuopt->input_pos_update();
            //renameinpuopt->update_flag_dropdwon();

            //LV_LOG_USER("param_state_hide == %d",param_state_hide);
            if(param_state_hide == 1)
            {
               param_state_hide = 0;
               renameinpuopt->usre_param->set_main_bg_img_src(NULL);
               renameheadopt->usre_param_label->show(true);
               renameinpuopt->clean_flag_dropdwon();
            }
            else if(param_state == 1 && param_state_hide == 0)
            {
                param_state_hide = 1;
                renameheadopt->usre_param_label->show(false);
                renameinpuopt->usre_param->set_main_bg_img_src(DUTY_SIGN_TMP);
                renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
                //LV_LOG_USER("param_state_hide == %d",param_state_hide);
                renameinpuopt->clean_flag_dropdwon();
            }
            if(param_state_hide == 0)
            {
                renameinpuopt->update_flag_dropdwon();
                renameinpuopt->usre_param->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
                renameinpuopt->usre_company->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
                renameinpuopt->usre_duty->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
                param_state = 1;
                renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_100);
                renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);
                renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);
                renameinpuopt->show_input_param(param_state);
                renameheadopt->param_change(param_state);
                color_setopt->get_rgb_vlaue(param_state);
            }
        }
    }
    else if(target == renameinpuopt->usre_company->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            renameinpuopt->input_pos_update();

           // renameinpuopt->update_flag_dropdwon();

            if(company_state_hide == 1)
            {

                company_state_hide = 0;
                renameinpuopt->usre_company->set_main_bg_img_src(NULL);
                renameheadopt->usre_company_label->show(true);
                renameinpuopt->clean_flag_dropdwon();
            }
            else if(param_state == 2 && company_state_hide == 0)
            {
                company_state_hide = 1;
                renameheadopt->usre_company_label->show(false);
                renameinpuopt->usre_company->set_main_bg_img_src(DUTY_SIGN_TMP);
                renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);
                renameinpuopt->clean_flag_dropdwon();
            }
            if(company_state_hide == 0)
            {
                renameinpuopt->usre_param->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
                renameinpuopt->usre_company->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
                renameinpuopt->usre_duty->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
                param_state = 2;
                renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_100);
                renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
                renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);
                renameinpuopt->show_input_param(param_state);
                renameheadopt->param_change(param_state);
                color_setopt->get_rgb_vlaue(param_state);
                renameinpuopt->update_flag_dropdwon();
            }

        }
    }
    else if(target == renameinpuopt->usre_duty->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            renameinpuopt->input_pos_update();
            //renameinpuopt->update_flag_dropdwon();
            if(duty_state_hide == 1)
            {
                duty_state_hide = 0;
                renameinpuopt->usre_duty->set_main_bg_img_src(NULL);
                renameheadopt->usre_duty_label->show(true);
                renameinpuopt->clean_flag_dropdwon();
            }
            else if(param_state == 3 && duty_state_hide == 0)
            {
                duty_state_hide = 1;
                renameheadopt->usre_duty_label->show(false);
                renameinpuopt->usre_duty->set_main_bg_img_src(DUTY_SIGN_TMP);
                renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);
                renameinpuopt->clean_flag_dropdwon();
            }
            if(duty_state_hide == 0)
            {

                renameinpuopt->usre_param->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);

                renameinpuopt->usre_company->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);

                renameinpuopt->usre_duty->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);

                param_state = 3;
                renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_100);

                renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);

                renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);

                renameinpuopt->show_input_param(param_state);
                renameheadopt->param_change(param_state);
                color_setopt->get_rgb_vlaue(param_state);
                renameinpuopt->update_flag_dropdwon();
            }
        }
    }
    //font size set
    else if(target == opt->font_W_down->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameinpuopt->font_w->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);

                renameinpuopt->font_w->set_txt(rgb_input_num);
                renameinpuopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameinpuopt->font_w->set_txt(rgb_input_num);
                    renameinpuopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
                renameeffectopt->change_font_size_and_between_auto(param_state,3);
            }
    }

    else if(target == renameinpuopt->rename_button->myobj)
    {
            if(renameheadopt->input_kb == nullptr)
            {
                renameheadopt->kb_create();
            }
            //LV_LOG_USER("usre_name");
            renameheadopt->input_kb->initial(3);
            if(param_state == 1)
            {
                renameheadopt->input_kb->input_box->set_text(renameheadopt->usre_param_label->get_txt());
            }
            else if(param_state == 2)
            {
                renameheadopt->input_kb->input_box->set_text(renameheadopt->usre_company_label->get_txt());

            }
            else if(param_state == 3)
            {
                renameheadopt->input_kb->input_box->set_text(renameheadopt->usre_duty_label->get_txt());

            }
            renameheadopt->input_kb->input_box->set_cursor_pos(renameheadopt->input_kb->input_box->get_cursor_pos());
    }

    else if(target == renameinpuopt->font_h_up->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameinpuopt->font_h->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 600)
                {
                    rgb_num = 600;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameinpuopt->font_h->set_txt(rgb_input_num);
                renameinpuopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 600)
                    {
                        rgb_num = 600;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameinpuopt->font_h->set_txt(rgb_input_num);
                    renameinpuopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;

            }
    }

    //font_x
    else if(target == renameinpuopt->font_x_down->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameinpuopt->font_x->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
               // sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameinpuopt->font_x->set_txt(rgb_input_num);
                renameinpuopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameinpuopt->font_x->set_txt(rgb_input_num);
                    renameinpuopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
            }
    }

    else if(target == renameinpuopt->font_x_up->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameinpuopt->font_x->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 1024)
                {
                    rgb_num = 1024;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);

                sprintf(rgb_input_num,"%d",rgb_num);
                renameinpuopt->font_x->set_txt(rgb_input_num);
                renameinpuopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 1024)
                    {
                        rgb_num = 1024;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameinpuopt->font_x->set_txt(rgb_input_num);
                    renameinpuopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
            }
    }

    //font_y
    else if(target == renameinpuopt->font_y_down->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameinpuopt->font_y->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameinpuopt->font_y->set_txt(rgb_input_num);
                renameinpuopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameinpuopt->font_y->set_txt(rgb_input_num);
                    renameinpuopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;

            }
    }

    else if(target == renameinpuopt->font_y_up->myobj)
    {
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameinpuopt->font_y->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 600)
                {
                    rgb_num = 600;
                }
               // sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameinpuopt->font_y->set_txt(rgb_input_num);
                 renameinpuopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 600)
                    {
                        rgb_num = 600;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameinpuopt->font_y->set_txt(rgb_input_num);
                    renameinpuopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;

            }
           }
    }
    //font_h
    else if(target == renameinpuopt->font_h_down->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameinpuopt->font_h->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameinpuopt->font_h->set_txt(rgb_input_num);
                renameinpuopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameinpuopt->font_h->set_txt(rgb_input_num);
                    renameinpuopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;

            }


    }

    else if(target == renameinpuopt->font_w_up->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameinpuopt->font_w->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 1024)
                {
                    rgb_num = 1024;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameinpuopt->font_w->set_txt(rgb_input_num);
                renameinpuopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 1024)
                    {
                        rgb_num = 1024;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameinpuopt->font_w->set_txt(rgb_input_num);
                    renameinpuopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
                 renameeffectopt->change_font_size_and_between_auto(param_state,3);
            }
        }

}


//右下

RenameeffectScreen::RenameeffectScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    //mscreen->set_bg_color(lv_color_hex(0xFF00FF),LV_OPA_40);
    mscreen->set_size(590,345);
    mscreen->set_pos(690,255);
    mparent = mscreen->get_screen();
    renameeffectopt = this;
    initial();

}

RenameeffectScreen::~RenameeffectScreen()
{

    if(change_font_alignment !=NULL)
    {
        delete  change_font_alignment;
        change_font_alignment = NULL;
    }
    if(change_refont_style !=NULL)
    {
        delete  change_refont_style;
        change_refont_style = NULL;
    }
    if(change_refont_form !=NULL)
    {
        delete  change_refont_form;
        change_refont_form = NULL;
    }
    if(change_font_color !=NULL)
    {
        delete  change_font_color;
        change_font_color = NULL;
    }
    if(font_size !=NULL)
    {
        delete  font_size;
        font_size = NULL;
    }
    if(font_between !=NULL)
    {
        delete  font_between;
        font_between = NULL;
    }
    if(font_effect_tip !=NULL)
    {
        delete  font_effect_tip;
        font_effect_tip = NULL;
    }
    if(border_line !=NULL)
    {
        delete  border_line;
        border_line = NULL;
    }
    if(font_size_up !=NULL)
    {
        delete  font_size_up;
        font_size_up = NULL;
    }
    if(font_size_down !=NULL)
    {
        delete  font_size_down;
        font_size_down = NULL;
    }
    if(font_size_tip !=NULL)
    {
        delete  font_size_tip;
        font_size_tip = NULL;
    }
    if(font_between_up !=NULL)
    {
        delete  font_between_up;
        font_between_up = NULL;
    }

    if(font_between_down !=NULL)
    {
        delete  font_between_down;
        font_between_down = NULL;
    }
    if(font_between_tip !=NULL)
    {
        delete  font_between_tip;
        font_between_tip = NULL;
    }
    if(font_between_tip !=NULL)
    {
        delete  font_between_tip;
        font_between_tip = NULL;
    }

    if(del_button !=NULL)
    {
        delete  del_button;
        del_button = NULL;
    }
    if(font_between_tip !=NULL)
    {
        delete  font_between_tip;
        font_between_tip = NULL;
    }
    if(back_button !=NULL)
    {
        delete  back_button;
        back_button = NULL;
    }
    if(mscreen !=NULL)
    {
        delete  mscreen;
        mscreen = NULL;
    }
}

void RenameeffectScreen::initial()
{
    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }

    if(font_effect_tip == NULL)
    {
        font_effect_tip = new LvcppLabel(mparent);
        font_effect_tip->set_txt("文字效果");
        font_effect_tip->set_pos(15,10);
        font_effect_tip->set_size(130,30);
        font_effect_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_effect_tip->set_style_text_font(myfont->font(),0);
        font_effect_tip->txt_font_size(30,0);
        font_effect_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }

    if(change_refont_style == nullptr)
    {
        change_refont_style =new LvcppDropdown(mparent);
        change_refont_style->set_pos(15,55);
        change_refont_style->set_size(160,50);
        change_refont_style->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(change_refont_style->get_list(),myfont->font(),0);
        lv_obj_set_scrollbar_mode(change_refont_style->get_list(),LV_SCROLLBAR_MODE_OFF);
        change_refont_style->set_options("黑体\n楷体\n魏体\n宋体\n隶书\n标宋\n中宋\n等宽\n微软雅黑");
        change_refont_style->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_0);
        change_refont_style->set_style_radius(0,0);
        change_refont_style->set_main_bg_img_src(FONT_JIAO_TMP);
        change_refont_style->txt_align(LV_TEXT_ALIGN_CENTER);
        change_refont_style->set_selected(0);
        change_refont_style->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        change_refont_style->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        if(access(FONT_PATH,F_OK)==0)
        {
            change_refont_style->add_option("用户",9);
        }
    }
    if(change_refont_form == nullptr)
    {
        change_refont_form =new LvcppDropdown(mparent);
        change_refont_form->align_to(change_refont_style->myobj,LV_ALIGN_RIGHT_MID,170,0);
        change_refont_form->set_size(120,50);
        change_refont_form->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(change_refont_form->get_list(),myfont->font(),0);
        lv_obj_set_scrollbar_mode(change_refont_form->get_list(),LV_SCROLLBAR_MODE_OFF);
        change_refont_form->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_0);
        change_refont_form->set_style_radius(0,0);
        change_refont_form->set_main_bg_img_src(TYPE_JIAO_TMP);
        change_refont_form->set_options("正常\n斜体\n粗体");
        change_refont_form->txt_align(LV_TEXT_ALIGN_CENTER);
        change_refont_form->set_selected(0);
        change_refont_form->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }

    if(change_font_alignment == nullptr)
    {
        change_font_alignment =new LvcppDropdown(mparent);
        change_font_alignment->set_pos(15,110);
        change_font_alignment->set_size(160,50);
        change_font_alignment->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(change_font_alignment->get_list(),myfont->font(),0);
        lv_obj_set_scrollbar_mode(change_font_alignment->get_list(),LV_SCROLLBAR_MODE_OFF);
        change_font_alignment->set_options("左对齐\n居中\n右对齐");
        change_font_alignment->txt_align(LV_TEXT_ALIGN_CENTER);
        change_font_alignment->set_style_radius(0,0);
        change_font_alignment->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_0);
        change_font_alignment->set_main_bg_img_src(FONT_JIAO_TMP);
        change_font_alignment->set_selected(0);
        change_font_alignment->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }

    if(change_font_color == nullptr)
    {
        /*
        change_font_color =new LvcppDropdown(mparent);
        change_font_color->align_to(change_font_alignment->myobj,LV_ALIGN_RIGHT_MID,170,0);
        change_font_color->set_size(120,50);
        change_font_color->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(change_font_color->get_list(),myfont->font(),0);
        change_font_color->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        change_font_color->set_options("红色\n黑色\n白色\n蓝色\n绿色\n黄色\n紫红\n灰色\n粉色");
        change_font_color->set_selected(1);
        change_font_color->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        */
        change_font_color =new LvcppButton(mparent);
        change_font_color->align_to(change_font_alignment->myobj,LV_ALIGN_RIGHT_MID,50,-20);
        change_font_color->set_size(120,50);
        change_font_color->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
        change_font_color->set_main_border(2,lv_color_black(),LV_OPA_20);
        change_font_color->set_main_radius(0);
        change_font_color->add_txt("");
        change_font_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

    if(border_line == NULL)
    {
        border_line = new LvcppLabel(mparent);
        border_line->set_txt("");
        border_line->set_pos(15,175);
        border_line->set_size(300,100);
        border_line->set_main_border(2,lv_color_black(),LV_OPA_100);
        border_line->set_main_bg_color(lv_color_hex(0xFFFFFF),LV_OPA_0);
    }

    if(font_size_tip == NULL)
    {
        font_size_tip = new LvcppLabel(mparent);
        font_size_tip->set_txt("大小");
        font_size_tip->set_pos(50,195);
        font_size_tip->set_size(50,25);
        font_size_tip->set_style_text_font(myfont->font(),0);
        font_size_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_size_down == nullptr)
    {
        font_size_down = new LvcppButton(mparent);
        font_size_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_size_down->align_to(font_size_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_size_down->set_size(26,35);
        font_size_down->add_txt("-");
        font_size_down->txt_center();
        font_size_down->txt_color(lv_color_black());
        font_size_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_size_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_size_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_size_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_size == NULL)
    {
        font_size = new LvcppLabel(mparent);
        font_size->set_txt("60");
        font_size->align_to(font_size_down->myobj,LV_ALIGN_RIGHT_MID,35,-4);
        font_size->set_size(70,35);
        font_size->set_style_text_font(myfont->font(),0);
        font_size->txt_align(LV_TEXT_ALIGN_CENTER);
        font_size->txt_color(lv_color_white(),0);
        font_size->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_size_up == nullptr)
    {
        font_size_up = new LvcppButton(mparent);
        font_size_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_size_up->align_to(font_size->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_size_up->set_size(26,35);
        font_size_up->add_txt("+");
        font_size_up->txt_center();
        font_size_up->txt_color(lv_color_black());
        font_size_up->set_style_text_font(myfont->font(),0);
        font_size_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_size_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_size_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_size_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_size_auto == nullptr)
    {
        font_size_auto = new LvcppButton(mparent);
        font_size_auto->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_size_auto->align_to(font_size_up->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
        font_size_auto->set_size(50,80);
        font_size_auto->add_txt("自\n动");
        font_size_auto->txt_color(lv_color_black());
        font_size_auto->txt_center();
        font_size_auto->set_style_text_font(myfont->font(),0);
        font_size_auto->set_main_bg_color(lv_color_hex3(0x87CEFA),LV_OPA_100);
        font_size_auto->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

    if(font_between_tip == NULL)
    {
        font_between_tip = new LvcppLabel(mparent);
        font_between_tip->set_txt("间距");
        font_between_tip->set_pos(50,240);
        font_between_tip->set_size(50,25);
        font_between_tip->set_style_text_font(myfont->font(),0);
        font_between_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_between_down == nullptr)
    {
        font_between_down = new LvcppButton(mparent);
        font_between_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_between_down->align_to(font_between_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_between_down->set_size(26,35);
        font_between_down->add_txt("-");
        font_between_down->txt_center();
        font_between_down->txt_color(lv_color_black());
        font_between_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_between_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_between_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_between_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_between == NULL)
    {
        font_between = new LvcppLabel(mparent);
        font_between->set_txt("0");
        font_between->align_to(font_between_down->myobj,LV_ALIGN_RIGHT_MID,19,-4);
        font_between->set_size(70,35);
        font_between->set_style_text_font(myfont->font(),0);
        font_between->txt_align(LV_TEXT_ALIGN_CENTER);
        font_between->txt_color(lv_color_white(),0);
        font_between->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_between_up == nullptr)
    {
        font_between_up = new LvcppButton(mparent);
        font_between_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_between_up->align_to(font_between->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_between_up->set_size(26,35);
        font_between_up->add_txt("+");
        font_between_up->txt_center();
        font_between_up->txt_color(lv_color_black());
        font_between_up->set_style_text_font(myfont->font(),0);
        font_between_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_between_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_between_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_between_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    /*if(font_between_auto == nullptr)
    {
        font_between_auto = new LvcppCheckBox(mparent);
        font_between_auto->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_between_auto->align_to(font_between_up->myobj,LV_ALIGN_OUT_RIGHT_MID,10,0);
        font_between_auto->set_size(100,100);
        font_between_auto->set_text_static("自动");
        font_between_auto->set_style_text_font(myfont->font(),0);
        font_between_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_0);
        font_between_auto->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }*/
/*
    if(auto_button == nullptr)
    {
        auto_button = new LvcppButton(mparent);
        auto_button->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        auto_button->align_to(font_size_up->myobj,LV_ALIGN_RIGHT_MID,45,-12);
        auto_button->set_size(60,80);
        auto_button->add_txt("自\n动");
        auto_button->txt_center();
        auto_button->set_main_radius(10);
        auto_button->txt_color(lv_color_black());
        auto_button->set_style_text_font(myfont->font(),0);
        auto_button->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        auto_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
*/

    if(ok_button == nullptr)
    {
        ok_button = new LvcppButton(mparent);
        ok_button->set_pos(15,290);
        ok_button->set_size(80,40);
        ok_button->add_txt("确认");
        ok_button->txt_font_size(25,0);
        ok_button->txt_align(LV_ALIGN_CENTER,0,0);
        ok_button->set_style_text_font(myfont->font(),0);
        ok_button->set_main_radius(10);
        ok_button->txt_color(lv_color_black());
        ok_button->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        ok_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(del_button == nullptr)
    {
        del_button = new LvcppButton(mparent);
        del_button->align_to(ok_button->myobj,LV_ALIGN_RIGHT_MID,45,-15);
        del_button->set_size(80,40);
        del_button->add_txt("复位");
        del_button->txt_font_size(25,0);
        del_button->txt_align(LV_ALIGN_CENTER,0,0);
        del_button->set_style_text_font(myfont->font(),0);
        del_button->set_main_radius(10);
        del_button->txt_color(lv_color_black());
        del_button->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        del_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(back_button == nullptr)
    {
        back_button = new LvcppButton(mparent);
        back_button->align_to(del_button->myobj,LV_ALIGN_RIGHT_MID,45,-15);
        back_button->set_size(80,40);
        back_button->add_txt("返回");
        back_button->txt_font_size(25,0);
        back_button->txt_align(LV_ALIGN_CENTER,0,0);
        back_button->set_style_text_font(myfont->font(),0);
        back_button->set_main_radius(10);
        back_button->txt_color(lv_color_black());
        back_button->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        back_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

}






void RenameeffectScreen::change_font_name(int param_state)
{
    ////LV_LOG_USER("tpye = %d",tpye);
    //static lv_ft_info_t ft_font0;
    change_refont_style->get_selected_str(g_RenameInfo.layout.detail[param_state-1].TextFont,sizeof(g_RenameInfo.layout.detail[param_state-1].TextFont));

    if(param_state == 1 )
    {
        //renameopt->font_scan_file_path(g_RenameInfo.layout.detail[param_state-1].TextFont,&ft_font0.name);
        renameopt->font_initial1();
        //LV_LOG_USER("param_state == 1 TextFont = %s,TextSize = %d",g_RenameInfo.layout.detail[param_state-1].TextFont,g_RenameInfo.layout.detail[param_state-1].TextSize);
        renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
    }
    else if(param_state == 2 )
    {
        //renameopt->font_scan_file_path(g_RenameInfo.layout.detail[param_state-1].TextFont,&ft_font0.name);
        renameopt->font_initial2();
        //LV_LOG_USER("param_state ==  2 TextFont = %s,TextSize = %d",g_RenameInfo.layout.detail[param_state-1].TextFont,g_RenameInfo.layout.detail[param_state-1].TextSize);
        renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);
    }
    else if(param_state == 3 )
    {
        //renameopt->font_scan_file_path(g_RenameInfo.layout.detail[param_state-1].TextFont,&ft_font0.name);
        //LV_LOG_USER("g_RenameInfo.layout.detail[param_state-1].TextFont = %s",g_RenameInfo.layout.detail[param_state-1].TextFont);
        renameopt->font_initial3();
        //LV_LOG_USER("param_state ==  3 TextFont = %s,TextSize = %d",g_RenameInfo.layout.detail[param_state-1].TextFont,g_RenameInfo.layout.detail[param_state-1].TextSize);
        renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
    }
    change_down_font_style(param_state,1);
     //LV_LOG_USER("over||| TextFont = %s,TextSize = %d",g_RenameInfo.layout.detail[param_state-1].TextFont,g_RenameInfo.layout.detail[param_state-1].TextSize);

}


void RenameeffectScreen::change_font_size_and_between_auto(int param_state,int type)
{
    int rgb_num;
    char rgb_input_num[10];
    rgb_num = atoi(renameeffectopt->font_size->get_txt());
    if(param_state == 1)
    {
        if(type==0)
        {
            if(auto_size_flag0==1)
            {
                if(strlen(renameinpuopt->rename_button->get_txt())==0)
                {
                    return;
                }
                font_size_auto->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
                renameeffectopt->font_between->set_txt("0");
                renameeffectopt->change_font_style(param_state,2);
                rgb_num = (atoi(renameinpuopt->font_w->get_txt()))*3/(strlen(renameinpuopt->rename_button->get_txt()));
                if(rgb_num>=510)
                {
                    rgb_num = 510;
                }
                else
                {
                    rgb_num -= 1;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
            else
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            }
        }
        else if(type==1)
        {
            auto_size_flag0 = !auto_size_flag0;
            if(auto_size_flag0==1)
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
            }
            else
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            }

            if(auto_size_flag0)
            {
                if(strlen(renameinpuopt->rename_button->get_txt())==0)
                {
                    return;
                }
                renameeffectopt->save_font_size0 = rgb_num;
                renameeffectopt->font_between->set_txt("0");
                renameeffectopt->change_font_style(param_state,2);
                rgb_num = (atoi(renameinpuopt->font_w->get_txt()))*3/(strlen(renameinpuopt->rename_button->get_txt()));
                if(rgb_num>=510)
                {
                    rgb_num = 510;
                }
                else
                {
                    rgb_num -= 1;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
            else
            {
                rgb_num = renameeffectopt->save_font_size0;
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
        }
        else if(type==3)
        {
            auto_size_flag0 = 0;
            font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        }
    }
    else if(param_state == 2)
    {
        if(type==0)
        {
            if(auto_size_flag1==1)
            {
                if(strlen(renameinpuopt->rename_button->get_txt())==0)
                {
                    return;
                }
                font_size_auto->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
                renameeffectopt->font_between->set_txt("0");
                renameeffectopt->change_font_style(param_state,2);
                rgb_num = (atoi(renameinpuopt->font_w->get_txt()))*3/(strlen(renameinpuopt->rename_button->get_txt()));
                if(rgb_num>=510)
                {
                    rgb_num = 510;
                }
                else
                {
                    rgb_num -= 1;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
            else
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            }
        }
        else if(type==1)
        {
            auto_size_flag1 = !auto_size_flag1;
            if(auto_size_flag1==1)
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
            }
            else
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            }
            if(auto_size_flag1)
            {
                if(strlen(renameinpuopt->rename_button->get_txt())==0)
                {
                    return;
                }
                renameeffectopt->save_font_size1 = rgb_num;
                renameeffectopt->font_between->set_txt("0");
                renameeffectopt->change_font_style(param_state,2);
                rgb_num = (atoi(renameinpuopt->font_w->get_txt()))*3/(strlen(renameinpuopt->rename_button->get_txt()));
                if(rgb_num>=510)
                {
                    rgb_num = 510;
                }
                else
                {
                    rgb_num -= 1;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
            else
            {
                rgb_num = renameeffectopt->save_font_size1;
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
        }
        else if(type==3)
        {
            auto_size_flag1 = 0;
            font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        }
    }
    else if(param_state == 3)
    {
        if(type==0)
        {
            if(auto_size_flag2==1)
            {
                if(strlen(renameinpuopt->rename_button->get_txt())==0)
                {
                    return;
                }
                font_size_auto->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
                renameeffectopt->font_between->set_txt("0");
                renameeffectopt->change_font_style(param_state,2);
                rgb_num = (atoi(renameinpuopt->font_w->get_txt()))*3/(strlen(renameinpuopt->rename_button->get_txt()));
                if(rgb_num>=510)
                {
                    rgb_num = 510;
                }
                else
                {
                    rgb_num -= 1;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
            else
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            }
        }
        else if(type==1)
        {
            auto_size_flag2 = !auto_size_flag2;
            if(auto_size_flag2==1)
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);
            }
            else
            {
                font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
            }
            if(auto_size_flag2)
            {
                if(strlen(renameinpuopt->rename_button->get_txt())==0)
                {
                    return;
                }
                renameeffectopt->save_font_size2 = rgb_num;
                renameeffectopt->font_between->set_txt("0");
                renameeffectopt->change_font_style(param_state,2);
                rgb_num = (atoi(renameinpuopt->font_w->get_txt()))*3/(strlen(renameinpuopt->rename_button->get_txt()));
                if(rgb_num>=510)
                {
                    rgb_num = 510;
                }
                else
                {
                    rgb_num -= 1;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
            else
            {
                rgb_num = renameeffectopt->save_font_size2;
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->font_size->invalidate();
                renameeffectopt->change_font_style(param_state,1);
            }
        }
        else if(type==3)
        {
            auto_size_flag2 = 0;
            font_size_auto->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        }
    }
}

void RenameeffectScreen::change_font_style(int param_state,int type)//up
{
    if(param_state == 1)
    {
        if(type == 1)
        {
            g_RenameInfo.layout.detail[0].TextSize = atoi( font_size->get_txt());
            //renameopt->font_initial1();
            renameheadopt->usre_param_label->txt_font_size(g_RenameInfo.layout.detail[0].TextSize*680/1024,0);

            //if(g_RenameInfo.layout.detail[0].TextSize +30 >= g_RenameInfo.layout.detail[0].EleHeight )
            //{
                g_RenameInfo.layout.detail[0].EleHeight = g_RenameInfo.layout.detail[0].TextSize*5/4;
                renameopt->font_initial1();
                char height[10];
                sprintf(height,"%d",g_RenameInfo.layout.detail[0].EleHeight);
                renameinpuopt->font_h->set_txt(height);
                renameinpuopt->font_change_style(param_state);
            //}
            //LV_LOG_USER("g_RenameInfo.layout.detail[0].TextSize =%d",g_RenameInfo.layout.detail[0].TextSize);
            //LV_LOG_USER("g_RenameInfo.layout.detail[0].EleHeight =%d",g_RenameInfo.layout.detail[0].EleHeight);
            renameopt->font_initial1();
            renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
        }
        else if(type == 2)
        {
            g_RenameInfo.layout.detail[0].TextLetterSpace = atoi( font_between->get_txt());
            //renameopt->font_initial1();

            renameheadopt->usre_param_label->set_style_text_letter_space(g_RenameInfo.layout.detail[0].TextLetterSpace*680/1024,0);

        }
        else if(type == 3)
        {

            g_RenameInfo.layout.detail[0].HorizontalAlign = renameeffectopt->change_font_alignment->get_selected()+1;
            renameopt->font_initial1();
            //LV_LOG_USER("g_RenameInfo.layout.detail[0].HorizontalAlign = %d",g_RenameInfo.layout.detail[0].HorizontalAlign);
            renameheadopt->usre_param_label->txt_align(g_RenameInfo.layout.detail[0].HorizontalAlign);

        }
        else if(type == 4)
        {
            g_RenameInfo.layout.detail[0].TextType = change_refont_form->get_selected();
            renameopt->font_initial1();
            //LV_LOG_USER("TextType =%d ,change_refont_form->get_selected() =%d",g_RenameInfo.layout.detail[0].TextType,change_refont_form->get_selected());
            renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
        }
    }
    else if(param_state == 2)
    {
        if(type == 1)
        {
            g_RenameInfo.layout.detail[1].TextSize = atoi( font_size->get_txt());
            //renameopt->font_initial2();

            renameheadopt->usre_company_label->txt_font_size(g_RenameInfo.layout.detail[1].TextSize*680/1024,0);

            //if(g_RenameInfo.layout.detail[1].TextSize +30  >= g_RenameInfo.layout.detail[1].EleHeight)
            //{
                g_RenameInfo.layout.detail[1].EleHeight = g_RenameInfo.layout.detail[1].TextSize*5/4;
                renameopt->font_initial2();
                char height[10];
                sprintf(height,"%d",g_RenameInfo.layout.detail[1].EleHeight);
                renameinpuopt->font_h->set_txt(height);
                renameinpuopt->font_change_style(param_state);
            //}
            renameopt->font_initial2();
            //LV_LOG_USER("g_RenameInfo.layout.detail[1].TextSize =%d",g_RenameInfo.layout.detail[1].TextSize);
            //LV_LOG_USER("g_RenameInfo.layout.detail[1].EleHeight =%d",g_RenameInfo.layout.detail[1].EleHeight);
            renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);
        }
        else if(type == 2)
        {
            g_RenameInfo.layout.detail[1].TextLetterSpace = atoi( font_between->get_txt());


            renameheadopt->usre_company_label->set_style_text_letter_space(g_RenameInfo.layout.detail[1].TextLetterSpace*680/1024,0);

        }
        else if(type == 3)
        {
            g_RenameInfo.layout.detail[1].HorizontalAlign = renameeffectopt->change_font_alignment->get_selected()+1;
            renameopt->font_initial2();
            //LV_LOG_USER("g_RenameInfo.layout.detail[1].HorizontalAlign = %d",g_RenameInfo.layout.detail[1].HorizontalAlign);
            renameheadopt->usre_company_label->txt_align(g_RenameInfo.layout.detail[1].HorizontalAlign);

        }
        else if(type == 4)
        {
            g_RenameInfo.layout.detail[1].TextType = change_refont_form->get_selected();
            renameopt->font_initial2();
            //LV_LOG_USER("TextType =%d ,change_refont_form->get_selected() =%d",g_RenameInfo.layout.detail[1].TextType,change_refont_form->get_selected());
            renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);

        }
    }
    else if(param_state == 3)
    {
        if(type == 1)
        {
            g_RenameInfo.layout.detail[2].TextSize = atoi( font_size->get_txt());
            renameheadopt->usre_duty_label->txt_font_size(g_RenameInfo.layout.detail[2].TextSize*680/1024,0);
            //if(g_RenameInfo.layout.detail[2].TextSize +100  >= g_RenameInfo.layout.detail[2].EleHeight)
            //{

                g_RenameInfo.layout.detail[2].EleHeight = g_RenameInfo.layout.detail[2].TextSize*5/4;
                renameopt->font_initial3();
                char height[10];
                sprintf(height,"%d",g_RenameInfo.layout.detail[2].EleHeight);
                renameinpuopt->font_h->set_txt(height);
                renameinpuopt->font_change_style(param_state);
                //LV_LOG_USER("==========================================");
            //}
            renameopt->font_initial3();
            //LV_LOG_USER("g_RenameInfo.layout.detail[2].TextSize =%d",g_RenameInfo.layout.detail[2].TextSize);
            //LV_LOG_USER("g_RenameInfo.layout.detail[2].EleHeight =%d",g_RenameInfo.layout.detail[2].EleHeight);
            renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
        }
        else if(type == 2)
        {
            g_RenameInfo.layout.detail[2].TextLetterSpace = atoi( font_between->get_txt());

            renameheadopt->usre_duty_label->set_style_text_letter_space(g_RenameInfo.layout.detail[2].TextLetterSpace*680/1024,0);
        }
        else if(type == 3)
        {
            g_RenameInfo.layout.detail[2].HorizontalAlign = renameeffectopt->change_font_alignment->get_selected()+1;
            //LV_LOG_USER("renameeffectopt->change_font_alignment->get_selected()+1 = %d",renameeffectopt->change_font_alignment->get_selected()+1);
            /*
            if(renameopt->myfont2)
            {
                lv_ft_font_destroy(renameopt->myfont2);
                renameopt->myfont2 = nullptr;
            }*/
            renameopt->font_initial3();
            renameheadopt->usre_duty_label->txt_align(g_RenameInfo.layout.detail[2].HorizontalAlign);
        }
        else if(type == 4)
        {
            g_RenameInfo.layout.detail[2].TextType = change_refont_form->get_selected();
            renameopt->font_initial3();
            //LV_LOG_USER("TextType =%d ,change_refont_form->get_selected() =%d",g_RenameInfo.layout.detail[2].TextType,change_refont_form->get_selected());
            renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
        }
    }

}


void RenameeffectScreen::change_down_font_style(int param_state,int type)
{
    if(param_state == 1)
    {
        if(type == 1)
        {
            g_RenameInfo.layout.detail[0].TextSize = atoi( font_size->get_txt());
            g_RenameInfo.layout.detail[0].EleHeight = g_RenameInfo.layout.detail[0].TextSize*5/4;

            char height[10];
            sprintf(height,"%d",g_RenameInfo.layout.detail[0].EleHeight);
            renameinpuopt->font_h->set_txt(height);
            renameinpuopt->font_change_style(param_state);
            renameopt->font_initial1();
            renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
        }
        else if(type == 2)
        {
            g_RenameInfo.layout.detail[0].TextLetterSpace = atoi( font_between->get_txt());
            //renameopt->font_initial1();
            renameheadopt->usre_param_label->set_style_text_letter_space(g_RenameInfo.layout.detail[0].TextLetterSpace*680/1024,0);

        }
        else if(type == 3)
        {

            g_RenameInfo.layout.detail[0].HorizontalAlign = renameeffectopt->change_font_alignment->get_selected()+1;
            renameopt->font_initial1();
            //LV_LOG_USER("g_RenameInfo.layout.detail[0].HorizontalAlign = %d",g_RenameInfo.layout.detail[0].HorizontalAlign);
            renameheadopt->usre_param_label->txt_align(g_RenameInfo.layout.detail[0].HorizontalAlign);

        }
        else if(type == 4)
        {
            g_RenameInfo.layout.detail[0].TextType = change_refont_form->get_selected();
            renameopt->font_initial1();
            //LV_LOG_USER("TextType =%d ,change_refont_form->get_selected() =%d",g_RenameInfo.layout.detail[0].TextType,change_refont_form->get_selected());
            renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);

        }
    }
    else if(param_state == 2)
    {
        if(type == 1)
        {
            g_RenameInfo.layout.detail[1].TextSize = atoi( font_size->get_txt());

            renameheadopt->usre_company_label->txt_font_size(g_RenameInfo.layout.detail[1].TextSize*680/1024,0);
            g_RenameInfo.layout.detail[1].EleHeight = g_RenameInfo.layout.detail[1].TextSize*5/4;

            char height[10];
            sprintf(height,"%d",g_RenameInfo.layout.detail[1].EleHeight);
            renameinpuopt->font_h->set_txt(height);
            renameinpuopt->font_change_style(param_state);

            renameopt->font_initial2();
            renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);
        }
        else if(type == 2)
        {
            g_RenameInfo.layout.detail[1].TextLetterSpace = atoi( font_between->get_txt());
            renameheadopt->usre_company_label->set_style_text_letter_space(g_RenameInfo.layout.detail[1].TextLetterSpace*680/1024,0);

        }
        else if(type == 3)
        {
            g_RenameInfo.layout.detail[1].HorizontalAlign = renameeffectopt->change_font_alignment->get_selected()+1;
            renameopt->font_initial2();
            //LV_LOG_USER("g_RenameInfo.layout.detail[1].HorizontalAlign = %d",g_RenameInfo.layout.detail[1].HorizontalAlign);
            renameheadopt->usre_company_label->txt_align(g_RenameInfo.layout.detail[1].HorizontalAlign);
        }
        else if(type == 4)
        {
            g_RenameInfo.layout.detail[1].TextType = change_refont_form->get_selected();
            renameopt->font_initial2();
            //LV_LOG_USER("TextType =%d ,change_refont_form->get_selected() =%d",g_RenameInfo.layout.detail[1].TextType,change_refont_form->get_selected());
            renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);

        }
    }
    else if(param_state == 3)
    {
        if(type == 1)
        {
            g_RenameInfo.layout.detail[2].TextSize = atoi( font_size->get_txt());

            renameheadopt->usre_duty_label->txt_font_size(g_RenameInfo.layout.detail[2].TextSize*680/1024,0);
            g_RenameInfo.layout.detail[2].EleHeight = g_RenameInfo.layout.detail[2].TextSize*5/4;

            char height[10];
            sprintf(height,"%d",g_RenameInfo.layout.detail[2].EleHeight);
            renameinpuopt->font_h->set_txt(height);
            renameinpuopt->font_change_style(param_state);

            renameopt->font_initial3();
            renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
        }
        else if(type == 2)
        {
            g_RenameInfo.layout.detail[2].TextLetterSpace = atoi( font_between->get_txt());

            renameheadopt->usre_duty_label->set_style_text_letter_space(g_RenameInfo.layout.detail[2].TextLetterSpace*680/1024,0);
        }
        else if(type == 3)
        {
            g_RenameInfo.layout.detail[2].HorizontalAlign = renameeffectopt->change_font_alignment->get_selected()+1;
            renameopt->font_initial3();
            renameheadopt->usre_duty_label->txt_align(g_RenameInfo.layout.detail[2].HorizontalAlign);
        }
        else if(type == 4)
        {
            g_RenameInfo.layout.detail[2].TextType = change_refont_form->get_selected();
            renameopt->font_initial3();
            //LV_LOG_USER("TextType =%d ,change_refont_form->get_selected() =%d",g_RenameInfo.layout.detail[2].TextType,change_refont_form->get_selected());
            renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
        }
    }

}
void RenameeffectScreen::manual_font_color(int param_state)
{
    /*
    if(change_font_color->get_selected() == 1)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(0,0,0),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(0,0,0),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(0,0,0),0);
        }
    }
    else if(change_font_color->get_selected() == 0)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,0,0),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,0,0),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,0,0),0);
        }
    }
    else if(change_font_color->get_selected() == 2)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,255,255),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,255,255),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,255,255),0);
        }
    }
    if(change_font_color->get_selected() == 3)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(0,0,255),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(0,0,255),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(0,0,255),0);
        }
    }
    else if(change_font_color->get_selected() == 4)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(0,255,0),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(0,255,0),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(0,255,0),0);
        }
    }
    else if(change_font_color->get_selected() == 5)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,255,0),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,255,0),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,255,0),0);
        }
    }
    else if(change_font_color->get_selected() == 6)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,0,255),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,0,255),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,0,255),0);
        }
    }
    else if(change_font_color->get_selected() == 7)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(128,128,128),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(128,128,128),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(128,128,128),0);
        }
    }
    else if(change_font_color->get_selected() == 8)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,90,90),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,90,90),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,90,90),0);
        }
    }*/

}

void RenameeffectScreen::hide_screen(void)
{
    if(renameopt->re_head != NULL)
    {
        //renameheadopt->mscreen->show(false);
        delete renameopt->re_head;
        renameopt->re_head =nullptr;
    }
    if(renameopt->re_bottom != NULL)
    {
        //renamebottomopt->mscreen->show(false);
        delete renameopt->re_bottom;
        renameopt->re_bottom =nullptr;
    }
    if(renameopt->re_input != NULL)
    {
        //renameinpuopt->mscreen->show(false);
        delete renameopt->re_input;
        renameopt->re_input =nullptr;
    }
    if(renameopt->re_effect != NULL)
    {
        //renameeffectopt->mscreen->show(false);
        delete renameopt->re_effect;
        renameopt->re_effect =nullptr;
    }
    if(renameopt->re_color != NULL)
    {
        //color_setopt->mscreen->show(false);
        delete renameopt->re_color;
        renameopt->re_color =nullptr;
    }
    if(renameopt->bg_color != NULL)
    {
        //bg_color_setopt->mscreen->show(false);
        delete renameopt->bg_color;
        renameopt->bg_color =nullptr;
    }
    if(renameopt->input_kb != NULL)
    {
        //bg_color_setopt->mscreen->show(false);
        delete renameopt->input_kb;
        renameopt->input_kb =nullptr;
    }

    renameopt->re_callback();
}

void RenameeffectScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenameeffectScreen* opt = (RenameeffectScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==renameeffectopt->change_refont_style->myobj)
    {

            if(event->code == LV_EVENT_VALUE_CHANGED)
            {
                renameeffectopt->change_font_name(param_state);
            }
            else if(event->code == LV_EVENT_CLICKED)
            {
                if(access(FONT_PATH,F_OK)==0)
                {
                    if(renameeffectopt->change_refont_style->get_option_cnt()<10)
                    {
                        renameeffectopt->change_refont_style->add_option("用户",9);
                    }
                }
            }

    }
    //font_size
    else if(target == renameeffectopt->font_size_down->myobj)
    {

            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameeffectopt->font_size->get_txt());/////////
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->change_down_font_style(param_state,1);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameeffectopt->font_size->set_txt(rgb_input_num);
                    renameeffectopt->change_down_font_style(param_state,1);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
                renameeffectopt->change_font_size_and_between_auto(param_state,3);
            }
    }

    else if(target == renameeffectopt->font_size_up->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameeffectopt->font_size->get_txt());////////
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 1024)
                {
                    rgb_num = 1024;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_size->set_txt(rgb_input_num);
                renameeffectopt->change_font_style(param_state,1);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 1024)
                    {
                        rgb_num = 1024;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameeffectopt->font_size->set_txt(rgb_input_num);
                    renameeffectopt->change_font_style(param_state,1);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
                 renameeffectopt->change_font_size_and_between_auto(param_state,3);
            }


    }

    //font_size_auto
    else if(target == renameeffectopt->font_size_auto->myobj)
    {

        if(event->code == LV_EVENT_CLICKED)
        {
            renameeffectopt->change_font_size_and_between_auto(param_state,1);
        }
    }

    //font_between
    else if(target == renameeffectopt->font_between_down->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameeffectopt->font_between->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_between->set_txt(rgb_input_num);
                renameeffectopt->change_font_style(param_state,2);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameeffectopt->font_between->set_txt(rgb_input_num);
                    renameeffectopt->change_font_style(param_state,2);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
            }
    }
    else if(target == renameeffectopt->font_between_up->myobj)
    {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renameeffectopt->font_between->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 1024)
                {
                    rgb_num = 1024;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_between->set_txt(rgb_input_num);
                renameeffectopt->change_font_style(param_state,2);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 1024)
                    {
                        rgb_num = 1024;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameeffectopt->font_between->set_txt(rgb_input_num);
                    renameeffectopt->change_font_style(param_state,2);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
            }

    }
    //font_between_auto
    /*else if(target == renameeffectopt->font_between_auto->myobj)
    {
        int rgb_num;
        char rgb_input_num[10];
        rgb_num = atoi(renameeffectopt->font_between->get_txt());
        if(event->code == LV_EVENT_VALUE_CHANGED )
        {
            if(renameeffectopt->font_size_auto->has_state(LV_STATE_CHECKED))
            {
                rgb_num = 0;
                sprintf(rgb_input_num,"%d",rgb_num);
                renameeffectopt->font_between->set_txt(rgb_input_num);
                renameeffectopt->change_font_style(param_state,2);
            }
            else
            {
                if(renameeffectopt->font_between_auto->has_state(LV_STATE_CHECKED))
                {
                    renameeffectopt->save_between_size = rgb_num;
                    if((int)(atoi(renameeffectopt->font_size->get_txt())*(strlen(renameinpuopt->rename_button->get_txt()))/3)<atoi(renameinpuopt->font_w->get_txt())-5)
                    {
                       rgb_num =  atoi(renameinpuopt->font_w->get_txt())- 5 - atoi(renameeffectopt->font_size->get_txt())*(strlen(renameinpuopt->rename_button->get_txt())/3);
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameeffectopt->font_between->set_txt(rgb_input_num);
                    renameeffectopt->font_between->invalidate();
                    renameeffectopt->change_font_style(param_state,2);
                }
                else
                {
                    rgb_num = renameeffectopt->save_between_size;
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renameeffectopt->font_between->set_txt(rgb_input_num);
                    renameeffectopt->font_between->invalidate();
                    renameeffectopt->change_font_style(param_state,2);
                }
            }
        }
    }*/

    else if(target == renameeffectopt->change_font_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            //renameeffectopt->manual_font_color(param_state);

            if(renameopt->re_color == NULL)
            {
                //LV_LOG_USER("new color");
                renameopt->Rename_color_Screen();
                //color_setopt->mscreen->show(false);
            }
            else
            {
                //LV_LOG_USER("show color");
                color_setopt->mscreen->show(true);
                color_setopt->mscreen->move_foreground();

                bg_color_setopt->mscreen->show(false);
                //renamfontsetwinopt->parameter_amplifier();
            }
        }
    }
    else if(target == renameeffectopt->ok_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->mscreen->show(false);
            bg_color_setopt->mscreen->show(false);
            renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);

            renameheadopt->mscreen->get_scroll_snap_x();

            memset(&g_RenameSaveInfo,0,sizeof(zpc_canvas_param_t));
            memcpy(&g_RenameSaveInfo,&g_RenameInfo,sizeof(zpc_canvas_param_t));

            lv_color_t bgcolor;
            bgcolor = lv_obj_get_style_bg_color(renameheadopt->mscreen->myobj,0);
            memset(g_RenameSaveInfo.layout.BgColor,0,sizeof(g_RenameSaveInfo.layout.BgColor));
            sprintf(g_RenameSaveInfo.layout.BgColor,"%02x%02x%02x",bgcolor.ch.red,bgcolor.ch.green,bgcolor.ch.blue);

            lv_color_t color_user;
            color_user = lv_obj_get_style_text_color(renameheadopt->usre_param_label->myobj,0);
            memset(g_RenameSaveInfo.layout.detail[0].TextColor,0,sizeof(g_RenameSaveInfo.layout.detail[0].TextColor));
            sprintf(g_RenameSaveInfo.layout.detail[0].TextColor,"%02x%02x%02x",color_user.ch.red,color_user.ch.green,color_user.ch.blue);

            lv_color_t color_company;
            color_company = lv_obj_get_style_text_color(renameheadopt->usre_company_label->myobj,0);
            memset(g_RenameSaveInfo.layout.detail[1].TextColor,0,sizeof(g_RenameSaveInfo.layout.detail[1].TextColor));
            sprintf(g_RenameSaveInfo.layout.detail[1].TextColor,"%02x%02x%02x",color_company.ch.red,color_company.ch.green,color_company.ch.blue);

            lv_color_t color_duty;
            color_duty = lv_obj_get_style_text_color(renameheadopt->usre_duty_label->myobj,0);
            memset(g_RenameSaveInfo.layout.detail[2].TextColor,0,sizeof(g_RenameSaveInfo.layout.detail[2].TextColor));
            sprintf(g_RenameSaveInfo.layout.detail[2].TextColor,"%02x%02x%02x",color_duty.ch.red,color_duty.ch.green,color_duty.ch.blue);

            memset(g_RenameSaveInfo.layout.BgImg,0,sizeof(g_RenameSaveInfo.layout.BgImg));
            renamebottomopt->select_photo_bg->get_selected_str(g_RenameSaveInfo.layout.BgImg,sizeof(g_RenameSaveInfo.layout.BgImg));

            lv_img_dsc_t *dsc;
            dsc = lv_snapshot_take(renameheadopt->mscreen->myobj, LV_IMG_CF_TRUE_COLOR_ALPHA);
            //LV_LOG_USER("dsc->header.w = %d,dsc->header.h = %d,,dsc->data_size = %d,",dsc->header.w,dsc->header.h,dsc->data_size);
            uint8_t* BmpData=nullptr;
            BmpData = (uint8_t*)LvcppMemory::mem_alloc(LV_CANVAS_BUF_SIZE_TRUE_COLOR(SCREEN_HOR_SIZE, SCREEN_VER_SIZE));
            renameboxopt->BgraToRgb((uint8_t*)dsc->data,dsc->header.w,dsc->header.h,BmpData);
            if(!lvcpp_bmp::encode(BmpData, dsc->header.w,dsc->header.h, IDCARD_PATH))
            {
                //LV_LOG_USER("bmp save success");
                #if QTSIM_PLATFORM==0
                msg_apps_t msg;
                memset(&msg,0,sizeof(msg_apps_t));
                msg.type = MSG_UPDATE_IDCARD;
                SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
                #endif
            }
            else {
                //LV_LOG_USER("bmp save failed");
            }

            lv_snapshot_free(dsc);
            if(BmpData)
            {
                LvcppMemory::mem_free(BmpData);
                BmpData = nullptr;
            }
        }
    }

    else if(target == renameeffectopt->del_button->myobj)
    {

        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->mscreen->show(false);
            bg_color_setopt->mscreen->show(false);
            renamfontsetwinopt->zp_param_clear();


            //LV_LOG_USER("zp_param_clear over");
        }
    }
    else if(target == renameeffectopt->back_button->myobj)
    {

        if(event->code == LV_EVENT_CLICKED)
        {
            opt->hide_screen();
            //LV_LOG_USER("zp_param_clear over");
        }
    }
    else if(target == renameeffectopt->change_refont_form->myobj)
    {

            if(event->code == LV_EVENT_VALUE_CHANGED)
            {
                //LV_LOG_USER("change_refont_style!!!!!!!!!!!!!!!!!!!!!!!!!!");
                renameeffectopt->change_font_style(param_state,4);
                //LV_LOG_USER("llllllllllllllllllllllllllllllllllllllllll");
            }


    }
    else if(target == renameeffectopt->change_font_alignment->myobj)
    {

            if(event->code == LV_EVENT_VALUE_CHANGED)
            {
                renameeffectopt->change_font_style(param_state,3);
            }

    }



}






//调色板

RenamecolorScreen::RenamecolorScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);//
    mscreen->set_bg_color(lv_color_hex(0xACACAC),LV_OPA_100);
    mscreen->set_size(330,345);
    mscreen->set_pos(690,80);
    mscreen->set_main_radius(10);
    mscreen->set_main_border(2,lv_color_hex(0x0000CC),LV_OPA_100);
    mparent = mscreen->get_screen();
    color_setopt = this;
    initial();
    save_r = atoi(font_R->get_txt());
    save_g = atoi(font_G->get_txt());
    save_b = atoi(font_B->get_txt());
    //lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE );
    mscreen->add_flag(LV_OBJ_FLAG_CLICKABLE);
    mscreen->clear_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    mscreen->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
    mscreen->add_event_cb(textarea_event_hander,LV_EVENT_PRESSED,this);
}

RenamecolorScreen::~RenamecolorScreen()
{
    if(color_tip != NULL)
    {
        delete color_tip;
        color_tip = NULL;
    }
    if(color_line != NULL)
    {
        delete color_line;
        color_line = NULL;
    }
    if(red_color != NULL)
    {
        delete red_color;
        red_color = NULL;
    }
    if(orange_color != NULL)
    {
        delete orange_color;
        orange_color = NULL;
    }
    if(yellow_color != NULL)
    {
        delete yellow_color;
        yellow_color = NULL;
    }
    if(green_color != NULL)
    {
        delete green_color;
        green_color = NULL;
    }
    if(blue_color != NULL)
    {
        delete blue_color;
        blue_color = NULL;
    }
    if(cyan_color != NULL)
    {
        delete cyan_color;
        cyan_color = NULL;
    }
    if(purple_color != NULL)
    {
        delete purple_color;
        purple_color = NULL;
    }
    if(black_color != NULL)
    {
        delete black_color;
        black_color = NULL;
    }
    if(white_color != NULL)
    {
        delete white_color;
        white_color = NULL;
    }
    if(canvas != NULL)
    {
        delete canvas;
        canvas = NULL;
    }
    if(font_R != NULL)
    {
        delete font_R;
        font_R = NULL;
    }
    if(font_R_up != NULL)
    {
        delete font_R_up;
        font_R_up = NULL;
    }
    if(font_R_down != NULL)
    {
        delete font_R_down;
        font_R_down = NULL;
    }
    if(font_R_tip != NULL)
    {
        delete font_R_tip;
        font_R_tip = NULL;
    }
    if(font_G != NULL)
    {
        delete font_G;
        font_G = NULL;
    }
    if(font_G_up != NULL)
    {
        delete font_G_up;
        font_G_up = NULL;
    }
    if(font_G_down != NULL)
    {
        delete font_G_down;
        font_G_down = NULL;
    }
    if(font_G_tip != NULL)
    {
        delete font_G_tip;
        font_G_tip = NULL;
    }
    if(font_B != NULL)
    {
        delete font_B;
        font_B = NULL;
    }
    if(font_B_up != NULL)
    {
        delete font_B_up;
        font_B_up = NULL;
    }
    if(font_B_down != NULL)
    {
        delete font_B_down;
        font_B_down = NULL;
    }
    if(font_B_tip != NULL)
    {
        delete font_B_tip;
        font_B_tip = NULL;
    }
    if(now_color_tip != NULL)
    {
        delete now_color_tip;
        now_color_tip = NULL;
    }
    if(now_color_show != NULL)
    {
        delete now_color_show;
        now_color_show = NULL;
    }
    if(ok_button != NULL)
    {
        delete ok_button;
        ok_button = NULL;
    }
    if(del_button != NULL)
    {
        delete del_button;
        del_button = NULL;
    }
    if(mscreen != NULL)
    {
        delete mscreen;
        mscreen = NULL;
    }
}

lv_color_t* RenamecolorScreen::create_canvas(void)
{
    static lv_color_t buf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(150, 150)];//分配buf存放画板数据
    if(canvas==nullptr)
    {
        canvas =new LvcppCanvas(mparent);
    }
    canvas->set_size(150,150);
    canvas->set_buffer(buf, 150, 150, LV_IMG_CF_TRUE_COLOR);//设置画板空间
    canvas->set_pos(10,86);
    int r,g,b;

    for(int x=0;x<150;x++)
    {
        for(int y=0;y<150;y++)
        {
            r = canvas_r;
            g = x*255/150;
            b = y*255/150;
            if(y%10 == 0 && x%10 == 0)
            {
                //LV_LOG_USER("b = %d",b);
            }
            canvas->set_px_color(x,y,lv_color_make(r,g,b));
        }
    }

    canvas->set_main_border(2,lv_color_black(),LV_OPA_100);
    canvas->add_flag(LV_OBJ_FLAG_CLICKABLE);
    canvas->add_event_cb(textarea_event_hander,LV_EVENT_ALL,this);
    lv_draw_img_dsc_init(&img_draw_dsc);
    return buf;
}

void RenamecolorScreen::canvas_reset(int type)
{
    if(canvas==nullptr)
    {
        return;
    }
    int r,g,b;
    color_type=type;
    if(type==0)
    {
        for(int x=0;x<150;x++)
        {
            for(int y=0;y<150;y++)
            {
                r = canvas_r;
                g = x*255/150;
                b = y*255/150;
                if(y%10 == 0 && x%10 == 0)
                {
                    //LV_LOG_USER("b = %d",b);
                }
                canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
        }
    }
    else if(type==1)
    {
        for(int x=0;x<150;x++)
        {
            for(int y=0;y<150;y++)
            {
                r = x*255/150;
                g = canvas_g;
                b = y*255/150;
                if(y%10 == 0 && x%10 == 0)
                {
                    //LV_LOG_USER("b = %d",b);
                }
                canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
        }
    }
    else if(type==2)
    {
        for(int x=0;x<150;x++)
        {
            for(int y=0;y<150;y++)
            {
                r = x*255/150;
                g = y*255/150;
                b = canvas_b;
                if(y%10 == 0 && x%10 == 0)
                {
                    //LV_LOG_USER("b = %d",b);
                }
                canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
        }
    }
}

lv_color_t* RenamecolorScreen::create_slide_canvas(void)
{
    static lv_color_t slidebuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(310, 40)];//分配buf存放画板数据
    if(slide_canvas==nullptr)
    {
        slide_canvas =new LvcppCanvas(mparent);
    }
    slide_canvas->set_size(310,40);
    slide_canvas->set_buffer(slidebuf, 310, 40, LV_IMG_CF_TRUE_COLOR);//设置画板空间
    slide_canvas->align_to(canvas->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,10);
    int r,g,b;

    for(int x=0;x<310;x++)
    {
        for(int y=0;y<40;y++)
        {
            if(x<(310/3))
            {
                r = x*255/(310/3);
                g = 0;
                b = 0;
                slide_canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
            else if(x<(310/3*2))
            {
                r = 0;
                g = (x-(310/3))*255/(310/3);
                b = 0;
                slide_canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
            else
            {
                r = 0;
                g = 0;
                b = (x-(310/3*2))*255/(310/3);
                slide_canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
        }
    }

    slide_canvas->set_main_border(2,lv_color_black(),LV_OPA_100);
    slide_canvas->add_flag(LV_OBJ_FLAG_CLICKABLE);
    slide_canvas->add_event_cb(textarea_event_hander,LV_EVENT_ALL,this);
    lv_draw_img_dsc_init(&img_draw_dsc);
    return slidebuf;
}


void RenamecolorScreen::initial()
{
    create_canvas();
    //create_slide_canvas();

    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }
    if(color_tip == nullptr)
    {
        color_tip = new LvcppLabel(mparent);
        color_tip->set_pos(0,0);
        color_tip->set_size(328,40);
        color_tip->set_style_text_font(myfont->font(),0);
        color_tip->txt_font_size(25,0);
        color_tip->set_main_bg_color(lv_color_hex(0x7D7D7D),LV_OPA_100);
        color_tip->set_txt("字体颜色");
        color_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        color_tip->txt_color(lv_color_white(),0);
    }
    if(color_line == nullptr)
    {
        color_line = new LvcppLabel(mparent);
        color_line->set_txt("");
        color_line->set_pos(0,40);
        color_line->set_size(340,1);
        color_line->set_main_bg_color(lv_color_hex(0xFFFFFF),LV_OPA_0);
        color_line->set_main_border(2,lv_color_hex(0x404040),LV_OPA_100);
    }

    if(red_color == nullptr)
    {
        red_color = new LvcppButton(mparent);
        red_color->set_pos(10,45);
        red_color->set_size(30,30);
        red_color->add_txt("");
        red_color->txt_font_size(25,0);
        red_color->txt_align(LV_ALIGN_CENTER,0,0);
        red_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        red_color->set_main_bg_color(lv_color_hex(0xFF00000),LV_OPA_100);
        red_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

    if(orange_color == nullptr)
    {
        orange_color = new LvcppButton(mparent);
        orange_color->align_to(red_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        orange_color->set_size(30,30);
        orange_color->add_txt("");
        orange_color->txt_font_size(25,0);
        orange_color->txt_align(LV_ALIGN_CENTER,0,0);
        orange_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        orange_color->set_main_bg_color(lv_color_hex(0xFF8000),LV_OPA_100);
        orange_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(yellow_color == nullptr)
    {
        yellow_color = new LvcppButton(mparent);
        yellow_color->align_to(orange_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        yellow_color->set_size(30,30);
        yellow_color->add_txt("");
        yellow_color->txt_font_size(25,0);
        yellow_color->txt_align(LV_ALIGN_CENTER,0,0);
        yellow_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        yellow_color->set_main_bg_color(lv_color_hex(0xFFFF00),LV_OPA_100);
        yellow_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(green_color == nullptr)
    {
        green_color = new LvcppButton(mparent);
        green_color->align_to(yellow_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        green_color->set_size(30,30);
        green_color->add_txt("");
        green_color->txt_font_size(25,0);
        green_color->txt_align(LV_ALIGN_CENTER,0,0);
        green_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        green_color->set_main_bg_color(lv_color_hex(0x00FF00),LV_OPA_100);
        green_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(blue_color == nullptr)
    {
        blue_color = new LvcppButton(mparent);
        blue_color->align_to(green_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        blue_color->set_size(30,30);
        blue_color->add_txt("");
        blue_color->txt_font_size(25,0);
        blue_color->txt_align(LV_ALIGN_CENTER,0,0);
        blue_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        blue_color->set_main_bg_color(lv_color_hex(0x0000FF),LV_OPA_100);
        blue_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(cyan_color == nullptr)
    {
        cyan_color = new LvcppButton(mparent);
        cyan_color->align_to(blue_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        cyan_color->set_size(30,30);
        cyan_color->add_txt("");
        cyan_color->txt_font_size(25,0);
        cyan_color->txt_align(LV_ALIGN_CENTER,0,0);
        cyan_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        cyan_color->set_main_bg_color(lv_color_hex(0x00FFFF),LV_OPA_100);
        cyan_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(purple_color == nullptr)
    {
        purple_color = new LvcppButton(mparent);
        purple_color->align_to(cyan_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        purple_color->set_size(30,30);
        purple_color->add_txt("");
        purple_color->txt_font_size(25,0);
        purple_color->txt_align(LV_ALIGN_CENTER,0,0);
        purple_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        purple_color->set_main_bg_color(lv_color_hex(0xFF00FF),LV_OPA_100);
        purple_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(black_color == nullptr)
    {
        black_color = new LvcppButton(mparent);
        black_color->align_to(purple_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        black_color->set_size(30,30);
        black_color->add_txt("");
        black_color->txt_font_size(25,0);
        black_color->txt_align(LV_ALIGN_CENTER,0,0);
        black_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        black_color->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
        black_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(white_color == nullptr)
    {
        white_color = new LvcppButton(mparent);
        white_color->align_to(black_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        white_color->set_size(30,30);
        white_color->add_txt("");
        white_color->txt_font_size(25,0);
        white_color->txt_align(LV_ALIGN_CENTER,0,0);
        white_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        white_color->set_main_bg_color(lv_color_hex(0xFFFFFF),LV_OPA_100);
        white_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_R_tip == NULL)
    {
        font_R_tip = new LvcppLabel(mparent);
        font_R_tip->set_txt("R");
        font_R_tip->set_pos(173,97);
        font_R_tip->set_size(20,25);
        font_R_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_R_tip->set_style_text_font(myfont->font(),0);
        font_R_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_R_down == nullptr)
    {
        font_R_down = new LvcppButton(mparent);
        font_R_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_R_down->align_to(font_R_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_R_down->set_size(26,35);
        font_R_down->add_txt("-");
        font_R_down->txt_center();
        font_R_down->txt_color(lv_color_white());
        font_R_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_R_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_R_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_R_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_R == NULL)
    {
        font_R = new LvcppLabel(mparent);
        font_R->set_txt("0");
        font_R->align_to(font_R_down->myobj,LV_ALIGN_RIGHT_MID,20,-4);
        font_R->set_size(70,35);
        font_R->set_style_text_font(myfont->font(),0);
        font_R->txt_align(LV_TEXT_ALIGN_CENTER);
        font_R->txt_color(lv_color_white(),0);
        font_R->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        font_R->add_flag(LV_OBJ_FLAG_CLICKABLE);
        font_R->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_R_up == nullptr)
    {
        font_R_up = new LvcppButton(mparent);
        font_R_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_R_up->align_to(font_R->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_R_up->set_size(26,35);
        font_R_up->add_txt("+");
        font_R_up->txt_center();
        font_R_up->txt_color(lv_color_white());
        font_R_up->set_style_text_font(myfont->font(),0);
        font_R_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_R_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_R_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_R_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }


    if(font_G_tip == NULL)
    {
        font_G_tip = new LvcppLabel(mparent);
        font_G_tip->set_txt("G");
        font_G_tip->set_pos(173,138);
        font_G_tip->set_size(20,25);
        font_G_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_G_tip->set_style_text_font(myfont->font(),0);
        font_G_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_G_down == nullptr)
    {
        font_G_down = new LvcppButton(mparent);
        font_G_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_G_down->align_to(font_G_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_G_down->set_size(26,35);
        font_G_down->add_txt("-");
        font_G_down->txt_center();
        font_G_down->txt_color(lv_color_white());
        font_G_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_G_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_G_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_G_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_G == NULL)
    {
        font_G = new LvcppLabel(mparent);
        font_G->set_txt("0");
        font_G->align_to(font_G_down->myobj,LV_ALIGN_RIGHT_MID,20,-4);
        font_G->set_size(70,35);
        font_G->set_style_text_font(myfont->font(),0);
        font_G->txt_align(LV_TEXT_ALIGN_CENTER);
        font_G->txt_color(lv_color_white(),0);
        font_G->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        font_G->add_flag(LV_OBJ_FLAG_CLICKABLE);
        font_G->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_G_up == nullptr)
    {
        font_G_up = new LvcppButton(mparent);
        font_G_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_G_up->align_to(font_G->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_G_up->set_size(26,35);
        font_G_up->add_txt("+");
        font_G_up->txt_center();
        font_G_up->txt_color(lv_color_white());
        font_G_up->set_style_text_font(myfont->font(),0);
        font_G_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_G_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_G_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_G_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_B_tip == NULL)
    {
        font_B_tip = new LvcppLabel(mparent);
        font_B_tip->set_txt("B");
        font_B_tip->set_pos(173,178);
        font_B_tip->set_size(20,25);
        font_B_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_B_tip->set_style_text_font(myfont->font(),0);
        font_B_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_B_down == nullptr)
    {
        font_B_down = new LvcppButton(mparent);
        font_B_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_B_down->align_to(font_B_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_B_down->set_size(26,35);
        font_B_down->add_txt("-");
        font_B_down->txt_center();
        font_B_down->txt_color(lv_color_white());
        font_B_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_B_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_B_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_B_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_B == NULL)
    {
        font_B = new LvcppLabel(mparent);
        font_B->set_txt("0");
        font_B->align_to(font_B_down->myobj,LV_ALIGN_RIGHT_MID,20,-4);
        font_B->set_size(70,35);
        font_B->set_style_text_font(myfont->font(),0);
        font_B->txt_align(LV_TEXT_ALIGN_CENTER);
        font_B->txt_color(lv_color_white(),0);
        font_B->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        font_B->add_flag(LV_OBJ_FLAG_CLICKABLE);
        font_B->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_B_up == nullptr)
    {
        font_B_up = new LvcppButton(mparent);
        font_B_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_B_up->align_to(font_B->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_B_up->set_size(26,35);
        font_B_up->add_txt("+");
        font_B_up->txt_center();
        font_B_up->txt_color(lv_color_white());
        font_B_up->set_style_text_font(myfont->font(),0);
        font_B_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_B_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_B_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_B_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }


    if(now_color_tip == nullptr)
    {
        now_color_tip = new LvcppLabel(mparent);
        now_color_tip->set_pos(170,212);
        now_color_tip->set_size(100,25);
        now_color_tip->set_style_text_font(myfont->font(),0);
        now_color_tip->txt_font_size(25,0);
        now_color_tip->set_txt("当前选择");
        now_color_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        now_color_tip->txt_color(lv_color_black(),0);
    }
    if(now_color_show == nullptr)
    {
        now_color_show = new LvcppLabel(mparent);
        now_color_show->align_to(now_color_tip->myobj,LV_ALIGN_OUT_RIGHT_MID,25,5);
        now_color_show->set_size(25,25);
        now_color_show->set_style_text_font(myfont->font(),0);
        now_color_show->set_txt("");
        now_color_show->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
    }

    if(ok_button == nullptr)
    {
        ok_button = new LvcppButton(mparent);
        ok_button->set_pos(25,280);
        ok_button->set_size(120,40);
        ok_button->add_txt("选择");
        ok_button->txt_font_size(25,0);
        ok_button->txt_align(LV_ALIGN_CENTER,0,0);
        ok_button->set_style_text_font(myfont->font(),0);
        ok_button->set_main_radius(10);
        ok_button->txt_color(lv_color_white());
        ok_button->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        ok_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(del_button == nullptr)
    {
        del_button = new LvcppButton(mparent);
        del_button->align_to(ok_button->myobj,LV_ALIGN_RIGHT_MID,45,-16);
        del_button->set_size(120,40);
        del_button->add_txt("取消");
        del_button->txt_font_size(25,0);
        del_button->txt_align(LV_ALIGN_CENTER,0,0);
        del_button->set_style_text_font(myfont->font(),0);
        del_button->set_main_radius(10);
        del_button->txt_color(lv_color_white());
        del_button->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        del_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

}

void RenamecolorScreen::auto_rgb_color_palette(void)
{
    int rgb_num;
    int rgb_num1;
    int rgb_num2;
    rgb_num = atoi(font_R->get_txt());
    rgb_num1 = atoi(font_G->get_txt());
    rgb_num2 = atoi(font_B->get_txt());
    now_color_show->set_main_bg_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),LV_OPA_100);

    renameeffectopt->change_font_color->set_main_bg_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),LV_OPA_100);
}

void RenamecolorScreen::font_rgb_color_palette(int param)
{
    int rgb_num;
    int rgb_num1;
    int rgb_num2;
    rgb_num = atoi(font_R->get_txt());
    rgb_num1 = atoi(font_G->get_txt());
    rgb_num2 = atoi(font_B->get_txt());

    //LV_LOG_USER("rgb_num = %d ,rgb_num = %d,rgb_num = %d",rgb_num,rgb_num,rgb_num);
    if(param == 1)
    {
        renameheadopt->usre_param_label->txt_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),0);
    }
    if(param == 2)
    {
        renameheadopt->usre_company_label->txt_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),0);
    }
    if(param == 3)
    {
        renameheadopt->usre_duty_label->txt_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),0);
    }
}


//改变字体颜色
void RenamecolorScreen::rgb_color_palette(int r,int g,int b)
{
    char font_rgb[10];
    char font_rgb1[10];
    char font_rgb2[10];
    now_color_show->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);
    //itoa(r,font_rgb,10);
    //itoa(g,font_rgb1,10);
    //itoa(b,font_rgb2,10);

    sprintf(font_rgb,"%d",r);
    sprintf(font_rgb1,"%d",g);
    sprintf(font_rgb2,"%d",b);
    font_R->set_txt(font_rgb);
    font_G->set_txt(font_rgb1);
    font_B->set_txt(font_rgb2);
    renameeffectopt->change_font_color->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);
}

uint8_t RenamecolorScreen::toByte(char c)
{
    unsigned char value = 0;

    if (c >= '0' && c <= '9')
        value = c - '0';
    else if (c >= 'A' && c <= 'Z')
        value = c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        value = c - 'a' + 10;

    return value;
}

void RenamecolorScreen::hexStringToByte(uint8_t *dstByte,const char *srcHexString ,int len)
{
    int index;

    for (int i = 0; i < len; i++){
        index = i * 2;
        dstByte[i] = ((toByte(srcHexString[index]))<<4) | toByte(srcHexString[index+1]);
    }
}

void RenamecolorScreen::get_rgb_vlaue(int param)
{
    char font_rgb[10];
    char font_rgb1[10];
    char font_rgb2[10];
    char rgb_value[10];
    int r,g,b;
    uint8_t color[3];
    lv_color_t color_key;
   if(param == 1)
   {
        color_key = lv_obj_get_style_text_color(renameheadopt->usre_param_label->myobj,0);
        sprintf(font_rgb,"%d",color_key.ch.red);
        sprintf(font_rgb1,"%d",color_key.ch.green);
        sprintf(font_rgb2,"%d",color_key.ch.blue);
        font_R->set_txt(font_rgb);
        font_G->set_txt(font_rgb1);
        font_B->set_txt(font_rgb2);
        now_color_show->set_main_bg_color(color_key,LV_OPA_100);
        renameeffectopt->change_font_color->set_main_bg_color(color_key,LV_OPA_100);
   }
   else if(param == 2)
   {
       color_key = lv_obj_get_style_text_color(renameheadopt->usre_company_label->myobj,0);
       sprintf(font_rgb,"%d",color_key.ch.red);
       sprintf(font_rgb1,"%d",color_key.ch.green);
       sprintf(font_rgb2,"%d",color_key.ch.blue);
       font_R->set_txt(font_rgb);
       font_G->set_txt(font_rgb1);
       font_B->set_txt(font_rgb2);
       now_color_show->set_main_bg_color(color_key,LV_OPA_100);
       renameeffectopt->change_font_color->set_main_bg_color(color_key,LV_OPA_100);
   }
   else if(param == 3)
   {
       color_key = lv_obj_get_style_text_color(renameheadopt->usre_duty_label->myobj,0);
       sprintf(font_rgb,"%d",color_key.ch.red);
       sprintf(font_rgb1,"%d",color_key.ch.green);
       sprintf(font_rgb2,"%d",color_key.ch.blue);
       font_R->set_txt(font_rgb);
       font_G->set_txt(font_rgb1);
       font_B->set_txt(font_rgb2);
       now_color_show->set_main_bg_color(color_key,LV_OPA_100);
       renameeffectopt->change_font_color->set_main_bg_color(color_key,LV_OPA_100);
   }
}
void RenamecolorScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenameeffectScreen* opt = (RenameeffectScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==color_setopt->canvas->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            lv_point_t point;
            lv_point_t x_point;
            LvcppIndev::get_indev_point(&x_point);
            //LV_LOG_USER("x_point.x = %d ,x_point.y = %d",x_point.x,x_point.y);
            point.x = x_point.x-color_setopt->canvas->pos_x()-color_setopt->mscreen->pos_x();
            point.y = x_point.y-color_setopt->canvas->pos_y()-color_setopt->mscreen->pos_y();
            //LV_LOG_USER("point.x = %d ,point.y = %d",point.x,point.y);
            int r,g,b;
            if(color_setopt->color_type == 0)
            {
                r = color_setopt->canvas_r;
                g = point.x*255/150;
                b = point.y*255/150;
            }
            else if(color_setopt->color_type == 1)
            {
                r = point.x*255/150;
                g = color_setopt->canvas_g;
                b = point.y*255/150;
            }
            else
            {
                r = point.x*255/150;
                g = point.y*255/150;
                b = color_setopt->canvas_b;
            }
            //b = ((point.x)^2+(point.x)^2)*255/150;
            //LV_LOG_USER("r = %d ,g = %d,b = %d",r,g,b);

            //改变画板
            color_setopt->rgb_color_palette(r,g,b);
            color_setopt->font_rgb_color_palette(param_state);
        }
    }
    /*else if(target==color_setopt->slide_canvas->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            lv_point_t point;
            lv_point_t x_point;
            LvcppIndev::get_indev_point(&x_point);
            //LV_LOG_USER("x_point.x = %d ,x_point.y = %d",x_point.x,x_point.y);
            point.x = x_point.x-color_setopt->slide_canvas->pos_x()-color_setopt->mscreen->pos_x();
            point.y = x_point.y-color_setopt->slide_canvas->pos_y()-color_setopt->mscreen->pos_y();
            //LV_LOG_USER("point.x = %d ,point.y = %d",point.x,point.y);
            int r,g,b;

            if(point.x<(310/3))
            {
                r = point.x*255/(310/3);
                g= 0;
                b= 0;
                color_setopt->canvas_r = r;
                color_setopt->canvas_g = g;
                color_setopt->canvas_b = b;
                color_setopt->canvas_reset(0);
            }
            else if(point.x<(310/3*2))
            {
                r = 0;
                g = (point.x-(310/3))*255/(310/3);
                b = 0;
                color_setopt->canvas_r = r;
                color_setopt->canvas_g = g;
                color_setopt->canvas_b = b;
                color_setopt->canvas_reset(1);
            }
            else
            {
                r = 0;
                g = 0;
                b = (point.x-(310/3*2))*255/(310/3);
                color_setopt->canvas_r = r;
                color_setopt->canvas_g = g;
                color_setopt->canvas_b = b;
                color_setopt->canvas_reset(2);
            }
            //改变画板
            color_setopt->rgb_color_palette(r,g,b);
            color_setopt->font_rgb_color_palette(param_state);
        }
    }*/
    else if(target==color_setopt->mscreen->myobj)
    {
        if(event->code == LV_EVENT_PRESSING)
        {

            /*
            lv_point_t x_point;
            LvcppIndev::get_indev_point(&x_point);
            //LV_LOG_USER("x_point.x = %d ,x_point.y = %d",x_point.x,x_point.y);
            color_setopt->mscreen->set_pos(x_point.x,x_point.y);*/


            lv_obj_t* obj = lv_event_get_target(event); //获取事件产生的对象
            lv_indev_t* indev = lv_indev_get_act();  //获取活动界面输入设备
            lv_point_t vect;
            lv_indev_get_vect(indev, &vect); //获取vect point
            lv_coord_t x = lv_obj_get_x(obj) + vect.x; //计算x
            lv_coord_t y = lv_obj_get_y(obj) + vect.y; // 计算y
            lv_obj_set_pos(obj, x, y); //移动对象到x,y
        }
        else if(event->code == LV_EVENT_PRESSED)
        {
            color_setopt->mscreen->move_foreground();
        }
    }
    //
    else if(target == color_setopt->red_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0xFF00000),LV_OPA_100);
            color_setopt->font_R->set_txt("255");
            color_setopt->font_G->set_txt("0");
            color_setopt->font_B->set_txt("0");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(255,0,0),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(255,0,0),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(255,0,0),0);
            }
        }
    }
    else if(target == color_setopt->orange_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0xFF8000),LV_OPA_100);
            color_setopt->font_R->set_txt("255");
            color_setopt->font_G->set_txt("128");
            color_setopt->font_B->set_txt("0");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(255,128,0),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(255,128,0),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(255,128,0),0);
            }
        }
    }
    else if(target == color_setopt->yellow_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0xFFFF00),LV_OPA_100);
            color_setopt->font_R->set_txt("255");
            color_setopt->font_G->set_txt("255");
            color_setopt->font_B->set_txt("0");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(255,255,0),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(255,255,0),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(255,255,0),0);
            }
        }
    }
    else if(target == color_setopt->green_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0x00FF00),LV_OPA_100);
            color_setopt->font_R->set_txt("0");
            color_setopt->font_G->set_txt("255");
            color_setopt->font_B->set_txt("0");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(0,255,0),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(0,255,0),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(0,255,0),0);
            }
        }
    }
    else if(target == color_setopt->blue_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0x0000FF),LV_OPA_100);
            color_setopt->font_R->set_txt("0");
            color_setopt->font_G->set_txt("0");
            color_setopt->font_B->set_txt("255");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(0,0,255),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(0,0,255),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(0,0,255),0);
            }
        }
    }
    else if(target == color_setopt->cyan_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0x00FFFF),LV_OPA_100);
            color_setopt->font_R->set_txt("0");
            color_setopt->font_G->set_txt("255");
            color_setopt->font_B->set_txt("255");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(0,255,255),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(0,255,255),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(0,255,255),0);
            }
        }
    }
    else if(target == color_setopt->purple_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0xFF00FF),LV_OPA_100);
            color_setopt->font_R->set_txt("255");
            color_setopt->font_G->set_txt("0");
            color_setopt->font_B->set_txt("255");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(255,0,255),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(255,0,255),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(255,0,255),0);
            }
        }
    }
    else if(target == color_setopt->black_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
            color_setopt->font_R->set_txt("0");
            color_setopt->font_G->set_txt("0");
            color_setopt->font_B->set_txt("0");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(0,0,0),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(0,0,0),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(0,0,0),0);
            }
        }
    }
    else if(target == color_setopt->white_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->now_color_show->set_main_bg_color(lv_color_hex(0xFFFFFF),LV_OPA_100);
            color_setopt->font_R->set_txt("255");
            color_setopt->font_G->set_txt("255");
            color_setopt->font_B->set_txt("255");
            color_setopt->auto_rgb_color_palette();
            if(param_state == 1)
            {
                renameheadopt->usre_param_label->txt_color(lv_color_make(255,255,255),0);
            }
            else if(param_state == 2)
            {
                renameheadopt->usre_company_label->txt_color(lv_color_make(255,255,255),0);
            }
            else if(param_state == 3)
            {
                renameheadopt->usre_duty_label->txt_color(lv_color_make(255,255,255),0);
            }
        }
    }


    //rgb  r num show
    else if(target == color_setopt->font_R_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(color_setopt->font_R->get_txt());

            if(event->code == LV_EVENT_PRESSING )
            {
                //LV_LOG_USER("PRESSING");
                state ++ ;
                //LV_LOG_USER("state =%d",state);
                if(state  >= 10)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                        sprintf(rgb_input_num,"%d",rgb_num);
                    color_setopt->font_R->set_txt(rgb_input_num);
                    color_setopt->canvas_r = rgb_num;
                }
            }
            else if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                //LV_LOG_USER("CLICKED");
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                color_setopt->font_R->set_txt(rgb_input_num);
                color_setopt->canvas_r = rgb_num;
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                //LV_LOG_USER("RELEASED");

               color_setopt->auto_rgb_color_palette();
               color_setopt->font_rgb_color_palette(param_state);
               color_setopt->canvas_reset(0);
               state = 0;
            }
        }

    }

    else if(target == color_setopt->font_R_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(color_setopt->font_R->get_txt());

            if(event->code == LV_EVENT_PRESSING)
            {
                //LV_LOG_USER("PRESSING");
                state ++ ;
                //LV_LOG_USER("state =%d",state);
                if(state >=10)
                {
                    rgb_num += 5;
                    if(rgb_num >= 255)
                    {
                        rgb_num = 255;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    color_setopt->font_R->set_txt(rgb_input_num);
                    color_setopt->canvas_r = rgb_num;
                }

            }
            else if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                 //LV_LOG_USER("CLICKED");
                rgb_num++;
                if(rgb_num >= 255)
                {
                    rgb_num = 255;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                color_setopt->font_R->set_txt(rgb_input_num);
                color_setopt->canvas_r = rgb_num;
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 //LV_LOG_USER("RELEASED");

               color_setopt->auto_rgb_color_palette();
               color_setopt->font_rgb_color_palette(param_state);
               color_setopt->canvas_reset(0);
               state = 0;
            }
        }

    }


    //rgb  g num show
    else if(target == color_setopt->font_G_down->myobj )
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(color_setopt->font_G->get_txt());
            if(event->code == LV_EVENT_CLICKED &&state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                color_setopt->font_G->set_txt(rgb_input_num);
                color_setopt->canvas_g = rgb_num;
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                //LV_LOG_USER("PRESSING");
                state ++ ;
                //LV_LOG_USER("state =%d",state);
                if(state  >= 10)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    color_setopt->font_G->set_txt(rgb_input_num);
                    color_setopt->canvas_g = rgb_num;
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {

               color_setopt->auto_rgb_color_palette();
               color_setopt->font_rgb_color_palette(param_state);
               color_setopt->canvas_reset(1);
               state =0 ;
            }
        }

    }

    else if(target == color_setopt->font_G_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(color_setopt->font_G->get_txt());
            if(event->code == LV_EVENT_CLICKED &&state == 0)
            {
                rgb_num++;
                if(rgb_num >= 255)
                {
                    rgb_num = 255;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                color_setopt->font_G->set_txt(rgb_input_num);
                color_setopt->canvas_g = rgb_num;
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 255)
                    {
                        rgb_num = 255;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    color_setopt->font_G->set_txt(rgb_input_num);
                    color_setopt->canvas_g = rgb_num;
                }

            }
            else if(event->code == LV_EVENT_RELEASED)
            {

               color_setopt->auto_rgb_color_palette();
               color_setopt->font_rgb_color_palette(param_state);
               color_setopt->canvas_reset(1);
               state = 0;
            }
        }

    }

    //rgb  B num show
    else if(target == color_setopt->font_B_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(color_setopt->font_B->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                color_setopt->font_B->set_txt(rgb_input_num);
                color_setopt->canvas_b = rgb_num;
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    color_setopt->font_B->set_txt(rgb_input_num);
                    color_setopt->canvas_b = rgb_num;
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {

               color_setopt->auto_rgb_color_palette();
               color_setopt->font_rgb_color_palette(param_state);
               color_setopt->canvas_reset(2);
               state = 0;
            }
        }

    }

    else if(target == color_setopt->font_B_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(color_setopt->font_B->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 255)
                {
                    rgb_num = 255;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                color_setopt->font_B->set_txt(rgb_input_num);
                color_setopt->canvas_b = rgb_num;
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state >10)
                {
                    rgb_num += 5;
                    if(rgb_num >= 255)
                    {
                        rgb_num = 255;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    color_setopt->font_B->set_txt(rgb_input_num);
                    color_setopt->canvas_b = rgb_num;
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {

               color_setopt->auto_rgb_color_palette();
               color_setopt->font_rgb_color_palette(param_state);
               color_setopt->canvas_reset(2);
               state = 0;
            }
        }
    }
    else if(target == color_setopt->font_R->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
            color_setopt->canvas_reset(0);
    }
    else if(target == color_setopt->font_G->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
            color_setopt->canvas_reset(1);
    }
    else if(target == color_setopt->font_B->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
            color_setopt->canvas_reset(2);
    }
    else if(target == color_setopt->del_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->mscreen->show(false);
            char r_value[16],g_value[16],b_value[16];
            sprintf(r_value,"%d",color_setopt->save_r);
            color_setopt->font_R->set_txt(r_value);
            sprintf(g_value,"%d",color_setopt->save_g);
            color_setopt->font_G->set_txt(g_value);
            sprintf(b_value,"%d",color_setopt->save_b);
            color_setopt->font_B->set_txt(b_value);
            color_setopt->auto_rgb_color_palette();
            color_setopt->font_rgb_color_palette(param_state);
        }
    }
    else if(target == color_setopt->ok_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            color_setopt->save_r = atoi(color_setopt->font_R->get_txt());
            color_setopt->save_g = atoi(color_setopt->font_G->get_txt());
            color_setopt->save_b = atoi(color_setopt->font_B->get_txt());
            color_setopt->mscreen->show(false);
        }
    }

}


//FONT SET WIN
RenamefontsetScreen::RenamefontsetScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);//lv_layer_top()
    mscreen->set_bg_color(lv_color_hex(0xAA89BD),LV_OPA_100);
    mscreen->set_size(350,460);
    mscreen->set_pos(600,65);
    mscreen->set_main_radius(10);
    mscreen->set_main_border(3,lv_color_hex(0x8957A1),LV_OPA_100);
    mparent = mscreen->get_screen();
    renamfontsetwinopt = this;
    initial();
    //lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
    mscreen->add_flag(LV_OBJ_FLAG_CLICKABLE);
    mscreen->clear_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    mscreen->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
    mscreen->add_event_cb(textarea_event_hander,LV_EVENT_PRESSED,this);
}

RenamefontsetScreen::~RenamefontsetScreen()
{

    if(font_w_tip !=NULL)
    {
        delete  font_w_tip;
        font_w_tip = NULL;
    }
    if(font_W_down !=NULL)
    {
        delete  font_W_down;
        font_W_down = NULL;
    }
    if(font_w !=NULL)
    {
        delete  font_w;
        font_w = NULL;
    }
    if(font_w_up !=NULL)
    {
        delete  font_w_up;
        font_w_up = NULL;
    }
    if(font_h_tip !=NULL)
    {
        delete  font_h_tip;
        font_h_tip = NULL;
    }
    if(font_h_down !=NULL)
    {
        delete  font_h_down;
        font_h_down = NULL;
    }
    if(font_h !=NULL)
    {
        delete  font_h;
        font_h = NULL;
    }
    if(font_h_up !=NULL)
    {
        delete  font_h_up;
        font_h_up = NULL;
    }
    if(font_x_tip !=NULL)
    {
        delete  font_x_tip;
        font_x_tip = NULL;
    }
    if(font_x_down !=NULL)
    {
        delete  font_x_down;
        font_x_down = NULL;
    }
    if(font_x_up !=NULL)
    {
        delete  font_x_up;
        font_x_up = NULL;
    }
    if(font_x !=NULL)
    {
        delete  font_x;
        font_x = NULL;
    }
    if(font_y !=NULL)
    {
        delete  font_y;
        font_y = NULL;
    }
    if(font_y_up !=NULL)
    {
        delete  font_y_up;
        font_y_up = NULL;
    }
    if(font_y_down !=NULL)
    {
        delete  font_y_down;
        font_y_down = NULL;
    }
    if(font_y_tip !=NULL)
    {
        delete  font_y_tip;
        font_y_tip = NULL;
    }
    if(font_effect_tip !=NULL)
    {
        delete  font_effect_tip;
        font_effect_tip = NULL;
    }
    if(change_refont_style !=NULL)
    {
        delete  change_refont_style;
        change_refont_style = NULL;
    }
    if(change_refont_form !=NULL)
    {
        delete  change_refont_form;
        change_refont_form = NULL;
    }
    if(change_font_alignment !=NULL)
    {
        delete  change_font_alignment;
        change_font_alignment = NULL;
    }
    if(change_font_color !=NULL)
    {
        delete  change_font_color;
        change_font_color = NULL;
    }
    if(border_line !=NULL)
    {
        delete  border_line;
        border_line = NULL;
    }
    if(font_size !=NULL)
    {
        delete  font_size;
        font_size = NULL;
    }
    if(font_size_up !=NULL)
    {
        delete  font_size_up;
        font_size_up = NULL;
    }
    if(font_size_down !=NULL)
    {
        delete  font_size_down;
        font_size_down = NULL;
    }
    if(font_size_tip !=NULL)
    {
        delete  font_size_tip;
        font_size_tip = NULL;
    }
    if(font_between !=NULL)
    {
        delete  font_between;
        font_between = NULL;
    }
    if(font_between_up !=NULL)
    {
        delete  font_between_up;
        font_between_up = NULL;
    }
    if(font_between_down !=NULL)
    {
        delete  font_between_down;
        font_between_down = NULL;
    }
    if(font_between_tip !=NULL)
    {
        delete  font_between_tip;
        font_between_tip = NULL;
    }
    if(auto_button !=NULL)
    {
        delete  auto_button;
        auto_button = NULL;
    }
    if(ok_button !=NULL)
    {
        delete  ok_button;
        ok_button = NULL;
    }
    if(del_button !=NULL)
    {
        delete  del_button;
        del_button = NULL;
    }



    if(mscreen !=NULL)
    {
        delete  mscreen;
        mscreen = NULL;
    }
}

void RenamefontsetScreen::initial()
{
    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }
    if(font_w_tip == NULL)
    {
        font_w_tip = new LvcppLabel(mparent);
        font_w_tip->set_txt("宽");
        font_w_tip->set_pos(23,30);
        font_w_tip->set_size(20,25);
        font_w_tip->set_style_text_font(myfont->font(),0);
        font_w_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_W_down == nullptr)
    {
        font_W_down = new LvcppButton(mparent);
        font_W_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_W_down->align_to(font_w_tip->myobj,LV_ALIGN_RIGHT_MID,19,-16);
        font_W_down->set_size(26,35);
        font_W_down->add_txt("-");
        font_W_down->txt_center();
        font_W_down->txt_color(lv_color_black());
        font_W_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_W_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_W_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_W_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_w == NULL)
    {
        font_w = new LvcppLabel(mparent);
        font_w->set_txt("1024");
        font_w->align_to(font_W_down->myobj,LV_ALIGN_RIGHT_MID,59,-4);
        font_w->set_size(70,35);
        font_w->set_style_text_font(myfont->font(),0);
        font_w->txt_align(LV_TEXT_ALIGN_CENTER);
        font_w->txt_color(lv_color_white(),0);
        font_w->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_w_up == nullptr)
    {
        font_w_up = new LvcppButton(mparent);
        font_w_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_w_up->align_to(font_w->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_w_up->set_size(26,35);
        font_w_up->add_txt("+");
        font_w_up->txt_center();
        font_w_up->txt_color(lv_color_black());
        font_w_up->set_style_text_font(myfont->font(),0);
        font_w_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_w_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_w_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_w_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_h_tip == NULL)
    {
        font_h_tip = new LvcppLabel(mparent);
        font_h_tip->set_txt("高");
        font_h_tip->set_pos(185,30);
        font_h_tip->set_size(20,25);
        font_h_tip->set_style_text_font(myfont->font(),0);
        font_h_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_h_down == nullptr)
    {
        font_h_down = new LvcppButton(mparent);
        font_h_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_h_down->align_to(font_h_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_h_down->set_size(26,35);
        font_h_down->add_txt("-");
        font_h_down->txt_center();
        font_h_down->txt_color(lv_color_black());
        font_h_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_h_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_h_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_h_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_h == NULL)
    {
        font_h = new LvcppLabel(mparent);
        font_h->set_txt("100");
        font_h->align_to(font_h_down->myobj,LV_ALIGN_RIGHT_MID,45,-4);
        font_h->set_size(70,35);
        font_h->set_style_text_font(myfont->font(),0);
        font_h->txt_align(LV_TEXT_ALIGN_CENTER);
        font_h->txt_color(lv_color_white(),0);
        font_h->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_h_up == nullptr)
    {
        font_h_up = new LvcppButton(mparent);
        font_h_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_h_up->align_to(font_h->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_h_up->set_size(26,35);
        font_h_up->add_txt("+");
        font_h_up->txt_center();
        font_h_up->txt_color(lv_color_black());
        font_h_up->set_style_text_font(myfont->font(),0);
        font_h_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_h_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_h_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_h_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_x_tip == NULL)
    {
        font_x_tip = new LvcppLabel(mparent);
        font_x_tip->set_txt("X");
        font_x_tip->set_pos(22,80);
        font_x_tip->set_size(20,25);
        font_x_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_x_tip->set_style_text_font(myfont->font(),0);
        font_x_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_x_down == nullptr)
    {
        font_x_down = new LvcppButton(mparent);
        font_x_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_x_down->align_to(font_x_tip->myobj,LV_ALIGN_RIGHT_MID,21,-16);
        font_x_down->set_size(26,35);
        font_x_down->add_txt("-");
        font_x_down->txt_center();
        font_x_down->txt_color(lv_color_black());
        font_x_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_x_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_x_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_x_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_x == NULL)
    {
        font_x = new LvcppLabel(mparent);
        font_x->set_txt("0");
        font_x->align_to(font_x_down->myobj,LV_ALIGN_RIGHT_MID,19,-4);
        font_x->set_size(70,35);
        font_x->set_style_text_font(myfont->font(),0);
        font_x->txt_align(LV_TEXT_ALIGN_CENTER);
        font_x->txt_color(lv_color_white(),0);
        font_x->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_x_up == nullptr)
    {
        font_x_up = new LvcppButton(mparent);
        font_x_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_x_up->align_to(font_x->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_x_up->set_size(26,35);
        font_x_up->add_txt("+");
        font_x_up->txt_center();
        font_x_up->txt_color(lv_color_black());
        font_x_up->set_style_text_font(myfont->font(),0);
        font_x_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_x_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
        font_x_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
        font_x_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_y_tip == NULL)
    {
        font_y_tip = new LvcppLabel(mparent);
        font_y_tip->set_txt("Y");
        font_y_tip->set_pos(185,80);
        font_y_tip->set_size(20,25);
        font_y_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_y_tip->set_style_text_font(myfont->font(),0);
        font_y_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_y_down == nullptr)
    {
        font_y_down = new LvcppButton(mparent);
        font_y_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_y_down->align_to(font_y_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_y_down->set_size(26,35);
        font_y_down->add_txt("-");
        font_y_down->txt_center();
        font_y_down->txt_color(lv_color_black());
        font_y_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_y_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_y_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_y_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_y == NULL)
    {
        font_y = new LvcppLabel(mparent);
        font_y->set_txt("200");
        font_y->align_to(font_y_down->myobj,LV_ALIGN_RIGHT_MID,51,-4);
        font_y->set_size(70,35);
        font_y->set_style_text_font(myfont->font(),0);
        font_y->txt_align(LV_TEXT_ALIGN_CENTER);
        font_y->txt_color(lv_color_white(),0);
        font_y->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_y_up == nullptr)
    {
        font_y_up = new LvcppButton(mparent);
        font_y_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_y_up->align_to(font_y->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_y_up->set_size(26,35);
        font_y_up->add_txt("+");
        font_y_up->txt_center();
        font_y_up->txt_color(lv_color_black());
        font_y_up->set_style_text_font(myfont->font(),0);
        font_y_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_y_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_y_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_y_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(rename_line == NULL)
    {
        rename_line = new LvcppLabel(mparent);
        rename_line->set_txt("");
        rename_line->set_pos(25,113);
        rename_line->set_size(307,2);
        rename_line->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
    }

    if(font_effect_tip == NULL)
    {
        font_effect_tip = new LvcppLabel(mparent);
        font_effect_tip->set_txt("文字效果");
        font_effect_tip->set_pos(27,120);
        font_effect_tip->set_size(130,30);
        font_effect_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_effect_tip->set_style_text_font(myfont->font(),0);
        font_effect_tip->txt_font_size(30,0);
        font_effect_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }

    if(change_refont_style == nullptr)
    {
        change_refont_style =new LvcppDropdown(mparent);
        change_refont_style->set_pos(20,160);
        change_refont_style->set_size(160,50);
        change_refont_style->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(change_refont_style->get_list(),myfont->font(),0);
        change_refont_style->set_options("黑体\n楷体\n魏体\n宋体\n隶书\n标宋\n中宋\n等宽\n微软雅黑");
        change_refont_style->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        change_refont_style->txt_align(LV_TEXT_ALIGN_CENTER);
        change_refont_style->set_selected(0);
        change_refont_style->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }
    if(change_refont_form == nullptr)
    {
        change_refont_form =new LvcppDropdown(mparent);
        change_refont_form->align_to(change_refont_style->myobj,LV_ALIGN_RIGHT_MID,170,0);
        change_refont_form->set_size(120,50);
        change_refont_form->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(change_refont_form->get_list(),myfont->font(),0);
        change_refont_form->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        change_refont_form->set_options("正常\n斜体\n粗体");
        change_refont_form->txt_align(LV_TEXT_ALIGN_CENTER);
        change_refont_form->set_selected(0);
        change_refont_form->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }

    if(change_font_alignment == nullptr)
    {
        change_font_alignment =new LvcppDropdown(mparent);
        change_font_alignment->set_pos(20,217);
        change_font_alignment->set_size(160,50);
        change_font_alignment->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(change_font_alignment->get_list(),myfont->font(),0);
        change_font_alignment->set_options("左对齐\n居中\n右对齐");
        change_font_alignment->txt_align(LV_TEXT_ALIGN_CENTER);
        change_font_alignment->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        change_font_alignment->set_selected(0);
        change_font_alignment->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
    }

    /*
    if(change_font_color == nullptr)
    {
        change_font_color =new LvcppDropdown(mparent);
        change_font_color->align_to(change_font_alignment->myobj,LV_ALIGN_RIGHT_MID,170,0);
        change_font_color->set_size(120,50);
        change_font_color->set_style_text_font(myfont->font(),0);
        lv_obj_set_style_text_font(change_font_color->get_list(),myfont->font(),0);
        change_font_color->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        change_font_color->set_options("红色\n黑色\n白色\n蓝色\n绿色\n黄色\n紫红\n灰色\n粉色");
        change_font_color->set_selected(1);
        change_font_color->add_event_cb(textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        change_font_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }*/

    if(color_win == nullptr)
    {
        color_win = new LvcppButton(mparent);
        color_win->align_to(change_font_alignment->myobj,LV_ALIGN_RIGHT_MID,50,-20);
        color_win->set_size(120,50);
        color_win->set_style_text_font(myfont->font(),0);
        color_win->add_txt("颜色");
        color_win->set_main_radius(10);
        color_win->txt_color(lv_color_hex(0x222222));
        //color_win->txt_align(LV_TEXT_ALIGN_CENTER,0,0);
        color_win->set_main_border(2,lv_color_white(),LV_OPA_100);
        color_win->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        color_win->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

    if(font_size_tip == NULL)
    {
        font_size_tip = new LvcppLabel(mparent);
        font_size_tip->set_txt("大小");
        font_size_tip->set_pos(70,295);
        font_size_tip->set_size(50,25);
        font_size_tip->set_style_text_font(myfont->font(),0);
        font_size_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_size_down == nullptr)
    {
        font_size_down = new LvcppButton(mparent);
        font_size_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_size_down->align_to(font_size_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_size_down->set_size(26,35);
        font_size_down->add_txt("-");
        font_size_down->txt_center();
        font_size_down->txt_color(lv_color_black());
        font_size_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_size_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_size_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_size_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_size == NULL)
    {
        font_size = new LvcppLabel(mparent);
        font_size->set_txt("100");
        font_size->align_to(font_size_down->myobj,LV_ALIGN_RIGHT_MID,45,-4);
        font_size->set_size(70,35);
        font_size->set_style_text_font(myfont->font(),0);
        font_size->txt_align(LV_TEXT_ALIGN_CENTER);
        font_size->txt_color(lv_color_white(),0);
        font_size->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_size_up == nullptr)
    {
        font_size_up = new LvcppButton(mparent);
        font_size_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_size_up->align_to(font_size->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_size_up->set_size(26,35);
        font_size_up->add_txt("+");
        font_size_up->txt_center();
        font_size_up->txt_color(lv_color_black());
        font_size_up->set_style_text_font(myfont->font(),0);
        font_size_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_size_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_size_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_size_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_between_tip == NULL)
    {
        font_between_tip = new LvcppLabel(mparent);
        font_between_tip->set_txt("间距");
        font_between_tip->set_pos(70,340);
        font_between_tip->set_size(50,25);
        font_between_tip->set_style_text_font(myfont->font(),0);
        font_between_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_between_down == nullptr)
    {
        font_between_down = new LvcppButton(mparent);
        font_between_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_between_down->align_to(font_between_tip->myobj,LV_ALIGN_RIGHT_MID,16,-16);
        font_between_down->set_size(26,35);
        font_between_down->add_txt("-");
        font_between_down->txt_center();
        font_between_down->txt_color(lv_color_black());
        font_between_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_between_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_between_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_between_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_between == NULL)
    {
        font_between = new LvcppLabel(mparent);
        font_between->set_txt("0");
        font_between->align_to(font_between_down->myobj,LV_ALIGN_RIGHT_MID,20,-4);
        font_between->set_size(70,35);
        font_between->set_style_text_font(myfont->font(),0);
        font_between->txt_align(LV_TEXT_ALIGN_CENTER);
        font_between->txt_color(lv_color_white(),0);
        font_between->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
    }
    if(font_between_up == nullptr)
    {
        font_between_up = new LvcppButton(mparent);
        font_between_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_between_up->align_to(font_between->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_between_up->set_size(26,35);
        font_between_up->add_txt("+");
        font_between_up->txt_center();
        font_between_up->txt_color(lv_color_black());
        font_between_up->set_style_text_font(myfont->font(),0);
        font_between_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_between_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_between_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_between_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
/*
    if(auto_button == nullptr)
    {
        auto_button = new LvcppButton(mparent);
        auto_button->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        auto_button->align_to(font_size_up->myobj,LV_ALIGN_RIGHT_MID,45,-12);
        auto_button->set_size(60,80);
        auto_button->add_txt("自\n动");
        auto_button->txt_center();
        auto_button->set_main_radius(10);
        auto_button->txt_color(lv_color_black());
        auto_button->set_style_text_font(myfont->font(),0);
        auto_button->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        auto_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
 */

    if(ok_button == nullptr)
    {
        ok_button = new LvcppButton(mparent);
        ok_button->set_pos(40,393);
        ok_button->set_size(120,40);
        ok_button->add_txt("确认");
        ok_button->txt_font_size(25,0);
        ok_button->txt_align(LV_ALIGN_CENTER,0,0);
        ok_button->set_style_text_font(myfont->font(),0);
        ok_button->set_main_radius(10);
        ok_button->txt_color(lv_color_black());
        ok_button->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        ok_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(del_button == nullptr)
    {
        del_button = new LvcppButton(mparent);
        del_button->align_to(ok_button->myobj,LV_ALIGN_RIGHT_MID,45,-12);
        del_button->set_size(120,40);
        del_button->add_txt("取消");
        del_button->txt_font_size(25,0);
        del_button->txt_align(LV_ALIGN_CENTER,0,0);
        del_button->set_style_text_font(myfont->font(),0);
        del_button->set_main_radius(10);
        del_button->txt_color(lv_color_black());
        del_button->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        del_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(border_line == NULL)
    {
        border_line = new LvcppLabel(mparent);
        border_line->set_txt("");
        border_line->set_pos(22,275);
        border_line->set_size(300,100);
        border_line->set_main_border(1,lv_color_hex(0x003300),LV_OPA_100);
        border_line->set_main_bg_color(lv_color_hex(0xFFFFFF),LV_OPA_0);
    }
    //parameter_amplifier();
}

void RenamefontsetScreen::parameter_amplifier(void)
{
    char x_tmp[10];
    char y_tmp[10];
    char w_tmp[10];
    char h_tmp[10];
    char TextLetterSpace_tmp[10];
    char TextSize_tmp[10];

    char x_tmp1[10];
    char y_tmp1[10];
    char w_tmp1[10];
    char h_tmp1[10];
    char TextLetterSpace_tmp1[10];
    char TextSize_tmp1[10];

    char x_tmp2[10];
    char y_tmp2[10];
    char w_tmp2[10];
    char h_tmp2[10];
    char TextLetterSpace_tmp2[10];
    char TextSize_tmp2[10];


    g_RenameInfo.layout.detail[0].ElePointX = g_RenameInfo.layout.detail[0].ElePointX;
    g_RenameInfo.layout.detail[0].ElePointY = g_RenameInfo.layout.detail[0].ElePointY;
    g_RenameInfo.layout.detail[0].EleWidth = g_RenameInfo.layout.detail[0].EleWidth;
    g_RenameInfo.layout.detail[0].EleHeight = g_RenameInfo.layout.detail[0].EleHeight;
    g_RenameInfo.layout.detail[0].TextSize  = g_RenameInfo.layout.detail[0].TextSize;//*1024/450
    g_RenameInfo.layout.detail[0].TextLetterSpace = g_RenameInfo.layout.detail[0].TextLetterSpace;

    g_RenameInfo.layout.detail[1].ElePointX = g_RenameInfo.layout.detail[1].ElePointX;
    g_RenameInfo.layout.detail[1].ElePointY = g_RenameInfo.layout.detail[1].ElePointY;
    g_RenameInfo.layout.detail[1].EleWidth = g_RenameInfo.layout.detail[1].EleWidth;//
    g_RenameInfo.layout.detail[1].EleHeight = g_RenameInfo.layout.detail[1].EleHeight;
    g_RenameInfo.layout.detail[1].TextSize  = g_RenameInfo.layout.detail[1].TextSize;
    g_RenameInfo.layout.detail[1].TextLetterSpace = g_RenameInfo.layout.detail[1].TextLetterSpace;

    g_RenameInfo.layout.detail[2].ElePointX = g_RenameInfo.layout.detail[2].ElePointX;
    g_RenameInfo.layout.detail[2].ElePointY = g_RenameInfo.layout.detail[2].ElePointY;
    g_RenameInfo.layout.detail[2].EleWidth = g_RenameInfo.layout.detail[2].EleWidth;//
    g_RenameInfo.layout.detail[2].EleHeight = g_RenameInfo.layout.detail[2].EleHeight;
    g_RenameInfo.layout.detail[2].TextSize  = g_RenameInfo.layout.detail[2].TextSize;//*1024/450
    g_RenameInfo.layout.detail[2].TextLetterSpace = g_RenameInfo.layout.detail[2].TextLetterSpace;




    renameopt->font_reset();

    sprintf(x_tmp,"%d",g_RenameInfo.layout.detail[0].ElePointX);
    sprintf(y_tmp,"%d",g_RenameInfo.layout.detail[0].ElePointY);
    sprintf(w_tmp,"%d",g_RenameInfo.layout.detail[0].EleWidth);
    sprintf(h_tmp,"%d",g_RenameInfo.layout.detail[0].EleHeight);
    sprintf(TextSize_tmp,"%d",g_RenameInfo.layout.detail[0].TextSize);
    sprintf(TextLetterSpace_tmp,"%d",g_RenameInfo.layout.detail[0].TextLetterSpace);

    sprintf(x_tmp1,"%d",g_RenameInfo.layout.detail[1].ElePointX);
    sprintf(y_tmp1,"%d",g_RenameInfo.layout.detail[1].ElePointY);
    sprintf(w_tmp1,"%d",g_RenameInfo.layout.detail[1].EleWidth);
    sprintf(h_tmp1,"%d",g_RenameInfo.layout.detail[1].EleHeight);
    sprintf(TextSize_tmp1,"%d",g_RenameInfo.layout.detail[1].TextSize);
    sprintf(TextLetterSpace_tmp1,"%d",g_RenameInfo.layout.detail[1].TextLetterSpace);

    sprintf(x_tmp2,"%d",g_RenameInfo.layout.detail[2].ElePointX);
    sprintf(y_tmp2,"%d",g_RenameInfo.layout.detail[2].ElePointY);
    sprintf(w_tmp2,"%d",g_RenameInfo.layout.detail[2].EleWidth);
    sprintf(h_tmp2,"%d",g_RenameInfo.layout.detail[2].EleHeight);
    sprintf(TextSize_tmp2,"%d",g_RenameInfo.layout.detail[2].TextSize);
    sprintf(TextLetterSpace_tmp2,"%d",g_RenameInfo.layout.detail[2].TextLetterSpace);

    if(param_state == 1)
    {
        //itoa(g_RenameInfo.layout.detail[0].ElePointX,x_tmp,10);
        //itoa(g_RenameInfo.layout.detail[0].ElePointY,x_tmp,10);
        font_x->set_txt(x_tmp);
        font_y->set_txt(y_tmp);
        font_w->set_txt(w_tmp);
        font_h->set_txt(h_tmp);
        font_size->set_txt(TextSize_tmp);
        font_between->set_txt(TextLetterSpace_tmp);
    }
    else if(param_state == 2)
    {
        font_x->set_txt(x_tmp1);
        font_y->set_txt(y_tmp1);
        font_w->set_txt(w_tmp1);
        font_h->set_txt(h_tmp1);
        font_size->set_txt(TextSize_tmp1);
        font_between->set_txt(TextLetterSpace_tmp1);
    }
    else if(param_state == 3)
    {
        font_x->set_txt(x_tmp2);
        font_y->set_txt(y_tmp2);
        font_w->set_txt(w_tmp2);
        font_h->set_txt(h_tmp2);
        font_size->set_txt(TextSize_tmp1);
        font_between->set_txt(TextLetterSpace_tmp2);
    }



    renameheadopt->usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);
    renameheadopt->usre_param_label->set_size(g_RenameInfo.layout.detail[0].EleWidth,g_RenameInfo.layout.detail[0].EleHeight);
    renameheadopt->usre_param_label->set_style_text_letter_space(g_RenameInfo.layout.detail[0].TextLetterSpace,0);
    renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);

    renameheadopt->usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX,g_RenameInfo.layout.detail[1].ElePointY);
    renameheadopt->usre_company_label->set_size(g_RenameInfo.layout.detail[1].EleWidth,g_RenameInfo.layout.detail[1].EleHeight);
    renameheadopt->usre_company_label->set_style_text_letter_space(g_RenameInfo.layout.detail[1].TextLetterSpace,0);
    renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);

    //LV_LOG_USER("x = %d y =%d w =%d,h =%d  ",g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY,g_RenameInfo.layout.detail[2].EleWidth,g_RenameInfo.layout.detail[2].EleHeight);

    renameheadopt->usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY);
    renameheadopt->usre_duty_label->set_size(g_RenameInfo.layout.detail[2].EleWidth,g_RenameInfo.layout.detail[2].EleHeight);
    renameheadopt->usre_duty_label->set_style_text_letter_space(g_RenameInfo.layout.detail[2].TextLetterSpace,0);
    renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
}

void RenamefontsetScreen::font_change_style(int type)
{
    //LV_LOG_USER("777777777777777777777777777777");
    g_RenameInfo.layout.detail[type-1].ElePointX = atoi(renamfontsetwinopt->font_x->get_txt());
    g_RenameInfo.layout.detail[type-1].ElePointY = atoi(renamfontsetwinopt->font_y->get_txt());
    g_RenameInfo.layout.detail[type-1].EleWidth =  atoi(renamfontsetwinopt->font_w->get_txt());
    g_RenameInfo.layout.detail[type-1].EleHeight =  atoi(renamfontsetwinopt->font_h->get_txt());
    //renameopt->font_reset();
    if(param_state == 1)
    {
        renameheadopt->usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);
        renameheadopt->usre_param_label->set_size(g_RenameInfo.layout.detail[0].EleWidth,g_RenameInfo.layout.detail[0].EleHeight);
    }
    else if(param_state == 2)
    {
        renameheadopt->usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX,g_RenameInfo.layout.detail[1].ElePointY);
        renameheadopt->usre_company_label->set_size(g_RenameInfo.layout.detail[1].EleWidth,g_RenameInfo.layout.detail[1].EleHeight);
    }
    else if(param_state == 3)
    {
        renameheadopt->usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY);
        renameheadopt->usre_duty_label->set_size(g_RenameInfo.layout.detail[2].EleWidth,g_RenameInfo.layout.detail[2].EleHeight);//w *600/1024
    }

}

void RenamefontsetScreen::change_font_style(int param_state)
{
    g_RenameInfo.layout.detail[param_state-1].TextSize = atoi( font_size->get_txt());
    g_RenameInfo.layout.detail[param_state-1].TextLetterSpace = atoi( font_between->get_txt());
    g_RenameInfo.layout.detail[param_state-1].TextType = renamfontsetwinopt->change_refont_form->get_selected();
    g_RenameInfo.layout.detail[param_state-1].HorizontalAlign = renamfontsetwinopt->change_font_alignment->get_selected()+1;
    //LV_LOG_USER("change_refont_form->get_selected() = %d",renamfontsetwinopt->change_refont_form->get_selected());
    //LV_LOG_USER("change_font_alignment->get_selected() =%d ",renamfontsetwinopt->change_font_alignment->get_selected());

    if(param_state == 1)
    {
        renameopt->font_initial1();
        renameheadopt->usre_param_label->set_style_text_letter_space(g_RenameInfo.layout.detail[param_state-1].TextLetterSpace,0);
        renameheadopt->usre_param_label->txt_align(g_RenameInfo.layout.detail[param_state-1].HorizontalAlign);
        renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
    }
    else if(param_state == 2)
    {
        renameopt->font_initial2();
        renameheadopt->usre_company_label->set_style_text_letter_space(g_RenameInfo.layout.detail[param_state-1].TextLetterSpace,0);
        renameheadopt->usre_company_label->txt_align(g_RenameInfo.layout.detail[param_state-1].HorizontalAlign);
        renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);
    }
    else if(param_state == 3)
    {
        renameopt->font_initial3();
        renameheadopt->usre_duty_label->set_style_text_letter_space(g_RenameInfo.layout.detail[param_state-1].TextLetterSpace,0);
        renameheadopt->usre_duty_label->txt_align(g_RenameInfo.layout.detail[param_state-1].HorizontalAlign);
        renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
    }

}
void RenamefontsetScreen::change_font_name(int param_state)
{
    ////LV_LOG_USER("tpye = %d",tpye);

    change_refont_style->get_selected_str(g_RenameInfo.layout.detail[param_state-1].TextFont,sizeof(g_RenameInfo.layout.detail[param_state-1].TextFont));

    if(param_state == 1 )
    {
        //LV_LOG_USER("param_state == 1 ");
        //renameopt->font_scan_file_path(g_RenameInfo.layout.detail[param_state-1].TextFont,&ft_font0.name);
        renameopt->font_initial1();
        renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
    }
    else if(param_state == 2 )
    {
        //LV_LOG_USER("param_state == 2 ");
        //renameopt->font_scan_file_path(g_RenameInfo.layout.detail[param_state-1].TextFont,&ft_font0.name);
        renameopt->font_initial2();
        renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);
    }
    else if(param_state == 3 )
    {
        //LV_LOG_USER("param_state == 3 ");
        //renameopt->font_scan_file_path(g_RenameInfo.layout.detail[param_state-1].TextFont,&ft_font0.name);
        renameopt->font_initial3();
        //LV_LOG_USER("font_scan_file_path");
        renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
    }
}

void RenamefontsetScreen::manual_font_color(int param_state)
{
    if(change_font_color->get_selected() == 1)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(0,0,0),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(0,0,0),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(0,0,0),0);
        }
    }
    else if(change_font_color->get_selected() == 0)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,0,0),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,0,0),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,0,0),0);
        }
    }
    else if(change_font_color->get_selected() == 2)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,255,255),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,255,255),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,255,255),0);
        }
    }
    if(change_font_color->get_selected() == 3)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(0,0,255),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(0,0,255),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(0,0,255),0);
        }
    }
    else if(change_font_color->get_selected() == 4)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(0,255,0),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(0,255,0),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(0,255,0),0);
        }
    }
    else if(change_font_color->get_selected() == 5)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,255,0),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,255,0),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,255,0),0);
        }
    }
    else if(change_font_color->get_selected() == 6)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,0,255),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,0,255),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,0,255),0);
        }
    }
    else if(change_font_color->get_selected() == 7)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(128,128,128),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(128,128,128),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(128,128,128),0);
        }
    }
    else if(change_font_color->get_selected() == 8)
    {
        if(param_state == 1)
        {
            renameheadopt->usre_param_label->txt_color(lv_color_make(255,90,90),0);
        }
        if(param_state == 2)
        {
            renameheadopt->usre_company_label->txt_color(lv_color_make(255,90,90),0);
        }
        if(param_state == 3)
        {
            renameheadopt->usre_duty_label->txt_color(lv_color_make(255,90,90),0);
        }
    }
}

void RenamefontsetScreen::zp_param_clear(void)
{
    LV_LOG_USER("---------------------------------");
    memset(&g_RenameInfo,0,sizeof(zpc_canvas_param_t));
    memcpy(&g_RenameInfo,&g_RenameSaveInfo,sizeof(zpc_canvas_param_t));
    //renameopt->font_reset();
    //LV_LOG_USER("---------------------------------");
    renameopt->font_initial_zp();
    char font_font_bet[16];
    sprintf(font_font_bet,"%d",g_RenameInfo.layout.detail[3].TextLetterSpace);
    renameeffectopt->font_between->set_txt(font_font_bet);
    renameheadopt->usre_duty_label->set_style_text_letter_space(g_RenameInfo.layout.detail[2].TextLetterSpace*680/1024,0);
    renameheadopt->usre_duty_label->txt_align(g_RenameInfo.layout.detail[2].HorizontalAlign);
    renameheadopt->usre_duty_label->set_style_text_font(renameopt->myfont2,0);
    renameheadopt->usre_duty_label->set_pos(g_RenameInfo.layout.detail[2].ElePointX*680/1024,g_RenameInfo.layout.detail[2].ElePointY*680/1024);
    renameheadopt->usre_duty_label->set_size(g_RenameInfo.layout.detail[2].EleWidth*680/1024,g_RenameInfo.layout.detail[2].EleHeight*680/1024);

    renameheadopt->usre_company_label->set_style_text_letter_space(g_RenameInfo.layout.detail[1].TextLetterSpace*680/1024,0);
    renameheadopt->usre_company_label->txt_align(g_RenameInfo.layout.detail[1].HorizontalAlign);
    renameheadopt->usre_company_label->set_style_text_font(renameopt->myfont1,0);
    renameheadopt->usre_company_label->set_pos(g_RenameInfo.layout.detail[1].ElePointX*680/1024,g_RenameInfo.layout.detail[1].ElePointY*680/1024);
    renameheadopt->usre_company_label->set_size(g_RenameInfo.layout.detail[1].EleWidth*680/1024,g_RenameInfo.layout.detail[1].EleHeight*680/1024);//*1024/680

    renameheadopt->usre_param_label->set_style_text_letter_space(g_RenameInfo.layout.detail[0].TextLetterSpace*680/1024,0);
    renameheadopt->usre_param_label->txt_align(g_RenameInfo.layout.detail[0].HorizontalAlign);
    renameheadopt->usre_param_label->set_style_text_font(renameopt->myfont0,0);
    renameheadopt->usre_param_label->set_pos(g_RenameInfo.layout.detail[0].ElePointX*680/1024,g_RenameInfo.layout.detail[0].ElePointY*680/1024);
    renameheadopt->usre_param_label->set_size(g_RenameInfo.layout.detail[0].EleWidth*680/1024,g_RenameInfo.layout.detail[0].EleHeight*680/1024);
    //LV_LOG_USER("---------------------------------");

    param_state_hide = 0;
    company_state_hide = 0;
    duty_state_hide = 0;
    param_state = 3;
    //LV_LOG_USER("aaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    renameinpuopt->clean_flag_dropdwon();

    renameeffectopt->change_font_size_and_between_auto(1,3);
    renameeffectopt->change_font_size_and_between_auto(2,3);
    renameeffectopt->change_font_size_and_between_auto(3,3);

    //update
    uint8_t color[3]={0};
    color_setopt->hexStringToByte(color,g_RenameInfo.layout.BgColor,strlen(g_RenameInfo.layout.BgColor));
    renamebottomopt->select_rgb_bg->set_main_bg_color(lv_color_make(color[0],color[1],color[2]),LV_OPA_100);//单色
    renameheadopt->mscreen->set_main_bg_color(lv_color_make(color[0],color[1],color[2]),LV_OPA_100);

    if(strcmp(g_RenameInfo.layout.BgImg,S_1_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(0);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,S_2_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(1);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,S_3_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(2);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,S_4_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(3);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,S_5_PNG)==0)
    {
        renamebottomopt->select_photo_bg->set_selected(4);//底图
    }
    else if(strcmp(g_RenameInfo.layout.BgImg,"temp.png")==0)
    {
        renamebottomopt->select_photo_bg->set_selected(6);//底图
    }
    else
    {
        renamebottomopt->select_photo_bg->set_selected(5);//底图
    }

    if(strcmp(g_RenameInfo.layout.BgImg,"未使用")!=0 && strlen(g_RenameInfo.layout.BgImg)!=0)
    {
        pthread_mutex_lock(&decodelock);
        if(idcard!=nullptr)
        {
            free_image(idcard);
            idcard = nullptr;
        }

        char imgPath[FILE_PATH_LONG];
        memset(imgPath,0,FILE_PATH_LONG);
        sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,g_RenameInfo.layout.BgImg);
        idcard = resize_image(imgPath,680,400);
        pthread_mutex_unlock(&decodelock);

        renameheadopt->mscreen->set_main_bg_img_src(idcard);
        renamebottomopt->select_rgb_bg->set_main_bg_img_src(DUTY_SIGN_TMP);
        if(idcard_big!=nullptr)
        {
            free_image(idcard_big);
            idcard_big = nullptr;
        }
    }
    else
    {
        renamebottomopt->select_rgb_bg->set_main_bg_img_src(NULL);
        renameheadopt->mscreen->set_main_bg_img_src(NULL);
        if(idcard!=nullptr)
        {
            free_image(idcard);
            idcard = nullptr;
        }
    }

    renameheadopt->usre_param_label->show(true);
    renameheadopt->usre_param_label->txt_color(renameopt->label_dsc0.color,0);
    renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);

    renameheadopt->usre_company_label->show(true);
    renameheadopt->usre_company_label->txt_color(renameopt->label_dsc1.color,0);
    renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);

    renameheadopt->usre_duty_label->show(true);
    renameheadopt->usre_duty_label->txt_color(renameopt->label_dsc2.color,0);
    renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_100);


    renameinpuopt->usre_param->set_main_bg_img_src(NULL);
    renameinpuopt->usre_param->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);

    renameinpuopt->usre_company->set_main_bg_img_src(NULL);
    renameinpuopt->usre_company->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);

    renameinpuopt->usre_duty->set_main_bg_img_src(NULL);
    renameinpuopt->usre_duty->set_main_bg_color(lv_color_hex(0x87CEFA),LV_OPA_100);

    renameinpuopt->input_pos_update();
    renameinpuopt->show_input_param(1);
    renameinpuopt->show_input_param(2);
    renameinpuopt->show_input_param(3);
    renameheadopt->param_change(param_state);
    color_setopt->get_rgb_vlaue(param_state);

    renameinpuopt->rename_button->clicked_enable(false);
    renameinpuopt->font_w_up->clicked_enable(false);
    renameinpuopt->font_W_down->clicked_enable(false);
    renameinpuopt->font_x_up->clicked_enable(false);
    renameinpuopt->font_x_down->clicked_enable(false);
    renameinpuopt->font_y_up->clicked_enable(false);
    renameinpuopt->font_y_down->clicked_enable(false);
    renameinpuopt->font_h_up->clicked_enable(false);
    renameinpuopt->font_h_down->clicked_enable(false);
    renameeffectopt->font_size_up->clicked_enable(false);
    renameeffectopt->font_size_down->clicked_enable(false);
    renameeffectopt->font_between_up->clicked_enable(false);
    renameeffectopt->font_between_down->clicked_enable(false);

}
void RenamefontsetScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenamefontsetScreen* opt = (RenamefontsetScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target==renamfontsetwinopt->mscreen->myobj)
    {  
        if(event->code == LV_EVENT_PRESSING)
        {

            lv_obj_t* obj = lv_event_get_target(event); //获取事件产生的对象
            lv_indev_t* indev = lv_indev_get_act();  //获取活动界面输入设备
            lv_point_t vect;
            lv_indev_get_vect(indev, &vect); //获取vect point
            lv_coord_t x = lv_obj_get_x(obj) + vect.x; //计算x
            lv_coord_t y = lv_obj_get_y(obj) + vect.y; // 计算y
            lv_obj_set_pos(obj, x, y); //移动对象到x,y
        }
        else if(event->code == LV_EVENT_PRESSED)
        {
            renamfontsetwinopt->mscreen->move_foreground();
        }
    }
    //font size set
    else if(target == renamfontsetwinopt->font_W_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_w->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);

                renamfontsetwinopt->font_w->set_txt(rgb_input_num);
                renamfontsetwinopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_w->set_txt(rgb_input_num);
                    renamfontsetwinopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
            }
        }

    }

    else if(target == renamfontsetwinopt->font_w_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_w->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 1024)
                {
                    rgb_num = 1024;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_w->set_txt(rgb_input_num);
                renamfontsetwinopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 1024)
                    {
                        rgb_num = 1024;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_w->set_txt(rgb_input_num);
                    renamfontsetwinopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
            }
        }

    }

    //font_h
    else if(target == renamfontsetwinopt->font_h_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_h->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_h->set_txt(rgb_input_num);
                renamfontsetwinopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_h->set_txt(rgb_input_num);
                    renamfontsetwinopt->font_change_style(param_state);
                }

            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
            }
        }

    }

    else if(target == renamfontsetwinopt->font_h_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_h->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 600)
                {
                    rgb_num = 600;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_h->set_txt(rgb_input_num);
                renamfontsetwinopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 600)
                    {
                        rgb_num = 600;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_h->set_txt(rgb_input_num);
                    renamfontsetwinopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
            }
        }

    }

    //font_x
    else if(target == renamfontsetwinopt->font_x_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_x->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_x->set_txt(rgb_input_num);
                renamfontsetwinopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_x->set_txt(rgb_input_num);
                    renamfontsetwinopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
            }
        }

    }

    else if(target == renamfontsetwinopt->font_x_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_x->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 1024)
                {
                    rgb_num = 1024;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_x->set_txt(rgb_input_num);
                renamfontsetwinopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 1024)
                    {
                        rgb_num = 1024;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_x->set_txt(rgb_input_num);
                    renamfontsetwinopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
            }
        }
    }

    //font_y
    else if(target == renamfontsetwinopt->font_y_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_y->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_y->set_txt(rgb_input_num);
                renamfontsetwinopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_y->set_txt(rgb_input_num);
                    renamfontsetwinopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
            }
        }

    }

    else if(target == renamfontsetwinopt->font_y_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_y->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 600)
                {
                    rgb_num = 600;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_y->set_txt(rgb_input_num);
                renamfontsetwinopt->font_change_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 600)
                    {
                        rgb_num = 600;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_y->set_txt(rgb_input_num);
                    renamfontsetwinopt->font_change_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
            }
        }

    }

    //font_size
    else if(target == renamfontsetwinopt->font_size_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_size->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_size->set_txt(rgb_input_num);
                renamfontsetwinopt->change_font_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_size->set_txt(rgb_input_num);
                    renamfontsetwinopt->change_font_style(param_state);

                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;

            }
        }

    }

    else if(target == renamfontsetwinopt->font_size_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_size->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 1024)
                {
                    rgb_num = 1024;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_size->set_txt(rgb_input_num);
                renamfontsetwinopt->change_font_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 1024)
                    {
                        rgb_num = 1024;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_size->set_txt(rgb_input_num);
                    renamfontsetwinopt->change_font_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
            }
        }

    }

    //font_between
    else if(target == renamfontsetwinopt->font_between_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_between->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_between->set_txt(rgb_input_num);
                renamfontsetwinopt->change_font_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_between->set_txt(rgb_input_num);
                    renamfontsetwinopt->change_font_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                state =0;
            }
        }

    }

    else if(target == renamfontsetwinopt->font_between_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(renamfontsetwinopt->font_between->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 1000)
                {
                    rgb_num = 1000;
                }
                sprintf(rgb_input_num,"%d",rgb_num);
                renamfontsetwinopt->font_between->set_txt(rgb_input_num);
                renamfontsetwinopt->change_font_style(param_state);
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 1000)
                    {
                        rgb_num = 1000;
                    }
                    sprintf(rgb_input_num,"%d",rgb_num);
                    renamfontsetwinopt->font_between->set_txt(rgb_input_num);
                    renamfontsetwinopt->change_font_style(param_state);
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 state =0;
            }
        }

    }
    else if(target == renamfontsetwinopt->change_refont_style->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            if(param_state == 1 && param_state_hide == 1)
            {
                //LV_LOG_USER("1hide");
            }
            if(param_state == 2 && company_state_hide == 1)
            {
                //LV_LOG_USER("2hide");
            }
            if(param_state == 3 && duty_state_hide == 1)
            {
                //LV_LOG_USER("3hide");
            }
            else
            {
                renamfontsetwinopt->change_font_name(param_state);
            }
        }
    }
    else if(target == renamfontsetwinopt->change_font_alignment->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            if(param_state == 1 && param_state_hide == 1)
            {
                //LV_LOG_USER("1hide");
            }
            if(param_state == 2 && company_state_hide == 1)
            {
                //LV_LOG_USER("2hide");
            }
            if(param_state == 3 && duty_state_hide == 1)
            {
                //LV_LOG_USER("3hide");
            }
            else
            {
                renamfontsetwinopt->change_font_style(param_state);
            }
        }
    }
    else if(target == renamfontsetwinopt->change_refont_form->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            ///
            if(param_state == 1 && param_state_hide == 1)
            {
                //LV_LOG_USER("1hide");
            }
            if(param_state == 2 && company_state_hide == 1)
            {
                //LV_LOG_USER("2hide");
            }
            if(param_state == 3 && duty_state_hide == 1)
            {
                //LV_LOG_USER("3hide");
            }
            else
            {
                renamfontsetwinopt->change_font_style(param_state);
            }
        }
    }
    /*
    else if(target == renamfontsetwinopt->change_font_color->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            if(event->code == LV_EVENT_VALUE_CHANGED)
            {
                renamfontsetwinopt->manual_font_color(param_state);
            }
            else if(event->code == LV_EVENT_CLICKED)
            {
                color_setopt->mscreen->show(true);
            }
        }
    }*/

    else if(target == renamfontsetwinopt->color_win->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            color_setopt->mscreen->show(true);
        }
    }
    else if(target == renamfontsetwinopt->del_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            renamfontsetwinopt->mscreen->show(false);
        }
    }
    else if(target == renamfontsetwinopt->ok_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);

            renamfontsetwinopt->mscreen->show(false);
        }
    }
}

//box
RenameboxtScreen::RenameboxtScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(mparent);//lv_layer_top()
    //mscreen->set_bg_color(lv_color_hex(0x222222),LV_OPA_40);
    mscreen->set_size(300,200);
    mscreen->set_pos(300,180);
    mscreen->set_main_radius(10);
    mscreen->set_main_border(5,lv_color_white(),LV_OPA_100);
    mscreen->set_main_bg_color(lv_color_hex(0xE0E0E0),LV_OPA_100);
    mparent = mscreen->get_screen();
    renameboxopt = this;
    initial();
}

RenameboxtScreen::~RenameboxtScreen()
{
    if(ok_button != nullptr)
    {
        delete ok_button;
        ok_button = NULL;
    }
    if(del_button != nullptr)
    {
        delete del_button;
        del_button = NULL;
    }
    if(tip_label != nullptr)
    {
        delete tip_label;
        tip_label = NULL;
    }

    if(mscreen != nullptr)
    {
        delete mscreen;
        mscreen = NULL;
    }
}

void RenameboxtScreen::initial()
{
    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }
   if(ok_button == nullptr)
   {
       ok_button = new LvcppButton(mparent);
       ok_button->set_pos(32,130);
       ok_button->set_size(100,50);
       ok_button->add_txt("显示");
       ok_button->txt_font_size(25,0);
       ok_button->txt_align(LV_ALIGN_CENTER,0,0);
       ok_button->set_style_text_font(myfont->font(),0);
       ok_button->set_main_radius(10);
       ok_button->txt_color(lv_color_black());
       ok_button->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
       ok_button->set_main_bg_color(lv_color_white(),LV_OPA_80);
       ok_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
   }
   if(del_button == nullptr)
   {
       del_button = new LvcppButton(mparent);
       del_button->set_pos(160,130);
       del_button->set_size(100,50);
       del_button->add_txt("退出");
       del_button->txt_font_size(25,0);
       del_button->txt_align(LV_ALIGN_CENTER,0,0);
       del_button->set_style_text_font(myfont->font(),0);
       del_button->set_main_radius(10);
       del_button->txt_color(lv_color_black());
       del_button->set_main_border(3,lv_color_hex(0x444444),LV_OPA_100);
       del_button->set_main_bg_color(lv_color_white(),LV_OPA_80);
       del_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
   }

   if(tip_label == NULL)
   {
       tip_label = new LvcppLabel(mparent);
       tip_label->set_txt("显示：进入预览模式\n退出：回到设置界面");
       tip_label->set_pos(40,50);
       tip_label->set_size(220,120);
       tip_label->txt_align(LV_TEXT_ALIGN_CENTER);
       tip_label->set_style_text_font(myfont->font(),0);
       tip_label->txt_font_size(20,0);
       tip_label->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
   }

}

void RenameboxtScreen::BgraToRgb(uint8_t *bgraData,int width,int height,uint8_t*rgbData)
{
    uint8_t bgrData[width*height*3];
    memset(bgrData,0,sizeof(bgrData));
    for(int i=0,j=0; j<width * height*4; i+=3,j+=4)
    {
        bgrData[i] = bgraData[j];
        bgrData[i+1] = bgraData[j+1];
        bgrData[i+2] = bgraData[j+2];
    }
    for(int n=0,m=0; n < width * height; n++,m+=3){
        uint8_t b_value = bgrData[m];
        uint8_t g_value = bgrData[m+1];
        uint8_t r_value = bgrData[m+2];
        *rgbData++ = r_value;
        *rgbData++ = g_value;
        *rgbData++ = b_value;
     }
}

void RenameboxtScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenameboxtScreen* opt = (RenameboxtScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==renameboxopt->ok_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {

            color_setopt->mscreen->show(false);
            renamfontsetwinopt->mscreen->show(false);
            renameboxopt->mscreen->show(false);

            renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);


        }
    }
    else if(target==renameboxopt->del_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            key_right_tmp = 0;
            if(renameboxopt->mscreen != NULL)
            {
                renameboxopt->mscreen->show(false);

                //LV_LOG_USER("00000000000000  %d %d",g_RenameInfo.layout.detail[0].ElePointX,g_RenameInfo.layout.detail[0].ElePointY);
                //LV_LOG_USER("11111111111111  %d %d",g_RenameInfo.layout.detail[1].ElePointX,g_RenameInfo.layout.detail[1].ElePointY);
                //LV_LOG_USER("22222222222222  %d %d",g_RenameInfo.layout.detail[2].ElePointX,g_RenameInfo.layout.detail[2].ElePointY);

                 renameheadopt->mscreen->set_size(680,400);
                 renameheadopt->mscreen->set_pos(5,5);
                  /*
                 if(tmp_view == 1)
                 {

                     tmp_view = 0;
                 }*/
                 //LV_LOG_USER("!!!!!!!!!!!!!!!!!!!Parameter_reduction !!!!!!!!!!!!!!!!");
                 renameheadopt->Parameter_reduction();
                 if(renameopt->re_color != NULL)
                 {
                     //LV_LOG_USER("hide color ");
                     color_setopt->mscreen->show(false);
                 }

                 if(renameopt->re_fontset != NULL)
                 {
                     //LV_LOG_USER("hide font");
                     renamfontsetwinopt->mscreen->show(false);
                 }

                 if(renameopt->re_box != NULL)
                 {
                     //LV_LOG_USER("hide font");
                     renameboxopt->mscreen->show(false);
                 }

                 renameheadopt->usre_param_label->clicked_enable(false);
                 renameheadopt->usre_duty_label->clicked_enable(false);
                 renameheadopt->usre_company_label->clicked_enable(false);

                 char imgPath[FILE_PATH_LONG]={0};
                 //LV_LOG_USER("renamebottomopt->select_photo_bg->get_selected() = %d",renamebottomopt->select_photo_bg->get_selected());
                 if(renamebottomopt->select_photo_bg->get_selected() != 5)
                 {
                     renamebottomopt->select_photo_bg->get_selected_str(g_RenameInfo.layout.BgImg,sizeof(g_RenameInfo.layout.BgImg));
                     memset(imgPath,0,FILE_PATH_LONG);
                     pthread_mutex_lock(&decodelock);
                     if(renamebottomopt->select_photo_bg->get_selected() == 0)
                     {
                         sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_1_PNG);
                     }
                     else if(renamebottomopt->select_photo_bg->get_selected() == 1)
                     {
                         sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_2_PNG);
                     }
                     else if(renamebottomopt->select_photo_bg->get_selected() == 2)
                     {
                         sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_3_PNG);
                     }
                     else if(renamebottomopt->select_photo_bg->get_selected() == 3)
                     {
                         sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_4_PNG);
                     }
                     else if(renamebottomopt->select_photo_bg->get_selected() == 4)
                     {
                         sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,S_5_PNG);
                     }
                     else
                     {
                         sprintf(imgPath,"%s",TEMP_PATH);
                     }

                     if(idcard!=nullptr)
                     {
                         free_image(idcard);
                         idcard = nullptr;
                     }

                     idcard = resize_image(imgPath,680,400);

                     pthread_mutex_unlock(&decodelock);
                     //LV_LOG_USER("!!!!!!!!!!!!!!!!!imgPath =%s",imgPath);
                     renameheadopt->mscreen->set_main_bg_img_src(idcard);
                     if(idcard_big!=nullptr)
                     {
                         free_image(idcard_big);
                         idcard_big = nullptr;
                     }

                     if(param_state == 1)
                     {
                         renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_100);
                     }
                     else if(param_state == 2)
                     {
                         renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_100);
                     }
                     else if(param_state == 3)
                     {
                         renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_100);
                     }



                 }
            }
        }
    }
}


//bg调色板

RenamebgcolorScreen::RenamebgcolorScreen(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);//
    mscreen->set_bg_color(lv_color_hex(0xACACAC),LV_OPA_100);
    mscreen->set_size(330,345);
    mscreen->set_pos(690,80);
    mscreen->set_main_radius(10);
    mscreen->set_main_border(2,lv_color_hex(0x0000CC),LV_OPA_100);
    mparent = mscreen->get_screen();
    bg_color_setopt = this;
    initial();
    save_r = atoi(font_R->get_txt());
    save_g = atoi(font_G->get_txt());
    save_b = atoi(font_B->get_txt());
    //lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE );
    mscreen->add_flag(LV_OBJ_FLAG_CLICKABLE);
    mscreen->clear_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    mscreen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    mscreen->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
    mscreen->add_event_cb(textarea_event_hander,LV_EVENT_PRESSED,this);
}

RenamebgcolorScreen::~RenamebgcolorScreen()
{
    if(color_tip != NULL)
    {
        delete color_tip;
        color_tip = NULL;
    }
    if(color_line != NULL)
    {
        delete color_line;
        color_line = NULL;
    }
    if(red_color != NULL)
    {
        delete red_color;
        red_color = NULL;
    }
    if(orange_color != NULL)
    {
        delete orange_color;
        orange_color = NULL;
    }
    if(yellow_color != NULL)
    {
        delete yellow_color;
        yellow_color = NULL;
    }
    if(green_color != NULL)
    {
        delete green_color;
        green_color = NULL;
    }
    if(blue_color != NULL)
    {
        delete blue_color;
        blue_color = NULL;
    }
    if(cyan_color != NULL)
    {
        delete cyan_color;
        cyan_color = NULL;
    }
    if(purple_color != NULL)
    {
        delete purple_color;
        purple_color = NULL;
    }
    if(black_color != NULL)
    {
        delete black_color;
        black_color = NULL;
    }
    if(white_color != NULL)
    {
        delete white_color;
        white_color = NULL;
    }
    if(slide_canvas != NULL)
    {
        delete slide_canvas;
        slide_canvas = NULL;
    }
    if(canvas != NULL)
    {
        delete canvas;
        canvas = NULL;
    }
    if(font_R != NULL)
    {
        delete font_R;
        font_R = NULL;
    }
    if(font_R_up != NULL)
    {
        delete font_R_up;
        font_R_up = NULL;
    }
    if(font_R_down != NULL)
    {
        delete font_R_down;
        font_R_down = NULL;
    }
    if(font_R_tip != NULL)
    {
        delete font_R_tip;
        font_R_tip = NULL;
    }
    if(font_G != NULL)
    {
        delete font_G;
        font_G = NULL;
    }
    if(font_G_up != NULL)
    {
        delete font_G_up;
        font_G_up = NULL;
    }
    if(font_G_down != NULL)
    {
        delete font_G_down;
        font_G_down = NULL;
    }
    if(font_G_tip != NULL)
    {
        delete font_G_tip;
        font_G_tip = NULL;
    }
    if(font_B != NULL)
    {
        delete font_B;
        font_B = NULL;
    }
    if(font_B_up != NULL)
    {
        delete font_B_up;
        font_B_up = NULL;
    }
    if(font_B_down != NULL)
    {
        delete font_B_down;
        font_B_down = NULL;
    }
    if(font_B_tip != NULL)
    {
        delete font_B_tip;
        font_B_tip = NULL;
    }
    if(now_color_tip != NULL)
    {
        delete now_color_tip;
        now_color_tip = NULL;
    }
    if(now_color_show != NULL)
    {
        delete now_color_show;
        now_color_show = NULL;
    }
    if(ok_button != NULL)
    {
        delete ok_button;
        ok_button = NULL;
    }
    if(del_button != NULL)
    {
        delete del_button;
        del_button = NULL;
    }
    if(mscreen != NULL)
    {
        delete mscreen;
        mscreen = NULL;
    }
}

lv_color_t* RenamebgcolorScreen::create_canvas(void)
{
    static lv_color_t buf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(150, 150)];//分配buf存放画板数据
    if(canvas==nullptr)
    {
        canvas =new LvcppCanvas(mparent);
    }
    canvas->set_size(150,150);
    canvas->set_buffer(buf, 150, 150, LV_IMG_CF_TRUE_COLOR);//设置画板空间
    canvas->set_pos(10,86);
    int r,g,b;

    for(int x=0;x<150;x++)
    {
        for(int y=0;y<150;y++)
        {
            r = canvas_r;
            g = x*255/150;
            b = y*255/150;
            if(y%10 == 0 && x%10 == 0)
            {
                //LV_LOG_USER("b = %d",b);
            }
            canvas->set_px_color(x,y,lv_color_make(r,g,b));
        }
    }

    canvas->set_main_border(2,lv_color_black(),LV_OPA_100);
    canvas->add_flag(LV_OBJ_FLAG_CLICKABLE);
    canvas->add_event_cb(textarea_event_hander,LV_EVENT_ALL,this);
    lv_draw_img_dsc_init(&img_draw_dsc);
    return buf;
}

void RenamebgcolorScreen::canvas_reset(int type)
{
    if(canvas==nullptr)
    {
        return;
    }
    int r,g,b;
    color_type=type;
    if(type==0)
    {
        for(int x=0;x<150;x++)
        {
            for(int y=0;y<150;y++)
            {
                r = canvas_r;
                g = x*255/150;
                b = y*255/150;
                if(y%10 == 0 && x%10 == 0)
                {
                    //LV_LOG_USER("b = %d",b);
                }
                canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
        }
    }
    else if(type==1)
    {
        for(int x=0;x<150;x++)
        {
            for(int y=0;y<150;y++)
            {
                r = x*255/150;
                g = canvas_g;
                b = y*255/150;
                if(y%10 == 0 && x%10 == 0)
                {
                    //LV_LOG_USER("b = %d",b);
                }
                canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
        }
    }
    else if(type==2)
    {
        for(int x=0;x<150;x++)
        {
            for(int y=0;y<150;y++)
            {
                r = x*255/150;
                g = y*255/150;
                b = canvas_b;
                if(y%10 == 0 && x%10 == 0)
                {
                    //LV_LOG_USER("b = %d",b);
                }
                canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
        }
    }
}

lv_color_t* RenamebgcolorScreen::create_slide_canvas(void)
{
    static lv_color_t slidebuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(310, 40)];//分配buf存放画板数据
    if(slide_canvas==nullptr)
    {
        slide_canvas =new LvcppCanvas(mparent);
    }
    slide_canvas->set_size(310,40);
    slide_canvas->set_buffer(slidebuf, 310, 40, LV_IMG_CF_TRUE_COLOR);//设置画板空间
    slide_canvas->align_to(canvas->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,10);
    int r,g,b;

    for(int x=0;x<310;x++)
    {
        for(int y=0;y<40;y++)
        {
            if(x<(310/3))
            {
                r = x*255/(310/3);
                g = 0;
                b = 0;
                slide_canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
            else if(x<(310/3*2))
            {
                r = 0;
                g = (x-(310/3))*255/(310/3);
                b = 0;
                slide_canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
            else
            {
                r = 0;
                g = 0;
                b = (x-(310/3*2))*255/(310/3);
                slide_canvas->set_px_color(x,y,lv_color_make(r,g,b));
            }
        }
    }

    slide_canvas->set_main_border(2,lv_color_black(),LV_OPA_100);
    slide_canvas->add_flag(LV_OBJ_FLAG_CLICKABLE);
    slide_canvas->add_event_cb(textarea_event_hander,LV_EVENT_ALL,this);
    lv_draw_img_dsc_init(&img_draw_dsc);
    return slidebuf;
}

void RenamebgcolorScreen::initial()
{
    create_canvas();
    //create_slide_canvas();

    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(24,0);
    }
    if(color_tip == nullptr)
    {
        color_tip = new LvcppLabel(mparent);
        color_tip->set_pos(0,0);
        color_tip->set_size(328,40);
        color_tip->set_style_text_font(myfont->font(),0);
        color_tip->txt_font_size(25,0);
        color_tip->set_main_bg_color(lv_color_hex(0x7D7D7D),LV_OPA_100);
        color_tip->set_txt("背景颜色");
        color_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        color_tip->txt_color(lv_color_white(),0);
    }
    if(color_line == nullptr)
    {
        color_line = new LvcppLabel(mparent);
        color_line->set_txt("");
        color_line->set_pos(0,40);
        color_line->set_size(340,1);
        color_line->set_main_bg_color(lv_color_hex(0xFFFFFF),LV_OPA_0);
        color_line->set_main_border(2,lv_color_hex(0x404040),LV_OPA_100);
    }

    if(red_color == nullptr)
    {
        red_color = new LvcppButton(mparent);
        red_color->set_pos(10,45);
        red_color->set_size(30,30);
        red_color->add_txt("");
        red_color->txt_font_size(25,0);
        red_color->txt_align(LV_ALIGN_CENTER,0,0);
        red_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        red_color->set_main_bg_color(lv_color_hex(0xFF00000),LV_OPA_100);
        red_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

    if(orange_color == nullptr)
    {
        orange_color = new LvcppButton(mparent);
        orange_color->align_to(red_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        orange_color->set_size(30,30);
        orange_color->add_txt("");
        orange_color->txt_font_size(25,0);
        orange_color->txt_align(LV_ALIGN_CENTER,0,0);
        orange_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        orange_color->set_main_bg_color(lv_color_hex(0xFF8000),LV_OPA_100);
        orange_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(yellow_color == nullptr)
    {
        yellow_color = new LvcppButton(mparent);
        yellow_color->align_to(orange_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        yellow_color->set_size(30,30);
        yellow_color->add_txt("");
        yellow_color->txt_font_size(25,0);
        yellow_color->txt_align(LV_ALIGN_CENTER,0,0);
        yellow_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        yellow_color->set_main_bg_color(lv_color_hex(0xFFFF00),LV_OPA_100);
        yellow_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(green_color == nullptr)
    {
        green_color = new LvcppButton(mparent);
        green_color->align_to(yellow_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        green_color->set_size(30,30);
        green_color->add_txt("");
        green_color->txt_font_size(25,0);
        green_color->txt_align(LV_ALIGN_CENTER,0,0);
        green_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        green_color->set_main_bg_color(lv_color_hex(0x00FF00),LV_OPA_100);
        green_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(blue_color == nullptr)
    {
        blue_color = new LvcppButton(mparent);
        blue_color->align_to(green_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        blue_color->set_size(30,30);
        blue_color->add_txt("");
        blue_color->txt_font_size(25,0);
        blue_color->txt_align(LV_ALIGN_CENTER,0,0);
        blue_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        blue_color->set_main_bg_color(lv_color_hex(0x0000FF),LV_OPA_100);
        blue_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(cyan_color == nullptr)
    {
        cyan_color = new LvcppButton(mparent);
        cyan_color->align_to(blue_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        cyan_color->set_size(30,30);
        cyan_color->add_txt("");
        cyan_color->txt_font_size(25,0);
        cyan_color->txt_align(LV_ALIGN_CENTER,0,0);
        cyan_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        cyan_color->set_main_bg_color(lv_color_hex(0x00FFFF),LV_OPA_100);
        cyan_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(purple_color == nullptr)
    {
        purple_color = new LvcppButton(mparent);
        purple_color->align_to(cyan_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        purple_color->set_size(30,30);
        purple_color->add_txt("");
        purple_color->txt_font_size(25,0);
        purple_color->txt_align(LV_ALIGN_CENTER,0,0);
        purple_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        purple_color->set_main_bg_color(lv_color_hex(0xFF00FF),LV_OPA_100);
        purple_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(black_color == nullptr)
    {
        black_color = new LvcppButton(mparent);
        black_color->align_to(purple_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        black_color->set_size(30,30);
        black_color->add_txt("");
        black_color->txt_font_size(25,0);
        black_color->txt_align(LV_ALIGN_CENTER,0,0);
        black_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        black_color->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
        black_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(white_color == nullptr)
    {
        white_color = new LvcppButton(mparent);
        white_color->align_to(black_color->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-10);
        white_color->set_size(30,30);
        white_color->add_txt("");
        white_color->txt_font_size(25,0);
        white_color->txt_align(LV_ALIGN_CENTER,0,0);
        white_color->set_main_border(3,lv_color_hex(0x7D7D7D),LV_OPA_100);
        white_color->set_main_bg_color(lv_color_hex(0xFFFFFF),LV_OPA_100);
        white_color->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_R_tip == NULL)
    {
        font_R_tip = new LvcppLabel(mparent);
        font_R_tip->set_txt("R");
        font_R_tip->set_pos(173,97);
        font_R_tip->set_size(20,25);
        font_R_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_R_tip->set_style_text_font(myfont->font(),0);
        font_R_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_R_down == nullptr)
    {
        font_R_down = new LvcppButton(mparent);
        font_R_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_R_down->align_to(font_R_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_R_down->set_size(26,35);
        font_R_down->add_txt("-");
        font_R_down->txt_center();
        font_R_down->txt_color(lv_color_white());
        font_R_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_R_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_R_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_R_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_R == NULL)
    {
        font_R = new LvcppLabel(mparent);
        font_R->set_txt("255");
        font_R->align_to(font_R_down->myobj,LV_ALIGN_RIGHT_MID,46,-4);
        font_R->set_size(70,35);
        font_R->set_style_text_font(myfont->font(),0);
        font_R->txt_align(LV_TEXT_ALIGN_CENTER);
        font_R->txt_color(lv_color_white(),0);
        font_R->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        font_R->add_flag(LV_OBJ_FLAG_CLICKABLE);
        font_R->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_R_up == nullptr)
    {
        font_R_up = new LvcppButton(mparent);
        font_R_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_R_up->align_to(font_R->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_R_up->set_size(26,35);
        font_R_up->add_txt("+");
        font_R_up->txt_center();
        font_R_up->txt_color(lv_color_white());
        font_R_up->set_style_text_font(myfont->font(),0);
        font_R_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_R_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_R_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_R_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }


    if(font_G_tip == NULL)
    {
        font_G_tip = new LvcppLabel(mparent);
        font_G_tip->set_txt("G");
        font_G_tip->set_pos(173,138);
        font_G_tip->set_size(20,25);
        font_G_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_G_tip->set_style_text_font(myfont->font(),0);
        font_G_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_G_down == nullptr)
    {
        font_G_down = new LvcppButton(mparent);
        font_G_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_G_down->align_to(font_G_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_G_down->set_size(26,35);
        font_G_down->add_txt("-");
        font_G_down->txt_center();
        font_G_down->txt_color(lv_color_white());
        font_G_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_G_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_G_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_G_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_G == NULL)
    {
        font_G = new LvcppLabel(mparent);
        font_G->set_txt("0");
        font_G->align_to(font_G_down->myobj,LV_ALIGN_RIGHT_MID,20,-4);
        font_G->set_size(70,35);
        font_G->set_style_text_font(myfont->font(),0);
        font_G->txt_align(LV_TEXT_ALIGN_CENTER);
        font_G->txt_color(lv_color_white(),0);
        font_G->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        font_G->add_flag(LV_OBJ_FLAG_CLICKABLE);
        font_G->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_G_up == nullptr)
    {
        font_G_up = new LvcppButton(mparent);
        font_G_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_G_up->align_to(font_G->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_G_up->set_size(26,35);
        font_G_up->add_txt("+");
        font_G_up->txt_center();
        font_G_up->txt_color(lv_color_white());
        font_G_up->set_style_text_font(myfont->font(),0);
        font_G_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_G_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_G_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_G_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }

    if(font_B_tip == NULL)
    {
        font_B_tip = new LvcppLabel(mparent);
        font_B_tip->set_txt("B");
        font_B_tip->set_pos(173,178);
        font_B_tip->set_size(20,25);
        font_B_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        font_B_tip->set_style_text_font(myfont->font(),0);
        font_B_tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
    }
    if(font_B_down == nullptr)
    {
        font_B_down = new LvcppButton(mparent);
        font_B_down->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_B_down->align_to(font_B_tip->myobj,LV_ALIGN_RIGHT_MID,17,-16);
        font_B_down->set_size(26,35);
        font_B_down->add_txt("-");
        font_B_down->txt_center();
        font_B_down->txt_color(lv_color_white());
        font_B_down->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_B_down->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_B_down->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_B_down->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }
    if(font_B == NULL)
    {
        font_B = new LvcppLabel(mparent);
        font_B->set_txt("0");
        font_B->align_to(font_B_down->myobj,LV_ALIGN_RIGHT_MID,20,-4);
        font_B->set_size(70,35);
        font_B->set_style_text_font(myfont->font(),0);
        font_B->txt_align(LV_TEXT_ALIGN_CENTER);
        font_B->txt_color(lv_color_white(),0);
        font_B->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        font_B->add_flag(LV_OBJ_FLAG_CLICKABLE);
        font_B->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(font_B_up == nullptr)
    {
        font_B_up = new LvcppButton(mparent);
        font_B_up->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        font_B_up->align_to(font_B->myobj,LV_ALIGN_RIGHT_MID,10,-12);
        font_B_up->set_size(26,35);
        font_B_up->add_txt("+");
        font_B_up->txt_center();
        font_B_up->txt_color(lv_color_white());
        font_B_up->set_style_text_font(myfont->font(),0);
        font_B_up->set_main_bg_color(lv_color_hex(0x777777),LV_OPA_40);
        font_B_up->add_event_cb(textarea_event_hander,LV_EVENT_PRESSING,this);
       font_B_up->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
       font_B_up->add_event_cb(textarea_event_hander,LV_EVENT_RELEASED,this);
    }


    if(now_color_tip == nullptr)
    {
        now_color_tip = new LvcppLabel(mparent);
        now_color_tip->set_pos(170,212);
        now_color_tip->set_size(100,25);
        now_color_tip->set_style_text_font(myfont->font(),0);
        now_color_tip->txt_font_size(25,0);
        now_color_tip->set_txt("当前选择");
        now_color_tip->txt_align(LV_TEXT_ALIGN_CENTER);
        now_color_tip->txt_color(lv_color_black(),0);
    }
    if(now_color_show == nullptr)
    {
        now_color_show = new LvcppLabel(mparent);
        now_color_show->align_to(now_color_tip->myobj,LV_ALIGN_OUT_RIGHT_MID,25,5);
        now_color_show->set_size(25,25);
        now_color_show->set_style_text_font(myfont->font(),0);
        now_color_show->set_txt("");
        now_color_show->set_main_bg_color(lv_color_hex(0xFF0000),LV_OPA_100);
    }

    if(ok_button == nullptr)
    {
        ok_button = new LvcppButton(mparent);
        ok_button->set_pos(25,280);
        ok_button->set_size(120,40);
        ok_button->add_txt("选择");
        ok_button->txt_font_size(25,0);
        ok_button->txt_align(LV_ALIGN_CENTER,0,0);
        ok_button->set_style_text_font(myfont->font(),0);
        ok_button->set_main_radius(10);
        ok_button->txt_color(lv_color_white());
        ok_button->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        ok_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }
    if(del_button == nullptr)
    {
        del_button = new LvcppButton(mparent);
        del_button->align_to(ok_button->myobj,LV_ALIGN_RIGHT_MID,45,-16);
        del_button->set_size(120,40);
        del_button->add_txt("取消");
        del_button->txt_font_size(25,0);
        del_button->txt_align(LV_ALIGN_CENTER,0,0);
        del_button->set_style_text_font(myfont->font(),0);
        del_button->set_main_radius(10);
        del_button->txt_color(lv_color_white());
        del_button->set_main_bg_color(lv_color_hex(0x222222),LV_OPA_70);
        del_button->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);
    }

}

void RenamebgcolorScreen::auto_rgb_color_palette(void)
{
    int rgb_num;
    int rgb_num1;
    int rgb_num2;
    rgb_num = atoi(font_R->get_txt());
    rgb_num1 = atoi(font_G->get_txt());
    rgb_num2 = atoi(font_B->get_txt());
    now_color_show->set_main_bg_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),LV_OPA_100);

    renameheadopt->mscreen->set_main_bg_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),LV_OPA_100);
    renamebottomopt->select_rgb_bg->set_main_bg_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),LV_OPA_100);


}

void RenamebgcolorScreen::font_rgb_color_palette(void)
{
    int rgb_num;
    int rgb_num1;
    int rgb_num2;
    rgb_num = atoi(font_R->get_txt());
    rgb_num1 = atoi(font_G->get_txt());
    rgb_num2 = atoi(font_B->get_txt());
    //char rgb[10];
    //uint8_t color[3]={0};
    //sprintf(rgb,"%02x%02x%02x",rgb_num,rgb_num1,rgb_num2);


    //hexStringToByte(color,rgb,strlen(rgb));
    //LV_LOG_USER("rgb_num = %d ,rgb_num = %d,rgb_num = %d",rgb_num,rgb_num,rgb_num);
    renameheadopt->mscreen->set_main_bg_color(lv_color_make(rgb_num, rgb_num1,rgb_num2),LV_OPA_100);
    renamebottomopt->select_rgb_bg->set_main_bg_color(lv_color_make(rgb_num,rgb_num1,rgb_num2),LV_OPA_100);
}


//改变bg颜色
void RenamebgcolorScreen::rgb_color_palette(int r,int g,int b)
{
    char font_rgb[10];
    char font_rgb1[10];
    char font_rgb2[10];
    now_color_show->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);
    //itoa(r,font_rgb,10);
    //itoa(g,font_rgb1,10);
    //itoa(b,font_rgb2,10);

    sprintf(font_rgb,"%d",r);
    sprintf(font_rgb1,"%d",g);
    sprintf(font_rgb2,"%d",b);
    font_R->set_txt(font_rgb);
    font_G->set_txt(font_rgb1);
    font_B->set_txt(font_rgb2);
    renameheadopt->mscreen->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);
    renamebottomopt->select_rgb_bg->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);

    renameheadopt->mscreen->set_main_bg_img_src(NULL);
    if(idcard!=nullptr)
    {
        free_image(idcard);
        idcard = nullptr;
    }
    renamebottomopt->select_photo_bg->set_selected(5);
}

uint8_t RenamebgcolorScreen::toByte(char c)
{
    unsigned char value = 0;

    if (c >= '0' && c <= '9')
        value = c - '0';
    else if (c >= 'A' && c <= 'Z')
        value = c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        value = c - 'a' + 10;

    return value;
}

void RenamebgcolorScreen::hexStringToByte(uint8_t *dstByte,const char *srcHexString ,int len)
{
    int index;

    for (int i = 0; i < len; i++){
        index = i * 2;
        dstByte[i] = ((toByte(srcHexString[index]))<<4) | toByte(srcHexString[index+1]);
    }
}

void RenamebgcolorScreen::get_rgb_vlaue(int param)
{
    char font_rgb[10];
    char font_rgb1[10];
    char font_rgb2[10];
    char rgb_value[10];
    int r,g,b;
    uint8_t color[3];
    lv_color_t color_key;
   if(param == 1)
   {
        color_key = lv_obj_get_style_text_color(renameheadopt->usre_param_label->myobj,0);
        sprintf(font_rgb,"%d",color_key.ch.red);
        sprintf(font_rgb1,"%d",color_key.ch.green);
        sprintf(font_rgb2,"%d",color_key.ch.blue);
        font_R->set_txt(font_rgb);
        font_G->set_txt(font_rgb1);
        font_B->set_txt(font_rgb2);
        now_color_show->set_main_bg_color(color_key,LV_OPA_100);
        renameeffectopt->change_font_color->set_main_bg_color(color_key,LV_OPA_100);
   }
   else if(param == 2)
   {
       color_key = lv_obj_get_style_text_color(renameheadopt->usre_company_label->myobj,0);
       sprintf(font_rgb,"%d",color_key.ch.red);
       sprintf(font_rgb1,"%d",color_key.ch.green);
       sprintf(font_rgb2,"%d",color_key.ch.blue);
       font_R->set_txt(font_rgb);
       font_G->set_txt(font_rgb1);
       font_B->set_txt(font_rgb2);
       now_color_show->set_main_bg_color(color_key,LV_OPA_100);
       renameeffectopt->change_font_color->set_main_bg_color(color_key,LV_OPA_100);
   }
   else if(param == 3)
   {
       color_key = lv_obj_get_style_text_color(renameheadopt->usre_duty_label->myobj,0);
       sprintf(font_rgb,"%d",color_key.ch.red);
       sprintf(font_rgb1,"%d",color_key.ch.green);
       sprintf(font_rgb2,"%d",color_key.ch.blue);
       font_R->set_txt(font_rgb);
       font_G->set_txt(font_rgb1);
       font_B->set_txt(font_rgb2);
       now_color_show->set_main_bg_color(color_key,LV_OPA_100);
       renameeffectopt->change_font_color->set_main_bg_color(color_key,LV_OPA_100);
   }
}
void RenamebgcolorScreen::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    RenamebgcolorScreen* opt = (RenamebgcolorScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->canvas->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            lv_point_t point;
            lv_point_t x_point;
            LvcppIndev::get_indev_point(&x_point);
            //LV_LOG_USER("x_point.x = %d ,x_point.y = %d",x_point.x,x_point.y);
            point.x = x_point.x-opt->canvas->pos_x()-opt->mscreen->pos_x();
            point.y = x_point.y-opt->canvas->pos_y()-opt->mscreen->pos_y();
            //LV_LOG_USER("point.x = %d ,point.y = %d",point.x,point.y);
            int r,g,b;
            if(opt->color_type == 0)
            {
                r = opt->canvas_r;
                g = point.x*255/150;
                b = point.y*255/150;
            }
            else if(opt->color_type == 1)
            {
                r = point.x*255/150;
                g = opt->canvas_g;
                b = point.y*255/150;
            }
            else
            {
                r = point.x*255/150;
                g = point.y*255/150;
                b = opt->canvas_b;
            }
            //b = ((point.x)^2+(point.x)^2)*255/150;
            //LV_LOG_USER("r = %d ,g = %d,b = %d",r,g,b);

            //改变画板
            char font_rgb[10];
            char font_rgb1[10];
            char font_rgb2[10];
            opt->now_color_show->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);
            //itoa(r,font_rgb,10);
            //itoa(g,font_rgb1,10);
            //itoa(b,font_rgb2,10);

            sprintf(font_rgb,"%d",r);
            sprintf(font_rgb1,"%d",g);
            sprintf(font_rgb2,"%d",b);
            opt->font_R->set_txt(font_rgb);
            opt->font_G->set_txt(font_rgb1);
            opt->font_B->set_txt(font_rgb2);
            renameheadopt->mscreen->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);
            renamebottomopt->select_rgb_bg->set_main_bg_color(lv_color_make(r,g,b),LV_OPA_100);
            opt->font_rgb_color_palette();
        }
    }
    /*else if(target==opt->slide_canvas->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            lv_point_t point;
            lv_point_t x_point;
            LvcppIndev::get_indev_point(&x_point);
            //LV_LOG_USER("x_point.x = %d ,x_point.y = %d",x_point.x,x_point.y);
            point.x = x_point.x-opt->slide_canvas->pos_x()-opt->mscreen->pos_x();
            point.y = x_point.y-opt->slide_canvas->pos_y()-opt->mscreen->pos_y();
            //LV_LOG_USER("point.x = %d ,point.y = %d",point.x,point.y);
            int r,g,b;

            if(point.x<(310/3))
            {
                r = point.x*255/(310/3);
                g= 0;
                b= 0;
                opt->canvas_r = r;
                opt->canvas_g = g;
                opt->canvas_b = b;
                opt->canvas_reset(0);
            }
            else if(point.x<(310/3*2))
            {
                r = 0;
                g = (point.x-(310/3))*255/(310/3);
                b = 0;
                opt->canvas_r = r;
                opt->canvas_g = g;
                opt->canvas_b = b;
                opt->canvas_reset(1);
            }
            else
            {
                r = 0;
                g = 0;
                b = (point.x-(310/3*2))*255/(310/3);
                opt->canvas_r = r;
                opt->canvas_g = g;
                opt->canvas_b = b;
                opt->canvas_reset(2);
            }
            //改变画板
            opt->rgb_color_palette(r,g,b);
            opt->font_rgb_color_palette();
        }
    }*/
    else if(target==opt->mscreen->myobj)
    {
        if(event->code == LV_EVENT_PRESSING)
        {

            /*
            lv_point_t x_point;
            LvcppIndev::get_indev_point(&x_point);
            //LV_LOG_USER("x_point.x = %d ,x_point.y = %d",x_point.x,x_point.y);
            opt->mscreen->set_pos(x_point.x,x_point.y);*/


            lv_obj_t* obj = lv_event_get_target(event); //获取事件产生的对象
            lv_indev_t* indev = lv_indev_get_act();  //获取活动界面输入设备
            lv_point_t vect;
            lv_indev_get_vect(indev, &vect); //获取vect point
            lv_coord_t x = lv_obj_get_x(obj) + vect.x; //计算x
            lv_coord_t y = lv_obj_get_y(obj) + vect.y; // 计算y
            lv_obj_set_pos(obj, x, y); //移动对象到x,y
        }
        else if(event->code == LV_EVENT_PRESSED)
        {
            opt->mscreen->move_foreground();
        }
    }
    //
    else if(target == opt->red_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0xFF00000),LV_OPA_100);
            opt->font_R->set_txt("255");
            opt->font_G->set_txt("0");
            opt->font_B->set_txt("0");
            opt->auto_rgb_color_palette();
        }
    }
    else if(target == opt->orange_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0xFF8000),LV_OPA_100);
            opt->font_R->set_txt("255");
            opt->font_G->set_txt("128");
            opt->font_B->set_txt("0");
            opt->auto_rgb_color_palette();
        }
    }
    else if(target == opt->yellow_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0xFFFF00),LV_OPA_100);
            opt->font_R->set_txt("255");
            opt->font_G->set_txt("255");
            opt->font_B->set_txt("0");
            opt->auto_rgb_color_palette();
        }
    }
    else if(target == opt->green_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0x00FF00),LV_OPA_100);
            opt->font_R->set_txt("0");
            opt->font_G->set_txt("255");
            opt->font_B->set_txt("0");
            opt->auto_rgb_color_palette();
        }
    }
    else if(target == opt->blue_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0x0000FF),LV_OPA_100);
            opt->font_R->set_txt("0");
            opt->font_G->set_txt("0");
            opt->font_B->set_txt("255");
            opt->auto_rgb_color_palette();
        }
    }
    else if(target == opt->cyan_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0x00FFFF),LV_OPA_100);
            opt->font_R->set_txt("0");
            opt->font_G->set_txt("255");
            opt->font_B->set_txt("255");
            opt->auto_rgb_color_palette();
        }
    }
    else if(target == opt->purple_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0xFF00FF),LV_OPA_100);
            opt->font_R->set_txt("255");
            opt->font_G->set_txt("0");
            opt->font_B->set_txt("255");
            opt->auto_rgb_color_palette();
        }
    }
    else if(target == opt->black_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_100);
            opt->font_R->set_txt("0");
            opt->font_G->set_txt("0");
            opt->font_B->set_txt("0");
            opt->auto_rgb_color_palette();
        }
    }
    else if(target == opt->white_color->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->now_color_show->set_main_bg_color(lv_color_hex(0xFFFFFF),LV_OPA_100);
            opt->font_R->set_txt("255");
            opt->font_G->set_txt("255");
            opt->font_B->set_txt("255");
            opt->auto_rgb_color_palette();
        }
    }


    //rgb  r num show
    else if(target == opt->font_R_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(opt->font_R->get_txt());

            if(event->code == LV_EVENT_PRESSING )
            {
                //LV_LOG_USER("PRESSING");
                state ++ ;
                //LV_LOG_USER("state =%d",state);
                if(state  >= 10)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                        sprintf(rgb_input_num,"%d",rgb_num);
                    opt->font_R->set_txt(rgb_input_num);
                    opt->canvas_r = rgb_num;
                }
            }
            else if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                //LV_LOG_USER("CLICKED");
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                opt->font_R->set_txt(rgb_input_num);
                opt->canvas_r = rgb_num;
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                //LV_LOG_USER("RELEASED");

               opt->auto_rgb_color_palette();
               opt->font_rgb_color_palette();
               opt->canvas_reset(0);
               state = 0;
            }
        }

    }

    else if(target == opt->font_R_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(opt->font_R->get_txt());

            if(event->code == LV_EVENT_PRESSING)
            {
                //LV_LOG_USER("PRESSING");
                state ++ ;
                //LV_LOG_USER("state =%d",state);
                if(state >=10)
                {
                    rgb_num += 5;
                    if(rgb_num >= 255)
                    {
                        rgb_num = 255;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    opt->font_R->set_txt(rgb_input_num);
                    opt->canvas_r = rgb_num;
                }

            }
            else if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                 //LV_LOG_USER("CLICKED");
                rgb_num++;
                if(rgb_num >= 255)
                {
                    rgb_num = 255;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                opt->font_R->set_txt(rgb_input_num);
                opt->canvas_r = rgb_num;
            }
            else if(event->code == LV_EVENT_RELEASED)
            {
                 //LV_LOG_USER("RELEASED");

               opt->auto_rgb_color_palette();
               opt->font_rgb_color_palette();
               opt->canvas_reset(0);
               state = 0;
            }
        }

    }


    //rgb  g num show
    else if(target == opt->font_G_down->myobj )
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(opt->font_G->get_txt());
            if(event->code == LV_EVENT_CLICKED &&state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                opt->font_G->set_txt(rgb_input_num);
                opt->canvas_g = rgb_num;
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                //LV_LOG_USER("PRESSING");
                state ++ ;
                //LV_LOG_USER("state =%d",state);
                if(state  >= 10)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    opt->font_G->set_txt(rgb_input_num);
                    opt->canvas_g = rgb_num;
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {

               opt->auto_rgb_color_palette();
               opt->font_rgb_color_palette();
               opt->canvas_reset(1);
               state =0 ;
            }
        }

    }

    else if(target == opt->font_G_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(opt->font_G->get_txt());
            if(event->code == LV_EVENT_CLICKED &&state == 0)
            {
                rgb_num++;
                if(rgb_num >= 255)
                {
                    rgb_num = 255;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                opt->font_G->set_txt(rgb_input_num);
                opt->canvas_g = rgb_num;
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state++;
                if(state > 5)
                {
                    rgb_num += 5;
                    if(rgb_num >= 255)
                    {
                        rgb_num = 255;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    opt->font_G->set_txt(rgb_input_num);
                    opt->canvas_g = rgb_num;
                }

            }
            else if(event->code == LV_EVENT_RELEASED)
            {

               opt->auto_rgb_color_palette();
               opt->font_rgb_color_palette();
               opt->canvas_reset(1);
               state = 0;
            }
        }

    }

    //rgb  B num show
    else if(target == opt->font_B_down->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(opt->font_B->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num--;
                if(rgb_num <= 0)
                {
                    rgb_num = 0;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                opt->font_B->set_txt(rgb_input_num);
                opt->canvas_b = rgb_num;
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state++;
                if(state > 5)
                {
                    rgb_num -= 5;
                    if(rgb_num <= 0)
                    {
                        rgb_num = 0;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    opt->font_B->set_txt(rgb_input_num);
                    opt->canvas_b = rgb_num;
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {

               opt->auto_rgb_color_palette();
               opt->font_rgb_color_palette();
               opt->canvas_reset(2);
               state = 0;
            }
        }

    }

    else if(target == opt->font_B_up->myobj)
    {
        if(param_state == 1 && param_state_hide == 1)
        {
            //LV_LOG_USER("1hide");
        }
        if(param_state == 2 && company_state_hide == 1)
        {
            //LV_LOG_USER("2hide");
        }
        if(param_state == 3 && duty_state_hide == 1)
        {
            //LV_LOG_USER("3hide");
        }
        else
        {
            int rgb_num;
            char rgb_input_num[10];
            rgb_num = atoi(opt->font_B->get_txt());
            if(event->code == LV_EVENT_CLICKED && state == 0)
            {
                rgb_num++;
                if(rgb_num >= 255)
                {
                    rgb_num = 255;
                }
                //sprintf(rgb_input_num,"%d",rgb_num);
                sprintf(rgb_input_num,"%d",rgb_num);
                opt->font_B->set_txt(rgb_input_num);
                opt->canvas_b = rgb_num;
            }
            else if(event->code == LV_EVENT_PRESSING)
            {
                state ++;
                if(state >10)
                {
                    rgb_num += 5;
                    if(rgb_num >= 255)
                    {
                        rgb_num = 255;
                    }
                    //sprintf(rgb_input_num,"%d",rgb_num);
                    sprintf(rgb_input_num,"%d",rgb_num);
                    opt->font_B->set_txt(rgb_input_num);
                    opt->canvas_b = rgb_num;
                }
            }
            else if(event->code == LV_EVENT_RELEASED)
            {

               opt->auto_rgb_color_palette();
               opt->font_rgb_color_palette();
               opt->canvas_reset(2);
               state = 0;
            }
        }
    }
    else if(target == opt->font_R->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
            opt->canvas_reset(0);
    }
    else if(target == opt->font_G->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
            opt->canvas_reset(1);
    }
    else if(target == opt->font_B->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
            opt->canvas_reset(2);
    }
    else if(target == opt->del_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->mscreen->show(false);
            char r_value[16],g_value[16],b_value[16];
            sprintf(r_value,"%d",opt->save_r);
            opt->font_R->set_txt(r_value);
            sprintf(g_value,"%d",opt->save_g);
            opt->font_G->set_txt(g_value);
            sprintf(b_value,"%d",opt->save_b);
            opt->font_B->set_txt(b_value);
            opt->auto_rgb_color_palette();
            opt->font_rgb_color_palette();
            renameheadopt->mscreen->set_main_bg_color(lv_color_make(opt->save_r, opt->save_g,opt->save_b),LV_OPA_100);
            renamebottomopt->select_rgb_bg->set_main_bg_color(lv_color_make(opt->save_r,opt->save_g,opt->save_b),LV_OPA_100);
        }
    }
    else if(target == opt->ok_button->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            renameheadopt->usre_param_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_company_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            renameheadopt->usre_duty_label->set_main_border(2,lv_color_black(),LV_OPA_0);
            opt->save_r = atoi(opt->font_R->get_txt());
            opt->save_g = atoi(opt->font_G->get_txt());
            opt->save_b = atoi(opt->font_B->get_txt());

            renamebottomopt->select_rgb_bg->set_main_bg_img_src(NULL);
            renameheadopt->mscreen->set_main_bg_img_src(NULL);
            if(idcard!=nullptr)
            {
                free_image(idcard);
                idcard = nullptr;
            }
            renamebottomopt->select_photo_bg->set_selected(5);
            opt->mscreen->show(false);
        }
    }
}

