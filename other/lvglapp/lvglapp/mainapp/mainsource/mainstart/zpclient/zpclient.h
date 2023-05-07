/*
 * zpclient.h
 *
 *  Created on: 2021年06月28日
 *      Author: CareyZeng
 */

#ifndef JNI_ZP_ZPCLIENT_H_
#define JNI_ZP_ZPCLIENT_H_

#define MAX_DATA_LENGTH			1024
#define MESSAGE_BUF_MAX_SIZE	100
#define MSG_LIST_MAX_NUM 		6
#define VOTE_CANDIDATE_NUM_ONE_LINE 	2
#define VOTE_CANDIDATE_NUM_MAX_LINE 	6
#define CLIENT_RECV_BUFSIZE		(1024*2)
#define CLIENT_SEND_BUFSIZE		(1024*2)
#define CLIENT_RECV_PIC_BUFSIZE	(1024*100)
#define VER_MAX_LENGTH			32
#define MAX_VOTE_OPTNUM         15

// 0 = 47.96.137.187 ; 1 = 47.110.35.20
#define SERVER_IP_SEL         0

typedef enum{
	ZPC_CBMSG_NULL=0,
	ZPC_CBMSG_POWER_STATE=1,
	ZPC_CBMSG_WIFI_STATE_CHANGE=2,	//wifi状态
	MSG_RECV_SUMMARY,
	MSG_RECV_LOGO_PIC,
	MSG_RECV_CMD_DOWNLOAD_AGENDA,
	MSG_RECV_SCROLL_MESSAGE,
	MSG_RECV_SYSTEM_MESSAGE,
	MSG_RECV_VOTE_CMD,
	MSG_RECV_VOTE_CANCEL,
	MSG_RECV_NET_TIME,
	MSG_RECV_CMD_DOWNLOAD_VOTE_RESULT,
	MSG_RECV_CMD_DEL_ALL_DATA,
	///MSG_POWER_OFF,

}ZPCServer_cbtype_e;

typedef struct{
	ZPCServer_cbtype_e type;
	int data_len;					//数据内容总字节数
	unsigned char data_buf[1024];	//数据内容缓冲
}ZPCServer_cbmsg_t;

typedef struct{
	int year;
	int month;
	int day;
	int wday;
	int hour;
	int minute;
	int second;
}rtc_datetime_t;


typedef struct {
	char id[32]; // 发送人
	char time[128]; // 发送时间
	bool read;  //是否读取过
	char info[1024];   //信息内容

}S_INFORM_INFO;

typedef struct vote_info_s
{
	unsigned int vote_sign;	// 0=不记名投票，1=记名
	unsigned int vote_mutil_sel;// 0=单选   , 1=多选 , 2=表决
	int vote_time;	//投票时长/minute
	char vote_title[1024];      //标题
}vote_info_t;

typedef struct {
	char opt[64]; // 候选项
	bool Selected; // 是否选中： 0=未选中   1=选中
}candidate;

typedef struct{
	char mac[20];
	char ip[16];
}zpc_hwinfo_t;

typedef struct meeting_db_s
{
	char meeting_theme[MAX_DATA_LENGTH];	//会议主题，标题
	char company[MAX_DATA_LENGTH];//单位名称
	char participant[MAX_DATA_LENGTH];//与会人员姓名
	char person_title[MAX_DATA_LENGTH];//与会人员称谓
	char version_content[VER_MAX_LENGTH];
	char version_agenda[VER_MAX_LENGTH];
	int agenda_total;
	int content_total;
	char sign_time[20];		//签到时间    eg:2016.06.24 12:00:00
	char server_dn[MAX_DATA_LENGTH];
	char server_ip[32];
	char server_lan_ip[32];
	char deskid[4];
	int port;
	zpc_hwinfo_t hwinfo;

	char *scroll_message;//[MAX_DATA_LENGTH];

	bool sign_data_flag;//签到数据准备好了
	bool sign_flag;//签到标志 0=未签到

	rtc_datetime_t server_dt;		//服务器日期时间
	char timeStr[64];

	unsigned int m_content_mode;//0x41=chapter || 0x42=content
	int candidate_num;
	bool ticked_status;	//0=had not sel  1=had ticked
	bool ticked_service;	//0=服务器尚未发起投票 ; 1=服务器已发起新的投票服务
	bool ticked_result;		//0=本地没有投票统计结果; 1=本地有投票结果
	bool wlan_on;
	unsigned int scroll_time;			//滚动时间:秒
	int 	summary_flag;//summary 初始化标志
	int     file_number;
	int use_name_pic_only;
	int heartbeat_flag;
	int server_connect;
	int deskid_flag;	//0=need check, 1=checking, 2=updating, 3=update finish
	int agenda_flag;
	int content_flag;
	int server_type;	//0=local server, 1=cloud server
	int battery;
	int status;
}zpc_param_t;

typedef enum{
	ZPC_MSG_NULL,
	ZPC_MSG_UPDATE_IP=1,		//更新服务器ip地址
	ZPC_MSG_UPDATE_PORT=2,		//更新端口号
	ZPC_MSG_UPDATE_ID=3,		//更新桌牌编号
	ZPC_MSG_MEETING_SIGNED=4,	//会议签到
	ZPC_MSG_MEETING_CALL=5,		//呼叫服务1、2、3、4
	ZPC_MSG_VOTE_RESULT=6,		//投票内容
	ZPC_MSG_DL_AGENDE=7,		//下载会议议程
	ZPC_MSG_CHANGE_SERVER_TYPE=8, //更改服务器类型
	ZPC_MSG_UPDATE_COMPANY=9,        //更新公司名
	ZPC_MSG_UPDATE_PRESENT=10,       //更新与会者
	ZPC_MSG_UPDATE_TITIE=11,        //更新与会者称谓
	ZPC_MSG_UPDATE_AGENDA=12,        //更新会议议程
	ZPC_MSG_UPDATE_CONTENT=13,        //更新会议内容
	ZPC_MSG_UPDATE_MEETING_INFO=14,   //更新会议信息
	ZPC_MSG_UPDATE_NET_CONFIG=15,   //更新网络状态
}zpcmsg_type_e;

typedef struct{
	zpcmsg_type_e type;
	int data_len;					//数据内容总字节数
	char data_buf[1024];
}zpc_msg_t;

extern zpc_param_t g_zpcInfo;
extern vote_info_t vote_data;
extern candidate check[MAX_VOTE_OPTNUM];
extern S_INFORM_INFO check_list[MESSAGE_BUF_MAX_SIZE];

typedef void (*ZPCServerCallback)(ZPCServer_cbmsg_t *msg);

int SSTAR_ZPClient_Init();
void SSTAR_ZPClient_Deinit();
int SSTAR_RegisterZPCServerListener(ZPCServerCallback pfnCallback);
void SSTAR_UnRegisterZPCServerListener(ZPCServerCallback pfnCallback);
void SSTAR_ZPCMsg(zpc_msg_t *msg);
int SSTAR_ZPCSyncConfig();
int SSTAR_ZPCGetConfigServerIp(char *buf);
int SSTAR_ZPCGetConfigDeskId(char *buf);
int SSTAR_ZPCGetServerConnectState();

#endif /* JNI_ZP_ZPCLIENT_H_ */
