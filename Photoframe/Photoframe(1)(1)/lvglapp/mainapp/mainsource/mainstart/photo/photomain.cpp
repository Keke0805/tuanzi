#include "photomain.h"
#include  "common/common.h"

photoMain* optPhotoMain =NULL;

photoMain::photoMain(lv_obj_t* parent,Http *httpStart,char *type,char *patch)
{
    httpEnter = httpStart;
    mparent = parent;
    optPhotoMain =this;
	image_init();
    if(strcmp(type,"List")==0)
    {
        enterPhotoList(0,patch);
    }
    else
    {
        enterPhotoPlay(0,patch);
    }
}
photoMain::~photoMain(void)
{
    if(PhotoList !=NULL)
    {
        delete PhotoList;
        PhotoList =NULL;
    }
    if(PhotoPlay !=NULL)
    {
        delete PhotoPlay;
        PhotoPlay =NULL;
    }
	image_exit();
}

void photoMain::enterPhotoList(int disType,char *patch)
{
    char filePath[1024]={0};

    if(patch !=NULL)
    {
        strcpy(filePath,patch);
    }
    if(optPhotoMain->httpEnter !=NULL)
    {
        optPhotoMain->httpEnter->set_msg_type(UI_PHOTOLIST);
    }
	LV_LOG_USER("enterPhotoList");
    optPhotoMain->PhotoList = new photoList(disType,optPhotoMain->mparent,filePath);
    optPhotoMain->PhotoList->init_parament();
}

void photoMain::enterPhotoPlay(int disType,char *patch)
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
    if(optPhotoMain->PhotoList !=NULL)
    {
        delete optPhotoMain->PhotoList;
        optPhotoMain->PhotoList =NULL;
    }
    if(optPhotoMain->httpEnter !=NULL)
    {
        optPhotoMain->httpEnter->set_msg_type(UI_PHOTOPLAY);
    }
	LV_LOG_USER("enterPhotoPlay");
    optPhotoMain->PhotoPlay = new photoPlaying();
    optPhotoMain->PhotoPlay->init_parament(disType,filePath);
}

void photoMain::exitPhotoPlay(int disType,char *patch)
{
    char filePath[1024]={0};

    if(patch !=NULL)
    {
        strcpy(filePath,patch);
    }
    if(optPhotoMain->PhotoPlay !=NULL)
    {
        delete optPhotoMain->PhotoPlay;
        optPhotoMain->PhotoPlay =NULL;
    }
	LV_LOG_USER("exitPhotoPlay");
    enterPhotoList(disType,filePath);
}
