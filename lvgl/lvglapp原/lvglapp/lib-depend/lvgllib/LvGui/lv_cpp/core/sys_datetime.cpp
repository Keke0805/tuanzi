#include  "sys_datetime.h"
#include  "lvgl/src/misc/lv_log.h"

#include <cstddef>

#if (CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
#include  "windows.h"
#else
    #include  <sys/time.h>
    #include  <time.h>
#endif

SYSDateTime::SYSDateTime()
{

}

SYSDateTime::~SYSDateTime()
{

}

int SYSDateTime::update_current(void)
{
    int ret = 0;
  #if(CURRENT_SIMOS == SIMULATOR_WIN32_PLAT)
  
    SYSTEMTIME systime;
    GetLocalTime( &systime );
	
	sys_datetime.year = systime.wYear;
    sys_datetime.month = systime.wMonth;
    sys_datetime.day = systime.wDay;
    sys_datetime.week = systime.wDayOfWeek;
    sys_datetime.hour = systime.wHour;
    sys_datetime.minute = systime.wMinute;
    sys_datetime.second = systime.wSecond;
    sys_datetime.msecond = systime.wMilliseconds;
	
  #else

	#if 0
	struct tm
	 {
	   int tm_sec;           /* Seconds. [0-60] (1 leap second) */
	   int tm_min;           /* Minutes. [0-59] */
	   int tm_hour;          /* Hours.   [0-23] */
	   int tm_mday;          /* Day.     [1-31] */
	   int tm_mon;           /* Month.   [0-11] */
	   int tm_year;          /* Year - 1900.  */
	   int tm_wday;          /* Day of week. [0-6] */
	   int tm_yday;          /* Days in year.[0-365] */
	   int tm_isdst;         /* DST.     [-1/0/1]*/
	   
	 # ifdef __USE_BSD
	   long int tm_gmtoff;       /* Seconds east of UTC.  */
	   const char *tm_zone;      /* Timezone abbreviation.  */
	 # else
	   long int __tm_gmtoff;     /* Seconds east of UTC.  */
	   const char *__tm_zone;    /* Timezone abbreviation.  */
	 # endif
	 };

	#endif

    struct timeval tv;
    time_t second;
    struct tm *datetime;
 
    gettimeofday(&tv, NULL);
    second = tv.tv_sec;
 
    datetime = localtime(&second);
    datetime->tm_year += 1900;
    datetime->tm_mon += 1;
	
  	sys_datetime.year = datetime->tm_year;
    sys_datetime.month = datetime->tm_mon;
    sys_datetime.day = datetime->tm_mday;
    sys_datetime.week = datetime->tm_wday;
    sys_datetime.hour = datetime->tm_hour;
    sys_datetime.minute = datetime->tm_min;
    sys_datetime.second = datetime->tm_sec;
    sys_datetime.msecond = tv.tv_usec/1000;

  #endif

 //   LV_LOG_WARN("sys_datetime=%d-%d-%d,week:%d,%d:%d:%d,\n",sys_datetime.year,sys_datetime.month,sys_datetime.day,sys_datetime.week,
 //                                                                     sys_datetime.hour,sys_datetime.minute,sys_datetime.second);

    return ret;
}

lvcpp_sys_date_t SYSDateTime::current_date()
{
    lvcpp_sys_date_t sys_date;
    update_current();
    sys_date.year = sys_datetime.year;
    sys_date.month = sys_datetime.month;
    sys_date.day = sys_datetime.day;
    sys_date.week = sys_datetime.week;

    return sys_date;
}

lvcpp_sys_time_t SYSDateTime::current_time()
{
    lvcpp_sys_time_t sys_time;
    update_current();
    sys_time.hour = sys_datetime.hour;
    sys_time.minute = sys_datetime.minute;
    sys_time.second = sys_datetime.second;
    sys_time.msecond = sys_datetime.msecond;

    return sys_time;
}

lvcpp_sys_datetime_t SYSDateTime::current_datetime()
{
    update_current();
    return sys_datetime;
}

