CPPSRCS += lvcpp_pushbutton.cpp
CPPSRCS += lvcpp_imagebutton.cpp
CPPSRCS += lvcpp_buttonmatrix.cpp


DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/button
VPATH += :$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/button

CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/button"
