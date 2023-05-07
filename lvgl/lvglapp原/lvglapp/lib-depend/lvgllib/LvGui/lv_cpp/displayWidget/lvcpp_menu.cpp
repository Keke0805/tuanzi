#include "lvcpp_menu.h"

LvcppMenu::LvcppMenu(lv_obj_t* parent)
{
    myobj = lv_menu_create(parent);
}

LvcppMenu::~LvcppMenu(void)
{

}

lv_obj_t * LvcppMenu::add_page(char * title)
{

    return lv_menu_page_create(myobj, title);;
}

lv_obj_t * LvcppMenu::add_cont(void)
{

    return lv_menu_cont_create(myobj);;
}

lv_obj_t * LvcppMenu::add_section(void)
{

    return lv_menu_section_create(myobj);;
}

lv_obj_t * LvcppMenu::add_separator(void)
{

    return lv_menu_separator_create(myobj);;
}


//set
int LvcppMenu::set_page(lv_obj_t * page)
{
    lv_menu_set_page(myobj, page);
    return 0;
}

int LvcppMenu::set_sidebar_page(lv_obj_t * page)
{
    lv_menu_set_sidebar_page(myobj, page);
    return 0;
}

int LvcppMenu::set_mode_header( lv_menu_mode_header_t mode_header)
{
    lv_menu_set_mode_header(myobj, mode_header);
    return 0;
}

int LvcppMenu::set_mode_root_back_btn( lv_menu_mode_root_back_btn_t mode_root_back_btn)
{
    lv_menu_set_mode_root_back_btn(myobj, mode_root_back_btn);
    return 0;
}

int LvcppMenu::set_load_page_event(lv_obj_t * obj, lv_obj_t * page)
{
    lv_menu_set_load_page_event(myobj, obj, page);
    return 0;
}


//get
lv_obj_t * LvcppMenu::get_cur_main_page(void)
{

    return lv_menu_get_cur_main_page(myobj);
}

lv_obj_t * LvcppMenu::get_cur_sidebar_page(void)
{

    return lv_menu_get_cur_sidebar_page(myobj);
}

lv_obj_t * LvcppMenu::get_main_header(void)
{

    return lv_menu_get_main_header(myobj);
}

lv_obj_t * LvcppMenu::get_main_header_back_btn(void)
{

    return lv_menu_get_main_header_back_btn(myobj);
}

lv_obj_t * LvcppMenu::get_sidebar_header(void)
{

    return lv_menu_get_sidebar_header(myobj);
}

lv_obj_t * LvcppMenu::get_sidebar_header_back_btn(void)
{

    return lv_menu_get_sidebar_header_back_btn(myobj);
}

bool LvcppMenu::back_btn_is_root(lv_obj_t * obj)
{

    return lv_menu_back_btn_is_root(myobj, obj);
}

int LvcppMenu::clear_history(void)
{
    lv_menu_clear_history(myobj);
    return 0;
}
