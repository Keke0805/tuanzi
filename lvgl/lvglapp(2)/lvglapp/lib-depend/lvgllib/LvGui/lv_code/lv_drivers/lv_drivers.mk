CSRCS += $(wildcard $(LVGL_DIR)/$(LVGL_DRIVERS_NAME)/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(LVGL_DRIVERS_NAME)/wayland/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(LVGL_DRIVERS_NAME)/indev/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(LVGL_DRIVERS_NAME)/gtkdrv/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(LVGL_DRIVERS_NAME)/display/*.c)

CFLAGS += "-I$(LVGL_DIR)/$(LVGL_DRIVERS_NAME)"
