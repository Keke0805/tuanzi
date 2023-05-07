CSRCS += linux_tick_get.c

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/linux
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/linux
CFLAGS += "-I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/linux"