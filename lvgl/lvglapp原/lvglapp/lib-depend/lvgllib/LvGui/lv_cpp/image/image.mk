CPPSRCS += lvcpp_bmp.cpp

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/image
VPATH += :$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/image

CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/image"
