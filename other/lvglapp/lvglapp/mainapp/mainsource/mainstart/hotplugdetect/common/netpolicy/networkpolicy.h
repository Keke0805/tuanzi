/*
 * networkpolicy.h
 *
 *  Created on: 2021Äê8ÔÂ19ÈÕ
 *      Author: careyZeng
 */

#ifndef _NETWORK_POLICY_H_
#define _NETWORK_POLICY_H_


#ifdef  __cplusplus
extern "C"
{
#endif



typedef struct{

}NetPolicy_data_t;

typedef enum{
	NetPolicy_CBMSG_DATA,
	NetPolicy_CBMSG_ERR,
}NetPolicy_cbmsgid_e;

typedef struct{
	NetPolicy_cbmsgid_e type;
	char content[1024];
	int size;
}NetPolicy_cbmsg_t;

enum{
	NET_CFG_STATICIP_SW,
	NET_CFG_IP,
	NET_CFG_GW,
	NET_CFG_NETMASK,
	NET_CFG_DNS1,
	NET_CFG_DNS2,
};

typedef struct{
	int static_ip;
	char mac[20];
	char ip[16];
	char gateway[16];
	char netmask[16];
	char dns1[16];
	char dns2[16];
}NetConfig_t;

typedef void (*NetPolicyCB)(NetPolicy_cbmsg_t *msg);

int NetPolicy_StartRun(int enable_eth, int enable_wifi);
void NetPolicy_StopRun();
int NetPolicy_RegisterNetPolicyCB(NetPolicyCB pfnCB);
void NetPolicy_UnRegisterNetPolicyCB(NetPolicyCB pfnCB);
//update ethernet config
void NetPolicyUpdateEthConfig(int type, char *buf);
//update wireless config
void NetPolicyUpdateWlanConfig(int type, char *buf);
//Confirm update network config
void NetPolicyConfirmUpdateConfig();
//get ethernet config
void NetPolicyGetEthConfig(NetConfig_t *buf);
//get wireless config
void NetPolicyGetWlanConfig(NetConfig_t *buf);
//get ethernet status,-1=unknown,0=plugout,1=plugin
void NetPolicyGetEthStatus(int *sta);
//get wireless status,-1=unknown,0=disconnected,1=connected
void NetPolicyGetWlanStatus(int *sta);


#ifdef  __cplusplus
}
#endif

#endif /* _NETWORK_POLICY_H_ */
