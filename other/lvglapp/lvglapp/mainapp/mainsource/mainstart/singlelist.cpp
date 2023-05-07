#include "singlelist.h"

singlelist::singlelist(lv_obj_t* praent)
{
    me_screen = new LvcppScreen(praent);
    me_screen->set_size(80,125);
    me_screen->set_main_radius(0);
    me_screen->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    me_parent = me_screen->get_screen();
    me_screen->set_main_pad_all(0);
    initial();
}

singlelist::~singlelist()
{
    if(txt_list != nullptr)
    {
        delete txt_list;
        txt_list = nullptr;
    }
}


void singlelist::initial(void)
{
    myfont = new LvcppFreeTypeFont(18,0);
    txt_list = new LvcppButton(me_parent);
    txt_list->set_size(80,125);
    txt_list->txt_align(LV_TEXT_ALIGN_CENTER,0,0);
    txt_list->txt_center();
    txt_list->txt_color(lv_color_hex(0xffffff));
    //txt_list->txt_font_size(40,0);
    txt_list->set_main_pad_all(0);
    //txt_list->set_main_border(1,lv_color_hex(0xffffff),LV_OPA_60);
    txt_list->center_align();
    txt_list->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
}

void singlelist::set_txt(const char * str,int index)
{
    txt_list->add_txt(str);
    if(index == 0)
    {
        txt_list->txt_align(LV_ALIGN_BOTTOM_MID,-10,0);
    }
    else
    {
        txt_list->txt_align(LV_ALIGN_BOTTOM_MID,0,0);
    }
    txt_list->set_style_text_font(myfont->font(),0);
}


void singlelist::set_logo_list(int index,int Hlight)
{
    if(Hlight == 0)
    {
        if(index == 0)
        {
            txt_list->set_main_bg_img_src(RENAME_PNG);
        }
        else if(index == 1)
        {
            txt_list->set_main_bg_img_src(SERVICE_PNG);
        }
        else if(index == 2)
        {
            txt_list->set_main_bg_img_src(ATTENDANCE_PNG);
        }
        else if(index == 3)
        {
            txt_list->set_main_bg_img_src(BALLOT_PNG);
        }
        else if(index == 4)
        {
            txt_list->set_main_bg_img_src(MEETING_PNG);
        }
        else if(index == 5)
        {
            txt_list->set_main_bg_img_src(SPEECH_PNG);
        }
        else if(index == 6)
        {
            txt_list->set_main_bg_img_src(MESSAGE_PNG);
        }
        else if(index == 7)
        {
            txt_list->set_main_bg_img_src(SETTING_PNG);
        }
    }

    else
    {
        if(index == 0)
        {
            txt_list->set_main_bg_img_src(RENAMEH_PNG);
        }
        else if(index == 1)
        {
            txt_list->set_main_bg_img_src(SERVICEH_PNG);
        }
        else if(index == 2)
        {
            txt_list->set_main_bg_img_src(ATTENDANCEH_PNG);
        }
        else if(index == 3)
        {
            txt_list->set_main_bg_img_src(BALLOTH_PNG);
        }
        else if(index == 4)
        {
            txt_list->set_main_bg_img_src(MEETINGH_PNG);
        }
        else if(index == 5)
        {
            txt_list->set_main_bg_img_src(SPEECHH_PNG);
        }
        else if(index == 6)
        {
            txt_list->set_main_bg_img_src(MESSAGEH_PNG);
        }
        else if(index == 7)
        {
            txt_list->set_main_bg_img_src(SETTINGH_PNG);
        }
    }

}
