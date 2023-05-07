#include "photolist_icon.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include  "common/common.h"


void photolistIcon::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    LIST_UNSEL_PNG=(void*)parse_image_from_file(LIST_UNSEL_PNG_PATH);
    LIST_SEL_PNG=(void*)parse_image_from_file(LIST_SEL_PNG_PATH);
#endif

}
void photolistIcon::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(LIST_UNSEL_PNG);
    free_image(LIST_SEL_PNG);
#endif
}
photolistIcon::photolistIcon(lv_obj_t* parent)
{
    ui_image_decode();
    btn = new LvcppButton(parent);
    btn->set_main_bg_opa(LV_OPA_0);
    btn->set_main_radius(0);
    btn->set_main_pad_all(0);
    btn->set_main_border_width(0);

    mainframe = btn->myobj;
    icon = new LvcppImageButton(mainframe);
    icon->set_main_radius(0);
    icon->show(false);
}
photolistIcon::~photolistIcon(void)
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
void photolistIcon::update_sceneList(void* iconPatch)
{
     if(btn != NULL)
        btn->set_main_bg_img_src(iconPatch);
}

void photolistIcon::update_sceneListIcon(void)
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
