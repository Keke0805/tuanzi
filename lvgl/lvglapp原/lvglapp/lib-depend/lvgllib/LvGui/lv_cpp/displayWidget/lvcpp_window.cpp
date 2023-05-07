#include "lvcpp_window.h"

LvcppWindow::LvcppWindow(lv_obj_t* parent)
{
    myobj = lv_win_create(parent, DEFAULT_HEADER_HEIGHT);
}

LvcppWindow::~LvcppWindow(void)
{

}

//set
lv_obj_t * LvcppWindow::add_title(const char * txt)
{

    return lv_win_add_title(myobj, txt);
}

lv_obj_t * LvcppWindow::add_btn(const void * icon, lv_coord_t btn_w)
{

    return lv_win_add_btn(myobj, icon, btn_w);
}

//get
lv_obj_t * LvcppWindow::get_header(void)
{

    return lv_win_get_header(myobj);
}

lv_obj_t * LvcppWindow::get_content(void)
{

    return lv_win_get_content(myobj);
}
