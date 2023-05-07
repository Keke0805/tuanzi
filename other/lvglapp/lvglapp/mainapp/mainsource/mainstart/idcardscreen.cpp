#include "idcardscreen.h"
#include "stbimage/va_image.h"

#if (QTSIM_PLATFORM==0)
#include  "hv/http_client.h"
using namespace hv;
#endif

using namespace LVGLIMAGE;
using namespace LVGLOPTAPI;

#define FILE_PATH_LONG 		1024

IdcardScreen* Idcardscreen = nullptr;

static int update_card = 0;
static pthread_mutex_t idcardlock;

static int update_canvsa = 0;
static pthread_mutex_t canvaslock;

static int update_temp = 0;
static pthread_mutex_t templock;

static int download = 0;
static pthread_mutex_t downloadlock;

static int font_download = 0;
static pthread_mutex_t font_downloadlock;

static int refresh_flag = 0; //1 =update canvas, 2 = update idcard

static void* idcard= nullptr;
static pthread_mutex_t decodelock;


void IdcardScreen::canvas_initial(void)
{
    cbuf = create_canvas();
    if(access(IDCARD_PATH,F_OK) == 0)
    {
        repaint_idcard();
    }
    else
    {
        repaint_canvas();
    }
}

lv_color_t* IdcardScreen::create_canvas(void)
{
    static lv_color_t buf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(SCREEN_HOR_SIZE, SCREEN_VER_SIZE)];//分配buf存放画板数据
    if(canvas==nullptr)
    {
        canvas =new LvcppCanvas(mparent);
    }
    canvas->set_buffer(buf, SCREEN_HOR_SIZE, SCREEN_VER_SIZE, LV_IMG_CF_TRUE_COLOR);//设置画板空间
    canvas->align(LV_ALIGN_CENTER, 0, 0);//画板居中显示
    canvas->fill_bg(lv_color_white(), LV_OPA_COVER);//画板默认背景色
    lv_draw_img_dsc_init(&img_draw_dsc);
    font_initial();
    return buf;
}

void IdcardScreen::repaint_canvas(void)
{
    uint8_t color[3];
    char imgPath[FILE_PATH_LONG]={0};
    if(canvas)
    {
        font_reset();
        hexStringToByte(color,g_CanvasInfo.layout.BgColor,strlen(g_CanvasInfo.layout.BgColor));
        memset(imgPath,0,FILE_PATH_LONG);
        sprintf(imgPath,"%s/%s",USB_IMAGE_PATH,g_CanvasInfo.layout.BgImg);
        if(strlen(g_CanvasInfo.layout.BgImg)>0 && access(imgPath,F_OK) == 0)
        {
            pthread_mutex_lock(&decodelock);
            if(idcard!=nullptr)
            {
                free_image(idcard);
                idcard = nullptr;
            }
            idcard = parse_image_from_file(imgPath);
            if(idcard==NULL)
            {
                return;
            }
            lv_img_dsc_t * img =(lv_img_dsc_t*)idcard;
            pthread_mutex_unlock(&decodelock);
            if(img->header.w* 600 < img->header.h *1024)
            {
                img_draw_dsc.zoom = 1024*256/img->header.w+1;
            }
            else
            {
                img_draw_dsc.zoom = 600*256/img->header.h+1;
            }
            canvas->draw_img(0, 0, idcard,&img_draw_dsc);//画板背景图
        }
        else
        {
            canvas->fill_bg(lv_color_make(color[0],color[1],color[2]), LV_OPA_COVER);//画板背景色
        }
        canvas->draw_text(g_CanvasInfo.layout.detail[3].ElePointX, g_CanvasInfo.layout.detail[3].ElePointY,
                  g_CanvasInfo.layout.detail[3].EleWidth, &label_dsc3, g_CanvasInfo.other);
        canvas->draw_text(g_CanvasInfo.layout.detail[2].ElePointX, g_CanvasInfo.layout.detail[2].ElePointY,
                  g_CanvasInfo.layout.detail[2].EleWidth, &label_dsc2, g_CanvasInfo.duty);
        canvas->draw_text(g_CanvasInfo.layout.detail[1].ElePointX, g_CanvasInfo.layout.detail[1].ElePointY,
                          g_CanvasInfo.layout.detail[1].EleWidth, &label_dsc1, g_CanvasInfo.company);
        canvas->draw_text(g_CanvasInfo.layout.detail[0].ElePointX, g_CanvasInfo.layout.detail[0].ElePointY,
                  g_CanvasInfo.layout.detail[0].EleWidth, &label_dsc0, g_CanvasInfo.username);
        canvas_to_img();
        canvas->invalidate();
    }
}

void IdcardScreen::repaint_idcard(void)
{
    if(canvas)
    {
        if(access(IDCARD_PATH,F_OK) == 0)
        {
            pthread_mutex_lock(&decodelock);
            if(idcard!=nullptr)
            {
                free_image(idcard);
                idcard = nullptr;
            }
            idcard = parse_image_from_file((char*)IDCARD_PATH);
            if(idcard==NULL)
            {
                return;
            }
            lv_img_dsc_t * img =(lv_img_dsc_t*)idcard;
            pthread_mutex_unlock(&decodelock);
            if(img->header.w* 600 < img->header.h *1024)
            {
                img_draw_dsc.zoom = 1024*256/img->header.w+1;
            }
            else
            {
                img_draw_dsc.zoom = 600*256/img->header.h+1;
            }
            canvas->draw_img(0, 0, idcard,&img_draw_dsc);//画板背景图
        }
        canvas->invalidate();
    }
}




void IdcardScreen::canvas_to_img(void)
{
    uint8_t* BmpData=nullptr;
    BmpData = (uint8_t*)LvcppMemory::mem_alloc(LV_CANVAS_BUF_SIZE_TRUE_COLOR(SCREEN_HOR_SIZE, SCREEN_VER_SIZE));
    BgraToRgb((uint8_t*)cbuf,SCREEN_HOR_SIZE,SCREEN_VER_SIZE,BmpData);
    if(!lvcpp_bmp::encode(BmpData, SCREEN_HOR_SIZE, SCREEN_VER_SIZE, IDCARD_PATH))
    {
        LV_LOG_USER("bmp save success");
    }
    else {
        LV_LOG_USER("bmp save failed");
    }
    if(BmpData)
    {
        LvcppMemory::mem_free(BmpData);
        BmpData = nullptr;
    }

    #if (QTSIM_PLATFORM==0)
    msg_apps_t msg;
    memset(&msg,0,sizeof(msg_apps_t));
    msg.type = MSG_UPDATE_IDCARD;
    SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
    #endif
}

void IdcardScreen::font_initial(void)
{
    uint8_t color[3];
    //username
    static lv_ft_info_t ft_font0;
    font_scan_file_path(g_CanvasInfo.layout.detail[0].TextFont,&(ft_font0.name));//字体文件
    ft_font0.weight = g_CanvasInfo.layout.detail[0].TextSize;//字号
    ft_font0.style = g_CanvasInfo.layout.detail[0].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font0);
    myfont0 =ft_font0.font;

    lv_draw_label_dsc_init(&label_dsc0);//初始化文本
    label_dsc0.font = myfont0;
    label_dsc0.align = g_CanvasInfo.layout.detail[0].HorizontalAlign;
    label_dsc0.line_space = g_CanvasInfo.layout.detail[0].TextLineSpace;
    label_dsc0.letter_space = g_CanvasInfo.layout.detail[0].TextLetterSpace;

    hexStringToByte(color,g_CanvasInfo.layout.detail[0].TextColor,strlen(g_CanvasInfo.layout.detail[0].TextColor));//文本颜色
    label_dsc0.color = lv_color_make(color[0],color[1],color[2]);

    //company
    static lv_ft_info_t ft_font1;
    font_scan_file_path(g_CanvasInfo.layout.detail[1].TextFont,&(ft_font1.name));//字体文件
    ft_font1.weight = g_CanvasInfo.layout.detail[1].TextSize;//字号
    ft_font1.style = g_CanvasInfo.layout.detail[1].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font1);
    myfont1 =ft_font1.font;

    lv_draw_label_dsc_init(&label_dsc1);//初始化文本
    label_dsc1.font = myfont1;
    label_dsc1.align = g_CanvasInfo.layout.detail[1].HorizontalAlign;
    label_dsc1.line_space = g_CanvasInfo.layout.detail[1].TextLineSpace;
    label_dsc1.letter_space = g_CanvasInfo.layout.detail[1].TextLetterSpace;

    hexStringToByte(color,g_CanvasInfo.layout.detail[1].TextColor,strlen(g_CanvasInfo.layout.detail[1].TextColor));//文本颜色
    label_dsc1.color = lv_color_make(color[0],color[1],color[2]);

    //duty
    static lv_ft_info_t ft_font2;
    font_scan_file_path(g_CanvasInfo.layout.detail[2].TextFont,&(ft_font2.name));//字体文件
    ft_font2.weight = g_CanvasInfo.layout.detail[2].TextSize;//字号
    ft_font2.style = g_CanvasInfo.layout.detail[2].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font2);
    myfont2 =ft_font2.font;

    lv_draw_label_dsc_init(&label_dsc2);//初始化文本
    label_dsc2.font = myfont2;
    label_dsc2.align = g_CanvasInfo.layout.detail[2].HorizontalAlign;
    label_dsc2.line_space = g_CanvasInfo.layout.detail[2].TextLineSpace;
    label_dsc2.letter_space = g_CanvasInfo.layout.detail[2].TextLetterSpace;

    hexStringToByte(color,g_CanvasInfo.layout.detail[2].TextColor,strlen(g_CanvasInfo.layout.detail[2].TextColor));//文本颜色
    label_dsc2.color = lv_color_make(color[0],color[1],color[2]);

    //other
    static lv_ft_info_t ft_font3;
    font_scan_file_path(g_CanvasInfo.layout.detail[3].TextFont,&(ft_font3.name));//字体文件
    ft_font3.weight = g_CanvasInfo.layout.detail[3].TextSize;//字号
    ft_font3.style = g_CanvasInfo.layout.detail[3].TextType;//字型 0正常 1斜体 2粗体
    lv_ft_font_init(&ft_font3);
    myfont3 =ft_font3.font;

    lv_draw_label_dsc_init(&label_dsc3);//初始化文本
    label_dsc3.font = myfont3;
    label_dsc3.align = g_CanvasInfo.layout.detail[3].HorizontalAlign;
    label_dsc3.line_space = g_CanvasInfo.layout.detail[3].TextLineSpace;
    label_dsc3.letter_space = g_CanvasInfo.layout.detail[3].TextLetterSpace;

    hexStringToByte(color,g_CanvasInfo.layout.detail[3].TextColor,strlen(g_CanvasInfo.layout.detail[3].TextColor));//文本颜色
    label_dsc3.color = lv_color_make(color[0],color[1],color[2]);
}


void IdcardScreen::font_destroy(void)
{
    if(myfont0)
    {
        lv_ft_font_destroy(myfont0);
        myfont0 = nullptr;
    }
    if(myfont1)
    {
        lv_ft_font_destroy(myfont1);
        myfont1 = nullptr;
    }
    if(myfont2)
    {
        lv_ft_font_destroy(myfont2);
        myfont2 = nullptr;
    }
    if(myfont3)
    {
        lv_ft_font_destroy(myfont3);
        myfont3 = nullptr;
    }

}

void IdcardScreen::font_reset(void)
{
    font_destroy();
    font_initial();

}


IdcardScreen::IdcardScreen(lv_obj_t* parent)
{
    Idcardscreen = this;
    mscreen = new LvcppScreen(parent);
    mscreen->set_bg_color(lv_color_white(),LV_OPA_100);
    mparent = mscreen->get_screen();
    initial();
    idcardtimer = startTimer(50,this);
}

IdcardScreen::~IdcardScreen()
{
    deinitial();
}

void IdcardScreen::initial()
{
    canvas_initial();
    #if (QTSIM_PLATFORM==0)
    SSTAR_RegisterApplib(APP_NAME_IDCARD, idcard_sys_proc);
    #endif
    if(back == nullptr)
    {
        back = new LvcppButton(mparent);
        back->set_size(44,26);
        back->add_txt("");
        back->set_main_bg_img_src(FH_AX_BUTTON);
        back->set_main_bg_color(lv_color_white(),LV_OPA_0);
        back->add_event_cb(btn_event_hander,LV_EVENT_PRESSING,this);
        back->add_event_cb(btn_event_hander,LV_EVENT_RELEASED,this);
    }
}

void IdcardScreen::deinitial()
{
    #if (QTSIM_PLATFORM==0)
    SSTAR_UnRegisterApplib(APP_NAME_IDCARD, idcard_sys_proc);
    #endif
    if(back != nullptr)
    {
        delete back;
        back = nullptr;
    }
    if(mscreen != nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

void IdcardScreen::decode_thread_start(void)
{
    pthread_attr_init(&pthread_attr);
    pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setscope(&pthread_attr, PTHREAD_SCOPE_SYSTEM);
    if(pthread_create(&m_tid,&pthread_attr,thread_decode_image,this) != 0)
    {
        LV_LOG_USER("decode_thread_start failed!");
    }
    pthread_attr_destroy(&pthread_attr);
}

void* IdcardScreen::thread_decode_image(void* arg)
{
    IdcardScreen* opt = (IdcardScreen*)arg;
    if(refresh_flag==1)
    {
        opt->repaint_canvas();
    }
    else if(refresh_flag==2)
    {
        opt->repaint_idcard();
    }
    refresh_flag = 0;
    usleep(10000);
    return NULL;
}


void IdcardScreen::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;//static variable once assign
    if(update_card)
    {
        if(refresh_flag==1)
        {
            repaint_canvas();
        }
        else if(refresh_flag==2)
        {
            repaint_idcard();
        }
        //decode_thread_start();
        pthread_mutex_lock(&idcardlock);
        refresh_flag = 0;
        update_card = 0;
        pthread_mutex_unlock(&idcardlock);
    }
    if(update_canvsa)
    {
        if(refresh_flag==1)
        {
            repaint_canvas();
        }
        else if(refresh_flag==2)
        {
            repaint_idcard();
        }
        //decode_thread_start();
        pthread_mutex_lock(&canvaslock);
        refresh_flag = 0;
        update_canvsa = 0;
        pthread_mutex_unlock(&canvaslock);
    }
    if(update_temp)
    {
        hv_http_request();
        pthread_mutex_lock(&templock);
        update_temp = 0;
        pthread_mutex_unlock(&templock);
    }
}

int IdcardScreen::hv_http_request(void)
{
    int ret = 0;
    #if (QTSIM_PLATFORM==0)
    HttpRequest req;
    req.method = HTTP_GET;
    if(strlen(url)>0)
    {
        LV_LOG_USER("http_request:url = %s",url);
        req.url = url;
    }
    else
    {
        return -1;
    }
    HttpResponse res;
    ret = http_client_send(&req, &res);
    printf("%s\n", req.Dump(true,true).c_str());
    if (ret != 0) {
        printf("* Failed:%s:%d\n", http_client_strerror(ret), ret);
    }
    else {
        LV_LOG_USER("%s\n", res.body.c_str());
        ReqStringtoJsonParse(res.body);
    }
    #endif
    return ret;
}

#if (QTSIM_PLATFORM==0)
void IdcardScreen::idcard_sys_proc(msg_apps_t *msg)
{
    switch(msg->type)
    {
        case MSG_UPDATE_TEMPLATE:
        {
            if(update_temp==0)
            {
                LV_LOG_USER("!!!! MSG_UPDATE_TEMPLATE !!!!\n");
                char url[1024];
                memset(Idcardscreen->url,0,sizeof(Idcardscreen->url));
                memcpy(Idcardscreen->url,msg->content,strlen(msg->content));
                pthread_mutex_lock(&templock);
                update_temp = 1;
                pthread_mutex_unlock(&templock);
            }
            break;
        }
        case MSG_UPDATE_CANVAS:
        {
            LV_LOG_USER("!!!! MSG_UPDATE_CANVAS !!!!\n");
            if(update_canvsa==0)
            {
                pthread_mutex_lock(&canvaslock);
                update_canvsa = 1;
                refresh_flag = 1;
                pthread_mutex_unlock(&canvaslock);
            }
            break;
        }
        case MSG_UPDATE_IDCARD:
        {
            LV_LOG_USER("!!!! MSG_UPDATE_IDCARD !!!!\n");
            if(update_card==0)
            {
                pthread_mutex_lock(&idcardlock);
                update_card = 1;
                if(download)
                {
                    refresh_flag = 1;
                    pthread_mutex_lock(&downloadlock);
                    download = 0;
                    pthread_mutex_unlock(&downloadlock);
                }
                else if(font_download)
                {
                    refresh_flag = 1;
                    pthread_mutex_lock(&font_downloadlock);
                    font_download = 0;
                    pthread_mutex_unlock(&font_downloadlock);
                }
                else
                {
                    refresh_flag = 2;
                }
                pthread_mutex_unlock(&idcardlock);
            }
            break;
        }
        case MSG_CLEAR_ALL_INFO:
        {
            LV_LOG_USER("!!!! MSG_CLEAR_ALL_INFO !!!!\n");
            Idcardscreen->zp_param_initial();
            if(update_canvsa==0)
            {
                pthread_mutex_lock(&canvaslock);
                update_canvsa = 1;
                refresh_flag = 1;
                pthread_mutex_unlock(&canvaslock);
            }
            break;
        }
        default:
        break;
    }
}

#endif

void IdcardScreen::font_scan_file_path(char* name,const char** font)
{
    char path[1024];
    if(strcmp(name,"黑体")==0)
    {
        *font = "./resource/font/HeiTi.ttf";
    }
    else if(strcmp(name,"楷体")==0)
    {
        *font = "./resource/font/FZKT.ttf";
    }
    else if(strcmp(name,"魏体")==0)
    {
        *font = "./resource/font/HWXW.ttf";
    }
    else if(strcmp(name,"宋体")==0)
    {
        *font = "./resource/font/HWZS.ttf";
    }
    else if(strcmp(name,"隶书")==0)
    {
        *font = "./resource/font/LS.ttf";
    }
    else if(strcmp(name,"标宋")==0)
    {
        *font = "./resource/font/BiaoSong.ttf";
    }
    else if(strcmp(name,"中宋")==0)
    {
        *font = "./resource/font/ZhongSong.ttf";
    }
    else if(strcmp(name,"等宽")==0)
    {
        *font = "./resource/font/Deng.ttf";
    }
    else if(strcmp(name,"微软雅黑")==0)
    {
        *font = "./resource/font/WRYH.ttf";
    }
    else
    {
        if(name && strlen(name)>0)
        {
            memset(path,0,sizeof(path));
            //LV_LOG_USER("name=%s",name);
            sprintf(path,"./resource/font/temp.ttf");
            if(access(path,F_OK) == 0)
            {
                *(font) = path;
            }
            else
            {
                *font = "./resource/font/FZKT.ttf";
            }
        }
        else
        {
            *font = "./resource/font/FZKT.ttf";
        }
    }
}

uint8_t IdcardScreen::toByte(char c)
{
    unsigned char value = 0;

    if (c >= '0' && c <= '9')
        value = c - '0';
    else if (c >= 'A' && c <= 'Z')
        value = c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        value = c - 'a' + 10;

    return value;
}

void IdcardScreen::hexStringToByte(uint8_t *dstByte,const char *srcHexString ,int len)
{
    int index;

    for (int i = 0; i < len; i++){
        index = i * 2;
        dstByte[i] = ((toByte(srcHexString[index]))<<4) | toByte(srcHexString[index+1]);
    }
}

void IdcardScreen::BgraToRgb(uint8_t *bgraData,int width,int height,uint8_t*rgbData)
{
    uint8_t bgrData[width*height*3];
    memset(bgrData,0,sizeof(bgrData));
    for(int i=0,j=0; j<width * height*4; i+=3,j+=4)
    {
        bgrData[i] = bgraData[j];
        bgrData[i+1] = bgraData[j+1];
        bgrData[i+2] = bgraData[j+2];
    }
    for(int n=0,m=0; n < width * height; n++,m+=3){
        uint8_t b_value = bgrData[m];
        uint8_t g_value = bgrData[m+1];
        uint8_t r_value = bgrData[m+2];
        *rgbData++ = r_value;
        *rgbData++ = g_value;
        *rgbData++ = b_value;
     }
}


void IdcardScreen::ReqStringtoJsonParse(std::string data)
{
    cJSON* root=NULL;
    cJSON* detail=NULL;
    cJSON* detail_array=NULL;
    cJSON* item=NULL;
    int ret=0;
    int array_total = 0;
    int i=0;
    char url[1024] = {0};
    char fonturl[1024] = {0};

    if(data.empty())
    {
        return;
    }
    //LV_LOG_USER("%s\n", data.c_str());
    root = cJSON_Parse(data.c_str());
    if (!root)
    {
        LV_LOG_USER("parse failed");
        return;
    }
    memset(&g_CanvasInfo,0,sizeof(zpc_canvas_param_t));

    item = cJSON_GetObjectItem(root, "result_code");
    if(item&&item->type==cJSON_Number)
    {
        if(item->valueint!=200)
        {
            LV_LOG_USER("result_code error");
            strcpy(g_CanvasInfo.layout.BgColor, "FF0000");
            strcpy(g_CanvasInfo.layout.BgImg, "");
            for(i=0;i<MAX_DETAIL_NUM;i++)
            {
                if(i==0)
                {
                    strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "username");
                    g_CanvasInfo.layout.detail[i].ElePointX=0;
                    g_CanvasInfo.layout.detail[i].ElePointY=200;
                    g_CanvasInfo.layout.detail[i].EleWidth=1024;
                    g_CanvasInfo.layout.detail[i].EleHeight=200;
                    g_CanvasInfo.layout.detail[i].TextSize=200;
                    strcpy(g_CanvasInfo.layout.detail[i].TextColor, "fac000");
                    strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                    g_CanvasInfo.layout.detail[i].HorizontalAlign=2;
                    g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                    g_CanvasInfo.layout.detail[i].TextLetterSpace=50;
                    g_CanvasInfo.layout.detail[i].TextType=2;
                }
                else if(i==1)
                {
                    strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "company");
                    g_CanvasInfo.layout.detail[i].ElePointX=0;
                    g_CanvasInfo.layout.detail[i].ElePointY=0;
                    g_CanvasInfo.layout.detail[i].EleWidth=1024;
                    g_CanvasInfo.layout.detail[i].EleHeight=80;
                    g_CanvasInfo.layout.detail[i].TextSize=80;
                    strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                    strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                    g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
                    g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                    g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                    g_CanvasInfo.layout.detail[i].TextType=0;
                }
                else if(i==2)
                {
                    strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "duty");
                    g_CanvasInfo.layout.detail[i].ElePointX=0;
                    g_CanvasInfo.layout.detail[i].ElePointY=500;
                    g_CanvasInfo.layout.detail[i].EleWidth=1024;
                    g_CanvasInfo.layout.detail[i].EleHeight=100;
                    g_CanvasInfo.layout.detail[i].TextSize=80;
                    strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                    strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                    g_CanvasInfo.layout.detail[i].HorizontalAlign=3;
                    g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                    g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                    g_CanvasInfo.layout.detail[i].TextType=0;
                }
                else if(i==3)
                {
                    strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "other");
                    g_CanvasInfo.layout.detail[i].ElePointX=0;
                    g_CanvasInfo.layout.detail[i].ElePointY=500;
                    g_CanvasInfo.layout.detail[i].EleWidth=1024;
                    g_CanvasInfo.layout.detail[i].EleHeight=100;
                    g_CanvasInfo.layout.detail[i].TextSize=80;
                    strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
                    strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
                    g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
                    g_CanvasInfo.layout.detail[i].TextLineSpace=0;
                    g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
                    g_CanvasInfo.layout.detail[i].TextType=0;
                }
            }
            return;
        }
        else
        {
            strcpy(g_CanvasInfo.layout.BgColor, "FF0000");
            strcpy(g_CanvasInfo.layout.BgImg, "temp.png");
        }
    }

    item = cJSON_GetObjectItem(root, "picture");
    if (item&&cJSON_IsBool(item))
    {
        if(cJSON_IsTrue(item))
        {
            LV_LOG_USER("picture = true");
            pthread_mutex_lock(&downloadlock);
            download = 1;
            pthread_mutex_unlock(&downloadlock);
        }
        else
        {
            LV_LOG_USER("picture = false");
            pthread_mutex_lock(&downloadlock);
            download = 0;
            pthread_mutex_unlock(&downloadlock);
        }
    }

    item = cJSON_GetObjectItem(root, "url");
    if (item&&item->type==cJSON_String)
    {
        char local_head_url[256];
        char local_tail_url[128];
        memset(local_head_url, 0, sizeof(local_head_url));
        memset(local_tail_url, 0, sizeof(local_tail_url));

        strcpy(local_tail_url, cJSON_GetStringValue(item));

        #if (QTSIM_PLATFORM==0)
        if(g_zpcInfo.server_type == 0)
        {
            sprintf(local_head_url,"http://%s",g_zpcInfo.server_lan_ip);
        }
        else
        {
            sprintf(local_head_url,"http://%s",g_zpcInfo.server_ip);
        }
        #endif
        strcat(local_head_url,local_tail_url);
        memcpy(url, local_head_url, strlen(local_head_url));
    }


    item = cJSON_GetObjectItem(root, "userFont");
    if (item&&cJSON_IsBool(item))
    {
        if(cJSON_IsTrue(item))
        {
            LV_LOG_USER("userFont = true");
            pthread_mutex_lock(&font_downloadlock);
            font_download = 1;
            pthread_mutex_unlock(&font_downloadlock);
        }
        else
        {
            LV_LOG_USER("userFont = false");
            pthread_mutex_lock(&font_downloadlock);
            font_download = 0;
            pthread_mutex_unlock(&font_downloadlock);
        }
    }

    item = cJSON_GetObjectItem(root, "fontUrl");
    if (item&&item->type==cJSON_String)
    {
        char fontlocal_head_url[256];
        char fontlocal_tail_url[128];
        memset(fontlocal_head_url, 0, sizeof(fontlocal_head_url));
        memset(fontlocal_tail_url, 0, sizeof(fontlocal_tail_url));

        strcpy(fontlocal_tail_url, cJSON_GetStringValue(item));

        #if (QTSIM_PLATFORM==0)
        if(g_zpcInfo.server_type == 0)
        {
            sprintf(fontlocal_head_url,"http://%s",g_zpcInfo.server_lan_ip);
        }
        else
        {
            sprintf(fontlocal_head_url,"http://%s",g_zpcInfo.server_ip);
        }
        #endif
        strcat(fontlocal_head_url,fontlocal_tail_url);
        memcpy(fonturl, fontlocal_head_url, strlen(fontlocal_head_url));
    }


    detail = cJSON_GetObjectItem(root, "detail");
    array_total = cJSON_GetArraySize(detail);
    //LV_LOG_USER("array_total = %d",array_total);
    for(int m=0;m<array_total;m++)
    {
        detail_array = cJSON_GetArrayItem(detail, m);

        item = cJSON_GetObjectItem(detail_array, "field");
        if (item&&item->type==cJSON_String)
        {
            if(strcmp(cJSON_GetStringValue(item),"username")==0)
            {
                i = 0;
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, cJSON_GetStringValue(item));
                item = cJSON_GetObjectItem(detail_array, "content");
                strcpy(g_CanvasInfo.username, cJSON_GetStringValue(item));
                LV_LOG_USER("field : username = %s",cJSON_GetStringValue(item));
            }
            else if(strcmp(cJSON_GetStringValue(item),"company")==0)
            {
                i = 1;
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, cJSON_GetStringValue(item));
                item = cJSON_GetObjectItem(detail_array, "content");
                strcpy(g_CanvasInfo.company, cJSON_GetStringValue(item));
                LV_LOG_USER("field : company = %s",cJSON_GetStringValue(item));
            }
            else if(strcmp(cJSON_GetStringValue(item),"duty")==0)
            {
                i = 2;
                strcpy(g_CanvasInfo.layout.detail[i].ElementNo, cJSON_GetStringValue(item));
                item = cJSON_GetObjectItem(detail_array, "content");
                strcpy(g_CanvasInfo.duty, cJSON_GetStringValue(item));
                LV_LOG_USER("field : duty = %s",cJSON_GetStringValue(item));
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
        item = cJSON_GetObjectItem(detail_array, "x");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].ElePointX=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "y");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].ElePointY=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "width");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].EleWidth=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "height");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].EleHeight=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "fontSize");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].TextSize=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "color");
        if (item&&item->type==cJSON_String)
        {
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(detail_array, "font");
        if (item&&item->type==cJSON_String)
        {
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, cJSON_GetStringValue(item));
        }
        item = cJSON_GetObjectItem(detail_array, "textAlign");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].HorizontalAlign=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "lineSpace");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].TextLineSpace=item->valueint;
        }
        item = cJSON_GetObjectItem(detail_array, "letterSpace");
        if (item&&item->type==cJSON_Number)
        {
            g_CanvasInfo.layout.detail[i].TextLetterSpace=item->valueint;
        }
        g_CanvasInfo.layout.detail[i].ElePointY=g_CanvasInfo.layout.detail[i].ElePointY+(g_CanvasInfo.layout.detail[i].EleHeight-g_CanvasInfo.layout.detail[i].TextSize)/2;
    }
    LV_LOG_USER("parse success");
    if(download || font_download)
    {
        if(download)
        {
            #if (QTSIM_PLATFORM==0)
            dl_msg_t dlmsg;
            memset(&dlmsg, 0, sizeof(dl_msg_t));
            dlmsg.type = DL_MSG_DL_URL;
            dlmsg.data_len = strlen(url);
            memcpy(dlmsg.data_buf, url, strlen(url));
            memcpy(dlmsg.filename, "/customer/resource/image/bg/temp.png", strlen("/customer/resource/image/bg/temp.png"));
            ret = SSTAR_DLMsg(&dlmsg);
            #endif
        }
        if(font_download)
        {
            #if (QTSIM_PLATFORM==0)
            dl_msg_t dlmsg;
            memset(&dlmsg, 0, sizeof(dl_msg_t));
            dlmsg.type = DL_MSG_DL_URL;
            dlmsg.data_len = strlen(fonturl);
            memcpy(dlmsg.data_buf, fonturl, strlen(fonturl));
            memcpy(dlmsg.filename, "/customer/resource/font/temp.ttf", strlen("/customer/resource/font/temp.ttf"));
            ret = SSTAR_DLMsg(&dlmsg);
            #endif
        }
    }
    else
    {
        #if (QTSIM_PLATFORM==0)
        msg_apps_t msg;
        memset(&msg,0,sizeof(msg_apps_t));
        msg.type = MSG_UPDATE_CANVAS;
        SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
        #endif
    }
}


void IdcardScreen::zp_param_initial(void)
{
    memset(&g_CanvasInfo,0,sizeof(zpc_canvas_param_t));
    g_CanvasInfo.clear_flag = 0;
    strcpy(g_CanvasInfo.username, "姓名");
    strcpy(g_CanvasInfo.company, "单位");
    strcpy(g_CanvasInfo.duty, "职务");
    strcpy(g_CanvasInfo.other, "");

    strcpy(g_CanvasInfo.layout.BgColor, "FF0000");
    strcpy(g_CanvasInfo.layout.BgImg, "");
    for(int i=0;i<MAX_DETAIL_NUM;i++)
    {
        if(i==0)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "username");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=200;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=200;
            g_CanvasInfo.layout.detail[i].TextSize=200;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "fac000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=2;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=50;
            g_CanvasInfo.layout.detail[i].TextType=2;
        }
        else if(i==1)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "company");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=0;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=80;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
        else if(i==2)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "duty");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=500;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=100;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=3;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
        else if(i==3)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "other");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=500;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=100;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
    }
}
/*
void IdcardScreen::sendcb(void (*callback)(void))
{
    LV_LOG_USER("aaaaaaaaaaa");
    incard_callback=callback;
    LV_LOG_USER("aaaaaaaaaaa");
}*/


void IdcardScreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    IdcardScreen* opt = (IdcardScreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);


    if(target==opt->back->myobj)//单机改名
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->back->set_main_bg_img_src(FH_AX_BUTTON);
            opt->mscreen->show(false);
        }
        else if(event->code == LV_EVENT_PRESSING)
        {
            opt->back->set_main_bg_img_src(FH_BUTTON);
        }

    }
}
