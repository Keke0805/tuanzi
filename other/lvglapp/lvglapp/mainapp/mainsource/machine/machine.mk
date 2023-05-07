CPPSRCS += LvglMachine.cpp
CPPSRCS += UartContext.cpp
CPPSRCS += httpserver.cpp

DEPPATH += --dep-path $(LVGL_DIR)/machine
VPATH += :$(LVGL_DIR)/machine
CPP_FLAGS += "-I$(LVGL_DIR)/machine"


