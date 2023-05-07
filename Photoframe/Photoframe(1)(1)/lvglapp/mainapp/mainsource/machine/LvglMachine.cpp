#include "LvglMachine.h"

LvglMachine::LvglMachine(void)
{

}

LvglMachine::~LvglMachine()
{
    if(lvglAPP != nullptr)
    {
        delete lvglAPP;
        lvglAPP = nullptr;
    }
    if(lvglSYS != nullptr)
    {
        delete lvglSYS;
        lvglSYS = nullptr;
    }
}

void LvglMachine::sysInitial(lv_disp_rot_t rotate)
{
    lvglSYS = new LvcppStartupSYS(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    lvglSYS->sysfont_init(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE, DEFAULT_FONT_TYPE);

    lvglSYS->display_init(rotate);
}

void LvglMachine::start_app(void)
{
    if(mainscreen == nullptr)
    {
       mainscreen = lvglSYS->mainScreen();
       lvglAPP = new MainAPPStart(mainscreen);
       lvgl_refresh();
    }
}

void LvglMachine::lvgl_refresh(void)
{
   lvglSYS->tick_event();
}
