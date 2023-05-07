#include "lvcpp_checkbox.h"

LvcppCheckBox::LvcppCheckBox(lv_obj_t* parent)
{
    myobj = lv_checkbox_create(parent);
}

LvcppCheckBox::~LvcppCheckBox(void)
{

}

//set
int LvcppCheckBox::set_text(const char * txt)
{
    lv_checkbox_set_text(myobj,txt);
    return 0;
}

int LvcppCheckBox::set_text_static(const char * txt)
{
    lv_checkbox_set_text_static(myobj,txt);
    return 0;
}

//get
const char * LvcppCheckBox::get_text(void)
{

    return lv_checkbox_get_text(myobj);
}
