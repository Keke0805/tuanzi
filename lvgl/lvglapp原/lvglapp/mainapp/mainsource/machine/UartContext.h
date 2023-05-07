/*
 * UartContext.h
 *
 *  Created on: Sep 5, 2017
 *      Author: guoxs
 */

#ifndef _UART_CONTEXT_H_
#define _UART_CONTEXT_H_

#include <vector>

#define LOGE(fmt,...) fprintf(stderr, fmt, ##__VA_ARGS__)
#define LOGD(fmt,...)  fprintf(stderr, fmt, ##__VA_ARGS__)

#ifndef BYTE
typedef unsigned char BYTE;
#endif
#ifndef UINT
typedef unsigned int UINT;
#endif
#ifndef UINT16
typedef unsigned short  UINT16;
#endif

class UartContext   
{
public:
	UartContext();
	~UartContext();
	
    bool openUart(const char *pFileName, UINT baudRate);
    int SetUart(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);

	void closeUart();

	bool isOpen() { return mIsOpen; }

	bool send(const BYTE *pData, UINT len);
    void addReadHook(void (*hook)(const unsigned char*, int));
    void removeReadHook();

    int readyToRun();
    void ReadData();



private:
	bool mIsOpen;
	int mUartID;

    // 用于拼接缓存数据，可能存在上一包数据解析未完全，残留有数据
	void (*mHook)(const BYTE*, int);
};

#endif /* _UART_CONTEXT_H_ */
