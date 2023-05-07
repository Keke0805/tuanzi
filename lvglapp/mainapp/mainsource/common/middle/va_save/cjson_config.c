#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "cjson_config.h"
#ifdef _UCHIP_T113
int init_cjson_config(cjson_config_t *config)
{
	FILE *fp = NULL;
	struct stat buf;

	config->valid = 0;
	pthread_mutex_init(&config->param_mutex, NULL);
	fp = fopen(config->config_path, "r");
	if(!fp) {
		com_warn("%s open fail\n", config->config_path);
		return -1;
	}
	memset(&buf, 0x00, sizeof(buf));
	stat(config->config_path, &buf);
	if (!buf.st_size){
		com_warn("%s size = 0\n", config->config_path);
		fclose(fp);
		return -1;
	}
	config->config_size = buf.st_size;
	config->config_contents = malloc(config->config_size);
	if(!config->config_contents){
		com_warn("malloc %d fail\n", config->config_size);
		fclose(fp);
		return -1;
	}
	fread(config->config_contents, 1, config->config_size, fp);
	fclose(fp);
	config->valid = 1;
	return 0;
}
int read_int_type_cjson_config(cjson_config_t *config, char *major, char *minor, int *param)
{
	int ret = 0;
	cJSON *root = NULL;
	cJSON *tmp_item = NULL;
	cJSON *main_item = NULL;

	pthread_mutex_lock(&config->param_mutex);
	if (!config->valid) {
		com_warn("%s not valid\n", config->config_path);
		ret = -1;
		goto Failed;
	}

	if (!config->config_contents) {
		ret = -1;
		goto Failed;
	}
	root = cJSON_Parse(config->config_contents);
	if (!root) {
		ret = -1;
		goto Failed;
	}

	main_item = cJSON_GetObjectItem(root, major);
	if (!main_item) {
		ret = -1;
		goto Failed;
	}
	tmp_item = cJSON_GetObjectItem(main_item, minor);
	if (!tmp_item) {
		ret = -1;
		goto Failed;
	}
	*param = tmp_item->valueint;
Failed:
	if (root) {
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}
int write_int_type_cjson_config(cjson_config_t *config, char *major, char *minor, int param)
{
	int ret = 0;
	cJSON *root = NULL;
	cJSON *item = NULL;
	cJSON *new_item = NULL;
	char *text = NULL;
	FILE *fp = NULL;

	pthread_mutex_lock(&config->param_mutex);
	if (config->config_contents)
	{
		root = cJSON_Parse(config->config_contents);
		if(!root){
			root = cJSON_CreateObject();
		}
		free(config->config_contents);
		config->config_contents = NULL;
		config->config_size = 0;
	} else {
		root = cJSON_CreateObject();
	}

	item = cJSON_GetObjectItem(root, major);
	if(item)
	{
		cJSON_DeleteItemFromObject(item, minor);
		cJSON_AddNumberToObject(item, minor, param);
	}
	else
	{
		new_item = cJSON_CreateObject();
		cJSON_AddItemToObject(root, major, new_item);
		cJSON_AddNumberToObject(new_item, minor, param);
	}
	text = cJSON_Print(root);
	config->config_contents = text;
	fp = fopen(config->config_path, "w+");
	if (!fp) {
		com_warn("%s open fail\n", config->config_path);
		ret = -1;
		goto Failed;
	}
	config->config_size = strlen(config->config_contents);
	ret = fwrite(config->config_contents, 1, config->config_size, fp);
	ret = 0;
	config->valid = 1;
Failed:

	if (fp) {
		fsync(fileno(fp));
		fclose(fp);
	}
	if(root){
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}
int read_string_type_cjson_config(cjson_config_t *config, char *major, char *minor, char *str, int len)
{
	int ret = 0;
	cJSON *root = NULL;
	cJSON *tmp_item = NULL;
	cJSON *main_item = NULL;

	pthread_mutex_lock(&config->param_mutex);

	if (!config->valid) {
		com_warn("%s not valid\n", config->config_path);
		ret = -1;
		goto Failed;
	}

	if (!config->config_contents) {
		ret = -1;
		goto Failed;
	}
	root = cJSON_Parse(config->config_contents);
	if(!root){
		ret = -1;
		goto Failed;
	}
	main_item = cJSON_GetObjectItem(root, major);
	if (!main_item) {
		ret = -1;
		goto Failed;
	}

	tmp_item = cJSON_GetObjectItem(main_item, minor);
	if(!tmp_item) {
		ret = -1;
		goto Failed;
	}
	if (strlen(tmp_item->valuestring) != 0) {
		memcpy(str, tmp_item->valuestring, strlen(tmp_item->valuestring) > len ? len:strlen(tmp_item->valuestring));
	} else {
		ret = -1;
	}
Failed:
	if (root) {
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int write_string_type_cjson_config(cjson_config_t *config, char *major, char *minor, char *str, int len)
{
	int ret = 0;
	cJSON *root = NULL;
	cJSON *item = NULL;
	cJSON *new_item = NULL;
	char *text = NULL;
	FILE *fp = NULL;

	pthread_mutex_lock(&config->param_mutex);
	if (config->config_contents)
	{
		root = cJSON_Parse(config->config_contents);
		if(!root){
			root = cJSON_CreateObject();
		}
		free(config->config_contents);
		config->config_contents = NULL;
		config->config_size = 0;
	} else {
		root = cJSON_CreateObject();
	}

	item = cJSON_GetObjectItem(root, major);
	if(item)
	{
		cJSON_DeleteItemFromObject(item, minor);
		if (str != NULL) {
			cJSON_AddStringToObject(item, minor, str);
		}
	}
	else
	{
		new_item = cJSON_CreateObject();
		cJSON_AddItemToObject(root, major, new_item);
		if (str != NULL) {
			cJSON_AddStringToObject(new_item, minor, str);
		}
	}
	text = cJSON_Print(root);
	config->config_contents = text;
	fp = fopen(config->config_path, "w+");
	if (!fp) {
		com_warn("%s open fail\n", config->config_path);
		ret = -1;
		goto Failed;
	}
	config->config_size = strlen(config->config_contents);
	ret = fwrite(config->config_contents, 1, config->config_size, fp);
	ret = 0;
	config->valid = 1;
Failed:
	if (fp) {
		fsync(fileno(fp));
		fclose(fp);
	}

	if(root){
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int clean_string_type_cjson_config(cjson_config_t *config, char *major)
{
	int ret = 0;
	cJSON *root = NULL;
	cJSON *item = NULL;
	cJSON *new_item = NULL;
	char *text = NULL;
	FILE *fp = NULL;

	pthread_mutex_lock(&config->param_mutex);
	if (config->config_contents)
	{
		root = cJSON_Parse(config->config_contents);
		if(!root){
			root = cJSON_CreateObject();
		}
		free(config->config_contents);
		config->config_contents = NULL;
		config->config_size = 0;
	} else {
		root = cJSON_CreateObject();
	}

	item = cJSON_GetObjectItem(root, major);
	if(item)
	{
		cJSON_DeleteItemFromObject(root, major);
	}
	text = cJSON_Print(root);
	config->config_contents = text;
	fp = fopen(config->config_path, "w+");
	if (!fp) {
		com_warn("%s open fail\n", config->config_path);
		ret = -1;
		goto Failed;
	}
	config->config_size = strlen(config->config_contents);
	ret = fwrite(config->config_contents, 1, config->config_size, fp);
	ret = 0;
	config->valid = 1;
Failed:
	if (fp) {
		fsync(fileno(fp));
		fclose(fp);
	}

	if(root){
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int clean_string_type_cjson_all_config(cjson_config_t *config)
{
	int ret = 0;
	FILE *fp = NULL;

	pthread_mutex_lock(&config->param_mutex);
	if (config->config_contents)
	{
		free(config->config_contents);
		config->config_contents = NULL;
		config->config_size = 0;
	}
	fp = fopen(config->config_path, "w+");
	if (!fp) {
		com_warn("%s open fail\n", config->config_path);
		ret = -1;
		goto Failed;
	}
	ret = 0;
	config->valid = 0;
Failed:
	if (fp) {
		fsync(fileno(fp));
		fclose(fp);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int read_string_cjson_config(cjson_config_t *config, char *major, char *minor1, 
	char *str1, int len1, char *minor2, char *str2, int len2, char *minor3, char *str3, int len3)
{
	int ret = 0;
	int ArrayNum = 0;
	cJSON *root = NULL;
	cJSON *tmp_item = NULL;
	cJSON *main_item = NULL;
	cJSON *object = NULL;

	pthread_mutex_lock(&config->param_mutex);

	if (!config->valid) {
		com_warn("%s not valid\n", config->config_path);
		ret = -1;
		goto Failed;
	}

	if (!config->config_contents) {
		ret = -1;
		goto Failed;
	}
	root = cJSON_Parse(config->config_contents);
	if(!root){
		ret = -1;
		goto Failed;
	}
	main_item = cJSON_GetObjectItem(root, major);
	if (!main_item) {
		ret = -1;
		goto Failed;
	}
	ArrayNum = cJSON_GetArraySize(main_item);
	if(ArrayNum <=0)
	{
		ret = -1;
		goto Failed;
	}
	object = cJSON_GetArrayItem(main_item,0);
	tmp_item = cJSON_GetObjectItem(object, minor1);
	if(!tmp_item) {
		ret = -1;
		goto Failed;
	}
	if (strlen(tmp_item->valuestring) != 0) {
		memcpy(str1, tmp_item->valuestring, strlen(tmp_item->valuestring) > len1 ? len1:strlen(tmp_item->valuestring));
	} else {
		ret = -1;
	}
	tmp_item = cJSON_GetObjectItem(object, minor2);
	if(!tmp_item) {
		ret = -1;
		goto Failed;
	}
	if (strlen(tmp_item->valuestring) != 0) {
		memcpy(str2, tmp_item->valuestring, strlen(tmp_item->valuestring) > len2 ? len2:strlen(tmp_item->valuestring));
	} else {
		ret = -1;
	}
	tmp_item = cJSON_GetObjectItem(object, minor3);
	if(!tmp_item) {
		ret = -1;
		goto Failed;
	}
	if (strlen(tmp_item->valuestring) != 0) {
		memcpy(str3, tmp_item->valuestring, strlen(tmp_item->valuestring) > len3 ? len3:strlen(tmp_item->valuestring));
	} else {
		ret = -1;
	}
Failed:
	if (root) {
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int write_string_cjson_config(cjson_config_t *config, char *major, char *minor1, 
	char *str1, char *minor2, char *str2, char *minor3, char *str3)
{
	int ret = 0;
	cJSON *root = NULL;
	cJSON *array = NULL;
	cJSON *item = NULL;
	char *text = NULL;
	FILE *fp = NULL;

	pthread_mutex_lock(&config->param_mutex);
	if (config->config_contents)
	{
		root = cJSON_Parse(config->config_contents);
		if(!root){
			root = cJSON_CreateObject();
		}
		free(config->config_contents);
		config->config_contents = NULL;
		config->config_size = 0;
	} else {
		root = cJSON_CreateObject();	
	}
	array = cJSON_GetObjectItem(root, major);
	if (!array) {
		array =  cJSON_CreateArray();
		cJSON_AddItemToObject(root, major, array);
	}
	item = cJSON_CreateObject();
	cJSON_AddStringToObject(item, minor1, str1);
	cJSON_AddStringToObject(item, minor2, str2);
	cJSON_AddStringToObject(item, minor3, str3);
	cJSON_AddItemToArray(array,item);
	text = cJSON_Print(root);
	config->config_contents = text;
	fp = fopen(config->config_path, "w+");
	if (!fp) {
		com_warn("%s open fail\n", config->config_path);
		ret = -1;
		goto Failed;
	}
	config->config_size = strlen(config->config_contents);
	ret = fwrite(config->config_contents, 1, config->config_size, fp);
	ret = 0;
	config->valid = 1;
Failed:
	if (fp) {
		fsync(fileno(fp));
		fclose(fp);
	}

	if(root){
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int check_string_cjson_config(cjson_config_t *config, char *major)
{
	int ret = 0;
	int ArrayNum = 0;
	cJSON *root = NULL;
	cJSON *main_item = NULL;

	pthread_mutex_lock(&config->param_mutex);

	if (!config->valid) {
		com_warn("%s not valid\n", config->config_path);
		ret = -1;
		goto Failed;
	}

	if (!config->config_contents) {
		ret = -1;
		goto Failed;
	}
	root = cJSON_Parse(config->config_contents);
	if(!root){
		ret = -1;
		goto Failed;
	}
	main_item = cJSON_GetObjectItem(root, major);
	if (!main_item) {
		ret = -1;
		goto Failed;
	}
	ArrayNum = cJSON_GetArraySize(main_item);
	if(ArrayNum <=0)
	{
		ret = -1;
		goto Failed;
	}
Failed:
	if (root) {
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int clean_string_cjson_config(cjson_config_t *config, char *major)
{
	int ret = 0,ArrayNum=0;
	cJSON *root = NULL;
	cJSON *array = NULL;
	cJSON *item = NULL;
	char *text = NULL;
	FILE *fp = NULL;
	
	pthread_mutex_lock(&config->param_mutex);
	if (config->config_contents)
	{
		root = cJSON_Parse(config->config_contents);
		if(!root){
			root = cJSON_CreateObject();
		}
		free(config->config_contents);
		config->config_contents = NULL;
		config->config_size = 0;
	} else {
		root = cJSON_CreateObject();
	}
	array = cJSON_GetObjectItem(root, major);
	if (!array) {
		ret = -1;
		goto Failed;
	}
	ArrayNum = cJSON_GetArraySize(array);
	if(ArrayNum <=0)
	{
		ret = -1;
		goto Failed;
	}
	cJSON_DeleteItemFromArray(array,0);
	text = cJSON_Print(root);
	config->config_contents = text;
	fp = fopen(config->config_path, "w+");
	if (!fp) {
		com_warn("%s open fail\n", config->config_path);
		ret = -1;
		goto Failed;
	}
	config->config_size = strlen(config->config_contents);
	ret = fwrite(config->config_contents, 1, config->config_size, fp);
	ret = 0;
	config->valid = 1;
Failed:
	if (fp) {
		fsync(fileno(fp));
		fclose(fp);
	}

	if(root){
		cJSON_Delete(root);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int clean_string_cjson_all_config(cjson_config_t *config)
{
	int ret = 0;
	FILE *fp = NULL;
	
	pthread_mutex_lock(&config->param_mutex);
	if (config->config_contents)
	{
		free(config->config_contents);
		config->config_contents = NULL;
		config->config_size = 0;
	} 
	
	fp = fopen(config->config_path, "w+");
	if (!fp) {
		com_warn("%s open fail\n", config->config_path);
		ret = -1;
		goto Failed;
	}
	ret = 0;
	config->valid = 0;
Failed:
	if (fp) {
		fsync(fileno(fp));
		fclose(fp);
	}
	pthread_mutex_unlock(&config->param_mutex);
	return ret;
}

int uninit_cjson_config(cjson_config_t *config)
{
	pthread_mutex_destroy(&config->param_mutex);
	if (config->config_contents) {
		free(config->config_contents);
	}
	config->valid = 0;
	memset(config, 0x00, sizeof(cjson_config_t));
	return 0;
}
#endif
