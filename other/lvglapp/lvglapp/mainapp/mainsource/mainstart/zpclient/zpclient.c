/*
 * zpclient.c
 *
 *  Created on: 2021年06月28日
 *      Author: CareyZeng
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/bitypes.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <netdb.h>
#include <stdbool.h>
#include <strings.h>
#include <sys/types.h>

#include "applib.h"
#include "app_config.h"
#include "urdevhotplug.h"

#include "list.h"
#include "cJSON.h"
#include "zpclient.h"
#include "packet.h"
#include "dl_service.h"
#include "networkpolicy.h"

#define ZPC_INFO(fmt, arg...) printf("[ZPC-INFO]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)
#define ZPC_ERR(fmt, arg...) printf("[ZPC-ERROR]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)

typedef struct
{
        list_t callbackList;
        ZPCServerCallback pfnCallback;
}ZPCServerCallbackListData_t;

typedef struct
{
        struct list_head list;
        zpc_msg_t msg;
        int flag;
}msg_list_t;

typedef struct{
        pthread_t MsgProc_tid;
        pthread_mutex_t MsgProcLock;
        pthread_cond_t MsgProcCondition;
        pthread_mutex_t MsgProcDataLock;
        msg_list_t Msg_list;
        char MsgProc_start;
        int msg_total;
        int proc_num;
}zpc_msg_proc_t;

typedef struct{
        pthread_t tid;
        pthread_mutex_t Lock;
        pthread_cond_t Condition;
        pthread_mutex_t DataLock;
        int ThreadRun;
        int FoundServer;
        char ServerIp[20];
        char ServerPort[8];
}zpc_discovery_t;

#define ZPC_SETTING_CFG		"/customer/ZPCSetting.cfg"
#define SYSTEM_DIR			"/customer/res/ui/"

static int g_registerZPCServerChanged = 0;
static pthread_t g_ZPCServerThread = 0;
static int g_ZPCServerThreadRun = 0;
static int discover = 0;

static list_t g_ZPCServerCallbackListHead;
static pthread_mutex_t g_ZPCServerCallbackListMutex;
static pthread_mutex_t g_ZPCServerParamMutex;
zpc_param_t g_zpcInfo;
dl_result_t dlresult;
cJSON * g_zpcRoot=NULL;
cJSON * g_zpcMeeting=NULL;
cJSON * g_zpcClient=NULL;

static int g_ZPCMsgProcThreadRun = 0;
static zpc_msg_proc_t g_zpcMsg;

#define RECONNED_WAIT_TIME				10
#define HB_LOOP_TIME				1000	//MS
#define HB_CONFIRM_CNT				10
#ifdef	USE_PRIVATE_TRANSMIT_PIC
char packet_data[CLIENT_RECV_PIC_BUFSIZE];
#else
char packet_data[CLIENT_RECV_BUFSIZE];
#endif
int heartbeat_keepAlive = 1;
long long hb_send_start_time=0;
int hb_send_cnt = 0;
static int client_pthread_exit_flag=0;
static int client_reconnect_flag=0;
bool download_busy=false;
bool link_server_waiting=false;
struct timeval tval={0,800000};
fd_set rset,wset;
int zpc_sockfd =-1;
char server_time[16]={0};//20160719170059

vote_info_t vote_data;

long long hb_send_start_time;

static int backlightpro;
static int deskid_dlid;
static int agenda_dlid;
static int content_dlid;

zpc_discovery_t g_discover;

int createZPDefaultConfig()
{
        FILE* fp = NULL;
        cJSON * root;
        cJSON * obj;
        cJSON * item;

        fp = fopen(ZPC_SETTING_CFG,"w+");
        if (!fp)
        {
                printf("should open json file first\n");
                return -1;
        }
        printf("create %s success\n", ZPC_SETTING_CFG);
        memset(g_zpcInfo.meeting_theme, 0, sizeof(g_zpcInfo.meeting_theme));
        //strcat(g_zpcInfo.meeting_theme, "");

        memset(g_zpcInfo.company, 0, sizeof(g_zpcInfo.company));
        //strcat(g_zpcInfo.company, "Company name");

        memset(g_zpcInfo.participant, 0, sizeof(g_zpcInfo.participant));
        //strcat(g_zpcInfo.participant, "Participant name");

        memset(g_zpcInfo.person_title, 0, sizeof(g_zpcInfo.person_title));
        //strcat(g_zpcInfo.person_title, "Participant position");

        memset(g_zpcInfo.version_content, 0, sizeof(g_zpcInfo.version_content));
        //strcat(g_zpcInfo.version_content, "Meeting theme");

        memset(g_zpcInfo.version_agenda, 0, sizeof(g_zpcInfo.version_agenda));
        //strcat(g_zpcInfo.version_agenda, "Meeting theme");

        memset(g_zpcInfo.sign_time, 0, sizeof(g_zpcInfo.sign_time));
        strcat(g_zpcInfo.sign_time, "0000-00-00 00:00:00");

        memset(g_zpcInfo.deskid, 0, sizeof(g_zpcInfo.deskid));
        strcat(g_zpcInfo.deskid, "001");

        memset(g_zpcInfo.server_dn, 0, sizeof(g_zpcInfo.server_dn));
        strcat(g_zpcInfo.server_dn, "www.dianzizhuopai.com");

    #if SERVER_IP_SEL == 0
	memset(g_zpcInfo.server_ip, 0, sizeof(g_zpcInfo.server_ip));
	strcat(g_zpcInfo.server_ip, "47.96.137.187");

	#elif SERVER_IP_SEL == 1
	memset(g_zpcInfo.server_ip, 0, sizeof(g_zpcInfo.server_ip));
	strcat(g_zpcInfo.server_ip, "47.110.35.20");

	#elif SERVER_IP_SEL == 2
	memset(g_zpcInfo.server_ip, 0, sizeof(g_zpcInfo.server_ip));
	strcat(g_zpcInfo.server_ip, "219.138.120.250");
	#endif
	memset(g_zpcInfo.server_lan_ip, 0, sizeof(g_zpcInfo.server_lan_ip));
	strcat(g_zpcInfo.server_lan_ip, "192.168.0.0");
        g_zpcInfo.port = 9994;
	g_zpcInfo.server_type = 0;
	g_zpcInfo.agenda_total = 0;
	g_zpcInfo.content_total = 0;

        root = cJSON_CreateObject();
        obj = cJSON_CreateObjectToObject(root, "meeting");
        cJSON_AddStringToObject(obj, "theme", g_zpcInfo.meeting_theme);
        cJSON_AddStringToObject(obj, "company", g_zpcInfo.company);
        cJSON_AddStringToObject(obj, "participant", g_zpcInfo.participant);
        cJSON_AddStringToObject(obj, "person_title", g_zpcInfo.person_title);
        cJSON_AddStringToObject(obj, "version_content", g_zpcInfo.version_content);
        cJSON_AddStringToObject(obj, "version_agenda", g_zpcInfo.version_agenda);
        cJSON_AddStringToObject(obj, "sign_time", g_zpcInfo.sign_time);
        cJSON_AddStringToObject(obj, "deskid", g_zpcInfo.deskid);
        cJSON_AddNumberToObject(obj, "content_total", g_zpcInfo.content_total);
        cJSON_AddNumberToObject(obj, "agenda_total", g_zpcInfo.agenda_total);

        obj = cJSON_CreateObjectToObject(root, "client");
        cJSON_AddStringToObject(obj, "server_dn", g_zpcInfo.server_dn);
        cJSON_AddStringToObject(obj, "server_ip", g_zpcInfo.server_ip);
        cJSON_AddStringToObject(obj, "server_lan_ip", g_zpcInfo.server_lan_ip);
        cJSON_AddNumberToObject(obj, "port", g_zpcInfo.port);
        cJSON_AddNumberToObject(obj, "server_type", g_zpcInfo.server_type);

        fseek(fp, 0, SEEK_SET);
        fwrite(cJSON_Print(root),strlen(cJSON_Print(root)),1,fp);
        cJSON_Delete(root);
        fclose(fp);
        fp = NULL;

        return 0;
}
int saveZPCConfig()
{
        FILE* fp = NULL;
        cJSON * root;
        cJSON * obj;
        cJSON * item;

        fp = fopen(ZPC_SETTING_CFG,"w+");
        if (!fp)
        {
                printf("should open json file first\n");
                return -1;
        }

        if(g_zpcRoot)
        {
                fseek(fp, 0, SEEK_SET);
                fwrite(cJSON_Print(g_zpcRoot),strlen(cJSON_Print(g_zpcRoot)),1,fp);
                //cJSON_Delete(g_zpcRoot);
                //g_zpcRoot = NULL;
        }
        else
        {
                ZPC_ERR("Never run here");
        }

        fclose(fp);
        fp = NULL;
        return 0;
}

int initZPCConfig()
{
        FILE* fp = NULL;
        long long len = 0;
        char * pConfData = NULL;
        int ret = -1;
        cJSON_Hooks hooks;
        cJSON * item;

        // check json config valid
        fp = fopen(ZPC_SETTING_CFG,"r+");
        if (!fp)
        {
                createZPDefaultConfig();
        }
        else
        {
                int isBlank = 0;
                getc(fp);

                if (feof(fp))
                        isBlank = 1;

                fclose(fp);
                fp = NULL;

                if (isBlank)
                        createZPDefaultConfig();
        }

        // read config param
        fp = fopen(ZPC_SETTING_CFG,"r+");
        if (!fp)
        {
                printf("should open json file first\n");
                return -1;
        }

        printf("open %s success\n", ZPC_SETTING_CFG);

        hooks.free_fn = free;
        hooks.malloc_fn = malloc;
        cJSON_InitHooks(&hooks);

        fseek(fp, 0, SEEK_END);
        len = ftell(fp);
        pConfData = (char *)malloc(len + 1);
        fseek(fp, 0, SEEK_SET);
        fread(pConfData, len, 1, fp);
        fclose(fp);
        fp = NULL;

        // read config
        cJSON_Minify(pConfData);
        g_zpcRoot = cJSON_Parse(pConfData);
        if (!g_zpcRoot)
        {
                printf("parse failed\n");
                goto exit;
        }

        g_zpcMeeting = cJSON_GetObjectItem(g_zpcRoot, "meeting");
        if (!g_zpcMeeting)
        {
                printf("Get object item meeting failed\n");
                goto exit;
        }

        printf("%s parse json success\n", __func__);
        item = cJSON_GetObjectItem(g_zpcMeeting, "theme");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.meeting_theme, cJSON_GetStringValue(item));
        }

        item = cJSON_GetObjectItem(g_zpcMeeting, "company");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.company, cJSON_GetStringValue(item));
        }

        item = cJSON_GetObjectItem(g_zpcMeeting, "participant");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.participant, cJSON_GetStringValue(item));
        }

        item = cJSON_GetObjectItem(g_zpcMeeting, "person_title");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.person_title, cJSON_GetStringValue(item));
        }

        item = cJSON_GetObjectItem(g_zpcMeeting, "version_content");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.version_content, cJSON_GetStringValue(item));
        }

        item = cJSON_GetObjectItem(g_zpcMeeting, "version_agenda");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.version_agenda, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(g_zpcMeeting, "sign_time");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.sign_time, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(g_zpcMeeting, "deskid");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.deskid, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(g_zpcMeeting, "content_total");
        if (item&&item->type==cJSON_Number)
        {
                g_zpcInfo.content_total=item->valueint;
        }
        item = cJSON_GetObjectItem(g_zpcMeeting, "agenda_total");
        if (item&&item->type==cJSON_Number)
        {
                g_zpcInfo.agenda_total=item->valueint;
        }

        g_zpcClient = cJSON_GetObjectItem(g_zpcRoot, "client");
        if (!g_zpcClient)
        {
                printf("Get object item client failed\n");
                goto exit;
        }
        item = cJSON_GetObjectItem(g_zpcClient, "server_dn");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.server_dn, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(g_zpcClient, "server_ip");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.server_ip, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(g_zpcClient, "server_lan_ip");
        if (item&&item->type==cJSON_String)
        {
                strcpy(g_zpcInfo.server_lan_ip, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(g_zpcClient, "port");
        if (item&&item->type==cJSON_Number)
        {
                g_zpcInfo.port = item->valueint;
        }
        item = cJSON_GetObjectItem(g_zpcClient, "server_type");
        if (item&&item->type==cJSON_Number)
        {
                g_zpcInfo.server_type = item->valueint;
        }

exit:
        if (pConfData)
                free(pConfData);

        return ret;
}

int DeinitZPCConfig()
{
        if (g_zpcRoot!=NULL)
        {
                cJSON_Delete(g_zpcRoot);
                g_zpcRoot = NULL;
                g_zpcMeeting = NULL;
                g_zpcClient = NULL;
        }
        return 0;
}

int updateZpcConfigString(cJSON *pobj, char *name, char *str)
{
        cJSON * item;

        if (!pobj)
        {
                ZPC_ERR("parent obj is null");
                return -1;
        }
        if (!name)
        {
                ZPC_ERR("name is null");
                return -1;
        }
        if (!str)
        {
                ZPC_ERR("str is null");
                return -1;
        }
        item = cJSON_CreateString(str);
        cJSON_ReplaceItemInObject(pobj, name, item);

        return 0;
}

int updateZpcConfigNumber(cJSON *pobj, char *name, int val)
{
        cJSON * item;

        if (!pobj)
        {
                ZPC_ERR("parent obj is null");
                return -1;
        }
        if (!name)
        {
                ZPC_ERR("name is null");
                return -1;
        }

        item = cJSON_CreateNumber(val);
        cJSON_ReplaceItemInObject(pobj, name, item);

        return 0;
}

long long get_ab_timer()
{
    struct timeval tv;
    long long tv_sec =0;
    long long tv_usec =0;

    gettimeofday(&tv, NULL);
    tv_sec =(long long)tv.tv_sec;
    tv_sec = (long long)(tv_sec*1000);
    tv_usec = (long long)tv.tv_usec;
    tv_usec = (long long)(tv_usec / 1000);
    tv_sec = (long long)(tv_sec + tv_usec);
    return tv_sec;
}
#if 0
unsigned int parse_file_list(FtpFile *ftpfile_list, playlist_t* list)
{
        unsigned char *pbuf=NULL;
        unsigned char *buf;
        unsigned int ret=0,i=0,j=0;
        unsigned int buf_size=0,file_size=0;
        FILE *fp=0;
        unsigned char *path;
        unsigned char file_parse[1024];
        int offset_r=0;//读文件操作指针偏移值
        bool CR_LF_separate=false;

        if(content_dl_broken == true && list->total!=0 && list==&ftpfile_content)
                return list->total;

        if(agenda_dl_broken == true && list->total!=0 && list==&ftpfile_agenda)
                return list->total;

        if(list->total!=0)
                filelist_remove_all_items(list);

        path = (unsigned char *)malloc(MAX_PATH_LENGTH);
        if(path==NULL)
        {
                ZPC_ERR("malloc failed!");
                return 0;
        }
        memset(path,0,MAX_PATH_LENGTH);

        buf = (unsigned char *)malloc(TXT_READ_SIZE_ONCE+1);
        if(buf==NULL)
        {
                ZPC_ERR("malloc failed!");
                goto parse_finish;
        }
        memset(buf,0,TXT_READ_SIZE_ONCE+1);

        memset(file_parse,0,1024);
        sprintf(file_parse,"%s/%s",SYSTEM_DIR,ftpfile_list->filename);
        fp = fopen(file_parse,"rb");
        if(fp==0)
                ZPC_ERR("%s open error!\n",file_parse);
        else
        {
                fseek(fp,0,SEEK_END);
                file_size = ftell(fp);
                fseek(fp,0,SEEK_SET);
                fclose(fp);
                fp = NULL;

                if(file_size<=0)
                        goto parse_finish;

                if(file_size>TXT_READ_SIZE_ONCE)
                {
                        buf_size = TXT_READ_SIZE_ONCE;
                }
                else
                {
                        buf_size = file_size;
                }

                list->total=0;
                list->current=0;

                j = 0;
                offset_r = 0;
                while(file_size)
                {
                        fp = fopen(file_parse,"rb");
                        if(fp==0)
                        {
                                ZPC_ERR("%s open error!\n",file_parse);
                                goto parse_finish;
                        }
                        memset(buf,0,TXT_READ_SIZE_ONCE+1);

                        fseek(fp,offset_r,SEEK_SET);
                        ret = fread(buf,1,buf_size,fp);
                        offset_r += ret;	//offset_r += buf_size;
                        fclose(fp);
                        fp = NULL;

                        pbuf = buf;
//ZPC_INFO("%s\n",buf);
                        if(pbuf[buf_size-1]=='\r')//本次刚好把 \r 读到buf尾，下一循环读到的buf将会以\n开始，会错过一条记录所以需要特别处理
                                CR_LF_separate = true;
                        else
                                CR_LF_separate = false;

                        for(i=0; i<buf_size; i++)
                        {
                                if(*pbuf=='\0')
                                {
                                        //ZPC_INFO("file read end");
                                        break;
                                }
                                if(*pbuf=='\r' && *(pbuf+1)=='\n')
                                {
                                        ret=filelist_insert_item(list, list->total, path);
                                        if(ret==false)
                                                goto parse_finish;
                                        if(list->total >= LIST_RECORD_NUM_MAX)
                                                goto parse_finish;

                                        pbuf +=2;
                                        j=0;
                                        memset(path,0,MAX_PATH_LENGTH);
                                        continue;
                                }

                                if(i==0 && *pbuf=='\n'&& CR_LF_separate==true)
                                {
                                        CR_LF_separate = false;
                                        ret=filelist_insert_item(list, list->total, path);
                                        if(ret==false)
                                                goto parse_finish;
                                        if(list->total >= LIST_RECORD_NUM_MAX)
                                                goto parse_finish;

                                        pbuf ++;
                                        j=0;
                                        memset(path,0,MAX_PATH_LENGTH);
                                        continue;
                                }

                                path[j] = *pbuf;
                                pbuf++;
                                if(j < MAX_PATH_LENGTH-1)	j++;

                        }

                        file_size -=buf_size;
                        if(file_size>TXT_READ_SIZE_ONCE)
                        {
                                buf_size = TXT_READ_SIZE_ONCE;
                        }
                        else
                        {
                                buf_size = file_size;
                        }
                }

        }
parse_finish:
        if(buf!=NULL)
        {
                free(buf);
                buf = NULL;
        }
        if(path!=NULL)
        {
                free(path);
                path = NULL;
        }
        if(fp)
        {
                fclose(fp);
                fp = NULL;
        }

        return list->total;
}

unsigned int check_file_version(FtpFile *list_file, char *ver_info)
{
        char *pbuf=NULL;
        char *buf=NULL;
        unsigned int ret=0,i=0,j=0;
        unsigned int buf_size=0,file_size=0;
        FILE *fp=0;
        char file_parse[1024];
        int read_buf_size=VER_MAX_LENGTH*2;

        if(ver_info==NULL)
        {
                ZPC_ERR("malloc failed!");
                return 0;
        }
        buf = (char *)malloc(read_buf_size);
        if(buf==NULL)
        {
                ZPC_ERR("malloc failed!");
                goto parse_finish;
        }
        memset(buf,0,read_buf_size);
        memset(file_parse,0,1024);
        sprintf(file_parse,"%s/%s",SYSTEM_DIR,list_file->filename);
        fp = fopen(file_parse,"rb");
        if(fp==0)
        {
                ZPC_ERR("%s open error!\n",file_parse);
        }
        else
        {
                fseek(fp,0,SEEK_END);
                file_size = ftell(fp);
                fseek(fp,0,SEEK_SET);
                fclose(fp);
                fp = NULL;
                if(file_size<=0)
                        goto parse_finish;

                j = 0;
                fp = fopen(file_parse,"rb");
                if(fp==0)
                {
                        ZPC_ERR("%s open error!\n",file_parse);
                        goto parse_finish;
                }

                buf_size = fread(buf,1,read_buf_size,fp);
                fclose(fp);
                fp = NULL;

                pbuf = buf;
                for(i=0; i<buf_size; i++)
                {
                        if(*pbuf=='\0')
                        {
                                //ZPC_INFO("file read end");
                                break;
                        }
                        if(*pbuf=='\r' && *(pbuf+1)=='\n') //只解析第一行
                        {
                                break;
                        }

                        ver_info[j] = *pbuf;
                        pbuf++;
                        if(j < VER_MAX_LENGTH-1)
                                j++;
                        else
                                break;
                }
        }

parse_finish:
        if(buf!=NULL)
        {
                free(buf);
                buf = NULL;
        }
        if(fp)
        {
                fclose(fp);
                fp = NULL;
        }

        return 1;
}
#endif
void remove_download_content_data()
{
        ZPC_INFO();
        system("rm /mnt/udisk/Content -rf");
        //system("rm /mnt/udisk/meeting_content_list.txt -rf");//不能放在这里删除!!!
}
void remove_download_agenda_data()
{
        ZPC_INFO();
        system("rm /mnt/udisk/Agenda -rf");
        //system("rm /mnt/udisk/meeting_agenda_list.txt -rf");//不能放在这里删除!!!
}
void remove_download_meeting_data()
{
        ZPC_INFO();
        remove_download_content_data();
        remove_download_agenda_data();
        system("rm /mnt/udisk/meeting_database.bin -rf");
        system("rm /mnt/udisk/meeting_content_list.txt -rf");
        system("rm /mnt/udisk/meeting_agenda_list.txt -rf");
}

void remove_download_desktop_card()
{
        ZPC_INFO();
        system("rm /mnt/udisk/BusinessCard -rf");
}

void remove_download_vote_result()
{
        ZPC_INFO();
        system("rm /mnt/udisk/VoteResult -rf");
        g_zpcInfo.ticked_result = false;
}
void delete_other_data()
{
        ZPC_INFO();

        //free_all_message();

        memset(g_zpcInfo.meeting_theme,0,MAX_DATA_LENGTH);
        memset(g_zpcInfo.company,0,MAX_DATA_LENGTH);
        memset(g_zpcInfo.participant,0,MAX_DATA_LENGTH);
        memset(g_zpcInfo.person_title,0,MAX_DATA_LENGTH);
        memset(g_zpcInfo.version_content,0,VER_MAX_LENGTH);
        memset(g_zpcInfo.version_agenda,0,VER_MAX_LENGTH);
        //content_dl_broken = false;
        //agenda_dl_broken = false;

        g_zpcInfo.ticked_status =  false;
        g_zpcInfo.ticked_service = false;
        g_zpcInfo.ticked_result = false;
}

char * meeting_agenda_dir()
{
        static char agenda_dir[200]={0};

#ifdef SELF_TRANSMIT_PIC
        rtc_date_t  date;
        rtc_time_t	time;
        unsigned char str_date[10];

        sys_get_rtc_date_time( &time, &date );
        sprintf(str_date,"%d%02d%02d",date.year,date.month,date.day);
        sprintf(agenda_dir,SYSTEM_DIR"%s/agenda/",str_date);
#else
        //sprintf(str_date,"%d%02d%02d",date.year,date.month,date.day);
        //sprintf(agenda_dir,SYSTEM_DIR"%s%s",str_date,"Agenda/Pictrue/");
        sprintf(agenda_dir,SYSTEM_DIR"%s","agenda/");
#endif

        return agenda_dir;
}

char *deskcard_dir()
{
        static char deskid_dir[200]={0};
#ifdef SELF_TRANSMIT_PIC
        rtc_date_t	date;
        rtc_time_t	time;

        char str_date[10];
        sys_get_rtc_date_time( &time, &date );
        sprintf(str_date,"%d%02d%02d%02d",date.year,date.month,date.day,time.hour);
        sprintf(deskid_dir,SYSTEM_DIR"%s/idcard/",str_date);
#else
        sprintf(deskid_dir,SYSTEM_DIR"%s","idcard/");
#endif
        return deskid_dir;
}

char * meeting_content_dir()
{
        static char content_dir[200]={0};

#ifdef SELF_TRANSMIT_PIC
        rtc_date_t	date;
        rtc_time_t	time;
        char str_date[10];

        sys_get_rtc_date_time( &time, &date );

        sprintf(str_date,"%d%02d%02d",date.year,date.month,date.day);
        sprintf(content_dir,SYSTEM_DIR"%s/content/",str_date);
#else
        //sprintf(str_date,"%d%02d%02d",date.year,date.month,date.day);
        //sprintf(content_dir,SYSTEM_DIR"%s%s",str_date,"Content/Pictrue/");
        sprintf(content_dir,SYSTEM_DIR"%s","content/");
#endif
        return content_dir;
}
static void mkdirs(char *dir)
{
    char tmp[1024];
    char *p;
    int32_t len;

    p = dir;
    while(p != NULL)
    {
        p = strchr(p+1, '/');
        if(p == NULL)
            break;

        len = p - dir;
        strncpy(tmp, dir, len);
        tmp[len] = 0;

        mkdir(tmp, 0777);
    }
}
void meetting_mkdirs( )
{
        mkdirs(deskcard_dir());
        mkdirs(meeting_content_dir());
        mkdirs(meeting_agenda_dir());
}


bool is_network_connected(void)
{
        NetConfig_t wire_info;
        int eth_sta=-1;
        int wlan_sta=-1;

        //get ethernet status,-1=unknown,0=plugout,1=plugin
        NetPolicyGetEthStatus(&eth_sta);
        //get wireless status,-1=unknown,0=disconnected,1=connected
        NetPolicyGetWlanStatus(&wlan_sta);
        if(eth_sta==1||wlan_sta==1)
        {
                memset(wire_info.mac, 0, sizeof(wire_info.mac));
                NetPolicyGetEthConfig(&wire_info);
                if(strcmp(wire_info.mac, "00:00:00:00:00:00")==0||strlen(wire_info.mac)==0)
                        return false;
                else
                {
                        memset(g_zpcInfo.hwinfo.mac, 0, sizeof(g_zpcInfo.hwinfo.mac));
                        memcpy(g_zpcInfo.hwinfo.mac, wire_info.mac, strlen(wire_info.mac));
                        return true;
                }
        }
        else
                return false;
}
//确认桌牌号是否可以用
//可以返回 1  否则返回0,网络错误返回-1.
int wait_confirm_deskid(char *buf, unsigned int len)
{
        int retrys = 3;
        int ret,type;
        unsigned int read_len;
        unsigned char packet_num, packet_id;

        while(retrys)
        {
                retrys--;
                //发送桌牌号
                ret = write_data(DP_TYPE_SN, buf, len);
                if(ret!=1)
                {
                        ZPC_ERR("[confirm deskid] send failed");
                        return 0;
                }

                memset(packet_data, 0, CLIENT_RECV_BUFSIZE);
                ret = read_data(&type, &packet_num, &packet_id, packet_data, &read_len);
                if(ret < 0)
                {
                        return ret;
                }
                else if(ret == 0)
                {
                        ZPC_INFO("ret=%d; 0=no data, -1=net error -2=checksum error", ret);
                        sleep(1);
                        continue;
                }

                ZPC_INFO("wait confirm deskid: read_len=%d packet_data=%s",read_len, packet_data);
                if(type == DP_TYPE_SN)
                {
                    if(strcmp(packet_data,g_zpcInfo.deskid)==0)
                    {
                        return 1;
                    }
                    else
                    {
						if(read_len>0)
						{
							memset(g_zpcInfo.deskid,0,sizeof(g_zpcInfo.deskid));
							memcpy(g_zpcInfo.deskid,packet_data,sizeof (g_zpcInfo.deskid));
							#if (QTSIM_PLATFORM==0)
							zpc_msg_t msg;
							msg.type = ZPC_MSG_UPDATE_ID;
							msg.data_len = strlen(g_zpcInfo.deskid);
							memset(msg.data_buf, 0, sizeof(msg.data_buf));
							strncpy(msg.data_buf,g_zpcInfo.deskid,msg.data_len);
							SSTAR_ZPCMsg(&msg);
							#endif
							return 0;
						}
                    }
                }
        }

        return 0;
}
void update_curl_severip(const unsigned char *new_ip)
{

}

int send_heartbeat(void)
{
        int ret = 0;
        char buf[64];

        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%s|%s|%d|%d", g_zpcInfo.deskid, g_zpcInfo.hwinfo.mac,g_zpcInfo.battery,g_zpcInfo.status);
        ZPC_INFO("send heartbeat:[%s]", buf);
        ret = write_data(DP_TYPE_CMD_HEARTBEAT_PACKET_REQUEST, buf, strlen(buf));

        return ret;
}

//成功返回1，失败返回0，   网络错误返回-1
int send_deskid_to_server(char *deskid)
{
        int ret=0;

        ret = write_data(DP_TYPE_SN, deskid, strlen(deskid));
        return ret;
}

//成功返回1，失败返回0，   网络错误返回-1
int send_packet_to_server(unsigned char type, char *buf, unsigned int bufsize)
{
        int ret=0;
        ret = write_data(type, buf, bufsize);
        return ret;
}

void close_sockfd()
{
        if(zpc_sockfd > 0)
        {
                close(zpc_sockfd);
                zpc_sockfd = -1;
        }
}
//return -1  连接失败 0 连接成功
int client_init(char *server_ip, unsigned int server_port)
{
        int res,flags,error;
        int ret = -1;
        int fd = -1;
        struct sockaddr_in serv_addr;
        socklen_t len;

        ZPC_INFO("client configuration\n");

        zpc_sockfd = fd;

        tval.tv_sec = 0;
        tval.tv_usec= 800000;
        //创建socket描述符
        if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                ZPC_INFO("socket error\n");
                goto ERR_RET;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port=htons(server_port);
        serv_addr.sin_addr.s_addr=inet_addr(server_ip);
        bzero(&(serv_addr.sin_zero),8);

        ZPC_INFO("start connect server %s:%d\n", server_ip, server_port);
        res = connect(fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
        flags = fcntl(fd,F_GETFL,0);
        fcntl( fd ,F_SETFL,flags|O_NONBLOCK);//设置为非阻塞

        if( res < 0)//失败
        {
                ZPC_INFO("connect: errno=%d", errno);
                if(errno != EINPROGRESS)
                {
                        close(fd);
                        fd = 0;
                        goto ERR_RET;
                }
                else
                {
                        res = 0;
                }
        }

        sleep(2);// 等待连接完成

//清空读写fd集合
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        FD_SET(fd,&rset);
        wset = rset;

        //判断socket描述符是否可写
        if( ( res = select(fd+1, NULL, &wset, NULL,&tval) ) <= 0)
        {
                ZPC_ERR("select: errno=%d", errno);
                close(fd);
                fd = -1;
                goto ERR_RET;
        }
        else
        {
                len = sizeof(error);
                getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len);
                if(error)
                {
                        close(fd);
                        fd = -1;
                        fprintf(stderr, "Error in connection() %d - %s\n", error, strerror(error));
                        goto ERR_RET;
                }
        }

        ret = 0;
ERR_RET:
        zpc_sockfd = fd;

        //成功只有可读可写
        if(zpc_sockfd>0)
                ZPC_INFO("connect sucessed");
        else
                ZPC_INFO("connect failed");
        return ret;
}

ZPCServer_cbmsg_t *client_dp_parse(unsigned char packet_num, unsigned char packet_id, char* recvbuf, unsigned int recvsize, int type)
{
        unsigned int i,j;
        unsigned char content_idx=0, name_idx=0;
        FILE *fp;
        ZPCServer_cbmsg_t *ret=NULL;
        msg_apps_t msg;
        static unsigned char time_tmp[4];
        static unsigned char cnt=0;
        //PT_Message  new_message=NULL;
        int y,m,d;
        char buf[1024]={0};
        char *str1=NULL;

        if(recvbuf == NULL || recvsize <= 0)
                return NULL;
//	ZPC_INFO("recvsize=%d",recvsize);
        hb_send_cnt = 0;
        switch(type)
        {
                case DP_TYPE_CMD_UPDATE_CARD:
                {
                    char head_url[960];
                    char local_head_url[256];
                    char local_tail_url[128];
                    ZPC_INFO("DP_TYPE_CMD_UPDATE_CARD url: %s", recvbuf);
                    memset(head_url, 0, sizeof(head_url));

                    if(g_zpcInfo.deskid_flag!=2)
                    {
                        dl_msg_t dlmsg;
                        memset(&dlmsg, 0, sizeof(dl_msg_t));
                        memset(local_head_url, 0, sizeof(local_head_url));
                        memset(local_tail_url, 0, sizeof(local_tail_url));
                        if(g_zpcInfo.server_type == 0)
                        {
                            sprintf(local_head_url,"http://%s",g_zpcInfo.server_lan_ip);
                        }
                        else
                        {
                            sprintf(local_head_url,"http://%s",g_zpcInfo.server_ip);
                        }
                        memcpy(local_tail_url, recvbuf, strlen(recvbuf));
                        //ZPC_INFO("local_head_url:%s local_tail_url=%s", local_head_url, local_tail_url);
                        strcat(local_head_url,local_tail_url);
                        memcpy(head_url, local_head_url, strlen(local_head_url));
                        ZPC_INFO("Head url:%s", head_url);
                        dlmsg.type = DL_MSG_DL_URL;
                        dlmsg.data_len = strlen(head_url);
                        memcpy(dlmsg.data_buf, head_url, strlen(head_url));
                        memcpy(dlmsg.filename, "/customer/resource/image/idcard/idcard.bmp", strlen("/customer/resource/image/idcard/idcard.bmp"));
                        deskid_dlid = SSTAR_DLMsg(&dlmsg);
                        if(deskid_dlid>=0)
                                g_zpcInfo.deskid_flag = 2;
                        else
                        {
                                g_zpcInfo.deskid_flag = 0;
                                ZPC_INFO("Add download list failed");
                        }
                    }
                }
                break;
                case DP_TYPE_CMD_UPDATE_SN:
                {
                    ZPC_INFO("DP_TYPE_CMD_UPDATE_SN: %s",recvbuf);
                    #if (QTSIM_PLATFORM==0)
                    zpc_msg_t g_msg;
                    g_msg.type = ZPC_MSG_UPDATE_ID;
                    g_msg.data_len = strlen(recvbuf);
                    memset(g_msg.data_buf, 0, sizeof(g_msg.data_buf));
                    strncpy(g_msg.data_buf,recvbuf,g_msg.data_len);
                    SSTAR_ZPCMsg(&g_msg);
                    #endif
                }
                break;

                case DP_TYPE_CMD_UPDATE_BACKLIGHT:
                {
                        ZPC_INFO("DP_TYPE_CMD_UPDATE_BACKLIGHT: %s",recvbuf);
						char cmd[128];
						int backlight_value = atoi(recvbuf);
						ZPC_INFO("backlightpro = %d",backlight_value+1);
						if(backlight_value>=0 && backlight_value<=9)
						{
							memset(cmd,0,sizeof(cmd));
							sprintf(cmd,"echo %d > /sys/class/pwm/pwmchip0/pwm0/duty_cycle",(backlight_value+1)*10);
							system(cmd);
							usleep(10000);
							memset(cmd,0,sizeof(cmd));
							sprintf(cmd,"echo %d > /sys/class/pwm/pwmchip0/pwm1/duty_cycle",(backlight_value+1)*10);
							system(cmd);
							system("sync");
						}
                }
                break;

                case DP_TYPE_CMD_UPDATE_POWER_STATE:
                {
                        ZPC_INFO(" DP_TYPE_CMD_UPDATE_POWER_STATE");
                        ZPC_INFO("clear cmd = %x",recvbuf);
                        //0待机   1 唤醒
                        int sendret;
                        if(g_zpcInfo.status==2)
                        {
                                msg.type = MSG_STANDBY;
                                SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
                                g_zpcInfo.status=1;
                        }
                        else
                        {
                                msg.type = MSG_RESUME;
                                SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
                                g_zpcInfo.status=2;
                        }
                        sendret = send_heartbeat();
                        if(sendret<0)
                        {
                            client_reconnect_flag=1;
                        }
                }
                break;

                case DP_TYPE_CMD_CLEAR_INFO:
                {
                        ZPC_INFO("DP_TYPE_CMD_CLEAR_INFO: %s",recvbuf);
                        memset(&msg,0,sizeof(msg_apps_t));
                        msg.type = MSG_CLEAR_ALL_INFO;
                        SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
                }
                break;
                case DP_TYPE_CMD_UPDATE_TEMPLATE:
                {
                        ZPC_INFO("DP_TYPE_CMD_UPDATE_TEMPLATE: %s",recvbuf);
                        char head_url[960];
                        char local_head_url[256];
                        char local_tail_url[128];

                        memset(head_url, 0, sizeof(head_url));
                        if(g_zpcInfo.deskid_flag!=2)
                        {
                            dl_msg_t dlmsg;
                            memset(&dlmsg, 0, sizeof(dl_msg_t));
                            memset(local_head_url, 0, sizeof(local_head_url));
                            memset(local_tail_url, 0, sizeof(local_tail_url));
                            if(g_zpcInfo.server_type == 0)
                            {
                                sprintf(local_head_url,"http://%s",g_zpcInfo.server_lan_ip);
                            }
                            else
                            {
                                sprintf(local_head_url,"http://%s",g_zpcInfo.server_ip);
                            }
                            memcpy(local_tail_url, recvbuf, strlen(recvbuf));
                            //ZPC_INFO("local_head_url:%s local_tail_url=%s", local_head_url, local_tail_url);
                            strcat(local_head_url,local_tail_url);
                            memcpy(head_url, local_head_url, strlen(local_head_url));
                            ZPC_INFO("Head url:%s", head_url);
                            msg_apps_t msg;
                            msg.type = MSG_UPDATE_TEMPLATE;
                            msg.csize = strlen(head_url);
                            memset(msg.content, 0, sizeof(msg.content));
                            memcpy(msg.content, head_url, msg.csize);
                            SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
                        }
                }
                break;
                case DP_TYPE_CMD_HEARTBEAT_PACKET_REQUEST:
                {
                    int sendret;
                    ZPC_INFO("recvice heart: %s",recvbuf);
                    j = 0;
                    for(i=0; i< recvsize; i++)
                    {
                            server_time[j++] = recvbuf[i];
                    }
                    g_zpcInfo.server_dt.year = (server_time[0]-'0')*1000 + (server_time[1]-'0')*100 + (server_time[2]-'0')*10 + (server_time[3]-'0');
                    g_zpcInfo.server_dt.month = (server_time[4]-'0')*10 + (server_time[5]-'0');
                    g_zpcInfo.server_dt.day = (server_time[6]-'0')*10 + (server_time[7]-'0');
                    g_zpcInfo.server_dt.hour = (server_time[8]-'0')*10 + (server_time[9]-'0');
                    g_zpcInfo.server_dt.minute = (server_time[10]-'0')*10 + (server_time[11]-'0');
                    g_zpcInfo.server_dt.second = (server_time[12]-'0')*10 + (server_time[13]-'0');
                    d=g_zpcInfo.server_dt.day;
                    m=g_zpcInfo.server_dt.month;
                    y=g_zpcInfo.server_dt.year;
                    if (m ==1||m ==2)
                    {
                            m+=12;
                            y--;
                    }
                    g_zpcInfo.server_dt.wday = (d+1+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
                    //ZPC_INFO("week day=%d",g_zpcInfo.server_dt.wday);
                    //sys_set_rtc_date_time(&g_zpcInfo.server_dt, &g_zpcInfo.server_dt);
                    sprintf(g_zpcInfo.timeStr, "%u-%u-%u %u:%u:%u", g_zpcInfo.server_dt.year, g_zpcInfo.server_dt.month, g_zpcInfo.server_dt.day, g_zpcInfo.server_dt.hour,g_zpcInfo.server_dt.minute,g_zpcInfo.server_dt.second);
                    g_zpcInfo.heartbeat_flag=1;
                }
                break;

                case DP_TYPE_ERROR:
                {
                    //ZPC_INFO("DP_TYPE_ERROR: %s",recvbuf);
                }
                break;

                default:
                break;
        }

        return ret;
}
static void zpc_check_space(char *str, char *out)
{
        char buf[1024];
        int i=0,j=0;
        if(str==NULL||out==NULL)
                return;
        memset(buf, 0, sizeof(buf));
        for(i=0;i<strlen(str);i++)
        {
                if(str[i]==' ')
                        continue;
                else
                        buf[j++] = str[i];
        }
        memcpy(out, buf, strlen(buf));
}
static int zpc_get_hwaddr(zpc_hwinfo_t *info)
{
        int fd=0;
        int trycnt=3;
        char buf[1024];
        int ret=0;
        char *str1=NULL;
        char *str2=NULL;
        char strbuf[64];
        char *mac = info->mac;
        char *ip = info->ip;

        system("ifconfig|grep eth0 -A 1 > /tmp/eth0_addr");

        fd = open("/tmp/eth0_addr", O_RDWR);
        if(fd<0)
        {
                ZPC_ERR("file open error");
                return -1;
        }
        memset(buf, 0, sizeof(buf));
        ret = read(fd, buf, sizeof(buf));
        if(ret<=0)
        {
                ZPC_ERR("File blank");
                close(fd);
                return -1;
        }
        //ZPC_INFO("%s", buf);
        str1 = strstr(buf, "HWaddr ");
        if(str1!=NULL)
        {
                str1 += strlen("HWaddr ");
                memset(mac, 0, sizeof(info->mac));
                memcpy(mac, str1, 17);
        }
        str1 = strstr(buf, "inet addr:");
        str2 = strstr(buf, "Bcast:");
        if(str1!=NULL&&str2!=NULL)
        {
                str1 += strlen("inet addr:");
                memset(strbuf, 0, sizeof(strbuf));
                memcpy(strbuf, str1, str2-str1);
                memset(ip, 0, sizeof(info->ip));
                zpc_check_space(strbuf, ip);
        }

        ZPC_INFO("eth mac[%s] ip[%s]", mac,ip);
        close(fd);
        return 0;
}

static void *ZPCServerProc(void *pdata)
{
        zpc_param_t *Mstate = (zpc_param_t*)pdata;
    int checkCnt=0;
    int PostDevStateEnable = 0;
    ZPCServer_cbmsg_t *msg;
    ZPCServerCallbackListData_t *pstZPCServerCallbackData = NULL;
    list_t *pListPos = NULL;
    int stateChange=0;
    char sendbuf[64];
    int ret=0;
        char *server_ip=NULL;
        char  deskid[5]={0};
        char  save_deskid[5]={0};
        int type;
        unsigned int len;
        int64_t hb_send_now_time;
        int64_t hb_send_interval;
        int hb_send_try_cnt;
        unsigned char packet_num, packet_id;

        printf("Exec %s\n",__func__);

        meetting_mkdirs();

relink:
        g_zpcInfo.server_connect = 0;
        if(client_pthread_exit_flag==1)
                return 0;

        while(is_network_connected()==false)
        {
                ZPC_INFO("Network disconnected!");
                download_busy = false;
                if(client_pthread_exit_flag==1)
                        return 0;
                sleep(1);
        }

        while(link_server_waiting==true)
        {
                ZPC_INFO("Link server: waiting......");
                if(client_pthread_exit_flag==1)
                        return 0;
                sleep(RECONNED_WAIT_TIME);
        }

        g_zpcInfo.server_connect = 0;

	if(g_zpcInfo.server_type==1)
	{
		#if (SERVER_IP_SEL==0)
		struct hostent *host=gethostbyname(g_zpcInfo.server_dn);
		if (!host)
			ZPC_ERR("gethost... error");
		else
		{
			server_ip = inet_ntoa(*(struct in_addr *)host->h_addr_list[0]);
			memset(g_zpcInfo.server_ip,0, strlen(g_zpcInfo.server_ip));
			memcpy(g_zpcInfo.server_ip, server_ip, strlen(server_ip));
		}
		#endif
		//192.168.1.112:520
		if(client_init(g_zpcInfo.server_ip, g_zpcInfo.port)<0)
		{
			ZPC_ERR("client_init error: relink\n");
			download_busy = false;
			sleep(RECONNED_WAIT_TIME);
			goto relink;
		}
	}
	else
	{
		//192.168.1.112:520
		if(discover==1)
		{
			if(client_init(g_zpcInfo.server_lan_ip, g_zpcInfo.port)<0)
			{
				ZPC_ERR("client_init error: relink\n");
				download_busy = false;
				sleep(RECONNED_WAIT_TIME);
				goto relink;
			}
		}
		else
		{
			goto relink;
		}
	}

        //发送一个 桌牌包给服务器
        //服务器收到之后立马发回桌牌确认包
        // 若收到确认包, 查看包内容是否为ok，若为 ok
        //成功连接服务器，否则继续三次这样的请求，
        //直到三次都失败，才进行重新连接操作。
        ZPC_INFO("deskid=%s len=%d", g_zpcInfo.deskid, strlen(g_zpcInfo.deskid));

        sprintf(sendbuf, "%s|%s|%d|%d", g_zpcInfo.deskid, g_zpcInfo.hwinfo.mac,g_zpcInfo.battery,g_zpcInfo.status);
        ZPC_INFO("send deskid:[%s]", sendbuf);
        if(wait_confirm_deskid(sendbuf, strlen(sendbuf)) != 1)
        {
                ZPC_ERR("wait confirm deskid failed ,new deskid:%s",g_zpcInfo.deskid);
                //确认失败重新连接
                close_sockfd();
                sleep(RECONNED_WAIT_TIME);
                goto relink;
        }

//连接成功
link_sucess:
        //发送桌牌
        /*ret = send_deskid_to_server(g_zpcInfo.deskid);
        if(ret == -1)
        {
                ZPC_ERR("send deskid to server failed, because net error");
                //确认失败重新连接
                close_sockfd();
                sleep(RECONNED_WAIT_TIME);
                goto relink;
        }*/

        memset(packet_data, 0, CLIENT_RECV_BUFSIZE);
        g_zpcInfo.server_connect = 1;

        //strcpy(g_zpcInfo.deskid, deskid);
        strcpy(save_deskid, g_zpcInfo.deskid);
        //strcpy(g_zpcInfo.server_ip, server_ip);
        //check_SeatNum = true;
        client_reconnect_flag=0;
        ZPC_INFO("deskid:[%s] len=%d", g_zpcInfo.deskid, strlen(g_zpcInfo.deskid));

//发送心跳包
HB_SEND_AGAIN:
        ret = send_heartbeat();
        hb_send_start_time = get_ab_timer();
        if(ret==0)
        {
                hb_send_try_cnt++;
                if(hb_send_try_cnt>HB_CONFIRM_CNT)
                {
                        ZPC_INFO("First heartbeat send failed");
                        close_sockfd();
                        goto relink;
                }
                else
                {
                        sleep(5);
                        ZPC_INFO("again send heartbeat");
                        goto HB_SEND_AGAIN;
                }
        }
        else if(ret==-1)
        {
                ZPC_INFO("network break when send HB");
                close_sockfd();
                goto relink;
        }
        else
        {
                ZPC_INFO("heartbeat_keepAlive loading...");
                hb_send_cnt = 1;
                heartbeat_keepAlive = 1;
        }

    while (g_ZPCServerThreadRun)
    {
        if(client_pthread_exit_flag==1)
                {
                ZPC_INFO("client_pthread_exit_flag==1");
                        ret = -2;
                        break;
                }
        if(client_reconnect_flag==1)
        {
                        ZPC_INFO("client_reconnect_flag==1");
                        client_reconnect_flag=0;
                        ret = -1;
                        break;
                }

                hb_send_now_time = get_tick_time_ms();
                hb_send_interval = hb_send_now_time - hb_send_start_time;
                if(hb_send_interval<0)
                        hb_send_interval = HB_LOOP_TIME+1;
                if(hb_send_interval > HB_LOOP_TIME)
                {
                        if(hb_send_cnt>0)
                        {
                                ZPC_INFO("heartbeat timeout %d",hb_send_cnt);
                                if(hb_send_cnt>=HB_CONFIRM_CNT)
                                {
                                        ZPC_INFO("Receive heartbeat failed, break current connect.");
                                        heartbeat_keepAlive = 0;
                                        g_zpcInfo.heartbeat_flag = 0;
                                        ret = -1;
                                        break;
                                }
                        }
                        ret = send_heartbeat();
                        hb_send_start_time = get_ab_timer();
                        if(ret>0)
                        {
                                hb_send_cnt++;
                                heartbeat_keepAlive = 1;
                        }
                        else if(ret==-1)
                        {
                                ZPC_INFO("network break when send HB");
                                heartbeat_keepAlive = 0;
                                ret = -1;
                                break;
                        }
                }

                checkCnt++;
                if(checkCnt>=3)
                {
                    checkCnt=0;
                    if(g_zpcInfo.deskid_flag == 0)
                    {

                            ZPC_INFO("Request [meeting name id] files");
                            memset(sendbuf, 0, sizeof(sendbuf));
                            sendbuf[0]=1;
                            #if 0
                            ret = send_packet_to_server(DP_TYPE_CMD_UPDATE_CARD, sendbuf, 1);
                            #else
                            ret = send_packet_to_server(DP_TYPE_CMD_UPDATE_CARD, g_zpcInfo.deskid, strlen(g_zpcInfo.deskid));
                            #endif
                            if(ret < 0)
                            {
                                    ZPC_ERR("ret=%d; 0=no data, -1=net error", ret);
                                    break;
                            }
                            g_zpcInfo.deskid_flag = 1;
                    }
                }

                //常规的接收数据就这么清除缓存
                memset(packet_data, 0, CLIENT_RECV_BUFSIZE);
                ret = read_data(&type, &packet_num, &packet_id, packet_data, &len);
                if(ret < 0)
                {
                        ZPC_ERR("ret=%d; 0=no data, -1=net error -2=checksum error", ret);
                        break;
                }
                else if(ret ==0)
                {
                        usleep(100000);
                        continue;
                }
                else//进行数据处理
                {
                        msg = client_dp_parse(packet_num, packet_id, packet_data, len, type);
                        if(msg)
                        {
                                PostDevStateEnable |= 0x01;
                        }
                }

        while(PostDevStateEnable)//post to gui app
                {
                        PostDevStateEnable = 0;
                        pthread_mutex_lock(&g_ZPCServerCallbackListMutex);
                        list_for_each(pListPos, &g_ZPCServerCallbackListHead)
                        {
                                pstZPCServerCallbackData = list_entry(pListPos, ZPCServerCallbackListData_t, callbackList);
                                pstZPCServerCallbackData->pfnCallback(msg);
                        }
                        pthread_mutex_unlock(&g_ZPCServerCallbackListMutex);

                        usleep(10000);
                }

    }

        if(ret <= 0)
        {
                //heartbeat_pthread_destory();//结束心跳包进程
                ZPC_ERR("heartbeat_pthread_destory");
                close_sockfd();
                goto relink;
        }
        printf("exit %s\n",__func__);
        return NULL;
}

/*************************************
Author: Carey
*return: 0=success,-1=fail
**************************************/
int zpc_start_proc_msg(zpc_msg_proc_t *scene)
{
        int ret=0;

        pthread_mutex_lock(&scene->MsgProcLock);
    scene->MsgProc_start=1;
    pthread_cond_signal(&scene->MsgProcCondition);
    pthread_mutex_unlock(&scene->MsgProcLock);
    return ret;
}


/*************************************
Author: Carey
*return: 0=success,-1=fail
**************************************/
int zpc_free_msg_list_res(zpc_msg_proc_t *scene)
{
        msg_list_t *cur=NULL;
        msg_list_t *next=NULL;

        list_for_each_entry_safe(cur, next, &scene->Msg_list.list, list)
        {
                list_del(&cur->list);
                cur = NULL;
        }
        scene->msg_total = 0;
        scene->proc_num = 0;
        return 0;
}

/*************************************
Author: Carey
*return: 0=success,-1=fail
**************************************/
int zpc_msg_list_append_one(const zpc_msg_t *msg, zpc_msg_proc_t *scene)
{
        msg_list_t *cur=NULL;
        int ret=-1;

        pthread_mutex_lock(&scene->MsgProcDataLock);
        cur = (msg_list_t*)malloc(sizeof(msg_list_t));
        if(cur==NULL)
        {
                ZPC_ERR("malloc error");
                ret=-1;
                goto err_exit;
        }
        memset(cur,0,sizeof(msg_list_t));
        memcpy(&cur->msg, msg, sizeof(zpc_msg_t));
        cur->flag = 1;
        list_add_tail(&cur->list, &scene->Msg_list.list);
        scene->msg_total++;
        scene->proc_num++;
        ret = 0;
err_exit:
        pthread_mutex_unlock(&scene->MsgProcDataLock);
        return ret;
}

static void zpc_proc_messages(zpc_msg_t *msg)
{
        int ret;
        unsigned char val=0;
        char buf[1024];
        char path[128];
        char path1[128];
        char path2[128];
        char path3[128];
        char cmd[1024];
        if(msg->type==ZPC_MSG_UPDATE_IP)
        {
                ZPC_INFO("update ip:%s",msg->data_buf);
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                memset(g_zpcInfo.server_lan_ip, 0, sizeof(g_zpcInfo.server_lan_ip));
                memcpy(g_zpcInfo.server_lan_ip, msg->data_buf, msg->data_len);
                updateZpcConfigString(g_zpcClient, "server_lan_ip", g_zpcInfo.server_lan_ip);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
        }
        else if(msg->type==ZPC_MSG_UPDATE_PORT)
        {
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                memcpy(&g_zpcInfo.port, msg->data_buf, msg->data_len);
                updateZpcConfigNumber(g_zpcClient, "port", g_zpcInfo.port);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
        }
        else if(msg->type==ZPC_MSG_UPDATE_ID)
        {
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                ZPC_INFO("update id:%s",msg->data_buf);
                memset(g_zpcInfo.deskid, 0, sizeof(g_zpcInfo.deskid));
                memcpy(g_zpcInfo.deskid, msg->data_buf,msg->data_len);
                updateZpcConfigString(g_zpcMeeting, "deskid", g_zpcInfo.deskid);
                ZPC_INFO("g_zpcInfo.deskid:%s",g_zpcInfo.deskid);
                SSTAR_ZPCSyncConfig();
                sprintf(path,"/customer/res/ui/idcard/%s.bmp",g_zpcInfo.deskid);
                sprintf(path1,"/customer/res/ui/idcard/%s.png",g_zpcInfo.deskid);
                sprintf(path2,"/customer/res/ui/idcard/%s.jpeg",g_zpcInfo.deskid);
                sprintf(path3,"/customer/res/ui/idcard/%s.jpg",g_zpcInfo.deskid);
                if(access(path,F_OK)==0)
                {
                        ZPC_INFO("path:%s",path);
                        system("rm -f /customer/res/ui/idcard/bg1.bmp");
                        sprintf(cmd,"cp -r %s /customer/res/ui/idcard/bg1.bmp",path);
                        system(cmd);
                        system("sync");
                }
                else if(access(path1,F_OK)==0)
                {
                        ZPC_INFO("path:%s",path1);
                        system("rm -f /customer/res/ui/idcard/bg1.bmp");
                        sprintf(cmd,"cp -r %s /customer/res/ui/idcard/bg1.bmp",path1);
                        system(cmd);
                        system("sync");
                }
                else if(access(path2,F_OK)==0)
                {
                        ZPC_INFO("path:%s",path2);
                        system("rm -f /customer/res/ui/idcard/bg1.bmp");
                        sprintf(cmd,"cp -r %s /customer/res/ui/idcard/bg1.bmp",path2);
                        system(cmd);
                        system("sync");
                }
                else if(access(path3,F_OK)==0)
                {
                        ZPC_INFO("path:%s",path3);
                        system("rm -f /customer/res/ui/idcard/bg1.bmp");
                        sprintf(cmd,"cp -r %s /customer/res/ui/idcard/bg1.bmp",path3);
                        system(cmd);
                        system("sync");
                }
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
                client_reconnect_flag=1;
                        g_zpcInfo.summary_flag = 0;
                        g_zpcInfo.deskid_flag = 0;
                        g_zpcInfo.agenda_flag = 0;
                        g_zpcInfo.content_flag = 0;
        }
        else if(msg->type==ZPC_MSG_CHANGE_SERVER_TYPE)
        {
                ZPC_INFO("update service type:%s",msg->data_buf);
                int type=0;
                memcpy(&type, msg->data_buf, sizeof(int));
                if(type!=g_zpcInfo.server_type)
                {
                        g_zpcInfo.server_type = type;
                        pthread_mutex_lock(&g_ZPCServerParamMutex);
                        updateZpcConfigNumber(g_zpcClient, "server_type",g_zpcInfo.server_type);
                        SSTAR_ZPCSyncConfig();
                        pthread_mutex_unlock(&g_ZPCServerParamMutex);
                        client_reconnect_flag=1;
                        g_zpcInfo.summary_flag = 0;
                        g_zpcInfo.deskid_flag = 0;
                        g_zpcInfo.agenda_flag = 0;
                        g_zpcInfo.content_flag = 0;
                }
        }
        else if(msg->type==ZPC_MSG_UPDATE_COMPANY)
        {
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                updateZpcConfigString(g_zpcMeeting, "company", g_zpcInfo.company);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
        }
        else if(msg->type==ZPC_MSG_UPDATE_PRESENT)
        {
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                updateZpcConfigString(g_zpcMeeting, "participant", g_zpcInfo.participant);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
        }
        else if(msg->type==ZPC_MSG_UPDATE_TITIE)
        {
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                updateZpcConfigString(g_zpcMeeting, "person_title", g_zpcInfo.person_title);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
        }
        else if(msg->type==ZPC_MSG_UPDATE_AGENDA)
        {
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                updateZpcConfigNumber(g_zpcMeeting, "agenda_total",g_zpcInfo.agenda_total);
                updateZpcConfigString(g_zpcMeeting, "version_agenda", g_zpcInfo.version_agenda);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
        }
        else if(msg->type==ZPC_MSG_UPDATE_CONTENT)
        {
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                updateZpcConfigNumber(g_zpcMeeting, "content_total",g_zpcInfo.content_total);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                updateZpcConfigString(g_zpcMeeting, "version_content", g_zpcInfo.version_content);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
        }
        else if(msg->type==ZPC_MSG_UPDATE_MEETING_INFO)
        {
                pthread_mutex_lock(&g_ZPCServerParamMutex);
                updateZpcConfigString(g_zpcMeeting, "theme", g_zpcInfo.meeting_theme);
                updateZpcConfigString(g_zpcMeeting, "company", g_zpcInfo.company);
                updateZpcConfigString(g_zpcMeeting, "participant", g_zpcInfo.participant);
                updateZpcConfigString(g_zpcMeeting, "person_title", g_zpcInfo.person_title);
                SSTAR_ZPCSyncConfig();
                pthread_mutex_unlock(&g_ZPCServerParamMutex);
        }
        else if(msg->type==ZPC_MSG_UPDATE_NET_CONFIG)
        {
                client_reconnect_flag=1;
        }
        else
        {
                printf("[error]msg type not define!\n");
        }
}

static void *ZPCMsgProc(void *pdata)
{
        zpc_param_t *Mstate = (zpc_param_t*)pdata;
    int ret=-1;
    msg_list_t *cur=NULL;
    msg_list_t *next=NULL;

    while (g_ZPCMsgProcThreadRun)
    {
                pthread_mutex_lock(&g_zpcMsg.MsgProcLock);
                while(!g_zpcMsg.MsgProc_start)
                {
                        //ZPC_INFO("sleep in");
                        pthread_cond_wait(&g_zpcMsg.MsgProcCondition, &g_zpcMsg.MsgProcLock);
                        //ZPC_INFO("sleep out");
                }

                if(g_zpcMsg.proc_num>0)
                {
                        list_for_each_entry_safe(cur, next, &g_zpcMsg.Msg_list.list, list)
                        {
                                if(cur->flag==1)
                                {
                                        zpc_proc_messages(&cur->msg);
                                        cur->flag = 0;
                                        g_zpcMsg.proc_num--;
                                        if(g_zpcMsg.proc_num<=0)
                                        {
                                                g_zpcMsg.proc_num = 0;
                                                break;
                                        }
                                }
                                pthread_mutex_lock(&g_zpcMsg.MsgProcDataLock);
                                list_del(&cur->list);
                                cur = NULL;
                                pthread_mutex_unlock(&g_zpcMsg.MsgProcDataLock);
                        }//list_for_each_entry_safe
                }
                g_zpcMsg.MsgProc_start=0;
                pthread_mutex_unlock(&g_zpcMsg.MsgProcLock);
                pthread_testcancel();
                usleep(100);
        }
        //printf("exit ZPCMsgProc\n");
        return NULL;
}

static void *ZPCDiscoverProc(void *param)
{
        int sockfd;
        struct sockaddr_in saddr;
        int ret;
        char recvline[1025];
        struct sockaddr_in presaddr;
        socklen_t len;
        char *str=NULL;
        char *str1=NULL;

        ZPC_INFO("Enter %s",__func__);
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        bzero(&saddr, sizeof(saddr));
        saddr.sin_family = AF_INET;
        saddr.sin_addr.s_addr = htonl(INADDR_ANY);
        saddr.sin_port = htons(9000);
        ZPC_INFO("saddr.sin_addr.s_addr:%x saddr.sin_port:%x",saddr.sin_addr.s_addr,saddr.sin_port);
        bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
        while (g_discover.ThreadRun)
        {
                memset(recvline, 0, sizeof(recvline));
                ret = recvfrom(sockfd, recvline, sizeof(recvline), 0 , (struct sockaddr*)&presaddr, &len);
                if (ret <= 0)
                {
                        ZPC_ERR("recv error, continue");
                        continue;
                }
                ZPC_INFO("recv %d bytes from [%s]", ret, inet_ntoa(presaddr.sin_addr));
                if(recvline[0]==0xfe&&recvline[1]==0xfe&&recvline[ret-2]==0xef&&recvline[ret-1]==0xef)
                {
                        str = &recvline[2];
                        str1=strchr(str, ':');
                        if(str1!=NULL)
                        {
                                memset(g_discover.ServerIp, 0, sizeof(g_discover.ServerIp));
                                memset(g_discover.ServerPort, 0, sizeof(g_discover.ServerPort));
                                memcpy(g_discover.ServerIp, str, str1-str);
                                str1++;
                                str=&recvline[ret-2];
                                memcpy(g_discover.ServerPort, str1, str-str1);
                                ZPC_INFO("server addr: %s:%s", g_discover.ServerIp, g_discover.ServerPort);
                                if(strcmp(g_zpcInfo.server_lan_ip,g_discover.ServerIp) != 0)
                                {
                                        memset(g_zpcInfo.server_lan_ip,0, strlen(g_zpcInfo.server_lan_ip));
                                        memcpy(g_zpcInfo.server_lan_ip, g_discover.ServerIp, strlen(g_discover.ServerIp));

                                        pthread_mutex_lock(&g_ZPCServerParamMutex);
                                        updateZpcConfigString(g_zpcClient, "server_lan_ip", g_zpcInfo.server_lan_ip);
                                        SSTAR_ZPCSyncConfig();
                                        pthread_mutex_unlock(&g_ZPCServerParamMutex);
                                }
                                g_zpcInfo.port = atoi(g_discover.ServerPort);
                                if(discover==0)
                                        discover=1;
                        }

                }
                usleep(500000);
        }
        ZPC_INFO("Leave %s",__func__);
        return 0;
}

static void DLServiceListener(DLService_cbmsg_t *msg)
{
        switch(msg->type)
        {
                case DL_CBMSG_DL_FINISH_ONE:
                {
                    memcpy(&dlresult, msg->data_buf, msg->data_len);
                    ZPC_INFO("Download one file, id=%d type=%d",dlresult.tid,dlresult.type);
                    if(dlresult.type==0)
                    {
                        system("sync");
                        usleep(10000);
                        msg_apps_t msg;
                        g_zpcInfo.deskid_flag = 3;
                        msg.type = MSG_UPDATE_IDCARD;
                        memset(msg.content, 0, sizeof(msg.content));
                        SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
                    }
                    else
                    {
                        msg_apps_t msg;
                        g_zpcInfo.deskid_flag = 0;
                        msg.type = MSG_DOWN_IDCARD_FAIL;
                        memset(msg.content, 0, sizeof(msg.content));
                        SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
                        ZPC_INFO("MSG_DOWN_IDCARD_FAIL");
                    }
                }
                break;
                default:
                        ZPC_INFO("DL ERROR");
                break;
        }
}

static int SSTAR_StartZPCServer()
{
        pthread_mutex_init(&g_ZPCServerParamMutex, NULL);
        pthread_mutex_init(&g_ZPCServerCallbackListMutex, NULL);
        INIT_LIST_HEAD(&g_ZPCServerCallbackListHead);

        initZPCConfig();
        ZPC_INFO("Server addr:%s %s, port=%d", g_zpcInfo.server_dn, g_zpcInfo.server_lan_ip, g_zpcInfo.port);
        //zpc_get_hwaddr(&g_zpcInfo.hwinfo);

        pthread_mutex_init(&g_zpcMsg.MsgProcLock, NULL);
        pthread_cond_init(&g_zpcMsg.MsgProcCondition, NULL);
        pthread_mutex_init(&g_zpcMsg.MsgProcDataLock, NULL);
        INIT_LIST_HEAD(&g_zpcMsg.Msg_list.list);

        SSTAR_RegisterDLServiceListener(DLServiceListener);

        g_ZPCMsgProcThreadRun = 1;
        pthread_create(&g_zpcMsg.MsgProc_tid, NULL, ZPCMsgProc, &g_zpcMsg);
        if (!g_zpcMsg.MsgProc_tid)
        {
                printf("create check ZPCServer thread failed\n");
                return 0;
        }

        g_ZPCServerThreadRun = 1;
        pthread_create(&g_ZPCServerThread, NULL, ZPCServerProc, &g_zpcInfo);
        if (!g_ZPCServerThread)
        {
                printf("create check ZPCServer thread failed\n");
                return 0;
        }

        g_discover.ThreadRun = 1;
        pthread_create(&g_discover.tid, NULL, ZPCDiscoverProc, &g_discover);
        if (!g_discover.tid)
        {
                printf("create discover thread failed\n");
                return 0;
        }
        return 0;
}

static void SSTAR_StopZPCServer()
{
        // exit thread
        g_discover.ThreadRun = 0;
        g_ZPCServerThreadRun = 0;
        g_ZPCMsgProcThreadRun = 0;

        saveZPCConfig();
        DeinitZPCConfig();
        system("sync");

        if(g_discover.tid)
        {
                printf("discover thread is exiting\n");
                pthread_cancel(g_discover.tid);
                pthread_join(g_discover.tid, NULL);
                g_discover.tid = 0;
                printf("discover thread exit\n");
        }

        zpc_free_msg_list_res(&g_zpcMsg);
        if(g_zpcMsg.MsgProc_tid)
        {
                printf("ZPCMsgProc thread is exiting\n");
                pthread_cancel(g_zpcMsg.MsgProc_tid);
                pthread_join(g_zpcMsg.MsgProc_tid, NULL);
                g_zpcMsg.MsgProc_tid = 0;
                printf("ZPCMsgProc thread exit\n");
        }

        if (g_ZPCServerThread)
        {
                printf("ZPCServer thread is exiting\n");
                pthread_join(g_ZPCServerThread, NULL);
                g_ZPCServerThread = 0;
                printf("ZPCServer thread exit\n");
        }

        pthread_mutex_destroy(&g_ZPCServerCallbackListMutex);
        pthread_mutex_destroy(&g_ZPCServerParamMutex);

        pthread_mutex_destroy(&g_zpcMsg.MsgProcLock);
        pthread_cond_destroy(&g_zpcMsg.MsgProcCondition);
        pthread_mutex_destroy(&g_zpcMsg.MsgProcDataLock);

        //pthread_mutex_destroy(&g_discover.Lock);
        //pthread_cond_destroy(&g_discover.Condition);
        //pthread_mutex_destroy(&g_discover.DataLock);
}

static void zpclient_sys_proc(msg_apps_t *msg)
{
        switch((int)msg->type)
        {
                case MSG_POWER_OFF:
                {
                        ZPC_INFO("Start power off");
                        break;
                }

                case MSG_STANDBY:
                {
                        g_zpcInfo.status=1;
                        ZPC_INFO("Start standby");
                        break;
                }

                case MSG_RESUME:
                {
                        ZPC_INFO("Resume");
                        g_zpcInfo.status=2;
                        break;
                }
        }
}

int SSTAR_RegisterZPCServerCallback(ZPCServerCallback pfnCallback)
{
        ZPCServerCallbackListData_t *pstZPCServerCallbackData = NULL;

        printf("Enter SSTAR_RegisterZPCServerCallback\n");

        if (!pfnCallback)
                return -1;

        pstZPCServerCallbackData = (ZPCServerCallbackListData_t*)malloc(sizeof(ZPCServerCallbackListData_t));
        memset(pstZPCServerCallbackData, 0, sizeof(ZPCServerCallbackListData_t));
        pstZPCServerCallbackData->pfnCallback = pfnCallback;

        pthread_mutex_lock(&g_ZPCServerCallbackListMutex);
        ZPCServerCallbackListData_t *pos = NULL;

        list_for_each_entry(pos, &g_ZPCServerCallbackListHead, callbackList)
        {
                if (pos->pfnCallback == pfnCallback)
                {
                        printf("have registered ZPCServer callback\n");
                        pthread_mutex_unlock(&g_ZPCServerCallbackListMutex);
                        return 0;
                }
        }

        list_add_tail(&pstZPCServerCallbackData->callbackList, &g_ZPCServerCallbackListHead);
        pthread_mutex_unlock(&g_ZPCServerCallbackListMutex);

        pthread_mutex_lock(&g_ZPCServerParamMutex);
        g_registerZPCServerChanged = 1;
        pthread_mutex_unlock(&g_ZPCServerParamMutex);

        printf("Leave SSTAR_RegisterZPCServerCallback\n");

        return 0;
}

void SSTAR_UnRegisterZPCServerCallback(ZPCServerCallback pfnCallback)
{
        ZPCServerCallbackListData_t *pstZPCServerCallbackData = NULL;
        list_t *pListPos = NULL;
        list_t *pListPosN = NULL;

        pthread_mutex_lock(&g_ZPCServerParamMutex);
        g_registerZPCServerChanged = 0;
        pthread_mutex_unlock(&g_ZPCServerParamMutex);

        pthread_mutex_lock(&g_ZPCServerCallbackListMutex);
        list_for_each_safe(pListPos, pListPosN, &g_ZPCServerCallbackListHead)
        {
                pstZPCServerCallbackData = list_entry(pListPos, ZPCServerCallbackListData_t, callbackList);

                if (pstZPCServerCallbackData->pfnCallback == pfnCallback)
                {
                        list_del(pListPos);
                        free(pstZPCServerCallbackData);
                }
        }
        pthread_mutex_unlock(&g_ZPCServerCallbackListMutex);
}

int SSTAR_ZPClient_Init()
{
        SSTAR_StartZPCServer();
        SSTAR_RegisterApplib(APP_NAME_ZPCLIENT, zpclient_sys_proc);

        return 0;
}

void SSTAR_ZPClient_Deinit()
{
        SSTAR_StopZPCServer();
        SSTAR_UnRegisterApplib(APP_NAME_ZPCLIENT, zpclient_sys_proc);
}

int SSTAR_RegisterZPCServerListener(ZPCServerCallback pfnCallback)
{
        return SSTAR_RegisterZPCServerCallback(pfnCallback);
}
void SSTAR_UnRegisterZPCServerListener(ZPCServerCallback pfnCallback)
{
        SSTAR_UnRegisterZPCServerCallback(pfnCallback);
}

void SSTAR_ZPCMsg(zpc_msg_t *msg)
{
        if(msg!=NULL)
        {
                zpc_msg_list_append_one(msg, &g_zpcMsg);
                zpc_start_proc_msg(&g_zpcMsg);
        }
}

int SSTAR_ZPCSyncConfig()
{
        int ret=-1;
        ret = saveZPCConfig();
        system("sync");
        return ret;
}

int SSTAR_ZPCGetConfigServerIp(char *buf)
{
        if(buf==NULL)
                return -1;
        memcpy(buf, g_zpcInfo.server_lan_ip, strlen(g_zpcInfo.server_lan_ip));
        return 0;
}

int SSTAR_ZPCGetConfigDeskId(char *buf)
{
        if(buf==NULL)
                return -1;
        memcpy(buf, g_zpcInfo.deskid, strlen(g_zpcInfo.deskid));
        return 0;
}

int SSTAR_ZPCGetServerConnectState()
{
        return g_zpcInfo.server_connect;
}


