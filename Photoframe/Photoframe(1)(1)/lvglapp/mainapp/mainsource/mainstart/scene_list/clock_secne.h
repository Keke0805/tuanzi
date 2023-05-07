#ifndef CLOCK_SECNE_H
#define CLOCK_SECNE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"

typedef struct _clockSecne_img_t {
    int hours;
    int minute;
    int second;
    const void  *platePath;
    const void  *hoursPath;
    const void  *minutePath;
    const void  *secondPath;
    const void  *dotPath;
} clockSecne_img_t;

class clockSecne
{
public:
    clockSecne(lv_obj_t* parent,clockSecne_img_t *clockInfo);
    ~clockSecne(void);
    void update_time(int Hour,int Minute,int Second);
    LvcppButton *plateImage =NULL;
	LvcppImage *hoursImage =NULL;
    LvcppImage *minuteImage =NULL;
    LvcppImage *secondImage =NULL;
    LvcppImage *dotImage =NULL;

private:
    
};

#endif // CLOCK_SECNE_H
