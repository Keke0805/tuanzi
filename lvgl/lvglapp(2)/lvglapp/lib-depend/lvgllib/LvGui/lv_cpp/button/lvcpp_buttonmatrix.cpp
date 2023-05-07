#include "lvcpp_buttonmatrix.h"

LvcppButtonMatrix::LvcppButtonMatrix(lv_obj_t* parent)
{
    myobj = lv_btnmatrix_create(parent);
}
LvcppButtonMatrix::~LvcppButtonMatrix()
{

}

//set
int LvcppButtonMatrix::set_map(const char ** map)
{
    lv_btnmatrix_set_map(myobj,map);
    return 0;
}

int LvcppButtonMatrix::set_selected_btn(uint16_t btn_id)
{
    lv_btnmatrix_set_selected_btn(myobj,btn_id);
    return 0;
}

int LvcppButtonMatrix::set_btn_width(uint16_t btn_id, uint8_t width)
{
    lv_btnmatrix_set_btn_width(myobj, btn_id, width);
    return 0;
}


int LvcppButtonMatrix::set_one_checked(bool en)
{
    lv_btnmatrix_set_one_checked(myobj,en);
    return 0;
}

//get
const char ** LvcppButtonMatrix::get_map(void)
{
    return lv_btnmatrix_get_map(myobj);
}


int LvcppButtonMatrix::get_selected_btn(void)
{
    return lv_btnmatrix_get_selected_btn(myobj);
}

const char * LvcppButtonMatrix::get_btn_text(uint16_t btn_id)
{

    return lv_btnmatrix_get_btn_text(myobj,btn_id);
}


bool LvcppButtonMatrix::get_one_checked(void)
{

    return lv_btnmatrix_get_one_checked(myobj);
}
