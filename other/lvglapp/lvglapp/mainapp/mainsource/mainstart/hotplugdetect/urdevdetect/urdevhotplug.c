/*
 * urdevhotplug.c
 *
 *  Created on: 2021年5月15日
 *      Author: careyZeng
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/bitypes.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include "list.h"
#include "urdevhotplug.h"
#include "max485_inner.h"
#include "applib.h"
#include "app_config.h"
#include "usbhotplug.h"

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE  (8192)

unsigned char fileBuf[BUF_SIZE];
int skfd = -1, cnfd = -1;

int urdevWrite_start_proc();
#define UR_INFO(fmt, arg...) printf("[UR-INFO]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)
#define UR_ERR(fmt, arg...) printf("[UR-ERROR]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)


typedef struct{
	pthread_t tid;
	pthread_mutex_t Lock;
	pthread_cond_t Condition;
	pthread_mutex_t DataLock;
	int ThreadRun;
	char WriteStart;
	int cmd_or_file;
	int cmd_index;
	int cur_cmd;
	int r2_uart_start;
}urdev_proc_t;

typedef struct{
	long long int total_val;
	long long int cur_val;
}upg_proc_t;

static urdev_proc_t g_urdevWrite;
static urdev_proc_t g_urdevread;


//return ret: ret==1数据可读; ret=0无数据; ret<0网络错误
int uart_can_read(int fd)
{
	int rc;
	fd_set rfds;
	struct timeval timeout;

	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	timeout.tv_sec  = 0;	//2
	timeout.tv_usec = 100000;//80000

	rc = select(fd+1, &rfds, NULL, NULL, &timeout);
	if (rc < 0)   //error
	{
		printf("%s select error, exit!!!\n",__func__);
		return -1;
	}

	return FD_ISSET(fd, &rfds) ? 1 : 0;
}

unsigned int Check_num(unsigned char *p,int len)
{
	unsigned int i,j;
	unsigned int cs;

	cs = (unsigned int)p[0];
	for(i = 1;i<=len;i++)
	{
		cs ^= (unsigned int)p[i];
	}
	return cs;
}

//i：0：显示bg.png图片   1：关闭背光 2：打开背光    3升级命令   cmd:5:命令 7开机交互
void uart_tmp(unsigned int i,unsigned int cmd, int tty1_fd)
{

	unsigned int ret = 0;
	unsigned int check_val = 0;
	unsigned char sendbuf[8];

	if(cmd != 5 && cmd != 7 && cmd != 9)
			return;

	if (-1 == tty1_fd)
	{
		//printf("open tty1 fail\n");
	}
	else
	{

		memset(sendbuf, 0, sizeof(sendbuf));
		sendbuf[0] = 0xfe;
		sendbuf[1] = 0xfe;
		sendbuf[2] = cmd;
		sendbuf[3] = i;//
		sendbuf[4] = 0;//
		

		check_val = Check_num(sendbuf,8);
		sendbuf[5] = check_val;
		sendbuf[6] = 0xef;
		sendbuf[7] = 0xef;

		ret=write(tty1_fd,sendbuf,8);
		if(ret!=8)
		{
			printf("cnfd write error3\n");
		}
	}

}


void uart_bg_bmp(char *logo_path,int cmd, int tty1_fd)
{
	unsigned char sendbuf[8];
	FILE *fd =NULL;
	unsigned int lsize =0;
	unsigned int totol_num = 0;
	unsigned int ret = 0;
	unsigned int i = 0;
	unsigned int datelen = 0;
	unsigned int j = 0,k = 0;
	unsigned int check_val = 0;
	printf("uart_bg_bmp\n");
	upg_proc_t g_cur_upg;
	msg_apps_t msg;
	int size, netSize;
	char buf[10];
	if(logo_path==NULL||tty1_fd<=0)
	{
		printf("NULL return\n");
		return;
	}
	if((access(logo_path,F_OK)==0) && (access(logo_path,R_OK)==0))
	{
		fd = fopen(logo_path,"r+");
		if(fd !=NULL)
		{
			//printf("uart_bg_bmp3\n");
			fseek(fd,0,SEEK_END);
			lsize = ftell(fd);
			fseek(fd,0,SEEK_SET);

			//printf("lsize = %d\n",lsize);
			g_cur_upg.total_val = lsize;
			g_cur_upg.cur_val = 0;
				
			memset(sendbuf, 0, sizeof(sendbuf));
			sendbuf[0] = 0xfe;
			sendbuf[1] = 0xfe;
			sendbuf[2] = cmd;
			sendbuf[3] = 0;//
			sendbuf[4] = 0;//

			check_val = Check_num(sendbuf,5+j);
			sendbuf[5] = check_val;
			sendbuf[6] = 0xef;
			sendbuf[7] = 0xef;
			//printf("sendbuf[3] = %d,sendbuf[4] = %d\n",sendbuf[3],sendbuf[4]);
			ret=write(tty1_fd,sendbuf,8);
			//printf("write ret = %d\n",ret);
			if(ret!=8)
			{
				printf("cnfd write error4\n");
			}	

			if( read(cnfd, buf, 2) != 2) {
				
				printf("cnfd read error\n");	
			}

			if(write(cnfd, (unsigned char *)&lsize, 4) != 4)
			{
				printf("lsize write error\n");
			}

			memset(fileBuf,0,8192);
			while(1)
			{
				if(fd!=NULL)
				{
					size = fread(fileBuf, 1, BUF_SIZE, fd);
					if(size>0)
					{
						//printf("size = %d\n",size);
						unsigned int size2 = 0;
						while( size2 < size ) {
							if( (netSize = write(cnfd, fileBuf + size2, size - size2) ) < 0 ) {
								printf("cnfd write error1\n");

							}
							size2 += netSize;
							//printf("size2 = %d\n",size2);
						}
						memset(fileBuf,0,8192);
						if(cmd == 6)
						{
							g_cur_upg.cur_val += size;

							msg.type = MSG_SEND_UPG_PRO;
							memset(msg.content, 0, sizeof(msg.content));
							memcpy(msg.content, &g_cur_upg, sizeof(upg_proc_t));
							SSTAR_SendAsyncMsg(APP_NAME_SET, &msg);
						}
					}
					else
					{
						msg.type = MSG_R2_SEND_FINISH;
						memset(msg.content, 0, sizeof(msg.content));
						SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
						break;
					}
				}
				else
				{
					break;
				}
		    }	

			fclose(fd);
			fd =NULL;
			
			if(cmd == 6)
			{
				if( read(cnfd, sendbuf, 8) != 8)
				{
					printf("cnfd read error\n");
					msg.type = MSG_SEND_UPG_PRO_FINISH;
					memset(msg.content, 0, sizeof(msg.content));
					SSTAR_SendAsyncMsg(APP_NAME_SET, &msg);

				}
				else
				{
					printf("cnfd read success\n");
					msg.type = MSG_SEND_UPG_PRO_FINISH;
					memset(msg.content, 0, sizeof(msg.content));
					SSTAR_SendAsyncMsg(APP_NAME_SET, &msg);
				}
			}
		
		}

	}

}

int net_up_flag = 0;
int net_up_flag2 = 0;
int net_up_flag3 = 0;
int net_up_state = 0;
int net_up_connect_state = 0;
int net_up_connect_state_time = 0;
static void *urdevreadProc(void *pdata)
{
	printf("Exec %s\n", __func__);
	struct sockaddr_in sockAddr, cltAddr;
	socklen_t addrLen;
	unsigned int fileSize;
	int size, netSize;
	char buf[10];
	int socket_flag = 0;
    FILE *fp_net = NULL;
    unsigned char sendbuf[8];
	int lsize = 0;
	char *rebuff = NULL;
	int ret = 0;
	msg_apps_t g_msg;
	int reuse = 1;
	while (g_urdevread.ThreadRun)
	{
		if(net_up_state == 0)
		{
			net_up_connect_state_time = 0;
			fp_net = fopen("/sys/class/net/usb0/operstate", "r");
			if( fp_net == NULL ) {
				printf("fp_net == NULL!\n");
				sleep(1);
			}
			else
			{
				fseek(fp_net,0,SEEK_END);
				lsize = ftell(fp_net);
				rewind(fp_net);
				rebuff= (char *)malloc(lsize+1);
				memset(rebuff,0,lsize+1);
				fread(rebuff,1, lsize,fp_net);
				if(strstr(rebuff,"down") || net_up_connect_state == 2)
				{
					printf("net_up_state down!\n");
					system("ifconfig usb0 192.168.5.1 up");

					sleep(1);
					system("echo -n \"2-1:1.0\"|tee /sys/bus/usb/drivers/cdc_ether/unbind");
					sleep(1);
					system("echo -n \"2-1:1.0\"|tee /sys/bus/usb/drivers/cdc_ether/bind");
					sleep(1);
					system("ifconfig usb0 192.168.5.1 up");

					net_up_connect_state = 0;
				}
				else
				{

					printf("net_up_state up!\n");
					net_up_state = 1;
				}
				fclose(fp_net);
				fp_net =NULL;
				free(rebuff);
			}

		}
		else
		{

			if(net_up_connect_state == 0)
			{
				net_up_connect_state_time = 0;
				printf("socket skfd = %d\n",skfd);
				if(skfd < 0)
				{
					if((skfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
					{
						printf("socket false\n");

					}
					else
					{
						//int reuse = 1;

						if (setsockopt(skfd, SOL_SOCKET, SO_REUSEADDR,&reuse, sizeof(reuse)))
						{
							perror("setsockopt failed");
							//exit(1);
						}
						printf("socket success!\n");
						memset(&sockAddr, 0, sizeof(struct sockaddr_in));
						sockAddr.sin_family = AF_INET;
						sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
						sockAddr.sin_port = htons(10002);


						//setsockopt(skfd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int));
					   //bind
						if(bind(skfd, (struct sockaddr *)(&sockAddr), sizeof(struct sockaddr)) < 0)
						{
							printf("bind false\n");

						}
						else
						{
							//printf("bind success!\n");
							if(listen(skfd, 4) < 0)
							{
								printf("Listen false\n");

							}
							else
							{
								//printf("listen success!\n");
								addrLen = sizeof(struct sockaddr_in);
								if((cnfd = accept(skfd, (struct sockaddr *)(&cltAddr), &addrLen)) < 0) {
									printf("Accept false\n");

								}
								else
								{
									g_urdevread.r2_uart_start = 1;
									printf("accept success!\n");
									//g_urdevread.ThreadRun = 0;
									net_up_connect_state = 1;
									g_msg.type = MSG_R2_INIT_FINISH;
									memset(g_msg.content, 0, sizeof(g_msg.content));
									SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &g_msg);
								}
						    }
						}
					}
				}
				else
				{

					if (setsockopt(skfd, SOL_SOCKET, SO_REUSEADDR,&reuse, sizeof(reuse)))
					{
						perror("setsockopt failed");
						//exit(1);
					}
					else
					{

						printf("setsockopt success!\n");
					}
					printf("socket success!\n");
					memset(&sockAddr, 0, sizeof(struct sockaddr_in));
					sockAddr.sin_family = AF_INET;
					sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
					sockAddr.sin_port = htons(10002);

				   //bind
					//setsockopt(skfd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int));
					if(bind(skfd, (struct sockaddr *)(&sockAddr), sizeof(struct sockaddr)) < 0)
					{
						printf("bind false\n");

					}
					else
					{
						printf("bind success!\n");
						if(listen(skfd, 4) < 0)
						{
							printf("Listen false\n");

						}
						else
						{
							printf("listen success!\n");
							addrLen = sizeof(struct sockaddr_in);
							if((cnfd = accept(skfd, (struct sockaddr *)(&cltAddr), &addrLen)) < 0) {
								printf("Accept false\n");

							}
							else
							{
								printf("accept success!\n");
								g_urdevread.r2_uart_start = 1;
								//g_urdevread.ThreadRun = 0;
								net_up_connect_state = 1;
								g_msg.type = MSG_R2_INIT_FINISH;
								memset(g_msg.content, 0, sizeof(g_msg.content));
								SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &g_msg);
							}
					   }
					}
				}
			}
			else
			{
				fp_net = fopen("/sys/class/net/usb0/operstate", "r");
				if( fp_net == NULL ) {
					printf("fp_net == NULL!\n");
					net_up_connect_state = 2;
					g_urdevread.r2_uart_start = 0;
					net_up_state = 0;
					close(skfd);
					skfd = -1;

					sleep(1);
				}
				else
				{
					fclose(fp_net);
					fp_net =NULL;
				}
				if(net_up_flag2 != 1 && g_urdevWrite.WriteStart == 0)
				{
					//printf("sendbuf write4\n");

					sleep(2);
					net_up_flag = 1;
					urdevWrite_start_proc();
				}
				//net_up_connect_state = 0;
			}
		}
	}

	
	if (g_urdevread.tid)
	{
		printf("g_urdevread thread is exiting\n");
		pthread_join(g_urdevread.tid, NULL);
		g_urdevread.tid = 0;
		printf("g_urdevread thread exit\n");
	}
	pthread_mutex_destroy(&g_urdevread.Lock);

	printf("Exit %s\n", __func__);
	return NULL;
}

int urdevWrite_start_proc()
{
	//printf("urdevWrite_start_proc Exec %s\n", __func__);
	pthread_mutex_lock(&g_urdevWrite.Lock);
	g_urdevWrite.WriteStart=1;
    pthread_cond_signal(&g_urdevWrite.Condition);
    pthread_mutex_unlock(&g_urdevWrite.Lock);
    return 0;
}

static void *urdevWriteProc(void *pdata)
{
    printf("Exec %s\n", __func__);
    unsigned char sendbuf[8];
    char path[128];
    int ret = 0;
    while (g_urdevWrite.ThreadRun)
    {

		pthread_mutex_lock(&g_urdevWrite.Lock);
		while(!g_urdevWrite.WriteStart)
		{
			pthread_cond_wait(&g_urdevWrite.Condition, &g_urdevWrite.Lock);
		}

		pthread_mutex_lock(&g_urdevWrite.DataLock);
		//printf("g_urdevWrite.WriteStart = %d\n", g_urdevWrite.WriteStart);
		//printf("net_up_connect_state = %d\n", net_up_connect_state);
		//printf("net_up_flag=%d / net_up_flag2=%d / net_up_flag3=%d \n",net_up_flag,net_up_flag2,net_up_flag3);
		if(net_up_connect_state != 3)
		{
			if(net_up_flag == 1 && net_up_flag2 != 1)
			{
				if(net_up_flag3 != 1)
				{
					net_up_flag = 0;
					//printf("sendbuf write\n");
					sendbuf[0] = 0xfe;
					sendbuf[1] = 0xfe;
					sendbuf[2] = 0xfe;
					sendbuf[3] = 0xfe;//
					sendbuf[4] = 0x00;//
					sendbuf[5] = 0x00;
					sendbuf[6] = 0x00;
					sendbuf[7] = 0x00;
					ret=send(cnfd,sendbuf,8,MSG_DONTWAIT);
					if(ret!=8)
					{
						printf("cnfd write error2\n");
						net_up_connect_state_time++;
					}
					else
					{
						//printf("sendbuf write2\n");
						memset(sendbuf,0,8);
						recv(cnfd,sendbuf,8,MSG_DONTWAIT);

						if(sendbuf[0] == 0xfe && sendbuf[1] == 0xfe && sendbuf[6] == 0xfe && sendbuf[7] == 0xfe)
						{
							//printf("sendbuf write22\n");
							net_up_connect_state_time = 0;
						}
						else
						{
							//printf("sendbuf write222\n");
							net_up_connect_state_time++;

						}
					}
					if(net_up_connect_state_time >= 10)
					{
						//printf("sendbuf write3\n");
						close(cnfd);
						close(skfd);
						skfd = -1;
						net_up_connect_state = 2;
						g_urdevread.r2_uart_start = 0;
						net_up_state = 0;
					}
				}
				else
					net_up_flag3 = 0;
			}
			else
			{
				if(g_urdevWrite.cmd_or_file == 1)
				{
					//printf("g_urdevWrite\n");
					if(g_urdevWrite.cmd_index == 1)
					{
						uart_bg_bmp(UR_SEND_BMP_PATH,g_urdevWrite.cur_cmd,cnfd);
					}
					else if(g_urdevWrite.cmd_index == 2)
					{
						memset(path,0,sizeof(path));
						sprintf(path,"%s/fwimage/fwimage.zip",stUsbParam.udisk_path);
						uart_bg_bmp(path,g_urdevWrite.cur_cmd,cnfd);
						printf("g_urdevWrite /fwimage/fwimage.zip xxxxxxxxxxxxxxxxxx\n");
					}
				}
				else if(g_urdevWrite.cmd_or_file == 2)
				{
					UR_INFO("g_urdevWrite.cmd_index = %d g_urdevWrite.cur_cmd = %d\n",g_urdevWrite.cmd_index,g_urdevWrite.cur_cmd);
					uart_tmp(g_urdevWrite.cmd_index,g_urdevWrite.cur_cmd,cnfd);
					if(g_urdevWrite.cmd_index == 3&& g_urdevWrite.cur_cmd == 5)
					{
						net_up_connect_state = 3;
						close(skfd);
						skfd = -1;
					}
				}
				net_up_flag2 = 0;
				net_up_flag3 = 1;
			}
		}

		pthread_mutex_unlock(&g_urdevWrite.DataLock);

		g_urdevWrite.WriteStart=0;

		pthread_mutex_unlock(&g_urdevWrite.Lock);
		pthread_testcancel();
	}
	printf("Exit %s\n", __func__);
	return NULL;
}

static void urdev_sys_proc(msg_apps_t *msg)
{
	urdev_param_t cur_g_urdevWrite;
	switch(msg->type)
	{
		case MSG_POWER_OFF:
		{
			UR_INFO("Start power off");
			break;
		}

		case MSG_STANDBY:
		{
			UR_INFO("Start standby");
			if(g_urdevread.r2_uart_start == 1)
			{
				UR_INFO("MSG_SEND_CMD_TO_R2");
				g_urdevWrite.cur_cmd = 5;
				g_urdevWrite.cmd_index = 1;
				g_urdevWrite.cmd_or_file = 2;
				net_up_flag2 = 1;
				if(g_urdevWrite.WriteStart==0)
					urdevWrite_start_proc();
			}
			break;
		}

		case MSG_RESUME:
		{
			UR_INFO("Resume");
			if(g_urdevread.r2_uart_start == 1)
			{
				UR_INFO("MSG_SEND_CMD_TO_R2");
				g_urdevWrite.cur_cmd = 5;
				g_urdevWrite.cmd_index = 2;
				g_urdevWrite.cmd_or_file = 2;
				net_up_flag2 = 1;
				if(g_urdevWrite.WriteStart==0)
					urdevWrite_start_proc();
			}
			break;
		}

		case MSG_SEND_ID_TO_FRONTLCD:
		{
			if(g_urdevread.r2_uart_start == 1)
			{
				UR_INFO("Update front lcd's id card");
				memcpy(&cur_g_urdevWrite, msg->content, sizeof(urdev_param_t));
				g_urdevWrite.cur_cmd =cur_g_urdevWrite.cur_cmd;
				g_urdevWrite.cmd_index =cur_g_urdevWrite.cmd_index;
				g_urdevWrite.cmd_or_file =cur_g_urdevWrite.cmd_or_file;
				net_up_flag2 = 1;
				if(g_urdevWrite.WriteStart==0)
					urdevWrite_start_proc();
			}

			break;
		}

		case MSG_SEND_CMD_TO_R2:
		{
			if(g_urdevread.r2_uart_start == 1)
			{
				UR_INFO("MSG_SEND_CMD_TO_R2");
				memcpy(&cur_g_urdevWrite, msg->content, sizeof(urdev_param_t));
				g_urdevWrite.cur_cmd =cur_g_urdevWrite.cur_cmd;
				g_urdevWrite.cmd_index =cur_g_urdevWrite.cmd_index;
				g_urdevWrite.cmd_or_file =cur_g_urdevWrite.cmd_or_file;
				net_up_flag2 = 1;
				if(g_urdevWrite.WriteStart==0)
					urdevWrite_start_proc();
			}
			break;
		}

	}
}

int urdev_StartCheckHotplug()
{
	int ret=-1;
	printf("urdev_StartCheckHotplug\n");
	SSTAR_RegisterApplib(APP_NAME_URDEV, urdev_sys_proc);
	pthread_mutex_init(&g_urdevread.Lock, NULL);
	g_urdevread.ThreadRun = 1;
	pthread_create(&g_urdevread.tid, NULL, urdevreadProc, NULL);
	if (!g_urdevread.tid)
	{
		printf("create check g_urdevread thread failed\n");
		return -1;
	}

	pthread_mutex_init(&g_urdevWrite.Lock, NULL);
	pthread_cond_init(&g_urdevWrite.Condition, NULL);
	pthread_mutex_init(&g_urdevWrite.DataLock, NULL);
	g_urdevWrite.ThreadRun = 1;
	pthread_create(&g_urdevWrite.tid, NULL, urdevWriteProc, NULL);
	if (!g_urdevWrite.tid)
	{
		printf("create check g_urdevWrite Write thread failed\n");
		return -1;
	}
	return 0;
}

void urdev_StopCheckHotplug()
{
	g_urdevread.ThreadRun = 0;
	if (g_urdevread.tid)
	{
		printf("g_urdevread thread is exiting\n");
		pthread_join(g_urdevread.tid, NULL);
		g_urdevread.tid = 0;
		printf("g_urdevread thread exit\n");
	}
	pthread_mutex_destroy(&g_urdevread.Lock);

	g_urdevWrite.ThreadRun = 0;
	if (g_urdevWrite.tid)
	{
		printf("check hotplug thread is exiting\n");
		pthread_join(g_urdevWrite.tid, NULL);
		g_urdevWrite.tid = 0;
		printf("check hotplug thread exit\n");
	}
	pthread_mutex_destroy(&g_urdevWrite.Lock);
	pthread_cond_destroy(&g_urdevWrite.Condition);
	pthread_mutex_destroy(&g_urdevWrite.DataLock);

	SSTAR_UnRegisterApplib(APP_NAME_URDEV, urdev_sys_proc);
}









