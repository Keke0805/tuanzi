CPPSRCS += lvcpp_animimg.cpp
CPPSRCS += lvcpp_rotate_animimg.cpp
CPPSRCS += lvcpp_arc.cpp
CPPSRCS += lvcpp_bar.cpp
CPPSRCS += lvcpp_calendar.cpp
CPPSRCS += lvcpp_canvas.cpp
CPPSRCS += lvcpp_image.cpp
CPPSRCS += lvcpp_label.cpp
CPPSRCS += lvcpp_led.cpp
CPPSRCS += lvcpp_menu.cpp
CPPSRCS += lvcpp_messagebox.cpp
CPPSRCS += lvcpp_span.cpp
CPPSRCS += lvcpp_table.cpp
CPPSRCS += lvcpp_tabelflex.cpp
CPPSRCS += lvcpp_tableview.cpp
CPPSRCS += lvcpp_textarea.cpp
CPPSRCS += lvcpp_tileview.cpp
CPPSRCS += lvcpp_window.cpp
CPPSRCS += lvcpp_gif.cpp
CPPSRCS += lvcpp_qrcode.cpp

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/displayWidget
VPATH += :$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/displayWidget

CPPFLAGS += "-I$(LVGL_DIR)/$(LVGL_CPP_DIR_NAME)/displayWidget"
