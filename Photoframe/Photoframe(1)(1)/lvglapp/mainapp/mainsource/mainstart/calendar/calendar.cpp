#include  "../mainappstart.h"
#include "calendar.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
static int today = 0;
static int todaySave = 0;
static int hours = 0;
static int hoursSave = 0;
static int dateInde[42]={0};

void Calendar::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);

    HEAD_ICON_CALENDART_PNG=(void*)parse_image_from_file(HEAD_ICON_CALENDART_PNG_PATH);

    LISTBG_PNG=(void*)parse_image_from_file(LISTBG_PNG_PATH);

    CALENDAR_UNPREV_PNG=(void*)parse_image_from_file(CALENDAR_UNPREV_PNG_PATH);
    CALENDAR_PREV_PNG=(void*)parse_image_from_file(CALENDAR_PREV_PNG_PATH);
    CALENDAR_UNNEXT_PNG=(void*)parse_image_from_file(CALENDAR_UNNEXT_PNG_PATH);
    CALENDAR_NEXT_PNG=(void*)parse_image_from_file(CALENDAR_NEXT_PNG_PATH);
#endif
}
void Calendar::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(HEAD_RETURN_PNG);
    free_image(HEAD_RETURN_SEL_PNG);

    free_image(HEAD_ICON_CALENDART_PNG);

    free_image(LISTBG_PNG);

    free_image(CALENDAR_UNPREV_PNG);
    free_image(CALENDAR_PREV_PNG);
    free_image(CALENDAR_UNNEXT_PNG);
    free_image(CALENDAR_NEXT_PNG);
#endif
}

Calendar::Calendar(lv_obj_t* parent)
{
    ui_image_decode();
    frame = new LvcppScreen(parent);
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_black(),LV_OPA_0);
    frame->set_main_bg_img_src(LISTBG_PNG);
    mainscreen = frame->myobj;
}

Calendar::~Calendar(void)
{
    StartTimerShow =false;
    calendar_head_dele();
    calList_list_dele();
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
        lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_CLICKABLE);
    }
    ui_image_free();
}

LvcppButton* Calendar::LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo)
{
    LvcppButton* child_button =NULL;

    child_button = new LvcppButton(paren);
    child_button->set_size(uiInfo->w,uiInfo->h);
    child_button->align_to(paren,LV_ALIGN_TOP_LEFT,uiInfo->x,uiInfo->y);
    child_button->set_main_bg_opa(LV_OPA_0);
    child_button->set_main_radius(0);
    child_button->set_main_pad_all(0);
    child_button->set_main_border_width(0);
    child_button->set_main_bg_img_src(uiInfo->ui_patch);
    child_button->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    child_button->set_userdata(NULL);
    if(show_cb ==true)
    {
        child_button->set_userdata((void*)uiInfo->userdata);
        child_button->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
        child_button->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
    }
    return child_button;
}

LvcppLabel* Calendar::LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo)
{
    LvcppLabel* childView =NULL;

    childView = new LvcppLabel(paren);
    childView->set_size(strInfo->w,strInfo->h);
    childView->align_to(paren,LV_ALIGN_TOP_LEFT, strInfo->x, strInfo->y);
    //childView->set_main_bg_color(lv_color_black(),LV_OPA_100);
    childView->txt_font_size(strInfo->h-6, FT_FONT_STYLE_NORMAL);
    childView->txt_align(align);
    childView->txt_color(lv_color_hex(strInfo->str_color),LV_PART_MAIN);
    childView->set_txt(strInfo->str_buff);
    return childView;
}

char* Calendar::calendar_get_week(int y,int m,int d)
{
    char *curWeek =NULL;
    int week =0;

    week =(d+1+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
    switch(week)
    {
        case 0:
            curWeek = (char*)STR_SUNDAY;
        break;
        case 1:
            curWeek = (char*)STR_MONDAY;
        break;
        case 2:
            curWeek = (char*)STR_TUESDAY;
        break;
        case 3:
            curWeek = (char*)STR_WEDNESDAY;
        break;
        case 4:
            curWeek = (char*)STR_THURSDAY;
        break;
        case 5:
            curWeek = (char*)STR_FRIDAY;
        break;
        case 6:
            curWeek = (char*)STR_SATURDAY;
        break;
        default:
        break;
    }
    return curWeek;
}

void Calendar::get_dateTime(void)
{
    SYSDateTime gettime;
    user_time = gettime.current_datetime();
    sprintf(headDate,"%.2d-%d",user_time.month,user_time.year);
    sprintf(todayDate,"%.2d-%.2d-%d",user_time.month,user_time.day,user_time.year);
    today = user_time.day;
    hours = user_time.hour;
    if(timeType ==12)
    {
        if((user_time.hour >0)&&(user_time.hour <12))
        {
            sprintf(todayTime,"%d:%.2d:%.2d",user_time.hour,user_time.minute,user_time.second);
            apmType =false;
        }
        else if((user_time.hour >12)&&(user_time.hour <24))
        {
            sprintf(todayTime,"%d:%.2d:%.2d",(user_time.hour -12),user_time.minute,user_time.second);
            apmType =true;
        }
        else if(user_time.hour ==0)
        {
            sprintf(todayTime,"12:%.2d:%.2d",user_time.minute,user_time.second);
            apmType =false;
        }
        else if(user_time.hour ==12)
        {
            sprintf(todayTime,"%d:%.2d:%.2d",user_time.hour,user_time.minute,user_time.second);
            apmType =true;
        }
    }
    else
    {
        sprintf(todayTime,"%.2d:%.2d:%.2d",user_time.hour,user_time.minute,user_time.second);
    }
    weekStr = calendar_get_week(user_time.year,user_time.month,user_time.day);
}

int Calendar::init_parament(void)
{
    calendar_head_creat();
    Calendar_scene_creat();
    startTimer(500, this);
    StartTimerShow =true;
    return 0;
}

void Calendar::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    if(StartTimerShow !=true)
        return;
    get_dateTime();
    strTime->set_txt(todayTime);
    if((hoursSave != hours)&&(timeType ==12))
    {
        if(apmType ==true)
        {
            strApm->set_txt(STR_TEMP_PM);
        }
        else
        {
            strApm->set_txt(STR_TEMP_AM);
        }
    }

    if(todaySave != today)
    {
        todaySave = today;
        strWeek->set_txt(weekStr);
        strDateTime->set_txt(todayDate);
        strDate->set_txt(headDate);
        lv_calendar_date_t highlighted_days;
        yearInde = user_time.year;
        monthInde = user_time.month;
        dayInde = user_time.day;
        calScene->set_showed_date(yearInde,monthInde);
        calScene->set_today_date(yearInde,monthInde,dayInde);
        highlighted_days.year = yearInde;
        highlighted_days.month = monthInde;
        highlighted_days.day = dayInde;
        calScene->set_highlighted_dates(&highlighted_days,1);
    }
}

void Calendar::calendar_head_creat(void)
{
    lv_ui_inof_t uiInfo;
    lv_str_inof_t strInfo;

    uiInfo.x =30;
    uiInfo.y =8;
    uiInfo.w =66;
    uiInfo.h =66;
    uiInfo.userdata =HEAD_ICON_RETURN;
    uiInfo.ui_patch =(char *)HEAD_RETURN_PNG;
    buttonReturn =LvcppButtonHead(mainscreen,true,&uiInfo);

    uiInfo.x =114;
    uiInfo.y =8;
    uiInfo.w =66;
    uiInfo.h =66;
    uiInfo.ui_patch =(char *)HEAD_ICON_CALENDART_PNG;
    calendarIcon =LvcppButtonHead(mainscreen,false,&uiInfo);
    calendarIcon->set_userdata(NULL);

    uiInfo.x =230;
    uiInfo.y =130;
    uiInfo.w =40;
    uiInfo.h =40;
    uiInfo.userdata =HEAD_ICON_PREV;
    uiInfo.ui_patch =(char *)CALENDAR_UNPREV_PNG;
    monthPrev =LvcppButtonHead(mainscreen,true,&uiInfo);

    uiInfo.x =510;
    uiInfo.y =130;
    uiInfo.w =40;
    uiInfo.h =40;
    uiInfo.userdata =HEAD_ICON_NEXT;
    uiInfo.ui_patch =(char *)CALENDAR_UNNEXT_PNG;
    monthNext =LvcppButtonHead(mainscreen,true,&uiInfo);

    get_dateTime();
    strInfo.x=270;
    strInfo.y =130;
    strInfo.w =240;
    strInfo.h =42;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =headDate;
    strDate = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strDate->txt_font_size(36, FT_FONT_STYLE_BOLD);

    strInfo.x=960;
    strInfo.y =500;
    strInfo.w =220;
    strInfo.h =46;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =weekStr;
    strWeek = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);

    strInfo.x=960;
    strInfo.y =550;
    strInfo.w =220;
    strInfo.h =46;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =todayDate;
    strDateTime = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strDateTime->txt_font_size(40, FT_FONT_STYLE_BOLD);

    strInfo.x=820;
    strInfo.y =350;
    strInfo.w =320;
    strInfo.h =80;
    strInfo.str_color =0xf9c139;
    strInfo.str_buff =todayTime;
    strTime = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_RIGHT,&strInfo);

    strInfo.x=1160;
    strInfo.y =380;
    strInfo.w =100;
    strInfo.h =50;
    strInfo.str_color =0xf9c139;
    if(apmType ==true)
    {
        strInfo.str_buff =(char*)STR_TEMP_PM;
    }
    else
    {
        strInfo.str_buff =(char*)STR_TEMP_AM;
    }
    strApm = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);
    if(timeType !=12)
    {
        strApm->show(false);
    }

    strToday = new LvcppButton(mainscreen);
    strToday->set_size(200,40);
    strToday->align(LV_ALIGN_TOP_LEFT,550,128);
    strToday->set_main_radius(0);
    strToday->set_main_pad_all(0);
    strToday->set_main_pad_row(0);
    strToday->set_main_bg_color(lv_color_hex(LIGHTBLUE_COLOR),LV_PART_MAIN);
    strToday->set_main_bg_opa(LV_ALIGN_TOP_LEFT);
    strToday->txt_size(180, 34, LV_LABEL_LONG_WRAP);
    strToday->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    strToday->txt_align(LV_ALIGN_TOP_MID,10,3);
    strToday->add_txt((char*)STR_TODAY);
    strToday->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    strToday->set_userdata(NULL);
    strToday->set_userdata((void*)HEAD_ICON_BALCK);
    strToday->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
    strToday->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);

    strInfo.x=80;
    strInfo.y =190;
    strInfo.w =90;
    strInfo.h =40;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =(char*)STR_SUN;
    strSun = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strSun->txt_font_size(34, FT_FONT_STYLE_BOLD);

    strInfo.x=170;
    strInfo.y =190;
    strInfo.w =90;
    strInfo.h =40;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =(char*)STR_MON;
    strMon = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strMon->txt_font_size(34, FT_FONT_STYLE_BOLD);

    strInfo.x=260;
    strInfo.y =190;
    strInfo.w =90;
    strInfo.h =40;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =(char*)STR_TUE;
    strTue = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strTue->txt_font_size(34, FT_FONT_STYLE_BOLD);

    strInfo.x=350;
    strInfo.y =190;
    strInfo.w =90;
    strInfo.h =40;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =(char*)STR_WED;
    strWeb = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strWeb->txt_font_size(34, FT_FONT_STYLE_BOLD);

    strInfo.x=440;
    strInfo.y =190;
    strInfo.w =90;
    strInfo.h =40;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =(char*)STR_THU;
    strThu = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strThu->txt_font_size(34, FT_FONT_STYLE_BOLD);

    strInfo.x=530;
    strInfo.y =190;
    strInfo.w =90;
    strInfo.h =40;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =(char*)STR_FRI;
    strFri = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strFri->txt_font_size(34, FT_FONT_STYLE_BOLD);

    strInfo.x=620;
    strInfo.y =190;
    strInfo.w =90;
    strInfo.h =40;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =(char*)STR_SAT;
    strSat = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strSat->txt_font_size(34, FT_FONT_STYLE_BOLD);
}

void Calendar::calendar_head_dele(void)
{
    if(strDateTime != NULL)
    {
        delete strDateTime;
        strDateTime =NULL;
    }
    if(strWeek != NULL)
    {
        delete strWeek;
        strWeek =NULL;
    }
    if(strApm != NULL)
    {
        delete strApm;
        strApm =NULL;
    }
    if(strTime != NULL)
    {
        delete strTime;
        strTime =NULL;
    }
    if(strDate != NULL)
    {
        delete strDate;
        strDate =NULL;
    }
    if(strToday != NULL)
    {
        delete strToday;
        strToday =NULL;
    }
    if(strSun != NULL)
    {
        delete strSun;
        strSun =NULL;
    }
    if(strMon != NULL)
    {
        delete strMon;
        strMon =NULL;
    }
    if(strTue != NULL)
    {
        delete strTue;
        strTue =NULL;
    }
    if(strWeb != NULL)
    {
        delete strWeb;
        strWeb =NULL;
    }
    if(strThu != NULL)
    {
        delete strThu;
        strThu =NULL;
    }
    if(strFri != NULL)
    {
        delete strFri;
        strFri =NULL;
    }
    if(strSat != NULL)
    {
        delete strSat;
        strSat =NULL;
    }
    if(monthNext != NULL)
    {
        delete monthNext;
        monthNext =NULL;
    }
    if(monthPrev != NULL)
    {
        delete monthPrev;
        monthPrev =NULL;
    }
    if(buttonReturn != NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
    if(calendarIcon != NULL)
    {
        delete calendarIcon;
        calendarIcon =NULL;
    }
}

void Calendar::head_event_handler(lv_event_t *event)
{
    Calendar* opt = (Calendar*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    int set_selete = (uintptr_t)target->user_data;

    switch(set_selete)
    {
        case HEAD_ICON_RETURN:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
            }
            else
            {
                opt->StartTimerShow =false;
        		MainAPPStart::calendarmain_destory();
				return;
            }
        break;

        case HEAD_ICON_BALCK:
            if(event->code== LV_EVENT_PRESSED)
            {
                lv_calendar_date_t highlighted_days;
                opt->yearInde = opt->user_time.year;
                opt->monthInde = opt->user_time.month;
                opt->dayInde = opt->user_time.day;
                opt->calScene->set_showed_date(opt->yearInde,opt->monthInde);
                sprintf(opt->headDate,"%.2d-%d",opt->monthInde,opt->yearInde);
                opt->strDate->set_txt(opt->headDate);
                opt->calScene->set_today_date(opt->yearInde,opt->monthInde,opt->dayInde);
                highlighted_days.year = opt->yearInde;
                highlighted_days.month = opt->monthInde;
                highlighted_days.day = opt->dayInde;
                opt->calScene->set_highlighted_dates(&highlighted_days,1);
            }
        break;
        case HEAD_ICON_PREV:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->monthPrev->set_main_bg_img_src(opt->CALENDAR_PREV_PNG);
            }
            else
            {
                opt->monthPrev->set_main_bg_img_src(opt->CALENDAR_UNPREV_PNG);
                opt->monthInde --;
                if(opt->monthInde <1)
                {
                    opt->monthInde =12;
                    opt->yearInde --;
                }
                lv_calendar_date_t highlighted_days;
                opt->calScene->set_showed_date(opt->yearInde,opt->monthInde);
                sprintf(opt->headDate,"%.2d-%d",opt->monthInde,opt->yearInde);
                opt->strDate->set_txt(opt->headDate);
                opt->calScene->set_showed_date(opt->yearInde,opt->monthInde);
                highlighted_days.year = opt->yearInde;
                highlighted_days.month = opt->monthInde;
                highlighted_days.day = 1;
                opt->calScene->set_highlighted_dates(&highlighted_days,1);
            }
        break;
        case HEAD_ICON_NEXT:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->monthNext->set_main_bg_img_src(opt->CALENDAR_NEXT_PNG);
            }
            else
            {
                opt->monthNext->set_main_bg_img_src(opt->CALENDAR_UNNEXT_PNG);
                opt->monthInde ++;
                if(opt->monthInde >12)
                {
                    opt->monthInde =1;
                    opt->yearInde ++;
                }
                lv_calendar_date_t highlighted_days;
                opt->calScene->set_showed_date(opt->yearInde,opt->monthInde);
                sprintf(opt->headDate,"%.2d-%d",opt->monthInde,opt->yearInde);
                opt->strDate->set_txt(opt->headDate);
                opt->calScene->set_showed_date(opt->yearInde,opt->monthInde);
                highlighted_days.year = opt->yearInde;
                highlighted_days.month = opt->monthInde;
                highlighted_days.day = opt->dayInde;
                opt->calScene->set_highlighted_dates(&highlighted_days,1);
            }
        break;
        default:
            break;
    }

}

void Calendar::Calendar_scene_creat(void)
{
    lv_calendar_date_t highlighted_days;
    yearInde = user_time.year;
    monthInde = user_time.month;
    dayInde = user_time.day;
    calScene = new LvcppCalendar(mainscreen);
    calScene->set_size(630, 540);
    calScene->align_to(mainscreen,LV_ALIGN_TOP_LEFT, 80, 230);
    calScene->set_main_bg_opa(LV_OPA_TRANSP);
    calScene->set_main_radius(0);
    calScene->set_main_pad_all(0);
    calScene->set_main_border_width(0);
    calScene->add_event_cb(calList_event_handler,LV_EVENT_VALUE_CHANGED,this);
    calScene->set_today_date(yearInde,monthInde,dayInde);
    calScene->set_showed_date(yearInde,monthInde);
    highlighted_days.year =yearInde;
    highlighted_days.month =monthInde;
    highlighted_days.day =dayInde;
    calScene->set_highlighted_dates(&highlighted_days,1);
}

void Calendar::calList_event_handler(lv_event_t *event)
{
    lv_calendar_date_t date;
    Calendar* opt = (Calendar*) event->user_data;
    if(event->code == LV_EVENT_VALUE_CHANGED)
    {
        opt->calScene->get_pressed_date(&date);
        if((date.year != opt->yearInde)||(date.month != opt->monthInde))
        {
            opt->yearInde = date.year;
            opt->monthInde = date.month;
            opt->calScene->set_showed_date(opt->yearInde,opt->monthInde);
            sprintf(opt->headDate,"%.2d-%d",opt->monthInde,opt->yearInde);
            opt->strDate->set_txt(opt->headDate);
        }
        opt->calScene->set_highlighted_dates(&date,1);
    }
}

void Calendar::calList_list_dele(void)
{
    if(calScene !=NULL)
    {
        delete calScene;
        calScene =NULL;
    }
}
