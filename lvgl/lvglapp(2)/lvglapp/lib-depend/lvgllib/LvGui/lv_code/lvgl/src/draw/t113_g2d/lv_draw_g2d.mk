CSRCS += lv_draw_g2d.c
CSRCS += lv_draw_g2d_arc.c
CSRCS += lv_draw_g2d_blend.c
CSRCS += lv_draw_g2d_img.c
CSRCS += lv_draw_g2d_letter.c
CSRCS += lv_draw_g2d_line.c
CSRCS += lv_draw_g2d_rect.c
CSRCS += lv_draw_g2d_polygon.c
CSRCS += lv_draw_g2d_gradient.c
CSRCS += lv_draw_g2d_dither.c

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/draw/t113_g2d
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/draw/t113_g2d

CFLAGS += "-I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/draw/t113_g2d"
