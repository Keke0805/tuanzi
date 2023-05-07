/**
 * @file lv_draw_g2d.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../lv_draw.h"
#include "lv_draw_g2d.h"
#include "../../core/lv_refr.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  GLOBAL PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_g2d_init_ctx(lv_disp_drv_t * drv, lv_draw_ctx_t * draw_ctx)
{
    LV_UNUSED(drv);

    lv_draw_g2d_ctx_t * draw_g2d_ctx = (lv_draw_g2d_ctx_t *) draw_ctx;
    lv_memset_00(draw_g2d_ctx, sizeof(lv_draw_g2d_ctx_t));

    draw_g2d_ctx->base_draw.draw_arc = lv_draw_g2d_arc;
    draw_g2d_ctx->base_draw.draw_rect = lv_draw_g2d_rect;
    draw_g2d_ctx->base_draw.draw_bg = lv_draw_g2d_bg;
    draw_g2d_ctx->base_draw.draw_letter = lv_draw_g2d_letter;
    draw_g2d_ctx->base_draw.draw_img_decoded = lv_draw_g2d_img_decoded;
    draw_g2d_ctx->base_draw.draw_line = lv_draw_g2d_line;
    draw_g2d_ctx->base_draw.draw_polygon = lv_draw_g2d_polygon;
    draw_g2d_ctx->base_draw.wait_for_finish = lv_draw_g2d_wait_for_finish;
    draw_g2d_ctx->blend = lv_draw_g2d_blend_basic;
}

void lv_draw_g2d_deinit_ctx(lv_disp_drv_t * drv, lv_draw_ctx_t * draw_ctx)
{
    LV_UNUSED(drv);

    lv_draw_g2d_ctx_t * draw_g2d_ctx = (lv_draw_g2d_ctx_t *) draw_ctx;
    lv_memset_00(draw_g2d_ctx, sizeof(lv_draw_g2d_ctx_t));
}

void lv_draw_g2d_wait_for_finish(lv_draw_ctx_t * draw_ctx)
{
    LV_UNUSED(draw_ctx);
    /*Nothing to wait for*/
    /*
    lv_disp_t * disp = _lv_refr_get_disp_refreshing();
    if(disp->driver && disp->driver->wait_cb) {
        while(1) {
            disp->driver->wait_cb(disp->driver);
        }
    }
    else {
        while(1);
    }
    lv_draw_g2d_wait_for_finish(draw_ctx);
    */
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
