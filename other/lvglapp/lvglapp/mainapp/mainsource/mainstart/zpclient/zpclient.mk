CSRCS += $(shell find -L $(LVGL_DIR)/mainstart/zpclient -name \*.c)

DEPPATH += --dep-path $(LVGL_DIR)/mainstart/zpclient
VPATH += :$(LVGL_DIR)/mainstart/zpclient
CFLAGS += "-I$(LVGL_DIR)/mainstart/zpclient"


