#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"


#if QTSIM_PLATFORM==0
#include  "hv/HttpServer.h"
using namespace hv;

class httpserver
{
public:
    httpserver(int port);
    ~httpserver();

    static std::string RespJsontoString(bool flag);
    static int ReqStringtoJsonParse(std::string data);

private:
    static void zp_param_initial(void);
    void http_service_register(void);

    HttpService service;
    HttpServer server;

};

#endif

#endif // HTTPSERVER_H
