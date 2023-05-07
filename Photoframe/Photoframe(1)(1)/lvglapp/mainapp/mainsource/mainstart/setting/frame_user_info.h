#ifndef FRAME_USER_INFO_H
#define FRAME_USER_INFO_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"


class frameUserInfo
{
public:
    frameUserInfo(char *userName);
    ~frameUserInfo(void);
    LvcppScreen* UserInfoScreen=NULL;
    LvcppLabel* headLabel=NULL;
    LvcppButton* ViewPhotos=NULL;
    LvcppButton* remarkName=NULL;
    LvcppButton* delUser=NULL;
    LvcppButton* delUserPhoto=NULL;
private:
    LvcppLabel* headNameLabel=NULL;
    LvcppLabel* lineLabel1=NULL;
    LvcppLabel* lineLabel2=NULL;
    LvcppLabel* lineLabel3=NULL;
    LvcppLabel* lineLabel4=NULL;
};

#endif // FRAME_USER_INFO_H
