#ifndef __APP_CONFIG_INTERFACE_H__
#define __APP_CONFIG_INTERFACE_H__
#include "app_config_param.h"
void va_save_param_init(void);
void va_save_param_uninit(void);
int read_int_type_param(char *major, char *minor, int *param);
int write_int_type_param(char *major, char *minor, int param);
int read_string_type_param(char *major, char *minor, char *str, int len);
int write_string_type_param(char *major, char *minor, char *str, int len);
int read_string_userinfo_param(char *major, char *minor, char *str, int len);
int write_string_userinfo_param(char *major, char *minor, char *str, int len);
int clean_string_userinfo_param(char *major);
int clean_string_all_userinfo_param(void);
int read_string_downfile_data_param(char *major, char *str1, int len1, char *str2, int len2, char *str3, int len3);
int write_string_downfile_data_param(char *major,char *str1, int len1, char *str2, int len2, char *str3, int len3);
int check_string_downfile_data_param(char *major);
int clean_string_downfile_data_param(char *major);
int clean_string_all_downfile_data_param(void);
void app_config_param_init(int reset);
#endif
