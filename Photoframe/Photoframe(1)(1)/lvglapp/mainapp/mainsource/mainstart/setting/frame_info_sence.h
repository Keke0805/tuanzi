#ifndef FRAMEINFOSENCE_H
#define FRAMEINFOSENCE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

class frameInfoSence
{
public:
    frameInfoSence(lv_obj_t* parent = nullptr);
    ~frameInfoSence();
    void qrcode_updata(void);
     LvcppLabel* frame=NULL;
    LvcppButton* qrcodeButton =NULL;
	
protected:
	void*  SETTING_FRAME_REFRESH_PNG=NULL; 
    void ui_image_decode(void);
    void ui_image_free(void);

private:

    lv_obj_t* mainframe=NULL;
    LvcppLabel* qrcodeLabel=NULL;
    LvcppQrcode* qrcode =NULL;
    LvcppLabel* connectLabel=NULL;
    LvcppLabel* numberLabel =NULL;
    LvcppLabel* emailLabel =NULL;
    LvcppLabel* andiorappLabel =NULL;
    LvcppLabel* iosappLabel =NULL;
};
#endif // FRAMEINFOSENCE_H
