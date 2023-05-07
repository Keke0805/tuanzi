#include "menu_list.h"

menuList::menuList(lv_obj_t* parent)
{
    Label =new LvcppLabel(parent);
    chelImage = new LvcppImageButton(Label->myobj);
    LineLabel =new LvcppLabel(parent);
}

menuList::~menuList(void)
{
    if(LineLabel != NULL)
    {
        delete LineLabel;
        LineLabel = NULL;
    }
    if(chelImage != NULL)
    {
        delete chelImage;
        chelImage = NULL;
    }
    if(Label != NULL)
    {
        delete Label;
        Label = NULL;
    }
}
