#ifndef MEDIALIST_H
#define MEDIALIST_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class medialist
{
public:
    medialist(lv_obj_t *parent = nullptr);
    ~medialist();
    void set_txt(const char * str);
    LvcppButton* txt_list = nullptr;
private:
    void initial(void);
    LvcppScreen* me_screen;
    lv_obj_t* me_parent;
    LvcppFreeTypeFont* myfont=nullptr;
};

#endif // MEDIALIST_H
