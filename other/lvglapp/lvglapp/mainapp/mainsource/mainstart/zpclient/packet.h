#ifndef _PACKET_H_
#define _PACKET_H_
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "errno.h"
#include <sys/socket.h>

enum{
    DP_TYPE_SN=0,                               /*桌牌标号*/
    DP_TYPE_CMD_UPDATE_CARD=1,                  /*桌牌名片更新*/
    DP_TYPE_CMD_UPDATE_SN = 2,                  /*更改桌牌编号*/
    DP_TYPE_CMD_UPDATE_BACKLIGHT = 3,           /*调节桌牌亮度*/
    DP_TYPE_CMD_UPDATE_POWER_STATE = 4,         /*休眠/唤醒桌牌*/
    DP_TYPE_CMD_CLEAR_INFO = 5,                 /*清除桌牌信息*/
    DP_TYPE_CMD_UPDATE_TEMPLATE = 6,            /*更新模板*/
    DP_TYPE_CMD_HEARTBEAT_PACKET_REQUEST = 9,   /*心跳包*/
    DP_TYPE_ERROR = 10,                         /*类型错误*/
};

int read_data(int *type, unsigned char *packet_num, unsigned char *packet_id, char *data, unsigned int *len);
int write_data(unsigned char type, char *data, unsigned int len);

#define     	packet_debug(...)

#endif//_PACKET_H_
