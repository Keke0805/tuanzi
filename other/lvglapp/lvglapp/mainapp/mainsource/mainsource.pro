QT += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

#lvgl driver
DEFINES += LVGL_DRIVER

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    machine/httpserver.cpp \
    main.cpp \
    mainstart/boxtipscreen.cpp \
    mainstart/idcardscreen.cpp \
    mainstart/kbscreen.cpp \
    mainstart/mainappstart.cpp \
    machine/LvglMachine.cpp \
    machine/UartContext.cpp \
    mainstart/medialist.cpp \
    mainstart/meetingscreen.cpp \
    mainstart/messagescreen.cpp \
    mainstart/renamescreen.cpp \
    mainstart/service.cpp \
    mainstart/setbrighscreen.cpp \
    mainstart/setlanguagescreen.cpp \
    mainstart/setnetwork.cpp \
    mainstart/setnumberscreen.cpp \
    mainstart/settingscreen.cpp \
    mainstart/setversion.cpp \
    mainstart/sginscreen.cpp \
    mainstart/single_screen.cpp \
    mainstart/singlelist.cpp \
    mainstart/speech.cpp \
    mainstart/votescreen.cpp \
    mainstart/wifiscreen.cpp \
    simulator/LvglSimulator.cpp \
    simulator/Qhttpserver.cpp \
    simulator/serialtool.cpp \
    stbimage/dblist/dbList.c \
    stbimage/va_image.c

HEADERS += \
    machine/httpserver.h \
    mainstart/boxtipscreen.h \
    mainstart/customer_config.h \
    mainstart/idcardscreen.h \
    mainstart/kbscreen.h \
    mainstart/mainappstart.h \
    machine/LvglMachine.h \
    machine/UartContext.h \
    mainstart/medialist.h \
    mainstart/meetingscreen.h \
    mainstart/messagescreen.h \
    mainstart/renamescreen.h \
    mainstart/service.h \
    mainstart/setbrighscreen.h \
    mainstart/setlanguagescreen.h \
    mainstart/setnetwork.h \
    mainstart/setnumberscreen.h \
    mainstart/settingscreen.h \
    mainstart/setversion.h \
    mainstart/sginscreen.h \
    mainstart/single_screen.h \
    mainstart/singlelist.h \
    mainstart/speech.h \
    mainstart/votescreen.h \
    mainstart/wifiscreen.h \
    simulator/LvglSimulator.h \
    simulator/Qhttpserver.h \
    simulator/serialtool.h \
    stbimage/dblist/dbList.h \
    stbimage/list.h \
    stbimage/stb_image.h \
    stbimage/stb_image_resize.h \
    stbimage/va_image.h

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
