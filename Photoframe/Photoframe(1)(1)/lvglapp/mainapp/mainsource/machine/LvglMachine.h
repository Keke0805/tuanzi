#ifndef LVGLMACHINE_H
#define LVGLMACHINE_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_startup.h"
#include  "mainstart/mainappstart.h"


class LvglMachine
{
 public:
    LvglMachine(void);
    ~LvglMachine(void);

    void sysInitial(lv_disp_rot_t rotate);
    void start_app(void);

 private:

    LvcppStartupSYS* lvglSYS=nullptr;
    LvcppMainScreen* mainscreen = nullptr;

    MainAPPStart* lvglAPP = nullptr;
    void lvgl_refresh(void);
};


#endif  // LVGLMACHINE_H


