#include "alarm_info_bell.h"
#include  "common/common.h"

void Alarminfo_Bell::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    LIST_CIRCLE_PNG = (void*)parse_image_from_file(LIST_CIRCLE_PNG_PATH);
    LIST_ICON_CHE_PNG = (void*)parse_image_from_file(LIST_ICON_CHE_PNG_PATH);
#endif
}

void Alarminfo_Bell::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(LIST_CIRCLE_PNG);
    free_image(LIST_ICON_CHE_PNG);
#endif
}

Alarminfo_Bell::Alarminfo_Bell(int Song,lv_obj_t* parent)
{
    ui_image_decode();
    memset(&click_bell_statue, 0, sizeof(click_bell_statue_t));
    alarm_frame_bell = new LvcppScreen(parent);
    alarm_frame_bell->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    alarm_frame_bell->align(LV_ALIGN_TOP_MID,0,0);
    alarm_frame_bell->set_main_bg_color(lv_color_black(),LV_OPA_60);
    alarmscreen = alarm_frame_bell->myobj;

    alarm_info = new LvcppButton(alarmscreen);
    alarm_info->set_size(650,630);
    alarm_info->set_main_pad_all(0);
    alarm_info->center_align();
    alarm_info->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info->set_style_radius(10,0);
    alarm_info->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    alarm_info_frame = alarm_info->myobj;

    alarm_info_1 = new LvcppButton(alarm_info_frame);
    alarm_info_1->set_size(650,87);
    alarm_info_1->set_main_pad_all(0);
    alarm_info_1->align(LV_ALIGN_TOP_LEFT,0,0);
    alarm_info_1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_1->set_style_radius(0,0);
    alarm_info_1->txt_color(lv_color_hex(0x000000));
    alarm_info_1->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_1->add_txt(STR_RINGTONE);
    alarm_info_1->txt_center();

    alarm_info_2 = new LvcppButton(alarm_info_frame);
    alarm_info_2->set_size(650,87);
    alarm_info_2->set_main_pad_all(0);
    alarm_info_2->align(LV_ALIGN_TOP_LEFT,0,89);
    alarm_info_2->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_2->set_style_radius(0,0);
    alarm_info_2->txt_color(lv_color_hex(0x000000));
    alarm_info_2->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_2->add_txt(STR_PLATINUM);
    alarm_info_2->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_2->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_3 = new LvcppButton(alarm_info_frame);
    alarm_info_3->set_size(650,87);
    alarm_info_3->set_main_pad_all(0);
    alarm_info_3->align(LV_ALIGN_TOP_LEFT,0,178);
    alarm_info_3->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_3->set_style_radius(0,0);
    alarm_info_3->txt_color(lv_color_hex(0x000000));
    alarm_info_3->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_3->add_txt(STR_ARGON);
    alarm_info_3->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_3->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_4 = new LvcppButton(alarm_info_frame);
    alarm_info_4->set_size(650,87);
    alarm_info_4->set_main_pad_all(0);
    alarm_info_4->align(LV_ALIGN_TOP_LEFT,0,267);
    alarm_info_4->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_4->set_style_radius(0,0);
    alarm_info_4->txt_color(lv_color_hex(0x000000));
    alarm_info_4->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_4->add_txt(STR_CLASSIC);
    alarm_info_4->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_4->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_5 = new LvcppButton(alarm_info_frame);
    alarm_info_5->set_size(650,87);
    alarm_info_5->set_main_pad_all(0);
    alarm_info_5->align(LV_ALIGN_TOP_LEFT,0,356);
    alarm_info_5->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_5->set_style_radius(0,0);
    alarm_info_5->txt_color(lv_color_hex(0x000000));
    alarm_info_5->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_5->add_txt(STR_HELIUM);
    alarm_info_5->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_5->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_line_1 = new LvcppButton(alarm_info_frame);
    alarm_info_line_1->set_size(650,2);
    alarm_info_line_1->align(LV_ALIGN_TOP_LEFT,0,87);
    alarm_info_line_1->set_main_bg_color(lv_color_hex(0x808080),LV_OPA_100);

    alarm_info_line_2 = new LvcppButton(alarm_info_frame);
    alarm_info_line_2->set_size(650,2);
    alarm_info_line_2->align(LV_ALIGN_TOP_LEFT,0,176);
    alarm_info_line_2->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_3 = new LvcppButton(alarm_info_frame);
    alarm_info_line_3->set_size(650,2);
    alarm_info_line_3->align(LV_ALIGN_TOP_LEFT,0,265);
    alarm_info_line_3->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_4 = new LvcppButton(alarm_info_frame);
    alarm_info_line_4->set_size(650,2);
    alarm_info_line_4->align(LV_ALIGN_TOP_LEFT,0,354);
    alarm_info_line_4->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_5 = new LvcppButton(alarm_info_frame);
    alarm_info_line_5->set_size(650,2);
    alarm_info_line_5->align(LV_ALIGN_TOP_LEFT,0,443);
    alarm_info_line_5->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    cancel = new LvcppButton(alarm_info_frame);
    cancel->set_size(300,55);
    cancel->set_main_pad_all(0);
    cancel->align(LV_ALIGN_TOP_LEFT,10,565);
    cancel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    cancel->set_style_radius(10,0);
    cancel->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    cancel->add_txt(STR_CANCEL);
    cancel->txt_center();

    confirm = new LvcppButton(alarm_info_frame);
    confirm->set_size(300,55);
    confirm->align(LV_ALIGN_TOP_RIGHT,-10,565);
    confirm->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    confirm->set_style_radius(10,0);
    confirm->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    confirm->add_txt(STR_OK);
    confirm->txt_center();

    alarm_info_pic1 = new LvcppButton(alarm_info_frame);
    alarm_info_pic1->set_size(32,32);
    alarm_info_pic1->align(LV_ALIGN_TOP_RIGHT,-15,121);
    alarm_info_pic1->set_main_bg_img_src(LIST_CIRCLE_PNG);
    alarm_info_pic1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_pic1->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_pic2 = new LvcppButton(alarm_info_frame);
    alarm_info_pic2->set_size(32,32);
    alarm_info_pic2->align(LV_ALIGN_TOP_RIGHT,-15,210);
    alarm_info_pic2->set_main_bg_img_src(LIST_CIRCLE_PNG);
    alarm_info_pic2->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_pic2->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_pic3 = new LvcppButton(alarm_info_frame);
    alarm_info_pic3->set_size(32,32);
    alarm_info_pic3->align(LV_ALIGN_TOP_RIGHT,-15,299);
    alarm_info_pic3->set_main_bg_img_src(LIST_CIRCLE_PNG);
    alarm_info_pic3->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_pic3->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_pic4 = new LvcppButton(alarm_info_frame);
    alarm_info_pic4->set_size(32,32);
    alarm_info_pic4->align(LV_ALIGN_TOP_RIGHT,-15,388);
    alarm_info_pic4->set_main_bg_img_src(LIST_CIRCLE_PNG);
    alarm_info_pic4->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_pic4->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);
	choose =Song;
	switch(choose)
	{
		case 0:
			alarm_info_pic1->set_main_bg_img_src(LIST_ICON_CHE_PNG);
			break;
		case 1:
			alarm_info_pic2->set_main_bg_img_src(LIST_ICON_CHE_PNG);
			break;
		case 2:
			alarm_info_pic3->set_main_bg_img_src(LIST_ICON_CHE_PNG);
			break;
		case 3:
			alarm_info_pic4->set_main_bg_img_src(LIST_ICON_CHE_PNG);
			break;
		default:
			break;
	}
}

void Alarminfo_Bell::clicked_event_handler(lv_event_t *event)
{
    Alarminfo_Bell* opt = (Alarminfo_Bell*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->alarm_info_2->myobj)
    {
        opt->alarm_info_pic1->set_main_bg_img_src(opt->LIST_ICON_CHE_PNG);
        opt->alarm_info_pic2->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic3->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic4->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->choose =0;
    }

    if(target==opt->alarm_info_3->myobj)
    {
        opt->alarm_info_pic1->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic2->set_main_bg_img_src(opt->LIST_ICON_CHE_PNG);
        opt->alarm_info_pic3->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic4->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->choose =1;
    }

    if(target==opt->alarm_info_4->myobj)
    {
        opt->alarm_info_pic1->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic2->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic3->set_main_bg_img_src(opt->LIST_ICON_CHE_PNG);
        opt->alarm_info_pic4->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->choose =2;
    }

    if(target==opt->alarm_info_5->myobj)
    {
        opt->alarm_info_pic1->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic2->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic3->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
        opt->alarm_info_pic4->set_main_bg_img_src(opt->LIST_ICON_CHE_PNG);
        opt->choose =3;
    }
}

int Alarminfo_Bell::get_info(void)
{
    return choose;
}

Alarminfo_Bell::~Alarminfo_Bell(void)
{
    if(alarm_info_pic4 != nullptr)
    {
        delete alarm_info_pic4;
        alarm_info_pic4= nullptr;
    }
    if(alarm_info_pic3 != nullptr)
    {
        delete alarm_info_pic3;
        alarm_info_pic3= nullptr;
    }
    if(alarm_info_pic2 != nullptr)
    {
        delete alarm_info_pic2;
        alarm_info_pic2= nullptr;
    }
    if(alarm_info_pic1 != nullptr)
    {
        delete alarm_info_pic1;
        alarm_info_pic1= nullptr;
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
    if(alarm_info_line_5 != nullptr)
    {
        delete alarm_info_line_5;
        alarm_info_line_5= nullptr;
    }
    if(alarm_info_line_4 != nullptr)
    {
        delete alarm_info_line_4;
        alarm_info_line_4= nullptr;
    }
    if(alarm_info_line_3 != nullptr)
    {
        delete alarm_info_line_3;
        alarm_info_line_3= nullptr;
    }
    if(alarm_info_line_2 != nullptr)
    {
        delete alarm_info_line_2;
        alarm_info_line_2= nullptr;
    }
    if(alarm_info_line_1 != nullptr)
    {
        delete alarm_info_line_1;
        alarm_info_line_1= nullptr;
    }
    if(alarm_info_5 != nullptr)
    {
        delete alarm_info_5;
        alarm_info_5= nullptr;
    }
    if(alarm_info_4 != nullptr)
    {
        delete alarm_info_4;
        alarm_info_4= nullptr;
    }
    if(alarm_info_3 != nullptr)
    {
        delete alarm_info_3;
        alarm_info_3= nullptr;
    }
    if(alarm_info_2 != nullptr)
    {
        delete alarm_info_2;
        alarm_info_2= nullptr;
    }
    if(alarm_info_1 != nullptr)
    {
        delete alarm_info_1;
        alarm_info_1= nullptr;
    }

    if(alarm_info != nullptr)
    {
        delete alarm_info;
        alarm_info= nullptr;
    }

    if(alarm_frame_bell != nullptr)
    {
        delete alarm_frame_bell;
        alarm_frame_bell= nullptr;
    }

    ui_image_free();
}
