/**
 * @file fbdev.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "fbdev.h"
#if USE_FBDEV || USE_BSD_FBDEV

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>

#if(QTSIM_PLATFORM == 0)
#include <sys/mman.h>
#include <sys/ioctl.h>

#ifdef USE_GFX_ROTATE
	#include <stdlib.h>
	#include <unistd.h>
	#include <stddef.h>
	#include <stdio.h>
	#include <fcntl.h>


	#include "mi_gfx.h"
	#include "mi_gfx_datatype.h"
	#include "mi_sys.h"
	#include "mi_common.h"
	#include "mi_common_datatype.h"

	MI_PHY phyAddr = NULL; // For example: Fill a rect to Fb. (u32PhyAddr = Fb Start Addr)
	MI_U64 u64VirAddr;
#endif

#ifdef _DISP_INIT
	#include "mi_panel_datatype.h"
	#include "mi_panel.h"
	#include "mi_disp_datatype.h"
	#include "mi_disp.h"

	#define STCHECKRESULT(result)\
    if (result != MI_SUCCESS)\
    {\
        printf("[%s %d]exec function failed\n", __FUNCTION__, __LINE__);\
        return 1;\
    }\
    else\
    {\
        printf("(%s %d)exec function pass\n", __FUNCTION__,__LINE__);\
    }

	#define DISP_INPUT_WIDTH    1024
	#define DISP_INPUT_HEIGHT   600

	#define MAKE_YUYV_VALUE(y,u,v)  ((y) << 24) | ((u) << 16) | ((y) << 8) | (v)
	#define YUYV_BLACK              MAKE_YUYV_VALUE(0,128,128)
	#define YUYV_WHITE              MAKE_YUYV_VALUE(255,128,128)
	#define YUYV_RED                MAKE_YUYV_VALUE(76,84,255)
	#define YUYV_GREEN              MAKE_YUYV_VALUE(149,43,21)
	#define YUYV_BLUE               MAKE_YUYV_VALUE(29,225,107)

	static unsigned long u32DispInWidth=1024;
	static unsigned long u32DispInHeight=600;

	static unsigned long u32DispOutWidth=1024;
	static unsigned long u32DispOutHeight =600;
#endif

#endif

#if USE_BSD_FBDEV
#include <sys/fcntl.h>
#include <sys/time.h>
#include <sys/consio.h>
#include <sys/fbio.h>
#else  /* USE_BSD_FBDEV */
#if(QTSIM_PLATFORM == 0)
#include <linux/fb.h>
#else
struct fb_var_screeninfo
{
    //struct fb_info的成员（可变参数），其记录用户可修改的显示控制器的参数，包括分
    //辨率和每个像素点的比特数，其成员需要在驱动程序中初始化和设置
    /********可见解析度（实际屏幕）********/
    uint32_t xres;  /* visible resolution*//*定义屏幕一行有多少个像素点 */
    uint32_t yres;  /*定义屏幕一列由多少个像素点 */

    /********虚拟解析度（虚拟屏幕）********/
    uint32_t xres_virtual;/* virtual resolution*/ /*虚拟屏幕一行有多少个像素点 */
    uint32_t yres_virtual;                                 /*虚拟屏幕一列由多少个像素点*/
    uint32_t xoffset;/* offset from virtual to visible */ /*虚拟到可见（实际）之间的行方向偏移 */
    uint32_t yoffset;/* resolution*/                           /*虚拟到可见（实际）之间的列方向偏移*/

    uint32_t bits_per_pixel; /* guess what */                  /*每像素位数(多少BPP)，单位为字节 */
    uint32_t grayscale; /* != 0 Graylevels instead of colors */  /*非0时指灰度*/

    uint32_t nonstd;/* != 0 Non standard pixel format *//*非标准像素格式时应该为非0值 (标志像素格式时 nonstd=0) */

    uint32_t activate;/* see FB_ACTIVATE_**/   /*查看宏FB_ACTIVATE_NOW */

    uint32_t height;/* height of picture in mm */ /* 高度*/
    uint32_t width;/* width of picture in mm*/     /* 宽度 */

    uint32_t accel_flags;/* (OBSOLETE) see fb_info.flags */ /*查看fb_info.flags */

  /************这参数必须通过查看LCD数据手册得到**************/
    /* Timing: All values in pixclocks, except pixclock (of course) */
    uint32_t pixclock; /* pixel clock in ps (pico seconds) */ /*像素时钟（皮秒），pixclock=1/Dclk=... */
    /* 行切换，从同步到绘图之间的延迟即HFPD(有效数据之后无效的像素的个数) ，对应于LCD数据手册的Hsyn的front-porch*/
    uint32_t left_margin; /* time from sync to picture */
    /*行切换，从绘图到同步之间的延迟即HBPD(Hsyn脉冲下降沿之后的无效像素的个数) ,对应于LCD数据手册的Hsyn的back-porch*/
    uint32_t right_margin; /* time from picture to sync */
    /*帧切换，从同步到绘图之间的延迟即VFPD(有效数据之后还要经历的无效行数(之后是下一帧数据)) ，对应于LCD数据手册的Vsyn的front-porch*/
    uint32_t upper_margin; /* time from sync to picture */
    /*帧切换，从绘图到同步之间的延迟即VBPD(Vsyn脉冲下降沿之后还要经历的无效行数) ，对应于LCD数据手册的Vsyn的back-porch */
    uint32_t lower_margin;
    /*水平同步的长度即HSPW(Hsyn信号的脉冲宽度)，对应于LCD数据手册的Hsyn的pulse Width */
    uint32_t hsync_len;  /* length of horizontal sync*/
    /*垂直同步的长度即VSPW(Vsyn信号的脉冲宽度)，对应于LCD数据手册的Vsyn的pulse Width */
    uint32_t vsync_len;  /* length of vertical sync*/

    uint32_t sync;   /* see FB_SYNC_**/            /* 查看宏FB_SYNC_*/
    uint32_t vmode;  /* see FB_VMODE_**/         /*  查看宏FB_VMODE_ */
    uint32_t rotate;  /* angle we rotate counter clockwise */ /*顺时钟旋转的角度 */
    uint32_t reserved[5]; /* Reserved for future compatibility */  /* */
 };

struct fb_fix_screeninfo
{
// struct fb_info的成员(固定参数)，其记录用户不能修改的显示控制器的参数，如屏幕缓冲区物理地址，
//长度，当对帧缓冲设备进行映射操作时，就是从此结构中取得缓冲区物理地址，其成员需要在驱动程序中初始化和设置

  char id[16]; /* identification string eg "TT Builtin" */           /*字符串形式的标识符  */
  /* fb缓冲内存的开始地址（物理地址），它一般是作为dma_alloc_writecombine的参数，该函数会将物理地址存放在该变量中*/
  unsigned long smem_start; /* Start of frame buffer mem physical address) */
  uint32_t smem_len; /* Length of frame buffer mem */            /* fb缓冲的长度,等于max_xres *max_yres*max_bpp/8  */
  uint32_t type;  /* see FB_TYPE_**/                               /*  查看宏 FB_TYPE_    FB_TYPE_PACKED_PIXELS=0  */
  uint32_t type_aux; /* Interleave for interleaved Planes*/      /* 分界，=0 */
  uint32_t visual;  /* see FB_VISUAL_**/  /* 查看宏FB_VISUAL_，用于记录屏幕使用的色彩模式，一般是FB_VISUAL_TRUECOLOR（真彩色） */
  uint16_t xpanstep; /* zero if no hardware panning*/            /* 如果没有硬件 panning，=0 */
  uint16_t ypanstep; /* zero if no hardware panning*/            /* 如果没有硬件 panning，=0 */
  uint16_t ywrapstep;/* zero if no hardware ywrap */             /* 如果没有硬件 panning，=0 */
  uint32_t line_length;/* length of a line in bytes */                /* 一行的字节数 */
  unsigned long mmio_start; /* Start of Memory Mapped I/O*/  /* 内存映射的I/O的开始位置 */
      /* (physical address) */
  uint32_t mmio_len; /* Length of Memory Mapped I/O  */            /* 内存映射的I/O的长度 */
  uint32_t accel; /* Indicate to driver which */                           /* = FB_ACCEL_NONE */
      /*  specific chip/card we have */
  uint16_t reserved[3];/* Reserved for future compatibility */       /*  */
 };
#endif
#endif /* USE_BSD_FBDEV */

/*********************
 *      DEFINES
 *********************/
#ifndef FBDEV_PATH
#define FBDEV_PATH  "/dev/fb0"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      STRUCTURES
 **********************/

struct bsd_fb_var_info{
    uint32_t xoffset;
    uint32_t yoffset;
    uint32_t xres;
    uint32_t yres;
    int bits_per_pixel;
 };

struct bsd_fb_fix_info{
    long int line_length;
    long int smem_len;
};

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

#if USE_BSD_FBDEV
static struct bsd_fb_var_info vinfo;
static struct bsd_fb_fix_info finfo;
#else
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
#endif /* USE_BSD_FBDEV */
static char *fbp = 0;
static long int screensize = 0;
static int fbfd = 0;

#ifdef USE_GFX_ROTATE
	int gfx_flag = 0;
	MI_U16 u16TargetFence;
	MI_GFX_Surface_t stDst;
	MI_GFX_Rect_t stDstRect;

	MI_GFX_Surface_t stSrc;
	MI_GFX_Rect_t stSrcRect;
	MI_GFX_Opt_t stOpt;


	#define ExecFunc(_func_, _ret_) \
	    if (_func_ != _ret_)\
	    {\
	        printf("[%s][%d]exec function failed\n", __FUNCTION__, __LINE__);\
	        return ;\
	    }\
	    else\
	    {\
	        printf("[%s][%d]exec function pass\n", __FUNCTION__, __LINE__);\
	    }
#endif
/**********************
 *      MACROS
 **********************/

#if USE_BSD_FBDEV
#define FBIOBLANK FBIO_BLANK
#endif /* USE_BSD_FBDEV */

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#if(QTSIM_PLATFORM == 0)

#ifdef _DISP_INIT
int ST_Screen_Init(void)
{
    MI_DISP_PubAttr_t stPubAttr;
    MI_DISP_VideoLayerAttr_t stLayerAttr;
    MI_DISP_InputPortAttr_t stInputPortAttr;
    MI_PANEL_IntfType_e eIntfType;
    
    //config disp
    memset(&stPubAttr, 0, sizeof(MI_DISP_PubAttr_t));
    stPubAttr.u32BgColor = YUYV_BLACK;
    stPubAttr.eIntfSync = E_MI_DISP_OUTPUT_USER;
    stPubAttr.eIntfType = E_MI_DISP_INTF_TTL;
    MI_DISP_SetPubAttr(0, &stPubAttr);
    STCHECKRESULT(MI_DISP_Enable(0));

    memset(&stPubAttr, 0, sizeof(MI_DISP_PubAttr_t));
    stPubAttr.eIntfType = E_MI_DISP_INTF_TTL;
    MI_DISP_GetPubAttr(0,&stPubAttr);

    memset(&stLayerAttr, 0, sizeof(MI_DISP_VideoLayerAttr_t));
    stLayerAttr.stVidLayerDispWin.u16X = 0;
    stLayerAttr.stVidLayerDispWin.u16Y = 0;
    stLayerAttr.stVidLayerDispWin.u16Width = stPubAttr.stSyncInfo.u16Hact;
    stLayerAttr.stVidLayerDispWin.u16Height = stPubAttr.stSyncInfo.u16Vact;
    STCHECKRESULT(MI_DISP_BindVideoLayer(0, 0));
    STCHECKRESULT(MI_DISP_SetVideoLayerAttr(0, &stLayerAttr));
    STCHECKRESULT(MI_DISP_EnableVideoLayer(0));

    memset(&stInputPortAttr, 0, sizeof(MI_DISP_InputPortAttr_t));
    stInputPortAttr.u16SrcWidth = u32DispInWidth;
    stInputPortAttr.u16SrcHeight = u32DispInHeight;
    stInputPortAttr.stDispWin.u16X = 0;
    stInputPortAttr.stDispWin.u16Y = 0;
    stInputPortAttr.stDispWin.u16Width = u32DispOutWidth;
    stInputPortAttr.stDispWin.u16Height = u32DispOutHeight;
    STCHECKRESULT(MI_DISP_SetInputPortAttr(0, 0, &stInputPortAttr));
    STCHECKRESULT(MI_DISP_EnableInputPort(0, 0));

    //init panel
    eIntfType = E_MI_PNL_INTF_TTL;
    STCHECKRESULT(MI_PANEL_Init(eIntfType));

    return 0;
}

int ST_Screen_DeInit(void)
{
    STCHECKRESULT(MI_DISP_DisableInputPort(0, 0));
    STCHECKRESULT(MI_DISP_DisableVideoLayer(0));
    STCHECKRESULT(MI_DISP_UnBindVideoLayer(0, 0));
    STCHECKRESULT(MI_DISP_Disable(0));
    STCHECKRESULT(MI_PANEL_DeInit());

    return 0;
}
#endif


void fbdev_init(lv_disp_rot_t rotate)
{
    // Open the file for reading and writing
#ifdef USE_GFX_ROTATE
    if(rotate == LV_DISP_ROT_NONE)
        gfx_flag = 0;
    else
        gfx_flag = 1;
#endif

#ifdef _DISP_INIT
    ST_Screen_Init();
# endif

    fbfd = open(FBDEV_PATH, O_RDWR);
    if(fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        return;
    }
    LV_LOG_INFO("The framebuffer device was opened successfully");

    // Make sure that the display is on.
    if (ioctl(fbfd, FBIOBLANK, FB_BLANK_UNBLANK) != 0) {
        perror("ioctl(FBIOBLANK)");
        return;
    }
	
#if USE_BSD_FBDEV
    struct fbtype fb;
    unsigned line_length;

    //Get fb type
    if (ioctl(fbfd, FBIOGTYPE, &fb) != 0) {
        perror("ioctl(FBIOGTYPE)");
        return;
    }

    //Get screen width
    if (ioctl(fbfd, FBIO_GETLINEWIDTH, &line_length) != 0) {
        perror("ioctl(FBIO_GETLINEWIDTH)");
        return;
    }

    vinfo.xres = (unsigned) fb.fb_width;
    vinfo.yres = (unsigned) fb.fb_height;
    vinfo.bits_per_pixel = fb.fb_depth;
    vinfo.xoffset = 0;
    vinfo.yoffset = 0;
    finfo.line_length = line_length;
    finfo.smem_len = finfo.line_length * vinfo.yres;
#else /* USE_BSD_FBDEV */

    // Get fixed screen information
    if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        return;
    }

    // Get variable screen information
    if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        return;
    }
#endif /* USE_BSD_FBDEV */

    LV_LOG_INFO("%dx%d, %dbpp", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize =  finfo.smem_len; //finfo.line_length * vinfo.yres;    

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if((intptr_t)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        return;
    }

    // Don't initialise the memory to retain what's currently displayed / avoid clearing the screen.
    // This is important for applications that only draw to a subsection of the full framebuffer.
	#ifdef USE_GFX_ROTATE
	if(gfx_flag == 1)
	{
		 if (phyAddr == NULL)
	    {
	        // Ethan add, 2021-03-01, wechat: icarxx
	        printf("phyAddr == NULL \r\n");
	        ExecFunc(MI_SYS_MMA_Alloc("mma_heap_name0", vinfo.yres * vinfo.xres * 4, &phyAddr), MI_SUCCESS);
	        
	        ExecFunc(MI_GFX_Open(), MI_SUCCESS);
	        ExecFunc(MI_SYS_Mmap(phyAddr, vinfo.yres * vinfo.xres * 4, &u64VirAddr , FALSE), MI_SUCCESS);
	        
	        memset((void *)u64VirAddr, 0xFF, vinfo.yres * vinfo.xres * 4);
	    }
		
		memset(&stOpt, 0, sizeof(stOpt));
		//TODO: Dosomething bitblit/fill

	    //bitblit
	    stSrc.eColorFmt = E_MI_GFX_FMT_ARGB8888;
	    stSrc.u32Width = vinfo.yres;
	    stSrc.u32Height = vinfo.xres;
	    stSrc.u32Stride = vinfo.yres * 4;
	    stSrc.phyAddr = phyAddr;

	    stSrcRect.s32Xpos = 0;
	    stSrcRect.s32Ypos = 0;
	    stSrcRect.u32Width = vinfo.yres;
	    stSrcRect.u32Height = vinfo.xres;

	    //rotation
	    stDst.eColorFmt = E_MI_GFX_FMT_ARGB8888;
	    stDst.u32Width = vinfo.xres;
	    stDst.u32Height = vinfo.yres;
	    stDst.u32Stride =  vinfo.xres * 4;
	    #if LV_DUAL_FRAMEBUFFER
	        if(toggle == 1)
	            stDst.phyAddr = finfo.smem_start;
	        else
	            stDst.phyAddr = finfo.smem_start + screensize;
	    #else
	        stDst.phyAddr = finfo.smem_start;
	    #endif
	    stDstRect.s32Xpos = 0;
	    stDstRect.s32Ypos = 0;
	    stDstRect.u32Width = vinfo.yres;
	    stDstRect.u32Height = vinfo.xres;

	    if(rotate == LV_DISP_ROT_90)
	    	stOpt.eRotate = E_MI_GFX_ROTATE_90;
	    else if(rotate == LV_DISP_ROT_180)
			stOpt.eRotate = E_MI_GFX_ROTATE_180;	
        else if(rotate == LV_DISP_ROT_270)
			stOpt.eRotate = E_MI_GFX_ROTATE_270;
        else
            stOpt.eRotate = E_MI_GFX_ROTATE_0;
			
	    stOpt.u32GlobalSrcConstColor = 0xFF000000;
	    stOpt.u32GlobalDstConstColor = 0xFF000000;
	    stOpt.eMirror = E_MI_GFX_MIRROR_NONE;

	    stOpt.eSrcDfbBldOp = E_MI_GFX_DFB_BLD_ONE;
	    stOpt.eDstDfbBldOp = E_MI_GFX_DFB_BLD_ZERO;
    }
	#endif
    LV_LOG_INFO("The framebuffer device was mapped to memory successfully");

}
#else
void framebuf_setting(lv_coord_t width, lv_coord_t height, lv_coord_t depth)
{
    vinfo.xres = width;
    vinfo.yres = height;
    vinfo.xoffset = 0;
    vinfo.yoffset = 0;
    if((depth == 24)||(depth == 32))
    {
      vinfo.bits_per_pixel = 32;
    }

    finfo.line_length = width * 4;
    screensize = vinfo.xres * vinfo.yres * (vinfo.bits_per_pixel/8);
    fbp = malloc(screensize);
    if((intptr_t)fbp == -1)
    {
        perror("Error: failed to map framebuffer device to memory");
        return;
    }
}
#endif

char* get_frambuff(lv_size_t* size, lv_coord_t* datalenth, uint32_t* datasize, lv_coord_t* rotate)
{
    (void)rotate;

    size->width = vinfo.xres;
    size->height = vinfo.yres;
    if((vinfo.bits_per_pixel == 24)||(vinfo.bits_per_pixel == 32))
    {
        *datalenth = 32;
    }
    else
    {
        *datalenth = vinfo.bits_per_pixel;
    }

    *datasize = screensize;

    return fbp;
}

void fbdev_exit(void)
{
    close(fbfd);
}

/**
 * Flush a buffer to the marked area
 * @param drv pointer to driver where this function belongs
 * @param area an area where to copy `color_p`
 * @param color_p an array of pixels to copy to the `area` part of the screen
 */
void fbdev_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
	#ifdef USE_GFX_ROTATE
    if(fbp == NULL || area->x2 < 0 || area->y2 < 0 || area->x1 > vinfo.yres - 1 ||
                                                      area->y1 > vinfo.xres - 1)
    {
        lv_disp_flush_ready(drv);
        return;
    }
    /*Truncate the area to the screen*/
	int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
	int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
	int32_t act_x2 = area->x2 > vinfo.yres - 1 ? vinfo.yres- 1 : area->x2;
	int32_t act_y2 = area->y2 > vinfo.xres - 1 ? vinfo.xres - 1 : area->y2;
	#else
    if(fbp == NULL || area->x2 < 0 || area->y2 < 0 || area->x1 > (int32_t)vinfo.xres - 1 ||
                                                      area->y1 > (int32_t)vinfo.yres - 1)
    {
        lv_disp_flush_ready(drv);
        return;
    }
	
    /*Truncate the area to the screen*/
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > (int32_t)vinfo.xres - 1 ? (int32_t)vinfo.xres - 1 : area->x2;
    int32_t act_y2 = area->y2 > (int32_t)vinfo.yres - 1 ? (int32_t)vinfo.yres - 1 : area->y2;

	#endif
    lv_coord_t w = (act_x2 - act_x1 + 1);
    long int location = 0;
    long int byte_location = 0;
    unsigned char bit_location = 0;

    /*32 or 24 bit per pixel*/
    if(vinfo.bits_per_pixel == 32 || vinfo.bits_per_pixel == 24)
    {
		#ifdef USE_GFX_ROTATE
		if(gfx_flag == 0)
   		{
	        uint32_t* fbp32 = (uint32_t*)fbp;
	        int32_t y;
	        for(y = act_y1; y <= act_y2; y++)
	        {
	            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 4;
	            memcpy(&fbp32[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1) * 4);
	            color_p += w;
	        }
        }
		else
		{
			//printf(" vinfo.xres == %d vinfo.yres == %d\r\n", vinfo.xres,vinfo.yres);
	        //ExecFunc(MI_SYS_Init(), MI_SUCCESS);
			MI_SYS_Init();

	        int32_t y;
	        for(y = act_y1; y <= act_y2; y++) 
	        {
	            location = (act_x1 ) + (y ) * vinfo.yres;
	            memcpy((uint32_t *)u64VirAddr + location, (uint32_t *)color_p, (act_x2 - act_x1 + 1) * 4);
	            color_p += w;
	        }
	        
	        //ExecFunc(MI_GFX_BitBlit(&stSrc, &stSrcRect, &stDst, &stDstRect, &stOpt, &u16TargetFence), MI_SUCCESS);
	        //ExecFunc(MI_GFX_WaitAllDone(FALSE, u16TargetFence), MI_SUCCESS);
			MI_GFX_BitBlit(&stSrc, &stSrcRect, &stDst, &stDstRect, &stOpt, &u16TargetFence);
			MI_GFX_WaitAllDone(FALSE, u16TargetFence);
		}
		#else
        uint32_t* fbp32 = (uint32_t*)fbp;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++)
        {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 4;
            memcpy(&fbp32[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1) * 4);
            color_p += w;
        }
		#endif
    }
    /*16 bit per pixel*/
    else if(vinfo.bits_per_pixel == 16)
    {
        uint16_t * fbp16 = (uint16_t *)fbp;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++)
        {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 2;
            memcpy(&fbp16[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1) * 2);
            color_p += w;
        }
    }
    /*8 bit per pixel*/
    else if(vinfo.bits_per_pixel == 8)
    {
        uint8_t * fbp8 = (uint8_t *)fbp;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++)
        {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length;
            memcpy(&fbp8[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1));
            color_p += w;
        }
    }
    /*1 bit per pixel*/
    else if(vinfo.bits_per_pixel == 1)
    {
        uint8_t * fbp8 = (uint8_t *)fbp;
        int32_t x;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++)
        {
            for(x = act_x1; x <= act_x2; x++)
            {
                location = (x + vinfo.xoffset) + (y + vinfo.yoffset) * vinfo.xres;
                byte_location = location / 8; /* find the byte we need to change */
                bit_location = location % 8; /* inside the byte found, find the bit we need to change */
                fbp8[byte_location] &= ~(((uint8_t)(1)) << bit_location);
                fbp8[byte_location] |= ((uint8_t)(color_p->full)) << bit_location;
                color_p++;
            }

            color_p += area->x2 - act_x2;
        }
    }
    else
    {
        /*Not supported bit per pixel*/
    }

    //May be some direct update command is required
    //ret = ioctl(state->fd, FBIO_UPDATE, (unsigned long)((uintptr_t)rect));
    lv_disp_flush_ready(drv);
}

void fbdev_get_sizes(uint32_t *width, uint32_t *height) {
    if (width)
        *width = vinfo.xres;

    if (height)
        *height = vinfo.yres;
}

void fbdev_set_offset(uint32_t xoffset, uint32_t yoffset) {
    vinfo.xoffset = xoffset;
    vinfo.yoffset = yoffset;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif
