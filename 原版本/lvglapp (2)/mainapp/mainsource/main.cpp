/**
 * @file main app
 *
 */
#include  "lvgl/lvgl.h"
#include  "lv_drivers/lv_drv_conf.h"

#if QTSIM_PLATFORM
#include  <QApplication>
#include  "simulator/LvglSimulator.h"
#else
#include "machine/LvglMachine.h"
#endif

int main(int argc, char *argv[])
{
#if QTSIM_PLATFORM
    QApplication deskapp(argc, argv);
    printf("QT application start\n");

    LvglSimulator simulator;
    simulator.start_serialtool();
    simulator.show();

    return deskapp.exec();
#else
    printf("LVGL application start\n");
    lv_disp_rot_t rotated=LV_DISP_ROT_NONE;
    if(argc >= 2)
    {
		rotated = (lv_disp_rot_t)(atoi(argv[1]));
    }
    LvglMachine machine;
    machine.sysInitial(rotated);
    machine.driver_init();
    machine.start_app();
    return 0;
#endif

}










