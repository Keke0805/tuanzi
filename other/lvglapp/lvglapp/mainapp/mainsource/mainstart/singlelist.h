#ifndef SINGLELIST_H
#define SINGLELIST_H


#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class singlelist
{
public:
     singlelist(lv_obj_t *parent = nullptr);
    ~singlelist();
    void set_txt(const char * str,int index);
    void set_logo_list(int index,int Hlight);
    LvcppButton* txt_list = nullptr;
private:
    void initial(void);
    LvcppScreen* me_screen;
    lv_obj_t* me_parent;
    LvcppFreeTypeFont* myfont=nullptr;
};

#endif // SINGLELIST_H
