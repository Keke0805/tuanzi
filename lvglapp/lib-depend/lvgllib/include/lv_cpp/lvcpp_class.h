#pragma once
/*
auth: crc
version:Lv8.20-1.1
date:2022-08-04 11:00
*/
#include  "lvgl/lvgl.h"
#include  "lv_drivers/lv_drv_conf.h"
//core
#include  "lv_cpp/core/lvcpp_object.h"
#include  "lv_cpp/core/lvcpp_operator.h"
#include  "lv_cpp/core/lvcpp_screen.h"
#include  "lv_cpp/core/lvcpp_style.h"
#include  "lv_cpp/core/lvcpp_startup.h"
#include  "lv_cpp/core/lvcpp_timertask.h"
#include  "lv_cpp/core/lvcpp_mainscreen.h"
#include  "lv_cpp/core/sys_datetime.h"
#include  "lv_cpp/core/sys_thread.h"

//include
#include  "lv_cpp/include/lvcpp_sysconfig.h"
#include  "lv_cpp/include/lvcpp_singalslot.h"
#include  "lv_cpp/include/lvcpp_sysmsg.h"
#include  "lv_cpp/include/lvcpp_optapi.h"

//image
#include  "lv_cpp/image/lvcpp_bmp.h"

//widget
#include  "lv_cpp/button/lvcpp_pushbutton.h"
#include  "lv_cpp/button/lvcpp_imagebutton.h"
#include  "lv_cpp/button/lvcpp_buttonmatrix.h"

#include  "lv_cpp/displayWidget/lvcpp_animimg.h"
#include  "lv_cpp/displayWidget/lvcpp_rotate_animimg.h"
#include  "lv_cpp/displayWidget/lvcpp_arc.h"
#include  "lv_cpp/displayWidget/lvcpp_bar.h"
#include  "lv_cpp/displayWidget/lvcpp_calendar.h"
#include  "lv_cpp/displayWidget/lvcpp_canvas.h"
#include  "lv_cpp/displayWidget/lvcpp_gif.h"
#include  "lv_cpp/displayWidget/lvcpp_image.h"
#include  "lv_cpp/displayWidget/lvcpp_label.h"
#include  "lv_cpp/displayWidget/lvcpp_led.h"
#include  "lv_cpp/displayWidget/lvcpp_menu.h"
#include  "lv_cpp/displayWidget/lvcpp_messagebox.h"
#include  "lv_cpp/displayWidget/lvcpp_qrcode.h"
#include  "lv_cpp/displayWidget/lvcpp_span.h"
#include  "lv_cpp/displayWidget/lvcpp_table.h"
#include  "lv_cpp/displayWidget/lvcpp_tabelflex.h"
#include  "lv_cpp/displayWidget/lvcpp_tableview.h"
#include  "lv_cpp/displayWidget/lvcpp_textarea.h"
#include  "lv_cpp/displayWidget/lvcpp_tileview.h"
#include  "lv_cpp/displayWidget/lvcpp_window.h"

#include  "lv_cpp/inputWidget/lvcpp_roller.h"
#include  "lv_cpp/inputWidget/lvcpp_chart.h"
#include  "lv_cpp/inputWidget/lvcpp_checkbox.h"
#include  "lv_cpp/inputWidget/lvcpp_colorwheel.h"
#include  "lv_cpp/inputWidget/lvcpp_dropdown.h"
#include  "lv_cpp/inputWidget/lvcpp_keyboard.h"
#include  "lv_cpp/inputWidget/lvcpp_line.h"
#include  "lv_cpp/inputWidget/lvcpp_list.h"
#include  "lv_cpp/inputWidget/lvcpp_meter.h"
#include  "lv_cpp/inputWidget/lvcpp_slider.h"
#include  "lv_cpp/inputWidget/lvcpp_spinbox.h"
#include  "lv_cpp/inputWidget/lvcpp_spinner.h"
#include  "lv_cpp/inputWidget/lvcpp_switch.h"


