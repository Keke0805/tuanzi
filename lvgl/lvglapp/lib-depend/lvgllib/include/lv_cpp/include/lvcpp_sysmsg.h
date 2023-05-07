#ifndef LVGL_CPP_SYSMSG_H
#define LVGL_CPP_SYSMSG_H

struct size_rect_t{
  int x;
  int y;
  int width;
  int height;
};

struct myMsg
{
   int module;
   int msg_type;
   int msg_value;
   char msg[128];
};

struct lvcpp_sys_datetime_t{
    int year;
    int month;
    int day;
    int week;
    int hour;
    int minute;
    int second;
    int msecond;
};

struct lvcpp_sys_date_t{
    int year;
    int month;
    int day;
    int week;
};

struct lvcpp_sys_time_t{
    int hour;
    int minute;
    int second;
    int msecond;
};

#endif // LVGL_CPP_SYSMSG_H
