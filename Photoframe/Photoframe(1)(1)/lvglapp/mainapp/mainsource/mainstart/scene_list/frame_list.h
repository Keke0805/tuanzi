#ifndef FRAME_LIST_H
#define FRAME_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "../include/configCustom.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"

typedef struct _frameList_btn_t {
    int x;
    int y;
    int w;
    int h;
    int bg_color;
    lv_opa_t value;
    lv_align_t align;
} frameList_btn_t;

typedef struct _frameList_txt_t {
    int x;
    int y;
    int w;
    int h;
    int font_size;
    lv_align_t align;
} frameList_txt_t;

typedef struct _framelist_iconLine_t {
    int x;
    int y;
    int w;
    int h;
    lv_align_t align;
} frameList_iconLine_t;

class frameList
{
public:
    frameList(lv_obj_t* parent,frameList_btn_t* btn_info,frameList_txt_t* txt_info,frameList_iconLine_t* iconLine_info);
    ~frameList(void);
    int update_frameList(char* name, int str_color,char* iconLinePatch);
    LvcppButton* btn=NULL;  
    LvcppImageButton* iconLine=NULL;
    char IconName[64];

private:
    lv_obj_t* mainframe=NULL;
};

#endif // FRAME_LIST_H
