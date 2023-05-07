#include "wlan_info.h"

Wlaninfo::Wlaninfo(lv_obj_t* parent)
{
    wlan_frame = new LvcppScreen(parent);
    wlan_frame->set_size(1280,800);
    wlan_frame->align(LV_ALIGN_TOP_MID,0,0);
    wlan_frame->set_main_bg_color(lv_palette_main(LV_PALETTE_GREY),LV_OPA_70);
    wlanscreen = wlan_frame->myobj;

    wlan_info = new LvcppButton(wlanscreen);
    wlan_info->set_size(540,340);
    wlan_info->set_main_pad_all(0);
    wlan_info->center_align();
    wlan_info->set_main_bg_color(lv_color_hex(0x686868),LV_OPA_100);
    wlan_info->clear_flag(LV_OBJ_FLAG_CLICKABLE);

    wlan_label = new LvcppLabel(wlan_info->myobj);
    wlan_label->set_size(520,32);
    wlan_label->align(LV_ALIGN_TOP_LEFT,10,0);
    wlan_label->txt_font_size(32,0);

    password_label = new LvcppLabel(wlan_info->myobj);
    password_label->set_size(520,32);
    password_label->align_to(wlan_label->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,10);
    password_label->txt_font_size(24,0);
    password_label->set_txt("Password");

    textarea = new LvcppTextArea(wlan_info->myobj);
    textarea->set_size(520,50);
    textarea->align_to(password_label->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,10);
    textarea->set_max_length(60);
    textarea->set_one_line(true);
    textarea->set_scrollbar_mode(0);
    textarea->set_password_mode(true);
    textarea->set_text("");
    textarea->add_event_cb(textarea_event_handler,LV_EVENT_PRESSED,this);

    password_mode = new LvcppCheckBox(wlan_info->myobj);
    password_mode->set_size(520,40);
    password_mode->align_to(textarea->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,10);
    password_mode->set_text("Password display");
    password_mode->add_event_cb(checkbox_event_handler,LV_EVENT_VALUE_CHANGED,this);

    connect_btn = new LvcppButton(wlan_info->myobj);
    connect_btn->set_size(80,50);
    connect_btn->align(LV_ALIGN_BOTTOM_RIGHT,-10,-10);
    connect_btn->add_txt("Connect");
    connect_btn->txt_font_size(24,0);
    connect_btn->txt_center();

    cancel_btn = new LvcppButton(wlan_info->myobj);
    cancel_btn->set_size(80,50);
    cancel_btn->align_to(connect_btn->myobj,LV_ALIGN_OUT_LEFT_TOP,-20,0);
    cancel_btn->add_txt("Cancel");
    cancel_btn->txt_font_size(24,0);
    cancel_btn->txt_center();

}

Wlaninfo::~Wlaninfo(void)
{
    if(cancel_btn != nullptr)
    {
        delete cancel_btn;
        cancel_btn= nullptr;
    }
    if(connect_btn != nullptr)
    {
        delete connect_btn;
        connect_btn= nullptr;
    }
    if(password_mode != nullptr)
    {
        delete password_mode;
        password_mode= nullptr;
    }
    if(textarea != nullptr)
    {
        delete textarea;
        textarea= nullptr;
    }
    if(password_label != nullptr)
    {
        delete password_label;
        password_label= nullptr;
    }
    if(wlan_label != nullptr)
    {
        delete wlan_label;
        wlan_label= nullptr;
    }
    if(wlan_info != nullptr)
    {
        delete wlan_info;
        wlan_info= nullptr;
    }
    if(kb != nullptr)
    {
        delete kb;
        kb= nullptr;
    }
	if(wlan_frame != nullptr)
	{
		delete wlan_frame;
		wlan_frame= nullptr;
	}	
}

void Wlaninfo::init_parament(net_wifi_scan_info_t wifi,wmgState status)
{
    show_keyboard();
    wlan_label->set_txt(wifi.ssid);

}

void Wlaninfo::show_keyboard(void)
{
    if(kb == nullptr)
    {
        kb = new LvcppKeyboard(wlanscreen);
        kb->add_event_cb(keyboard_event_handler,LV_EVENT_VALUE_CHANGED,this);
    }
    kb->set_textarea(textarea->myobj);
    kb->show(true);
    wlan_info->align_to(kb->myobj,LV_ALIGN_OUT_TOP_MID,0,-30);
    wlan_info->invalidate();
}

void Wlaninfo::hide_keyboard(void)
{
    if(kb != nullptr){
        kb->show(false);
    }
    wlan_info->center_align();
    wlan_info->invalidate();
}

void Wlaninfo::checkbox_event_handler(lv_event_t *event)
{
    Wlaninfo* opt = (Wlaninfo*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(event->code == LV_EVENT_VALUE_CHANGED)
    {
        if(opt->password_mode->has_state(LV_STATE_CHECKED)){
            opt->textarea->set_password_mode(false);
        }
        else {
            opt->textarea->set_password_mode(true);
        }
    }
}

void Wlaninfo::textarea_event_handler(lv_event_t *event)
{
    Wlaninfo* opt = (Wlaninfo*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    opt->show_keyboard();
}

void Wlaninfo::keyboard_event_handler(lv_event_t *event)
{
    Wlaninfo* opt = (Wlaninfo*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    const char * txt = lv_btnmatrix_get_btn_text(target, lv_btnmatrix_get_selected_btn(target));
    if(txt == NULL) return;
    //switch
    if(strcmp(txt, LV_SYMBOL_CLOSE) == 0 || strcmp(txt, LV_SYMBOL_KEYBOARD) == 0) {
        opt->hide_keyboard();
    }
    //sure
    else if(strcmp(txt, LV_SYMBOL_OK) == 0) {
        opt->hide_keyboard();
    }
}





