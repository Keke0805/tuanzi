#CONFIG -= qt
QT  += core

TEMPLATE = lib
CONFIG += staticlib

CONFIG += console c++11

DEFINES += LVGL_DRIVER


include(lv_code/lvgl/lvgl.pri)
include(lv_code/lv_drivers/lvgldrv.pri)
include(lv_cpp/lvcppclass.pri)

INCLUDEPATH += lv_code lv_cpp
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
libpath = $$PWD/../
target.path = $$libpath/lib/mingw_64
!isEmpty(target.path): INSTALLS += target

####cpp include
cpppath = $$libpath/include/lv_cpp
cpproot.files = $$PWD/lv_cpp/*.h
cpproot.path = $$cpppath
INSTALLS += cpproot

cppbase.files = $$PWD/lv_cpp/base/*.h
cppbase.path = $$cpppath/base
INSTALLS += cppbase

cppbutton.files = $$PWD/lv_cpp/button/*.h
cppbutton.path = $$cpppath/button
INSTALLS += cppbutton

cppcore.files = $$PWD/lv_cpp/core/*.h
cppcore.path = $$cpppath/core
INSTALLS += cppcore

cppcontainer.files = $$PWD/lv_cpp/container/*.h
cppcontainer.path = $$cpppath/container
INSTALLS += cppcontainer

cppdisplayWidget.files = $$PWD/lv_cpp/displayWidget/*.h
cppdisplayWidget.path = $$cpppath/displayWidget
INSTALLS += cppdisplayWidget

cppfont.files = $$PWD/lv_cpp/font/*.h
cppfont.path = $$cpppath/font
INSTALLS += cppfont

cppinclude.files = $$PWD/lv_cpp/include/*.h
cppinclude.path = $$cpppath/include
INSTALLS += cppinclude

cppinputWidget.files = $$PWD/lv_cpp/inputWidget/*.h
cppinputWidget.path = $$cpppath/inputWidget
INSTALLS += cppinputWidget

cppstyle.files = $$PWD/lv_cpp/style/*.h
cppstyle.path = $$cpppath/style
INSTALLS += cppstyle

cppimage.files = $$PWD/lv_cpp/image/*.h
cppimage.path = $$cpppath/image
INSTALLS += cppimage

####lvgl include
lvglpath = $$libpath/include/lv_code

lvglbase.files = $$PWD/lv_code/lvgl/*.h
lvglbase.path = $$lvglpath/lvgl
INSTALLS += lvglbase

lvglsrc.files += $$PWD/lv_code/lvgl/src/*.h
lvglsrc.path = $$lvglpath/lvgl/src
INSTALLS += lvglsrc

lvglcore.files = $$PWD/lv_code/lvgl/src/core/*.h
lvglcore.path = $$lvglpath/lvgl/src/core
INSTALLS += lvglcore

lvgldraw.files = $$PWD/lv_code/lvgl/src/draw/*.h
lvgldraw.path = $$lvglpath/lvgl/src/draw
INSTALLS += lvgldraw

lvgldrawsw.files += $$PWD/lv_code/lvgl/src/draw/sw/*.h
lvgldrawsw.path = $$lvglpath/lvgl/src/draw/sw
INSTALLS += lvgldrawsw

lvgldrawsdl.files += $$PWD/lv_code/lvgl/src/draw/sdl/*.h
lvgldrawsdl.path = $$lvglpath/lvgl/src/draw/sdl
INSTALLS += lvgldrawsdl

lvgldrawstm32dma2d.files += $$PWD/lv_code/lvgl/src/draw/stm32_dma2d/*.h
lvgldrawstm32dma2d.path = $$lvglpath/lvgl/src/draw/stm32_dma2d
INSTALLS += lvgldrawstm32dma2d

lvgldrawt113g2d.files += $$PWD/lv_code/lvgl/src/draw/t113_g2d/*.h
lvgldrawt113g2d.path = $$lvglpath/lvgl/src/draw/t113_g2d
INSTALLS += lvgldrawt113g2d

lvglfont.files = $$PWD/lv_code/lvgl/src/font/*.h
lvglfont.path = $$lvglpath/lvgl/src/font
INSTALLS += lvglfont

lvglhal.files = $$PWD/lv_code/lvgl/src/hal/*.h
lvglhal.path = $$lvglpath/lvgl/src/hal
INSTALLS += lvglhal

lvglmisc.files = $$PWD/lv_code/lvgl/src/misc/*.h
lvglmisc.path = $$lvglpath/lvgl/src/misc
INSTALLS += lvglmisc

lvglwidgets.files = $$PWD/lv_code/lvgl/src/widgets/*.h
lvglwidgets.path = $$lvglpath/lvgl/src/widgets
INSTALLS += lvglwidgets

lvglextra.files = $$PWD/lv_code/lvgl/src/extra/*.h
lvglextra.path = $$lvglpath/lvgl/src/extra
INSTALLS += lvglextra

lvglextlayouts.files = $$PWD/lv_code/lvgl/src/extra/layouts/*.h
lvglextlayouts.path = $$lvglpath/lvgl/src/extra/layouts
INSTALLS += lvglextlayouts

lvglextlyflex.files = $$PWD/lv_code/lvgl/src/extra/layouts/flex/*.h
lvglextlyflex.path = $$lvglpath/lvgl/src/extra/layouts/flex
INSTALLS += lvglextlyflex

lvglextlygrid.files = $$PWD/lv_code/lvgl/src/extra/layouts/grid/*.h
lvglextlygrid.path = $$lvglpath/lvgl/src/extra/layouts/grid
INSTALLS += lvglextlygrid

lvglextthemes.files = $$PWD/lv_code/lvgl/src/extra/themes/*.h
lvglextthemes.path = $$lvglpath/lvgl/src/extra/themes
INSTALLS += lvglextthemes

lvglextthbasic.files = $$PWD/lv_code/lvgl/src/extra/themes/basic/*.h
lvglextthbasic.path = $$lvglpath/lvgl/src/extra/themes/basic
INSTALLS += lvglextthbasic

lvglextthdef.files = $$PWD/lv_code/lvgl/src/extra/themes/default/*.h
lvglextthdef.path = $$lvglpath/lvgl/src/extra/themes/default
INSTALLS += lvglextthdef

lvglextthmono.files = $$PWD/lv_code/lvgl/src/extra/themes/mono/*.h
lvglextthmono.path = $$lvglpath/lvgl/src/extra/themes/mono
INSTALLS += lvglextthmono

lvglextwidgets.files = $$PWD/lv_code/lvgl/src/extra/widgets/*.h
lvglextwidgets.path = $$lvglpath/lvgl/src/extra/widgets
INSTALLS += lvglextwidgets

lvglextanimimg.files = $$PWD/lv_code/lvgl/src/extra/widgets/animimg/*.h
lvglextanimimg.path = $$lvglpath/lvgl/src/extra/widgets/animimg
INSTALLS += lvglextanimimg

lvglextcalendar.files = $$PWD/lv_code/lvgl/src/extra/widgets/calendar/*.h
lvglextcalendar.path = $$lvglpath/lvgl/src/extra/widgets/calendar
INSTALLS += lvglextcalendar

lvglextchart.files = $$PWD/lv_code/lvgl/src/extra/widgets/chart/*.h
lvglextchart.path = $$lvglpath/lvgl/src/extra/widgets/chart
INSTALLS += lvglextchart

lvglextkeyboard.files = $$PWD/lv_code/lvgl/src/extra/widgets/keyboard/*.h
lvglextkeyboard.path = $$lvglpath/lvgl/src/extra/widgets/keyboard
INSTALLS += lvglextkeyboard

lvglextlist.files = $$PWD/lv_code/lvgl/src/extra/widgets/list/*.h
lvglextlist.path = $$lvglpath/lvgl/src/extra/widgets/list
INSTALLS += lvglextlist

lvglextmenu.files = $$PWD/lv_code/lvgl/src/extra/widgets/menu/*.h
lvglextmenu.path = $$lvglpath/lvgl/src/extra/widgets/menu
INSTALLS += lvglextmenu

lvglextmsgbox.files = $$PWD/lv_code/lvgl/src/extra/widgets/msgbox/*.h
lvglextmsgbox.path = $$lvglpath/lvgl/src/extra/widgets/msgbox
INSTALLS += lvglextmsgbox

lvglextmeter.files = $$PWD/lv_code/lvgl/src/extra/widgets/meter/*.h
lvglextmeter.path = $$lvglpath/lvgl/src/extra/widgets/meter
INSTALLS += lvglextmeter

lvglextspinbox.files = $$PWD/lv_code/lvgl/src/extra/widgets/spinbox/*.h
lvglextspinbox.path = $$lvglpath/lvgl/src/extra/widgets/spinbox
INSTALLS += lvglextspinbox

lvglextspinner.files = $$PWD/lv_code/lvgl/src/extra/widgets/spinner/*.h
lvglextspinner.path = $$lvglpath/lvgl/src/extra/widgets/spinner
INSTALLS += lvglextspinner

lvglexttabview.files = $$PWD/lv_code/lvgl/src/extra/widgets/tabview/*.h
lvglexttabview.path = $$lvglpath/lvgl/src/extra/widgets/tabview
INSTALLS += lvglexttabview

lvglexttileview.files = $$PWD/lv_code/lvgl/src/extra/widgets/tileview/*.h
lvglexttileview.path = $$lvglpath/lvgl/src/extra/widgets/tileview
INSTALLS += lvglexttileview

lvglextwin.files = $$PWD/lv_code/lvgl/src/extra/widgets/win/*.h
lvglextwin.path = $$lvglpath/lvgl/src/extra/widgets/win
INSTALLS += lvglextwin

lvglextcolorwheel.files = $$PWD/lv_code/lvgl/src/extra/widgets/colorwheel/*.h
lvglextcolorwheel.path = $$lvglpath/lvgl/src/extra/widgets/colorwheel
INSTALLS += lvglextcolorwheel

lvglextled.files = $$PWD/lv_code/lvgl/src/extra/widgets/led/*.h
lvglextled.path = $$lvglpath/lvgl/src/extra/widgets/led
INSTALLS += lvglextled

lvglextimgbtn.files = $$PWD/lv_code/lvgl/src/extra/widgets/imgbtn/*.h
lvglextimgbtn.path = $$lvglpath/lvgl/src/extra/widgets/imgbtn
INSTALLS += lvglextimgbtn

lvglextspan.files = $$PWD/lv_code/lvgl/src/extra/widgets/span/*.h
lvglextspan.path = $$lvglpath/lvgl/src/extra/widgets/span
INSTALLS += lvglextspan

lvglextothers.files = $$PWD/lv_code/lvgl/src/extra/others/*.h
lvglextothers.path = $$lvglpath/lvgl/src/extra/others
INSTALLS += lvglextothers

lvglextotgridnav.files = $$PWD/lv_code/lvgl/src/extra/others/gridnav/*.h
lvglextotgridnav.path = $$lvglpath/lvgl/src/extra/others/gridnav
INSTALLS += lvglextotgridnav

lvglextotmonkey.files = $$PWD/lv_code/lvgl/src/extra/others/monkey/*.h
lvglextotmonkey.path = $$lvglpath/lvgl/src/extra/others/monkey
INSTALLS += lvglextotmonkey

lvglextotsnapshot.files = $$PWD/lv_code/lvgl/src/extra/others/snapshot/*.h
lvglextotsnapshot.path = $$lvglpath/lvgl/src/extra/others/snapshot
INSTALLS += lvglextotsnapshot

lvglextotfileexplorer.files = $$PWD/lv_code/lvgl/src/extra/others/file_explorer/*.h
lvglextotfileexplorer.path = $$lvglpath/lvgl/src/extra/others/file_explorer
INSTALLS += lvglextotfileexplorer

lvglextlibs.files = $$PWD/lv_code/lvgl/src/extra/libs/*.h
lvglextlibs.path = $$lvglpath/lvgl/src/extra/libs
INSTALLS += lvglextlibs

lvgllibsbmp.files = $$PWD/lv_code/lvgl/src/extra/libs/bmp/*.h
lvgllibsbmp.path = $$lvglpath/lvgl/src/extra/libs/bmp
INSTALLS += lvgllibsbmp

lvgllibsfsdrv.files = $$PWD/lv_code/lvgl/src/extra/libs/fsdrv/*.h
lvgllibsfsdrv.path = $$lvglpath/lvgl/src/extra/libs/fsdrv
INSTALLS += lvgllibsfsdrv

lvgllibspng.files = $$PWD/lv_code/lvgl/src/extra/libs/png/*.h
lvgllibspng.path = $$lvglpath/lvgl/src/extra/libs/png
INSTALLS += lvgllibspng

lvgllibsgif.files = $$PWD/lv_code/lvgl/src/extra/libs/gif/*.h
lvgllibsgif.path = $$lvglpath/lvgl/src/extra/libs/gif
INSTALLS += lvgllibsgif

lvgllibsqrcode.files = $$PWD/lv_code/lvgl/src/extra/libs/qrcode/*.h
lvgllibsqrcode.path = $$lvglpath/lvgl/src/extra/libs/qrcode
INSTALLS += lvgllibsqrcode

lvgllibssjpg.files = $$PWD/lv_code/lvgl/src/extra/libs/sjpg/*.h
lvgllibssjpg.path = $$lvglpath/lvgl/src/extra/libs/sjpg
INSTALLS += lvgllibssjpg

lvgllibsfreetype.files = $$PWD/lv_code/lvgl/src/extra/libs/freetype/*.h
lvgllibsfreetype.path = $$lvglpath/lvgl/src/extra/libs/freetype
INSTALLS += lvgllibsfreetype

lvgllibsrlottie.files = $$PWD/lv_code/lvgl/src/extra/libs/rlottie/*.h
lvgllibsrlottie.path = $$lvglpath/lvgl/src/extra/libs/rlottie
INSTALLS += lvgllibsrlottie

lvgllibsffmpeg.files = $$PWD/lv_code/lvgl/src/extra/libs/ffmpeg/*.h
lvgllibsffmpeg.path = $$lvglpath/lvgl/src/extra/libs/ffmpeg
INSTALLS += lvgllibsffmpeg

lvgllibscjson.files = $$PWD/lv_code/lvgl/src/custom/cjson/*.h
lvgllibscjson.path = $$lvglpath/lvgl/src/custom/cjson
INSTALLS += lvgllibscjson

lvgllibslinux.files = $$PWD/lv_code/lvgl/src/custom/linux/*.h
lvgllibslinux.path = $$lvglpath/lvgl/src/custom/linux
INSTALLS += lvgllibslinux

lvgllibscn_ime.files = $$PWD/lv_code/lvgl/src/custom/chinese_ime/*.h
lvgllibscn_ime.path = $$lvglpath/lvgl/src/custom/chinese_ime
INSTALLS += lvgllibscn_ime

lvgldrvbase.files = $$PWD/lv_code/lv_drivers/*.h
lvgldrvbase.path = $$lvglpath/lv_drivers
INSTALLS += lvgldrvbase

lvgldrvdisplay.files = $$PWD/lv_code/lv_drivers/display/*.h
lvgldrvdisplay.path = $$lvglpath/lv_drivers/display
INSTALLS += lvgldrvdisplay

lvgldrvgtkdrv.files = $$PWD/lv_code/lv_drivers/gtkdrv/*.h
lvgldrvgtkdrv.path = $$lvglpath/lv_drivers/gtkdrv
INSTALLS += lvgldrvgtkdrv

lvgldrvindev.files = $$PWD/lv_code/lv_drivers/indev/*.h
lvgldrvindev.path = $$lvglpath/lv_drivers/indev
INSTALLS += lvgldrvindev

lvgldrvsdl.files = $$PWD/lv_code/lv_drivers/sdl/*.h
lvgldrvsdl.path = $$lvglpath/lv_drivers/sdl
INSTALLS += lvgldrvsdl

lvgldrvwayland.files = $$PWD/lv_code/lv_drivers/wayland/*.h
lvgldrvwayland.path = $$lvglpath/lv_drivers/wayland
INSTALLS += lvgldrvwayland

lvgldrvwin32drv.files = $$PWD/lv_code/lv_drivers/win32drv/*.h
lvgldrvwin32drv.path = $$lvglpath/lv_drivers/win32drv
INSTALLS += lvgldrvwin32drv
###############lvgl include end

win32: LIBS += -L$$PWD/../../freetype/lib/mingw_64/ -lfreetype
INCLUDEPATH += $$PWD/../../freetype/include/freetype2
DEPENDPATH += $$PWD/../../freetype/include/freetype2
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../freetype/lib/mingw_64/libfreetype.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../freetype/lib/mingw_64/libfreetype.a
