CPPSRCS += mainappstart.cpp
CPPSRCS += idcardscreen.cpp
CPPSRCS += renamescreen.cpp
CPPSRCS += settingscreen.cpp
CPPSRCS += kbscreen.cpp
CPPSRCS += medialist.cpp
CPPSRCS += setbrighscreen.cpp
CPPSRCS += setlanguagescreen.cpp
CPPSRCS += setnetwork.cpp
CPPSRCS += setnumberscreen.cpp
CPPSRCS += setversion.cpp

include $(LVGL_DIR)/mainstart/zpclient/zpclient.mk
include $(LVGL_DIR)/mainstart/hotplugdetect/hotplugdetect.mk

DEPPATH += --dep-path $(LVGL_DIR)/mainstart
VPATH += :$(LVGL_DIR)/mainstart
CPP_FLAGS += "-I$(LVGL_DIR)/mainstart"


