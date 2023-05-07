#include "frame_user_sence.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
#include  "common/common.h"


void frameUserSence::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    SETTING_FRAME_USERHEAD_PNG=(void*)parse_image_from_file(SETTING_FRAME_USERHEAD_PNG_PATH);
#endif
}

void frameUserSence::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(SETTING_FRAME_USERHEAD_PNG);
#endif
}

frameUserSence::frameUserSence(lv_obj_t* parent)
{
    ui_image_decode();
    frameUser = new LvcppLabel(parent);
    frameUser->set_size(170,96);
    frameUser->set_main_bg_color(lv_color_hex(0x00516a),LV_OPA_0);
    frameUser->set_txt("");
    frameUser->add_flag(LV_OBJ_FLAG_CLICKABLE);

    userBg = new LvcppLabel(frameUser->myobj);
    userBg->set_size(50,50);
    userBg->set_main_bg_img_src(SETTING_FRAME_USERHEAD_PNG);
    userBg->set_main_radius(25);
    userBg->set_main_bg_opa(LV_OPA_0);
    userBg->align(LV_ALIGN_TOP_MID,0,0);
    userBg->set_txt("");

    userName = new LvcppLabel(frameUser->myobj);
    userName->set_size(160,36);
    userName->set_main_bg_opa(LV_OPA_0);
    userName->align(LV_ALIGN_BOTTOM_MID,0,-10);
    userName->txt_color(lv_color_white(),LV_PART_MAIN);
    userName->txt_font_size(26, FT_FONT_STYLE_NORMAL);
    userName->txt_align(LV_TEXT_ALIGN_CENTER);
    userName->txt_long_mode(LV_LABEL_LONG_DOT);
    userName->set_txt("");
}
frameUserSence::~frameUserSence(void)
{
    if(userName != NULL)
    {
        delete userName;
        userName = NULL;
    }
    if(userBg != NULL)
    {
        delete userBg;
        userBg = NULL;
    }
    if(frameUser != NULL)
    {
        delete frameUser;
        frameUser = NULL;
    }
    ui_image_free();
}
void frameUserSence::frameUser_updata_Bg(void* bg_path)
{
    if(bg_path != NULL)
    {
        LV_LOG_USER("frameUser_updata_Bg");
    }
    else
    {
        if(userBg !=NULL)
            userBg->set_main_bg_img_src(SETTING_FRAME_USERHEAD_PNG);
    }
}

void frameUserSence::frameUser_updata_Name(char* Name)
{
    if(userName !=NULL)
        userName->set_txt(Name);
}
