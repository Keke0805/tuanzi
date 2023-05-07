#ifndef FRAME_SCENELIST_H
#define FRAME_SCENELIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"

typedef struct _frame_scenelist_btn_t {
    int x;
    int y;
    int w;
    int h;
} frame_scenelist_t;

class frame_SceneList
{
public:
    frame_SceneList(lv_obj_t* parent,frame_scenelist_t* icon_info,frame_scenelist_t* SceneList);
    ~frame_SceneList(void);
    void update_frameSceneList(void* iconPatch);
    void update_frameSceneListIcon(void);
    LvcppButton* btn =NULL;
    int type =0;
    bool check_ok=false;

protected:
	void*  LIST_UNSEL_PNG=NULL;            
	void*  LIST_SEL_PNG=NULL;              
    void ui_image_decode(void);
    void ui_image_free(void);
private:
    lv_obj_t* mainframe=NULL;
    LvcppImageButton* icon=NULL;
};

#endif // FRAME_SCENELIST_H
