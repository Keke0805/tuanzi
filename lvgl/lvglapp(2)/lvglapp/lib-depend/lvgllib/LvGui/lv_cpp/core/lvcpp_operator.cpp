
#include "lvcpp_operator.h"

void* SystemMemory::mem_alloc(size_t size)
{
    return lv_mem_alloc(size);
}

int SystemMemory::mem_free(void* data)
{
    lv_mem_free(data);

    return 0;
}

void* SystemMemory::mem_realloc(void* data_p, size_t new_size)
{
    return lv_mem_realloc(data_p, new_size);
}

int SystemMemory::memset(void* dst, uint8_t v, size_t len)
{
    lv_memset(dst, v, len);

    return 0;
}
void* SystemMemory::memcpy(void* dst, const void* src, size_t len)
{
    return lv_memcpy(dst, src, len);
}

/////////////////////////////////////////////////////////////////////////////

lv_obj_t* SystemEvent::get_target(lv_event_t* event)
{
    return lv_event_get_target(event);
}

void* SystemEvent::get_target_userdata(lv_event_t* event)
{
    lv_obj_t* obj = get_target(event);
    return lv_obj_get_user_data(obj);
}

lv_event_code_t SystemEvent::get_event_code(lv_event_t* event)
{
    return lv_event_get_code(event);
}

void* SystemEvent::get_event_userdata(lv_event_t* event)
{
    return lv_event_get_user_data(event);
}

int SystemDevice::get_indev_point(lv_point_t* point)
{
    lv_indev_t* indev = lv_indev_get_act();
    if (lv_indev_get_type(indev) != LV_INDEV_TYPE_POINTER)
    {
        return -1;
    }

    lv_indev_get_point(indev, point);
    return 0;
}
