#include "lvcpp_messagebox.h"

LvcppMessageBox::LvcppMessageBox(lv_obj_t* parent)
{
    const char* str[2] = {"BTN1","BTN2"};
    myobj = lv_msgbox_create(parent, "MESSAGE BOX", "meaasge",str,true);
}

LvcppMessageBox::~LvcppMessageBox(void)
{

}
