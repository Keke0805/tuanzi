CSRCS += $(shell find -L $(LVGL_DIR)/mainstart/hotplugdetect -name \*.c)

DEPPATH += --dep-path $(LVGL_DIR)/mainstart/hotplugdetect
VPATH += :$(LVGL_DIR)/mainstart/hotplugdetect
CFLAGS += "-I$(LVGL_DIR)/mainstart/hotplugdetect"


