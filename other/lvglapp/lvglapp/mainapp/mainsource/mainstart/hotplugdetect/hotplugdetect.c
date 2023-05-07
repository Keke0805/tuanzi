/*
 * hotplugdetect.c
 *
 *  Created on: 2020年2月14日
 *      Author: koda.xu
 */


#include "hotplugdetect.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/bitypes.h>
#include <ctype.h>
#include <errno.h>
#include "list.h"
#include "plugin_input.h"

static int cfg_enable_wifi = 1;

void SSTAR_ConnectWifi(MI_WLAN_ConnectParam_t *pstConnParam)
{
	if(cfg_enable_wifi==1)
		Wifi_Connect(pstConnParam);
}

void SSTAR_DisconnectWifi()
{
	if(cfg_enable_wifi==1)
		Wifi_Disconnect();
}

int SSTAR_GetWifiEnableStatus()
{
	int ret=0;
	if(cfg_enable_wifi==1)
		ret=Wifi_GetEnableStatus();
	else
		ret=0;
	return ret;
}

void SSTAR_SetWifiEnableStatus(int enable)
{
	if(cfg_enable_wifi==1)
		Wifi_SetEnableStatus(enable);
}

int SSTAR_GetWifiSupportStatus()
{
	int ret=0;

	if(cfg_enable_wifi==1)
		ret = Wifi_GetSupportStatus();
	else
		ret = 0;
	return ret;
}

int SSTAR_GetWifiCurConnStatus(MI_WLAN_Status_t *status)
{
	int ret=0;

	if(cfg_enable_wifi==1)
		ret = Wifi_GetCurConnStatus(status);
	else
		ret = -1;
	return ret;
}

int SSTAR_GetWiredNetworkCurrentStatus()
{
	return 1;
}

int SSTAR_GetUsbCurrentStatus()
{
	return USB_CheckCurrentStatus();
}

void SSTAR_GetUsbPath(char *pUsbPath, int nLen)
{
	USB_GetUsbPath(pUsbPath, nLen);
}

int SSTAR_RegisterWifiStaConnListener(WifiConnCallback pfnCallback)
{
	int ret=-1;

	if(cfg_enable_wifi==1)
		ret = Wifi_RegisterConnectCallback(pfnCallback);
	else
		ret = -1;
	return ret;
}

void SSTAR_UnRegisterWifiStaConnListener(WifiConnCallback pfnCallback)
{
	if(cfg_enable_wifi==1)
		Wifi_UnRegisterConnectCallback(pfnCallback);
}

int SSTAR_RegisterWifiStaScanListener(WifiScanCallback pfnCallback)
{
	int ret=0;
	if(cfg_enable_wifi==1)
		ret = Wifi_RegisterScanCallback(pfnCallback);
	else
		ret = -1;
	return ret;
}

void SSTAR_UnRegisterWifiStaScanListener(WifiScanCallback pfnCallback)
{
	if(cfg_enable_wifi==1)
		Wifi_UnRegisterScanCallback(pfnCallback);
}

int SSTAR_RegisterUsbListener(UsbHotplugCallback pfnCallback)
{
	return USB_RegisterCallback(pfnCallback);
}

void SSTAR_UnRegisterUsbListener(UsbHotplugCallback pfnCallback)
{
	USB_UnRegisterCallback(pfnCallback);
}

int SSTAR_RegisterWiredNetworkListener(NetHotplugCallback pfnCallback)
{
	return WiredNetwork_RegisterCallback(pfnCallback);
}

void SSTAR_UnRegisterWiredNetworkListener(NetHotplugCallback pfnCallback)
{
	WiredNetwork_UnRegisterCallback(pfnCallback);
}



int SSTAR_InitHotplugDetect()
{
	int ret=0;
    Wifi_StartCheckHotplug();
	USB_StartCheckHotplug();
	//WiredNetwork_StartCheckHotplug();
    if(cfg_enable_wifi==1)
		NetPolicy_StartRun(1, 1);
	else
        NetPolicy_StartRun(1, 0);
    //SSTAR_initusb_net();
	sstar_plugin_input_open();
	return 0;
}

int SSTAR_initusb_net()
{
	int ret=0;
	ret=urdev_StartCheckHotplug();
	if(ret!=0)
	{
		printf("uart device process start failed\n");
		urdev_StopCheckHotplug();
	}
	return 0;
}

int SSTAR_deinitusb_net()
{
	urdev_StopCheckHotplug();
	return 0;
}



void SSTAR_DeinitHotPlugDetect()
{
	sstar_plugin_input_close();
    Wifi_StopCheckHotplug();
	USB_StopCheckHotplug();
	//WiredNetwork_StopCheckHotplug();
	NetPolicy_StopRun();
	//SSTAR_deinitusb_net();
}
