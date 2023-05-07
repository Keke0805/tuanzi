#include "videomain.h"
videoMain* optVideoMain =NULL;

videoMain::videoMain(lv_obj_t* parent,Http *httpStart,char *type,char *patch)
{
    httpEnter = httpStart;
    mparent = parent;
    optVideoMain =this;

    if(strcmp(type,"List")==0)
    {
        enterVideoList(0,patch);
    }
    else
    {
        enterVideoPlay(0,patch);
    }
}

videoMain::~videoMain(void)
{
    if(VideoPlaying !=NULL)
    {
        delete VideoPlaying;
        VideoPlaying =NULL;
    }
    if(VideoList !=NULL)
    {
        delete VideoList;
        VideoList =NULL;
    }
}

void videoMain::enterVideoList(int disType,char *patch)
{
    char filePath[1024]={0};

    if(patch !=NULL)
    {
        strcpy(filePath,patch);
    }
    if(optVideoMain->httpEnter !=NULL)
    {
        optVideoMain->httpEnter->set_msg_type(UI_VIDEOLIST);
    }
    LV_LOG_USER("enterVideoList");
	if(optVideoMain->VideoList ==NULL)
	{
    	optVideoMain->VideoList = new videoList(optVideoMain->mparent);
		optVideoMain->VideoList->init_parament(disType,filePath);
	}

}

void videoMain::enterVideoPlay(int disType,char *patch)
{
    char filePath[1024]={0};

    if(patch !=NULL)
    {
        strcpy(filePath,patch);
    }
    else
    {
        return;
    }
    if(strlen(filePath)<=0)
    {
        return;
    }
    if(optVideoMain->VideoList !=NULL)
    {
        delete optVideoMain->VideoList;
        optVideoMain->VideoList =NULL;
    }
    if(optVideoMain->httpEnter !=NULL)
    {
        optVideoMain->httpEnter->set_msg_type(UI_VIDEOPLAY);
    }
    LV_LOG_USER("enterVideoPlay");
    optVideoMain->Mplayer_ui = media_get_player_data();
	if(optVideoMain->VideoPlaying == NULL)
	{
    	optVideoMain->VideoPlaying = new VideoPlay(optVideoMain->Mplayer_ui);
		optVideoMain->VideoPlaying->init_parament(disType,filePath);
	}
}

void videoMain::exitVideoPlay(int disType,char *patch)
{
    char filePath[1024]={0};

    if(patch !=NULL)
    {
        strcpy(filePath,patch);
    }
    if(optVideoMain->VideoPlaying !=NULL)
    {
        delete optVideoMain->VideoPlaying;
        optVideoMain->VideoPlaying =NULL;
    }
	LV_LOG_USER("exitVideoPlay");
    enterVideoList(disType,filePath);
}

