#ifndef PHOTOMAIN_H
#define PHOTOMAIN_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "appmsg/appmsg.h"
#include  "photolist.h"
#include  "photoplaying.h"
#include  "network/http.h"

class photoMain
{
public:
    photoMain(lv_obj_t* parent,Http *httpStart,char *type,char *patch);
    ~photoMain(void);
   static void enterPhotoList(int disType,char *patch);
   static void enterPhotoPlay(int disType,char *patch);
   static  void exitPhotoPlay(int disType,char *patch);
private:
    photoList* PhotoList =NULL;
    photoPlaying* PhotoPlay =NULL;
    Http *httpEnter =NULL;
    lv_obj_t* mparent =NULL;
};

#endif // PHOTOMAIN_H
