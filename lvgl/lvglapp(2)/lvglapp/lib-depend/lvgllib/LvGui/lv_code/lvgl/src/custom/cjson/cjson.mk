CSRCS += cJSON.c

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/cjson
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/cjson
CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/custom/cjson"
