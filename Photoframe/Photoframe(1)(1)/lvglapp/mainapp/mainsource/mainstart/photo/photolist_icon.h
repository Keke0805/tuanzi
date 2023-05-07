#ifndef PHOTOLIST_ICON_H
#define PHOTOLIST_ICON_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

class photolistIcon
{
public:
    photolistIcon(lv_obj_t* parent =nullptr);
    ~photolistIcon(void);
    void update_sceneList(void* iconPatch);
    void update_sceneListIcon(void);
    LvcppButton* btn =NULL;
    LvcppImageButton* icon=NULL;
	int myindex =0;
    int type =0;
    bool bmp_valid=false;
    bool check_ok=false;
    char filepatch[1024]={0};
protected:
	
	void*  LIST_SEL_PNG=NULL;                 
	void*  LIST_UNSEL_PNG=NULL;
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    lv_obj_t* mainframe=NULL;
};

#endif // PHOTOLIST_ICON_H
