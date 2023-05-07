/*
 * max485_inner.h
 *
 *  Created on: 2021年5月15日
 *      Author: careyZeng
 */
#ifndef _JNI_MAX485_INNER_H_
#define _JNI_MAX485_INNER_H_

#define MAX485_INFO(fmt, arg...) printf("[MAX485 INFO]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)
#define MAX485_ERR(fmt, arg...) printf("[MAX485 ERROR]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)

#define DEVICE_MAX485_NAME		"/dev/ttyS1"
#define MAX485_LO_ADDR			1//1~63


#define MAX485_CMD_CO2_RESULT			0x01
#define MAX485_CMD_MANUAL_CALIBRATION 	0x03
#define MAX485_CMD_MODULE_VER			0x1e
#define MAX485_CMD_AUTO_CALIBRATION		0x10
#define MAX485_CMD_MODULE_ID			0x1f

#define MAX485_RE_GPIO		1



typedef struct _max485_packet {
	int find_cmd;		//是否收到帧头
	int finish;			//是否收到完整一帧数据
	int idx;			//
	int rec_len;		//已经收到的字节数//有可能一次收不完一个命令帧

	int data_len;		//数据内容总字节数
	unsigned char data_buf[128];	//数据内容缓冲
	unsigned char checksum;
	unsigned char tail1;
	unsigned char tail2;
	unsigned char packetInvalid;
}max485_packet_t;

int max485_read_frame_data(int fd, max485_packet_t *packet);
int max485_write_one_frame(int fd, unsigned char *buf, int bufSize);
int max485_write_test(int fd);
void max485_config(int iHandle);

#endif/*_JNI_MAX485_INNER_H_*/
