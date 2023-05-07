#ifndef ALBUM_LANGUAGE_LIST_H
#define ALBUM_LANGUAGE_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

class albumLanguageList
{
public:
    albumLanguageList(lv_obj_t* parent = nullptr);
    ~albumLanguageList(void);
    LvcppButton* headLabel =NULL;
    LvcppLabel* nameLabel =NULL;
    LvcppLabel* iconLabel =NULL;
protected:
	void*  SETTING_ALBUM_TURE_PNG=NULL;  
    void ui_image_decode(void);
    void ui_image_free(void);
private:
    LvcppLabel* lineLabel =NULL;
};

#endif // ALBUM_LANGUAGE_LIST_H
