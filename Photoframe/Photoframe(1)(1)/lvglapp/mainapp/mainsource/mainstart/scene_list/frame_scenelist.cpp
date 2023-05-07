#include "frame_scenelist.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"

#include  "common/common.h"

void frame_SceneList::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    LIST_UNSEL_PNG=(void*)parse_image_from_file(LIST_UNSEL_PNG_PATH);
    LIST_SEL_PNG=(void*)parse_image_from_file(LIST_SEL_PNG_PATH);
#endif
}

void frame_SceneList::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(LIST_UNSEL_PNG);
    free_image(LIST_SEL_PNG);
#endif
}


frame_SceneList::frame_SceneList(lv_obj_t* parent,frame_scenelist_t* icon_info,frame_scenelist_t* SceneList)
{
	ui_image_decode();
    btn = new LvcppButton(parent);
    btn->set_size(SceneList->w,SceneList->h);
    btn->align(LV_ALIGN_TOP_LEFT,SceneList->x,SceneList->y);
    btn->set_main_bg_opa(LV_OPA_0);
    btn->set_main_radius(0);
    btn->set_main_pad_all(0);
    btn->set_main_border_width(0);


    mainframe = btn->myobj;
    icon = new LvcppImageButton(mainframe);
    icon->set_size(icon_info->w,icon_info->h);
    icon->set_main_radius(0);
    icon->align(LV_ALIGN_TOP_LEFT,icon_info->x,icon_info->y);
    icon->show(false);
}

frame_SceneList::~frame_SceneList(void)
{
	if(icon != NULL)
    {
        delete icon;
        icon =NULL;
    }
    if(btn != NULL)
    {
        delete btn;
        btn =NULL;
    }
	ui_image_free();
}

void frame_SceneList::update_frameSceneList(void* iconPatch)
{
	 if(btn != NULL)
    	btn->set_main_bg_img_src(iconPatch);
}

void frame_SceneList::update_frameSceneListIcon(void)
{
    if(type !=0)
    {
    	if(icon != NULL)
        	icon->show(true);
        if(type ==1)
        {
        	if(icon != NULL)
            	icon->set_main_bg_img_src(LIST_UNSEL_PNG);
        }
        else if(type ==2)
        {
        	if(icon != NULL)
            	icon->set_main_bg_img_src(LIST_SEL_PNG);
        }
    }
    else
    {
    	if(icon != NULL)
        	icon->show(false);
    }
}
