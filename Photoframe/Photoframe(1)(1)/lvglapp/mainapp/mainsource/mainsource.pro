QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += LVGL_DRIVER _WIN32_QT_LIB PAHO_MQTT_STATIC

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    appmsg/appmsg.c \
    common/driver/va_audio.c \
    common/driver/va_display.c \
    common/driver/va_gsensor.c \
    common/driver/va_power.c \
    common/driver/va_system.c \
    common/driver/va_wifi.c \
    common/middle/FileList/FileList.c \
    common/middle/circle_buf/circle_buf.c \
    common/middle/cjson/cJSON.c \
    common/middle/dblist/dbList.c \
    common/middle/diskmanager/DiskManager.c \
    common/middle/message/msg.c \
    common/middle/scan_file/ScanStack.c \
    common/middle/scan_file/rat/rat.c \
    common/middle/scan_file/rat/rat_npl.c \
    common/middle/scan_file/scan.c \
    common/middle/va_lvgl/va_font/va_font.c \
    common/middle/va_lvgl/va_image.c \
    common/middle/va_media/media_load_file.c \
    common/middle/va_media/media_mixture.c \
    common/middle/va_media/media_spectrum.c \
    common/middle/va_media/music_lrc.c \
    common/middle/va_media/va_player/player_int.c \
    common/middle/va_media/va_recorder/recorder_int.c \
    common/middle/va_media/va_vdecoder/Vp_image.c \
    common/middle/va_photo/bmp/libnsbmp.c \
    common/middle/va_photo/bmp_decode.c \
    common/middle/va_photo/image.c \
    common/middle/va_photo/image_display.c \
    common/middle/va_photo/image_process.c \
    common/middle/va_photo/jpg_decode.c \
    common/middle/va_photo/png_decode.c \
    common/middle/va_save/app_config_interface.c \
    common/middle/va_save/cjson_config.c \
    common/middle/va_save/va_ota_conf.c \
    machine/LvglMachine.cpp \
    machine/UartContext.cpp \
    main.cpp \
    mainstart/alarm/alarm.cpp \
    mainstart/calendar/calendar.cpp \
    mainstart/clock/clock.cpp \
    mainstart/mainappstart.cpp \
    mainstart/music/music.cpp \
    mainstart/photo/photolist.cpp \
    mainstart/photo/photolist_icon.cpp \
    mainstart/photo/photomain.cpp \
    mainstart/photo/photoplaying.cpp \
    mainstart/scene_list/alarm_bounced.cpp \
    mainstart/scene_list/alarm_info.cpp \
    mainstart/scene_list/alarm_info_bell.cpp \
    mainstart/scene_list/alarm_info_label.cpp \
    mainstart/scene_list/alarm_info_time.cpp \
    mainstart/scene_list/alarm_list.cpp \
    mainstart/scene_list/clock_list.cpp \
    mainstart/scene_list/clock_secne.cpp \
    mainstart/scene_list/clock_timelist.cpp \
    mainstart/scene_list/frame_list.cpp \
    mainstart/scene_list/frame_list_icon.cpp \
    mainstart/scene_list/frame_list_icon_center.cpp \
    mainstart/scene_list/frame_scenelist.cpp \
    mainstart/scene_list/menu_list.cpp \
    mainstart/scene_list/shuffle_list.cpp \
    mainstart/scene_list/weather_list.cpp \
    mainstart/scene_list/wlan_info.cpp \
    mainstart/scene_list/wlan_list.cpp \
    mainstart/setting/about_sence.cpp \
    mainstart/setting/album_language.cpp \
    mainstart/setting/album_language_list.cpp \
    mainstart/setting/album_list.cpp \
    mainstart/setting/album_montion.cpp \
    mainstart/setting/album_scene.cpp \
    mainstart/setting/album_slideshow.cpp \
    mainstart/setting/album_slideshow_mode.cpp \
    mainstart/setting/factory_sence.cpp \
    mainstart/setting/frame_change_str.cpp \
    mainstart/setting/frame_info_sence.cpp \ 
    mainstart/setting/frame_sence.cpp \
    mainstart/setting/frame_user_info.cpp \
    mainstart/setting/frame_user_sence.cpp \
    mainstart/setting/help_sence.cpp \
    mainstart/setting/setting.cpp \
    mainstart/setting/setting_mute_list.cpp \
    mainstart/video/videolist.cpp \
    mainstart/video/videomain.cpp \
    mainstart/video/videoplay.cpp \
    mainstart/weather/weather.cpp \
    network/azure_iot.cpp \
    network/checktimemsg.cpp \
    network/http.cpp \
    simulator/LvglSimulator.cpp \
    simulator/serialtool.cpp

HEADERS += \
    appmsg/appmsg.h \
    common/common.h \
    common/driver/disp.h \
    common/driver/drv_display.h \
    common/driver/sunxi_display1.h \
    common/driver/sunxi_display2.h \
    common/driver/va_audio.h \
    common/driver/va_display.h \
    common/driver/va_driver.h \
    common/driver/va_gsensor.h \
    common/driver/va_power.h \
    common/driver/va_system.h \
    common/driver/va_wifi.h \
    common/list.h \
    common/middle/FileList/FileList.h \
    common/middle/circle_buf/circle_buf.h \
    common/middle/cjson/cJSON.h \
    common/middle/dblist/dbList.h \
    common/middle/diskmanager/DiskManager.h \
    common/middle/message/msg.h \
    common/middle/scan_file/Scan.h \
    common/middle/scan_file/ScanPri.h \
    common/middle/scan_file/ScanStack.h \
    common/middle/scan_file/ScanStackPri.h \
    common/middle/scan_file/common.h \
    common/middle/scan_file/rat/rat.h \
    common/middle/scan_file/rat/rat_common.h \
    common/middle/scan_file/rat/rat_npl.h \
    common/middle/stbimage/stb_image.h \
    common/middle/va_lvgl/va_font/lang.h \
    common/middle/va_lvgl/va_font/va_font.h \
    common/middle/va_lvgl/va_image.h \
    common/middle/va_media/media_load_file.h \
    common/middle/va_media/media_mixture.h \
    common/middle/va_media/media_spectrum.h \
    common/middle/va_media/music_lrc.h \
    common/middle/va_media/va_player/player_int.h \
    common/middle/va_media/va_recorder/recorder_int.h \
    common/middle/va_media/va_vdecoder/Vp_image.h \
    common/middle/va_middle.h \
    common/middle/va_photo/bmp/libnsbmp.h \
    common/middle/va_photo/bmp/utils/log.h \
    common/middle/va_photo/bmp_decode.h \
    common/middle/va_photo/g2d_driver_enh.h \
    common/middle/va_photo/image.h \
    common/middle/va_photo/jpg_decode.h \
    common/middle/va_photo/png_decode.h \
    common/middle/va_photo/stb.h \
    common/middle/va_photo/stb_image.h \
    common/middle/va_photo/stb_image_resize.h \
    common/middle/va_photo/stb_image_write.h \
    common/middle/va_save/app_config_interface.h \
    common/middle/va_save/app_config_param.h \
    common/middle/va_save/cjson_config.h \
    common/middle/va_save/va_ota_conf.h \
    common/smt_config.h \
    machine/LvglMachine.h \
    machine/UartContext.h \
    mainstart/alarm/alarm.h \
    mainstart/calendar/calendar.h \
    mainstart/clock/clock.h \
    mainstart/customer_config.h \
    mainstart/include/configCustom.h \
    mainstart/include/str_config.h \
    mainstart/include/ui_config.h \
    mainstart/mainappstart.h \
    mainstart/music/music.h \
    mainstart/photo/photolist.h \
    mainstart/photo/photolist_icon.h \
    mainstart/photo/photomain.h \
    mainstart/photo/photoplaying.h \
    mainstart/scene_list/alarm_bounced.h \
    mainstart/scene_list/alarm_info.h \
    mainstart/scene_list/alarm_info_bell.h \
    mainstart/scene_list/alarm_info_label.h \
    mainstart/scene_list/alarm_info_time.h \
    mainstart/scene_list/alarm_list.h \
    mainstart/scene_list/clock_list.h \
    mainstart/scene_list/clock_secne.h \
    mainstart/scene_list/clock_timelist.h \
    mainstart/scene_list/frame_list.h \
    mainstart/scene_list/frame_list_icon.h \
    mainstart/scene_list/frame_list_icon_center.h \
    mainstart/scene_list/frame_scenelist.h \
    mainstart/scene_list/menu_list.h \
    mainstart/scene_list/shuffle_list.h \
    mainstart/scene_list/weather_list.h \
    mainstart/scene_list/wlan_info.h \
    mainstart/scene_list/wlan_list.h \
    mainstart/setting/about_sence.h \
    mainstart/setting/album_language.h \
    mainstart/setting/album_language_list.h \
    mainstart/setting/album_list.h \
    mainstart/setting/album_montion.h \
    mainstart/setting/album_scene.h \
    mainstart/setting/album_slideshow.h \
    mainstart/setting/album_slideshow_mode.h \
    mainstart/setting/factory_sence.h \
    mainstart/setting/frame_change_str.h \
    mainstart/setting/frame_info_sence.h \
    mainstart/setting/frame_sence.h \
    mainstart/setting/frame_user_info.h \
    mainstart/setting/frame_user_sence.h \
    mainstart/setting/help_sence.h \
    mainstart/setting/setting.h \
    mainstart/setting/setting_mute_list.h \
    mainstart/video/videolist.h \
    mainstart/video/videomain.h \
    mainstart/video/videoplay.h \
    mainstart/weather/weather.h \
    network/azure_iot.h \
    network/checktimemsg.h \
    network/http.h \
    simulator/LvglSimulator.h \
    simulator/serialtool.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

resfont.files = $$PWD/resource/font/*
resfont.path = $$OUT_PWD/resource/font
INSTALLS += resfont

resimage.files = $$PWD/resource/image/*
resimage.path = $$OUT_PWD/resource/image
INSTALLS += resimage

resmovie.files = $$PWD/resource/movie/*
resmovie.path = $$OUT_PWD/resource/movie
INSTALLS += resmovie

reslibdll.files = $$PWD/../../lib-depend/ffmpeg/bin/*.dll
reslibdll.files += $$PWD/../../lib-depend/libhv/bin/*.dll
reslibdll.files += $$PWD/../../lib-depend/openssl/bin/*.dll
reslibdll.path = $$OUT_PWD/
INSTALLS += reslibdll

win32: LIBS += -L$$PWD/../../lib-depend/lvgllib/lib/mingw_64 -lLvGui
INCLUDEPATH += $$PWD/../../lib-depend/lvgllib/include
DEPENDPATH += $$PWD/../../lib-depend/lvgllib/include
INCLUDEPATH += $$PWD/../../lib-depend/lvgllib/include/lv_code
DEPENDPATH += $$PWD/../../lib-depend/lvgllib/include/lv_code
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/lvgllib/lib/mingw_64/LvGui.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/lvgllib/lib/mingw_64/libLvGui.a

win32: LIBS += -L$$PWD/../../lib-depend/freetype/lib/mingw_64 -lfreetype
INCLUDEPATH += $$PWD/../../lib-depend/freetype/include/freetype2
DEPENDPATH += $$PWD/../../lib-depend/freetype/include/freetype2
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/freetype/lib/mingw_64/libfreetype.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/freetype/lib/mingw_64/libfreetype.a

win32: LIBS += -L$$PWD/../../lib-depend/libhv/lib/mingw_64 -lhv_static
INCLUDEPATH += $$PWD/../../lib-depend/libhv/include
DEPENDPATH += $$PWD/../../lib-depend/libhv/include
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/libhv/lib/mingw_64/hv_static.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/libhv/lib/mingw_64/libhv_static.a

win32: LIBS += -L$$PWD/../../lib-depend/ffmpeg/lib/ -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale
INCLUDEPATH += $$PWD/../../lib-depend/ffmpeg/include
DEPENDPATH += $$PWD/../../lib-depend/ffmpeg/include

win32: LIBS += -L$$PWD/../../lib-depend/openssl/lib/ -lssl -lcrypto
INCLUDEPATH += $$PWD/../../lib-depend/openssl/include
DEPENDPATH += $$PWD/../../lib-depend/openssl/include

LIBS += -lpthread libwsock32 libws2_32

INCLUDEPATH += $$PWD/common \
    $$PWD/common/driver \
    $$PWD/common/middle \
    $$PWD/common/middle/circle_buf \
    $$PWD/common/middle/cjson \
    $$PWD/common/middle/dblist \
    $$PWD/common/middle/diskmanager \
    $$PWD/common/middle/Filelist \
    $$PWD/common/middle/message \
    $$PWD/common/middle/scan_file \
    $$PWD/common/middle/scan_file/rat \
    $$PWD/common/middle/va_lvgl/va_font \
    $$PWD/common/middle/va_lvgl \
    $$PWD/common/middle/va_media \
    $$PWD/common/middle/va_media/va_player \
    $$PWD/common/middle/va_media/va_recorder \
    $$PWD/common/middle/va_photo \
    $$PWD/common/middle/va_photo/bmp \
    $$PWD/common/middle/va_save

INCLUDEPATH += $$PWD/../../lib-depend/azure-iot-sdk-c/include
DEPENDPATH += $$PWD/../../lib-depend/azure-iot-sdk-c/include
