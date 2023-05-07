/*
 * urdevhotplug.h
 *
 *  Created on: 2021年5月15日
 *      Author: careyZeng
 */

#ifndef JNI_HOTPLUGDETECT_URDEVDETECTHOTPLUG_H_
#define JNI_HOTPLUGDETECT_URDEVDETECTHOTPLUG_H_


#ifdef  __cplusplus
extern "C"
{
#endif

typedef struct{
	int cmd_or_file;	//1=file 2=cmd
	int cmd_index;		//uart cmd: 1=bg.bmp, 5=命令 6=upg 7=开机交互
	int cur_cmd;		//0：显示bg.png图片   1：关闭背光 2：打开背光    3升级命令 4=删除upg
}urdev_param_t;

int urdev_StartCheckHotplug();
void urdev_StopCheckHotplug();


#ifdef  __cplusplus
}
#endif

#endif /* JNI_HOTPLUGDETECT_URDEVDETECTHOTPLUG_H_ */
