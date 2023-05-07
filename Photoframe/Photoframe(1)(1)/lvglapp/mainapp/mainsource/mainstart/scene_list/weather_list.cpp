#include "weather_list.h"
#include  "common/common.h"

void WeatherList::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    WEATHER_CLOSE_PNG=(void*)parse_image_from_file(WEATHER_CLOSE_PNG_PATH);
    WEATHER_GRAY_PNG=(void*)parse_image_from_file(WEATHER_GRAY_PNG_PATH);
    WEATHER_YELLOW_PNG=(void*)parse_image_from_file(WEATHER_YELLOW_PNG_PATH);
#endif
}

void WeatherList::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(WEATHER_CLOSE_PNG);
    free_image(WEATHER_GRAY_PNG);
    free_image(WEATHER_YELLOW_PNG);
#endif
}

WeatherList::WeatherList(lv_obj_t* parent,double lat,double lon,char *cityName)
{
    ui_image_decode();
    name = new char[strlen(cityName) + 8];
    strcpy(name,cityName);
    latData =lat;
    lonData =lon;

    btn = new LvcppButton(parent);
    btn->set_size(320,60);
    btn->align(LV_ALIGN_TOP_LEFT,0,0);
    btn->set_main_radius(0);
    btn->set_main_pad_all(0);
    btn->set_main_pad_row(0);
    btn->set_main_bg_color(lv_color_hex(0x216fb1),LV_PART_MAIN);
    btn->set_main_bg_opa(LV_OPA_0);
    btn->txt_size(100, 40, LV_LABEL_LONG_WRAP);
    btn->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    btn->txt_align(LV_ALIGN_TOP_LEFT,60,10);
    btn->txt_color(lv_color_hex(0xcdcdcd));
    btn->add_txt(name);
    mainframe = btn->myobj;

    Icon1 = new LvcppScreen(mainframe);
    Icon1->set_size(40,40);
    Icon1->align(LV_ALIGN_TOP_LEFT, 20, 10);
    Icon1->set_main_bg_img_src(WEATHER_GRAY_PNG);
    Icon1->set_main_bg_opa(LV_OPA_0);

    Icon2 = new LvcppScreen(mainframe);
    Icon2->set_size(40,40);
    Icon2->align(LV_ALIGN_TOP_LEFT, 260, 10);
    Icon2->set_main_bg_img_src(WEATHER_CLOSE_PNG);
    Icon2->set_main_bg_opa(LV_OPA_0);
}

WeatherList::~WeatherList(void)
{
    if(Icon1 != NULL)
    {
        delete Icon1;
        Icon1 = NULL;
    }
    if(Icon2 != NULL)
    {
        delete Icon2;
        Icon2 = NULL;
    }
    if(name!= NULL)
    {
        delete[] name;
        name =NULL;
    }
    if(btn != NULL)
    {
        delete btn;
        btn = NULL;
    }
    ui_image_free();
}
void WeatherList::update_weatherList(bool checkStatus)
{
    if(checkStatus ==true)
    {
        btn->txt_color(lv_color_hex(0xf9c000));
        Icon1->set_main_bg_img_src(WEATHER_YELLOW_PNG);
    }
    else
    {
        btn->txt_color(lv_color_hex(0xcdcdcd));
        Icon1->set_main_bg_img_src(WEATHER_GRAY_PNG);
    }
}
