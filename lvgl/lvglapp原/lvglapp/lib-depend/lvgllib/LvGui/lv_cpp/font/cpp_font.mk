CPPSRCS += lvcpp_dotarrayfont.cpp
CPPSRCS += lvcpp_freetypefont.cpp


DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/font
VPATH += :$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/font

CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/font"
