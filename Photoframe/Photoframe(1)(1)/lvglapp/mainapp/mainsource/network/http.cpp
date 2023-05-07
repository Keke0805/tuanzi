#include "http.h"

#if 0
    std::string decrypt_text;
    int base64de_len =0;
    int len =0;
    LV_LOG_USER("****src_text******\n%s\n",src_text);
    len =(int)(encrypt_text.length()*3/2+1);
    char *Base64de_text = new char[len];
    memset(Base64de_text, 0, len);
    base64de_len = hv_base64_decode(parameter_txt[0].data,(unsigned int)strlen(parameter_txt[0].data),(unsigned char*)Base64de_text);
    decrypt_text = RsaPriDecrypt(Base64de_text,privateKey);
    LV_LOG_USER("***decrypt_text***\n%s\n",decrypt_text.c_str());
    delete[] Base64de_text;
    Base64de_text =NULL;
    return 0;
#endif

#if 1
char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDXIvie7Vmy1ohwjvy3Lj+BHEri\n"\
    "yUR0gODsnJM5VTHboVieKuvZZH3YyG3aiAGPQpb12yULgMTRWMFodwGDjqU4jldY\n"\
    "yx471646Q+zvaEd9aWfVu2MnT+1doMyBabVu5lPsLav9CKGfcDNnGEBBkQGk1m8z\n"\
    "4TPLoco8uwp2FTi0bwIDAQAB\n"\
    "-----END PUBLIC KEY-----\n";

#else
char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
    "MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAIcwCxH2ZNWTHlAkScqRMxlSREhufqYM\n"\
    "wS5Qkf/sqT49eJAJ07KRKiyi+diswKV1HxDUrNXAfZjvGbN25P9CXysCAwEAAQ==\n"\
    "-----END PUBLIC KEY-----\n";

#endif

char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
    "MIIBVAIBADANBgkqhkiG9w0BAQEFAASCAT4wggE6AgEAAkEAhzALEfZk1ZMeUCRJ\n"\
    "ypEzGVJESG5+pgzBLlCR/+ypPj14kAnTspEqLKL52KzApXUfENSs1cB9mO8Zs3bk\n"\
    "/0JfKwIDAQABAkAOQxFH6dild4nhJpLqXfsoFrfBdHbECeBvhGyCtXL9b9M8REWB\n"\
    "TTc3CRzAZKLduxh+vGHRsGjx121DZkL11vXhAiEA0Tdv+x3FYJn4qZTsnvLpEomI\n"\
    "Zxnr6ujgZVTY+D3ZSHkCIQClatYPLIDTtXU5xV2FW9U0YAR+rXSmvyaCNJKU2ezD\n"\
    "wwIgLF3/R1eW5deBHiVQ0JxexOmZnZOnrhdYjuShZnNnQrECIANIpKk2c/Q/9OzJ\n"\
    "qzqbgRcCFPTC0r8Aqm4JRyOnU9jrAiEAnKnhyZIWBQseCdcl1LzWllkcugdJDCCO\n"\
    "YewhOeU1sGw=\n"\
    "-----END RSA PRIVATE KEY-----\n";

const short monthDays[] ={ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
using namespace std;
Http *httpmsg =NULL;
static void iot_set_userInfo(char *name);

std::string RsaPubEncrypt(const std::string &clear_text, const std::string &pub_key)
{
    std::string encrypt_text;
    BIO *keybio = BIO_new_mem_buf((unsigned char *)pub_key.c_str(), -1);
    RSA* rsa = RSA_new();
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);

    int key_len = RSA_size(rsa);
    int block_len = key_len - 11;

    char *sub_text = new char[key_len + 1];
    memset(sub_text, 0, key_len + 1);
    int ret = 0;
    int pos = 0;
    std::string sub_str;

    while (pos < (int)clear_text.length())
    {
        sub_str = clear_text.substr(pos, block_len);
        memset(sub_text, 0, key_len + 1);
        ret = RSA_public_encrypt(sub_str.length(), (const unsigned char*)sub_str.c_str(), (unsigned char*)sub_text, rsa, RSA_PKCS1_PADDING);
        if (ret >= 0) {
            encrypt_text.append(std::string(sub_text, ret));
        }
        pos += block_len;
    }

    BIO_free_all(keybio);
    RSA_free(rsa);
    delete[] sub_text;
    return encrypt_text;
}

std::string RsaPriDecrypt(const std::string &cipher_text, const std::string &pri_key)
{
    std::string decrypt_text;
    RSA *rsa = RSA_new();
    BIO *keybio;
    keybio = BIO_new_mem_buf((unsigned char *)pri_key.c_str(), -1);

    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    if (rsa == nullptr) {
        unsigned long err = ERR_get_error();
        char err_msg[1024] = { 0 };
        ERR_error_string(err, err_msg);
        printf("err msg: err:%ld, msg:%s\n", err, err_msg);
        return std::string();
    }

    int key_len = RSA_size(rsa);
    char *sub_text = new char[key_len + 1];
    memset(sub_text, 0, key_len + 1);
    int ret = 0;
    std::string sub_str;
    int pos = 0;

    while (pos < (int)cipher_text.length())
    {
        sub_str = cipher_text.substr(pos, key_len);
        memset(sub_text, 0, key_len + 1);
        ret = RSA_private_decrypt(sub_str.length(), (const unsigned char*)sub_str.c_str(), (unsigned char*)sub_text, rsa, RSA_PKCS1_PADDING);
        if (ret >= 0) {
            decrypt_text.append(std::string(sub_text, ret));
            printf("pos:%d, sub: %s\n", pos, sub_text);
            pos += key_len;
        }
    }

    delete[] sub_text;
    BIO_free_all(keybio);
    RSA_free(rsa);
    return decrypt_text;
}

static unsigned char hexchars[] = "0123456789ABCDEF";
static int url_htoi(char *s)
{
    int value;
    int c;

    c = ((unsigned char *)s)[0];
    if (isupper(c))
        c = tolower(c);
    value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

    c = ((unsigned char *)s)[1];
    if (isupper(c))
        c = tolower(c);
    value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

    return (value);
}
char *_url_encode(char const *s, int len, int *new_length)
{
    unsigned char c;
    unsigned char *to, *start;
    unsigned char const *from, *end;

    from = (unsigned char *)s;
    end  = (unsigned char *)s + len;
    start = to = (unsigned char *) calloc(1, 3*len+1);

    while (from < end)
    {
        c = *from++;

        if (c == ' ')
        {
            *to++ = '+';
        }
        else if ((c < '0' && c != '-' && c != '.') ||
                 (c < 'A' && c > '9') ||
                 (c > 'Z' && c < 'a' && c != '_') ||
                 (c > 'z'))
        {
            to[0] = '%';
            to[1] = hexchars[c >> 4];
            to[2] = hexchars[c & 15];
            to += 3;
        }
        else
        {
            *to++ = c;
        }
    }
    *to = 0;
    if (new_length)
    {
        *new_length = to - start;
    }
    return (char *) start;
}

int _url_decode(char *str, int len)
{
    char *dest = str;
    char *data = str;

    while (len--)
    {
        if (*data == '+')
        {
            *dest = ' ';
        }
        else if (*data == '%' && len >= 2 && isxdigit((int) *(data + 1)) && isxdigit((int) *(data + 2)))
        {
            *dest = (char) url_htoi(data + 1);
            data += 2;
            len -= 2;
        }
        else
        {
            *dest = *data;
        }
        data++;
        dest++;
    }
    *dest = '\0';
    return dest - str;
}


int get_file_num(char *path)
{
    int total_file_num = 0;
#ifdef _UCHIP_T113
	DIR *dir = opendir(path);    
	if (dir == NULL)    
	{       
		LV_LOG_USER("opendir:%s",path);        
		return 0;    
	}    
	struct dirent *ptr; 
	while ((ptr = readdir(dir)) != NULL)    
	{             
		char *d_name = ptr->d_name;         
		if (strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0)            
			continue;               
		if (ptr->d_type == DT_DIR)        
		{            
			char new_path[256];                       
			sprintf(new_path, "%s/%s", path, d_name);                       
			total_file_num += get_file_num(new_path);        
		}               
		if (ptr->d_type == DT_REG)        
		{                      
			total_file_num++;        
		}    
	}    
    closedir(dir);
#endif
	return total_file_num;
}

int decode_Zip_file(char *file_url)
{
    int file_num =0;
#ifdef _UCHIP_T113
	ZipArchive za;
	ZipArchive *za_enter;
    int err =-1;

	int i =0;
	char fileName_buff[1024]={0};
	char patch_buff[1024]={0};
	
    err = mzOpenZipArchive(file_url, &za);
    if (err != 0) 
	{
        LV_LOG_USER("failed to open package %s: %s\n",file_url, strerror(err));
        return 0;
    }
	file_num = za.numEntries;
	for(i=0;i<file_num;i++)
	{
		if(za.pEntries !=NULL)
		{
			if(za.pEntries[i].fileName !=NULL)
			{
				memcpy(fileName_buff,za.pEntries[i].fileName,(strlen(za.pEntries[i].fileName)-5));
				LV_LOG_USER("fileName_buff:%s",fileName_buff);
			}	
		}
	}
	za_enter=&za;

	if(za_enter !=NULL) 
	{
        mzCloseZipArchive(za_enter);
		za_enter = NULL;
    }
#endif
	return file_num;
}

char* itoa(int num,char* str,int radix)
{
	char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum;
	int i=0,j,k;
	
    if(radix==10&&num<0)
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else 
		unum=(unsigned)num;

	do
    {
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
 
    }while(unum);
 
    str[i]='\0';

    if(str[0]=='-') k=1;
    else k=0;
 
    char temp;
    for(j=k;j<=(i-1)/2;j++)
    {
		temp=str[j];
		str[j]=str[i-1+k-j];
		str[i-1+k-j]=temp;
    }
    return str;
}

static long long _curtime_to_sec(void)
{
    struct timeval tv;
    long long tv_sec =0;
    long long tv_usec =0;

    gettimeofday(&tv, NULL);
    tv_sec =(long long)tv.tv_sec;
    tv_sec = (long long)(tv_sec*1000);
    tv_usec = (long long)tv.tv_usec;
    tv_usec = (long long)(tv_usec / 1000);
    tv_sec = (long long)(tv_sec + tv_usec);
    return tv_sec;
}

static int _sec_toweek(time_t tv_sec,char *datatime_str)
{
    struct tm tm;
    int y=0,m=0,d=0,week=0;

    localtime_r(&tv_sec,&tm);
    sprintf(datatime_str,"%.4d-%.2d-%.2d-%.2d:%.2d:%.2d",(tm.tm_year + 1900),(tm.tm_mon + 1),tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
    //LV_LOG_USER("%.4d-%.2d-%.2d-%.2d:%.2d:%.2d",(tm.tm_year + 1900),(tm.tm_mon + 1),tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
    y =(tm.tm_year + 1900);
    m =(tm.tm_mon + 1);
    d = tm.tm_mday;
    week =(d+1+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
    //LV_LOG_USER("week:%d",week);
    return week;
}

void Http::Http_get_weather_info(void)
{
#ifdef _UCHIP_T113
	read_int_type_param(WEATHER_SCENE, WEEKCUR, &weatherInfoCur.week);
	read_string_type_param(WEATHER_SCENE, TEMPCUR, tempBuff,sizeof(tempBuff));
	weatherInfoCur.temp = atof(tempBuff);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, TEMPMAXCUR, tempBuff,sizeof(tempBuff));
	weatherInfoCur.temp_max = atof(tempBuff);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, TEMPMINCUR, tempBuff,sizeof(tempBuff));
	weatherInfoCur.temp_min = atof(tempBuff);
	read_int_type_param(WEATHER_SCENE, HUMCUR, &weatherInfoCur.humidity);
	read_int_type_param(WEATHER_SCENE, IDCUR, &weatherInfoCur.id);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, SPEEDCUR, tempBuff,sizeof(tempBuff));
	weatherInfoCur.speed = atof(tempBuff);
	read_string_type_param(WEATHER_SCENE, WEINFCUR, weatherInfoCur.weinfo,sizeof(weatherInfoCur.weinfo));
	read_string_type_param(WEATHER_SCENE, ICONCUR, weatherInfoCur.icon,sizeof(weatherInfoCur.icon));

	read_int_type_param(WEATHER_SCENE, WEEKONE, &weatherInfoFirst.week);
	read_string_type_param(WEATHER_SCENE, TEMPONE, tempBuff,sizeof(tempBuff));
	weatherInfoFirst.temp = atof(tempBuff);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, TEMPMAXONE, tempBuff,sizeof(tempBuff));
	weatherInfoFirst.temp_max = atof(tempBuff);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, TEMPMINONE, tempBuff,sizeof(tempBuff));
	weatherInfoFirst.temp_min = atof(tempBuff);
	read_int_type_param(WEATHER_SCENE, HUMONE, &weatherInfoFirst.humidity);
	read_int_type_param(WEATHER_SCENE, IDONE, &weatherInfoFirst.id);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, SPEEDONE, tempBuff,sizeof(tempBuff));
	weatherInfoFirst.speed = atof(tempBuff);
	read_string_type_param(WEATHER_SCENE, WEINFONE, weatherInfoFirst.weinfo,sizeof(weatherInfoFirst.weinfo));
	read_string_type_param(WEATHER_SCENE, ICONONE, weatherInfoFirst.icon,sizeof(weatherInfoFirst.icon));

	read_int_type_param(WEATHER_SCENE, WEEKTOW, &weatherInfoSecond.week);
	read_string_type_param(WEATHER_SCENE, TEMPTOW, tempBuff,sizeof(tempBuff));
	weatherInfoSecond.temp = atof(tempBuff);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, TEMPMAXTOW, tempBuff,sizeof(tempBuff));
	weatherInfoSecond.temp_max = atof(tempBuff);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, TEMPMINTOW, tempBuff,sizeof(tempBuff));
	weatherInfoSecond.temp_min = atof(tempBuff);
	read_int_type_param(WEATHER_SCENE, HUMTOW, &weatherInfoSecond.humidity);
	read_int_type_param(WEATHER_SCENE, IDTOW, &weatherInfoSecond.id);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, SPEEDTOW, tempBuff,sizeof(tempBuff));
	weatherInfoSecond.speed = atof(tempBuff);
	read_string_type_param(WEATHER_SCENE, WEINFTOW, weatherInfoSecond.weinfo,sizeof(weatherInfoSecond.weinfo));
	read_string_type_param(WEATHER_SCENE, ICONTOW, weatherInfoSecond.icon,sizeof(weatherInfoSecond.icon));

	read_int_type_param(WEATHER_SCENE, WEEKTHREE, &weatherInfoThree.week);
	read_string_type_param(WEATHER_SCENE, TEMPTHREE, tempBuff,sizeof(tempBuff));
	weatherInfoThree.temp = atof(tempBuff);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, TEMPMAXTHREE, tempBuff,sizeof(tempBuff));
	weatherInfoThree.temp_max = atof(tempBuff);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, TEMPMINTHREE, tempBuff,sizeof(tempBuff));
	weatherInfoThree.temp_min = atof(tempBuff);
	read_int_type_param(WEATHER_SCENE, HUMTHREE, &weatherInfoThree.humidity);
	read_int_type_param(WEATHER_SCENE, IDTHREE, &weatherInfoThree.id);
	memset(tempBuff,0,24);
	read_string_type_param(WEATHER_SCENE, SPEEDTHREE, tempBuff,sizeof(tempBuff));
	weatherInfoThree.speed = atof(tempBuff);
	read_string_type_param(WEATHER_SCENE, WEINFTHREE, weatherInfoThree.weinfo,sizeof(weatherInfoThree.weinfo));
	read_string_type_param(WEATHER_SCENE, ICONTHREE, weatherInfoThree.icon,sizeof(weatherInfoThree.icon));   
	memset(fcmToken,0,256);
	read_string_type_param(WEATHER_SCENE, FCMTOKEN, fcmToken,sizeof(fcmToken));
	read_int_type_param(PUBLIC_SCENE, TIMEZONE, &TimeZone);
	read_int_type_param(PUBLIC_SCENE, NETTIME, &ZoneState);
#endif
}

void Http::Http_set_weather_info(int type)
{
#ifdef _UCHIP_T113
	switch(type)
	{
		case 0:
			write_int_type_param(WEATHER_SCENE, WEEKCUR, weatherInfoCur.week);
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoCur.temp);
			write_string_type_param(WEATHER_SCENE, TEMPCUR, tempBuff,sizeof(tempBuff));
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoCur.temp_max);
			write_string_type_param(WEATHER_SCENE, TEMPMAXCUR, tempBuff,sizeof(tempBuff));
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoCur.temp_min);
			write_string_type_param(WEATHER_SCENE, TEMPMINCUR, tempBuff,sizeof(tempBuff));

			write_int_type_param(WEATHER_SCENE, HUMCUR, weatherInfoCur.humidity);
			write_int_type_param(WEATHER_SCENE, IDCUR, weatherInfoCur.id);
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoCur.speed);
			write_string_type_param(WEATHER_SCENE, SPEEDCUR, tempBuff,sizeof(tempBuff));
			write_string_type_param(WEATHER_SCENE, WEINFCUR, weatherInfoCur.weinfo,sizeof(weatherInfoCur.weinfo));
			write_string_type_param(WEATHER_SCENE, ICONCUR, weatherInfoCur.icon,sizeof(weatherInfoCur.icon));
			break;
		case 1:
			write_int_type_param(WEATHER_SCENE, WEEKONE, weatherInfoFirst.week);
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoFirst.temp);
			write_string_type_param(WEATHER_SCENE, TEMPONE, tempBuff,sizeof(tempBuff));
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoFirst.temp_max);
			write_string_type_param(WEATHER_SCENE, TEMPMAXONE, tempBuff,sizeof(tempBuff));
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoFirst.temp_min);
			write_string_type_param(WEATHER_SCENE, TEMPMINONE, tempBuff,sizeof(tempBuff));
			write_int_type_param(WEATHER_SCENE, HUMONE, weatherInfoFirst.humidity);
			write_int_type_param(WEATHER_SCENE, IDONE, weatherInfoFirst.id);
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoFirst.speed);
			write_string_type_param(WEATHER_SCENE, SPEEDONE, tempBuff,sizeof(tempBuff));
			write_string_type_param(WEATHER_SCENE, WEINFONE, weatherInfoFirst.weinfo,sizeof(weatherInfoFirst.weinfo));
			write_string_type_param(WEATHER_SCENE, ICONONE, weatherInfoFirst.icon,sizeof(weatherInfoFirst.icon));
			break;
		case 2:
			write_int_type_param(WEATHER_SCENE, WEEKTOW, weatherInfoSecond.week);
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoSecond.temp);
			write_string_type_param(WEATHER_SCENE, TEMPTOW, tempBuff,sizeof(tempBuff));
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoSecond.temp_max);
			write_string_type_param(WEATHER_SCENE, TEMPMAXTOW, tempBuff,sizeof(tempBuff));
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoSecond.temp_min);
			write_string_type_param(WEATHER_SCENE, TEMPMINTOW, tempBuff,sizeof(tempBuff));
			write_int_type_param(WEATHER_SCENE, HUMTOW, weatherInfoSecond.humidity);
			write_int_type_param(WEATHER_SCENE, IDTOW, weatherInfoSecond.id);;
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoSecond.speed);
			write_string_type_param(WEATHER_SCENE, SPEEDTOW, tempBuff,sizeof(tempBuff));
			write_string_type_param(WEATHER_SCENE, WEINFTOW, weatherInfoSecond.weinfo,sizeof(weatherInfoSecond.weinfo));
			write_string_type_param(WEATHER_SCENE, ICONTOW, weatherInfoSecond.icon,sizeof(weatherInfoSecond.icon));
			break;
		case 3:
			write_int_type_param(WEATHER_SCENE, WEEKTHREE, weatherInfoThree.week);
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoThree.temp);
			write_string_type_param(WEATHER_SCENE, TEMPTHREE, tempBuff,sizeof(tempBuff));
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoThree.temp_max);
			write_string_type_param(WEATHER_SCENE, TEMPMAXTHREE, tempBuff,sizeof(tempBuff));
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoThree.temp_min);
			write_string_type_param(WEATHER_SCENE, TEMPMINTHREE, tempBuff,sizeof(tempBuff));
			write_int_type_param(WEATHER_SCENE, HUMTHREE, weatherInfoThree.humidity);
			write_int_type_param(WEATHER_SCENE, IDTHREE, weatherInfoThree.id);
			memset(tempBuff,0,24);
			sprintf(tempBuff,"%f",weatherInfoThree.speed);
			write_string_type_param(WEATHER_SCENE, SPEEDTHREE, tempBuff,sizeof(tempBuff));
			write_string_type_param(WEATHER_SCENE, WEINFTHREE, weatherInfoThree.weinfo,sizeof(weatherInfoThree.weinfo));
			write_string_type_param(WEATHER_SCENE, ICONTHREE, weatherInfoThree.icon,sizeof(weatherInfoThree.icon));
			break;
		default:
            break;
	}
#endif
}

Http::Http(void)
{
    httpmsg =this;
    httpActiveType =0;
    httpLoginType =0;
	memset(&weatherInfoCur,0,sizeof(weather_info_t));
    memset(&weatherInfoFirst,0,sizeof(weather_info_t));
    memset(&weatherInfoSecond,0,sizeof(weather_info_t));
    memset(&weatherInfoThree,0,sizeof(weather_info_t));
    weatherInfoCur.week =7;
    weatherInfoFirst.week =7;
    weatherInfoSecond.week =7;
    weatherInfoThree.week =7;
#ifdef _UCHIP_T113
    read_string_type_param(WEATHER_SCENE, SERIALADDRESS, serialAddress,sizeof(serialAddress));
    read_string_type_param(WEATHER_SCENE, MACADDRESS, macAddress,sizeof(macAddress));
    read_string_type_param(WEATHER_SCENE, NICKNAME, nickName,sizeof(nickName));
    read_string_type_param(WEATHER_SCENE, CITYNAME, cityName,sizeof(cityName));
	read_string_type_param(WEATHER_SCENE, LATDATA, latDataBuff,sizeof(latDataBuff));
	read_string_type_param(WEATHER_SCENE, LONDATA, lonDataBuff,sizeof(lonDataBuff));
    read_string_type_param(WEATHER_SCENE, COMPANYNAME, companyName,sizeof(companyName));
	LV_LOG_USER("latDataBuff:%s\n",latDataBuff);
	LV_LOG_USER("lonDataBuff:%s\n",lonDataBuff);
	latData = atof(latDataBuff);
	lonData = atof(lonDataBuff);
	read_int_type_param(WEATHER_SCENE, CITYID, &cityId);
	Http_get_weather_info();
#else
    sprintf(serialAddress,"%s","ZXF8FA9D9636A2838A53");//账号a
    sprintf(macAddress,"%s","00:e0:4c:53:3e:bb");//账号a
    sprintf(nickName,"%s","zxf");
    sprintf(cityName,"%s","shenzhen");
    sprintf(companyName,"%s","VPhoto");
    cityId = 2161853;
    latData=22.54679;
    lonData=114.11256;
#endif
	LV_LOG_USER("serialAddress:%s\n",serialAddress);
	LV_LOG_USER("macAddress:%s\n",macAddress);
	LV_LOG_USER("nickName:%s\n",nickName);
	LV_LOG_USER("cityName:%s\n",cityName);
	LV_LOG_USER("cityId:%d\n",cityId);
	printf("latData:%lf\n",latData);
	printf("lonData:%lf\n",lonData);
	LV_LOG_USER("TimeZone:%d  ZoneState:%d",TimeZone,ZoneState);
	
    startTimer(100, this);
}

Http::~Http(void)
{
    if(citylistInfo !=NULL)
    {
        delete[] citylistInfo;
        citylistInfo =NULL;
    }
    if(AzureIotStart != NULL)
    {
        delete AzureIotStart;
        AzureIotStart =NULL;
    }
    httpmsg =NULL;
}

void Http::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;
    timecnt++;

#ifdef _UCHIP_T113
    wifi_data_t wifi;
    connection_status info;
    wmgState networkStatu;
    if((timecnt%10)==0)
    {
        memset(&wifi,0,sizeof(wifi_data_t));
        get_wifi_data(&wifi);
        networkStatu =net_wifi_get_wifi_state();
        //net_wifi_get_mac_adrress(wifi.mac_address,sizeof(wifi.mac_address)-1);
        //LV_LOG_USER("mac_address:%s",wifi.mac_address);
        if(networkStatu ==NETWORK_CONNECTED)
        {
            net_wifi_get_connect_info(wifi.p_wifi_hd,&info);
            wifi.rssi = 100 + info.rssi;
            memcpy(wifi.ssid, info.ssid, strlen(info.ssid));
            if(active_ok!=true)
            {
                //LV_LOG_USER("Http_active_init:%d",active_ok);
				if(ZoneState)
				{
                    //LV_LOG_USER("Http_get_network_time");
                	Http_get_network_time();
				}
                Http_active_init();
            }
        }
        else
        {
            wifi.rssi = 0;
            memset(wifi.ssid, 0, sizeof(wifi.ssid));
        }
        set_wifi_data(&wifi);
    }
#else
    if((timecnt%10)==0)
    {
        if(active_ok!=true)
        {
            Http_get_network_time();
            Http_active_init();
        }
    }
#endif

    if(httpActiveType ==200)
    {
        if(httpActiveTypeNum >10)
        {
            httpActiveTypeNum =0;
            httpActiveType =0;
			httpLoginType =0; 
            Http_dev_login(devId,serialAddress,companyName,NULL);
        }
        httpActiveTypeNum ++;
    }
    else if(httpActiveType !=0)
    {
        httpActiveTypeNum ++;
        if(httpActiveTypeNum >1200)
        {
            httpActiveType =0;
            httpActiveTypeNum =0;
            LV_LOG_USER("*********Http_dev_active again!!!*********");
            Http_dev_active(nickName,NULL);
        }
    }
    else
    {
        if(httpLoginType ==200)
        {
            if(httpLoginTypeNum >10)
            {
                httpLoginType =0;
                httpLoginTypeNum =0;
				IotType =0;
                IotTypeNum =0;
				Http_dev_regist();
                Http_dev_weather(1);
            }
            httpLoginTypeNum ++;
        }
		else if(httpLoginType !=0)
	    {
	        httpLoginTypeNum ++;
	        if(httpLoginTypeNum >1200)
	        {
	            httpLoginType =0;
	            httpLoginTypeNum =0;
                LV_LOG_USER("*********Http_dev_login again!!!*********");
            	Http_dev_login(devId,serialAddress,companyName,NULL);
	        }
	    }
        else
        {
        	if(IotType ==200)
            {
                if(IotTypeNum >10)
                {
                    IotType =0;
                    IotTypeNum =0;
                    devCodeType =0;
					devCodeTypeNum =0;
                    if(AzureIotStart == NULL)
                    {
                        AzureIotStart = new azureIot();
                        AzureIotStart->addReadHook(iot_redata);
                    }
                    Http_dev_cod(devId);
                }
                IotTypeNum ++;
            }
			if(devCodeType ==200)
            {
                if(devCodeTypeNum >10)
                {
                    devCodeTypeNum =0;
                    devCodeType =0;
                    msg_apps_t msg;
                    memset(&msg,0,sizeof(msg));
                    msg.type = msgType;
                    msg.mode = MODE_DEVCODE;
                    SSTAR_SendAsyncMsg(APP_NAME_UI,&msg);
                }
                devCodeTypeNum ++;
            }
            if(devUserType ==200)
            {
                if(devUserTypeNum >10)
                {
                    devUserTypeNum =0;
                    devUserType =0;
                    msg_apps_t msg;
                    memset(&msg,0,sizeof(msg));
                    msg.type = msgType;
                    msg.mode = MODE_DEVUSER;
                    SSTAR_SendAsyncMsg(APP_NAME_UI,&msg);
                }
                devUserTypeNum ++;
            }
            if(httpcityListType ==200)
            {
                if(httpcityListTypeNum >10)
                {
                    httpcityListTypeNum =0;
                    httpcityListType =0;
                    weatherInfoTypeNum =0;
                }
                httpcityListTypeNum ++;
            }
            if(weatherInfoType ==200)
            {
                if(weatherInfoTypeNum >5)
                {
                    weatherInfoTypeNum =0;
                    weatherInfoType =0;
                    msg_apps_t msg;
                    memset(&msg,0,sizeof(msg));
                    msg.type = msgType;
                    msg.mode = MODE_UPDATA;
                    SSTAR_SendAsyncMsg(APP_NAME_UI,&msg);
                }
                weatherInfoTypeNum ++;
            }
			
			if(downStatus == FILE_START)
			{
				LV_LOG_USER("downfileTypeNum:%d",downfileTypeNum);
				if(downfileTypeNum >5)
                {
                    downfileTypeNum =0;
                    Http_downFile();
                }
                downfileTypeNum ++;
			}
			if(devEmailType ==200)
            {
                if(devEmailTypeNum >5)
                {
                    devEmailTypeNum =0;
                    devEmailType =0;
                    get_dev_user();
                }
                devEmailTypeNum ++;
            }
        }
    }
}

int Http::Http_dev_active(char *nickname,char *uuid)
{
    std::string encrypt_text;
    unsigned char* encrypt_ptr = NULL;
    parameter_info_t parameter_txt[4];
    parameter_info_t parameter_buff;
    char *url_buff= NULL;
    char http_buff[1024]={0};
    char sign_buff[34]={0};
    char src_text[128]={0};
    int i=0,j=0;
    int lenth =0;
    int len_text =100;
    int base64_len =0;
    int nickname_len =0;
    int uuid_len =0;

    httpLoginTypeNum =0;
    if((strlen(serialAddress) <20)||(strlen(macAddress) <17))
		return -1;
    for(i=0;i<4;i++)
    {
        memset(parameter_txt[i].name,0,20);
        memset(parameter_txt[i].data,0,512);
    }
    strcpy(parameter_txt[0].name,"device_secret");
    strcpy(parameter_txt[1].name,"device_nickname");
    strcpy(parameter_txt[2].name,"device_uuid");
    strcpy(parameter_txt[3].name,"timestamp");

    if(nickname !=NULL)
    {
        nickname_len =strlen(nickname);
        strcpy(parameter_txt[1].data,nickname);
    }
    if(uuid !=NULL)
    {
        uuid_len =strlen(uuid);
        strcpy(parameter_txt[2].data,uuid);
    }

    len_text = (int)(100 + nickname_len + uuid_len);

    sprintf(src_text,"%s,%s",serialAddress,macAddress);
    encrypt_text = RsaPubEncrypt(src_text, publicKey);
    encrypt_ptr = (unsigned char *)encrypt_text.c_str();
    char *Base64_text = new char[encrypt_text.length()*3/2+1];
    memset(Base64_text, 0, encrypt_text.length()*3/2+1);
    base64_len = hv_base64_encode(encrypt_ptr,encrypt_text.length(),Base64_text);
    strcpy(parameter_txt[0].data,Base64_text);
    delete[] Base64_text;
    Base64_text =NULL;

    len_text +=(base64_len*2);
    sprintf(parameter_txt[3].data,"%lld",_curtime_to_sec());

    for(i=0;i<3;i++)
    {
        for(j=0;j<(3-i);j++)
        {
            if(strcmp(parameter_txt[j].name,parameter_txt[j+1].name)>0)
            {
                memset(parameter_buff.name,0,sizeof(parameter_buff.name));
                memset(parameter_buff.data,0,sizeof(parameter_buff.data));
                strcpy(parameter_buff.name,parameter_txt[j].name);
                strcpy(parameter_buff.data,parameter_txt[j].data);
                strcpy(parameter_txt[j].name,parameter_txt[j+1].name);
                strcpy(parameter_txt[j].data,parameter_txt[j+1].data);
                strcpy(parameter_txt[j+1].name,parameter_buff.name);
                strcpy(parameter_txt[j+1].data,parameter_buff.data);
            }
        }
    }

    char *signMd5Text = new char[len_text];
    memset(signMd5Text, 0, len_text);
    for(i=0;i<4;i++)
    {
        if(strlen(parameter_txt[i].data)>0)
        {
            strcat(signMd5Text,parameter_txt[i].name);
            strcat(signMd5Text,parameter_txt[i].data);
        }
    }
    for(i=0;i<4;i++)
    {
        if(strcmp(parameter_txt[i].name,"device_secret")==0)
        {
            strcat(signMd5Text,parameter_txt[i].data);
        }
    }
    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }
    delete[] signMd5Text;
    signMd5Text =NULL;

    j=0;
    for(i=0;i<3;i++)
    {
        if(strlen(parameter_txt[i].data)>0)
        {
            if(j !=0)
            {
                strcat(http_buff,"&");
            }
            url_buff = _url_encode(parameter_txt[i].name,strlen(parameter_txt[i].name),&lenth);
            strcat(http_buff,url_buff);
            strcat(http_buff,"=");
            free(url_buff);
            url_buff = NULL;
            url_buff = _url_encode(parameter_txt[i].data,strlen(parameter_txt[i].data),&lenth);
            strcat(http_buff,url_buff);
            free(url_buff);
            url_buff = NULL;
            j++;
        }
    }
    Http_dev_active_start((char *)HTTP_ACTIVE,NULL,parameter_txt[3].data,sign_buff,http_buff);
    return 0;
}

static void active_body(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
	char *out =	NULL;
    int ret =0;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
    LV_LOG_USER("*********active*********\n");
    json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        ret =0;
        goto error;
    }
	#if 1
    out=cJSON_Print(json);
    if(out == NULL)
    {
        LV_LOG_USER("cJSON_Print fail !!!");
        goto error;
    }
    else
    {
        cout<<out<<endl;
        free(out);
        out =NULL;
    }
#endif
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        //LV_LOG_USER("status:%d",arrayItem->valueint);
        ret = arrayItem->valueint;
    }
    arrayItem = cJSON_GetObjectItem(json,"data");
    if((arrayItem != NULL)&&(ret ==200))
    {
        item = cJSON_GetObjectItem(arrayItem,"deviceId");
        if(item != NULL)
        {
            //LV_LOG_USER("deviceId:%d",item->valueint);
            sprintf(httpmsg->devId,"%d",item->valueint);
#ifdef _UCHIP_T113
            write_string_type_param(WEATHER_SCENE, DEVID, httpmsg->devId,sizeof(httpmsg->devId));
#endif
        }
        httpmsg->active_status =1;
        httpmsg->active_ok =true;
    }
    else
    {
        httpmsg->active_status =-1;
        httpmsg->active_ok =false;
        LV_LOG_USER("MAIN_HTTP_ACTIVE false");
    }
 error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
   httpmsg->httpActiveType =ret;
}

static void http_dev_active_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            active_body(resp->body);
        }
        else
        {
            httpmsg->active_status =-1;
        }
    }
}

int Http::Http_dev_active_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_POST;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    if(devId !=NULL)
    {
        req->headers["device_id"] = devId;
    }
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    req->content_type = APPLICATION_URLENCODED;
    if(bodyData !=NULL)
    {
        req->body = bodyData;
    }
    //LV_LOG_USER("******url*********\n%s\n",url);
    req->timeout = 10;
    http_client_send_async(req, http_dev_active_cb);
    return 0;
}

int Http::Http_dev_login(char *deviceId,char *devFcmToken,char *cpyName,char *extraInfo)
{
    std::string encrypt_text;
    unsigned char* encrypt_ptr = NULL;
    parameter_info_t parameter_txt[6];
    parameter_info_t parameter_buff;
    char *url_buff= NULL;
    char http_buff[1024]={0};
    char sign_buff[34]={0};
    char src_text[128]={0};
    int i=0,j=0;
    int lenth =0;
    int len_text =144;
    int base64_len =0;
    int extraInfo_len =0;

    httpActiveTypeNum =0;
    if(strlen(cpyName)<=0)
        return -1;

    for(i=0;i<5;i++)
    {
        memset(parameter_txt[i].name,0,20);
        memset(parameter_txt[i].data,0,512);
    }
    strcpy(parameter_txt[0].name,"device_secret");
    strcpy(parameter_txt[1].name,"device_fcm_token");
    strcpy(parameter_txt[2].name,"company_name");
    strcpy(parameter_txt[3].name,"extra_info");
    strcpy(parameter_txt[4].name,"device_id");
    strcpy(parameter_txt[5].name,"timestamp");

    if(extraInfo !=NULL)
    {
        extraInfo_len =strlen(extraInfo);
        strcpy(parameter_txt[3].data,extraInfo);
    }
    len_text = (int)(144 + extraInfo_len);
    len_text +=strlen(devFcmToken);
    strcpy(parameter_txt[1].data,devFcmToken);
    len_text +=strlen(cpyName);
    strcpy(parameter_txt[2].data,cpyName);
    len_text +=strlen(deviceId);
    strcpy(parameter_txt[4].data,deviceId);

    sprintf(src_text,"%s,%s",serialAddress,macAddress);
    encrypt_text = RsaPubEncrypt(src_text, publicKey);
    encrypt_ptr = (unsigned char *)encrypt_text.c_str();
    char *Base64_text = new char[encrypt_text.length()*3/2+1];
    memset(Base64_text, 0, encrypt_text.length()*3/2+1);
    base64_len = hv_base64_encode(encrypt_ptr,encrypt_text.length(),Base64_text);
    strcpy(parameter_txt[0].data,Base64_text);
    delete[] Base64_text;
    Base64_text =NULL;

    len_text +=(base64_len*2);
    sprintf(parameter_txt[5].data,"%lld",_curtime_to_sec());
    for(i=0;i<5;i++)
    {
        for(j=0;j<(5-i);j++)
        {
            if(strcmp(parameter_txt[j].name,parameter_txt[j+1].name)>0)
            {
                memset(parameter_buff.name,0,sizeof(parameter_buff.name));
                memset(parameter_buff.data,0,sizeof(parameter_buff.data));
                strcpy(parameter_buff.name,parameter_txt[j].name);
                strcpy(parameter_buff.data,parameter_txt[j].data);
                strcpy(parameter_txt[j].name,parameter_txt[j+1].name);
                strcpy(parameter_txt[j].data,parameter_txt[j+1].data);
                strcpy(parameter_txt[j+1].name,parameter_buff.name);
                strcpy(parameter_txt[j+1].data,parameter_buff.data);
            }
        }
    }
    char *signMd5Text = new char[len_text];
    memset(signMd5Text, 0, len_text);
    for(i=0;i<6;i++)
    {
        if(strlen(parameter_txt[i].data)>0)
        {
            strcat(signMd5Text,parameter_txt[i].name);
            strcat(signMd5Text,parameter_txt[i].data);
        }
    }
    for(i=0;i<6;i++)
    {
        if(strcmp(parameter_txt[i].name,"device_secret")==0)
        {
            strcat(signMd5Text,parameter_txt[i].data);
        }
    }
    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }
    delete[] signMd5Text;
    signMd5Text =NULL;
    j=0;
    for(i=0;i<5;i++)
    {
        if(strlen(parameter_txt[i].data)>0)
        {
            if(j !=0)
            {
                strcat(http_buff,"&");
            }
            url_buff = _url_encode(parameter_txt[i].name,strlen(parameter_txt[i].name),&lenth);
            strcat(http_buff,url_buff);
            strcat(http_buff,"=");
            free(url_buff);
            url_buff = NULL;
            url_buff = _url_encode(parameter_txt[i].data,strlen(parameter_txt[i].data),&lenth);
            strcat(http_buff,url_buff);
            free(url_buff);
            url_buff = NULL;
            j++;
        }
    }
    Http_dev_login_start((char *)HTTP_LOGIN,deviceId,parameter_txt[5].data,sign_buff,http_buff);
    return 0;
}

static void login_body(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
	cJSON	*arrayjson = NULL;
	cJSON	*item_child = NULL;
	char *out =NULL;
	char *senderBuff =NULL;
	char Buff[64]={0};
	char patchBuff[72]={0};
    char userPatch[64]={0};
	char avatarUrl[128]={0};
    int ret =0,ArrayTotal =0;
    int lenth =0,i=0,userId=0;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
    LV_LOG_USER("*********login*********\n");
    json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        ret =0;
        goto error;
    }
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        //LV_LOG_USER("status:%d",arrayItem->valueint);
        ret = arrayItem->valueint;
    }
    arrayItem = cJSON_GetObjectItem(json,"data");
    if((arrayItem != NULL)&&(ret ==200))
    {
#if 1
	    out=cJSON_Print(json);
	    if(out == NULL)
	    {
	        LV_LOG_USER("cJSON_Print fail !!!");
	        goto error;
	    }
	    else
	    {
	        cout<<out<<endl;
	        free(out);
	        out =NULL;
	    }
#endif
        item = cJSON_GetObjectItem(arrayItem,"device_token");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, DEVICETOKEN, item->valuestring,sizeof(item->valuestring));
#endif
            }
        }
		item = cJSON_GetObjectItem(arrayItem,"deviceNickname");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, DEVNICKNAME, item->valuestring,sizeof(item->valuestring));
#endif
            }
        }
		item = cJSON_GetObjectItem(arrayItem,"email");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, EMAILLINFO, item->valuestring,sizeof(item->valuestring));
#endif
            }
        }
		item = cJSON_GetObjectItem(arrayItem,"android");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, ANDROIDINFO, item->valuestring,sizeof(item->valuestring));
#endif
            }
        }
		item = cJSON_GetObjectItem(arrayItem,"ios");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, IOSINFO, item->valuestring,sizeof(item->valuestring));
#endif
            }
        }
        item = cJSON_GetObjectItem(arrayItem,"deviceEmail");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
                memset(httpmsg->EmailData,0,32);
                sprintf(httpmsg->EmailData,"%s",item->valuestring);
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, EMAILDATA, httpmsg->EmailData,sizeof(httpmsg->EmailData));
#endif
            }
        }
		item = cJSON_GetObjectItem(arrayItem,"ios_download_link");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, IOSLINK, item->valuestring,sizeof(item->valuestring));
#endif
            }
        }
		item = cJSON_GetObjectItem(arrayItem,"android_download_link");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, GOOGLELINK, item->valuestring,sizeof(item->valuestring));
#endif
            }
        }
        item = cJSON_GetObjectItem(arrayItem,"access_token");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
                sprintf(httpmsg->accessToken,"%s",item->valuestring);
#ifdef _UCHIP_T113
                write_string_type_param(WEATHER_SCENE, ACCESSTOKEN, httpmsg->accessToken,sizeof(httpmsg->accessToken));
#endif
            }
        }
		item = cJSON_GetObjectItem(arrayItem,"users");
        if(item != NULL)
        {
			ArrayTotal = cJSON_GetArraySize(item);
			if(ArrayTotal >0)
			{
				for(i=0;i<ArrayTotal;i++)
				{
					arrayjson = cJSON_GetArrayItem(item,i);
		            if(arrayjson != NULL)
		            {
		                item_child = cJSON_GetObjectItem(arrayjson,"id");
		                if(item_child != NULL)
		                {
		                	userId =item_child->valueint;
		                	if(userId >0)
		                	{
#ifdef _UCHIP_T113
		                    	senderBuff = itoa(userId,Buff,10);
					            write_string_userinfo_param(senderBuff,SENDERID,senderBuff,strlen(senderBuff));
					            memset(userPatch,0,64);
					            sprintf(userPatch,"%s/%s",ROOT_PATCH,senderBuff);
					            if(0 != access(userPatch, 0))
					            {
					                mkdir(userPatch, 0777);
					            }
					            iot_set_userInfo(senderBuff);
#endif
		                	}
		                }
						item_child = cJSON_GetObjectItem(arrayjson,"name");
		                if((item_child != NULL)&&(item_child->valuestring != NULL)&&(userId >0))
		                {
#ifdef _UCHIP_T113
            				write_string_userinfo_param(senderBuff,SENDNAME,item_child->valuestring,strlen(item_child->valuestring));
#endif
		                }
						item_child = cJSON_GetObjectItem(arrayjson,"nickname");
		                if((item_child != NULL)&&(item_child->valuestring != NULL)&&(userId >0))
		                {
#ifdef _UCHIP_T113
            				write_string_userinfo_param(senderBuff,SENDERNICKNAME,item_child->valuestring,strlen(item_child->valuestring));
#endif
		                }
						item_child = cJSON_GetObjectItem(arrayjson,"remarkname");
		                if((item_child != NULL)&&(item_child->valuestring != NULL)&&(userId >0))
		                {
#ifdef _UCHIP_T113
            				write_string_userinfo_param(senderBuff,SENDERREMARKNAME,item_child->valuestring,strlen(item_child->valuestring));
#endif 
		                }
						item_child = cJSON_GetObjectItem(arrayjson,"avatar");
		                if((item_child != NULL)&&(item_child->valuestring != NULL)&&(userId >0))
		                {
		                	memset(patchBuff,0,72);
#if 0//#ifdef _UCHIP_T113
							read_string_userinfo_param(senderBuff,SENDERAVATAR,avatarUrl,sizeof(avatarUrl));
							if(strcmp(avatarUrl,item_child->valuestring)!=0)
							{
								sprintf(patchBuff,"%s/%s.png",ROOT_PATCH,senderBuff);
								remove(patchBuff);
								if((0 != access(patchBuff, 0))&&(strlen(item_child->valuestring)>0))
								{
									write_string_downfile_data_param(DOWNFILE_INFO,senderBuff,sizeof(senderBuff),patchBuff,sizeof(patchBuff),item_child->valuestring,strlen(item_child->valuestring));
									write_string_userinfo_param(senderBuff,SENDERAVATAR,item_child->valuestring,strlen(item_child->valuestring));
									if(httpmsg->downStatus ==FILE_STOP)
									{
										httpmsg->downfileTypeNum =0;
										httpmsg->downStatus =FILE_START;
									}
								}
							}
#endif
		                }
		            }
					if(senderBuff !=NULL)
				    {
				        delete[] senderBuff;
				        senderBuff =NULL;
				    }
				}
			}
        }
    }
 error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
   httpmsg->httpLoginType =ret;
}

static void http_dev_login_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            login_body(resp->body);
        }
    }
}

int Http::Http_dev_login_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_POST;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    if(devId !=NULL)
    {
        req->headers["device_id"] = devId;
    }
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    req->content_type = APPLICATION_URLENCODED;
    if(bodyData !=NULL)
    {
        req->body = bodyData;
    }
    //LV_LOG_USER("******url*********\n%s\n",url);
    req->timeout = 10;
    http_client_send_async(req, http_dev_login_cb);
    return 0;
}

int Http::Http_dev_cod(char *deviceId)
{
    parameter_info_t parameter_txt[2];
    char sign_buff[34]={0};
    int i=0;
    int len_text =20;

    if((strlen(accessToken)<=0)||(strlen(deviceId)<=0))
        return -1;
    strcpy(parameter_txt[0].name,"device_id");
    strcpy(parameter_txt[1].name,"timestamp");
    len_text =20 + strlen(accessToken);
    len_text +=strlen(deviceId);
    strcpy(parameter_txt[0].data,deviceId);
    sprintf(parameter_txt[1].data,"%lld",_curtime_to_sec());
    len_text +=strlen(parameter_txt[1].data);

    char *signMd5Text = new char[len_text];
    memset(signMd5Text, 0, len_text);
    for(i=0;i<2;i++)
    {
        strcat(signMd5Text,parameter_txt[i].name);
        strcat(signMd5Text,parameter_txt[i].data);
    }
    strcat(signMd5Text,accessToken);
    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }
    delete[] signMd5Text;
    signMd5Text =NULL;

    Http_dev_cod_start((char *)HTTP_GETCONNECTIONCODE,deviceId,parameter_txt[1].data,sign_buff,NULL);
    return 0;
}
static void _dev_cod_body(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
    int ret =0;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
    //LV_LOG_USER("*********http_buff*********\n%s\n",http_buff);
    json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        ret =0;
        goto error;
    }
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        //LV_LOG_USER("status:%d",arrayItem->valueint);
        ret = arrayItem->valueint;
    }
    arrayItem = cJSON_GetObjectItem(json,"data");
    if((arrayItem != NULL)&&(ret ==200))
    {
        item = cJSON_GetObjectItem(arrayItem,"deviceConnectionCode");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
                memset(httpmsg->devCode,0,24);
                sprintf(httpmsg->devCode,"%s",item->valuestring);
                LV_LOG_USER("devCode:%s\n",httpmsg->devCode);
#ifdef _UCHIP_T113
    			write_string_type_param(WEATHER_SCENE, DEVCODE, httpmsg->devCode,sizeof(httpmsg->devCode));
#endif
            }
        }
    }
 error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
	httpmsg->devCodeType =ret;
}

static void http_dev_cod_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            _dev_cod_body(resp->body);
        }
    }
}

int Http::Http_dev_cod_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_POST;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    if(devId !=NULL)
    {
        req->headers["device_id"] = devId;
    }
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    req->content_type = APPLICATION_URLENCODED;
    if(bodyData !=NULL)
    {
        req->body = bodyData;
    }
    //LV_LOG_USER("******url*********\n%s\n",url);
    req->timeout = 10;
    http_client_send_async(req, http_dev_cod_cb);
    return 0;
}

int Http::Http_dev_user(char *deviceId)
{
    parameter_info_t parameter_txt[2];
    char sign_buff[34]={0};
    int i=0;
    int len_text =20;

    if((strlen(accessToken)<=0)||(strlen(deviceId)<=0))
        return -1;
    strcpy(parameter_txt[0].name,"device_id");
    strcpy(parameter_txt[1].name,"timestamp");
    len_text =20 + strlen(accessToken);
    len_text +=strlen(deviceId);
    strcpy(parameter_txt[0].data,deviceId);
    sprintf(parameter_txt[1].data,"%lld",_curtime_to_sec());
    len_text +=strlen(parameter_txt[1].data);

    char *signMd5Text = new char[len_text];
    memset(signMd5Text, 0, len_text);
    for(i=0;i<2;i++)
    {
        strcat(signMd5Text,parameter_txt[i].name);
        strcat(signMd5Text,parameter_txt[i].data);
    }
    strcat(signMd5Text,accessToken);
    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }
    delete[] signMd5Text;
    signMd5Text =NULL;

    Http_dev_user_start((char *)HTTP_GETDEVICEUSER,deviceId,parameter_txt[1].data,sign_buff,NULL);
    return 0;
}

static void _dev_user_body(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
	cJSON	*arrayjson = NULL;
	cJSON	*item_child = NULL;
	char *out =NULL;
	char *senderBuff =NULL;
	char Buff[64]={0};
	char patchBuff[72]={0};
    char userPatch[64]={0};
    int ret =0,ArrayTotal =0;
    int i=0,userId=0;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
    //LV_LOG_USER("*********http_buff*********\n%s\n",http_buff);
    json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        ret =0;
        goto error;
    }
#if 1
    out=cJSON_Print(json);
    if(out == NULL)
    {
        LV_LOG_USER("cJSON_Print fail !!!");
        goto error;
    }
    else
    {
        cout<<out<<endl;
        free(out);
        out =NULL;
    }
#endif
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        //LV_LOG_USER("status:%d",arrayItem->valueint);
        ret = arrayItem->valueint;
    }
    arrayItem = cJSON_GetObjectItem(json,"data");
    if((arrayItem != NULL)&&(ret ==200))
    {
        item = cJSON_GetObjectItem(arrayItem,"users");
        if(item != NULL)
        {
			ArrayTotal = cJSON_GetArraySize(item);
			if(ArrayTotal >0)
			{
				for(i=0;i<ArrayTotal;i++)
				{
					arrayjson = cJSON_GetArrayItem(item,i);
		            if(arrayjson != NULL)
		            {
		                item_child = cJSON_GetObjectItem(arrayjson,"id");
		                if(item_child != NULL)
		                {
		                	userId =item_child->valueint;
#ifdef _UCHIP_T113
		                	if(userId >0)
		                	{
		                    	senderBuff = itoa(userId,Buff,10);
					            write_string_userinfo_param(senderBuff,SENDERID,senderBuff,strlen(senderBuff));
					            memset(userPatch,0,64);
					            sprintf(userPatch,"%s/%s",ROOT_PATCH,senderBuff);
					            if(0 != access(userPatch, 0))
					            {
					                mkdir(userPatch, 0777);
					            }
					            iot_set_userInfo(senderBuff);
		                	}
#endif
		                }
						item_child = cJSON_GetObjectItem(arrayjson,"name");
					    if((item_child != NULL)&&(item_child->valuestring != NULL)&&(userId >0))
					    {
					        if(item_child->valuestring !=NULL)
					        {
#ifdef _UCHIP_T113
					            write_string_userinfo_param(senderBuff,SENDNAME,item_child->valuestring,strlen(item_child->valuestring));
#endif
					        }
					    }
						item_child = cJSON_GetObjectItem(arrayjson,"nickname");
		                if((item_child != NULL)&&(item_child->valuestring != NULL)&&(userId >0))
		                {
#ifdef _UCHIP_T113
            				write_string_userinfo_param(senderBuff,SENDERNICKNAME,item_child->valuestring,strlen(item_child->valuestring));
#endif
		                }
						item_child = cJSON_GetObjectItem(arrayjson,"remarkname");
		                if((item_child != NULL)&&(item_child->valuestring != NULL)&&(userId >0))
		                {
#ifdef _UCHIP_T113
            				write_string_userinfo_param(senderBuff,SENDERREMARKNAME,item_child->valuestring,strlen(item_child->valuestring));
#endif 
		                }
						item_child = cJSON_GetObjectItem(arrayjson,"avatar");
		                if((item_child != NULL)&&(item_child->valuestring != NULL)&&(userId >0))
		                {
		                	memset(patchBuff,0,72);
#if 0//#ifdef _UCHIP_T113
							sprintf(patchBuff,"%s/%s.png",ROOT_PATCH,senderBuff);
							if((0 != access(patchBuff, 0))&&(strlen(item_child->valuestring)>0))
					        {
								write_string_downfile_data_param(DOWNFILE_INFO,senderBuff,sizeof(senderBuff),patchBuff,sizeof(patchBuff),item_child->valuestring,strlen(item_child->valuestring));
								if(httpmsg->downStatus ==FILE_STOP)
								{
									httpmsg->downfileTypeNum =0;
									httpmsg->downStatus =FILE_START;
								}
							}
#endif
		                }
		            }
					if(senderBuff !=NULL)
				    {
				        delete[] senderBuff;
				        senderBuff =NULL;
				    }
				}
			}
        }
    }
 error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
}

static void http_dev_user_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            _dev_user_body(resp->body);
        }
    }
}

int Http::Http_dev_user_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_POST;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    if(devId !=NULL)
    {
        req->headers["device_id"] = devId;
    }
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    req->content_type = APPLICATION_URLENCODED;
    if(bodyData !=NULL)
    {
        req->body = bodyData;
    }
    //LV_LOG_USER("******url*********\n%s\n",url);
    req->timeout = 10;
    http_client_send_async(req, http_dev_user_cb);
    return 0;
}

int Http::Http_dev_BindByEmail(char *emailData,char *deviceId)
{
    parameter_info_t parameter_txt[4];
    char *url_buff =NULL;
    char signMd5Text[256]={0};
    char http_buff[128]={0};
    char sign_buff[34]={0};
    int i=0,lenth =0;

    if((strlen(accessToken)<=0)||(strlen(deviceId)<=0))
        return -1;
    strcpy(parameter_txt[0].name,"company_name");
    strcpy(parameter_txt[1].name,"device_id");
    strcpy(parameter_txt[2].name,"timestamp");
    strcpy(parameter_txt[3].name,"user_email");
    strcpy(parameter_txt[0].data,"VPhoto");
    strcpy(parameter_txt[1].data,deviceId);
    sprintf(parameter_txt[2].data,"%lld",_curtime_to_sec());
    strcpy(parameter_txt[3].data,emailData);

    memset(signMd5Text, 0, sizeof(signMd5Text));
    for(i=0;i<4;i++)
    {
        strcat(signMd5Text,parameter_txt[i].name);
        strcat(signMd5Text,parameter_txt[i].data);
    }
    strcat(signMd5Text,accessToken);

    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }

    url_buff = _url_encode(parameter_txt[0].name,strlen(parameter_txt[0].name),&lenth);
    strcat(http_buff,url_buff);
    strcat(http_buff,"=");
    free(url_buff);
    url_buff = NULL;
    url_buff = _url_encode(parameter_txt[0].data,strlen(parameter_txt[0].data),&lenth);
    strcat(http_buff,url_buff);
    free(url_buff);
    url_buff = NULL;
    strcat(http_buff,"&");
    url_buff = _url_encode(parameter_txt[3].name,strlen(parameter_txt[3].name),&lenth);
    strcat(http_buff,url_buff);
    strcat(http_buff,"=");
    free(url_buff);
    url_buff = NULL;
    url_buff = _url_encode(parameter_txt[3].data,strlen(parameter_txt[3].data),&lenth);
    strcat(http_buff,url_buff);
    free(url_buff);
    url_buff = NULL;

    Http_dev_BindByEmail_start((char *)HTTP_BINDBYEMAIL,deviceId,parameter_txt[2].data,sign_buff,http_buff);
    return 0;
}

static void _dev_BindByEmail_body(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
	char *out = NULL;
    int ret =-1;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
	json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        goto error;
    }
#if 0
    out=cJSON_Print(json);
    if(out == NULL)
    {
        LV_LOG_USER("cJSON_Print fail !!!");
        goto error;
    }
    else
    {
        cout<<out<<endl;
        free(out);
        out =NULL;
    }
#endif
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        ret = arrayItem->valueint;
    }
error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
    httpmsg->devEmailType =ret;
}

static void http_dev_BindByEmail_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            _dev_BindByEmail_body(resp->body);
        }
        else
        {
        	LV_LOG_USER("*********BindByEmail*********->code:%d\n",resp->status_code);
            httpmsg->devEmailType =-1;
        }
    }
}

int Http::Http_dev_BindByEmail_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_POST;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    if(devId !=NULL)
    {
        req->headers["device_id"] = devId;
    }
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    req->content_type = APPLICATION_URLENCODED;
    if(bodyData !=NULL)
    {
        req->body = bodyData;
    }
    req->timeout = 10;
    http_client_send_async(req, http_dev_BindByEmail_cb);
    return 0;
}

int Http::Http_dev_factory(char *deviceId)
{
    parameter_info_t parameter_txt[2];
    char sign_buff[34]={0};
    int i=0;
    int len_text =20;

    if((strlen(accessToken)<=0)||(strlen(deviceId)<=0))
        return -1;
    strcpy(parameter_txt[0].name,"device_id");
    strcpy(parameter_txt[1].name,"timestamp");
    len_text =20 + strlen(accessToken);
    len_text +=strlen(deviceId);
    strcpy(parameter_txt[0].data,deviceId);
    sprintf(parameter_txt[1].data,"%lld",_curtime_to_sec());
    len_text +=strlen(parameter_txt[1].data);

    char *signMd5Text = new char[len_text];
    memset(signMd5Text, 0, len_text);
    for(i=0;i<2;i++)
    {
        strcat(signMd5Text,parameter_txt[i].name);
        strcat(signMd5Text,parameter_txt[i].data);
    }
    strcat(signMd5Text,accessToken);
    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }
    delete[] signMd5Text;
    signMd5Text =NULL;

    Http_dev_factory_start((char*)HTTP_RESTORFACTORY,deviceId,parameter_txt[1].data,sign_buff,NULL);
    return 0;
}

static void _dev_factory_body(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
    int ret =0;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
    //LV_LOG_USER("*********http_buff*********\n%s\n",http_buff);
    json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        ret =0;
        goto error;
    }
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        //LV_LOG_USER("status:%d",arrayItem->valueint);
        ret = arrayItem->valueint;
    }
    arrayItem = cJSON_GetObjectItem(json,"data");
    if((arrayItem != NULL)&&(ret ==200))
    {
        httpmsg->iot_clean_userInfo();
#ifdef _UCHIP_T113
		clean_string_all_userinfo_param();
		clean_string_all_downfile_data_param();
		sleep(1);
		system("reboot");
#endif
		
    }
 error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
	httpmsg->devFactoryType = ret;
}

static void http_dev_factory_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            _dev_factory_body(resp->body);
        }
		else
		{
			httpmsg->devFactoryType =-1;
		}
    }
}

int Http::Http_dev_factory_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_POST;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    if(devId !=NULL)
    {
        req->headers["device_id"] = devId;
    }
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    req->content_type = APPLICATION_URLENCODED;
    if(bodyData !=NULL)
    {
        req->body = bodyData;
    }
    //LV_LOG_USER("******url*********\n%s\n",url);
    req->timeout = 10;
    http_client_send_async(req, http_dev_factory_cb);
    return 0;
}

void Http::Http_dev_regist(void)
{
    std::string encrypt_text;
    unsigned char* encrypt_ptr = NULL;
    parameter_info_t parameter_txt[5];
    parameter_info_t parameter_buff;
    char *url_buff= NULL;
    char sign_buff[34]={0};
    char src_text[128]={0};
    char body_buff[1024]={0};
    int i=0,j=0,lenth=0;
    int len_text =80;
    int base64_len =0;

    if((strlen(accessToken)<=0)||(strlen(devId)<=0))
        return;
	strcpy(parameter_txt[0].name,"device_secret");
    strcpy(parameter_txt[1].name,"device_id");
    strcpy(parameter_txt[2].name,"id");
    strcpy(parameter_txt[3].name,"fcm_token");
    strcpy(parameter_txt[4].name,"timestamp");

    sprintf(src_text,"%s,%s",serialAddress,macAddress);
    encrypt_text = RsaPubEncrypt(src_text, publicKey);
    encrypt_ptr = (unsigned char *)encrypt_text.c_str();
    char *Base64_text = new char[encrypt_text.length()*3/2+1];
    memset(Base64_text, 0, encrypt_text.length()*3/2+1);
    base64_len = hv_base64_encode(encrypt_ptr,encrypt_text.length(),Base64_text);
    strcpy(parameter_txt[0].data,Base64_text);
    delete[] Base64_text;
    Base64_text =NULL;
    len_text +=strlen(accessToken);
    len_text +=base64_len;
    len_text +=(strlen(devId)*2);
    strcpy(parameter_txt[1].data,devId);
    strcpy(parameter_txt[2].data,devId);
    if(strlen(fcmToken)>0)
    {
        len_text +=strlen(fcmToken);
        strcpy(parameter_txt[3].data,fcmToken);
    }
    sprintf(parameter_txt[4].data,"%lld",_curtime_to_sec());
    for(i=0;i<4;i++)
    {
        for(j=0;j<(4-i);j++)
        {
            if(strcmp(parameter_txt[j].name,parameter_txt[j+1].name)>0)
            {
                memset(parameter_buff.name,0,sizeof(parameter_buff.name));
                memset(parameter_buff.data,0,sizeof(parameter_buff.data));
                strcpy(parameter_buff.name,parameter_txt[j].name);
                strcpy(parameter_buff.data,parameter_txt[j].data);
                strcpy(parameter_txt[j].name,parameter_txt[j+1].name);
                strcpy(parameter_txt[j].data,parameter_txt[j+1].data);
                strcpy(parameter_txt[j+1].name,parameter_buff.name);
                strcpy(parameter_txt[j+1].data,parameter_buff.data);
            }
        }
    }
    char *signMd5Text = new char[len_text];
    memset(signMd5Text, 0, len_text);
    for(i=0;i<5;i++)
    {
        if(strlen(parameter_txt[i].data)>0)
        {
            strcat(signMd5Text,parameter_txt[i].name);
            strcat(signMd5Text,parameter_txt[i].data);
        }
    }
    strcat(signMd5Text,accessToken);
    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }
    delete[] signMd5Text;
    signMd5Text =NULL;
    j=0;
    for(i=0;i<5;i++)
    {
        if(strlen(parameter_txt[i].data)>0)
        {
            if(j !=0)
            {
                strcat(body_buff,"&");
            }
            url_buff = _url_encode(parameter_txt[i].name,strlen(parameter_txt[i].name),&lenth);
            strcat(body_buff,url_buff);
            strcat(body_buff,"=");
            free(url_buff);
            url_buff = NULL;
            url_buff = _url_encode(parameter_txt[i].data,strlen(parameter_txt[i].data),&lenth);
            strcat(body_buff,url_buff);
            free(url_buff);
            url_buff = NULL;
            j++;
        }
    }
    Http_dev_iot_start((char*)HTTP_IOT,devId,parameter_txt[4].data,sign_buff,body_buff);
}

static void iot_body(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
    int ret =0,delen =0;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
    json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        ret =0;
        goto error;
    }
	
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        //LV_LOG_USER("status:%d",arrayItem->valueint);
        ret = arrayItem->valueint;
    }
    arrayItem = cJSON_GetObjectItem(json,"data");
    if((arrayItem != NULL)&&(ret ==200))
    {
    	item = cJSON_GetObjectItem(arrayItem,"fcm_token");
        if(item != NULL)
        {
            if(item->valuestring != NULL)
            {
                memset(httpmsg->fcmToken,0,256);
                delen = _url_decode(item->valuestring,strlen(item->valuestring));
                strcpy(httpmsg->fcmToken,item->valuestring);
                //LV_LOG_USER("fcmToken:%s",httpmsg->fcmToken);
#ifdef _UCHIP_T113
				write_string_type_param(WEATHER_SCENE, FCMTOKEN, httpmsg->fcmToken,sizeof(httpmsg->fcmToken));
#endif
			}
        }
		
    }
 error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
	httpmsg->IotType =ret;
}

static void http_dev_iot_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            iot_body(resp->body);
        }
    }
}

int Http::Http_dev_iot_start(char *url,char *devId,char *timeTp,char *sign,char *bodyData)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_POST;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    if(devId !=NULL)
    {
        req->headers["device_id"] = devId;
    }
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    req->content_type = APPLICATION_URLENCODED;
    if(bodyData !=NULL)
    {
        req->body = bodyData;
    }
    //LV_LOG_USER("******url*********\n%s\n",url);
    req->timeout = 10;
    http_client_send_async(req, http_dev_iot_cb);
    return 0;
}

static void weather_dateinfo(cJSON *json,int timezone,weather_info_t *weInfo)
{
    cJSON *arrayItem = NULL;
    cJSON *item = NULL;
    cJSON *item_child = NULL;
    char datatime[64]={0};
	char weatherPatch[64]={0};
	char buff[64]={0};
	char logo[8]={0};

    arrayItem = cJSON_GetObjectItem(json,"dt");
    if(arrayItem != NULL)
    {
        weInfo->week =_sec_toweek((time_t)(arrayItem->valueint + timezone),datatime);
    }
    arrayItem = cJSON_GetObjectItem(json,"main");
    if(arrayItem != NULL)
    {
        item = cJSON_GetObjectItem(arrayItem,"temp");
        if(item != NULL)
        {
            weInfo->temp =(float)item->valuedouble;
        }
        item = cJSON_GetObjectItem(arrayItem,"temp_max");
        if(item != NULL)
        {
            weInfo->temp_max =(float)item->valuedouble;
        }
        item = cJSON_GetObjectItem(arrayItem,"temp_min");
        if(item != NULL)
        {
            weInfo->temp_min =(float)item->valuedouble;
        }
        item = cJSON_GetObjectItem(arrayItem,"humidity");
        if(item != NULL)
        {
            weInfo->humidity =item->valueint;
        }
    }
    arrayItem = cJSON_GetObjectItem(json,"weather");
    if(arrayItem != NULL)
    {
        if(cJSON_GetArraySize(arrayItem) >0)
        {
            item = cJSON_GetArrayItem(arrayItem,0);
            if(item != NULL)
            {
                item_child = cJSON_GetObjectItem(item,"id");
                if(item_child != NULL)
                {
                    weInfo->id =item_child->valueint;
                }
                item_child = cJSON_GetObjectItem(item,"main");
                if(item_child != NULL)
                {
                    strcpy(weInfo->weinfo,item_child->valuestring);
                }
                item_child = cJSON_GetObjectItem(item,"icon");
                if(item_child != NULL)
                {
                    strcpy(weInfo->icon,item_child->valuestring);
#ifdef _UCHIP_T113
					memset(weatherPatch,0,64);
					sprintf(weatherPatch,"%s%s.png",WEA_PATCH,item_child->valuestring);
					if((0 != access(weatherPatch, 0))&&(strlen(item_child->valuestring)>0))
		            {

						LV_LOG_USER("down logo");
						strcpy(logo,"logo");
						memset(buff,0,64);
						sprintf(buff,"http://wellcdn.waophoto.com/weather/%s.png",item_child->valuestring);
						write_string_downfile_data_param(DOWNFILE_INFO,logo,sizeof(logo),weatherPatch,sizeof(weatherPatch),buff,strlen(buff));
						
						if(httpmsg->downStatus ==FILE_STOP)
						{
							httpmsg->downfileTypeNum =0;
							httpmsg->downStatus =FILE_START;
						}

		            }
#endif
                }
            }
        }
    }
    arrayItem = cJSON_GetObjectItem(json,"wind");
    if(arrayItem != NULL)
    {
        item = cJSON_GetObjectItem(arrayItem,"speed");
        if(item != NULL)
        {
            weInfo->speed =(float)item->valuedouble;
        }
    }
}

static void weather_info(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
    cJSON	*item_child = NULL;
    char *out =NULL;
    int timezone =0;
    int ret =0;
    int i=0,total =0;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
    //LV_LOG_USER("*********http_buff*********\n%s\n",http_buff);
    json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        ret =0;
        goto error;
    }
#if 0
    out=cJSON_Print(json);
    if(out != NULL)
    {
        LV_LOG_USER("*********weatherinfo*********\n%s\n",out);
        free(out);
        out = NULL;
    }
#endif
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        //LV_LOG_USER("status:%d",arrayItem->valueint);
        ret = arrayItem->valueint;
    }
    if(ret !=200)
        goto error;

    arrayItem = cJSON_GetObjectItem(json,"data");
    if((arrayItem != NULL)&&(ret ==200))
    {
        item = cJSON_GetObjectItem(arrayItem,"name");
        if(item != NULL)
        {
            //LV_LOG_USER("name:%s",item->valuestring);
            strcpy(httpmsg->curCityName,item->valuestring);
        }
        item = cJSON_GetObjectItem(arrayItem,"timezone");
        if(item != NULL)
        {
            LV_LOG_USER("timezone:%d",item->valueint);
            //timezone =item->valueint;
        }
        item = cJSON_GetObjectItem(arrayItem,"cur_data");
        if(item != NULL)
        {
            weather_dateinfo(item,timezone,&httpmsg->weatherInfoCur);
			httpmsg->Http_set_weather_info(0);
        }

        item = cJSON_GetObjectItem(arrayItem,"days_data");
        if(item != NULL)
        {
            total =0;
            total = cJSON_GetArraySize(item);
            if(total >0)
            {
                for(i=0;i<3;i++)
                {
                    item_child = cJSON_GetArrayItem(item,i);
                    if(item_child !=NULL)
                    {
                        if(i ==0)
                        {
                            weather_dateinfo(item_child,timezone,&httpmsg->weatherInfoFirst);
                        }
                        else if(i==1)
                        {
                            weather_dateinfo(item_child,timezone,&httpmsg->weatherInfoSecond);
                        }
                        else
                        {
                            weather_dateinfo(item_child,timezone,&httpmsg->weatherInfoThree);
                        }
						httpmsg->Http_set_weather_info(i+1);
                    }
                }
            }
        }
    }

 error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
   httpmsg->weatherInfoType =ret;
}

static void weather_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            weather_info(resp->body);
        }
    }
}

int Http::Http_weather_start(char *url,char *devId,char *timeTp,char *sign)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_GET;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    req->headers["device_id"] = devId;
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    //LV_LOG_USER("*********devId*********\n%s\n",devId);
    //LV_LOG_USER("*********timeTp*********\n%s\n",timeTp);
    //LV_LOG_USER("*********sign*********\n%s\n",sign);
    req->content_type = APPLICATION_XML;
    req->timeout = 10;
    http_client_send_async(req, weather_cb);
    return 0;
}

int Http::Http_dev_weather(int weathertype)
{
    char signMd5Text[512]={0};
    char curTime[24]={0};
    char urlBuff[512]={0};
    char sign_buff[34]={0};
    char dataBuff[32]={0};
    char *url_buff= NULL;
    int lenth =0;

    if((strlen(accessToken)<=0)||(strlen(devId)<=0)||(strlen(cityName)<=0))
        return -1;
    memset(curTime,0,24);
    sprintf(curTime,"%lld",_curtime_to_sec());
    if(weathertype ==0)
    {
        memset(signMd5Text,0,512);
        sprintf(signMd5Text,"city_id%ddevice_id%stimestamp%s%s",cityId,devId,curTime,accessToken);
    }
    else
    {
        memset(signMd5Text,0,512);
        sprintf(signMd5Text,"device_id%slat%flon%ftimestamp%s%s",devId,latData,lonData,curTime,accessToken);
    }
    //LV_LOG_USER("*********signMd5Text*********\n%s\n",signMd5Text);
    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(int i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }
    memset(urlBuff,0,512);
    if(weathertype ==0)
    {
        strcpy(urlBuff,HTTP_CITYIDWEATHER);
        memset(dataBuff,0,32);
        strcpy(dataBuff,"city_id");
        url_buff = _url_encode(dataBuff,strlen(dataBuff),&lenth);
        strcat(urlBuff,url_buff);
        strcat(urlBuff,"=");
        free(url_buff);
        url_buff = NULL;
        memset(dataBuff,0,32);
        sprintf(dataBuff,"%d",cityId);
        url_buff = _url_encode(dataBuff,strlen(dataBuff),&lenth);
        strcat(urlBuff,url_buff);
        free(url_buff);
        url_buff = NULL;
    }
    else
    {
        strcpy(urlBuff,HTTP_CITYLATLON);
        memset(dataBuff,0,32);
        strcpy(dataBuff,"lat");
        url_buff = _url_encode(dataBuff,strlen(dataBuff),&lenth);
        strcat(urlBuff,url_buff);
        strcat(urlBuff,"=");
        free(url_buff);
        url_buff = NULL;
        memset(dataBuff,0,32);
        sprintf(dataBuff,"%f",latData);
        url_buff = _url_encode(dataBuff,strlen(dataBuff),&lenth);
        strcat(urlBuff,url_buff);
        free(url_buff);
        url_buff = NULL;

        strcat(urlBuff,"&");

        memset(dataBuff,0,32);
        strcpy(dataBuff,"lon");
        url_buff = _url_encode(dataBuff,strlen(dataBuff),&lenth);
        strcat(urlBuff,url_buff);
        strcat(urlBuff,"=");
        free(url_buff);
        url_buff = NULL;
        memset(dataBuff,0,32);
        sprintf(dataBuff,"%f",lonData);
        url_buff = _url_encode(dataBuff,strlen(dataBuff),&lenth);
        strcat(urlBuff,url_buff);
        free(url_buff);
        url_buff = NULL;
    }
    //LV_LOG_USER("*********urlBuff*********\n%s\n",urlBuff);
    Http_weather_start(urlBuff,devId,curTime,sign_buff);
    return 0;
}

static void weather_citylist(http_body ret_buff)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
    cJSON	*item_child = NULL;
    int ret =0;
    int i=0,total =0;

    char *http_buff = new char[ret_buff.length()+2];
    memset(http_buff, 0, ret_buff.length()+2);
    mempcpy(http_buff,ret_buff.c_str(),ret_buff.length());
    //LV_LOG_USER("*********http_buff*********\n%s\n",http_buff);
    json=cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        ret =0;
        goto error;
    }
    arrayItem = cJSON_GetObjectItem(json,"status");
    if(arrayItem != NULL)
    {
        //LV_LOG_USER("status:%d",arrayItem->valueint);
        ret = arrayItem->valueint;
    }
    if(ret !=200)
        goto error;

    arrayItem = cJSON_GetObjectItem(json,"data");
    if((arrayItem != NULL)&&(ret ==200))
    {
#if 1
    char *out =NULL;
    out=cJSON_Print(json);  //这个是可以输出的。为获取的整个json的值
    if(out == NULL)
    {
        LV_LOG_USER("cJSON_Print fail !!!");
        goto error;
    }
    else
    {
        cout<<out<<endl;
        free(out);
        out =NULL;
    }
#endif
        total = cJSON_GetArraySize(arrayItem);
        if(total>0)
        {
            if(httpmsg->citylistInfo !=NULL)
            {
                delete[] httpmsg->citylistInfo;
                httpmsg->citylistInfo =NULL;
            }
            httpmsg->citylistInfo = new citylist_info_t[total];
            memset(httpmsg->citylistInfo,0,(sizeof(citylist_info_t)*total));
            for(i=0;i<total;i++)
            {
                item = cJSON_GetArrayItem(arrayItem,i);
                if(item !=NULL)
                {
                    item_child = cJSON_GetObjectItem(item,"name");
                    if(item_child !=NULL)
                    {
                        if(item_child->valuestring !=NULL)
                        {
                            LV_LOG_USER("name:%s",item_child->valuestring);
                            strcpy(httpmsg->citylistInfo[i].name,item_child->valuestring);
                        }
                    }
                    item_child = cJSON_GetObjectItem(item,"qualifiedName");
                    if(item_child !=NULL)
                    {
                        if(item_child->valuestring !=NULL)
                        {
                            LV_LOG_USER("qualifiedName:%s",item_child->valuestring);
                            strcpy(httpmsg->citylistInfo[i].qualifiedName,item_child->valuestring);
                        }
                    }
                    item_child = cJSON_GetObjectItem(item,"lat");
                    if(item_child !=NULL)
                    {
                        httpmsg->citylistInfo[i].lat=item_child->valuedouble;
                    }
                    item_child = cJSON_GetObjectItem(item,"lon");
                    if(item_child !=NULL)
                    {
                        httpmsg->citylistInfo[i].lon=item_child->valuedouble;
                    }
                }
            }
        }
        httpmsg->latData =httpmsg->citylistInfo[0].lat;
        httpmsg->lonData =httpmsg->citylistInfo[0].lon;
    }
 error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
    httpmsg->httpcityListType =ret;
}

static void weather_citylist_cb(HttpResponsePtr resp)
{
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            weather_citylist(resp->body);
        }
    }
}

int Http::Http_weather_citylist_start(char *url,char *devId,char *timeTp,char *sign)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_GET;
    req->url = url;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    req->headers["device_id"] = devId;
    req->headers["timestamp"] = timeTp;
    req->headers["sign"] = sign;
    req->content_type = APPLICATION_XML;
    req->timeout = 10;
    http_client_send_async(req, weather_citylist_cb);
    return 0;
}

int Http::Http_dev_citylist_weather(void)
{
    char signMd5Text[512]={0};
    char curTime[24]={0};
    char urlBuff[512]={0};
    char sign_buff[34]={0};
    char dataBuff[32]={0};
    char *url_buff= NULL;
    int lenth =0;

    if((strlen(accessToken)<=0)||(strlen(devId)<=0)||(strlen(cityName)<=0))
        return -1;
    memset(curTime,0,24);
    sprintf(curTime,"%lld",_curtime_to_sec());

    memset(signMd5Text,0,512);
    sprintf(signMd5Text,"cityName%sdevice_id%stimestamp%s%s",cityName,devId,curTime,accessToken);

    hv_md5_hex((unsigned char*)signMd5Text,strlen(signMd5Text),sign_buff,sizeof(sign_buff));
    for(int i=0;i<(int)strlen(sign_buff);i++)
    {
        if(sign_buff[i]>='a'&&sign_buff[i]<='z')
        {
            sign_buff[i] -= 32;
        }
    }
    memset(urlBuff,0,512);
    strcpy(urlBuff,HTTP_CITYLIST);
    memset(dataBuff,0,32);
    strcpy(dataBuff,"cityName");
    url_buff = _url_encode(dataBuff,strlen(dataBuff),&lenth);
    strcat(urlBuff,url_buff);
    strcat(urlBuff,"=");
    free(url_buff);
    url_buff = NULL;
    url_buff = _url_encode(cityName,strlen(cityName),&lenth);
    strcat(urlBuff,url_buff);
    free(url_buff);
    url_buff = NULL;
    Http_weather_citylist_start(urlBuff,devId,curTime,sign_buff);
    return 0;
}

static int _isLeapYear(int y)
{
    return (((y % 4) == 0) && ((y % 100) != 0)) || ((y % 400) == 0);
}

static int _daysInMonth_Internal(int y, int m)
{
    if ((m == 2) && (_isLeapYear(y) ))
    {
        return 29;
    }
    else
    {
        return monthDays[m];
    }
}

static int dateTime_infon_mon(char *monStr)
{
    if(strcmp(monStr,"Jan")==0)
    {
        return 1;
    }
    else if(strcmp(monStr,"Feb")==0)
    {
        return 2;
    }
    else if(strcmp(monStr,"Mar")==0)
    {
        return 3;
    }
    else if(strcmp(monStr,"Apr")==0)
    {
        return 4;
    }
    else if(strcmp(monStr,"May")==0)
    {
        return 5;
    }
    else if(strcmp(monStr,"Jun")==0)
    {
        return 6;
    }
    else if(strcmp(monStr,"Jul")==0)
    {
        return 7;
    }
    else if(strcmp(monStr,"Aug")==0)
    {
        return 8;
    }
    else if(strcmp(monStr,"Sep")==0)
    {
        return 9;
    }
    else if(strcmp(monStr,"Oct")==0)
    {
        return 10;
    }
    else if(strcmp(monStr,"Nov")==0)
    {
        return 11;
    }
    else if(strcmp(monStr,"Dec")==0)
    {
        return 12;
    }
    return 1;
}
static void dateTime_infon(char *timeStr)
{
    char buff[24]={0};
    int year=0,mon=0,day=0,hour=0,minute=0,second=0;

    memset(buff,0,24);
    strncpy(buff,timeStr+5,2);
    day = atoi(buff);

    memset(buff,0,24);
    strncpy(buff,timeStr+8,3);
    mon = dateTime_infon_mon(buff);

    memset(buff,0,24);
    strncpy(buff,timeStr+12,4);
    year = atoi(buff);

    memset(buff,0,24);
    strncpy(buff,timeStr+17,2);
    hour = atoi(buff);

    memset(buff,0,24);
    strncpy(buff,timeStr+20,2);
    minute = atoi(buff);

    memset(buff,0,24);
    strncpy(buff,timeStr+23,2);
    second = atoi(buff);

    if(httpmsg->ZoneState)
    {
        hour +=httpmsg->TimeZone;
        if(hour >23)
        {
            hour -=24;
            day ++;
            if (day > _daysInMonth_Internal(year, mon))
            {
                day = 1;
                mon++;
                if (mon > 12)
                {
                    mon = 1;
                    year++;
                }
            }
        }
		else if(hour <0)
        {
            hour +=24;
            day --;
            if (day < 1)
            {
                mon--;
                if (mon < 1)
                {
                    mon = 12;
                    year--;
                }
                day = _daysInMonth_Internal(year, mon);
            }
        }
		memset(buff,0,24);
    	sprintf(buff,"date -s \"%.4d-%.2d-%.2d %.2d:%.2d:%.2d\"",year,mon,day,hour,minute,second);
#ifdef _UCHIP_T113
	    system(buff);
#endif
    }
}

static void weather_netTime_cb(HttpResponsePtr resp)
{
    char timeStr[64]={0};
    if(resp ==NULL)
        return;
    memset(timeStr,0,64);
    if(httpmsg !=NULL)
    {
        if(resp->status_code ==200)
        {
            if(!(resp->GetHeader("date")).empty())
            {
                strcpy(timeStr,(resp->GetHeader("date")).data());
                dateTime_infon(timeStr);
            }
        }
        else
        {
            LV_LOG_USER("*********status_code:%d*********\n",resp->status_code);
        }
    }
}

void Http::Http_get_network_time(void)
{
    HttpRequestPtr req(new HttpRequest);
    char urlBuff[128]={0};

    memset(urlBuff,0,128);
    strcpy(urlBuff,"http://vphoto.waophoto.com");
    req->method = HTTP_GET;
    req->url = urlBuff;
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    req->content_type = APPLICATION_XML;
    req->timeout = 10;
    http_client_send_async(req, weather_netTime_cb);
}

static void _get_file_body(http_body ret_buff)
{
	LV_LOG_USER("_get_file_body");
#ifdef _UCHIP_T113
	FILE *fp = NULL;
	char *ext =NULL;
	char type[8]={0};
	char downPatch[132]={0};
	char buff[128]={0};
	int ret =-1;
	int oldNum =0;
	int newNum =0;
	int FileNum =0;
	
	if(ret_buff.length()<=0)
		goto Failed;
	memset(downPatch,0,132);
	sprintf(downPatch,"%s.tmp",httpmsg->downPatch);

	fp = fopen(downPatch, "w+");
	if (!fp) {
		LV_LOG_USER("%s open fail\n", httpmsg->downPatch);
		goto Failed;
	}

	ret = fwrite(ret_buff.c_str(), 1, ret_buff.length(), fp);

	if(fp){
		fsync(fileno(fp));
		fclose(fp);
		fp =NULL;
	}
	
	if(ret == ret_buff.length())
	{
		rename(downPatch,httpmsg->downPatch);
		ext = strrchr(httpmsg->downPatch, '.');
		if(ext !=NULL)
		{
			ext++;
			memset(type,0,8);
			strcpy(type,ext);
			if(strcmp(type,"zip")==0)
			{
				oldNum = get_file_num(httpmsg->downFilePatch);
				sprintf(buff,"unzip -o %s -d %s",httpmsg->downPatch,httpmsg->downFilePatch);
				system(buff);
				//decode_Zip_file(httpmsg->downPatch);
				newNum = get_file_num(httpmsg->downFilePatch);
				remove(httpmsg->downPatch);
				FileNum = newNum - oldNum;
			}
			else
			{
				FileNum =1;
			}
		}
	}
	else
	{
		remove(downPatch);
	}
	system("sync");
	system("sync");
	LV_LOG_USER("FileNum:%d\n", FileNum);
Failed:
	memset(httpmsg->downPatch,0,128);
	memset(httpmsg->downFilePatch,0,128);
	clean_string_downfile_data_param(DOWNFILE_INFO);
	if(check_string_downfile_data_param(DOWNFILE_INFO)==0)
		httpmsg->downStatus= FILE_START;
	else
		httpmsg->downStatus= FILE_STOP;
#endif
}
static void _get_file_cb(HttpResponsePtr resp)
{
	char senderIdBuff[64] ={0};
	char url[256] ={0};
	
    if(resp ==NULL)
        return;
    if(httpmsg !=NULL)
    {
    	LV_LOG_USER("status_code:%d\n", resp->status_code);
        if(resp->status_code ==200)
        {
			_get_file_body(resp->body);
        }
		else
		{
#ifdef _UCHIP_T113
			memset(httpmsg->downPatch,0,128);
			memset(httpmsg->downFilePatch,0,128);
			read_string_downfile_data_param(DOWNFILE_INFO,senderIdBuff,sizeof(senderIdBuff),httpmsg->downPatch,sizeof(httpmsg->downPatch),url,sizeof(url));
			write_string_downfile_data_param(DOWNFILE_INFO,senderIdBuff,sizeof(senderIdBuff),httpmsg->downPatch,sizeof(httpmsg->downPatch),url,sizeof(url));
			clean_string_downfile_data_param(DOWNFILE_INFO);
			httpmsg->downStatus= FILE_START;
#endif
		}
    }
}

int Http::Http_get_file_start(char *url)
{
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_GET;
    req->url = url;
	LV_LOG_USER("url:%s\n", url);
    req->headers["Accept"] = "*/*";
    req->headers["application"] = "keep-alive";
    req->headers["Accept-Encoding"] = "gzip, deflate, br";
    req->content_type = APPLICATION_XML;
    req->timeout = 10;
    http_client_send_async(req, _get_file_cb);
    return 0;
}

bool Http::get_wifi_status(void)
{
    bool ret =true;
#ifdef _UCHIP_T113
    wmgState networkStatu;
    networkStatu =net_wifi_get_wifi_state();
    if(networkStatu !=NETWORK_CONNECTED)
    {
        ret =false;
    }
#endif
    return ret;
}
void Http::Http_downFile(void)
{
#ifdef _UCHIP_T113
	char senderIdBuff[64] ={0};
	char url[256] ={0};
	int ret =-1;
connect:
	LV_LOG_USER("Http_downFile!!!");
	if(get_wifi_status())
    {
    	memset(downPatch,0,128);
		if(read_string_downfile_data_param(DOWNFILE_INFO,senderIdBuff,sizeof(senderIdBuff),downPatch,sizeof(downPatch),url,sizeof(url))<0)
		{
			downStatus =FILE_STOP;
			LV_LOG_USER("read file fail!!!");
			return;
		}
		LV_LOG_USER("senderIdBuff:%s   downPatch:%s  url:%s\n",senderIdBuff,downPatch,url);
		downStatus =FILE_DOWNING;
		if(iot_status_userInfo(senderIdBuff)==0)
		{
			memset(downFilePatch,0,128);
			sprintf(downFilePatch,"%s/%s",ROOT_PATCH,senderIdBuff);
			Http_get_file_start(url);
		}
		else
		{
			LV_LOG_USER("clean_string_downfile_data_param!!!");
			clean_string_downfile_data_param(DOWNFILE_INFO);
			goto connect;
		}
	}
#endif
}
void Http::Http_set_cityName(char *name)
{
    sprintf(cityName,"%s",name);
    httpcityListType =0;
    if(get_wifi_status())
    {
        Http_dev_citylist_weather();
    }
}

void Http::Http_active_init(void)
{
    if(active_status <0)
    {
        LV_LOG_USER("active_status:%d",active_status);
        active_status =0;
        Http_dev_active(nickName,NULL);
    }
}

void Http::Http_get_weather(void)
{
    weatherInfoTypeNum =0;
    weatherInfoType =0;
    LV_LOG_USER("*********Http_get_weather:*********\n");
    if(get_wifi_status())
    {
        Http_dev_weather(1);
    }
}

void Http::get_cur_weather(void *info)
{
    weather_info_t *weInfo =(weather_info_t *)info;
    mempcpy(weInfo,&weatherInfoCur,sizeof(weather_info_t));
}

void Http::get_first_weather(void *info)
{
    weather_info_t *weInfo =(weather_info_t *)info;
    mempcpy(weInfo,&weatherInfoFirst,sizeof(weather_info_t));
}

void Http::get_second_weather(void *info)
{
    weather_info_t *weInfo =(weather_info_t *)info;
    mempcpy(weInfo,&weatherInfoSecond,sizeof(weather_info_t));
}

void Http::get_three_weather(void *info)
{
    weather_info_t *weInfo =(weather_info_t *)info;
    mempcpy(weInfo,&weatherInfoThree,sizeof(weather_info_t));
}

void Http::set_msg_type(msg_type_e type)
{
    msgType =type;
}

void Http::set_TimeZone(int zone)
{
	TimeZone = zone;
#ifdef _UCHIP_T113
    write_int_type_param(PUBLIC_SCENE, TIMEZONE, TimeZone);
#endif	
}

void Http::set_TimeZoneStatus(int type)
{
	ZoneState =type;
#ifdef _UCHIP_T113
    write_int_type_param(PUBLIC_SCENE, NETTIME, ZoneState);
#endif
}

void Http::get_devCod(void)
{
    devCodeType =0;
	devCodeTypeNum =0;
    if(get_wifi_status())
    {
        Http_dev_cod(devId);
    }
}

void Http::set_dev_factory(void)
{
    devFactoryType =0;
	devFactoryTypeNum =0;
    if(get_wifi_status())
    {
        Http_dev_factory(devId);
    }
}

void Http::get_dev_user(void)
{
    devUserType =0;
    devUserTypeNum =0;
    if(get_wifi_status())
    {
        Http_dev_user(devId);
    }
}

void Http::_dev_BindByEmail(char *emailData)
{
    devEmailType =0;
    devEmailTypeNum =0;
    if(get_wifi_status())
    {
        Http_dev_BindByEmail(emailData,devId);
    }
}

void Http::iot_redata(const unsigned char* buff, size_t len)
{
    cJSON	*json = NULL;
    cJSON	*arrayItem = NULL;;
    char *out =NULL;

    char *http_buff = new char[len+2];
    memset(http_buff, 0, len+2);
    mempcpy(http_buff,buff,len);

    json= cJSON_Parse(http_buff);
    if (json == NULL)
    {
        LV_LOG_USER("cJSON_Parset error\n");
        goto error;
    }
#if 1
    out=cJSON_Print(json);
    if(out == NULL)
    {
        LV_LOG_USER("cJSON_Print fail !!!");
        goto error;
    }
    else
    {
        cout<<out<<endl;
        free(out);
        out =NULL;
    }
#endif
    arrayItem = cJSON_GetObjectItem(json,"type");
    if(arrayItem != NULL)
    {
        if(arrayItem->valuestring !=NULL)
        {
            if(strcmp(arrayItem->valuestring,"new user")==0)
            {
                iot_newUser(json);
            }
            else if(strcmp(arrayItem->valuestring,"unbind user")==0)
            {
                iot_unbindUser(json);
            }
            else if(strcmp(arrayItem->valuestring,"image")==0)
            {
                iot_imageUp(json);
            }
            else if(strcmp(arrayItem->valuestring,"video")==0)
            {
                iot_videoUp(json);
            }
            else if(strcmp(arrayItem->valuestring,"update_user_name")==0)
            {
                iot_updateUserName(json);
            }
            else if(strcmp(arrayItem->valuestring,"updateUserProImg")==0)
            {
                updateUserProImg(json);
            }
            else if(strcmp(arrayItem->valuestring,"deleteDeviceUser")==0)
            {
                deleteDeviceUser(json);
            }
        }
    }

error:
    if(json != NULL)
    {
        cJSON_Delete(json);
        json = NULL;
    }
    delete[] http_buff;
    http_buff =NULL;
}

static void iot_set_userInfo(char *name)
{
#ifdef _UCHIP_T113
    char nameInfo[512]={0};
	char nameInfoBuff[512]={0};
    char *token = NULL;
    char line[]={";"};

    if(read_string_type_param(PUBLIC_SCENE,USERINFO,nameInfo,sizeof(nameInfo))==0)
    {
    	memset(nameInfoBuff,0,512);
		memcpy(nameInfoBuff,nameInfo,strlen(nameInfo));
        for(token = strtok(nameInfoBuff, line); token != NULL; token = strtok(NULL, line))
        {
            if(strcmp(name,token)==0)
            {
                return;
            }
        }
        strcat(nameInfo,name);
        strcat(nameInfo,";");
    }
    else
    {
        sprintf(nameInfo,"%s;",name);
    }
	
    write_string_type_param(PUBLIC_SCENE,USERINFO,nameInfo,sizeof(nameInfo));
#endif
}

void Http::iot_remov_userInfo(char *name)
{
#ifdef _UCHIP_T113
    char nameInfo[512]={0};
    char saveNameInfo[512]={0};
    char *token = NULL;
    char line[]={";"};

    if(read_string_type_param(PUBLIC_SCENE,USERINFO,nameInfo,sizeof(nameInfo))==0)
    {
        for(token = strtok(nameInfo, line); token != NULL; token = strtok(NULL, line))
        {
            if(strcmp(name,token)!=0)
            {
                strcat(saveNameInfo,name);
                strcat(saveNameInfo,";");
            }
        }
        write_string_type_param(PUBLIC_SCENE,USERINFO,saveNameInfo,sizeof(saveNameInfo));
    }
#endif
}

void Http::iot_clean_userInfo(void)
{
#ifdef _UCHIP_T113
    char nameInfo[512]={0};
    write_string_type_param(PUBLIC_SCENE,USERINFO,nameInfo,sizeof(nameInfo));
#endif
}

int Http::iot_status_userInfo(char *name)
{
#ifdef _UCHIP_T113
    char nameInfo[512]={0};
    char *token = NULL;
    char line[]={";"};

	if(strcmp(name,"logo")==0)
	{
		return 0;
	}
    if(read_string_type_param(PUBLIC_SCENE,USERINFO,nameInfo,sizeof(nameInfo))==0)
    {
        for(token = strtok(nameInfo, line); token != NULL; token = strtok(NULL, line))
        {
            if(strcmp(name,token)==0)
            {
                return 0;
            }
        }
    }
#endif
    return -1;
}
void Http::iot_newUser(cJSON *json)
{
    cJSON	*arrayItem = NULL;
    char *senderBuff =NULL;
	char Buff[64]={0};
	char patchBuff[72]={0};
    char userPatch[64]={0};
	int senderId =0;

    arrayItem = cJSON_GetObjectItem(json,"sender_id");
    if(arrayItem != NULL)
    {
        if(arrayItem->valueint >0)
        {
#ifdef _UCHIP_T113
			senderId = arrayItem->valueint;
			senderBuff = itoa(senderId,Buff,10);
            write_string_userinfo_param(senderBuff,SENDERID,senderBuff,strlen(senderBuff));
            memset(userPatch,0,64);
            sprintf(userPatch,"%s/%s",ROOT_PATCH,senderBuff);
            if(0 != access(userPatch, 0))
            {
                mkdir(userPatch, 0777);
            }
            iot_set_userInfo(senderBuff);
#endif
        }
    }
	arrayItem = cJSON_GetObjectItem(json,"name");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#ifdef _UCHIP_T113
            write_string_userinfo_param(senderBuff,SENDNAME,arrayItem->valuestring,strlen(arrayItem->valuestring));
#endif
        }
    }
    arrayItem = cJSON_GetObjectItem(json,"sender_remarkname");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#ifdef _UCHIP_T113
            write_string_userinfo_param(senderBuff,SENDERREMARKNAME,arrayItem->valuestring,strlen(arrayItem->valuestring));
#endif
        }
    }
    arrayItem = cJSON_GetObjectItem(json,"sender_nickname");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#ifdef _UCHIP_T113
            write_string_userinfo_param(senderBuff,SENDERNICKNAME,arrayItem->valuestring,strlen(arrayItem->valuestring));
#endif
        }
    }
    arrayItem = cJSON_GetObjectItem(json,"sender_avatar");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
        	memset(patchBuff,0,72);
#if 0//#ifdef _UCHIP_T113
			write_string_userinfo_param(senderBuff,SENDERAVATAR,arrayItem->valuestring,strlen(arrayItem->valuestring));
			sprintf(patchBuff,"%s/%s.png",ROOT_PATCH,senderBuff);
			write_string_downfile_data_param(DOWNFILE_INFO,senderBuff,sizeof(senderBuff),patchBuff,sizeof(patchBuff),arrayItem->valuestring,strlen(arrayItem->valuestring));
			LV_LOG_USER("downStatus:%d",httpmsg->downStatus);
			if(httpmsg->downStatus ==FILE_STOP)
			{
				httpmsg->downfileTypeNum =0;
				httpmsg->downStatus =FILE_START;
			}
#endif
		}
    }
    if(senderBuff !=NULL)
    {
        delete[] senderBuff;
        senderBuff =NULL;
    }
}

void Http::iot_unbindUser(cJSON *json)
{
    cJSON	*arrayItem = NULL;
	char *senderBuff =NULL;
    char Buff[64]={0};
	char pachBuff[128]={0};

    arrayItem = cJSON_GetObjectItem(json,"sender_id");
    if(arrayItem != NULL)
    {
        if(arrayItem->valueint >0)
        {
#ifdef _UCHIP_T113
			senderBuff = itoa(arrayItem->valueint,Buff,10);            
			clean_string_userinfo_param(senderBuff);
            iot_remov_userInfo(senderBuff);
			memset(pachBuff,0,128);
			sprintf(pachBuff,"%s/%s.png",ROOT_PATCH,senderBuff);
			remove(pachBuff);
			system("sync");
			system("sync");
#endif
        }
    }
    if(senderBuff !=NULL)
    {
        delete[] senderBuff;
        senderBuff =NULL;
    }
}

void Http::iot_imageUp(cJSON *json)
{
	cJSON	*arrayItem = NULL;
    char *senderBuff =NULL;
	char Buff[64]={0};
	char userPatch[64]={0};
	char patchBuff[128]={0};
	int senderId =0;

    arrayItem = cJSON_GetObjectItem(json,"sender_id");
    if(arrayItem != NULL)
    {
        if(arrayItem->valueint >0)
        {
#ifdef _UCHIP_T113
			senderId = arrayItem->valueint;
			senderBuff = itoa(senderId,Buff,10);
			memset(userPatch,0,64);
            sprintf(userPatch,"%s/%s",ROOT_PATCH,senderBuff);
            if(0 != access(userPatch, 0))
            {
                mkdir(userPatch, 0777);
            }
#endif
        }
    }
	arrayItem = cJSON_GetObjectItem(json,"file_name");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
        	memset(patchBuff,0,128);
#ifdef _UCHIP_T113
			sprintf(patchBuff,"%s/%s/%s",ROOT_PATCH,senderBuff,arrayItem->valuestring);	
#endif
		}
    }
	arrayItem = cJSON_GetObjectItem(json,"url");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#ifdef _UCHIP_T113
			write_string_downfile_data_param(DOWNFILE_INFO,senderBuff,sizeof(senderBuff),patchBuff,sizeof(patchBuff),arrayItem->valuestring,strlen(arrayItem->valuestring));
			LV_LOG_USER("downStatus:%d",httpmsg->downStatus);
			if(httpmsg->downStatus ==FILE_STOP)
			{
				httpmsg->downfileTypeNum =0;
				httpmsg->downStatus =FILE_START;
			}
#endif
		}
    }
	if(senderBuff !=NULL)
    {
        delete[] senderBuff;
        senderBuff =NULL;
    }
}

void Http::iot_videoUp(cJSON *json)
{
	cJSON	*arrayItem = NULL;
    char *senderBuff =NULL;
	char Buff[64]={0};
	char userPatch[64]={0};
	char patchBuff[128]={0};
	int senderId =0;

    arrayItem = cJSON_GetObjectItem(json,"sender_id");
    if(arrayItem != NULL)
    {
        if(arrayItem->valueint >0)
        {
#ifdef _UCHIP_T113
			senderId = arrayItem->valueint;
			senderBuff = itoa(senderId,Buff,10);
			memset(userPatch,0,64);
            sprintf(userPatch,"%s/%s",ROOT_PATCH,senderBuff);
            if(0 != access(userPatch, 0))
            {
                mkdir(userPatch, 0777);
            }
#endif
        }
    }
	arrayItem = cJSON_GetObjectItem(json,"file_name");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
        	memset(patchBuff,0,128);
#ifdef _UCHIP_T113
			sprintf(patchBuff,"%s/%s/%s",ROOT_PATCH,senderBuff,arrayItem->valuestring);
#endif
        }
    }
	arrayItem = cJSON_GetObjectItem(json,"url");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#ifdef _UCHIP_T113
			write_string_downfile_data_param(DOWNFILE_INFO,senderBuff,sizeof(senderBuff),patchBuff,sizeof(patchBuff),arrayItem->valuestring,strlen(arrayItem->valuestring));
			LV_LOG_USER("downStatus:%d",httpmsg->downStatus);
			if(httpmsg->downStatus ==FILE_STOP)
			{
				httpmsg->downfileTypeNum =0;
				httpmsg->downStatus =FILE_START;
			}
#endif
		}
    }
	if(senderBuff !=NULL)
    {
        delete[] senderBuff;
        senderBuff =NULL;
    }
}

void Http::iot_updateUserName(cJSON *json)
{
    cJSON	*arrayItem = NULL;
    char *senderBuff =NULL;
	char Buff[64]={0};
	int senderId =0;

    arrayItem = cJSON_GetObjectItem(json,"sender_id");
    if(arrayItem != NULL)
    {
        if(arrayItem->valueint >0)
        {
#ifdef _UCHIP_T113
            senderId = arrayItem->valueint;
			senderBuff = itoa(senderId,Buff,10);
            write_string_userinfo_param(senderBuff,SENDERID,senderBuff,strlen(senderBuff));
#endif
        }
    }
	arrayItem = cJSON_GetObjectItem(json,"name");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#ifdef _UCHIP_T113
            write_string_userinfo_param(senderBuff,SENDNAME,arrayItem->valuestring,strlen(arrayItem->valuestring));
#endif
        }
    }
    arrayItem = cJSON_GetObjectItem(json,"sender_remarkname");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#ifdef _UCHIP_T113
            write_string_userinfo_param(senderBuff,SENDERREMARKNAME,arrayItem->valuestring,strlen(arrayItem->valuestring));
#endif
        }
    }
    arrayItem = cJSON_GetObjectItem(json,"sender_nickname");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#ifdef _UCHIP_T113
            write_string_userinfo_param(senderBuff,SENDERNICKNAME,arrayItem->valuestring,strlen(arrayItem->valuestring));
#endif
        }
    }
    if(senderBuff !=NULL)
    {
        delete[] senderBuff;
        senderBuff =NULL;
    }
}

void Http::updateUserProImg(cJSON *json)
{
    cJSON	*arrayItem = NULL;
    char *senderBuff =NULL;
	char Buff[64]={0};
	char patchBuff[128]={0};
	int senderId =0;

    arrayItem = cJSON_GetObjectItem(json,"sender_id");
    if(arrayItem != NULL)
    {
        if(arrayItem->valueint >0)
        {
#ifdef _UCHIP_T113
            senderId = arrayItem->valueint;
			senderBuff = itoa(senderId,Buff,10);
#endif
        }
    }
	arrayItem = cJSON_GetObjectItem(json,"sender_avatar");
    if((arrayItem != NULL)&&(senderId >0))
    {
        if(arrayItem->valuestring !=NULL)
        {
#if 0//#ifdef _UCHIP_T113
			sprintf(patchBuff,"%s/%s.png",ROOT_PATCH,senderBuff);
			remove(patchBuff);
            write_string_userinfo_param(senderBuff,SENDERAVATAR,arrayItem->valuestring,strlen(arrayItem->valuestring));
			write_string_downfile_data_param(DOWNFILE_INFO,senderBuff,sizeof(senderBuff),patchBuff,sizeof(patchBuff),arrayItem->valuestring,strlen(arrayItem->valuestring));
			if(httpmsg->downStatus ==FILE_STOP)
			{
				httpmsg->downfileTypeNum =0;
				httpmsg->downStatus =FILE_START;
			}
#endif
        }
    }
    if(senderBuff !=NULL)
    {
        delete[] senderBuff;
        senderBuff =NULL;
    }
}

void Http::deleteDeviceUser(cJSON *json)
{

}

