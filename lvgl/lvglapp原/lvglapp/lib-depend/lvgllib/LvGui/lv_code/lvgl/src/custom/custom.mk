DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom
CFLAGS += "-I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom"

include $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/cjson/cjson.mk
include $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/linux/linux.mk
include $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/chinese_ime/lv_chinese_ime.mk