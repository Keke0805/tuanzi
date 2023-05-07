#ifndef FRAME_LIST_ICON_CENTER_H
#define FRAME_LIST_ICON_CENTER_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"

typedef struct _frameiconlist_btn_t {
    int x;
    int y;
    int w;
    int h;
    int bg_color;
    lv_opa_t value;
    lv_align_t align;
} frameiconlist_btn_t;

typedef struct _frameiconlist_icon_t {
    int x;
    int y;
    int w;
    int h;
    lv_align_t align;
} frameiconlist_icon_t;

class frameListIconCenter
{
public:
    frameListIconCenter(lv_obj_t* parent,frameiconlist_btn_t* btn_info,int txt_color,frameiconlist_icon_t* icon_info);
    ~frameListIconCenter(void);
    void set_IconName(void);
    int set_IconPtch(int icon_w, void * iconPatch);
    LvcppButton* btn=NULL;
    LvcppButton* btn_child=NULL;
    LvcppImageButton* icon=NULL;
    char IconName[64];

private:
    lv_obj_t* mainframe=NULL;
};

#endif // FRAME_LIST_ICON_CENTER_H
