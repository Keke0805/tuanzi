#include "alarm_info_label.h"

Alarminfo_Label::Alarminfo_Label(lv_obj_t* parent)
{
    alarm_frame_label = new LvcppScreen(parent);
    alarm_frame_label->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    alarm_frame_label->align(LV_ALIGN_TOP_MID,0,0);
    alarm_frame_label->set_main_bg_color(lv_color_black(),LV_OPA_60);
    alarmscreen = alarm_frame_label->myobj;

    alarm_info = new LvcppButton(alarmscreen);
    alarm_info->set_size(650,150);
    alarm_info->align(LV_ALIGN_TOP_LEFT,315,100);
    alarm_info->set_main_pad_all(0);
    alarm_info->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info->set_style_radius(10,0);
    alarm_info->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    alarm_info_frame = alarm_info->myobj;


    textarea = new LvcppTextArea(alarmscreen);
    textarea->set_size(650,50);
    textarea->align(LV_ALIGN_TOP_LEFT,315,110);
    textarea->set_max_length(32);
    textarea->set_one_line(true);
    textarea->set_scrollbar_mode(0);
    textarea->set_password_mode(false);
    textarea->set_text("");
    textarea->set_main_border(0,lv_color_hex(0xffffff),LV_OPA_100);

    alarm_info_line_1 = new LvcppButton(alarm_info_frame);
    alarm_info_line_1->set_size(650,2);
    alarm_info_line_1->align(LV_ALIGN_TOP_LEFT,0,62);
    alarm_info_line_1->set_main_bg_color(lv_color_hex(0xff),LV_OPA_100);

    cancel = new LvcppButton(alarm_info_frame);
    cancel->set_size(300,50);
    cancel->set_main_pad_all(0);
    cancel->align(LV_ALIGN_TOP_LEFT,10,80);
    cancel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    cancel->set_style_radius(10,0);
    cancel->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    cancel->add_txt(STR_CANCEL);
    cancel->txt_center();

    confirm = new LvcppButton(alarm_info_frame);
    confirm->set_size(300,50);
    confirm->align(LV_ALIGN_TOP_RIGHT,-10,80);
    confirm->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    confirm->set_style_radius(10,0);
    confirm->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    confirm->add_txt(STR_OK);
    confirm->txt_center();

    show_keyboard();
}

void Alarminfo_Label::show_keyboard(void)
{
    if(kb == nullptr)
    {
        kb = new LvcppKeyboard(alarmscreen);
    }
    kb->set_textarea(textarea->myobj);
    kb->show(true);
}

void Alarminfo_Label::Alarminfo_Label_delete(void)
{
    if(kb != nullptr)
    {
        delete kb;
        kb= nullptr;
    }
    if(confirm != nullptr)
    {
        delete confirm;
        confirm= nullptr;
    }
    if(cancel != nullptr)
    {
        delete cancel;
        cancel= nullptr;
    }
    if(alarm_info_line_1 != nullptr)
    {
        delete alarm_info_line_1;
        alarm_info_line_1= nullptr;
    }
    if(textarea != nullptr)
    {
        delete textarea;
        textarea= nullptr;
    }
    if(alarm_info != nullptr)
    {
        delete alarm_info;
        alarm_info= nullptr;
    }

    if(alarm_frame_label != nullptr)
    {
        delete alarm_frame_label;
        alarm_frame_label= nullptr;
    }

}

Alarminfo_Label::~Alarminfo_Label(void)
{
    if(confirm != nullptr)
    {
        delete confirm;
        confirm= nullptr;
    }
    if(cancel != nullptr)
    {
        delete cancel;
        cancel= nullptr;
    }
    if(alarm_info_line_1 != nullptr)
    {
        delete alarm_info_line_1;
        alarm_info_line_1= nullptr;
    }
    if(textarea != nullptr)
    {
        delete textarea;
        textarea= nullptr;
    }
    if(alarm_info != nullptr)
    {
        delete alarm_info;
        alarm_info= nullptr;
    }

    if(alarm_frame_label != nullptr)
    {
        delete alarm_frame_label;
        alarm_frame_label= nullptr;
    }
}



