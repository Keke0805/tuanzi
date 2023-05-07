#ifndef LVCPP_DISPLAYENGINE_H
#define LVCPP_DISPLAYENGINE_H

#include  "lvgl/lvgl.h"
#include  "../include/lvcpp_sysconfig.h"


#ifdef LVGL_DRIVER
#if (CURRENT_SIMOS == SIMULATOR_QTRUN_PLAT)
#include  <vector>
#include  <QDebug>
#include  <QPixmap>
#include  <QImage>
#endif

#include  "lv_cpp/core/lvcpp_mainscreen.h"

struct m_buffer_fbdisp_t
{
    lv_size_t size;
    lv_coord_t rgb_byte;
    uint32_t length;
    lv_coord_t rotate;
    char* buf;
};

class LvcppStartupSYS
{

public:
    LvcppStartupSYS(void);
    LvcppStartupSYS(lv_coord_t width, lv_coord_t height);
    ~LvcppStartupSYS(void);

    void display_init(lv_disp_rot_t rotate);
    void sysfont_init(const char* path, int size, int type);
    void tick_event(void);
    int  get_width(void);
    int  get_height(void);
    void refresh_disp(void);

    m_buffer_fbdisp_t framer_buff(void) { return  m_framer;}

#if (CURRENT_SIMOS == SIMULATOR_QTRUN_PLAT)
    void updateMouseStatus(lv_coord_t x, lv_coord_t y, lv_indev_state_t state);
#endif

    LvcppMainScreen* mainScreen(void);

protected:
    void sysfont_set_size(int size, int type);

private:

    lv_disp_drv_t m_dispDrv;
    lv_indev_drv_t m_touch_drv;
	
	lv_indev_drv_t key_drv;
	lv_indev_t *key_dev;
	lv_group_t *key_group;
	
    lv_disp_t*  topdrv_screen;
    LvcppMainScreen*   main_screen;
    m_buffer_fbdisp_t  m_framer;
    lv_disp_draw_buf_t m_dispBuf;

    void sys_initial(void);

#if (CURRENT_SIMOS == SIMULATOR_QTRUN_PLAT)
    int qtsim_driver_init(lv_disp_rot_t rotate);
    lv_indev_data_t m_inputdata;
    bool inputHandler(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
    static void inputCb(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
    static void logCb(const char *buf);
#elif(USE_FBDEV)
    void embeded_unix_init(lv_disp_rot_t rotate);
#endif
};

#else
#if (CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
#include  <vector>
#include  <QDebug>
#include  <QPixmap>
#include  <QImage>
#endif

#define DISP_BUF_SIZE (LV_VER_RES_MAX * LV_HOR_RES_MAX)

class LvcppStartupSYS
{
public:
    LvcppStartupSYS(void);
    LvcppStartupSYS(lv_coord_t width, lv_coord_t height);
    ~LvcppStartupSYS(void);

    void display_init(void);
    void sysfont_init(const char* path, int size, int type);
    void sysfont_set_size(int size, int type);
    void tick_event(void);
    int  get_width(void);
    int  get_height(void);
    void refresh_now(void);
    void creat_btn(int num);

#if (CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
   bool set_scrSize(int width, int height);
   lv_obj_t* get_dispdrv_scr(void);
   lv_font_t* get_main_font(void);
   int simulator_start(void);
   QPixmap getpic_screen(void);
#endif

private:
   void sys_initial(void);
   lv_coord_t  screen_width, screen_height;

#if(CURRENT_SIMOS == _OS_UNIX_SYSTEM)
    int unix_fbinit(void);
#elif (CURRENT_SIMOS == _OS_SSD202D_UNIX_SYS)
    int ssd202_fbinit(void);
#elif (CURRENT_SIMOS == _OS_SDLSIM_SYSTEM)
    int sdl_display_config(void);
#elif (CURRENT_SIMOS == _OS_WIN32MSVC_SYSTEM)
    int msvc_display_config(void);
#elif (CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
   std::vector<lv_color_t> m_dispFrameBuf;
   std::vector<lv_color_t> m_buf1;
   std::vector<lv_color_t> m_buf2;
   lv_disp_draw_buf_t m_dispBuf;
   lv_disp_drv_t m_dispDrv;
   lv_disp_t*  topdrv_screen;
   lv_obj_t*   root_screen;

   lv_font_t*  main_font;

   lv_indev_data_t m_inputData;

   void flushHandler(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
   static void flushCb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
   bool inputHandler(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
   static void inputCb(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
   static void logCb(const char *dsc);

   void initfont(void);
#endif

};

#endif  //QTSIM_PLATFORM

#endif // LVCPP_DISPLAYENGINE_H
