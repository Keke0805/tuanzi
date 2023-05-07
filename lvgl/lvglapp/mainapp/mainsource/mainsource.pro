QT += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

#lvgl driver
DEFINES += LVGL_DRIVER

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
    main.cpp \
    mainstart/mainappstart.cpp \
    machine/LvglMachine.cpp \
    machine/UartContext.cpp \
    mainstart/subwindow/alarm.cpp \
    mainstart/subwindow/bluetooth.cpp \
    mainstart/subwindow/brightness.cpp \
    mainstart/subwindow/clock.cpp \
    mainstart/subwindow/dynamic.cpp \
    mainstart/subwindow/eq_setting.cpp \
    mainstart/subwindow/kbscreen.cpp \
    mainstart/subwindow/language.cpp \
    mainstart/subwindow/light.cpp \
    mainstart/subwindow/lyrics.cpp \
    mainstart/subwindow/microphone.cpp \
    mainstart/subwindow/net_radio.cpp \
    mainstart/subwindow/sounds.cpp \
    mainstart/subwindow/statical.cpp \
    mainstart/subwindow/timer.cpp \
    mainstart/subwindow/user.cpp \
    mainstart/subwindow/version.cpp \
    mainstart/subwindow/volume.cpp \
    mainstart/subwindow/wifi.cpp \
    simulator/LvglSimulator.cpp \
    simulator/serialtool.cpp

HEADERS += \
    appmsg/appmsg.h \
    common/common.h \
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
    common/middle/va_save/cjson_config.h \
    common/middle/va_save/va_ota_conf.h \
    common/smt_config.h \
    mainstart/customer_config.h \
    mainstart/mainappstart.h \
    machine/LvglMachine.h \
    machine/UartContext.h \
    mainstart/packet.h \
    mainstart/subwindow/alarm.h \
    mainstart/subwindow/bluetooth.h \
    mainstart/subwindow/brightness.h \
    mainstart/subwindow/clock.h \
    mainstart/subwindow/dynamic.h \
    mainstart/subwindow/eq_setting.h \
    mainstart/subwindow/kbscreen.h \
    mainstart/subwindow/language.h \
    mainstart/subwindow/light.h \
    mainstart/subwindow/lyrics.h \
    mainstart/subwindow/microphone.h \
    mainstart/subwindow/net_radio.h \
    mainstart/subwindow/sounds.h \
    mainstart/subwindow/statical.h \
    mainstart/subwindow/timer.h \
    mainstart/subwindow/user.h \
    mainstart/subwindow/version.h \
    mainstart/subwindow/volume.h \
    mainstart/subwindow/wifi.h \
    simulator/LvglSimulator.h \
    simulator/serialtool.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

resfile.files = $$PWD/resource/*
resfile.path = $$OUT_PWD/resource
INSTALLS += resfile

win32: LIBS += -L$$PWD/../../lib-depend/lvgllib/lib/mingw_64/ -lLvGui
INCLUDEPATH += $$PWD/../../lib-depend/lvgllib/include
DEPENDPATH += $$PWD/../../lib-depend/lvgllib/include
INCLUDEPATH += $$PWD/../../lib-depend/lvgllib/include/lv_code
DEPENDPATH += $$PWD/../../lib-depend/lvgllib/include/lv_code
INCLUDEPATH += $$PWD/../../lib-depend/lvgllib/include/lv_cpp
DEPENDPATH += $$PWD/../../lib-depend/lvgllib/include/lv_cpp
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/lvgllib/lib/mingw_64/LvGui.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/lvgllib/lib/mingw_64/libLvGui.a

win32: LIBS += -L$$PWD/../../lib-depend/freetype/lib/mingw_64/ -lfreetype
INCLUDEPATH += $$PWD/../../lib-depend/freetype/include/freetype2
DEPENDPATH += $$PWD/../../lib-depend/freetype/include/freetype2
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/freetype/lib/mingw_64/libfreetype.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/freetype/lib/mingw_64/libfreetype.a

win32: LIBS += -L$$PWD/../../lib-depend/libhv/lib/mingw_64/ -lhv_static
INCLUDEPATH += $$PWD/../../lib-depend/libhv/include
DEPENDPATH += $$PWD/../../lib-depend/libhv/include
INCLUDEPATH += $$PWD/../../lib-depend/libhv/include/hv
DEPENDPATH += $$PWD/../../lib-depend/libhv/include/hv
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/libhv/lib/mingw_64/libhv.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../lib-depend/libhv/lib/mingw_64/libhv_static.a

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
