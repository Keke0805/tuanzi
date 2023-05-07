#ifndef LVCPP_DROPDOWN_H
#define LVCPP_DROPDOWN_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppDropdown : public LvcppObject
{
public:
    LvcppDropdown(lv_obj_t* parent = nullptr);
    ~LvcppDropdown(void);

    //set
    int set_text(const char * txt);
    int set_options(const char * options);
    int set_options_static(const char * options);
    int add_option(const char * option, uint32_t pos);
    int clear_options(void);
    int set_selected(uint16_t sel_opt);
    int set_dir(lv_dir_t dir);
    int set_symbol(const void * symbol);
    int set_selected_highlight(bool en);


    //get
    lv_obj_t * get_list(void);
    const char * get_text(void);
    const char * get_options(void);
    int get_selected(void);
    int get_option_cnt(void);
    int get_selected_str(char * buf, uint32_t buf_size);
    const char * get_symbol(void);
    bool get_selected_highlight(void);
    int get_dir(void);

};

#endif // LVCPP_DROPDOWN_H
