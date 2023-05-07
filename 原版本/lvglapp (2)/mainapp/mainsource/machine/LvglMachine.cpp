#include "LvglMachine.h"

#if (QTSIM_PLATFORM==0)
#include "common/common.h"

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
    driver_deinit();
}

void LvglMachine::sysInitial(lv_disp_rot_t rotate)
{
    lvglSYS = new LvcppStartupSYS(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    lvglSYS->sysfont_init(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE, DEFAULT_FONT_TYPE);
    lvglSYS->display_init(rotate);
}

void LvglMachine::driver_init(void)
{
#ifdef _UCHIP_SSD202

#endif
	
#ifdef _UCHIP_T113
    rat_init();
    va_audio_init();
    va_audio_play_init();
    message_sys_init();
    media_init();
#endif
}

void LvglMachine::driver_deinit(void)
{
#ifdef _UCHIP_SSD202

#endif

#ifdef _UCHIP_T113

#endif
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

#endif
