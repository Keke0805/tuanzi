#include "about_sence.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif

static bool get_storage_info(const char * file_path, storage_info_t * storage)
{
    struct statfs disk_statfs; 
    off64_t bytes = 0;
	unsigned g_bytes = 0;
    double mega_bytes = 0;
    double kilo_bytes = 0;
	unsigned kilo_bytes_cur = 0;
	double d_bytes =0;
	
    if(statfs(file_path, &disk_statfs) < 0 ) 
    { 
        LV_LOG_USER("get disk statfs fail!\n"); 
        return false; 
    } 
    
    storage->total_size = (off64_t)disk_statfs.f_bsize * (off64_t)disk_statfs.f_blocks;
	storage->free_size = (off64_t)disk_statfs.f_bsize * (off64_t)disk_statfs.f_bfree;

	/* format storage info show string */
	bytes = storage->total_size;
	if(bytes >= (1 << 30))
	{
		mega_bytes = (double)(bytes/1024);
		d_bytes =(double)(mega_bytes/(1<<20));
        sprintf(storage->total_str, "%.2fGB", d_bytes);
    }
        
	bytes = storage->free_size;
	if(bytes >= (1 << 30))
	{
		mega_bytes = (double)(bytes/1024);
		d_bytes =(double)(mega_bytes/(1<<20));
        sprintf(storage->free_str, "%.2fGB", d_bytes);
    }
    else if(bytes >= (1 << 20))
    {
    	kilo_bytes = (double)(bytes/(1<<10));
		d_bytes = (double)(kilo_bytes/(1<<10));
        sprintf(storage->free_str, "%.2fMB", d_bytes);
    }
    else if( bytes >= (1 << 10) )
    {
        kilo_bytes = (double)(bytes /(1 << 10));
        sprintf(storage->total_str, "%.2fKB", kilo_bytes);
    }
    else
    {
        sprintf(storage->free_str, "%ldB", bytes);
    }
    
	return true;
}
aboutSence::aboutSence(lv_obj_t* parent)
{
    char version[12]={0};
    char frameID[24]={0};
    char serialAddress[34]={0};
    char macAddress[48]={0};
    char model[24]={0};
    char buildNum[32]={0};
	char totalBuff[128]={0};
	char availBuff[128]={0};
	storage_info_t storage;

#ifdef _UCHIP_T113
    read_string_type_param(PUBLIC_SCENE, VERSION, version,sizeof(version));
    read_string_type_param(WEATHER_SCENE, DEVICETOKEN, frameID,sizeof(frameID));
    read_string_type_param(WEATHER_SCENE, SERIALADDRESS, serialAddress,sizeof(serialAddress));
    read_string_type_param(WEATHER_SCENE, MACADDRESS, macAddress,sizeof(macAddress));
    read_string_type_param(PUBLIC_SCENE, MODEL, model,sizeof(model));
    read_string_type_param(PUBLIC_SCENE, BUILDNUM, buildNum,sizeof(buildNum));
	get_storage_info("/mnt/UDISK",&storage);
#endif
    versionButton = new LvcppButton(parent);
    versionButton->set_size(880,100);
    versionButton->align(LV_ALIGN_TOP_LEFT,0,0);
    versionButton->set_main_radius(0);
    versionButton->set_main_pad_all(0);
    versionButton->set_main_border_width(0);
    versionButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    versionButton->txt_color(lv_color_white());
    versionButton->txt_size(550, 32, LV_LABEL_LONG_WRAP);
    versionButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    versionButton->txt_align(LV_ALIGN_TOP_LEFT,20,10);
    versionButton->add_txt(STR_VERSION);
    versionButton->add_event_cb(aboutSence_event_handler,LV_EVENT_RELEASED,this);

    versionLabel = new LvcppLabel(versionButton->myobj);
    versionLabel->set_size(550,32);
    versionLabel->align(LV_ALIGN_TOP_LEFT,20,52);
    versionLabel->set_main_border_width(0);
    versionLabel->set_main_bg_opa(LV_OPA_0);
    versionLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    versionLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    versionLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    versionLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    versionLabel->set_txt(version);

    versionChildLabel = new LvcppLabel(versionButton->myobj);
    versionChildLabel->set_size(300,32);
    versionChildLabel->align(LV_ALIGN_TOP_RIGHT,-20,52);
    versionChildLabel->set_main_border_width(0);
    versionChildLabel->set_main_bg_opa(LV_OPA_0);
    versionChildLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    versionChildLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    versionChildLabel->txt_align(LV_TEXT_ALIGN_RIGHT);
    versionChildLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    versionChildLabel->set_txt(STR_UPDATES);

    versionline = new LvcppLabel(versionButton->myobj);
    versionline->set_size(880,1);
    versionline->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    versionline->align(LV_ALIGN_BOTTOM_MID,0,0);
    versionline->set_txt("");

    frameIdButton = new LvcppButton(parent);
    frameIdButton->set_size(880,100);
    frameIdButton->align(LV_ALIGN_TOP_LEFT,0,101);
    frameIdButton->set_main_radius(0);
    frameIdButton->set_main_pad_all(0);
    frameIdButton->set_main_border_width(0);
    frameIdButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    frameIdButton->txt_color(lv_color_white());
    frameIdButton->txt_size(550, 32, LV_LABEL_LONG_WRAP);
    frameIdButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    frameIdButton->txt_align(LV_ALIGN_TOP_LEFT,20,10);
    frameIdButton->add_txt(STR_FRAMEID);

    frameIdLabel = new LvcppLabel(frameIdButton->myobj);
    frameIdLabel->set_size(550,32);
    frameIdLabel->align(LV_ALIGN_TOP_LEFT,20,52);
    frameIdLabel->set_main_border_width(0);
    frameIdLabel->set_main_bg_opa(LV_OPA_0);
    frameIdLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    frameIdLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    frameIdLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    frameIdLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    frameIdLabel->set_txt(frameID);

    frameIdline = new LvcppLabel(frameIdButton->myobj);
    frameIdline->set_size(880,1);
    frameIdline->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    frameIdline->align(LV_ALIGN_BOTTOM_MID,0,0);
    frameIdline->set_txt("");

    serialNumButton = new LvcppButton(parent);
    serialNumButton->set_size(880,100);
    serialNumButton->align(LV_ALIGN_TOP_LEFT,0,201);
    serialNumButton->set_main_radius(0);
    serialNumButton->set_main_pad_all(0);
    serialNumButton->set_main_border_width(0);
    serialNumButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    serialNumButton->txt_color(lv_color_white());
    serialNumButton->txt_size(550, 32, LV_LABEL_LONG_WRAP);
    serialNumButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    serialNumButton->txt_align(LV_ALIGN_TOP_LEFT,20,10);
    serialNumButton->add_txt(STR_SERIALNUM);

    serialNumLabel = new LvcppLabel(serialNumButton->myobj);
    serialNumLabel->set_size(550,32);
    serialNumLabel->align(LV_ALIGN_TOP_LEFT,20,52);
    serialNumLabel->set_main_border_width(0);
    serialNumLabel->set_main_bg_opa(LV_OPA_0);
    serialNumLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    serialNumLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    serialNumLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    serialNumLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    serialNumLabel->set_txt(serialAddress);

    serialNumline = new LvcppLabel(serialNumButton->myobj);
    serialNumline->set_size(880,1);
    serialNumline->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    serialNumline->align(LV_ALIGN_BOTTOM_MID,0,0);
    serialNumline->set_txt("");

    wifiMACButton = new LvcppButton(parent);
    wifiMACButton->set_size(880,100);
    wifiMACButton->align(LV_ALIGN_TOP_LEFT,0,301);
    wifiMACButton->set_main_radius(0);
    wifiMACButton->set_main_pad_all(0);
    wifiMACButton->set_main_border_width(0);
    wifiMACButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    wifiMACButton->txt_color(lv_color_white());
    wifiMACButton->txt_size(550, 32, LV_LABEL_LONG_WRAP);
    wifiMACButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    wifiMACButton->txt_align(LV_ALIGN_TOP_LEFT,20,10);
    wifiMACButton->add_txt(STR_WIFIMAC);

    wifiMACLabel = new LvcppLabel(wifiMACButton->myobj);
    wifiMACLabel->set_size(550,32);
    wifiMACLabel->align(LV_ALIGN_TOP_LEFT,20,52);
    wifiMACLabel->set_main_border_width(0);
    wifiMACLabel->set_main_bg_opa(LV_OPA_0);
    wifiMACLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    wifiMACLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    wifiMACLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    wifiMACLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    wifiMACLabel->set_txt(macAddress);

    wifiMACline = new LvcppLabel(wifiMACButton->myobj);
    wifiMACline->set_size(880,1);
    wifiMACline->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    wifiMACline->align(LV_ALIGN_BOTTOM_MID,0,0);
    wifiMACline->set_txt("");

    modelButton = new LvcppButton(parent);
    modelButton->set_size(880,100);
    modelButton->align(LV_ALIGN_TOP_LEFT,0,401);
    modelButton->set_main_radius(0);
    modelButton->set_main_pad_all(0);
    modelButton->set_main_border_width(0);
    modelButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    modelButton->txt_color(lv_color_white());
    modelButton->txt_size(550, 32, LV_LABEL_LONG_WRAP);
    modelButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    modelButton->txt_align(LV_ALIGN_TOP_LEFT,20,10);
    modelButton->add_txt(STR_MODEL);

    modelLabel = new LvcppLabel(modelButton->myobj);
    modelLabel->set_size(550,32);
    modelLabel->align(LV_ALIGN_TOP_LEFT,20,52);
    modelLabel->set_main_border_width(0);
    modelLabel->set_main_bg_opa(LV_OPA_0);
    modelLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    modelLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    modelLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    modelLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    modelLabel->set_txt(model);

    modelline = new LvcppLabel(modelButton->myobj);
    modelline->set_size(880,1);
    modelline->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    modelline->align(LV_ALIGN_BOTTOM_MID,0,0);
    modelline->set_txt("");

    buildNumButton = new LvcppButton(parent);
    buildNumButton->set_size(880,100);
    buildNumButton->align(LV_ALIGN_TOP_LEFT,0,501);
    buildNumButton->set_main_radius(0);
    buildNumButton->set_main_pad_all(0);
    buildNumButton->set_main_border_width(0);
    buildNumButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    buildNumButton->txt_color(lv_color_white());
    buildNumButton->txt_size(550, 32, LV_LABEL_LONG_WRAP);
    buildNumButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    buildNumButton->txt_align(LV_ALIGN_TOP_LEFT,20,10);
    buildNumButton->add_txt(STR_BUILDNUM);

    buildNumLabel = new LvcppLabel(buildNumButton->myobj);
    buildNumLabel->set_size(550,32);
    buildNumLabel->align(LV_ALIGN_TOP_LEFT,20,52);
    buildNumLabel->set_main_border_width(0);
    buildNumLabel->set_main_bg_opa(LV_OPA_0);
    buildNumLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    buildNumLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    buildNumLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    buildNumLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    buildNumLabel->set_txt(buildNum);

    buildNumline = new LvcppLabel(buildNumButton->myobj);
    buildNumline->set_size(880,1);
    buildNumline->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    buildNumline->align(LV_ALIGN_BOTTOM_MID,0,0);
    buildNumline->set_txt("");

    storageButton = new LvcppButton(parent);
    storageButton->set_size(880,100);
    storageButton->align(LV_ALIGN_TOP_LEFT,0,601);
    storageButton->set_main_radius(0);
    storageButton->set_main_pad_all(0);
    storageButton->set_main_border_width(0);
    storageButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    storageButton->txt_color(lv_color_white());
    storageButton->txt_size(550, 32, LV_LABEL_LONG_WRAP);
    storageButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    storageButton->txt_align(LV_ALIGN_TOP_LEFT,20,10);
    storageButton->add_txt(STR_INTERNALSTORAGE);

    storageLabel = new LvcppLabel(storageButton->myobj);
    storageLabel->set_size(550,32);
    storageLabel->align(LV_ALIGN_TOP_LEFT,20,52);
    storageLabel->set_main_border_width(0);
    storageLabel->set_main_bg_opa(LV_OPA_0);
    storageLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    storageLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    storageLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    storageLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
	memset(totalBuff,0,sizeof(totalBuff));
	sprintf(totalBuff,"%s %s",STR_TOTAL,storage.total_str);
    storageLabel->set_txt(totalBuff);

    storageLabel = new LvcppLabel(storageButton->myobj);
    storageLabel->set_size(300,32);
    storageLabel->align(LV_ALIGN_TOP_RIGHT,-20,52);
    storageLabel->set_main_border_width(0);
    storageLabel->set_main_bg_opa(LV_OPA_0);
    storageLabel->txt_color(MENU_BTN_COLOR,LV_PART_MAIN);
    storageLabel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    storageLabel->txt_align(LV_TEXT_ALIGN_RIGHT);
    storageLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
	memset(availBuff,0,sizeof(availBuff));
	sprintf(availBuff,"%s %s",STR_AVAILABLE,storage.free_str);
    storageLabel->set_txt(availBuff);

    storageline = new LvcppLabel(storageButton->myobj);
    storageline->set_size(880,1);
    storageline->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    storageline->align(LV_ALIGN_BOTTOM_MID,0,0);
    storageline->set_txt("");
}
aboutSence::~aboutSence(void)
{
    if(storageline !=NULL)
    {
        delete storageline;
        storageline = NULL;
    }
    if(storageChildLabel !=NULL)
    {
        delete storageChildLabel;
        storageChildLabel = NULL;
    }
    if(storageLabel !=NULL)
    {
        delete storageLabel;
        storageLabel = NULL;
    }
    if(storageButton !=NULL)
    {
        delete storageButton;
        storageButton = NULL;
    }
    if(buildNumline !=NULL)
    {
        delete buildNumline;
        buildNumline = NULL;
    }
    if(buildNumLabel !=NULL)
    {
        delete buildNumLabel;
        buildNumLabel = NULL;
    }
    if(buildNumButton !=NULL)
    {
        delete buildNumButton;
        buildNumButton = NULL;
    }
    if(modelline !=NULL)
    {
        delete modelline;
        modelline = NULL;
    }
    if(modelLabel !=NULL)
    {
        delete modelLabel;
        modelLabel = NULL;
    }
    if(modelButton !=NULL)
    {
        delete modelButton;
        modelButton = NULL;
    }
    if(wifiMACline !=NULL)
    {
        delete wifiMACline;
        wifiMACline = NULL;
    }
    if(wifiMACLabel !=NULL)
    {
        delete wifiMACLabel;
        wifiMACLabel = NULL;
    }
    if(wifiMACButton !=NULL)
    {
        delete wifiMACButton;
        wifiMACButton = NULL;
    }
    if(serialNumline !=NULL)
    {
        delete serialNumline;
        serialNumline = NULL;
    }
    if(serialNumLabel !=NULL)
    {
        delete serialNumLabel;
        serialNumLabel = NULL;
    }
    if(serialNumButton !=NULL)
    {
        delete serialNumButton;
        serialNumButton = NULL;
    }
    if(frameIdline !=NULL)
    {
        delete frameIdline;
        frameIdline = NULL;
    }
    if(frameIdLabel !=NULL)
    {
        delete frameIdLabel;
        frameIdLabel = NULL;
    }
    if(frameIdButton !=NULL)
    {
        delete frameIdButton;
        frameIdButton = NULL;
    }
    if(versionline !=NULL)
    {
        delete versionline;
        versionline = NULL;
    }
    if(versionChildLabel !=NULL)
    {
        delete versionChildLabel;
        versionChildLabel = NULL;
    }
    if(versionLabel !=NULL)
    {
        delete versionLabel;
        versionLabel = NULL;
    }
    if(versionButton !=NULL)
    {
        delete versionButton;
        versionButton = NULL;
    }
}

void aboutSence::aboutSence_event_handler(lv_event_t *event)
{
    aboutSence* opt = (aboutSence*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if((opt->versionButton !=NULL)&&(target ==opt->versionButton->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {

        }
    }

}
