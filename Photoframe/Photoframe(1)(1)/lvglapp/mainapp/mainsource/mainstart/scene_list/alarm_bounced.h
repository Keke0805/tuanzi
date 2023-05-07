#ifndef ALARM_BOUNCED_H
#define ALARM_BOUNCED_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

class Alarmbounced : public LvcppTimerTask
{
public:
    Alarmbounced(void);
    ~Alarmbounced(void);

protected:

	void*  ALARM_SLIDING0_PNG=NULL; 		  
	void*  ALARM_SLIDING1_PNG=NULL; 		  
	void*  ALARM_SLIDING2_PNG=NULL; 		  
	void*  ALARM_SLIDING3_PNG=NULL; 		  
	void*  ALARM_SLIDING_PNG=NULL;

    void ui_image_decode(void);
    void ui_image_free(void);

private:
    LvcppScreen* frame=NULL;
    LvcppList*  alarmScene=NULL;
    LvcppLabel* SceneFirst=NULL;
    LvcppLabel* SceneSecond=NULL;
    LvcppImageButton* BgSecond=NULL;
    LvcppImageButton* LineSecond=NULL;
    LvcppLabel* NameSecond=NULL;
    lv_timer_t* sceneTime =NULL;
    int lineNum=0;
	int timeNum=0;
	bool TimerStatus =false;
    void TimerCB(lv_timer_t * tmr);
	void StopTimerCB(void);
	void exit_scene(void);
    static void scene_event_handler(lv_event_t *event);
};
#endif // ALARM_BOUNCED_H
