INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/src/core/lv_disp.c \
    $$PWD/src/core/lv_event.c \
    $$PWD/src/core/lv_group.c \
    $$PWD/src/core/lv_indev.c \
    $$PWD/src/core/lv_indev_scroll.c \
    $$PWD/src/core/lv_obj.c \
    $$PWD/src/core/lv_obj_class.c \
    $$PWD/src/core/lv_obj_draw.c \
    $$PWD/src/core/lv_obj_pos.c \
    $$PWD/src/core/lv_obj_scroll.c \
    $$PWD/src/core/lv_obj_style.c \
    $$PWD/src/core/lv_obj_style_gen.c \
    $$PWD/src/core/lv_obj_tree.c \
    $$PWD/src/core/lv_refr.c \
    $$PWD/src/core/lv_theme.c \
    $$PWD/src/custom/chinese_ime/chinese_ime.c \
    $$PWD/src/custom/chinese_ime/zh_cn_pinyin_dict.c \
    $$PWD/src/custom/cjson/cJSON.c \
    $$PWD/src/custom/linux/linux_tick_get.c \
    $$PWD/src/draw/lv_draw.c \
    $$PWD/src/draw/lv_draw_arc.c \
    $$PWD/src/draw/lv_draw_img.c \
    $$PWD/src/draw/lv_draw_label.c \
    $$PWD/src/draw/lv_draw_line.c \
    $$PWD/src/draw/lv_draw_mask.c \
    $$PWD/src/draw/lv_draw_rect.c \
    $$PWD/src/draw/lv_draw_triangle.c \
    $$PWD/src/draw/lv_img_buf.c \
    $$PWD/src/draw/lv_img_cache.c \
    $$PWD/src/draw/lv_img_decoder.c \
    $$PWD/src/draw/nxp_pxp/lv_gpu_nxp_pxp.c \
    $$PWD/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.c \
    $$PWD/src/draw/nxp_vglite/lv_gpu_nxp_vglite.c \
    $$PWD/src/draw/sdl/lv_draw_sdl.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_arc.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_bg.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_composite.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_img.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_label.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_line.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_mask.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_polygon.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_rect.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_stack_blur.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_texture_cache.c \
    $$PWD/src/draw/sdl/lv_draw_sdl_utils.c \
    $$PWD/src/draw/stm32_dma2d/lv_gpu_stm32_dma2d.c \
    $$PWD/src/draw/sw/lv_draw_sw.c \
    $$PWD/src/draw/sw/lv_draw_sw_arc.c \
    $$PWD/src/draw/sw/lv_draw_sw_blend.c \
    $$PWD/src/draw/sw/lv_draw_sw_dither.c \
    $$PWD/src/draw/sw/lv_draw_sw_gradient.c \
    $$PWD/src/draw/sw/lv_draw_sw_img.c \
    $$PWD/src/draw/sw/lv_draw_sw_letter.c \
    $$PWD/src/draw/sw/lv_draw_sw_line.c \
    $$PWD/src/draw/sw/lv_draw_sw_polygon.c \
    $$PWD/src/draw/sw/lv_draw_sw_rect.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_arc.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_blend.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_dither.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_gradient.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_img.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_letter.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_line.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_polygon.c \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_rect.c \
    $$PWD/src/extra/layouts/flex/lv_flex.c \
    $$PWD/src/extra/layouts/grid/lv_grid.c \
    $$PWD/src/extra/libs/bmp/lv_bmp.c \
    $$PWD/src/extra/libs/ffmpeg/lv_ffmpeg.c \
    $$PWD/src/extra/libs/freetype/lv_freetype.c \
    $$PWD/src/extra/libs/fsdrv/lv_fs_fatfs.c \
    $$PWD/src/extra/libs/fsdrv/lv_fs_posix.c \
    $$PWD/src/extra/libs/fsdrv/lv_fs_stdio.c \
    $$PWD/src/extra/libs/fsdrv/lv_fs_win32.c \
    $$PWD/src/extra/libs/gif/gifdec.c \
    $$PWD/src/extra/libs/gif/lv_gif.c \
    $$PWD/src/extra/libs/png/lodepng.c \
    $$PWD/src/extra/libs/png/lv_png.c \
    $$PWD/src/extra/libs/qrcode/lv_qrcode.c \
    $$PWD/src/extra/libs/qrcode/qrcodegen.c \
    $$PWD/src/extra/libs/rlottie/lv_rlottie.c \
    $$PWD/src/extra/libs/sjpg/lv_sjpg.c \
    $$PWD/src/extra/libs/sjpg/tjpgd.c \
    $$PWD/src/extra/lv_extra.c \
    $$PWD/src/extra/others/file_explorer/lv_file_explorer.c \
    $$PWD/src/extra/others/gridnav/lv_gridnav.c \
    $$PWD/src/extra/others/monkey/lv_monkey.c \
    $$PWD/src/extra/others/snapshot/lv_snapshot.c \
    $$PWD/src/extra/themes/basic/lv_theme_basic.c \
    $$PWD/src/extra/themes/default/lv_theme_default.c \
    $$PWD/src/extra/themes/mono/lv_theme_mono.c \
    $$PWD/src/extra/widgets/animimg/lv_animimg.c \
    $$PWD/src/extra/widgets/calendar/lv_calendar.c \
    $$PWD/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
    $$PWD/src/extra/widgets/calendar/lv_calendar_header_dropdown.c \
    $$PWD/src/extra/widgets/chart/lv_chart.c \
    $$PWD/src/extra/widgets/colorwheel/lv_colorwheel.c \
    $$PWD/src/extra/widgets/imgbtn/lv_imgbtn.c \
    $$PWD/src/extra/widgets/keyboard/lv_keyboard.c \
    $$PWD/src/extra/widgets/led/lv_led.c \
    $$PWD/src/extra/widgets/list/lv_list.c \
    $$PWD/src/extra/widgets/menu/lv_menu.c \
    $$PWD/src/extra/widgets/meter/lv_meter.c \
    $$PWD/src/extra/widgets/msgbox/lv_msgbox.c \
    $$PWD/src/extra/widgets/span/lv_span.c \
    $$PWD/src/extra/widgets/spinbox/lv_spinbox.c \
    $$PWD/src/extra/widgets/spinner/lv_spinner.c \
    $$PWD/src/extra/widgets/tabview/lv_tabview.c \
    $$PWD/src/extra/widgets/tileview/lv_tileview.c \
    $$PWD/src/extra/widgets/win/lv_win.c \
    $$PWD/src/font/lv_font.c \
    $$PWD/src/font/lv_font_dejavu_16_persian_hebrew.c \
    $$PWD/src/font/lv_font_dotarray_default.cpp \
    $$PWD/src/font/lv_font_fmt_txt.c \
    $$PWD/src/font/lv_font_freetype_default.c \
    $$PWD/src/font/lv_font_loader.c \
    $$PWD/src/font/lv_font_montserrat_10.c \
    $$PWD/src/font/lv_font_montserrat_12.c \
    $$PWD/src/font/lv_font_montserrat_12_subpx.c \
    $$PWD/src/font/lv_font_montserrat_14.c \
    $$PWD/src/font/lv_font_montserrat_16.c \
    $$PWD/src/font/lv_font_montserrat_18.c \
    $$PWD/src/font/lv_font_montserrat_20.c \
    $$PWD/src/font/lv_font_montserrat_22.c \
    $$PWD/src/font/lv_font_montserrat_24.c \
    $$PWD/src/font/lv_font_montserrat_26.c \
    $$PWD/src/font/lv_font_montserrat_28.c \
    $$PWD/src/font/lv_font_montserrat_28_compressed.c \
    $$PWD/src/font/lv_font_montserrat_30.c \
    $$PWD/src/font/lv_font_montserrat_32.c \
    $$PWD/src/font/lv_font_montserrat_34.c \
    $$PWD/src/font/lv_font_montserrat_36.c \
    $$PWD/src/font/lv_font_montserrat_38.c \
    $$PWD/src/font/lv_font_montserrat_40.c \
    $$PWD/src/font/lv_font_montserrat_42.c \
    $$PWD/src/font/lv_font_montserrat_44.c \
    $$PWD/src/font/lv_font_montserrat_46.c \
    $$PWD/src/font/lv_font_montserrat_48.c \
    $$PWD/src/font/lv_font_montserrat_8.c \
    $$PWD/src/font/lv_font_simsun_16_cjk.c \
    $$PWD/src/font/lv_font_unscii_16.c \
    $$PWD/src/font/lv_font_unscii_8.c \
    $$PWD/src/hal/lv_hal_disp.c \
    $$PWD/src/hal/lv_hal_indev.c \
    $$PWD/src/hal/lv_hal_tick.c \
    $$PWD/src/misc/lv_anim.c \
    $$PWD/src/misc/lv_anim_timeline.c \
    $$PWD/src/misc/lv_area.c \
    $$PWD/src/misc/lv_async.c \
    $$PWD/src/misc/lv_bidi.c \
    $$PWD/src/misc/lv_color.c \
    $$PWD/src/misc/lv_fs.c \
    $$PWD/src/misc/lv_gc.c \
    $$PWD/src/misc/lv_ll.c \
    $$PWD/src/misc/lv_log.c \
    $$PWD/src/misc/lv_lru.c \
    $$PWD/src/misc/lv_math.c \
    $$PWD/src/misc/lv_mem.c \
    $$PWD/src/misc/lv_printf.c \
    $$PWD/src/misc/lv_style.c \
    $$PWD/src/misc/lv_style_gen.c \
    $$PWD/src/misc/lv_templ.c \
    $$PWD/src/misc/lv_timer.c \
    $$PWD/src/misc/lv_tlsf.c \
    $$PWD/src/misc/lv_txt.c \
    $$PWD/src/misc/lv_txt_ap.c \
    $$PWD/src/misc/lv_utils.c \
    $$PWD/src/widgets/lv_arc.c \
    $$PWD/src/widgets/lv_bar.c \
    $$PWD/src/widgets/lv_btn.c \
    $$PWD/src/widgets/lv_btnmatrix.c \
    $$PWD/src/widgets/lv_canvas.c \
    $$PWD/src/widgets/lv_checkbox.c \
    $$PWD/src/widgets/lv_dropdown.c \
    $$PWD/src/widgets/lv_img.c \
    $$PWD/src/widgets/lv_label.c \
    $$PWD/src/widgets/lv_line.c \
    $$PWD/src/widgets/lv_objx_templ.c \
    $$PWD/src/widgets/lv_roller.c \
    $$PWD/src/widgets/lv_slider.c \
    $$PWD/src/widgets/lv_switch.c \
    $$PWD/src/widgets/lv_table.c \
    $$PWD/src/widgets/lv_textarea.c

HEADERS += \
    $$PWD/lvgl.h \
    $$PWD/lv_conf.h \
    $$PWD/src/core/lv_disp.h \
    $$PWD/src/core/lv_event.h \
    $$PWD/src/core/lv_group.h \
    $$PWD/src/core/lv_indev.h \
    $$PWD/src/core/lv_indev_scroll.h \
    $$PWD/src/core/lv_obj.h \
    $$PWD/src/core/lv_obj_class.h \
    $$PWD/src/core/lv_obj_draw.h \
    $$PWD/src/core/lv_obj_pos.h \
    $$PWD/src/core/lv_obj_scroll.h \
    $$PWD/src/core/lv_obj_style.h \
    $$PWD/src/core/lv_obj_style_gen.h \
    $$PWD/src/core/lv_obj_tree.h \
    $$PWD/src/core/lv_refr.h \
    $$PWD/src/core/lv_theme.h \
    $$PWD/src/custom/chinese_ime/chinese_ime.h \
    $$PWD/src/custom/chinese_ime/lv_chinese_ime.h \
    $$PWD/src/custom/chinese_ime/lv_chinese_ime_conf.h \
    $$PWD/src/custom/cjson/cJSON.h \
    $$PWD/src/draw/lv_draw.h \
    $$PWD/src/draw/lv_draw_arc.h \
    $$PWD/src/draw/lv_draw_img.h \
    $$PWD/src/draw/lv_draw_label.h \
    $$PWD/src/draw/lv_draw_line.h \
    $$PWD/src/draw/lv_draw_mask.h \
    $$PWD/src/draw/lv_draw_rect.h \
    $$PWD/src/draw/lv_draw_triangle.h \
    $$PWD/src/draw/lv_img_buf.h \
    $$PWD/src/draw/lv_img_cache.h \
    $$PWD/src/draw/lv_img_decoder.h \
    $$PWD/src/draw/nxp_pxp/lv_gpu_nxp_pxp.h \
    $$PWD/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.h \
    $$PWD/src/draw/nxp_vglite/lv_gpu_nxp_vglite.h \
    $$PWD/src/draw/sdl/lv_draw_sdl.h \
    $$PWD/src/draw/sdl/lv_draw_sdl_composite.h \
    $$PWD/src/draw/sdl/lv_draw_sdl_img.h \
    $$PWD/src/draw/sdl/lv_draw_sdl_mask.h \
    $$PWD/src/draw/sdl/lv_draw_sdl_priv.h \
    $$PWD/src/draw/sdl/lv_draw_sdl_rect.h \
    $$PWD/src/draw/sdl/lv_draw_sdl_stack_blur.h \
    $$PWD/src/draw/sdl/lv_draw_sdl_texture_cache.h \
    $$PWD/src/draw/sdl/lv_draw_sdl_utils.h \
    $$PWD/src/draw/stm32_dma2d/lv_gpu_stm32_dma2d.h \
    $$PWD/src/draw/sw/lv_draw_sw.h \
    $$PWD/src/draw/sw/lv_draw_sw_blend.h \
    $$PWD/src/draw/sw/lv_draw_sw_dither.h \
    $$PWD/src/draw/sw/lv_draw_sw_gradient.h \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d.h \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_blend.h \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_dither.h \
    $$PWD/src/draw/t113_g2d/lv_draw_g2d_gradient.h \
    $$PWD/src/extra/layouts/flex/lv_flex.h \
    $$PWD/src/extra/layouts/grid/lv_grid.h \
    $$PWD/src/extra/layouts/lv_layouts.h \
    $$PWD/src/extra/libs/bmp/lv_bmp.h \
    $$PWD/src/extra/libs/ffmpeg/lv_ffmpeg.h \
    $$PWD/src/extra/libs/freetype/lv_freetype.h \
    $$PWD/src/extra/libs/fsdrv/lv_fsdrv.h \
    $$PWD/src/extra/libs/gif/gifdec.h \
    $$PWD/src/extra/libs/gif/lv_gif.h \
    $$PWD/src/extra/libs/lv_libs.h \
    $$PWD/src/extra/libs/png/lodepng.h \
    $$PWD/src/extra/libs/png/lv_png.h \
    $$PWD/src/extra/libs/qrcode/lv_qrcode.h \
    $$PWD/src/extra/libs/qrcode/qrcodegen.h \
    $$PWD/src/extra/libs/rlottie/lv_rlottie.h \
    $$PWD/src/extra/libs/sjpg/lv_sjpg.h \
    $$PWD/src/extra/libs/sjpg/tjpgd.h \
    $$PWD/src/extra/libs/sjpg/tjpgdcnf.h \
    $$PWD/src/extra/lv_extra.h \
    $$PWD/src/extra/others/file_explorer/lv_file_explorer.h \
    $$PWD/src/extra/others/gridnav/lv_gridnav.h \
    $$PWD/src/extra/others/lv_others.h \
    $$PWD/src/extra/others/monkey/lv_monkey.h \
    $$PWD/src/extra/others/snapshot/lv_snapshot.h \
    $$PWD/src/extra/themes/basic/lv_theme_basic.h \
    $$PWD/src/extra/themes/default/lv_theme_default.h \
    $$PWD/src/extra/themes/lv_themes.h \
    $$PWD/src/extra/themes/mono/lv_theme_mono.h \
    $$PWD/src/extra/widgets/animimg/lv_animimg.h \
    $$PWD/src/extra/widgets/calendar/lv_calendar.h \
    $$PWD/src/extra/widgets/calendar/lv_calendar_header_arrow.h \
    $$PWD/src/extra/widgets/calendar/lv_calendar_header_dropdown.h \
    $$PWD/src/extra/widgets/chart/lv_chart.h \
    $$PWD/src/extra/widgets/colorwheel/lv_colorwheel.h \
    $$PWD/src/extra/widgets/imgbtn/lv_imgbtn.h \
    $$PWD/src/extra/widgets/keyboard/lv_keyboard.h \
    $$PWD/src/extra/widgets/led/lv_led.h \
    $$PWD/src/extra/widgets/list/lv_list.h \
    $$PWD/src/extra/widgets/lv_widgets.h \
    $$PWD/src/extra/widgets/menu/lv_menu.h \
    $$PWD/src/extra/widgets/meter/lv_meter.h \
    $$PWD/src/extra/widgets/msgbox/lv_msgbox.h \
    $$PWD/src/extra/widgets/span/lv_span.h \
    $$PWD/src/extra/widgets/spinbox/lv_spinbox.h \
    $$PWD/src/extra/widgets/spinner/lv_spinner.h \
    $$PWD/src/extra/widgets/tabview/lv_tabview.h \
    $$PWD/src/extra/widgets/tileview/lv_tileview.h \
    $$PWD/src/extra/widgets/win/lv_win.h \
    $$PWD/src/font/lv_font.h \
    $$PWD/src/font/lv_font_fmt_txt.h \
    $$PWD/src/font/lv_font_freetype_default.h \
    $$PWD/src/font/lv_font_loader.h \
    $$PWD/src/font/lv_symbol_def.h \
    $$PWD/src/hal/lv_hal.h \
    $$PWD/src/hal/lv_hal_disp.h \
    $$PWD/src/hal/lv_hal_indev.h \
    $$PWD/src/hal/lv_hal_tick.h \
    $$PWD/src/lv_api_map.h \
    $$PWD/src/lv_conf_internal.h \
    $$PWD/src/lv_conf_kconfig.h \
    $$PWD/src/lvgl.h \
    $$PWD/src/misc/lv_anim.h \
    $$PWD/src/misc/lv_anim_timeline.h \
    $$PWD/src/misc/lv_area.h \
    $$PWD/src/misc/lv_assert.h \
    $$PWD/src/misc/lv_async.h \
    $$PWD/src/misc/lv_bidi.h \
    $$PWD/src/misc/lv_color.h \
    $$PWD/src/misc/lv_fs.h \
    $$PWD/src/misc/lv_gc.h \
    $$PWD/src/misc/lv_ll.h \
    $$PWD/src/misc/lv_log.h \
    $$PWD/src/misc/lv_lru.h \
    $$PWD/src/misc/lv_math.h \
    $$PWD/src/misc/lv_mem.h \
    $$PWD/src/misc/lv_printf.h \
    $$PWD/src/misc/lv_style.h \
    $$PWD/src/misc/lv_style_gen.h \
    $$PWD/src/misc/lv_templ.h \
    $$PWD/src/misc/lv_timer.h \
    $$PWD/src/misc/lv_tlsf.h \
    $$PWD/src/misc/lv_txt.h \
    $$PWD/src/misc/lv_txt_ap.h \
    $$PWD/src/misc/lv_types.h \
    $$PWD/src/misc/lv_utils.h \
    $$PWD/src/widgets/lv_arc.h \
    $$PWD/src/widgets/lv_bar.h \
    $$PWD/src/widgets/lv_btn.h \
    $$PWD/src/widgets/lv_btnmatrix.h \
    $$PWD/src/widgets/lv_canvas.h \
    $$PWD/src/widgets/lv_checkbox.h \
    $$PWD/src/widgets/lv_dropdown.h \
    $$PWD/src/widgets/lv_img.h \
    $$PWD/src/widgets/lv_label.h \
    $$PWD/src/widgets/lv_line.h \
    $$PWD/src/widgets/lv_objx_templ.h \
    $$PWD/src/widgets/lv_roller.h \
    $$PWD/src/widgets/lv_slider.h \
    $$PWD/src/widgets/lv_switch.h \
    $$PWD/src/widgets/lv_table.h \
    $$PWD/src/widgets/lv_textarea.h \

DISTFILES +=
