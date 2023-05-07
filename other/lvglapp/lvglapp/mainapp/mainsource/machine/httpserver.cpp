#include "httpserver.h"
#include "lvgl/src/custom/cjson/cJSON.h"

#if (QTSIM_PLATFORM==0)
#ifdef __cplusplus
extern "C" {
#endif
#include  "mainstart/hotplugdetect/common/applib/applib.h"
#include  "mainstart/hotplugdetect/common/applib/app_config.h"
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif

#if QTSIM_PLATFORM==0

httpserver::httpserver(int port)
{
    http_service_register();
    server.registerHttpService(&service);
    server.setPort(port);
    server.setThreadNum(1);
    server.run(false);
}

httpserver::~httpserver()
{
    server.stop();
}

std::string httpserver::RespJsontoString(bool flag)
{
    std::string data;
    cJSON* root = NULL;
    root = cJSON_CreateObject();
    if(flag)
    {
        cJSON_AddNumberToObject(root, "code",0);
        cJSON_AddStringToObject(root, "msg", "推送成功");
    }
    else
    {
        cJSON_AddNumberToObject(root, "code",1);
        cJSON_AddStringToObject(root, "msg", "推送失败");
    }
    data = cJSON_Print(root);
    LV_LOG_USER("body = %s",data.c_str());
    cJSON_Delete(root);
    return data;
}

int httpserver::ReqStringtoJsonParse(std::string data)
{
    cJSON* root=NULL;
    cJSON* layout=NULL;
    cJSON* detail=NULL;
    cJSON* detail_array=NULL;
    cJSON* item=NULL;
    int array_total = 0;

    if(data.empty())
    {
        return -1;
    }
    root = cJSON_Parse(data.c_str());
    if (!root)
    {
        LV_LOG_USER("parse failed");
        return -1;
    }
    memset(&g_CanvasInfo,0,sizeof(zpc_canvas_param_t));

    item = cJSON_GetObjectItem(root, "clear");
    if(item&&item->type==cJSON_Number)
    {
        g_CanvasInfo.clear_flag=item->valueint;
        if(g_CanvasInfo.clear_flag)
        {
            zp_param_initial();
            msg_apps_t msg;
            memset(&msg,0,sizeof(msg_apps_t));
            msg.type = MSG_UPDATE_CANVAS;
            SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
            return 0;
        }
    }
	else
    {
        g_CanvasInfo.clear_flag=0;
    }
	
    item = cJSON_GetObjectItem(root, "username");
    if (item&&item->type==cJSON_String)
    {
        strcpy(g_CanvasInfo.username, cJSON_GetStringValue(item));
        LV_LOG_USER("g_CanvasInfo.username = %s",g_CanvasInfo.username);
    }
    else
    {
        strcpy(g_CanvasInfo.username, "姓名");
    }
    item = cJSON_GetObjectItem(root, "company");
    if (item&&item->type==cJSON_String)
    {
        strcpy(g_CanvasInfo.company, cJSON_GetStringValue(item));
        LV_LOG_USER("g_CanvasInfo.company = %s",g_CanvasInfo.company);
    }
    else
    {
        strcpy(g_CanvasInfo.company, "");
    }
    item = cJSON_GetObjectItem(root, "duty");
    if (item&&item->type==cJSON_String)
    {
        strcpy(g_CanvasInfo.duty, cJSON_GetStringValue(item));
        LV_LOG_USER("g_CanvasInfo.duty = %s",g_CanvasInfo.duty);
    }
    else
    {
        strcpy(g_CanvasInfo.duty, "");
    }

    item = cJSON_GetObjectItem(root, "other");
    if (item&&item->type==cJSON_String)
    {
        strcpy(g_CanvasInfo.other, cJSON_GetStringValue(item));
        LV_LOG_USER("g_CanvasInfo.other = %s",g_CanvasInfo.other);
    }
    else
    {
        strcpy(g_CanvasInfo.other, "");
    }

    layout = cJSON_GetObjectItem(root, "layout");
    if (!layout)
    {
        LV_LOG_USER("layout is NULL");
        strcpy(g_CanvasInfo.layout.BgColor, "FF0000");
        strcpy(g_CanvasInfo.layout.BgImg, "");
        for(int i=0;i<MAX_DETAIL_NUM;i++)
		{
			if(i==0)
			{
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "username");
                g_CanvasInfo.layout.detail[i].ElePointX=0;
                g_CanvasInfo.layout.detail[i].ElePointY=200;
                g_CanvasInfo.layout.detail[i].EleWidth=1024;
                g_CanvasInfo.layout.detail[i].EleHeight=200;
                g_CanvasInfo.layout.detail[i].TextSize=200;
                strcpy(g_CanvasInfo.layout.detail[i].TextColor, "fac000");
                strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                g_CanvasInfo.layout.detail[i].HorizontalAlign=2;
                g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                g_CanvasInfo.layout.detail[i].TextLetterSpace=50;
                g_CanvasInfo.layout.detail[i].TextType=2;
			}
			else if(i==1)
			{
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "company");
                g_CanvasInfo.layout.detail[i].ElePointX=0;
                g_CanvasInfo.layout.detail[i].ElePointY=0;
                g_CanvasInfo.layout.detail[i].EleWidth=1024;
                g_CanvasInfo.layout.detail[i].EleHeight=80;
                g_CanvasInfo.layout.detail[i].TextSize=80;
                strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
                g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                g_CanvasInfo.layout.detail[i].TextType=0;
			}
			else if(i==2)
			{
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "duty");
                g_CanvasInfo.layout.detail[i].ElePointX=0;
                g_CanvasInfo.layout.detail[i].ElePointY=500;
                g_CanvasInfo.layout.detail[i].EleWidth=1024;
                g_CanvasInfo.layout.detail[i].EleHeight=100;
                g_CanvasInfo.layout.detail[i].TextSize=80;
                strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                g_CanvasInfo.layout.detail[i].HorizontalAlign=3;
                g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                g_CanvasInfo.layout.detail[i].TextType=0;
			}
            else if(i==3)
            {
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "other");
                g_CanvasInfo.layout.detail[i].ElePointX=0;
                g_CanvasInfo.layout.detail[i].ElePointY=500;
                g_CanvasInfo.layout.detail[i].EleWidth=1024;
                g_CanvasInfo.layout.detail[i].EleHeight=100;
                g_CanvasInfo.layout.detail[i].TextSize=80;
                strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
                g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                g_CanvasInfo.layout.detail[i].TextType=0;
            }
		}
        //update_flag=1;
        msg_apps_t msg;
        memset(&msg,0,sizeof(msg_apps_t));
        msg.type = MSG_UPDATE_CANVAS;
        SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
        return 0;
    }
    item = cJSON_GetObjectItem(layout, "BackgroundColor");
    if (item&&item->type==cJSON_String)
    {
        strcpy(g_CanvasInfo.layout.BgColor, cJSON_GetStringValue(item));
    }
    else
    {
        strcpy(g_CanvasInfo.layout.BgColor, "FF0000");
    }
    item = cJSON_GetObjectItem(layout, "BackgroundImage");
    if (item&&item->type==cJSON_String)
    {
        strcpy(g_CanvasInfo.layout.BgImg, cJSON_GetStringValue(item));
    }
    else
    {
        strcpy(g_CanvasInfo.layout.BgImg, "");
    }

    detail = cJSON_GetObjectItem(layout, "detail");
    if (!detail)
    {
        LV_LOG_USER("detail is NULL");
        for(int i=0;i<MAX_DETAIL_NUM;i++)
		{
			if(i==0)
			{
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "username");
                g_CanvasInfo.layout.detail[i].ElePointX=0;
                g_CanvasInfo.layout.detail[i].ElePointY=200;
                g_CanvasInfo.layout.detail[i].EleWidth=1024;
                g_CanvasInfo.layout.detail[i].EleHeight=200;
                g_CanvasInfo.layout.detail[i].TextSize=200;
                strcpy(g_CanvasInfo.layout.detail[i].TextColor, "fac000");
                strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                g_CanvasInfo.layout.detail[i].HorizontalAlign=2;
                g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                g_CanvasInfo.layout.detail[i].TextLetterSpace=50;
                g_CanvasInfo.layout.detail[i].TextType=2;
			}
			else if(i==1)
			{
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "company");
                g_CanvasInfo.layout.detail[i].ElePointX=0;
                g_CanvasInfo.layout.detail[i].ElePointY=0;
                g_CanvasInfo.layout.detail[i].EleWidth=1024;
                g_CanvasInfo.layout.detail[i].EleHeight=80;
                g_CanvasInfo.layout.detail[i].TextSize=80;
                strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
                g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                g_CanvasInfo.layout.detail[i].TextType=0;
			}
			else if(i==2)
			{
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "duty");
                g_CanvasInfo.layout.detail[i].ElePointX=0;
                g_CanvasInfo.layout.detail[i].ElePointY=500;
                g_CanvasInfo.layout.detail[i].EleWidth=1024;
                g_CanvasInfo.layout.detail[i].EleHeight=100;
                g_CanvasInfo.layout.detail[i].TextSize=80;
                strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                g_CanvasInfo.layout.detail[i].HorizontalAlign=3;
                g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                g_CanvasInfo.layout.detail[i].TextType=0;
			}
            else if(i==3)
            {
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "other");
                g_CanvasInfo.layout.detail[i].ElePointX=0;
                g_CanvasInfo.layout.detail[i].ElePointY=500;
                g_CanvasInfo.layout.detail[i].EleWidth=1024;
                g_CanvasInfo.layout.detail[i].EleHeight=100;
                g_CanvasInfo.layout.detail[i].TextSize=80;
                strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
                g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                g_CanvasInfo.layout.detail[i].TextType=0;
            }

		}
        //update_flag=1;
        msg_apps_t msg;
        memset(&msg,0,sizeof(msg_apps_t));
        msg.type = MSG_UPDATE_CANVAS;
        SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
        return 0;
    }
    array_total = cJSON_GetArraySize(detail);
    //LV_LOG_USER("array_total = %d",array_total);
    for(int i=0;i<array_total;i++)
    {
        detail_array = cJSON_GetArrayItem(detail, i);
        if (!detail_array)
        {
            LV_LOG_USER("detail_array is NULL");
            for(int i=0;i<MAX_DETAIL_NUM;i++)
			{
				if(i==0)
				{
                    strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "username");
                    g_CanvasInfo.layout.detail[i].ElePointX=0;
                    g_CanvasInfo.layout.detail[i].ElePointY=200;
                    g_CanvasInfo.layout.detail[i].EleWidth=1024;
                    g_CanvasInfo.layout.detail[i].EleHeight=200;
                    g_CanvasInfo.layout.detail[i].TextSize=200;
                    strcpy(g_CanvasInfo.layout.detail[i].TextColor, "fac000");
                    strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                    g_CanvasInfo.layout.detail[i].HorizontalAlign=2;
                    g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                    g_CanvasInfo.layout.detail[i].TextLetterSpace=50;
                    g_CanvasInfo.layout.detail[i].TextType=2;
				}
				else if(i==1)
				{
                    strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "company");
                    g_CanvasInfo.layout.detail[i].ElePointX=0;
                    g_CanvasInfo.layout.detail[i].ElePointY=0;
                    g_CanvasInfo.layout.detail[i].EleWidth=1024;
                    g_CanvasInfo.layout.detail[i].EleHeight=80;
                    g_CanvasInfo.layout.detail[i].TextSize=80;
                    strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                    strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                    g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
                    g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                    g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                    g_CanvasInfo.layout.detail[i].TextType=0;
				}
				else if(i==2)
				{
                    strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "duty");
                    g_CanvasInfo.layout.detail[i].ElePointX=0;
                    g_CanvasInfo.layout.detail[i].ElePointY=500;
                    g_CanvasInfo.layout.detail[i].EleWidth=1024;
                    g_CanvasInfo.layout.detail[i].EleHeight=100;
                    g_CanvasInfo.layout.detail[i].TextSize=80;
                    strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                    strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                    g_CanvasInfo.layout.detail[i].HorizontalAlign=3;
                    g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                    g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                    g_CanvasInfo.layout.detail[i].TextType=0;
				}
                else if(i==3)
                {
                    strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "other");
                    g_CanvasInfo.layout.detail[i].ElePointX=0;
                    g_CanvasInfo.layout.detail[i].ElePointY=500;
                    g_CanvasInfo.layout.detail[i].EleWidth=1024;
                    g_CanvasInfo.layout.detail[i].EleHeight=100;
                    g_CanvasInfo.layout.detail[i].TextSize=80;
                    strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                    strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                    g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
                    g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                    g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                    g_CanvasInfo.layout.detail[i].TextType=0;
                }
			}
            //update_flag=1;
            msg_apps_t msg;
            memset(&msg,0,sizeof(msg_apps_t));
            msg.type = MSG_UPDATE_CANVAS;
            SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
            return 0;
        }
        item = cJSON_GetObjectItem(detail_array, "ElementNo");
        if (item&&item->type==cJSON_String)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(detail_array, "ElePointX");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].ElePointX=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "ElePointY");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].ElePointY=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "EleWidth");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].EleWidth=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "EleHeight");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].EleHeight=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "TextSize");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].TextSize=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "TextColor");
        if (item&&item->type==cJSON_String)
        {
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(detail_array, "TextFont");
        if (item&&item->type==cJSON_String)
        {
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(detail_array, "HorizontalAlign");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].HorizontalAlign=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "TextLineSpace");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].TextLineSpace=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "TextLetterSpace");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].TextLetterSpace=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "TextType");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].TextType=item->valueint;
        }
    }
    LV_LOG_USER("parse success");
    //update_flag=1;
    msg_apps_t msg;
    memset(&msg,0,sizeof(msg_apps_t));
    msg.type = MSG_UPDATE_CANVAS;
    SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
    return 0;
}

void httpserver::http_service_register(void)
{
    service.POST("/eboard/control", [](HttpRequest* req, HttpResponse* resp) {
        resp->content_type = req->content_type;
        resp->content_length = req->content_length;
        resp->body = req->body;
        if(resp->content_type ==MULTIPART_FORM_DATA)
        {
            std::string type =  req->GetFormData("Type");
            if(!type.empty())
            {
                LV_LOG_USER("type = %s",type.c_str());
                if(strcmp(type.c_str(),"cmd")==0)
                {
                    std::string cmd = req->GetFormData("Cmd");
                    if(!cmd.empty())
                    {
                        if(strcmp(cmd.c_str(),"休眠")==0)
                        {
                            msg_apps_t cmd_msg;
                            memset(&cmd_msg,0,sizeof(msg_apps_t));
                            cmd_msg.type = MSG_STANDBY;
                            SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &cmd_msg);
                            return resp->String(RespJsontoString(true));
                        }
                        else if(strcmp(cmd.c_str(),"唤醒")==0){
                            msg_apps_t cmd_msg;
                            memset(&cmd_msg,0,sizeof(msg_apps_t));
                            cmd_msg.type = MSG_RESUME;
                            SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &cmd_msg);
                            return resp->String(RespJsontoString(true));
                        }
                        else
                        {
                            return resp->String(RespJsontoString(false));
                        }
                    }
                    else {
                        return resp->String(RespJsontoString(false));
                    }
                }
                else if(strcmp(type.c_str(),"image")==0)
                {
                    int ret = req->SaveFormFile("Image",IDCARD_PATH);
                    system("sync");
                    if(ret == 200)
                    {
                        msg_apps_t msg;
                        memset(&msg,0,sizeof(msg_apps_t));
                        msg.type = MSG_UPDATE_IDCARD;
                        SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
                        return resp->String(RespJsontoString(true));
                    }
                    else
                    {
                        return resp->String(RespJsontoString(false));
                    }
                }
                else if(strcmp(type.c_str(),"temp")==0)
                {
                    int ret = req->SaveFormFile("Temp",TEMP_PATH);
                    system("sync");
                    if(ret == 200)
                    {
                        msg_apps_t msg;
                        memset(&msg,0,sizeof(msg_apps_t));
                        msg.type = MSG_ADD_TEMP;
                        SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
                        return resp->String(RespJsontoString(true));
                    }
                    else
                    {
                        return resp->String(RespJsontoString(false));
                    }
                }
                else
                {
                    return resp->String(RespJsontoString(false));
                }
            }
            else
            {
                return resp->String(RespJsontoString(false));
            }
        }
        else if(resp->content_type ==APPLICATION_JSON)
        {
            if(ReqStringtoJsonParse(resp->body)==0)
            {
                return resp->String(RespJsontoString(true));
            }
            else
            {
                return resp->String(RespJsontoString(false));
            }
        }
        else
        {
            return resp->String(RespJsontoString(false));
        }

    });
}

void httpserver::zp_param_initial(void)
{
    memset(&g_CanvasInfo,0,sizeof(zpc_canvas_param_t));
    g_CanvasInfo.clear_flag = 0;
    strcpy(g_CanvasInfo.username, "姓名");
    strcpy(g_CanvasInfo.company, "单位");
    strcpy(g_CanvasInfo.duty, "职务");
    strcpy(g_CanvasInfo.other, "");

    strcpy(g_CanvasInfo.layout.BgColor, "FF0000");
    strcpy(g_CanvasInfo.layout.BgImg, "");
    for(int i=0;i<MAX_DETAIL_NUM;i++)
    {
        if(i==0)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "username");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=200;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=200;
            g_CanvasInfo.layout.detail[i].TextSize=200;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "fac000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=2;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=50;
            g_CanvasInfo.layout.detail[i].TextType=2;
        }
        else if(i==1)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "company");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=0;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=80;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
        else if(i==2)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "duty");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=500;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=100;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=3;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
        else if(i==3)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "other");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=500;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=100;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
    }
}

#endif
