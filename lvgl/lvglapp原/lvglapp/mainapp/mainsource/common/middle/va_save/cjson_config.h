#include "lvgl/src/custom/cjson/cJSON.h"
#include "smt_config.h"


typedef struct cjson_config_tag {
    #ifdef _UCHIP_T113
	__u8  valid;
	#endif
	pthread_mutex_t param_mutex;
	char *config_path;
	char *config_contents;
	unsigned int config_size;
} cjson_config_t;
int init_cjson_config(cjson_config_t *config);
int uninit_cjson_config(cjson_config_t *config);
int read_int_type_cjson_config(cjson_config_t *config, char *major, char *minor, int *param);
int write_int_type_cjson_config(cjson_config_t *config, char *major, char *minor, int param);
int read_string_type_cjson_config(cjson_config_t *config, char *major, char *minor, char *str, int len);
int write_string_type_cjson_config(cjson_config_t *config, char *major, char *minor, char *str, int len);
int clean_string_type_cjson_config(cjson_config_t *config, char *major);
int clean_string_type_cjson_all_config(cjson_config_t *config);
int read_string_cjson_config(cjson_config_t *config, char *major,char *minor1,char *str1,int len1,char *minor2,char *str2,int len2,char *minor3,char *str3,int len3);
int write_string_cjson_config(cjson_config_t *config, char *major, char *minor1, char *str1,char *minor2, char *str2, char *minor3, char *str3);
int check_string_cjson_config(cjson_config_t *config, char *major);
int clean_string_cjson_config(cjson_config_t *config, char *major);
int clean_string_cjson_all_config(cjson_config_t *config);