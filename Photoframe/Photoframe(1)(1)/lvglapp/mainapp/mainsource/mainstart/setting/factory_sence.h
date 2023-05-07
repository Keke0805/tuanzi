#ifndef FACTORY_SENCE_H
#define FACTORY_SENCE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

class factorySence
{
public:
    factorySence(lv_obj_t* parent = nullptr);
    ~factorySence(void);

protected:
	void*  LIST_SEL_PNG=NULL;                 
	void*  LIST_UNSEL_PNG=NULL; 
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    static void factory_list_event_handler(lv_event_t *event);
    LvcppLabel* factoryList =NULL;
    LvcppLabel* factoryListOne =NULL;
    LvcppLabel* factoryListTow =NULL;
    LvcppLabel* factoryListThree =NULL;
    LvcppLabel* factoryListFour =NULL;
    LvcppLabel* factoryListFive =NULL;
    LvcppLabel* factoryListSix =NULL;
    LvcppLabel* lineList =NULL;
    LvcppLabel* datList =NULL;
    LvcppButton* factoryListSeven =NULL;
    LvcppButton* resetDevice =NULL;
    bool selStatus =false;
};

#endif // FACTORY_SENCE_H
