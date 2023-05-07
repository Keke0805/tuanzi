#ifndef CHECKTIMEMSG_H
#define CHECKTIMEMSG_H
#include <sys/stat.h>
#include  "lvgl/lvgl.h"
#include  "../appmsg/appmsg.h"
#include  "lvgl/src/custom/cjson/cJSON.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"
#include  "mainstart/include/configCustom.h"
#define VA_ALARMLIST_PATH			"/etc/alarm_list.cfg"

typedef struct
{
    int hours;
    int minute;
    int second;
    int type;
    int ring;
    int status;
    char name[64];
}alarm_info;

typedef struct alarm_list_s
{
    alarm_info AlarmInfo;
    struct alarm_list_s *next_list;
}alarm_list_t;
typedef std::function<void(myMsg)> MsgCallBack;
class checkTimeMsg : public LvcppTimerTask
{
public:
    checkTimeMsg();
    ~checkTimeMsg(void);
	static void funcallback(msg_apps_t *msg);
    void alarm_add_list(alarm_info *alarnInfo);
    void alarm_rm_node(alarm_info *alarnInfo);
    void alarm_change_status(alarm_info *alarnInfo,int status);
    void alarm_save_file(void);
private:
    void TimerCB(lv_timer_t * tmr);
    void cjson_alarmInfo(char*alarmBuff);
    void alarm_add_node(alarm_list_t *node);
    void alarm_destory(void);
    void alarm_check_time(void);
    alarm_list_t *AlarmInfoList = NULL;
    bool ringSta =false;
	int saveTime =0;
};

#endif // CHECKTIMEMSG_H
