#pragma once
#include  "lvgl/lvgl.h"

namespace LVGLSYSTEM {
    class SystemMemory;
    class SystemEvent;
};

class SystemMemory
{
public:
   // SystemMemory() {};
   // ~SystemMemory() {};

    void* mem_alloc(size_t size);
    int mem_free(void* data);
    void* mem_realloc(void* data_p, size_t new_size);
    int memset(void* dst, uint8_t v, size_t len);
    void* memcpy(void* dst, const void* src, size_t len);

private:

};

class SystemEvent
{
public:
  //  SystemEvent(void);
  //  virtual ~SystemEvent(void);

    lv_obj_t* get_target(lv_event_t* event);
    void* get_target_userdata(lv_event_t* event);
    lv_event_code_t get_event_code(lv_event_t* event);
    void* get_event_userdata(lv_event_t* event);

private:

};

class SystemDevice
{
public:
    //  SystemDevice(void);
    //  virtual ~SystemDevice(void);

    int get_indev_point(lv_point_t* point);

private:

};


