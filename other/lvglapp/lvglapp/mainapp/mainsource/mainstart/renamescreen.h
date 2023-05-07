#ifndef RENAMESCREEN_H
#define RENAMESCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "kbscreen.h"

#if (QTSIM_PLATFORM==0)
#ifdef __cplusplus
extern "C" {
#endif
#include  "mainstart/hotplugdetect/common/applib/applib.h"
#include  "mainstart/hotplugdetect/common/applib/app_config.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif


//box
class RenameboxtScreen
{
public:
    RenameboxtScreen(lv_obj_t* parent=nullptr);
    ~RenameboxtScreen();
    LvcppScreen* mscreen=nullptr;
    void initial(void);
    void BgraToRgb(uint8_t *bgraData,int width,int height,uint8_t*rgbData);
private:
    LvcppFreeTypeFont* myfont=nullptr;

    lv_obj_t* mparent=nullptr;
    LvcppButton *ok_button = nullptr;
    LvcppButton *del_button = nullptr;
    LvcppLabel *tip_label = nullptr;
    static void textarea_event_hander(lv_event_t *event);
};


//fontset
class RenamefontsetScreen
{
public:
    RenamefontsetScreen(lv_obj_t* parent=nullptr);
    ~RenamefontsetScreen();
    LvcppScreen* mscreen=nullptr;
    void initial(void);
    void deinitial(void);
    void manual_font_color(int param_state);
    LvcppLabel *font_x = nullptr;
    LvcppLabel *font_y = nullptr;
    LvcppLabel *font_w = nullptr;
    LvcppLabel *font_h = nullptr;
    LvcppLabel *font_size = nullptr;
    LvcppLabel *font_between = nullptr;
    LvcppDropdown *change_refont_style = nullptr;
    LvcppDropdown *change_refont_form = nullptr;
    LvcppDropdown *change_font_alignment = nullptr;
    LvcppDropdown *change_font_color = nullptr;
    LvcppButton *color_win = nullptr;
    void zp_param_clear(void);
    void  parameter_amplifier(void);//fangda
private:
    LvcppFreeTypeFont* myfont=nullptr;

    lv_obj_t* mparent=nullptr;

    LvcppButton *font_w_up = nullptr;
    LvcppButton *font_W_down = nullptr;
    LvcppLabel *font_w_tip = nullptr;


    LvcppButton *font_h_up = nullptr;
    LvcppButton *font_h_down = nullptr;
    LvcppLabel *font_h_tip = nullptr;


    LvcppButton *font_x_up = nullptr;
    LvcppButton *font_x_down = nullptr;
    LvcppLabel *font_x_tip = nullptr;


    LvcppButton *font_y_up = nullptr;
    LvcppButton *font_y_down = nullptr;
    LvcppLabel *font_y_tip = nullptr;
    LvcppLabel *rename_line = nullptr;

    LvcppLabel *font_effect_tip = nullptr;


    LvcppLabel *border_line = nullptr;


    LvcppButton *font_size_up = nullptr;
    LvcppButton *font_size_down = nullptr;
    LvcppLabel *font_size_tip = nullptr;


    LvcppButton *font_between_up = nullptr;
    LvcppButton *font_between_down = nullptr;
    LvcppLabel *font_between_tip = nullptr;

    LvcppButton *auto_button = nullptr;
    LvcppButton *ok_button = nullptr;
    LvcppButton *del_button = nullptr;
    void font_change_style(int type);
    void change_font_style(int param_state);
    void change_font_name(int param_state);


    static void textarea_event_hander(lv_event_t *event);
};

//bg color
class RenamebgcolorScreen
{
public:
    RenamebgcolorScreen(lv_obj_t* parent=nullptr);
    ~RenamebgcolorScreen();
    LvcppScreen* mscreen=nullptr;
    void initial(void);
    void deinitial(void);
    LvcppLabel * now_color_show = nullptr;
    LvcppLabel *font_R = nullptr;
    LvcppLabel *font_G = nullptr;
    LvcppLabel *font_B = nullptr;
    void get_rgb_vlaue(int param_state);
    uint8_t toByte(char c);
    void hexStringToByte(uint8_t *dstByte,const char *srcHexString ,int len);
private:
    LvcppFreeTypeFont* myfont=nullptr;
    lv_draw_img_dsc_t img_draw_dsc;
    lv_obj_t* mparent=nullptr;
    LvcppLabel * color_tip = nullptr;
    LvcppLabel * color_line = nullptr;
    LvcppButton *   red_color = nullptr;
    LvcppButton *   orange_color = nullptr;
    LvcppButton *   yellow_color = nullptr;
    LvcppButton *   green_color = nullptr;
    LvcppButton *   blue_color = nullptr;
    LvcppButton *   cyan_color = nullptr;
    LvcppButton *   purple_color = nullptr;
    LvcppButton *   black_color = nullptr;
    LvcppButton *   white_color = nullptr;

    int canvas_r=255,canvas_g=0,canvas_b=0;
    int color_type=0;
    int save_r=255,save_g=0,save_b=0;
    LvcppCanvas* canvas=nullptr;
    LvcppCanvas* slide_canvas=nullptr;

    LvcppButton *font_R_up = nullptr;
    LvcppButton *font_R_down = nullptr;
    LvcppLabel *font_R_tip = nullptr;


    LvcppButton *font_G_up = nullptr;
    LvcppButton *font_G_down = nullptr;
    LvcppLabel *font_G_tip = nullptr;


    LvcppButton *font_B_up = nullptr;
    LvcppButton *font_B_down = nullptr;
    LvcppLabel *font_B_tip = nullptr;

    LvcppLabel * now_color_tip = nullptr;

    LvcppButton * ok_button = nullptr;
    LvcppButton * del_button = nullptr;
    lv_color_t* create_canvas(void);
    lv_color_t* create_slide_canvas(void);
    void canvas_reset(int type);

    void rgb_color_palette(int r,int g,int b);
    void auto_rgb_color_palette(void);
    void font_rgb_color_palette(void);
    static void textarea_event_hander(lv_event_t *event);
};



//color
class RenamecolorScreen
{
public:
    RenamecolorScreen(lv_obj_t* parent=nullptr);
    ~RenamecolorScreen();
    LvcppScreen* mscreen=nullptr;
    void initial(void);
    void deinitial(void);
    LvcppLabel * now_color_show = nullptr;
    LvcppLabel *font_R = nullptr;
    LvcppLabel *font_G = nullptr;
    LvcppLabel *font_B = nullptr;
    void get_rgb_vlaue(int param_state);
    uint8_t toByte(char c);
    void hexStringToByte(uint8_t *dstByte,const char *srcHexString ,int len);
private:
    LvcppFreeTypeFont* myfont=nullptr;
    lv_draw_img_dsc_t img_draw_dsc;
    lv_obj_t* mparent=nullptr;
    LvcppLabel * color_tip = nullptr;
    LvcppLabel * color_line = nullptr;
    LvcppButton *   red_color = nullptr;
    LvcppButton *   orange_color = nullptr;
    LvcppButton *   yellow_color = nullptr;
    LvcppButton *   green_color = nullptr;
    LvcppButton *   blue_color = nullptr;
    LvcppButton *   cyan_color = nullptr;
    LvcppButton *   purple_color = nullptr;
    LvcppButton *   black_color = nullptr;
    LvcppButton *   white_color = nullptr;

    int canvas_r=0,canvas_g=0,canvas_b=0;
    int color_type=0;
    int save_r=0,save_g=0,save_b=0;
    LvcppCanvas* canvas=nullptr;
    LvcppCanvas* slide_canvas=nullptr;

    LvcppButton *font_R_up = nullptr;
    LvcppButton *font_R_down = nullptr;
    LvcppLabel *font_R_tip = nullptr;


    LvcppButton *font_G_up = nullptr;
    LvcppButton *font_G_down = nullptr;
    LvcppLabel *font_G_tip = nullptr;


    LvcppButton *font_B_up = nullptr;
    LvcppButton *font_B_down = nullptr;
    LvcppLabel *font_B_tip = nullptr;

    LvcppLabel * now_color_tip = nullptr;

    LvcppButton * ok_button = nullptr;
    LvcppButton * del_button = nullptr;
    lv_color_t* create_canvas(void);
    lv_color_t* create_slide_canvas(void);
    void canvas_reset(int type);

    void rgb_color_palette(int r,int g,int b);
    void auto_rgb_color_palette(void);
    void font_rgb_color_palette(int param);
    static void textarea_event_hander(lv_event_t *event);
};

//左上
class RenameheadScreen
{
public:
    RenameheadScreen(lv_obj_t* parent=nullptr);
    ~RenameheadScreen();
    LvcppScreen* mscreen=nullptr;
    void initial(void);
    void deinitial(void);
    void label_bg_change(int r,int g,int b);
    LvcppLabel * usre_param_label = nullptr;
    LvcppLabel * usre_company_label = nullptr;
    LvcppLabel * usre_duty_label = nullptr;
    void kb_create(void);
    static void kb_cb(void);
    kbscreen *input_kb = nullptr;
    void get_kbinput_text(void);
    void param_change(int param);
    void pos_update(void);
    void Parameter_reduction(void);//suo xiao

private:
    LvcppFreeTypeFont* myfont=nullptr;
    lv_obj_t* mparent=nullptr;
    void Cursor_switching(void);
    static void textarea_event_hander(lv_event_t *event);
};

//左下
class RenamebottomScreen
{
public:
    RenamebottomScreen(lv_obj_t* parent=nullptr);
    ~RenamebottomScreen();
    LvcppScreen* mscreen=nullptr;
    void initial(void);
    void deinitial(void);
    void set_bg_img(void);
    LvcppDropdown * select_photo_bg = nullptr;
    LvcppButton * select_rgb_bg = nullptr;
private:
    LvcppFreeTypeFont* myfont=nullptr;

    lv_obj_t* mparent=nullptr;
    LvcppLabel *function_tip = nullptr;
    LvcppLabel *rename_line = nullptr;
    LvcppLabel *color_tip =nullptr;
    LvcppLabel *photo_tip = nullptr;
    LvcppButton *change_pos = nullptr;



    void manual_bg_color(void);

    static void textarea_event_hander(lv_event_t *event);
};

//右上
class RenameinputScreen
{
public:
    RenameinputScreen(lv_obj_t* parent=nullptr);
    ~RenameinputScreen();
    LvcppScreen* mscreen=nullptr;
    void initial(void);
    void deinitial(void);
    LvcppButton * usre_param = nullptr;
    LvcppButton * usre_company = nullptr;
    LvcppButton * usre_duty = nullptr;
    LvcppButton *rename_button = nullptr;
    LvcppLabel *font_x = nullptr;
    LvcppLabel *font_y = nullptr;
    LvcppLabel *font_w = nullptr;
    LvcppLabel *font_h = nullptr;
    void input_pos_update(void);
    void clean_flag_dropdwon(void);
    void update_flag_dropdwon(void);
    void show_input_param(int state);
    void font_change_style(int type);
    LvcppButton *font_w_up = nullptr;
    LvcppButton *font_W_down = nullptr;
    LvcppButton *font_x_up = nullptr;
    LvcppButton *font_x_down = nullptr;
    LvcppButton *font_y_up = nullptr;
    LvcppButton *font_y_down = nullptr;
    LvcppButton *font_h_up = nullptr;
    LvcppButton *font_h_down = nullptr;
private:
    LvcppFreeTypeFont* myfont=nullptr;
    lv_obj_t* mparent=nullptr;
    //第一排

    LvcppLabel *rename_line = nullptr;
    LvcppLabel *rename_line1 = nullptr;

    //第二排
    LvcppLabel *font_w_tip = nullptr;
    LvcppLabel *font_h_tip = nullptr;
    LvcppLabel *font_x_tip = nullptr;
    LvcppLabel *font_y_tip = nullptr;



    static void textarea_event_hander(lv_event_t *event);
};


//右下
class RenameeffectScreen
{
public:
    RenameeffectScreen(lv_obj_t* parent=nullptr);
    ~RenameeffectScreen();
    LvcppScreen* mscreen=nullptr;
    void initial(void);
    void deinitial(void);
    LvcppDropdown *change_refont_style = nullptr;
    LvcppDropdown *change_refont_form = nullptr;
    LvcppDropdown *change_font_alignment = nullptr;
    LvcppButton *change_font_color = nullptr;
    LvcppLabel *font_size = nullptr;
    LvcppLabel *font_between = nullptr;

    LvcppButton *font_size_up = nullptr;
    LvcppButton *font_size_down = nullptr;

    LvcppButton *font_between_up = nullptr;
    LvcppButton *font_between_down = nullptr;

    int auto_size_flag0 = 0;
    int auto_size_flag1 = 0;
    int auto_size_flag2 = 0;
    int auto_between_flag0 = 0;
    int auto_between_flag1 = 0;
    int auto_between_flag2 = 0;
    int save_font_size0 = 0;
    int save_font_size1 = 0;
    int save_font_size2 = 0;
    int save_between_size = 0;
    LvcppButton *font_size_auto = nullptr;
    LvcppCheckBox *font_between_auto = nullptr;

    void change_font_size_and_between_auto(int param_state,int type);
private:
    LvcppFreeTypeFont* myfont=nullptr;
    lv_obj_t* mparent=nullptr;
    LvcppLabel *font_effect_tip = nullptr;


    //第二排
    LvcppLabel *border_line = nullptr;


    LvcppLabel *font_size_tip = nullptr;


    LvcppLabel *font_between_tip = nullptr;

    LvcppButton *auto_button = nullptr;
    LvcppButton *ok_button = nullptr;
    LvcppButton *del_button = nullptr;
    LvcppButton *back_button = nullptr;
    void change_font_repaly(void);
    void change_font_name(int param_state);
    void change_font_style(int param_state,int type);
    void change_down_font_style(int param_state,int type);
    void hide_screen(void);
    void manual_font_color(int param_state);
    static void textarea_event_hander(lv_event_t *event);

    void savebmp(unsigned char * pdata, char * bmp_file, int width, int height);
};

class RenameScreen : public LvcppTimerTask
{
public:
    RenameScreen(lv_obj_t* parent=nullptr);
    ~RenameScreen();
    void font_initial(void);
    void font_initial1(void);
    void font_initial2(void);
    void font_initial3(void);
    void font_initial_zp(void);
    void font_destroy(void);
    void initial(void);
    void deinitial(void);
    void RenameInfo_param_initial(void);
    void font_reset(void);
     void font_scan_file_path(char* name,const char** font);
     void repaint_canvas(void);
     lv_font_t* myfont0=nullptr;
     lv_font_t* myfont1=nullptr;
     lv_font_t* myfont2=nullptr;
     lv_draw_label_dsc_t label_dsc0;
     lv_draw_label_dsc_t label_dsc1;
     lv_draw_label_dsc_t label_dsc2;
     lv_draw_img_dsc_t img_draw_dsc;
     void sendcb(void (*callback)(void));
     void Rename_fontset_Screen(void);
     RenamefontsetScreen *re_fontset = nullptr;

     void Rename_effect_Screen_create(void);
     RenameeffectScreen *re_effect = nullptr;

     void Rename_color_Screen(void);
     RenamecolorScreen *re_color = nullptr;

     void Rename_bg_color_Screen(void);
     RenamebgcolorScreen *bg_color = nullptr;

     void Rename_box_create(void);
     RenameboxtScreen *re_box = nullptr;

     void zp_param_sync(void);

     void Rename_head_Screen_create(void);
     RenameheadScreen *re_head = nullptr;

     void Rename_bottom_Screen_create(void);
     RenamebottomScreen *re_bottom = nullptr;

     void Rename_input_Screen_create(void);
     RenameinputScreen *re_input = nullptr;

     kbscreen *input_kb = nullptr;
     void (*re_callback)(void);
private:
    int type = 0;
    int show_text_tmp = 0;
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;

    int sync_flag = 0 ;
    int font_flag = 0 ;
    int temp_flag = 0 ;
    void TimerCB(lv_timer_t * tmr);

    lv_timer_t* renametimer=nullptr;

    LvcppCanvas* canvas=nullptr;
    lv_color_t* cbuf=nullptr;
    LvcppFreeTypeFont* myfont=nullptr;

    LvcppButton * show_preview = nullptr;
    LvcppDropdown * s_bg_color = nullptr;
    LvcppDropdown * s_font_color = nullptr;
    LvcppDropdown * bg_img = nullptr;
    LvcppDropdown * refont_style = nullptr;
    LvcppDropdown * refont_size_style = nullptr;
    LvcppDropdown * switch_object = nullptr;
    LvcppDropdown * font_alignment = nullptr;
    LvcppLabel * font_tp = nullptr;
    LvcppLabel * manual_h_tip = nullptr;
    LvcppLabel * manual_photo_tip = nullptr;
    LvcppLabel * manual_bg_color_tip = nullptr;
    LvcppLabel * manual_font_color_tip = nullptr;
    LvcppLabel * manual_aglin_tip = nullptr;
    LvcppLabel * manual_line_tip = nullptr;
    LvcppLabel * manual_font_tip = nullptr;
    LvcppLabel * font_size_tip = nullptr;
    LvcppLabel * rgb_color_tip = nullptr;
    LvcppLabel * object_name_tip = nullptr;
    LvcppLabel * x_tip = nullptr;
    LvcppLabel * y_tip = nullptr;
    LvcppLabel * w_tip = nullptr;
    LvcppLabel * rgb_bg_color_tip = nullptr;
    LvcppButton * font_space_between = nullptr;
    LvcppButton * font_line_between = nullptr;
    LvcppButton * font_size =nullptr;
    LvcppButton * rgb_color1 = nullptr;
    LvcppButton * rgb_color2 = nullptr;
    LvcppButton * rgb_color3 = nullptr;
    LvcppButton * rgb_bg_color1 = nullptr;
    LvcppButton * rgb_bg_color2 = nullptr;
    LvcppButton * rgb_bg_color3 = nullptr;
    LvcppButton * usre_param = nullptr;
    //LvcppTextArea * usre_company = nullptr;
    //LvcppTextArea * usre_duty = nullptr;
    LvcppButton * wide = nullptr;
    LvcppButton * x = nullptr;
    LvcppButton * y = nullptr;
    LvcppButton * h =nullptr;
    void switch_object_get_int(void);
    lv_color_t* create_canvas(void);
    void canvas_to_img(void);
    void clear_canvas(void);
    void delete_canvas(void);
    void TextArea_initial(void);
    void dropdown_initial(void);
    void label_initial(void);
    uint8_t toByte(char c);
    void hexStringToByte(uint8_t *dstByte,const char *srcHexString ,int len);
    void BgraToRgb(uint8_t *bgraData,int width,int height,uint8_t*rgbData);
    void change_size(int type);
    void change_size_style(int type);
    void manual_bg_color(void);
    void manual_font_color(int type);
    void change_rgb_color(int type);
    void change_bg_rgb_color(void);
    void change_font_name(int type);
    void change_usre_param(int type);
    void change_x_y_h_w(int type);
    void change_font_space_between(int type);
    void change_font_line_between(int type);
    void change_font_aglin_preview(int type);
    void get_kbinput_text(void);
    void to_show_preview(void);
    void set_bg_img(void);
    void zp_param_clear1(void);
    LvcppKeyboard* kb = nullptr;
    void kb_create(void);
    static void kb_cb(void);  
    static void textarea_event_hander(lv_event_t *event);

    #if (QTSIM_PLATFORM==0)
    static void idcard_sys_proc(msg_apps_t *msg);
    #endif

};

#endif // RENAMESCREEN_H
