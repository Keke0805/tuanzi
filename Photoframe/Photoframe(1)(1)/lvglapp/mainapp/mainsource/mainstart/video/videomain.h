#ifndef VIDEOMAIN_H
#define VIDEOMAIN_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "appmsg/appmsg.h"
#include  "videolist.h"
#include  "videoplay.h"
#include  "network/http.h"


class videoMain
{
public:
    videoMain(lv_obj_t* parent,Http *httpStart,char *type,char *patch);
    ~videoMain(void);
    static void enterVideoList(int disType,char *patch);
    static void enterVideoPlay(int disType,char *patch);
	static void exitVideoPlay(int disType,char *patch);
private:
    videoList* VideoList =NULL;
    VideoPlay* VideoPlaying =NULL;
    Http *httpEnter =NULL;
    lv_obj_t* mparent =NULL;
	player_ui_t *Mplayer_ui=NULL;
};

#endif // VIDEOMAIN_H
