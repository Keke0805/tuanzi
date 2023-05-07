CPPSRCS += LvglSimulator.cpp
CPPSRCS += serialtool.cpp

DEPPATH += --dep-path $(LVGL_DIR)/simulator
VPATH += :$(LVGL_DIR)/simulator
CPP_FLAGS += "-I$(LVGL_DIR)/simulator"


