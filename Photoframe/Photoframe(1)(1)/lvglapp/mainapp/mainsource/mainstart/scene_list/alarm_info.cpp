#include "alarm_info.h"
#include  "common/common.h"


void Alarminfo::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    LIST_CIRCLE_PNG = (void*)parse_image_from_file(LIST_CIRCLE_PNG_PATH);
    LIST_ICON_CHE_PNG = (void*)parse_image_from_file(LIST_ICON_CHE_PNG_PATH);
#endif
}

void Alarminfo::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(LIST_CIRCLE_PNG);
    free_image(LIST_ICON_CHE_PNG);
#endif
}

Alarminfo::Alarminfo(int dayType,lv_obj_t* parent)
{
    ui_image_decode();
	void *iconPatch[2]={LIST_CIRCLE_PNG,LIST_ICON_CHE_PNG};
    memset(&click_statue, 0, sizeof(click_statue_t));
	set_info(dayType);
    alarm_frame = new LvcppScreen(parent);
    alarm_frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    alarm_frame->align(LV_ALIGN_TOP_MID,0,0);
    alarm_frame->set_main_bg_color(lv_color_black(),LV_OPA_60);
    alarmscreen = alarm_frame->myobj;

    alarm_info = new LvcppButton(alarmscreen);
    alarm_info->set_size(680,700);
    alarm_info->set_main_pad_all(0);
    alarm_info->center_align();
    alarm_info->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info->set_style_radius(10,0);
    alarm_info->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    alarm_info_frame = alarm_info->myobj;

    alarm_info_sun = new LvcppButton(alarm_info_frame);
    alarm_info_sun->set_size(680,87);
    alarm_info_sun->set_main_pad_all(0);
    alarm_info_sun->align(LV_ALIGN_TOP_LEFT,0,0);
    alarm_info_sun->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_sun->set_style_radius(0,0);
    alarm_info_sun->txt_color(lv_color_hex(0x000000));
    alarm_info_sun->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_sun->add_txt(STR_SUN);
    alarm_info_sun->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_sun->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_mon = new LvcppButton(alarm_info_frame);
    alarm_info_mon->set_size(680,87);
    alarm_info_mon->set_main_pad_all(0);
    alarm_info_mon->align(LV_ALIGN_TOP_LEFT,0,89);
    alarm_info_mon->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_mon->set_style_radius(0,0);
    alarm_info_mon->txt_color(lv_color_hex(0x000000));
    alarm_info_mon->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_mon->add_txt(STR_MON);
    alarm_info_mon->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_mon->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_tue = new LvcppButton(alarm_info_frame);
    alarm_info_tue->set_size(680,87);
    alarm_info_tue->set_main_pad_all(0);
    alarm_info_tue->align(LV_ALIGN_TOP_LEFT,0,178);
    alarm_info_tue->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_tue->set_style_radius(0,0);
    alarm_info_tue->txt_color(lv_color_hex(0x000000));
    alarm_info_tue->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_tue->add_txt(STR_TUE);
    alarm_info_tue->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_tue->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_wed = new LvcppButton(alarm_info_frame);
    alarm_info_wed->set_size(680,87);
    alarm_info_wed->set_main_pad_all(0);
    alarm_info_wed->align(LV_ALIGN_TOP_LEFT,0,267);
    alarm_info_wed->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_wed->set_style_radius(0,0);
    alarm_info_wed->txt_color(lv_color_hex(0x000000));
    alarm_info_wed->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_wed->add_txt(STR_WED);
    alarm_info_wed->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_wed->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_thur = new LvcppButton(alarm_info_frame);
    alarm_info_thur->set_size(680,87);
    alarm_info_thur->set_main_pad_all(0);
    alarm_info_thur->align(LV_ALIGN_TOP_LEFT,0,356);
    alarm_info_thur->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_thur->set_style_radius(0,0);
    alarm_info_thur->txt_color(lv_color_hex(0x000000));
    alarm_info_thur->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_thur->add_txt(STR_THU);
    alarm_info_thur->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_thur->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_fri = new LvcppButton(alarm_info_frame);
    alarm_info_fri->set_size(680,87);
    alarm_info_fri->set_main_pad_all(0);
    alarm_info_fri->align(LV_ALIGN_TOP_LEFT,0,445);
    alarm_info_fri->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_fri->set_style_radius(0,0);
    alarm_info_fri->txt_color(lv_color_hex(0x000000));
    alarm_info_fri->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_fri->add_txt(STR_FRI);
    alarm_info_fri->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_fri->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_sat = new LvcppButton(alarm_info_frame);
    alarm_info_sat->set_size(680,87);
    alarm_info_sat->set_main_pad_all(0);
    alarm_info_sat->align(LV_ALIGN_TOP_LEFT,0,534);
    alarm_info_sat->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info_sat->set_style_radius(10,0);
    alarm_info_sat->txt_color(lv_color_hex(0x000000));
    alarm_info_sat->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    alarm_info_sat->add_txt(STR_SAT);
    alarm_info_sat->txt_align(LV_ALIGN_LEFT_MID,10,0);
    alarm_info_sat->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_line_1 = new LvcppButton(alarm_info_frame);
    alarm_info_line_1->set_size(680,2);
    alarm_info_line_1->align(LV_ALIGN_TOP_LEFT,0,87);
    alarm_info_line_1->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_2 = new LvcppButton(alarm_info_frame);
    alarm_info_line_2->set_size(680,2);
    alarm_info_line_2->align(LV_ALIGN_TOP_LEFT,0,176);
    alarm_info_line_2->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_3 = new LvcppButton(alarm_info_frame);
    alarm_info_line_3->set_size(680,2);
    alarm_info_line_3->align(LV_ALIGN_TOP_LEFT,0,265);
    alarm_info_line_3->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_4 = new LvcppButton(alarm_info_frame);
    alarm_info_line_4->set_size(680,2);
    alarm_info_line_4->align(LV_ALIGN_TOP_LEFT,0,354);
    alarm_info_line_4->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_5 = new LvcppButton(alarm_info_frame);
    alarm_info_line_5->set_size(680,2);
    alarm_info_line_5->align(LV_ALIGN_TOP_LEFT,0,443);
    alarm_info_line_5->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_6 = new LvcppButton(alarm_info_frame);
    alarm_info_line_6->set_size(680,2);
    alarm_info_line_6->align(LV_ALIGN_TOP_LEFT,0,532);
    alarm_info_line_6->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    alarm_info_line_7 = new LvcppButton(alarm_info_frame);
    alarm_info_line_7->set_size(680,2);
    alarm_info_line_7->align(LV_ALIGN_TOP_LEFT,0,621);
    alarm_info_line_7->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);

    cancel = new LvcppButton(alarm_info_frame);
    cancel->set_size(315,55);
    cancel->set_main_pad_all(0);
    cancel->align(LV_ALIGN_TOP_LEFT,10,635);
    cancel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    cancel->set_style_radius(10,0);
    cancel->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    cancel->add_txt(STR_CANCEL);
    cancel->txt_center();

    confirm = new LvcppButton(alarm_info_frame);
    confirm->set_size(315,55);
    confirm->align(LV_ALIGN_TOP_RIGHT,-10,635);
    confirm->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    confirm->set_style_radius(10,0);
    confirm->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    confirm->add_txt(STR_OK);
    confirm->txt_center();

    alarm_info_sun_pic = new LvcppButton(alarm_info_frame);
    alarm_info_sun_pic->set_size(32,32);
    alarm_info_sun_pic->align(LV_ALIGN_TOP_RIGHT,-15,30);
    alarm_info_sun_pic->set_main_bg_img_src(iconPatch[click_statue.click_sun]);
    alarm_info_sun_pic->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_sun_pic->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_mon_pic = new LvcppButton(alarm_info_frame);
    alarm_info_mon_pic->set_size(32,32);
    alarm_info_mon_pic->align(LV_ALIGN_TOP_RIGHT,-15,121);
    alarm_info_mon_pic->set_main_bg_img_src(iconPatch[click_statue.click_mon]);
    alarm_info_mon_pic->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_mon_pic->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_tue_pic = new LvcppButton(alarm_info_frame);
    alarm_info_tue_pic->set_size(32,32);
    alarm_info_tue_pic->align(LV_ALIGN_TOP_RIGHT,-15,210);
    alarm_info_tue_pic->set_main_bg_img_src(iconPatch[click_statue.click_tue]);
    alarm_info_tue_pic->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_tue_pic->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_wed_pic = new LvcppButton(alarm_info_frame);
    alarm_info_wed_pic->set_size(32,32);
    alarm_info_wed_pic->align(LV_ALIGN_TOP_RIGHT,-15,299);
    alarm_info_wed_pic->set_main_bg_img_src(iconPatch[click_statue.click_wed]);
    alarm_info_wed_pic->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_wed_pic->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_thur_pic = new LvcppButton(alarm_info_frame);
    alarm_info_thur_pic->set_size(32,32);
    alarm_info_thur_pic->align(LV_ALIGN_TOP_RIGHT,-15,388);
    alarm_info_thur_pic->set_main_bg_img_src(iconPatch[click_statue.click_thui]);
    alarm_info_thur_pic->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_thur_pic->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_fri_pic = new LvcppButton(alarm_info_frame);
    alarm_info_fri_pic->set_size(32,32);
    alarm_info_fri_pic->align(LV_ALIGN_TOP_RIGHT,-15,477);
    alarm_info_fri_pic->set_main_bg_img_src(iconPatch[click_statue.click_fri]);
    alarm_info_fri_pic->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_fri_pic->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    alarm_info_sat_pic = new LvcppButton(alarm_info_frame);
    alarm_info_sat_pic->set_size(32,32);
    alarm_info_sat_pic->align(LV_ALIGN_TOP_RIGHT,-15,566);
    alarm_info_sat_pic->set_main_bg_img_src(iconPatch[click_statue.click_sat]);
    alarm_info_sat_pic->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    alarm_info_sat_pic->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);
}

void Alarminfo::clicked_event_handler(lv_event_t *event)
{
    Alarminfo* opt = (Alarminfo*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	void *iconPatch[2]={opt->LIST_CIRCLE_PNG,opt->LIST_ICON_CHE_PNG};
	
    if(target==opt->alarm_info_sun->myobj)
    {
        opt->click_statue.click_sun = !opt->click_statue.click_sun;
		opt->alarm_info_sun_pic->set_main_bg_img_src(iconPatch[opt->click_statue.click_sun]);
    }

    if(target==opt->alarm_info_mon->myobj)
    {
        opt->click_statue.click_mon = !opt->click_statue.click_mon;
        opt->alarm_info_mon_pic->set_main_bg_img_src(iconPatch[opt->click_statue.click_mon]);
    }

    if(target==opt->alarm_info_tue->myobj)
    {
    	opt->click_statue.click_tue = !opt->click_statue.click_tue;
        opt->alarm_info_tue_pic->set_main_bg_img_src(iconPatch[opt->click_statue.click_tue]);
    }

    if(target==opt->alarm_info_wed->myobj)
    {
    	opt->click_statue.click_wed = !opt->click_statue.click_wed;
        opt->alarm_info_wed_pic->set_main_bg_img_src(iconPatch[opt->click_statue.click_wed]);
    }

    if(target==opt->alarm_info_thur->myobj)
    {
    	opt->click_statue.click_thui = !opt->click_statue.click_thui;
        opt->alarm_info_thur_pic->set_main_bg_img_src(iconPatch[opt->click_statue.click_thui]);
    }

    if(target==opt->alarm_info_fri->myobj)
    {
    	opt->click_statue.click_fri = !opt->click_statue.click_fri;
		opt->alarm_info_fri_pic->set_main_bg_img_src(iconPatch[opt->click_statue.click_fri]);
    }

    if(target==opt->alarm_info_sat->myobj)
    {
    	opt->click_statue.click_sat = !opt->click_statue.click_sat;
        opt->alarm_info_sat_pic->set_main_bg_img_src(iconPatch[opt->click_statue.click_sat]);
    }
}
void Alarminfo::set_info(int dayType)
{
	if(dayType&DAY_SUN)
	{
		click_statue.click_sun=true;
	}
	if(dayType&DAY_MON)
	{
		click_statue.click_mon=true;
	}
	if(dayType&DAY_TUES)
	{
		click_statue.click_tue=true;
	}
	if(dayType&DAY_WED)
	{
		click_statue.click_wed=true;
	}
	if(dayType&DAY_THUR)
	{
		click_statue.click_thui=true;
	}
	if(dayType&DAY_FRI)
	{
		click_statue.click_fri=true;
	}
	if(dayType&DAY_SAT)
	{
		click_statue.click_sat=true;
	}
}
int Alarminfo::get_info(void)
{
	bool status =true;
	int dayType =0;
	
    if(click_statue.click_sun == 1)
    {
       dayType |=DAY_SUN;
	   status =false;
    }
    if(click_statue.click_mon == 1)
    {
		dayType |=DAY_MON;
		status =false;
    }
    if(click_statue.click_tue == 1)
    {
 		dayType |=DAY_TUES;
		status =false;
    }
    if(click_statue.click_wed == 1)
    {
		dayType |=DAY_WED;
		status =false;
    }
    if(click_statue.click_thui == 1)
    {
		dayType |=DAY_THUR;
		status =false;
    }
    if(click_statue.click_fri == 1)
    {
		dayType |=DAY_FRI;
		status =false;
    }
    if(click_statue.click_sat == 1)
    {
 		dayType |=DAY_SAT;
		status =false;
    }
	if(status ==true)
	{
		dayType =WDAY_EN;
		status =false;
	}
    return dayType;
}

Alarminfo::~Alarminfo(void)
{
    if(alarm_info_sat != nullptr)
    {
        delete alarm_info_sat;
        alarm_info_sat= nullptr;
    }

    if(alarm_info_fri != nullptr)
    {
        delete alarm_info_fri;
        alarm_info_fri= nullptr;
    }

    if(alarm_info_thur != nullptr)
    {
        delete alarm_info_thur;
        alarm_info_thur= nullptr;
    }

    if(alarm_info_wed != nullptr)
    {
        delete alarm_info_wed;
        alarm_info_wed= nullptr;
    }

    if(alarm_info_tue != nullptr)
    {
        delete alarm_info_tue;
        alarm_info_tue= nullptr;
    }

    if(alarm_info_mon != nullptr)
    {
        delete alarm_info_mon;
        alarm_info_mon= nullptr;
    }

    if(alarm_info_sun_pic != nullptr)
    {
        delete alarm_info_sun_pic;
        alarm_info_sun_pic= nullptr;
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

    if(alarm_info_line_7 != nullptr)
    {
        delete alarm_info_line_7;
        alarm_info_line_7= nullptr;
    }

    if(alarm_info_line_6 != nullptr)
    {
        delete alarm_info_line_6;
        alarm_info_line_6= nullptr;
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
    if(alarm_info_sat != nullptr)
    {
        delete alarm_info_sat;
        alarm_info_sat= nullptr;
    }
    if(alarm_info_fri != nullptr)
    {
        delete alarm_info_fri;
        alarm_info_fri= nullptr;
    }
    if(alarm_info_thur != nullptr)
    {
        delete alarm_info_thur;
        alarm_info_thur= nullptr;
    }
    if(alarm_info_wed != nullptr)
    {
        delete alarm_info_wed;
        alarm_info_wed= nullptr;
    }
    if(alarm_info_tue != nullptr)
    {
        delete alarm_info_tue;
        alarm_info_tue= nullptr;
    }
    if(alarm_info_mon != nullptr)
    {
        delete alarm_info_mon;
        alarm_info_mon= nullptr;
    }
    if(alarm_info_sun != nullptr)
    {
        delete alarm_info_sun;
        alarm_info_sun= nullptr;
    }

    if(alarm_info != nullptr)
    {
        delete alarm_info;
        alarm_info= nullptr;
    }

	if(alarm_frame != nullptr)
	{
		delete alarm_frame;
		alarm_frame= nullptr;
	}	
    ui_image_free();
}



