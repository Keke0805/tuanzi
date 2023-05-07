#ifndef FRAME_USER_SENCE_H
#define FRAME_USER_SENCE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

class frameUserSence
{
public:
    frameUserSence(lv_obj_t* parent = nullptr);
    ~frameUserSence(void);
    void frameUser_updata_Bg(void* bg_path);
    void frameUser_updata_Name(char* userName);
    LvcppLabel* frameUser =NULL;
    LvcppLabel* userBg =NULL;
    LvcppLabel* userName =NULL;

protected:
	void*  SETTING_FRAME_USERHEAD_PNG=NULL; 
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    bool frameInfoStatus =true;
};

#endif // FRAME_USER_SENCE_H
