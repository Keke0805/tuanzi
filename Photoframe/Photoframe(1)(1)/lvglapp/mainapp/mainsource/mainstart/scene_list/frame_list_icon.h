#ifndef FRAME_LIST_ICON_H
#define FRAME_LIST_ICON_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"

enum {
    PFALSH_ALL = 0,
    PFALSH_INTERNAL,
    PFALSH_SD,
    PFALSH_USB,
    PFALSH_FILE,
    PFALSH_LOVE,
    PFALSH_USER,
    PFALSH_MAX
};
typedef uint32_t pflash_list_t;

typedef struct _framelist_btn_t {
    int x;
    int y;
    int w;
    int h;
    int bg_color;
    int line_h;
    int line_color;
    lv_align_t align;
} framelist_btn_t;

typedef struct _framelist_txt_t {
    int x;
    int y;
    int w;
    int h;
    int font_size;
    int txt_color;
    lv_align_t align;
	lv_font_t * font;
} framelist_txt_t;

typedef struct _framelist_icon_t {
    int x;
    int y;
    int w;
    int h;
    bool showStatus;
    void *iconPatch;
    lv_align_t align;
} framelist_icon_t;

class frameListIcon
{
public:
    frameListIcon(lv_obj_t* parent,framelist_btn_t* btn_info,framelist_txt_t* txt_info,framelist_icon_t*icon_info);
    ~frameListIcon(void);
    void set_IconName(char * iconname);
    void set_IconPtch(const void *iconPatch);
    LvcppButton* btn=NULL;
    LvcppImageButton* icon=NULL;
    LvcppImageButton* iconLine=NULL;
    char IconName[64]={0};
    bool check_ok=false;
private:
    lv_obj_t* mainframe=NULL;
};

#endif // FRAME_LIST_ICON_H
