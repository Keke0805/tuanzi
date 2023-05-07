include $(LVGL_DIR)/$(LVGL_DIR_NAME)/lvgl.mk
include $(LVGL_DIR)/$(LVGL_DRIVERS_NAME)/lv_drivers.mk

CFLAGS += "-I$(LVGL_DIR)/lv_code"
