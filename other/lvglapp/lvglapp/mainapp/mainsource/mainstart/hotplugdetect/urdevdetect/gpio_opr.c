/*
 * gpio_opr.c
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



/******************通知系统需要导出控制的GPIO引脚编号**********************/
int gpio_export_init(int pin)
{
	char buffer[64];

    snprintf(buffer, sizeof(buffer), "/sys/class/gpio/gpio%d/value", pin);
	if(access(buffer,F_OK)==0)
		return 0;
	sprintf(buffer,"echo %d > /sys/class/gpio/export",pin);
  	system(buffer);
	usleep(30);
    return 1;
}


/************************通知系统取消导出*******************************/
int gpio_unexport_deinit(int pin)
{
    char buffer[64];
	sprintf(buffer,"echo %d > /sys/class/gpio/unexport",pin);
  	system(buffer);
	usleep(30);
    return 1;
}

/***********************定义输入输入方向*****************************/
//dir: 1-->IN, 0-->OUT
int gpio_direction_set(int pin, int dir)
{
	char buffer[64];

	if(dir ==1)
	{
		sprintf(buffer,"echo in > /sys/class/gpio/gpio%d/direction",pin);
	}
	else
	{
		sprintf(buffer,"echo out > /sys/class/gpio/gpio%d/direction",pin);
	}
	usleep(30);
    system(buffer);
    return 1;
}

/********************设置io状态***************************/
//value: 0-->LOW, 1-->HIGH

int gpio_status_write(int pin, int value)
{
    char buffer[64];

	if(value ==0)
	{
		sprintf(buffer,"echo 0 >/sys/class/gpio/gpio%d/value",pin);
	}
	else
	{
		sprintf(buffer,"echo 1 >/sys/class/gpio/gpio%d/value",pin);
	}
    system(buffer);
	usleep(30);
    return 1;
}

/********************获取io状态***************************/

int gpio_status_read(int pin)
{
    char path[64];
    char value_str[3];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    if (fd < 0)
	{
        printf("Failed to open gpio value for reading!\n");
        return -1;
    }

    if (read(fd, value_str, 3) < 0)
	{
        printf("Failed to read value!\n");
        return -1;
    }

    close(fd);
    return (atoi(value_str));
}

int get_gpio_in_state(int gpionum)
{
	int iostate=-1;

	gpio_export_init(gpionum);
	gpio_direction_set(gpionum, 1);
	iostate=gpio_status_read(gpionum);
	printf("read gpio%d iostate=%d\n", gpionum, iostate);
	return iostate;
}
void set_gpio_out_state(int gpionum, int iostate)
{
	gpio_export_init(gpionum);
	printf("set gpio%d to %d\n", gpionum, iostate);
	gpio_direction_set(gpionum, 0);
	gpio_status_write(gpionum, iostate);
}
void release_gpio(int gpionum)
{
	printf("release gpio%d\n", gpionum);
	gpio_unexport_deinit(gpionum);
}

