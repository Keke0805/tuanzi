CPPSRCS += CJsonObject.cpp

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/base
VPATH += :$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/base

CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/base"
