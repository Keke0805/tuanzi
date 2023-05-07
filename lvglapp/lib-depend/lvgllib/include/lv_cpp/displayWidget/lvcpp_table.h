#ifndef LVCPP_TABLE_H
#define LVCPP_TABLE_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppTable : public LvcppObject
{
public:
    LvcppTable(lv_obj_t* parent = nullptr);
    ~LvcppTable(void);

    //set
    int set_cell_value(uint16_t row, uint16_t col, const char * txt);
    int set_row_cnt(uint16_t row_cnt);
    int set_col_cnt(uint16_t col_cnt);
    int set_col_width(uint16_t col_id, lv_coord_t w);
    int add_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl);
    int clear_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl);

    //get
    const char * get_cell_value(uint16_t row, uint16_t col);
    int get_row_cnt(void);
    int get_col_cnt(void);
    int get_col_width(uint16_t col);
    bool has_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl);
    int get_selected_cell(uint16_t * row, uint16_t * col);

};

#endif // LVCPP_TABLE_H
