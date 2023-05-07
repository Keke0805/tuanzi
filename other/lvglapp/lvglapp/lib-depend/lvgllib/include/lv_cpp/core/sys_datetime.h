#ifndef SYS_DATETIME_H
#define SYS_DATETIME_H

#include  "lv_cpp/include/lvcpp_sysmsg.h"
#include "lv_cpp/include/lvcpp_sysconfig.h"

class SYSDateTime
{
public:
    SYSDateTime();
    ~SYSDateTime();

    lvcpp_sys_date_t current_date(void);
    lvcpp_sys_time_t current_time(void);
    lvcpp_sys_datetime_t current_datetime(void);

private:
    lvcpp_sys_datetime_t sys_datetime;

    int update_current(void);
};

#endif // SYS_DATETIME_H
