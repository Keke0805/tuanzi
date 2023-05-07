#include  "lvcpp_startup.h"
#include  "stdlib.h"
#include  "stdio.h"
#include  "unistd.h"

#ifdef LVGL_DRIVER
#if(USE_FBDEV == 1)
    #include  "lv_drivers/display/fbdev.h"
    #include  "lv_drivers/indev/evdev.h"
    #include  "lv_drivers/indev/sunxi_key.h"
    #include  "lv_drivers/display/sunxifb.h"
    #include  "lv_drivers/indev/sunxi_ctpdev.h"
#endif

LvcppStartupSYS::LvcppStartupSYS(void)
{
    sys_initial();
    m_framer.size.width = 1024;
    m_framer.size.height = 600;

    topdrv_screen = nullptr;
    main_screen = nullptr;
}

LvcppStartupSYS::LvcppStartupSYS(lv_coord_t width, lv_coord_t height)
{
    sys_initial();
    m_framer.size.width = width;
    m_framer.size.height = height;

    topdrv_screen = nullptr;
    main_screen = nullptr;
}

LvcppStartupSYS::~LvcppStartupSYS(void)
{
    if(topdrv_screen != nullptr)
    {
        delete topdrv_screen;
        topdrv_screen = NULL;
    }

    if(main_screen != nullptr)
    {
        delete main_screen;
        main_screen = NULL;
    }

    if(lv_is_initialized() == true)
    {
        lv_deinit();
    }
}

void LvcppStartupSYS::sys_initial(void)
{
#if(CURRENT_SIMOS == SIMULATOR_QTRUN_PLAT)
    lv_log_register_print_cb(logCb);
#endif
    lv_init();
}

void LvcppStartupSYS::sysfont_init(const char* path, int size, int type)
{
  #if(LV_USE_FREETYPE == 1)
      init_default_ttf(path, size, type);
  #endif

   init_dotarray_font(DEFAULT_DOTFONT_SIZE);
}

void LvcppStartupSYS::sysfont_set_size(int size, int type)
{
  #if(LV_USE_FREETYPE)
     change_font_size(size, type);
  #endif
}

int  LvcppStartupSYS::get_width(void)
{
     return m_framer.size.width;
}
int  LvcppStartupSYS::get_height(void)
{
    return m_framer.size.height;
}
void LvcppStartupSYS::refresh_disp(void)
{
    lv_refr_now(topdrv_screen);
}
LvcppMainScreen* LvcppStartupSYS::mainScreen(void)
{
    return main_screen;
}

void LvcppStartupSYS::tick_event(void)
{
    // Periodically call the lv_task handler. */
    // It could be done in a timer interrupt or an OS task too.*/
#if(QTSIM_PLATFORM == 1)
    lv_tick_inc(5);
    lv_timer_handler();
    usleep(5*1000);
#else
  while(1)
  {
    //lv_tick_inc(5);
    lv_timer_handler();
    usleep(10*1000);
  }
#endif
}

void LvcppStartupSYS::display_init(lv_disp_rot_t rotate)
{
  #if(CURRENT_SIMOS == SIMULATOR_QTRUN_PLAT)
    qtsim_driver_init(rotate);
  #elif(USE_FBDEV == 1)
    embeded_unix_init(rotate);
  #endif
}

#if(CURRENT_SIMOS == SIMULATOR_QTRUN_PLAT)
void LvcppStartupSYS::updateMouseStatus(lv_coord_t x, lv_coord_t y, lv_indev_state_t state)
{
    touch_write_data(x, y, state);
}

void LvcppStartupSYS::logCb(const char *buf)
{
   qDebug().nospace() << "[lvgl debug]" << buf;
}

int LvcppStartupSYS::qtsim_driver_init(lv_disp_rot_t rotate)
{
    framebuf_setting(m_framer.size.width, m_framer.size.height, 32);
    m_framer.buf = get_frambuff(&m_framer.size, &m_framer.rgb_byte,&m_framer.length,&m_framer.rotate);

    static void* m_buf1 = malloc(m_framer.length);
    static void* m_buf2 = malloc(m_framer.length);
    lv_disp_draw_buf_init(&m_dispBuf, m_buf1, m_buf2, m_framer.length);

    lv_disp_drv_init(&m_dispDrv);
    if (rotate == LV_DISP_ROT_NONE || rotate == LV_DISP_ROT_180)
    {
        m_dispDrv.hor_res = m_framer.size.width;
        m_dispDrv.ver_res = m_framer.size.height;
    }
    else
    {
        m_dispDrv.hor_res = m_framer.size.height;
        m_dispDrv.ver_res = m_framer.size.width;
    }
    m_dispDrv.flush_cb = fbdev_flush;
    m_dispDrv.draw_buf = &m_dispBuf;
    m_dispDrv.sw_rotate = 0;
    m_dispDrv.rotated = rotate;
    topdrv_screen = lv_disp_drv_register(&m_dispDrv);
    lv_theme_t * th = lv_theme_default_init(topdrv_screen, lv_palette_main(LV_PALETTE_BLUE),
                      lv_palette_main(LV_PALETTE_RED),LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
    lv_disp_set_theme(topdrv_screen, th);

    main_screen = new LvcppMainScreen(m_framer.size.width, m_framer.size.height, topdrv_screen->act_scr);

    lv_indev_drv_init(&m_touch_drv);
    m_touch_drv.type = LV_INDEV_TYPE_POINTER;
    m_touch_drv.read_cb = evdev_read;
    lv_indev_drv_register(&m_touch_drv);

    return 0;
}

#elif(USE_FBDEV == 1)
void LvcppStartupSYS::embeded_unix_init(lv_disp_rot_t rotate)
{
#ifdef _UCHIP_T113
    #ifndef USE_SUNXIFB_G2D_ROTATE
    if (rotate != LV_DISP_ROT_NONE)
        m_dispDrv.sw_rotate = 1;
    #endif
    sunxifb_init(rotate);
    static uint32_t width, height;
    sunxifb_get_sizes(&width, &height);

    static lv_color_t* buf1;
    buf1 = (lv_color_t*) sunxifb_alloc(width * height * sizeof(lv_color_t),
            "mainapp");

    if (buf1 == NULL) {
        sunxifb_exit();
        printf("malloc draw buffer fail\n");
        return;
    }
    lv_disp_draw_buf_init(&m_dispBuf, buf1, NULL, width * height);

    lv_disp_drv_init(&m_dispDrv);

    if(rotate == LV_DISP_ROT_90 || rotate == LV_DISP_ROT_270)
    {
        m_dispDrv.hor_res = m_framer.size.height;
        m_dispDrv.ver_res = m_framer.size.width;
    }
    else
    {
        m_dispDrv.hor_res = m_framer.size.width;
        m_dispDrv.ver_res = m_framer.size.height;
    }
    m_dispDrv.flush_cb = sunxifb_flush;
    m_dispDrv.draw_buf = &m_dispBuf;
    m_dispDrv.rotated = rotate;//indev_rotate
    m_dispDrv.screen_transp = LV_COLOR_SCREEN_TRANSP;
    topdrv_screen = lv_disp_drv_register(&m_dispDrv);

    lv_theme_t * theme = lv_theme_default_init(topdrv_screen, lv_palette_main(LV_PALETTE_BLUE),
                         lv_palette_main(LV_PALETTE_RED),LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
    lv_disp_set_theme(topdrv_screen, theme);
    lv_obj_set_style_bg_opa(topdrv_screen->act_scr,LV_OPA_TRANSP,LV_PART_MAIN);
    lv_disp_set_bg_opa(NULL, LV_OPA_TRANSP);

    main_screen = new LvcppMainScreen(m_framer.size.width, m_framer.size.height, topdrv_screen->act_scr);
#ifdef __CTP_USE__
	ctpdev_init();
	lv_indev_drv_init(&m_touch_drv);
	m_touch_drv.type = LV_INDEV_TYPE_POINTER;
	m_touch_drv.read_cb = ctpdev_read;
    m_touch_drv.feedback_cb = ctpdev_feedback;
	lv_indev_drv_register(&m_touch_drv);
#endif

#if USE_SUNXI_KEY
    #ifdef USE_SUNXI_TP_KEY
    keydev_init();
    lv_indev_drv_init(&key_drv);
    key_drv.type = LV_INDEV_TYPE_ENCODER;
    key_drv.read_cb = keydev_read;
    key_drv.feedback_cb = keydev_feedback;
    key_dev = lv_indev_drv_register(&key_drv);
    key_group = key_group_create();
    lv_indev_set_group(key_dev, key_group);
    #else
	keydev_init();
	lv_indev_drv_init(&key_drv);
	key_drv.type = LV_INDEV_TYPE_KEYPAD;
	key_drv.read_cb = keydev_read;
    key_drv.feedback_cb = keydev_feedback;
	key_dev = lv_indev_drv_register(&key_drv);
	key_group = key_group_create();
	lv_indev_set_group(key_dev, key_group);
    #endif
#endif

#else
    fbdev_init(rotate);
#ifndef USE_GFX_ROTATE
    if (rotate != LV_DISP_ROT_NONE)
        m_dispDrv.sw_rotate = 1;
#endif
    m_framer.buf = get_frambuff(&m_framer.size, &m_framer.rgb_byte,&m_framer.length,&m_framer.rotate);

    static void* m_buf1 = malloc(m_framer.length);
    lv_disp_draw_buf_init(&m_dispBuf, m_buf1, NULL, m_framer.length);

    lv_disp_drv_init(&m_dispDrv);

    if(rotate == LV_DISP_ROT_90 || rotate == LV_DISP_ROT_270)
    {
        m_dispDrv.hor_res = m_framer.size.height;
        m_dispDrv.ver_res = m_framer.size.width;
    }
    else
    {
        m_dispDrv.hor_res = m_framer.size.width;
        m_dispDrv.ver_res = m_framer.size.height;
    }

    m_dispDrv.flush_cb = fbdev_flush;
    m_dispDrv.draw_buf = &m_dispBuf;
    m_dispDrv.rotated = rotate;
    m_dispDrv.screen_transp = LV_COLOR_SCREEN_TRANSP;
    topdrv_screen = lv_disp_drv_register(&m_dispDrv);

    lv_theme_t * th = lv_theme_default_init(topdrv_screen, lv_palette_main(LV_PALETTE_BLUE),
                      lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
    lv_disp_set_theme(topdrv_screen, th);

    main_screen = new LvcppMainScreen(m_framer.size.width, m_framer.size.height, topdrv_screen->act_scr);

	evdev_init();
    lv_indev_drv_init(&m_touch_drv);
    m_touch_drv.type = LV_INDEV_TYPE_POINTER;
    m_touch_drv.read_cb = evdev_read;
    lv_indev_drv_register(&m_touch_drv);

#if USE_SUNXI_KEY
    keydev_init();
    lv_indev_drv_init(&key_drv);
    key_drv.type = LV_INDEV_TYPE_KEYPAD;
    key_drv.read_cb = keydev_read;
    key_dev = lv_indev_drv_register(&key_drv);
    key_group = key_group_create();
    lv_indev_set_group(key_dev, key_group);
#endif

#endif
}
#endif
#else
#if (CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
#include  <windows.h>
#endif

LvcppStartupSYS::LvcppStartupSYS(void)
{
    sys_initial();
    screen_width = LV_HOR_RES_MAX;
    screen_height = LV_VER_RES_MAX;
}

LvcppStartupSYS::LvcppStartupSYS(lv_coord_t width, lv_coord_t height)
{
    sys_initial();
    screen_width = width;
    screen_height = height;
}

LvcppStartupSYS::~LvcppStartupSYS(void)
{
    if(lv_is_initialized() == true)
    {
        lv_deinit();
    }
}

void LvcppStartupSYS::sys_initial(void)
{
    lv_init();
}

int  LvcppStartupSYS::get_width(void)
{
     return screen_width;
}
int  LvcppStartupSYS::get_height(void)
{
    return screen_height;
}
void LvcppStartupSYS::refresh_now(void)
{
    lv_refr_now(topdrv_screen);
}

void LvcppStartupSYS::tick_event(void)
{
    // Periodically call the lv_task handler. */
    // It could be done in a timer interrupt or an OS task too.*/
#if (CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
    while(1)
    {
       Sleep(10);
    }
#endif
}

void LvcppStartupSYS::display_init(void)
{
#if (CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
    simulator_start();
#endif
}

void LvcppStartupSYS::sysfont_init(const char* path, int size, int type)
{
  #if(LV_USE_FREETYPE == 1)
     init_default_ttf(path, size, type);
  #endif

   init_dotarray_font(DEFAULT_DOTFONT_SIZE);
}

void LvcppStartupSYS::sysfont_set_size(int size, int type)
{
  #if(LV_USE_FREETYPE)
     change_font_size(size, type);
  #endif
}


#if (CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
void LvcppStartupSYS::logCb(const char *buf)
{
   qDebug().nospace() << "[lvgl debug:" << buf;
}

void LvcppStartupSYS::flushHandler(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  const auto stride = disp->hor_res;
  for (auto y = area->y1; y <= area->y2; ++y)
  {
    for (auto x = area->x1; x <= area->x2; ++x)
    {
      m_dispFrameBuf[x + y * stride].full = color_p->full;
      color_p++;
    }
  }
  lv_disp_flush_ready(disp);
}
void LvcppStartupSYS::flushCb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  LvcppStartupSYS *self = reinterpret_cast<LvcppStartupSYS *>(disp->user_data);
  self->flushHandler(disp, area, color_p);
}

bool LvcppStartupSYS::inputHandler(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  (void)indev_driver;

  data->state = m_inputData.state; //LV_INDEV_STATE_RELEASED;
  data->point.x = m_inputData.point.x;
  data->point.y = m_inputData.point.y;

  return false; /*Return `false` because we are not buffering and no more data to read*/
}
void LvcppStartupSYS::inputCb(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  LvcppStartupSYS *self = reinterpret_cast<LvcppStartupSYS*>(indev_driver->user_data);
  self->inputHandler(indev_driver, data);
}

QPixmap LvcppStartupSYS::getpic_screen(void)
{
   QImage img(screen_width, screen_height, QImage::Format_ARGB32);
   memcpy(img.bits(),  m_dispFrameBuf.data(), static_cast<size_t>(screen_width * screen_height) * 4);

   return QPixmap::fromImage(img);
}

int LvcppStartupSYS::simulator_start(void)
{
    const uint32_t n = static_cast<uint32_t>(screen_width * screen_height);
    m_dispFrameBuf.resize(n);
    m_buf1.resize(n);
    m_buf2.resize(n);

    lv_disp_draw_buf_init(&m_dispBuf, m_buf1.data(), m_buf2.data(), n);

    lv_disp_drv_init(&m_dispDrv);
    m_dispDrv.hor_res = static_cast<lv_coord_t>(screen_width);
    m_dispDrv.ver_res = static_cast<lv_coord_t>(screen_height);
    m_dispDrv.user_data = this;
    m_dispDrv.flush_cb = flushCb;
    m_dispDrv.draw_buf = &m_dispBuf;
    topdrv_screen = lv_disp_drv_register(&m_dispDrv);

    // to be sure that there is no button press at the start
    m_inputData.state = LV_INDEV_STATE_REL;

    root_screen = topdrv_screen->act_scr;

    lv_log_register_print_cb(logCb);

    initfont();

    return 0;
}

void LvcppStartupSYS::initfont(void)
{

}

bool LvcppStartupSYS::set_scrSize(int width, int height)
{
    screen_width = width;
    screen_height = height;
    const uint32_t pic_size = screen_width * screen_height;

    if (pic_size != m_dispBuf.size)
    {
       m_dispFrameBuf.resize(pic_size);
       m_buf1.resize(pic_size);
       m_buf2.resize(pic_size);
       lv_disp_draw_buf_init(&m_dispBuf, m_buf1.data(), m_buf2.data(), pic_size);
    }

    m_dispDrv.hor_res = static_cast<lv_coord_t>(screen_width);
    m_dispDrv.ver_res = static_cast<lv_coord_t>(screen_height);
    lv_disp_drv_update(topdrv_screen, &m_dispDrv);

    refresh_now();
    return false;
}

void LvcppStartupSYS::creat_btn(int num)
{
    lv_obj_t* btn = lv_btn_create(root_screen);
    lv_obj_set_size(btn,30,30);
    lv_obj_set_pos(btn,num*31,200);

    qDebug("num btn=%d",num);
}

lv_obj_t* LvcppStartupSYS::get_dispdrv_scr(void)
{
    return root_screen;
}

lv_font_t* LvcppStartupSYS::get_main_font(void)
{
    return main_font;
}
#endif

#endif  //QTSIM_PLATFORM
