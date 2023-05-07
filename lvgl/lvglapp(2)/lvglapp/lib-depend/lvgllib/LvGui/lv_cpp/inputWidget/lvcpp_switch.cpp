#include "lvcpp_switch.h"

LvcppSwitch::LvcppSwitch(lv_obj_t* parent)
{
    myobj = lv_switch_create(parent);
}

LvcppSwitch::~LvcppSwitch(void)
{

}
