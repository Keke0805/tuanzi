#ifndef LVCPP_TILEVIEW_H
#define LVCPP_TILEVIEW_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppTileView : public LvcppObject
{
public:
    LvcppTileView(lv_obj_t* parent = nullptr);
    ~LvcppTileView(void);

    //set
    lv_obj_t * add_tile(uint8_t col_id, uint8_t row_id, lv_dir_t dir);
    int set_tile(lv_obj_t* tile_obj,lv_anim_enable_t anim_en);
    int set_tile_id(uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en);

    //get
    lv_obj_t * get_tile_act(void);
};

#endif // LVCPP_TILEVIEW_H
