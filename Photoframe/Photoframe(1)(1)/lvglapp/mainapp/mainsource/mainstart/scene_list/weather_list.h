#ifndef WEATHERLIST_H
#define WEATHERLIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "../include/configCustom.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"

class WeatherList
{
public:
    WeatherList(lv_obj_t* parent,double lat,double lon,char *cityName);
    ~WeatherList(void);
    void update_weatherList(bool checkStatus);
    LvcppButton* btn=NULL;  
    LvcppScreen* Icon1=NULL;  
    LvcppScreen* Icon2=NULL;  
    char *name =NULL;
    double latData;
    double lonData;

protected:
	void*  WEATHER_UNADD_PNG=NULL;            
	void*  WEATHER_ADD_PNG=NULL;              
	void*  WEATHER_CLOSE_PNG=NULL;            
	void*  WEATHER_BIG_PNG=NULL;              
	void*  WEATHER_MODE_PNG=NULL;             
	void*  WEATHER_MODEB_PNG=NULL;            
	void*  WEATHER_GRAY_PNG=NULL;             
	void*  WEATHER_YELLOW_PNG=NULL; 
    void ui_image_decode(void);
    void ui_image_free(void);
private:
    lv_obj_t* mainframe=NULL;
};

#endif // WEATHERLIST_H
