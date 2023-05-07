#ifndef __APP_CONFIG_INTERFACE_H__
#define __APP_CONFIG_INTERFACE_H__

#include "cjson_config.h"

typedef enum {
	CONFIG_PARAM_TYPE_INIT = 0,
	CONFIG_PARAM_TYPE_STRING,
} config_param_type_t;

typedef struct __config_param_tag {
	char				*major;
	char				*minor;
	config_param_type_t type;
	int				val;
	char				*str_config;
} config_param_t;


void app_config_param_init(int reset,config_param_t* config_param,cjson_config_t save_param,
									cjson_config_t userinfo_param,cjson_config_t filedown_param);
int read_int_type_param(char *major, char *minor, int *param);
int write_int_type_param(char *major, char *minor, int param);
int read_string_type_param(char *major, char *minor, char *str, int len);
int write_string_type_param(char *major, char *minor, char *str, int len);
int read_string_userinfo_param(char *major, char *minor, char *str, int len);
int write_string_userinfo_param(char *major, char *minor, char *str, int len);
int clean_string_userinfo_param(char *major);
int clean_string_all_userinfo_param(void);
int check_string_downfile_data_param(char *major);
int clean_string_downfile_data_param(char *major);
int clean_string_all_downfile_data_param(void);

#endif
