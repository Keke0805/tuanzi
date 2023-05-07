CPPSRCS += http.cpp

DEPPATH += --dep-path $(LVGL_DIR)/network
VPATH += :$(LVGL_DIR)/network
CPP_FLAGS += "-I$(LVGL_DIR)/network"


