#ifndef LVCPP_BUTTONMATRIX_H
#define LVCPP_BUTTONMATRIX_H

#include   "lvgl/lvgl.h"
#include   "../core/lvcpp_object.h"

class LvcppButtonMatrix : public LvcppObject
{
public:
    LvcppButtonMatrix(lv_obj_t* parent = nullptr);
    ~LvcppButtonMatrix();

    //set
    int set_map(const char ** map);
    int set_selected_btn(uint16_t btn_id);
    int set_btn_width(uint16_t btn_id, uint8_t width);
    int set_one_checked(bool en);

    //get
    const char ** get_map(void);
    int get_selected_btn(void);
    const char * get_btn_text(uint16_t btn_id);
    bool get_one_checked(void);
};

#endif // LVCPP_BUTTONMATRIX_H
