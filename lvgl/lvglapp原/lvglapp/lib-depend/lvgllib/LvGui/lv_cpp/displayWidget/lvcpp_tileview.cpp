#include "lvcpp_tileview.h"

LvcppTileView::LvcppTileView(lv_obj_t* parent)
{
    myobj = lv_tileview_create(parent);
}

LvcppTileView::~LvcppTileView(void)
{

}

//set
lv_obj_t * LvcppTileView::add_tile(uint8_t col_id, uint8_t row_id, lv_dir_t dir)
{

    return lv_tileview_add_tile(myobj, col_id, row_id, dir);
}

int LvcppTileView::set_tile(lv_obj_t* tile_obj,lv_anim_enable_t anim_en)
{
    lv_obj_set_tile(myobj, tile_obj, anim_en);
    return 0;
}

int LvcppTileView::set_tile_id(uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en)
{
    lv_obj_set_tile_id(myobj, col_id, row_id, anim_en);
    return 0;
}

//get
lv_obj_t * LvcppTileView::get_tile_act(void)
{

    return lv_tileview_get_tile_act(myobj);
}
