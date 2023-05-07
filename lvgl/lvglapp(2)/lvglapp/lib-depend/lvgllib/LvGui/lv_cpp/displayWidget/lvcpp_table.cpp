#include "lvcpp_table.h"

LvcppTable::LvcppTable(lv_obj_t* parent)
{
    myobj = lv_table_create(parent);
}

LvcppTable::~LvcppTable(void)
{

}

//set
int LvcppTable::set_cell_value(uint16_t row, uint16_t col, const char * txt)
{
    lv_table_set_cell_value(myobj, row, col, txt);
    return 0;
}


int LvcppTable::set_row_cnt(uint16_t row_cnt)
{
    lv_table_set_row_cnt(myobj, row_cnt);
    return 0;
}

int LvcppTable::set_col_cnt(uint16_t col_cnt)
{
    lv_table_set_col_cnt(myobj, col_cnt);
    return 0;
}

int LvcppTable::set_col_width(uint16_t col_id, lv_coord_t w)
{
    lv_table_set_col_width(myobj, col_id, w);
    return 0;
}

int LvcppTable::add_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl)
{
    lv_table_add_cell_ctrl(myobj, row, col, ctrl);
    return 0;
}

int LvcppTable::clear_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl)
{
    lv_table_clear_cell_ctrl(myobj, row, col, ctrl);
    return 0;
}


//get
const char * LvcppTable::get_cell_value(uint16_t row, uint16_t col)
{

    return lv_table_get_cell_value(myobj, row, col);
}

int LvcppTable::get_row_cnt(void)
{

    return lv_table_get_row_cnt(myobj);

}

int LvcppTable::get_col_cnt(void)
{

    return lv_table_get_col_cnt(myobj);
}

int LvcppTable::get_col_width(uint16_t col)
{

    return lv_table_get_col_width(myobj, col);
}

bool LvcppTable::has_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl)
{

    return lv_table_has_cell_ctrl(myobj, row, col, ctrl);
}

int LvcppTable::get_selected_cell(uint16_t * row, uint16_t * col)
{
    lv_table_get_selected_cell(myobj, row, col);
    return 0;
}
