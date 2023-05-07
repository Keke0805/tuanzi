#ifndef HELP_SENCE_H
#define HELP_SENCE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"


class helpSence
{
public:
    helpSence(void);
    ~helpSence(void);
    LvcppScreen* helpScreen=NULL;
protected:
	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL; 
	void* SETTING_ICON_SCENE1_PNG=NULL;       
	void* SETTING_ICON_SCENE2_PNG=NULL;       
	void* SETTING_ICON_SCENE3_PNG=NULL;       
	void* SETTING_ICON_SCENE4_PNG=NULL;       
	void* SETTING_ICON_SCENE5_PNG=NULL;       
	void* SETTING_GOOGLE_PNG=NULL;            
	void* SETTING_IOSAPP_PNG=NULL;            
	void* SETTING_LEFT_PNG=NULL;              
	void* SETTING_RIGHT_PNG=NULL;             
	void* SETTING_SCENE1_PNG=NULL;            
	void* SETTING_SCENE2_PNG=NULL;            
	void* SETTING_SCENE3_PNG=NULL;            
	void* SETTING_SCENE4_PNG=NULL;            
	void* SETTING_SCENE5_PNG=NULL;            
	void* SETTING_SCENE6_PNG=NULL; 
    void ui_image_decode(void);
    void ui_image_free(void);
private:
    static void helpSence_event_handler(lv_event_t *event);
    void show_scene_num(int type);
    LvcppList*  helpList=NULL;
    LvcppLabel* helpSceneLabel1 =NULL;
    LvcppLabel* helpHeadLabel1 =NULL;
    LvcppLabel* helpStrLabel1 =NULL;
    LvcppLabel* helpIconLabel1 =NULL;
    LvcppLabel* helpGoogleLabel1 =NULL;
    LvcppLabel* helpIOSLabel1 =NULL;
    LvcppLabel* GoogleqrcodeLabel =NULL;
    LvcppLabel* IOSqrcodeLabel =NULL;
    LvcppQrcode* GoogleQrcode =NULL;
    LvcppQrcode* IOSQrcode =NULL;

    LvcppLabel* helpSceneLabel2 =NULL;
    LvcppLabel* helpHeadLabel2 =NULL;
    LvcppLabel* helpStrLabel2 =NULL;
    LvcppLabel* helpIconLabel2 =NULL;
    LvcppLabel* DevqrcodeLabel =NULL;
    LvcppQrcode* DevQrcode =NULL;
    LvcppLabel* connectLabel =NULL;
    LvcppLabel* devIdLabel =NULL;

    LvcppLabel* helpSceneLabel3 =NULL;
    LvcppLabel* helpHeadLabel3 =NULL;
    LvcppLabel* helpStrLabel3 =NULL;
    LvcppLabel* helpIconLabel3 =NULL;
    LvcppLabel* DevqrcodeLabel1 =NULL;
    LvcppQrcode* DevQrcode1 =NULL;
    LvcppLabel* connectLabel1 =NULL;
    LvcppLabel* devIdLabel1 =NULL;

    LvcppLabel* helpSceneLabel4 =NULL;
    LvcppLabel* helpHeadLabel4 =NULL;
    LvcppLabel* helpStrLabel4 =NULL;
    LvcppLabel* helpIconLabel4 =NULL;

    LvcppLabel* helpSceneLabel5 =NULL;
    LvcppLabel* helpHeadLabel5 =NULL;
    LvcppLabel* helpStrLabel5 =NULL;
    LvcppLabel* helpIconLabel5 =NULL;

    LvcppLabel* helpSceneLabel6 =NULL;
    LvcppLabel* helpHeadLabel6 =NULL;
    LvcppLabel* helpStrLabel6 =NULL;
    LvcppLabel* helpIconLabel6 =NULL;

    LvcppButton* helpLeft =NULL;
    LvcppButton* helpRight =NULL;
    LvcppLabel* senceLabel =NULL;
    int curScene =0;
};

#endif // HELP_SENCE_H
