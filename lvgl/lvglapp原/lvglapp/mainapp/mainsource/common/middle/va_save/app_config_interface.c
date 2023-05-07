#include "app_config_interface.h"

static cjson_config_t* va_save_param=NULL;
static cjson_config_t* va_userinfo_param=NULL;
static cjson_config_t* va_filedown_param=NULL;

#ifdef _UCHIP_T113
void va_save_param_init(cjson_config_t* save_param)
{
	va_save_param = save_param;
	init_cjson_config(va_save_param);
}

void va_save_param_uninit(void)
{
	uninit_cjson_config(va_save_param);
}

int read_int_type_param(char *major, char *minor, int *param)
{
	int ret = 0;
	if (strlen(major) == 0 || strlen(minor)==0) {
		com_warn("\n");
		ret = -1;
		goto END;
	}
	*param = 0;

	ret = read_int_type_cjson_config(va_save_param, major, minor, param);
END:
	return ret;
}

int write_int_type_param(char *major, char *minor, int param)
{
	int ret;
	if (strlen(major) == 0 || strlen(minor)==0) {
		com_warn("\n");
		ret = -1;
		goto END;
	}
	ret = write_int_type_cjson_config(va_save_param, major, minor, param);
END:
	return ret;
}

int read_string_type_param(char *major, char *minor, char *str, int len)
{
	int ret;
	if(strlen(major)==0 || strlen(minor)==0 || len<=0) {
		com_warn("\n");
		ret = -1;
		goto END;
	}

	ret = read_string_type_cjson_config(va_save_param,  major, minor, str, len);
END:
	return ret;
}

int write_string_type_param(char *major, char *minor, char *str, int len)
{
	int ret;
	if(strlen(major)==0 || strlen(minor)==0 || len<=0) {
		com_warn("major:%s, minor:%s\n", major, minor);
		ret = -1;
		goto END;
	}
	ret = write_string_type_cjson_config(va_save_param, major, minor, str, len);
END:
	return ret;
}

void va_userinfo_param_init(cjson_config_t* userinfo_param)
{
	va_userinfo_param = userinfo_param;
	init_cjson_config(va_userinfo_param);
}

int read_string_userinfo_param(char *major, char *minor, char *str, int len)
{
	int ret;
	if(strlen(major)==0 || strlen(minor)==0 || len<=0) {
		com_warn("\n");
		ret = -1;
		goto END;
	}

	ret = read_string_type_cjson_config(va_userinfo_param,  major, minor, str, len);
END:
	return ret;
}

int write_string_userinfo_param(char *major, char *minor, char *str, int len)
{
	int ret;
	if(strlen(major)==0 || strlen(minor)==0 || len<=0) {
		com_warn("major:%s, minor:%s\n", major, minor);
		ret = -1;
		goto END;
	}
	ret = write_string_type_cjson_config(va_userinfo_param, major, minor, str, len);
END:
	return ret;
}

int clean_string_userinfo_param(char *major)
{
	int ret;
	if(strlen(major)==0) {
		com_warn("major:%s\n", major);
		ret = -1;
		goto END;
	}
	ret = clean_string_type_cjson_config(va_userinfo_param, major);
END:
	return ret;
}

int clean_string_all_userinfo_param(void)
{
	int ret;
	ret = clean_string_type_cjson_all_config(va_userinfo_param);
END:
	return ret;
}

void va_downfile_data_param_init(cjson_config_t* filedown_param)
{
	va_filedown_param = filedown_param;
	init_cjson_config(va_filedown_param);
}

int check_string_downfile_data_param(char *major)
{
	int ret;
	if(strlen(major)==0 ) {
		com_warn("major:%s\n", major);
		ret = -1;
		goto END;
	}
	ret = check_string_cjson_config(va_filedown_param, major);
END:
	return ret;
}
int clean_string_downfile_data_param(char *major)
{
	int ret;
	if(strlen(major)==0) {
		com_warn("major:%s\n", major);
		ret = -1;
		goto END;
	}
	ret = clean_string_cjson_config(va_filedown_param, major);
END:
	return ret;
}

int clean_string_all_downfile_data_param(void)
{
	int ret;
	ret = clean_string_cjson_all_config(va_filedown_param);
END:
	return ret;
}

static cjson_config_t* va_save_param;
static cjson_config_t* va_userinfo_param;
static cjson_config_t* va_filedown_param;


void app_config_param_init(int reset,config_param_t* config_param,cjson_config_t save_param,
									cjson_config_t userinfo_param,cjson_config_t filedown_param)
{
	int index = 0;

	if (!reset) {
		va_save_param_init(&save_param);
	}

	if (reset || access(save_param.config_path, F_OK) != 0) {
		for (index = 0; index < sizeof(config_param)/sizeof(config_param[0]); index++) {
			if (config_param[index].type == CONFIG_PARAM_TYPE_INIT) {
				write_int_type_param(config_param[index].major, config_param[index].minor, config_param[index].val);
			} else if (config_param[index].type == CONFIG_PARAM_TYPE_STRING) {
				int len = 0;
				if (config_param[index].str_config != NULL) {
					len = strlen(config_param[index].str_config);
				}
				write_string_type_param(config_param[index].major, config_param[index].minor, config_param[index].str_config, len);
			}
		}
	}
	va_userinfo_param_init(&userinfo_param);
	va_downfile_data_param_init(&filedown_param);
}
#endif
