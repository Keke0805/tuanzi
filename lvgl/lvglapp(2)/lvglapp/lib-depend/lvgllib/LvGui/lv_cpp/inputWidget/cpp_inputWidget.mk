CPPSRCS += lvcpp_roller.cpp
CPPSRCS += lvcpp_chart.cpp
CPPSRCS += lvcpp_checkbox.cpp
CPPSRCS += lvcpp_colorwheel.cpp
CPPSRCS += lvcpp_dropdown.cpp
CPPSRCS += lvcpp_keyboard.cpp
CPPSRCS += lvcpp_line.cpp
CPPSRCS += lvcpp_list.cpp
CPPSRCS += lvcpp_meter.cpp
CPPSRCS += lvcpp_slider.cpp
CPPSRCS += lvcpp_spinbox.cpp
CPPSRCS += lvcpp_spinner.cpp
CPPSRCS += lvcpp_switch.cpp

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/inputWidget
VPATH += :$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/inputWidget

CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/inputWidget"
