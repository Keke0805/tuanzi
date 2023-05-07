CPPSRCS += lvcpp_object.cpp
CPPSRCS += lvcpp_operator.cpp
CPPSRCS += lvcpp_screen.cpp
CPPSRCS += lvcpp_style.cpp
CPPSRCS += lvcpp_startup.cpp
CPPSRCS += lvcpp_timertask.cpp
CPPSRCS += lvcpp_mainscreen.cpp
CPPSRCS += sys_thread.cpp
CPPSRCS += sys_datetime.cpp

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/core
VPATH += :$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/core

CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/core"
