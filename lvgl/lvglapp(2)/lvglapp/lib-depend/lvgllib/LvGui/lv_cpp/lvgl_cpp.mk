include $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/base/cpp_base.mk
include $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/button/cpp_button.mk
include $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/core/cpp_core.mk
include $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/displayWidget/cpp_displayWidget.mk
include $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/font/cpp_font.mk
include $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/inputWidget/cpp_inputWidget.mk
include $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/image/image.mk

CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)"
