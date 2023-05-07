#ifndef LVCPP_CALENDAR_H
#define LVCPP_CALENDAR_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppCalendar : public LvcppObject
{
public:
    LvcppCalendar(lv_obj_t* parent = nullptr);
    ~LvcppCalendar(void);

    //set
    int calendar_set_font(int weight,int fontType);
    int calendar_set_bgAndBorder(lv_opa_t bgopa, lv_opa_t borderopa,int btnradius,int bgcolor);
    int calendar_set_color(int bgcolorcur,int today,int month,int unMonthr,int week,int cur);
    int set_today_date(uint32_t year, uint32_t month, uint32_t day);
    int set_highlighted_dates(lv_calendar_date_t highlighted[], uint16_t date_num);
    int set_showed_date(uint32_t year, uint32_t month);

    //get
    const lv_calendar_date_t * get_today_date(void);
    const lv_calendar_date_t * get_showed_date(void);
    lv_calendar_date_t * get_highlighted_dates(void);
    int  get_highlighted_dates_num(void);
    int get_pressed_date(lv_calendar_date_t * date);

private:

    lv_calendar_date_t user_date;

};

#endif // LVCPP_CALENDAR_H
