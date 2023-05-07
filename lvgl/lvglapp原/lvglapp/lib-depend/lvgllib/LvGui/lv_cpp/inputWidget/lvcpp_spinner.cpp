#include "lvcpp_spinner.h"

LvcppSpinner::LvcppSpinner(lv_obj_t* parent)
{
    myobj = lv_spinner_create(parent, DEFAULT_TIME_CYCLE,DEFAULT_ARC_LENGTH);
}

LvcppSpinner::~LvcppSpinner(void)
{

}
