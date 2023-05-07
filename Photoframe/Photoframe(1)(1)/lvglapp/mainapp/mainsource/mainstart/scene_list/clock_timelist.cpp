#include "clock_timelist.h"
#include  "common/common.h"


#ifdef IMAGE_DECODE
static char* weekStr[7]={STR_SUNDAY,STR_MONDAY,STR_TUESDAY,STR_WEDNESDAY,STR_THURSDAY,STR_FRIDAY,STR_SATURDAY};
static char* monNum[12]={STR_JAN,STR_FEB,STR_MAR,STR_APR,STR_MAY,STR_JUN,STR_JUL,STR_AUG,STR_SEP,
                         STR_OCT,STR_NOV,STR_DEC};
#else
static char* weekStr[7]={STR_SUNDAY,STR_MONDAY,STR_TUESDAY,STR_WEDNESDAY,STR_THURSDAY,STR_FRIDAY,STR_SATURDAY};
static const void* timeNum[10]={CLOCK_NUM0_PNG,CLOCK_NUM1_PNG,CLOCK_NUM2_PNG,CLOCK_NUM3_PNG,CLOCK_NUM4_PNG,
                         CLOCK_NUM5_PNG,CLOCK_NUM6_PNG,CLOCK_NUM7_PNG,CLOCK_NUM8_PNG,CLOCK_NUM9_PNG};
static char* monNum[12]={STR_JAN,STR_FEB,STR_MAR,STR_APR,STR_MAY,STR_JUN,STR_JUL,STR_AUG,STR_SEP,
                         STR_OCT,STR_NOV,STR_DEC};
#endif

void clockTimeList::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    CLOCK_NUM0_PNG=(void*)parse_image_from_file(CLOCK_NUM0_PNG_PATH);
    CLOCK_NUM1_PNG=(void*)parse_image_from_file(CLOCK_NUM1_PNG_PATH);
    CLOCK_NUM2_PNG=(void*)parse_image_from_file(CLOCK_NUM2_PNG_PATH);
    CLOCK_NUM3_PNG=(void*)parse_image_from_file(CLOCK_NUM3_PNG_PATH);
    CLOCK_NUM4_PNG=(void*)parse_image_from_file(CLOCK_NUM4_PNG_PATH);
    CLOCK_NUM5_PNG=(void*)parse_image_from_file(CLOCK_NUM5_PNG_PATH);
    CLOCK_NUM6_PNG=(void*)parse_image_from_file(CLOCK_NUM6_PNG_PATH);
    CLOCK_NUM7_PNG=(void*)parse_image_from_file(CLOCK_NUM7_PNG_PATH);
    CLOCK_NUM8_PNG=(void*)parse_image_from_file(CLOCK_NUM8_PNG_PATH);
    CLOCK_NUM9_PNG=(void*)parse_image_from_file(CLOCK_NUM9_PNG_PATH);
    CLOCK_SCENE0_PNG=(void*)parse_image_from_file(CLOCK_SCENE0_PNG_PATH);
#endif

}
void clockTimeList::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(CLOCK_NUM0_PNG);
    free_image(CLOCK_NUM1_PNG);
    free_image(CLOCK_NUM2_PNG);
    free_image(CLOCK_NUM3_PNG);
    free_image(CLOCK_NUM4_PNG);
    free_image(CLOCK_NUM5_PNG);
    free_image(CLOCK_NUM6_PNG);
    free_image(CLOCK_NUM7_PNG);
    free_image(CLOCK_NUM8_PNG);
    free_image(CLOCK_NUM9_PNG);
    free_image(CLOCK_SCENE0_PNG);
#endif

}

clockTimeList::clockTimeList(lv_obj_t* parent,lvcpp_sys_datetime_t *dateTime)
{
    ui_image_decode();
    memset(&dateTimesave,0,sizeof(lvcpp_sys_time_t));
    int week =0;
#ifdef IMAGE_DECODE
    void* timeNum[10]={CLOCK_NUM0_PNG,CLOCK_NUM1_PNG,CLOCK_NUM2_PNG,CLOCK_NUM3_PNG,CLOCK_NUM4_PNG,
                             CLOCK_NUM5_PNG,CLOCK_NUM6_PNG,CLOCK_NUM7_PNG,CLOCK_NUM8_PNG,CLOCK_NUM9_PNG};
#endif
    week =(dateTime->day+1+2*dateTime->month+3*(dateTime->month+1)/5+dateTime->year+dateTime->year/4-dateTime->year/100+dateTime->year/400)%7;
    plateImage = new LvcppButton(parent);
    plateImage->set_size(LV_HOR_RES_MAX,LV_VER_RES_MAX);
    plateImage->set_main_bg_color(lv_color_black(),LV_OPA_100);
    plateImage->align(LV_ALIGN_CENTER, 0, 0);
    mainframe =plateImage->myobj;

    hours0Image = new LvcppImage(mainframe);
    hours0Image->set_src(timeNum[dateTime->hour/10]);
    hours0Image->align(LV_ALIGN_TOP_LEFT, 238, 292);

    hours1Image = new LvcppImage(mainframe);
    hours1Image->set_src(timeNum[dateTime->hour%10]);
    hours1Image->align(LV_ALIGN_TOP_LEFT, 358, 292);

    minute0Image = new LvcppImage(mainframe);
    minute0Image->set_src(timeNum[dateTime->minute/10]);
    minute0Image->align(LV_ALIGN_TOP_LEFT, 526, 292);

    minute1Image = new LvcppImage(mainframe);
    minute1Image->set_src(timeNum[dateTime->minute%10]);
    minute1Image->align(LV_ALIGN_TOP_LEFT, 646, 292);

    second0Image = new LvcppImage(mainframe);
    second0Image->set_src(timeNum[dateTime->second/10]);
    second0Image->align(LV_ALIGN_TOP_LEFT, 810, 292);

    second1Image = new LvcppImage(mainframe);
    second1Image->set_src(timeNum[dateTime->second%10]);
    second1Image->align(LV_ALIGN_TOP_LEFT, 932, 292);

    strWeek = new LvcppLabel(mainframe);
    strWeek->set_size(350,40);
    strWeek->align_to(mainframe,LV_ALIGN_TOP_LEFT, 220, 170);
    strWeek->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    strWeek->txt_color(lv_color_hex(WHITE_COLOR),LV_PART_MAIN);
    strWeek->txt_align(LV_TEXT_ALIGN_LEFT);
    strWeek->set_txt(weekStr[week]);

    strDate = new LvcppLabel(mainframe);
    strDate->set_size(300,40);
    strDate->align_to(mainframe,LV_ALIGN_TOP_LEFT, 750, 170);
    strDate->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    strDate->txt_color(lv_color_hex(WHITE_COLOR),LV_PART_MAIN);
    strDate->txt_align(LV_TEXT_ALIGN_RIGHT);
    sprintf(month,"%s %.2d,%d",monNum[dateTime->month-1],dateTime->day,dateTime->year);
    strDate->set_txt(month);
}
clockTimeList::~clockTimeList(void)
{
    if(hours0Image != NULL)
    {
        delete hours0Image;
        hours0Image = NULL;
    }
    if(hours1Image != NULL)
    {
        delete hours1Image;
        hours1Image = NULL;
    }
    if(minute0Image != NULL)
    {
        delete minute0Image;
        minute0Image = NULL;
    }
    if(minute1Image != NULL)
    {
        delete minute1Image;
        minute1Image = NULL;
    }
    if(second0Image != NULL)
    {
        delete second0Image;
        second0Image = NULL;
    }
    if(second1Image != NULL)
    {
        delete second1Image;
        second1Image = NULL;
    }
    if(strWeek != NULL)
    {
        delete strWeek;
        strWeek = NULL;
    }
    if(strDate != NULL)
    {
        delete strDate;
        strDate = NULL;
    }
    if(plateImage != NULL)
    {
        delete plateImage;
        plateImage = NULL;
    }
    ui_image_free();
}

void clockTimeList::update_time(lvcpp_sys_datetime_t *dateTime)
{
    int week =0;
#ifdef IMAGE_DECODE
    void* timeNum[10]={CLOCK_NUM0_PNG,CLOCK_NUM1_PNG,CLOCK_NUM2_PNG,CLOCK_NUM3_PNG,CLOCK_NUM4_PNG,
                             CLOCK_NUM5_PNG,CLOCK_NUM6_PNG,CLOCK_NUM7_PNG,CLOCK_NUM8_PNG,CLOCK_NUM9_PNG};
#endif
    week =(dateTime->day+1+2*dateTime->month+3*(dateTime->month+1)/5+dateTime->year+dateTime->year/4-dateTime->year/100+dateTime->year/400)%7;
    if(dateTimesave.hour != dateTime->hour)
    {
        if(dateTimesave.hour/10 != dateTime->hour/10)
        {
            hours0Image->set_src((lv_img_dsc_t*)timeNum[dateTime->hour/10]);
        }
        if(dateTimesave.hour%10 != dateTime->hour%10)
        {
            hours1Image->set_src((lv_img_dsc_t*)timeNum[dateTime->hour%10]);
        }
        dateTimesave.hour = dateTime->hour;
    }
    if(dateTimesave.minute != dateTime->minute)
    {
        if(dateTimesave.minute/10 != dateTime->minute/10)
        {
            minute0Image->set_src((lv_img_dsc_t*)timeNum[dateTime->minute/10]);
        }
        if(dateTimesave.minute%10 != dateTime->minute%10)
        {
            minute1Image->set_src((lv_img_dsc_t*)timeNum[dateTime->minute%10]);
        }
        dateTimesave.minute = dateTime->minute;
    }
    if(dateTimesave.second != dateTime->second)
    {
        if(dateTimesave.second/10 != dateTime->second/10)
        {
            second0Image->set_src((lv_img_dsc_t*)timeNum[dateTime->second/10]);
        }
        if(dateTimesave.second%10 != dateTime->second%10)
        {
            second1Image->set_src((lv_img_dsc_t*)timeNum[dateTime->second%10]);
        }
        dateTimesave.second = dateTime->second;
    }
    strWeek->set_txt(weekStr[week]);
    memset(month,0,64);
    sprintf(month,"%s %.2d,%d",monNum[dateTime->month-1],dateTime->day,dateTime->year);
    strDate->set_txt(month);
}
