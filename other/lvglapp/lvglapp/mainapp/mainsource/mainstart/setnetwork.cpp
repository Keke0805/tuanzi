#include "setnetwork.h"
#include <stdio.h>
#include <string.h>

static int eth_update=0;
static pthread_mutex_t ethlock;

SettingNet::SettingNet(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(lv_scr_act());
    mscreen->set_bg_color(lv_color_white(),LV_OPA_100);
    mparent = mscreen->get_screen();
    initial();
	settimer = startTimer(1000,this);
}

SettingNet::~SettingNet()
{
    deinitial();
    if(go_back !=nullptr)
    {
        delete go_back;
        go_back = nullptr;
    }
    if(mscreen)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

void SettingNet::initial(void)
{
    #if (QTSIM_PLATFORM==0)
    NetPolicyGetEthStatus(&eth_state);
	NetPolicyGetEthConfig(&eth_info);
    #else
    memset(&eth_info,0,sizeof(NetConfig_t));
    #endif

    if(go_back == nullptr)
    {
        go_back = new LvcppButton(mparent);
    }
    go_back->add_txt("返回");
    go_back->set_size(150,100);
    go_back->align(LV_ALIGN_TOP_LEFT,0,0);
    go_back->txt_font_size(30,0);
    go_back->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    go_back->txt_color(lv_color_hex(0x666666));
    go_back->add_event_cb(go_back_btn_event_hander,LV_EVENT_CLICKED,this);
    keyboard_create();
    ip_textedit_create();
    mask_textedit_create();
    gateway_textedit_create();
	network_initial();
}

void SettingNet::deinitial(void)
{
	network_deinitial();
    ip_textedit_delete();
    mask_textedit_delete();
    gateway_textedit_delete();
    keyboard_delete();
}


void SettingNet::network_initial(void)
{
   if(dhcp_win == nullptr)
    {
        dhcp_win = new LvcppScreen(mparent);
    }
   
    dhcp_win->set_size(600,250);
    dhcp_win ->align(LV_ALIGN_TOP_MID,0,50);

    if(dhcpsw == nullptr)
    {
        dhcpsw = new LvcppSwitch(mparent);
    }
    dhcpsw->align(LV_ALIGN_TOP_RIGHT,-15,15);

    if(eth_info.static_ip)
    {
        dhcpsw->add_state(LV_STATE_CHECKED);
		dhcp_win->show(false);
		dhcp_win->move_background();
		dhcp_win->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    }
    else
    {
        dhcpsw->clear_state(LV_STATE_CHECKED);
		dhcp_win->show(true);
		dhcp_win->move_foreground();
		dhcp_win->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
    }
	dhcpsw->add_event_cb(dhcp_sw_event_hander,LV_EVENT_VALUE_CHANGED,this);
}

void SettingNet::network_deinitial(void)
{
    if(dhcpsw!=nullptr)
    {
        delete dhcpsw;
        dhcpsw = nullptr;
    }
    if(dhcp_win!=nullptr)
    {
        delete dhcp_win;
        dhcp_win = nullptr;
    }
}

void SettingNet::network_config_update(void)
{
	int i=0,m=0,n=0;
	char* mask[4]={0};
	char* ipaddr[4]={0};
	char* gateway[4]={0};

    #if (QTSIM_PLATFORM==0)
    NetPolicyConfirmUpdateConfig();
    NetPolicyGetEthConfig(&eth_info);
    #endif
	if(eth_info.ip && strlen(eth_info.ip)>0)
	{
		/* 获取第一个子字符串 */
		ipaddr[i] = strtok(eth_info.ip, ".");
		LV_LOG_USER("%s", ipaddr[i]);
		/* 继续获取其他的子字符串 */
		while( ipaddr[i] != NULL && i < 3 ) {
			++i;
			ipaddr[i] = strtok(NULL, ".");
			LV_LOG_USER("%s", ipaddr[i]);
		}
	}

	if(input_ip1)
	{
		input_ip1->set_text(ipaddr[0]);
	}
	if(input_ip2)
	{
		input_ip2->set_text(ipaddr[1]);
	}
	if(input_ip3)
	{
		input_ip3->set_text(ipaddr[2]);
	}
	if(input_ip4)
	{
		input_ip4->set_text(ipaddr[3]);
	}

	if(eth_info.netmask && strlen(eth_info.netmask)>0)
	{
		/* 获取第一个子字符串 */
		mask[m] = strtok(eth_info.netmask, ".");
		LV_LOG_USER("%s", mask[m]);
		/* 继续获取其他的子字符串 */
		while( mask[m] != NULL && m < 3 ) {
			++m;
			mask[m] = strtok(NULL, ".");
			LV_LOG_USER("%s", mask[m]);
		}
	}

	if(input_mask1)
	{
		input_mask1->set_text(mask[0]);
	}
	if(input_mask2)
	{
		input_mask2->set_text(mask[1]);
	}
	if(input_mask3)
	{
		input_mask3->set_text(mask[2]);
	}
	if(input_mask4)
	{
		input_mask4->set_text(mask[3]);
	}

	if(eth_info.gateway && strlen(eth_info.gateway)>0)
	{
		gateway[n] = strtok(eth_info.gateway, ".");
		LV_LOG_USER("%s", gateway[n]);
		while( gateway[n] != NULL && n < 3 ) {
			++n;
			gateway[n] = strtok(NULL, ".");
			LV_LOG_USER("%s", gateway[n]);
		}
	}
	if(input_gw1)
	{
		input_gw1->set_text(gateway[0]);
	}
	if(input_gw2)
	{
		input_gw2->set_text(gateway[1]);
	}
	if(input_gw3)
	{
		input_gw3->set_text(gateway[2]);
	}
	if(input_gw4)
	{
		input_gw4->set_text(gateway[3]);
	}


}

void SettingNet::keyboard_create(void)
{
    if(keyboard==nullptr)
    {
        keyboard = new LvcppKeyboard(mparent);
    }
    keyboard->set_mode(4);
	keyboard->set_main_bg_color(lv_color_black(),LV_OPA_50);
    keyboard->add_event_cb(keyboard_event_hander,LV_EVENT_VALUE_CHANGED,this);
}
void SettingNet::keyboard_delete(void)
{
    if(keyboard!=nullptr)
    {
        delete keyboard;
        keyboard = nullptr;
    }
}

void SettingNet::ip_textedit_create(void)
{
	int i = 0;
	char* ipaddr[4]={0};

	if(eth_info.ip && strlen(eth_info.ip)>0)
	{
		/* 获取第一个子字符串 */
		ipaddr[i] = strtok(eth_info.ip, ".");
		LV_LOG_USER("%s", ipaddr[i]);
		/* 继续获取其他的子字符串 */
		while( ipaddr[i] != NULL && i < 3 ) {
			++i;
			ipaddr[i] = strtok(NULL, ".");
			LV_LOG_USER("%s", ipaddr[i]);
		}
	}

    label_ip = new LvcppLabel(mparent);
    label_ip->set_size(600,50);
    label_ip->align(LV_ALIGN_TOP_MID,0,50);
    label_ip->set_txt("IP地址：        .      .      .");
    label_ip->txt_font_size(32,0);
    label_ip->set_main_border_width(1);
    label_ip->set_main_pad_T_B(10,0);
    label_ip->set_main_pad_L_R(10,0);

    input_ip1 = new LvcppTextArea(label_ip->myobj);
    input_ip1->set_size(100,50);
    input_ip1->align(LV_ALIGN_TOP_LEFT,155,-10);
    input_ip1->set_one_line(true);
    input_ip1->set_max_length(3);
    input_ip1->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_ip1->set_main_bg_opa(LV_OPA_0);
    input_ip1->set_main_border_width(0);
    input_ip1->set_accepted_chars("0123456789");
    input_ip1->set_align(LV_TEXT_ALIGN_CENTER);
	if(ipaddr[0] !=NULL)
	{
		input_ip1->set_text(ipaddr[0]);
	}
    input_ip1->add_event_cb(ip_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_ip1->add_event_cb(ip_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);

    input_ip2 = new LvcppTextArea(label_ip->myobj);
    input_ip2->set_size(100,50);
    input_ip2->align_to(input_ip1->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_ip2->set_one_line(true);
    input_ip2->set_max_length(3);
    input_ip2->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_ip2->set_main_bg_opa(LV_OPA_0);
    input_ip2->set_main_border_width(0);
    input_ip2->set_accepted_chars("0123456789");
    input_ip2->set_align(LV_TEXT_ALIGN_CENTER);
	if(ipaddr[1] !=NULL)
	{
		input_ip2->set_text(ipaddr[1]);
	}
    input_ip2->add_event_cb(ip_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_ip2->add_event_cb(ip_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);

    input_ip3 = new LvcppTextArea(label_ip->myobj);
    input_ip3->set_size(100,50);
    input_ip3->align_to(input_ip2->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_ip3->set_one_line(true);
    input_ip3->set_max_length(3);
    input_ip3->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_ip3->set_main_bg_opa(LV_OPA_0);
    input_ip3->set_main_border_width(0);
    input_ip3->set_accepted_chars("0123456789");
    input_ip3->set_align(LV_TEXT_ALIGN_CENTER);
	if(ipaddr[2] !=NULL)
	{
		input_ip3->set_text(ipaddr[2]);
	}
    input_ip3->add_event_cb(ip_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_ip3->add_event_cb(ip_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);

    input_ip4 = new LvcppTextArea(label_ip->myobj);
    input_ip4->set_size(100,50);
    input_ip4->align_to(input_ip3->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_ip4->set_one_line(true);
    input_ip4->set_max_length(3);
    input_ip4->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_ip4->set_main_bg_opa(LV_OPA_0);
    input_ip4->set_main_border_width(0);
    input_ip4->set_accepted_chars("0123456789");
    input_ip4->set_align(LV_TEXT_ALIGN_CENTER);
	if(ipaddr[3] !=NULL)
	{
		input_ip4->set_text(ipaddr[3]);
	}
    input_ip4->add_event_cb(ip_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_ip4->add_event_cb(ip_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);


}

void SettingNet::ip_textedit_delete(void)
{
    if(input_ip4)
    {
        delete input_ip4;
        input_ip4 = nullptr;
    }
    if(input_ip3)
    {
        delete input_ip3;
        input_ip3 = nullptr;
    }
    if(input_ip2)
    {
        delete input_ip2;
        input_ip2 = nullptr;
    }
    if(input_ip1)
    {
        delete input_ip1;
        input_ip1 = nullptr;
    }

    if(label_ip)
    {
        delete label_ip;
        label_ip = nullptr;
    }
}

void SettingNet::mask_textedit_create(void)
{
	int i = 0;
	char* mask[4]={0};

	if(eth_info.netmask && strlen(eth_info.netmask)>0)
	{
		/* 获取第一个子字符串 */
		mask[i] = strtok(eth_info.netmask, ".");
		LV_LOG_USER("%s", mask[i]);
		/* 继续获取其他的子字符串 */
		while( mask[i] != NULL && i < 3 ) {
			
			++i;
			mask[i] = strtok(NULL, ".");
			LV_LOG_USER("%s", mask[i]);
		}
	}

    label_mask = new LvcppLabel(mparent);
    label_mask->set_size(600,50);
    label_mask->align_to(label_ip->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,30);
    label_mask->set_txt("子网掩码：      .      .      .");
    label_mask->txt_font_size(32,0);
    label_mask->set_main_border_width(1);
    label_mask->set_main_pad_T_B(10,0);
    label_mask->set_main_pad_L_R(10,0);

    input_mask1 = new LvcppTextArea(label_mask->myobj);
    input_mask1->set_size(100,50);
    input_mask1->align(LV_ALIGN_TOP_LEFT,155,-10);
    input_mask1->set_one_line(true);
    input_mask1->set_max_length(3);
    input_mask1->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_mask1->set_main_bg_opa(LV_OPA_0);
    input_mask1->set_main_border_width(0);
    input_mask1->set_accepted_chars("0123456789");
    input_mask1->set_align(LV_TEXT_ALIGN_CENTER);
	if(mask[0] !=NULL)
	{
		input_mask1->set_text(mask[0]);
	}
    input_mask1->add_event_cb(mask_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_mask1->add_event_cb(mask_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);


    input_mask2 = new LvcppTextArea(label_mask->myobj);
    input_mask2->set_size(100,50);
    input_mask2->align_to(input_mask1->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_mask2->set_one_line(true);
    input_mask2->set_max_length(3);
    input_mask2->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_mask2->set_main_bg_opa(LV_OPA_0);
    input_mask2->set_main_border_width(0);
    input_mask2->set_accepted_chars("0123456789");
    input_mask2->set_align(LV_TEXT_ALIGN_CENTER);
	if(mask[1] !=NULL)
	{
		input_mask2->set_text(mask[1]);
	}
    input_mask2->add_event_cb(mask_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_mask2->add_event_cb(mask_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);

    input_mask3 = new LvcppTextArea(label_mask->myobj);
    input_mask3->set_size(100,50);
    input_mask3->align_to(input_mask2->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_mask3->set_one_line(true);
    input_mask3->set_max_length(3);
    input_mask3->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_mask3->set_main_bg_opa(LV_OPA_0);
    input_mask3->set_main_border_width(0);
    input_mask3->set_accepted_chars("0123456789");
    input_mask3->set_align(LV_TEXT_ALIGN_CENTER);
	if(mask[2] !=NULL)
	{
		input_mask3->set_text(mask[2]);
	}
    input_mask3->add_event_cb(mask_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_mask3->add_event_cb(mask_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);

    input_mask4 = new LvcppTextArea(label_mask->myobj);
    input_mask4->set_size(100,50);
    input_mask4->align_to(input_mask3->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_mask4->set_one_line(true);
    input_mask4->set_max_length(3);
    input_mask4->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_mask4->set_main_bg_opa(LV_OPA_0);
    input_mask4->set_main_border_width(0);
    input_mask4->set_accepted_chars("0123456789");
    input_mask4->set_align(LV_TEXT_ALIGN_CENTER);
	if(mask[3] !=NULL)
	{
		input_mask4->set_text(mask[3]);
	}
    input_mask4->add_event_cb(mask_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_mask4->add_event_cb(mask_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);

}

void SettingNet::mask_textedit_delete(void)
{
    if(input_mask4)
    {
        delete input_mask4;
        input_mask4 = nullptr;
    }
    if(input_mask3)
    {
        delete input_mask3;
        input_mask3 = nullptr;
    }
    if(input_mask2)
    {
        delete input_mask2;
        input_mask2 = nullptr;
    }
    if(input_mask1)
    {
        delete input_mask1;
        input_mask1 = nullptr;
    }

    if(label_mask)
    {
        delete label_mask;
        label_mask = nullptr;
    }
}

void SettingNet::gateway_textedit_create(void)
{
	int i = 0;
	char* gateway[4]={0};

	if(eth_info.gateway && strlen(eth_info.gateway)>0)
	{

		/* 获取第一个子字符串 */
		gateway[i] = strtok(eth_info.gateway, ".");
		LV_LOG_USER("%s", gateway[i]);
		/* 继续获取其他的子字符串 */
		while( gateway[i] != NULL && i < 3 ) {
			++i;
			gateway[i] = strtok(NULL, ".");
			LV_LOG_USER("%s", gateway[i]);
		}
	}

    label_gateway = new LvcppLabel(mparent);
    label_gateway->set_size(600,50);
    label_gateway->align_to(label_mask->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,30);
    label_gateway->set_txt("默认网关：      .      .      .");
    label_gateway->txt_font_size(32,0);
    label_gateway->set_main_border_width(1);
    label_gateway->set_main_pad_T_B(10,0);
    label_gateway->set_main_pad_L_R(10,0);

    input_gw1 = new LvcppTextArea(label_gateway->myobj);
    input_gw1->set_size(100,50);
    input_gw1->align(LV_ALIGN_TOP_LEFT,155,-10);
    input_gw1->set_one_line(true);
    input_gw1->set_max_length(3);
    input_gw1->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_gw1->set_main_bg_opa(LV_OPA_0);
    input_gw1->set_main_border_width(0);
    input_gw1->set_accepted_chars("0123456789");
    input_gw1->set_align(LV_TEXT_ALIGN_CENTER);
	if(gateway[0] !=NULL)
	{
		input_gw1->set_text(gateway[0]);
	}
    input_gw1->add_event_cb(gateway_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_gw1->add_event_cb(gateway_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);


    input_gw2 = new LvcppTextArea(label_gateway->myobj);
    input_gw2->set_size(100,50);
    input_gw2->align_to(input_gw1->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_gw2->set_one_line(true);
    input_gw2->set_max_length(3);
    input_gw2->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_gw2->set_main_bg_opa(LV_OPA_0);
    input_gw2->set_main_border_width(0);
    input_gw2->set_accepted_chars("0123456789");
    input_gw2->set_align(LV_TEXT_ALIGN_CENTER);
	if(gateway[1] !=NULL)
	{
		input_gw2->set_text(gateway[1]);
	}
    input_gw2->add_event_cb(gateway_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_gw2->add_event_cb(gateway_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);
	

    input_gw3 = new LvcppTextArea(label_gateway->myobj);
    input_gw3->set_size(100,50);
    input_gw3->align_to(input_gw2->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_gw3->set_one_line(true);
    input_gw3->set_max_length(3);
    input_gw3->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_gw3->set_main_bg_opa(LV_OPA_0);
    input_gw3->set_main_border_width(0);
    input_gw3->set_accepted_chars("0123456789");
    input_gw3->set_align(LV_TEXT_ALIGN_CENTER);
	if(gateway[2] !=NULL)
	{
		input_gw3->set_text(gateway[2]);
	}
    input_gw3->add_event_cb(gateway_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_gw3->add_event_cb(gateway_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);


    input_gw4 = new LvcppTextArea(label_gateway->myobj);
    input_gw4->set_size(100,50);
    input_gw4->align_to(input_gw3->myobj,LV_ALIGN_OUT_RIGHT_TOP,10,0);
    input_gw4->set_one_line(true);
    input_gw4->set_max_length(3);
    input_gw4->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    input_gw4->set_main_bg_opa(LV_OPA_0);
    input_gw4->set_main_border_width(0);
    input_gw4->set_accepted_chars("0123456789");
    input_gw4->set_align(LV_TEXT_ALIGN_CENTER);
	if(gateway[3] !=NULL)
	{
		input_gw4->set_text(gateway[3]);
	}
    input_gw4->add_event_cb(gateway_textedit_event_hander,LV_EVENT_CLICKED,this);
    input_gw4->add_event_cb(gateway_textedit_event_hander,LV_EVENT_VALUE_CHANGED,this);

}

void SettingNet::gateway_textedit_delete(void)
{
    if(input_gw4)
    {
        delete input_gw4;
        input_gw4 = nullptr;
    }
    if(input_gw3)
    {
        delete input_gw3;
        input_gw3 = nullptr;
    }
    if(input_gw2)
    {
        delete input_gw2;
        input_gw2 = nullptr;
    }
    if(input_gw1)
    {
        delete input_gw1;
        input_gw1 = nullptr;
    }

    if(label_gateway)
    {
        delete label_gateway;
        label_gateway = nullptr;
    }
}


void SettingNet::textarea_pos_move_last(lv_obj_t* obj)
{
	if(obj == input_ip1->myobj)
	{
		input_ip1->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_ip2->myobj)
	{
		input_ip2->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_ip3->myobj)
	{
		input_ip3->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_ip4->myobj)
	{
		input_ip4->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_mask1->myobj)
	{
		input_mask1->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_mask2->myobj)
	{
		input_mask2->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_mask3->myobj)
	{
		input_mask3->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_mask4->myobj)
	{
		input_mask4->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_gw1->myobj)
	{
		input_gw1->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_gw2->myobj)
	{
		input_gw2->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_gw3->myobj)
	{
		input_gw3->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
	else if(obj == input_gw4->myobj)
	{
		input_gw4->set_cursor_pos(LV_TEXTAREA_CURSOR_LAST);
	}
}

void SettingNet::keyboard_event_hander(lv_event_t* event)
{
    SettingNet* opt = (SettingNet*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target == opt->keyboard->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            const char * txt = lv_btnmatrix_get_btn_text(target, lv_btnmatrix_get_selected_btn(target));
            if(txt == NULL) return;
            //OK
            if(strcmp(txt, LV_SYMBOL_OK) == 0) {
                LV_LOG_USER("LV_SYMBOL_OK");
                if(opt->keyboard->get_textarea()!=nullptr)
                {
					opt->textarea_pos_move_last(opt->keyboard->get_textarea());
				}
            }
			else if(strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) {
                LV_LOG_USER("LV_SYMBOL_BACKSPACE");
                if(opt->keyboard->get_textarea()!=nullptr)
                {
                    if(strlen(lv_textarea_get_text(opt->keyboard->get_textarea()))==0)
                    {
                        lv_textarea_set_text(opt->keyboard->get_textarea(), "0");
                    }
                }
            }
        }
    }
}

void SettingNet::dhcp_sw_event_hander(lv_event_t* event)
{
    SettingNet* opt = (SettingNet*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    char buf[32];
    if(target == opt->dhcpsw->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            if(opt->dhcpsw->has_state(LV_STATE_CHECKED))
            {
            	opt->eth_info.static_ip = 1;
                opt->dhcp_win->show(false);
                opt->dhcp_win->move_background();
                opt->dhcp_win->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
                LV_LOG_USER("SW ON");
            }
            else
            {
				opt->eth_info.static_ip = 0;
                opt->dhcp_win->show(true);
                opt->dhcp_win->move_foreground();
                opt->dhcp_win->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
                opt->keyboard->set_textarea(NULL);
                LV_LOG_USER("SW OFF");
            }
			memset(buf,0,sizeof(buf));
			memcpy(buf, &(opt->eth_info.static_ip), sizeof(int));
            #if (QTSIM_PLATFORM==0)
            NetPolicyUpdateEthConfig(NET_CFG_STATICIP_SW, buf);
            NetPolicyConfirmUpdateConfig();
            #endif
        }
    }
}

void SettingNet::ip_textedit_event_hander(lv_event_t* event)
{
    SettingNet* opt = (SettingNet*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	int value1 = 0;
	int value2 = 0;
	int value3 = 0;
	int value4 = 0;
	char absvalue[32]={0};
	if(opt->eth_info.static_ip==0)
	{
		return;
	}
    if(event->code == LV_EVENT_CLICKED)
    {
        if(opt->keyboard)
        {
            opt->keyboard->set_textarea(target);
        }
    }
    else if(event->code == LV_EVENT_VALUE_CHANGED)
    {
        int value=0;
        if(target == opt->input_ip1->myobj)
        {
            value = atoi(opt->input_ip1->get_text());
            LV_LOG_USER("value = %d",value);
            if(value<1)
            {
                opt->input_ip1->set_text("1");
				value = 1;
            }
            else if(value==127)
            {
                opt->input_ip1->set_text("1");
				value = 1;
            }
            else if(value>223)
            {
                opt->input_ip1->set_text("223");
				value = 223;
            }
	        if(0 < value && value < 127)
	        {
	            opt->input_mask1->set_text("255");
	            opt->input_mask2->set_text("0");
	            opt->input_mask3->set_text("0");
	            opt->input_mask4->set_text("0");
	        }
	        else if(127 < value && value < 192)
	        {
	            opt->input_mask1->set_text("255");
	            opt->input_mask2->set_text("255");
	            opt->input_mask3->set_text("0");
	            opt->input_mask4->set_text("0");
	        }
	        else if(191 < value && value < 224)
	        {
	            opt->input_mask1->set_text("255");
	            opt->input_mask2->set_text("255");
	            opt->input_mask3->set_text("255");
	            opt->input_mask4->set_text("0");
	        }
	        else {
	            LV_LOG_USER("network error");
	        }
        }
        else if(target == opt->input_ip2->myobj)
        {
            value = atoi(opt->input_ip2->get_text());
            LV_LOG_USER("value = %d",value);
			if(value>255)
            {
                opt->input_ip2->set_text("255");
            }
            else if(value<10 && strlen(opt->input_ip2->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_ip2->set_text(absvalue);
            }
        }
        else if(target == opt->input_ip3->myobj)
        {
            value = atoi(opt->input_ip3->get_text());
            LV_LOG_USER("value = %d",value);
            if(value>255)
            {
                opt->input_ip3->set_text("255");
            }
            else if(value<10 && strlen(opt->input_ip3->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_ip3->set_text(absvalue);
            }
        }
        else if(target == opt->input_ip4->myobj)
        {
            value = atoi(opt->input_ip4->get_text());
            LV_LOG_USER("value = %d",value);
            if(value<1)
            {
                opt->input_ip4->set_text("1");
                value = 1;
            }
            else if(value>255)
            {
                opt->input_ip4->set_text("255");
            }
            else if(value<10 && strlen(opt->input_ip4->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_ip4->set_text(absvalue);
            }
        }

		value1 = atoi(opt->input_ip1->get_text());
		value2 = atoi(opt->input_ip2->get_text());
		value3 = atoi(opt->input_ip3->get_text());
		value4 = atoi(opt->input_ip4->get_text());
		memset(opt->eth_info.ip,0,sizeof(opt->eth_info.ip));
		sprintf(opt->eth_info.ip,"%d.%d.%d.%d",value1,value2,value3,value4);
		LV_LOG_USER("static_ip = %d ////  eth_info.ip=%s",opt->eth_info.static_ip,opt->eth_info.ip);
		if(opt->eth_info.static_ip)
		{
            #if (QTSIM_PLATFORM==0)
            NetPolicyUpdateEthConfig(NET_CFG_IP, opt->eth_info.ip);
            NetPolicyConfirmUpdateConfig();
            #endif
		}
    }
}


void SettingNet::mask_textedit_event_hander(lv_event_t* event)
{
    SettingNet* opt = (SettingNet*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	int value1 = 0;
	int value2 = 0;
	int value3 = 0;
	int value4 = 0;
	char absvalue[32]={0};
	if(opt->eth_info.static_ip==0)
	{
		return;
	}
    if(event->code == LV_EVENT_CLICKED)
    {
        if(opt->keyboard)
        {
            opt->keyboard->set_textarea(target);
        }
    }
    else if(event->code == LV_EVENT_VALUE_CHANGED)
    {
        int value=0;
        if(target == opt->input_mask1->myobj)
        {
            value = atoi(opt->input_mask1->get_text());
            LV_LOG_USER("value = %d",value);
            if(value>255)
            {
                opt->input_mask1->set_text("255");
            }
            else if(value<10 && strlen(opt->input_mask1->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_mask1->set_text(absvalue);
            }
        }
        else if(target == opt->input_mask2->myobj)
        {
            value = atoi(opt->input_mask2->get_text());
            LV_LOG_USER("value = %d",value);
            if(value>255)
            {
                opt->input_mask2->set_text("255");
            }
            else if(value<10 && strlen(opt->input_mask2->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_mask2->set_text(absvalue);
            }
        }
        else if(target == opt->input_mask3->myobj)
        {
            value = atoi(opt->input_mask3->get_text());
            LV_LOG_USER("value = %d",value);
            if(value>255)
            {
                opt->input_mask3->set_text("255");
            }
            else if(value<10 && strlen(opt->input_mask3->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_mask3->set_text(absvalue);
            }
        }
        else if(target == opt->input_mask4->myobj)
        {
            value = atoi(opt->input_mask4->get_text());
            LV_LOG_USER("value = %d",value);
            if(value>255)
            {
                opt->input_mask4->set_text("255");
            }
            else if(value<10 && strlen(opt->input_mask4->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_mask4->set_text(absvalue);
            }
        }
		value1 = atoi(opt->input_mask1->get_text());
		value2 = atoi(opt->input_mask2->get_text());
		value3 = atoi(opt->input_mask3->get_text());
		value4 = atoi(opt->input_mask4->get_text());
		
		memset(opt->eth_info.netmask,0,sizeof(opt->eth_info.netmask));
		sprintf(opt->eth_info.netmask,"%d.%d.%d.%d",value1,value2,value3,value4);
		LV_LOG_USER("static_ip = %d ////  eth_info.netmask=%s",opt->eth_info.static_ip,opt->eth_info.netmask);
		if(opt->eth_info.static_ip)
		{
            #if (QTSIM_PLATFORM==0)
            NetPolicyUpdateEthConfig(NET_CFG_NETMASK, opt->eth_info.netmask);
            NetPolicyConfirmUpdateConfig();
            #endif
		}
    }
}

void SettingNet::gateway_textedit_event_hander(lv_event_t* event)
{
    SettingNet* opt = (SettingNet*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	int value1 = 0;
	int value2 = 0;
	int value3 = 0;
	int value4 = 0;
    char absvalue[32]={0};
	if(opt->eth_info.static_ip==0)
	{
		return;
    }
    if(event->code == LV_EVENT_CLICKED)
    {
        if(opt->keyboard)
        {
            opt->keyboard->set_textarea(target);
        }
    }
    else if(event->code == LV_EVENT_VALUE_CHANGED)
    {
        int value=0;
        if(target == opt->input_gw1->myobj)
        {
            value = atoi(opt->input_gw1->get_text());
            LV_LOG_USER("value = %d",value);
            if(value<1)
            {
                opt->input_gw1->set_text("1");
            }
            else if(value==127)
            {
                opt->input_gw1->set_text("1");
            }
            else if(value>223)
            {
                opt->input_gw1->set_text("223");
            }
        }
        else if(target == opt->input_gw2->myobj)
        {
            value = atoi(opt->input_gw2->get_text());
            LV_LOG_USER("value = %d",value);
            if(value>255)
            {
                opt->input_gw2->set_text("255");
            }
            else if(value<10 && strlen(opt->input_gw2->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_gw2->set_text(absvalue);
            }
        }
        else if(target == opt->input_gw3->myobj)
        {
            value = atoi(opt->input_gw3->get_text());
            LV_LOG_USER("value = %d",value);
            if(value>255)
            {
                opt->input_gw3->set_text("255");
            }
            else if(value<10 && strlen(opt->input_gw3->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_gw3->set_text(absvalue);
            }
        }
        else if(target == opt->input_gw4->myobj)
        {
            value = atoi(opt->input_gw4->get_text());
            LV_LOG_USER("value = %d",value);
            if(value>255)
            {
                opt->input_gw4->set_text("255");
            }
            else if(value<10 && strlen(opt->input_gw4->get_text())>=2)
            {
                sprintf(absvalue,"%d",value);
                opt->input_gw4->set_text(absvalue);
            }
        }
		value1 = atoi(opt->input_gw1->get_text());
		value2 = atoi(opt->input_gw2->get_text());
		value3 = atoi(opt->input_gw3->get_text());
        value4 = atoi(opt->input_gw4->get_text());
		memset(opt->eth_info.gateway,0,sizeof(opt->eth_info.gateway));
		sprintf(opt->eth_info.gateway,"%d.%d.%d.%d",value1,value2,value3,value4);
		LV_LOG_USER("static_ip = %d ////  eth_info.gateway=%s",opt->eth_info.static_ip,opt->eth_info.gateway);
		if(opt->eth_info.static_ip)
		{
            #if (QTSIM_PLATFORM==0)
            NetPolicyUpdateEthConfig(NET_CFG_GW,opt->eth_info.gateway);
            NetPolicyConfirmUpdateConfig();
            #endif

        }
    }
}


void SettingNet::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;//static variable once assign
    int state=0;

	if(eth_update)
	{
	    timecnt++;
		if(timecnt>1)
		{
			timecnt = 0;
			eth_update=0;
			network_config_update();
		}
    }
    if(eth_info.static_ip==0)
    {
        #if (QTSIM_PLATFORM==0)
        NetPolicyGetEthStatus(&state);
        #endif
        if(state != eth_state)
        {
            eth_state = state;
            if(eth_state==1)
            {
                eth_update = 1;
            }
        }
    }
}

void SettingNet::go_back_btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    SettingNet* opt = (SettingNet*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target == opt->go_back->myobj)
    {
        opt->net_callback();
    }
}

void SettingNet::sendcb(void (*callback)(void))
{
    net_callback = callback;
}


