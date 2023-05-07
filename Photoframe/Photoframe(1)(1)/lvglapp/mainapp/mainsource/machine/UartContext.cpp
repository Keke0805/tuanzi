/*
 *
 * UartContext.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: guoxs
 */
#include "lv_cpp/lvcpp_class.h"
#include "UartContext.h"
#define UART_DATA_MEM_BUF           16384   // 16KB
#define UART_DATA_BUF_LEN			1024	// 1KB

#if(CURRENT_SIMOS==SIMULATOR_NONE_PLAT)
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/select.h>
#endif

UartContext::UartContext() :
	mIsOpen(false),
    mUartID(0),
	mHook(NULL){

}

UartContext::~UartContext() {
    closeUart();
}
#if(CURRENT_SIMOS==SIMULATOR_NONE_PLAT)
int UartContext::SetUart(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)
{

    int   i;
    int   status;
    int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};
    int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};

    struct termios options;


    if( tcgetattr( fd,&options)  !=  0)
    {
        perror("SetupSerial 1");
        return(-1);
    }

    //设置串口输入波特率和输出波特率
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
    {
        if  (speed == name_arr[i])
        {
            cfsetispeed(&options, speed_arr[i]);
            cfsetospeed(&options, speed_arr[i]);
        }
    }

    //修改控制模式，保证程序不会占用串口
    options.c_cflag |= CLOCAL;
    //修改控制模式，使得能够从串口中读取输入数据
    options.c_cflag |= CREAD;

    //设置数据流控制
    switch(flow_ctrl)
    {

        case 0 ://不使用流控制
              options.c_cflag &= ~CRTSCTS;
              break;

        case 1 ://使用硬件流控制
              options.c_cflag |= CRTSCTS;
              break;
        case 2 ://使用软件流控制
              options.c_cflag |= IXON | IXOFF | IXANY;
              break;
    }
    //设置数据位
    //屏蔽其他标志位
    options.c_cflag &= ~CSIZE;
    switch (databits)
    {
        case 5    :
                     options.c_cflag |= CS5;
                     break;
        case 6    :
                     options.c_cflag |= CS6;
                     break;
        case 7    :
                 options.c_cflag |= CS7;
                 break;
        case 8:
                 options.c_cflag |= CS8;
                 break;
        default:
                 fprintf(stderr,"Unsupported data size\n");
                 return (-1);
    }
    //设置校验位
    switch (parity)
    {
        case 'n':
        case 'N': //无奇偶校验位。
                 options.c_cflag &= ~PARENB;
                 options.c_iflag &= ~INPCK;
                 break;
        case 'o':
        case 'O'://设置为奇校验
                 options.c_cflag |= (PARODD | PARENB);
                 options.c_iflag |= INPCK;
                 break;
        case 'e':
        case 'E'://设置为偶校验
                 options.c_cflag |= PARENB;
                 options.c_cflag &= ~PARODD;
                 options.c_iflag |= INPCK;
                 break;
        case 's':
        case 'S': //设置为空格
                 options.c_cflag &= ~PARENB;
                 options.c_cflag &= ~CSTOPB;
                 break;
        default:
                 fprintf(stderr,"Unsupported parity\n");
                 return (-1);
    }
    // 设置停止位
    switch (stopbits)
    {
        case 1:
                 options.c_cflag &= ~CSTOPB; break;
        case 2:
                 options.c_cflag |= CSTOPB; break;
        default:
                       fprintf(stderr,"Unsupported stop bits\n");
                       return (-1);
    }

    options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    //修改输出模式，原始数据输出
    options.c_oflag &= ~OPOST;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    //options.c_lflag &= ~(ISIG | ICANON);
    //设置等待时间和最小接收字符
    options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */
    options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */
    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读
    tcflush(fd,TCIFLUSH);

    //激活配置 (将修改后的termios数据设置到串口中）
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        perror("com set error!\n");
        return (-1);
    }
    return (0);
}
#endif

bool UartContext::openUart(const char *pFileName, UINT baudRate) {
	LOGD("openUart pFileName = %s, baudRate = %d\n", pFileName, baudRate);

    #if(CURRENT_SIMOS==SIMULATOR_NONE_PLAT)
    mUartID = open(pFileName, O_RDWR|O_NOCTTY);

	if (mUartID <= 0) {
		mIsOpen = false;
	} else {
        if(fcntl(mUartID, F_SETFL, FNDELAY) < 0)
        {
            printf("fcntl failed!\n");
            mIsOpen = false;
        }
        else
        {
            printf("fcntl=%d\n",fcntl(mUartID, F_SETFL,FNDELAY));
            if (SetUart(mUartID,baudRate,0,8,1,'N') == -1)
            {
                mIsOpen = false;
            }
            else
            {
                mIsOpen = true;
            }
        }
        /*
		struct termios oldtio = { 0 };
		struct termios newtio = { 0 };
		tcgetattr(mUartID, &oldtio);

		newtio.c_cflag = baudRate|CS8|CLOCAL|CREAD;
		newtio.c_iflag = 0;	// IGNPAR | ICRNL
		newtio.c_oflag = 0;
		newtio.c_lflag = 0;	// ICANON
        newtio.c_cc[VTIME] = 0;
        newtio.c_cc[VMIN] = 1;
		tcflush(mUartID, TCIOFLUSH);
		tcsetattr(mUartID, TCSANOW, &newtio);

		// 设置为非阻塞
        fcntl(mUartID, F_SETFL, O_NONBLOCK);

        mIsOpen = true;
		if (!mIsOpen) {
			close(mUartID);
			mUartID = 0;
		}
        */
	}
    LOGD("openUart mIsOpen = %d\n", mIsOpen);
    #endif
	return mIsOpen;
}

void UartContext::closeUart() {
	LOGD("closeUart mIsOpen: %d...\n", mIsOpen);

	if (mIsOpen) {
		//requestExit();
		close(mUartID);
		mUartID = 0;
		mIsOpen = false;
	}
}

bool UartContext::send(const BYTE *pData, UINT len) {
	if (!mIsOpen) {
		return false;
	}

	if (write(mUartID, pData, (size_t)len) != (ssize_t)len) {	// fail
		LOGD("send Fail\n");
		return false;
	}

	// success
    printf("Send[");
    for (int i = 0; i < len; ++i)
    {
      printf("%02x ", pData[i]);
    }
    printf("]//end\n");

	return true;
}


int UartContext::readyToRun() {
    #if(CURRENT_SIMOS==SIMULATOR_NONE_PLAT)
    int rc;
    fd_set rfds;
    struct timeval timeout;

    FD_ZERO(&rfds);
    FD_SET(mUartID, &rfds);

    timeout.tv_sec  = 0;	//2
    timeout.tv_usec = 500000;//80000

    rc = select(mUartID+1, &rfds, NULL, NULL, &timeout);
    if (rc < 0)   //error
    {
        printf("%s select error, exit!!!\n",__func__);
        return -1;
    }

    return FD_ISSET(mUartID, &rfds) ? 1 : 0;
    #endif
}

void UartContext::ReadData() {
    int len;
    unsigned char revicebuf[1024] = {0};
	if (mIsOpen) {
        if(readyToRun()==1)
        {
            memset(&revicebuf,0,sizeof(revicebuf));
            len = read(mUartID, revicebuf, UART_DATA_BUF_LEN);
            printf("ret =%d \n",len);
            if (len > 0) {
                if (mHook) {
                    mHook(revicebuf, len);
                }
            }
        }
	}
}

void UartContext::addReadHook(void (*hook)(const unsigned char*, int)) {
    mHook = hook;
}

void UartContext::removeReadHook() {
    mHook = NULL;
}

