#include "clock_secne.h"

clockSecne::clockSecne(lv_obj_t* parent,clockSecne_img_t *clockInfo)
{
    plateImage = new LvcppButton(parent);
    plateImage->set_size(LV_HOR_RES_MAX,LV_VER_RES_MAX);
    plateImage->set_main_bg_color(lv_color_black(),LV_OPA_100);
    plateImage->set_main_bg_img_src(clockInfo->platePath);
    plateImage->align(LV_ALIGN_CENTER, 0, 0);

    hoursImage = new LvcppImage(plateImage->myobj);
    hoursImage->set_src(clockInfo->hoursPath);
    hoursImage->align(LV_ALIGN_CENTER, 0, 0);
    uint16_t h = clockInfo->hours * 300 + clockInfo->minute / 12 % 12 * 60;
    hoursImage->set_angle(h);

    minuteImage = new LvcppImage(plateImage->myobj);
    minuteImage->set_src(clockInfo->minutePath);
    minuteImage->align(LV_ALIGN_CENTER, 0, 0);
    minuteImage->set_angle(clockInfo->minute*60);

    secondImage = new LvcppImage(plateImage->myobj);
    secondImage->set_src(clockInfo->secondPath);
    secondImage->align(LV_ALIGN_CENTER, 0, 0);
    secondImage->set_angle(clockInfo->second*60);

    dotImage = new LvcppImage(plateImage->myobj);
    dotImage->set_src(clockInfo->dotPath);
    dotImage->align(LV_ALIGN_CENTER, 0, 0);
}
clockSecne::~clockSecne(void)
{
    if(dotImage != NULL)
    {
        delete dotImage;
        dotImage = NULL;
    }
    if(secondImage != NULL)
    {
        delete secondImage;
        secondImage = NULL;
    }
    if(minuteImage != NULL)
    {
        delete minuteImage;
        minuteImage = NULL;
    }
    if(hoursImage != NULL)
    {
        delete hoursImage;
        hoursImage = NULL;
    }
    if(plateImage != NULL)
    {
        delete plateImage;
        plateImage = NULL;
    }
}

void clockSecne::update_time(int Hour,int Minute,int Second)
{
    uint16_t h = Hour * 300 + Minute / 12 % 12 * 60;
    hoursImage->set_angle(h);
    minuteImage->set_angle(Minute*60);
    secondImage->set_angle(Second*60);
}

