#ifndef FRAME_CHANGE_STR_H
#define FRAME_CHANGE_STR_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"


class frameChangeStr
{
public:
    frameChangeStr(char *headStr,char *dataStr);
    ~frameChangeStr(void);
    LvcppScreen* StrScreen = NULL;
    LvcppLabel* headLabel=NULL;
    LvcppButton* OKLabel=NULL;
    LvcppButton* CancelLabel=NULL;
    LvcppTextArea* textarea=NULL;
private:
    LvcppLabel* headNameLabel=NULL;
    LvcppLabel* lineLabel1=NULL;
    LvcppLabel* lineLabel2=NULL;
    LvcppKeyboard* Keyboard=NULL;
};

#endif // FRAME_CHANGE_STR_H
