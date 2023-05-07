#ifndef LVCPP_MENU_H
#define LVCPP_MENU_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppMenu : public LvcppObject
{
public:
    enum{
        Page,
        Cont,
        Section,
        Separator
    };

    LvcppMenu(lv_obj_t* parent = nullptr);
    ~LvcppMenu(void);

    lv_obj_t * add_page(char * title);
    lv_obj_t * add_cont(void);
    lv_obj_t * add_section(void);
    lv_obj_t * add_separator(void);

    //set
    int set_page(lv_obj_t * page);
    int set_sidebar_page(lv_obj_t * page);
    int set_mode_header(lv_menu_mode_header_t mode_header);
    int set_mode_root_back_btn(lv_menu_mode_root_back_btn_t mode_root_back_btn);
    int set_load_page_event(lv_obj_t * obj, lv_obj_t * page);

    //get
    lv_obj_t * get_cur_main_page(void);
    lv_obj_t * get_cur_sidebar_page(void);
    lv_obj_t * get_main_header(void);
    lv_obj_t * get_main_header_back_btn(void);
    lv_obj_t * get_sidebar_header(void);
    lv_obj_t * get_sidebar_header_back_btn(void);
    bool back_btn_is_root(lv_obj_t * obj);
    int clear_history(void);

};

#endif // LVCPP_MENU_H
