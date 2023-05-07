CPPSRCS += mainappstart.cpp

DEPPATH += --dep-path $(LVGL_DIR)/mainstart
VPATH += :$(LVGL_DIR)/mainstart
CPP_FLAGS += "-I$(LVGL_DIR)/mainstart"


