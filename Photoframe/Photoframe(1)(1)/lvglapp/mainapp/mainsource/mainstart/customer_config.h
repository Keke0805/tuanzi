#ifndef CUSTOMER_CONFIG_H
#define CUSTOMER_CONFIG_H

#define   SCREEN_HOR_SIZE  1280
#define   SCREEN_VER_SIZE  800

#define DEBUG(fmt, arg...) printf("[DEBUG]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)

#define BG_PNG  "S:/resource/image/bg.png"

#endif // CUSTOMER_CONFIG_H
