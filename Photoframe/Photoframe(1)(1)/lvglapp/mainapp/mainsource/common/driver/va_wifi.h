#ifndef _VA_WIFI_H_
#define _VA_WIFI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "smt_config.h"
#ifdef _UCHIP_T113
#include <wifi_intf.h>
#else
    #define SSID_MAX 64
    typedef void aw_wifi_interface_t;
    enum wmgState{
        NETWORK_CONNECTED = 0x01,
        CONNECTING,
        OBTAINING_IP,
        DISCONNECTED,
        CONNECTED,
        STATE_UNKNOWN,
    };
    typedef struct connection_status {
        char ssid[SSID_MAX];
        char ip_address[32];
        int freq;
        int rssi;
        int link_speed;
        int noise;
    } connection_status;
#endif
/*
**************************************************************************
*							wifi											*
**************************************************************************
*/
#define WIFI_MAX_SCAN_NUM 100
#define WIFI_MAX_SCAN_SIZE 4096
#define WIFI_MAX_SSID_SIZE	48
#define WIFI_MAX_BSSID_SIZE	32
#define WIFI_MAX_PASSWORD_SIZE	48

typedef struct
{
	char ssid[WIFI_MAX_SSID_SIZE];
	int level;
} net_wifi_scan_info_t;

typedef struct
{
	char ssid[WIFI_MAX_SSID_SIZE];
	char bssid[WIFI_MAX_BSSID_SIZE];
	int freq;
	int rssi;
	int speed;
	int noise;
} net_wifi_cur_info_t;

typedef struct {
    aw_wifi_interface_t *p_wifi_hd;
    int event_label;
    int update_flag;

    bool manu_on;	/* 1:on; 0:off */
    bool manu_connected;	/* 1:yes; 0:no */
    char manu_ssid[WIFI_MAX_SSID_SIZE];		/* ssid */
    char manu_password[WIFI_MAX_PASSWORD_SIZE];		/* password */

    bool is_on;	/* 1:on; 0:off */
    bool is_connected;	/* 1:yes; 0:no */
    char ssid[WIFI_MAX_SSID_SIZE];		/* ssid */
    char password[WIFI_MAX_PASSWORD_SIZE];		/* password */
    char mac_address[WIFI_MAX_BSSID_SIZE];		/* MAC address */
    int rssi;	/* level 0-100 */
} wifi_data_t;

void wifi_data_init(void);
void wifi_data_uninit(void);
void set_wifi_data(wifi_data_t *wifi);
void get_wifi_data(wifi_data_t *wifi);

void wifi_manu_param_save(wifi_data_t wifi);

#ifdef _UCHIP_T113
aw_wifi_interface_t *net_wifi_on(int event_label);
int net_wifi_off(aw_wifi_interface_t *p_wifi_hd);
int net_wifi_connect_ap(aw_wifi_interface_t *p_wifi_hd, const char *ssid, const char *passwd, int event_label);
int net_wifi_disconnect_ap(aw_wifi_interface_t *p_wifi_hd, int event_label);
int net_wifi_reconnect_ap(aw_wifi_interface_t *p_wifi_hd, int event_label);
int net_wifi_remove_all_networks(aw_wifi_interface_t *p_wifi_hd);
enum wmgState net_wifi_get_wifi_state();
int net_wifi_get_scan_results(aw_wifi_interface_t *p_wifi_hd, char *scan_results);
int net_wifi_parse_scan_results(net_wifi_scan_info_t *p_scan_info, int num, char *scan_results, int len);
int net_wifi_get_connect_info(aw_wifi_interface_t *p_wifi_hd, connection_status *info);
int net_wifi_is_ap_connected(aw_wifi_interface_t *p_wifi_hd, char *ssid, int *len);
int net_wifi_get_mac_adrress(char *buf, int len);
#endif

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
