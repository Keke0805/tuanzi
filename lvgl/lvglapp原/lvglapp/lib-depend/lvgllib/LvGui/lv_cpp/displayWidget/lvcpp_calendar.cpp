#include "lvcpp_calendar.h"

LvcppCalendar::LvcppCalendar(lv_obj_t* parent)
{
    myobj = lv_calendar_create(parent);
}

LvcppCalendar::~LvcppCalendar(void)
{

}

//set
int LvcppCalendar::calendar_set_font(int weight,int fontType)
{
    lv_calendar_set_font(weight, fontType);
    return 0;
}
int LvcppCalendar::calendar_set_bgAndBorder(lv_opa_t bgopa, lv_opa_t borderopa,int btnradius,int bgcolor)
{
    lv_calendar_set_bgAndBorder(bgopa, borderopa,btnradius,bgcolor);
    return 0;
}
int LvcppCalendar::calendar_set_color(int bgcolorcur,int today,int month,int unMonthr,int week,int cur)
{
    lv_calendar_set_color(bgcolorcur,today,month,unMonthr,week,cur);
    return 0;
}
int LvcppCalendar::set_today_date(uint32_t year, uint32_t month, uint32_t day)
{
    lv_calendar_set_today_date(myobj, year, month, day);
    return 0;
}


int LvcppCalendar::set_highlighted_dates(lv_calendar_date_t highlighted[], uint16_t date_num)
{
    lv_calendar_set_highlighted_dates(myobj, highlighted, date_num);
    return 0;
}


int LvcppCalendar::set_showed_date(uint32_t year, uint32_t month)
{
    lv_calendar_set_showed_date(myobj, year, month);
    return 0;
}


//get
const lv_calendar_date_t * LvcppCalendar::get_today_date(void)
{

    return lv_calendar_get_today_date(myobj);
}


const lv_calendar_date_t * LvcppCalendar::get_showed_date(void)
{

    return lv_calendar_get_showed_date(myobj);
}


lv_calendar_date_t * LvcppCalendar::get_highlighted_dates(void)
{

    return lv_calendar_get_highlighted_dates(myobj);
}


int  LvcppCalendar::get_highlighted_dates_num(void)
{

    return lv_calendar_get_highlighted_dates_num(myobj);
}


int LvcppCalendar::get_pressed_date(lv_calendar_date_t * date)
{

    return lv_calendar_get_pressed_date(myobj,  date);
}

