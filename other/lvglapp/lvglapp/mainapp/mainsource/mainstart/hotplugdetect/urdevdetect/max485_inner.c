/*
 * max485_inner.c
 *
 *  Created on: 2021年5月15日
 *      Author: careyZeng
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "linux/rtc.h"
#include <sys/ioctl.h>
#include "max485_inner.h"
#include "linux/serial.h"

static char parse_buf[64];
max485_packet_t max485recPacket;
static int read_len = 0;   //已经读到数据长度


static void max485_parse_packet(char *buf, int bufsize, max485_packet_t *max485recPacket)
{
	int i=0, j=0;
	int val=0;
	int data_left_size=0;
	int rec_cs=0;

	if(buf==NULL||max485recPacket==NULL)
		return;

	for(i=0;i<bufsize;i++)
	{
		if(buf[i]==0xf3 && buf[i+1]==0xf5)
		{
			memset(max485recPacket, 0, sizeof(max485_packet_t));
			max485recPacket->find_cmd=1;
			max485recPacket->idx = 2;
			i++;
			continue;
		}

		if(max485recPacket->find_cmd)
		{
			if(max485recPacket->idx==2)
			{
				max485recPacket->data_len = buf[i];	//不包含检验码和结束码
				data_left_size = max485recPacket->data_len;
			}
			else
			{
				if(max485recPacket->rec_len < data_left_size)
				{
					max485recPacket->data_buf[max485recPacket->rec_len] = buf[i];
					max485recPacket->rec_len++;
				}
				else
				{
					if(max485recPacket->idx==14)
						rec_cs = buf[i];
					else if(max485recPacket->idx==15)
						max485recPacket->tail1 = buf[i];
					else if(max485recPacket->idx==16)
					{
						max485recPacket->tail2 = buf[i];
						if(max485recPacket->tail1==0xf3 && max485recPacket->tail2==0xfb)
						{
							max485recPacket->finish=1;
							val = max485recPacket->data_len;
							for(j=0; j<max485recPacket->data_len; j++)
								val += max485recPacket->data_buf[j];
							max485recPacket->checksum = val;
							if(max485recPacket->checksum!=rec_cs)
							{
								MAX485_ERR("Packet checksum error: my cs=0x%x recv cs=0x%x", max485recPacket->checksum,rec_cs);
								max485recPacket->packetInvalid=1;
							}

						}
						else
						{
							MAX485_ERR("tail[0xf3 0xfb] not found!");
							max485recPacket->packetInvalid=1;
						}
						break;
					}
				}
			}
			max485recPacket->idx++;
		}//max485recPacket->find_cmd
	}
}

//return: error=-1, 0=continue, 1=get one packet
int max485_read_frame_data(int fd, max485_packet_t *packet)
{
	int ret=-1;
	char rcv_buf[64];
	int i;
	int len=0;

	if(packet==NULL)
	{
		MAX485_ERR("output buf is NULL");
		return -1;
	}

	memset(rcv_buf, 0, sizeof(rcv_buf));
	len = read(fd, rcv_buf, sizeof(rcv_buf));
	//MAX485_INFO("read %d bytes",len);
	if(len > 0)
	{
#if 1
		printf("max485[");
		int i;
		for(i = 0; i < len; i++)
		{
			printf("%02x ", rcv_buf[i]);
		}
		printf("]\n");
#endif
		memcpy(&parse_buf[read_len], rcv_buf, len);
		read_len += len;
		if(read_len>=17)//||(max485recPacket.data_len>0&&(max485recPacket.rec_len+len)>=max485recPacket.data_len))
		{
			max485_parse_packet(parse_buf, read_len, &max485recPacket);
			memset(parse_buf, 0, sizeof(parse_buf));
			read_len = 0;
		}

		if(max485recPacket.find_cmd && max485recPacket.finish)
		{
			if(max485recPacket.packetInvalid==0)
			{
				memcpy(packet, &max485recPacket, sizeof(max485_packet_t));
				memset(&max485recPacket, 0, sizeof(max485_packet_t));
				memset(parse_buf, 0, sizeof(parse_buf));
				read_len = 0;
				ret = 1;
				MAX485_INFO("read one packet");
			}
			else
			{
				memset(&max485recPacket, 0, sizeof(max485_packet_t));
				memset(parse_buf, 0, sizeof(parse_buf));
				read_len = 0;
				ret = -1;
				MAX485_ERR("read invalid packet");
			}
		}
	}
	else
	{
		ret = 0;
	}

    return ret;
}

int max485_write_one_frame(int fd, unsigned char *buf, int bufSize)
{
	int ret=0;

	if(buf==NULL||bufSize==0)
	{
		MAX485_ERR("NULL buf");
		return -1;
	}
	if(fd>0)
	{
		ret = write(fd, buf, bufSize);
		if(ret!=bufSize)
		{
			MAX485_ERR("write ret!=send_size, ret=%d size=%d", ret, bufSize);
			return -1;
		}
	}
	return ret;
}

int max485_write_test(int fd)
{
	int ret=0;
	unsigned char sendbuf[64];
	int send_size=0;

	send_size = 4;
	sendbuf[0]=0x11;
	sendbuf[1]=0xff;
	sendbuf[2]=0xaa;
	sendbuf[3]=0xbb;
	ret=write(fd, sendbuf, send_size);
	if(ret!=send_size)
	{
		MAX485_ERR("write ret!=send_size, ret=%d size=%d", ret, send_size);
		return -1;
	}
	return 0;
}

void max485_config(int iHandle)
{
	struct serial_rs485 rs485conf;
	memset(&rs485conf,0,sizeof(rs485conf));
	rs485conf.padding[0] = 17; //用来控制slaver收发的gpio index
	rs485conf.delay_rts_after_send = 2000; //发送完最后一个字节需要的delay，单位：us
	rs485conf.flags |= SER_RS485_RTS_ON_SEND; //发送前拉高gpio，打开SER_RS485_RTS_AFTER_SEND指的是发送后拉高
	rs485conf.flags |= SER_RS485_ENABLED; // 使能本串口485模式，默认禁用
	ioctl(iHandle, TIOCSRS485, &rs485conf);
}









