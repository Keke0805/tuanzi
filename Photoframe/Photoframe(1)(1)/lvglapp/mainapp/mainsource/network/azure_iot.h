#ifndef AZURE_IOT_H
#define AZURE_IOT_H
#include  "lv_cpp/lvcpp_class.h"

#ifdef _UCHIP_T113
#include  "common/common.h"
#endif

class azureIot
{
public:
    azureIot(void);
    ~azureIot(void);
    char fcmToken[256]={0};
    void addReadHook(void (*hook)(const unsigned char*, size_t));
    void (*mHook)(const unsigned char*, size_t);
private:

};

#endif // AZURE_IOT_H
