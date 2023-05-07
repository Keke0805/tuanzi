#include "LvglMachine.h"

#if (QTSIM_PLATFORM==0)

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
    SSTAR_Applib_Init(APP_GLOBAL_CFG);
    SSTAR_DLService_Init();
    SSTAR_ZPClient_Init();
    SSTAR_InitHotplugDetect();
    system("echo 0 > /sys/class/pwm/pwmchip0/export");
    system("echo 2000 > /sys/class/pwm/pwmchip0/pwm0/period");
    system("echo 80 > /sys/class/pwm/pwmchip0/pwm0/duty_cycle");
    system("echo normal > /sys/class/pwm/pwmchip0/pwm0/polarity");
    system("echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable");

    system("echo 1 > /sys/class/pwm/pwmchip0/export");
    system("echo 2000 > /sys/class/pwm/pwmchip0/pwm1/period");
    system("echo 80 > /sys/class/pwm/pwmchip0/pwm1/duty_cycle");
    system("echo normal > /sys/class/pwm/pwmchip0/pwm1/polarity");
    system("echo 1 > /sys/class/pwm/pwmchip0/pwm1/enable");
#endif
	
#ifdef _UCHIP_T113

#endif
}

void LvglMachine::driver_deinit(void)
{
#ifdef _UCHIP_SSD202
    SSTAR_DeinitHotPlugDetect();
    SSTAR_ZPClient_Deinit();
    SSTAR_DLService_Deinit();
    SSTAR_Applib_Deinit();
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
