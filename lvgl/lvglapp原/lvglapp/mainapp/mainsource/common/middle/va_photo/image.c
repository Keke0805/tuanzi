#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "image.h"
#include "jpg_decode.h"
#include "png_decode.h"
#include "bmp_decode.h"
#ifdef _UCHIP_T113
#include <linux/input.h>
#include "ion_mem_alloc.h"
#include "jpegdecode.h"
#endif

#if USE_SUNXIFB_G2D
#include "lv_drivers/display/sunximem.h"
#endif

#define PRINT_ZXF 1
#if PRINT_ZXF
#define print_zxf(format, arg...)		printf("<***image***>%s,%d,"format"\n",__FILE__,__LINE__, ## arg);
#else
#define print_zxf(format, arg...)		do {} while (0)
#endif
#define STB_IMAGE_STATIC
#define MOSAIC_NUM 100
//#define STBI_WINDOWS_UTF8
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
//#define STB_IMAGE_RESIZE_IMPLEMENTATION
//#include "stb_image_resize.h"
//#define STB_DEFINE
//#include "stb.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// STBIDEF unsigned char *stbi_xload(char const *filename, int *x, int *y, int *frames);
static image_t image;
static image_show_mode_t show_mode;

static struct SunxiMemOpsS *ionHdle;

#define SAVE_DATA_PATH     "mnt/exUDISK/bin"
#define SAVE_DECODE_DATA   0
#define SAVE_STANDARD_DATA 0
#define SAVE_DISPLAY_DATA  0
#define SAVE_THUMB_DATA    0
#define DECODE_LIMIT_WIDTH  10000
#define DECODE_LIMIT_HEIGHT 10000
#define DECODE_LIMIT_SIZE  (DECODE_LIMIT_WIDTH*DECODE_LIMIT_HEIGHT*4)
#ifdef _UCHIP_T113
static long get_time(void)
{
	struct timeval tv2;
	gettimeofday(&tv2, NULL);
	return (long)((tv2.tv_sec) * 1000000 + tv2.tv_usec);
}

static int image_standardized(image_buffer_t *buf)
{
    image_enh_t src_enh, dst_enh;
    image_buffer_t dst;
    int ret;

    memset(&dst, 0, sizeof(dst));
    memcpy(&dst,buf,sizeof(image_buffer_t));

    dst.vir_addr = ionHdle->palloc(IMAGE_HOR_RES_MAX * IMAGE_VER_RES_MAX * 4);
    // printf("dst.vir_addr = %p\n",dst.vir_addr);
    dst.phy_addr = ionHdle->cpu_get_phyaddr(dst.vir_addr);
    dst.fd = ionHdle->get_bufferFd(dst.vir_addr);
    dst.comp  = 4;//buf->comp;
    dst.width  = IMAGE_HOR_RES_MAX;//disp_info.disp_rect.w;
    dst.height = IMAGE_VER_RES_MAX;//disp_info.disp_rect.h;
    dst.length = dst.width * dst.height * dst.comp;
    dst.fmt = IMAGE_FORMAT_ARGB8888;

    memset(&src_enh, 0, sizeof(src_enh));
    memset(&dst_enh, 0, sizeof(dst_enh));

    src_enh.buf = *buf;
    src_enh.clip_rect.w = buf->width;
    src_enh.clip_rect.h = buf->height;

    dst_enh.buf = dst;
    dst_enh.clip_rect.w = dst.width;
    dst_enh.clip_rect.h = dst.height;

    ret = image.opr.process->scaler(&src_enh, &dst_enh);

    if(ret < 0)
    {
        return ret;
    }
    if(buf->vir_addr)
    {
    	ionHdle->pfree(buf->vir_addr);
		buf->vir_addr = NULL;
    }
    buf->comp = 4;
    buf->width = dst.width;
    buf->height = dst.height;
    buf->length = buf->width*buf->height*buf->comp;
    buf->vir_addr = dst.vir_addr;
    buf->phy_addr = dst.phy_addr;
    buf->fmt = IMAGE_FORMAT_ARGB8888;
    buf->fd = dst.fd;

    return 0;

}

static int sunxi_image_rotate_scaler_standardized(image_buffer_t *buf,image_rotate_angle_t rotate_angle)
{

	image_enh_t src_enh, dst_enh;
	image_buffer_t dst;
	int ret;
	int width =0,height =0;

	memset(&dst, 0, sizeof(dst));
	memcpy(&dst,buf,sizeof(image_buffer_t));

	if((buf->width * IMAGE_HOR_RES_MAX) < (buf->height * IMAGE_VER_RES_MAX))
	{
		height = IMAGE_HOR_RES_MAX;
		width = (IMAGE_HOR_RES_MAX * buf->width) / buf->height;
	}
	else
	{
		width = IMAGE_VER_RES_MAX;
		height = (buf->height * IMAGE_VER_RES_MAX) / buf->width;
	}
	
	//print_zxf("width:%d  height:%d",width,height);
	dst.vir_addr = ionHdle->palloc(IMAGE_HOR_RES_MAX * IMAGE_VER_RES_MAX * 4);
	//printf("dst.vir_addr = %p\n",dst.vir_addr);
	dst.phy_addr = ionHdle->cpu_get_phyaddr(dst.vir_addr);
	dst.fd = ionHdle->get_bufferFd(dst.vir_addr);
	dst.comp  = 4;//buf->comp;
	
	dst.width  = width;//disp_info.disp_rect.w;
	dst.height = height;//disp_info.disp_rect.h;
	dst.length = dst.width * dst.height * dst.comp;
	dst.fmt = IMAGE_FORMAT_ARGB8888;

	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh.buf = *buf;
	src_enh.clip_rect.w = buf->width;
	src_enh.clip_rect.h = buf->height;

	dst_enh.buf = dst;
	dst_enh.clip_rect.w = dst.width;
	dst_enh.clip_rect.h = dst.height;

	ret = image.opr.process->scaler(&src_enh, &dst_enh);
	//printf("resize ret = %d\n",ret);

	if(ret < 0)
	{
		printf("g2d error: ret = %d\n",ret);
		return ret;
	}
	if(buf->vir_addr)
	{
		ionHdle->pfree(buf->vir_addr);
		buf->vir_addr = NULL;
	}
	buf->comp = 4;
	buf->width = dst.width;
	buf->height = dst.height;
	buf->length = buf->width*buf->height*buf->comp;
	buf->vir_addr = dst.vir_addr;
	buf->phy_addr = dst.phy_addr;
	buf->fmt = IMAGE_FORMAT_ARGB8888;
	buf->fd = dst.fd;
	return 0;
}

static int sunxi_image_rotate_fullsrceen_standardized(image_buffer_t *buf,image_rotate_angle_t rotate_angle)
{

	image_enh_t src_enh, dst_enh;
	image_buffer_t dst;
	int ret;

	memset(&dst, 0, sizeof(dst));
	memcpy(&dst,buf,sizeof(image_buffer_t));

	dst.vir_addr = ionHdle->palloc(IMAGE_HOR_RES_MAX * IMAGE_VER_RES_MAX * 4);
	// printf("dst.vir_addr = %p\n",dst.vir_addr);
	dst.phy_addr = ionHdle->cpu_get_phyaddr(dst.vir_addr);
	dst.fd = ionHdle->get_bufferFd(dst.vir_addr);
	dst.comp  = 4;//buf->comp;

    dst.width  = IMAGE_VER_RES_MAX;//disp_info.disp_rect.w;
    dst.height = IMAGE_HOR_RES_MAX;//disp_info.disp_rect.h;
	//print_zxf("width:%d  height:%d",dst.width,dst.height);
	dst.length = dst.width * dst.height * dst.comp;
	dst.fmt = IMAGE_FORMAT_ARGB8888;

	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh.buf = *buf;
	src_enh.clip_rect.w = buf->width;
	src_enh.clip_rect.h = buf->height;

	dst_enh.buf = dst;
	dst_enh.clip_rect.w = dst.width;
	dst_enh.clip_rect.h = dst.height;

	ret = image.opr.process->scaler(&src_enh, &dst_enh);

	if(ret < 0)
	{
		   return ret;
	}
	if(buf->vir_addr)
	{
		ionHdle->pfree(buf->vir_addr);
		buf->vir_addr = NULL;
	}
	buf->comp = 4;
	buf->width = dst_enh.clip_rect.w;
	buf->height = dst_enh.clip_rect.h;
	buf->length = buf->width*buf->height*buf->comp;
	buf->vir_addr = dst.vir_addr;
	buf->phy_addr = dst.phy_addr;
	buf->fmt = IMAGE_FORMAT_ARGB8888;
	buf->fd = dst.fd;
	return 0;
}

static int sunxi_image_scaler_adapt_standardized(image_buffer_t *buf, unsigned int width, unsigned int height)
{
	image_enh_t src_enh, dst_enh;
	unsigned int scaler_width, scaler_height;
	int ret,ratio_percent;
	image_buffer_t dst;

	memset(&dst, 0, sizeof(dst));
	memcpy(&dst,buf,sizeof(image_buffer_t));
	dst.vir_addr = ionHdle->palloc(IMAGE_HOR_RES_MAX * IMAGE_VER_RES_MAX * 4);
	dst.phy_addr = ionHdle->cpu_get_phyaddr(dst.vir_addr);
	dst.fd = ionHdle->get_bufferFd(dst.vir_addr);
	dst.comp  = 4;//buf->comp;
    dst.width  = buf->width;
    dst.height = buf->height;
	dst.length = dst.width * dst.height * dst.comp;
	dst.fmt = IMAGE_FORMAT_ARGB8888;

	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	uint32_t y_a= height * buf->width;
	uint32_t x_b= width * buf->height;

	if (x_b <= y_a)
	{
		ratio_percent = height*100/buf->height;
		scaler_width = height * buf->width / buf->height;
		scaler_height = height * buf->height / buf->height;
	}
	else
	{
		ratio_percent = width*100/buf->width;
		scaler_width = width * buf->width/ buf->width;
		scaler_height = width * buf->height/ buf->width;
	}
	
	if (scaler_width > IMAGE_VER_RES_MAX) {
		scaler_width = IMAGE_VER_RES_MAX;
		scaler_height = buf->height * scaler_width / buf->width;
	}
	if (scaler_height > IMAGE_HOR_RES_MAX) {
		scaler_height = IMAGE_HOR_RES_MAX;
		scaler_width = buf->width * scaler_height / buf->height;
	}

	src_enh.buf = *buf;
	src_enh.clip_rect.w = (width*100/ratio_percent)<(buf->width)? (width*100/ratio_percent) : buf->width;
	src_enh.clip_rect.h = (height*100/ratio_percent)<(buf->height)? (height*100/ratio_percent) : buf->height;
	src_enh.clip_rect.x = (src_enh.buf.width-src_enh.clip_rect.w)/2;
	src_enh.clip_rect.y = (src_enh.buf.height-src_enh.clip_rect.h)/2;
	src_enh.coor.x = 0;
	src_enh.coor.y = 0;

	dst_enh.buf = dst;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	dst_enh.buf.width = IMAGE_VER_RES_MAX;
	dst_enh.buf.height = IMAGE_HOR_RES_MAX;
	dst_enh.buf.comp = src_enh.buf.comp;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.w = IMAGE_VER_RES_MAX;
	dst_enh.clip_rect.h = IMAGE_HOR_RES_MAX;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	ret = image.opr.process->scaler(&src_enh, &dst_enh);
	if(ret <0)
	{
		print_zxf("image.opr.process->scaler fail !!!");
		return -1;
	}
	
	if(buf->vir_addr)
	{
		ionHdle->pfree(buf->vir_addr);
		buf->vir_addr = NULL;
	}
	buf->comp = 4;
	buf->width = dst_enh.clip_rect.w;
	buf->height = dst_enh.clip_rect.h;
	buf->length = buf->width*buf->height*buf->comp;
	buf->vir_addr = dst.vir_addr;
	buf->phy_addr = dst.phy_addr;
	buf->fmt = IMAGE_FORMAT_ARGB8888;
	buf->fd = dst.fd;

	return 0;
err:
	return ret;
}

static int sunxi_image_scaler_fullsrceen_standardized(image_buffer_t *buf, unsigned int width, unsigned int height)
{
	image_enh_t src_enh, dst_enh;
	unsigned int scaler_width, scaler_height;
	int ret,ratio_percent;
	image_buffer_t dst;

	memset(&dst, 0, sizeof(dst));
	memcpy(&dst,buf,sizeof(image_buffer_t));
	dst.vir_addr = ionHdle->palloc(IMAGE_HOR_RES_MAX * IMAGE_VER_RES_MAX * 4);
	dst.phy_addr = ionHdle->cpu_get_phyaddr(dst.vir_addr);
	dst.fd = ionHdle->get_bufferFd(dst.vir_addr);
	dst.comp  = 4;//buf->comp;
    dst.width  = IMAGE_VER_RES_MAX;
    dst.height = IMAGE_HOR_RES_MAX;
	dst.length = dst.width * dst.height * dst.comp;
	dst.fmt = IMAGE_FORMAT_ARGB8888;
	
	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh.buf = *buf;
	src_enh.clip_rect.w = src_enh.buf.width*src_enh.buf.width/width;
	src_enh.clip_rect.h = src_enh.buf.height*src_enh.buf.height/height;
	src_enh.clip_rect.x = (src_enh.buf.width-src_enh.clip_rect.w)/2;
	src_enh.clip_rect.y = (src_enh.buf.height-src_enh.clip_rect.h)/2;
	src_enh.coor.x = 0;
	src_enh.coor.y = 0;

	dst_enh.buf = dst;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	dst_enh.buf.width = IMAGE_VER_RES_MAX;
	dst_enh.buf.height = IMAGE_HOR_RES_MAX;
	dst_enh.buf.comp = src_enh.buf.comp;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.w = IMAGE_VER_RES_MAX;
	dst_enh.clip_rect.h = IMAGE_HOR_RES_MAX;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	ret = image.opr.process->scaler(&src_enh, &dst_enh);
	if(ret <0)
	{
		print_zxf("image.opr.process->scaler fail !!!");
		return -1;
	}

	if(buf->vir_addr)
	{
		ionHdle->pfree(buf->vir_addr);
		buf->vir_addr = NULL;
	}
	buf->comp = 4;
	buf->width = dst_enh.clip_rect.w;
	buf->height = dst_enh.clip_rect.h;
	buf->length = buf->width*buf->height*buf->comp;
	buf->vir_addr = dst.vir_addr;
	buf->phy_addr = dst.phy_addr;
	buf->fmt = IMAGE_FORMAT_ARGB8888;
	buf->fd = dst.fd;
	
	return 0;
err:
	return ret;
}

static int sunxi_image_scaler_fullsrceen_move_standardized(image_buffer_t *buf, unsigned int width, unsigned int height ,int x_off,int y_off)
{
	image_enh_t src_enh, dst_enh;
	unsigned int scaler_width, scaler_height;
	int ret,ratio_percent;
	image_buffer_t dst;

	memset(&dst, 0, sizeof(dst));
	memcpy(&dst,buf,sizeof(image_buffer_t));
	dst.vir_addr = ionHdle->palloc(IMAGE_HOR_RES_MAX * IMAGE_VER_RES_MAX * 4);
	dst.phy_addr = ionHdle->cpu_get_phyaddr(dst.vir_addr);
	dst.fd = ionHdle->get_bufferFd(dst.vir_addr);
	dst.comp  = 4;//buf->comp;
    dst.width  = IMAGE_VER_RES_MAX;
    dst.height = IMAGE_HOR_RES_MAX;
	dst.length = dst.width * dst.height * dst.comp;
	dst.fmt = IMAGE_FORMAT_ARGB8888;
	
	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh.buf = *buf;
	src_enh.clip_rect.w = src_enh.buf.width*src_enh.buf.width/width;
	src_enh.clip_rect.h = src_enh.buf.height*src_enh.buf.height/height;
	
	src_enh.clip_rect.x = (src_enh.buf.width-src_enh.clip_rect.w)/2;
	src_enh.clip_rect.x -= x_off;
	//print_zxf("src_enh.clip_rect.x = %d !!!",src_enh.clip_rect.x);
	if(src_enh.clip_rect.x < 0)
	{
		src_enh.clip_rect.x = 0;
	}
	else if(src_enh.clip_rect.x>(src_enh.buf.width-src_enh.clip_rect.w))
	{
		src_enh.clip_rect.x = src_enh.buf.width-src_enh.clip_rect.w;
	}
	src_enh.clip_rect.y = (src_enh.buf.height-src_enh.clip_rect.h)/2;
	src_enh.clip_rect.y -= y_off;
	//print_zxf("src_enh.clip_rect.y = %d !!!",src_enh.clip_rect.y);
	if(src_enh.clip_rect.y < 0)
	{
		src_enh.clip_rect.y = 0;
	}
	else if(src_enh.clip_rect.y>(src_enh.buf.height-src_enh.clip_rect.h))
	{
		src_enh.clip_rect.y = src_enh.buf.height-src_enh.clip_rect.h;
	}
	src_enh.coor.x = 0;
	src_enh.coor.y = 0;

	dst_enh.buf = dst;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	dst_enh.buf.width = IMAGE_VER_RES_MAX;
	dst_enh.buf.height = IMAGE_HOR_RES_MAX;
	dst_enh.buf.comp = src_enh.buf.comp;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.w = IMAGE_VER_RES_MAX;
	dst_enh.clip_rect.h = IMAGE_HOR_RES_MAX;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	ret = image.opr.process->scaler(&src_enh, &dst_enh);
	if(ret <0)
	{
		print_zxf("image.opr.process->scaler fail !!!");
		return -1;
	}

	if(buf->vir_addr)
	{
		ionHdle->pfree(buf->vir_addr);
		buf->vir_addr = NULL;
	}
	buf->comp = 4;
	buf->width = dst_enh.clip_rect.w;
	buf->height = dst_enh.clip_rect.h;
	buf->length = buf->width*buf->height*buf->comp;
	buf->vir_addr = dst.vir_addr;
	buf->phy_addr = dst.phy_addr;
	buf->fmt = IMAGE_FORMAT_ARGB8888;
	buf->fd = dst.fd;
	
	return 0;
err:
	return ret;
}


static int sunxi_image_scaler_standardized(image_buffer_t *buf)
{

	 image_enh_t src_enh, dst_enh;
	 image_buffer_t dst;
	 int ret;
	 int width =0,height =0;

	 memset(&dst, 0, sizeof(dst));
	 memcpy(&dst,buf,sizeof(image_buffer_t));

	 if((buf->width * IMAGE_VER_RES_MAX) < (buf->height * IMAGE_HOR_RES_MAX))
	 {
	    height = IMAGE_VER_RES_MAX;
	    width = (IMAGE_VER_RES_MAX * buf->width) / buf->height;
	 }
	 else
	 {
	    width = IMAGE_HOR_RES_MAX;
	    height = (buf->height * IMAGE_HOR_RES_MAX) / buf->width;
	 }

	 //print_zxf("width:%d  height:%d",width,height);
	 dst.vir_addr = ionHdle->palloc(width * height * 4);
	 //printf("dst.vir_addr = %p\n",dst.vir_addr);
	 dst.phy_addr = ionHdle->cpu_get_phyaddr(dst.vir_addr);
	 dst.fd = ionHdle->get_bufferFd(dst.vir_addr);
	 dst.comp  = 4;//buf->comp;
 
	 dst.width  = width;//disp_info.disp_rect.w;
	 dst.height = height;//disp_info.disp_rect.h;
	 dst.length = dst.width * dst.height * dst.comp;
	 dst.fmt = IMAGE_FORMAT_ARGB8888;

	 memset(&src_enh, 0, sizeof(src_enh));
	 memset(&dst_enh, 0, sizeof(dst_enh));

	 src_enh.buf = *buf;
	 src_enh.clip_rect.w = buf->width;
	 src_enh.clip_rect.h = buf->height;

	 dst_enh.buf = dst;
	 dst_enh.clip_rect.w = dst.width;
	 dst_enh.clip_rect.h = dst.height;

	 ret = image.opr.process->scaler(&src_enh, &dst_enh);
	 //printf("resize ret = %d\n",ret);

	 if(ret < 0)
	 {
	  	return ret;
	 }
	 if(buf->vir_addr)
	 {
	  	ionHdle->pfree(buf->vir_addr);
	 }
	 buf->comp = 4;
	 buf->width = dst.width;
	 buf->height = dst.height;
	 buf->length = buf->width*buf->height*buf->comp;
	 buf->vir_addr = dst.vir_addr;
	 buf->phy_addr = dst.phy_addr;
	 buf->fmt = IMAGE_FORMAT_ARGB8888;
	 buf->fd = dst.fd;
	 return 0;

}



static int sunxi_image_scaler_zoom(image_buffer_t *buf, int *ratio_percent)
{
	image_enh_t src_enh, dst_enh;
	unsigned int scaler_width, scaler_height;
	int ret;


	scaler_width = *ratio_percent * buf->width / 100;
	scaler_height = *ratio_percent * buf->height / 100;
	if (scaler_width > IMAGE_HOR_RES_MAX) {
		scaler_width = IMAGE_HOR_RES_MAX;
		scaler_height = buf->height * scaler_width / buf->width;
	}
	if (scaler_height > IMAGE_VER_RES_MAX) {
		scaler_height = IMAGE_VER_RES_MAX;
		scaler_width = buf->width * scaler_height / buf->height;
	}

	src_enh.buf = *buf;
	src_enh.clip_rect.w = src_enh.buf.width;
	src_enh.clip_rect.h = src_enh.buf.height;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;

	dst_enh.buf.phy_addr = buf->phy_addr;
	dst_enh.buf.vir_addr = buf->vir_addr;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	dst_enh.buf.width = scaler_width;
	dst_enh.buf.height = scaler_height;
	dst_enh.buf.comp = src_enh.buf.comp;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.w = scaler_width;
	dst_enh.clip_rect.h = scaler_height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	image.opr.process->scaler(&src_enh, &dst_enh);

	buf->width = scaler_width;
	buf->height = scaler_height;
	buf->length = buf->width * buf->height * buf->comp;

	*ratio_percent = scaler_height * 100 / buf->height;
	buf->scaler_ratito = *ratio_percent;
	//printf("image scaler change! = %d\n",buf->scaler_ratito);

	return 0;
err:
	return ret;
}

static int sunxi_image_scaler(image_buffer_t *buf, unsigned int scaler_width, unsigned int scaler_height)
{
	image_enh_t src_enh, dst_enh;
	unsigned int ratio_w, ratio_h;
	int ret;
	int ratio_percent;

	if (scaler_width > IMAGE_HOR_RES_MAX) {
		scaler_width = IMAGE_HOR_RES_MAX;
		scaler_height = buf->height * scaler_width / buf->width;
	}
	if (scaler_height > IMAGE_VER_RES_MAX) {
		scaler_height = IMAGE_VER_RES_MAX;
		scaler_width = buf->width * scaler_height / buf->height;
	}

	src_enh.buf = *buf;
	src_enh.clip_rect.w = src_enh.buf.width;
	src_enh.clip_rect.h = src_enh.buf.height;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;

	dst_enh.buf.phy_addr = buf->phy_addr;
	dst_enh.buf.vir_addr = buf->vir_addr;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	dst_enh.buf.width = scaler_width;
	dst_enh.buf.height = scaler_height;
	dst_enh.buf.comp = src_enh.buf.comp;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.w = scaler_width;
	dst_enh.clip_rect.h = scaler_height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	image.opr.process->scaler(&src_enh, &dst_enh);

	buf->width = scaler_width;
	buf->height = scaler_height;
	buf->length = buf->width * buf->height * buf->comp;

	//*ratio_percent = scaler_height * 100 / buf->height;
	//buf->scaler_ratito = *ratio_percent;
	buf->scaler_ratito = scaler_height * 100 / buf->height;
    //printf("image scaler change! = %d\n",buf->scaler_ratito);

	return 0;
err:
	return ret;
}

static int sunxi_image_scaler_adapt(image_buffer_t *buf, unsigned int width, unsigned int height)
{
	image_enh_t src_enh, dst_enh;
	unsigned int scaler_width, scaler_height;
	int ret,ratio_percent;

    uint32_t y_a= height * buf->width;
    uint32_t x_b= width * buf->height;

    if (x_b <= y_a)
    {
    	ratio_percent = height*100/buf->height;
		scaler_width = height * buf->width / buf->height;
		scaler_height = height * buf->height / buf->height;
    }
    else
    {
    	ratio_percent = width*100/buf->width;
		scaler_width = width * buf->width/ buf->width;
		scaler_height = width * buf->height/ buf->width;
    }
	
	if (scaler_width > IMAGE_HOR_RES_MAX) {
		scaler_width = IMAGE_HOR_RES_MAX;
		scaler_height = buf->height * scaler_width / buf->width;
	}
	if (scaler_height > IMAGE_VER_RES_MAX) {
		scaler_height = IMAGE_VER_RES_MAX;
		scaler_width = buf->width * scaler_height / buf->height;
	}
	
	src_enh.buf = *buf;
	src_enh.clip_rect.w = (width*100/ratio_percent)<(buf->width)? (width*100/ratio_percent) : buf->width;
	src_enh.clip_rect.h = (height*100/ratio_percent)<(buf->height)? (height*100/ratio_percent) : buf->height;
	src_enh.clip_rect.x = (src_enh.buf.width-src_enh.clip_rect.w)/2;
	src_enh.clip_rect.y = (src_enh.buf.height-src_enh.clip_rect.h)/2;
	src_enh.coor.x = 0;
	src_enh.coor.y = 0;

	dst_enh.buf.phy_addr = buf->phy_addr;
	dst_enh.buf.vir_addr = buf->vir_addr;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	dst_enh.buf.width = width;
	dst_enh.buf.height = height;
	dst_enh.buf.comp = src_enh.buf.comp;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.w = width;
	dst_enh.clip_rect.h = height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	ret = image.opr.process->scaler(&src_enh, &dst_enh);
	if(ret <0)
	{
		print_zxf("image.opr.process->scaler fail !!!");
		return -1;
	}

	buf->width = width;
	buf->height = height;
	buf->length = buf->width * buf->height * buf->comp;

	return 0;
err:
	return ret;
}


/* for debug */
static int image_save_file(image_buffer_t *src, const char *file_name)
{
	int ret;
	FILE *fd;

	if ((fd = fopen(file_name, "wb+")) == NULL) {
		printf("open file %s fail. \n", file_name);
		ret = -1;
		goto err;
	}
	ret = fwrite(src->vir_addr, src->length, 1, fd);
	//printf("%s: length = %d, ret = %d !!!\n", __func__, src->length, ret);

	fsync(fd);
	fclose(fd);

err:
	return 0;
}
/*通用存数据方法*/
// static int save_data_for_check(void* addr[3],int width,int height,char *name,int flag)
// {
//	FILE *fd;
//	char *filename[100];
//	int ret;
//	if(flag == 0){
//		return 0;
//	}

//	if(addr[0] != NULL && addr[1] == NULL && addr[2] == NULL){
//		sprintf(filename,SAVE_DATA_PATH"%s_%d_%d_argb.bin",name,width,height);
//		if ((fd = fopen(filename, "wb+")) == NULL) {
//			printf("open file %s fail. \n", filename);
//			ret = -1;
//			goto err;
//		}
//		ret = fwrite(src->addr[0], width*height*4, 1, fd);
//		printf("%s: length = %d, ret = %d !!!\n", __func__, src->length, ret);
//		fclose(fd);
//		system("sync");
//	}
//	else if(addr[0] != NULL && addr[1] != NULL && addr[2] == NULL){
//		sprintf(filename,SAVE_DATA_PATH"%s_%d_%d_y.bin",name,width,height);
//		if ((fd = fopen(filename, "wb+")) == NULL) {
//			printf("open file %s fail. \n", filename);
//			ret = -1;
//			goto err;
//		}
//		ret = fwrite(src->addr[0], width*height, 1, fd);
//		printf("%s: length = %d, ret = %d !!!\n", __func__, src->length, ret);
//		fclose(fd);
//		system("sync");

//		sprintf(filename,SAVE_DATA_PATH"%s_%d_%d_uv.bin",name,width,height);
//		if ((fd = fopen(filename, "wb+")) == NULL) {
//			printf("open file %s fail. \n", filename);
//			ret = -1;
//			goto err;
//		}
//		ret = fwrite(src->addr[0], width*height/2, 1, fd);
//		printf("%s: length = %d, ret = %d !!!\n", __func__, src->length, ret);
//		fclose(fd);
//		system("sync");
//	}
//	else if(addr[0] != NULL && addr[1] != NULL && addr[2] != NULL){
//		sprintf(filename,SAVE_DATA_PATH"%s_%d_%d_y.bin",name,width,height);
//		if ((fd = fopen(filename, "wb+")) == NULL) {
//			printf("open file %s fail. \n", filename);
//			ret = -1;
//			goto err;
//		}
//		ret = fwrite(src->addr[0], width*height, 1, fd);
//		printf("%s: length = %d, ret = %d !!!\n", __func__, src->length, ret);
//		fclose(fd);
//		system("sync");

//		sprintf(filename,SAVE_DATA_PATH"%s_%d_%d_u.bin",name,width,height);
//		if ((fd = fopen(filename, "wb+")) == NULL) {
//			printf("open file %s fail. \n", filename);
//			ret = -1;
//			goto err;
//		}
//		ret = fwrite(src->addr[0], width*height/4, 1, fd);
//		printf("%s: length = %d, ret = %d !!!\n", __func__, src->length, ret);
//		fclose(fd);
//		system("sync");

//		sprintf(filename,SAVE_DATA_PATH"%s_%d_%d_v.bin",name,width,height);
//		if ((fd = fopen(filename, "wb+")) == NULL) {
//			printf("open file %s fail. \n", filename);
//			ret = -1;
//			goto err;
//		}
//		ret = fwrite(src->addr[0], width*height/4, 1, fd);
//		printf("%s: length = %d, ret = %d !!!\n", __func__, src->length, ret);
//		fclose(fd);
//		system("sync");
//	}
//	return ret;
// err:
//	return -1;
// }

static void image_dst_buffer_switch(void)
{
	int ret;
	image_buffer_t dst_tmp;

	dst_tmp = image.dst_previous;
	image.dst_previous = image.dst_next;
	image.dst_next = dst_tmp;
}

static void image_full_buffer_switch(void)
{
	int ret;
	image_buffer_t dst_tmp;

	dst_tmp = image.dst_previous;
	image.dst_previous = image.full_buf;
	image.full_buf = dst_tmp;
}

static int image_show_persianblind1(image_buffer_t *src)
{
	int i, size;
	image_disp_info_t disp_info;

	image.opr.display->disp_info_get(&disp_info);
	size = disp_info.screen_width * disp_info.screen_height * 4;
	for (i = 0; i < disp_info.screen_height / 8; i++) {
		memcpy(disp_info.fb_vir + (disp_info.screen_width * i * 4), \
			src->vir_addr + (src->width * i * 4), src->width * 4);
		memcpy(disp_info.fb_vir + (size / 8) + (disp_info.screen_width * i * 4), \
			src->vir_addr + (src->length / 8) + (src->width * i * 4), src->width * 4);
		memcpy(disp_info.fb_vir + (size / 8 * 2) + (disp_info.screen_width * i * 4), \
			src->vir_addr + (src->length / 8 * 2) + (src->width * i * 4), src->width * 4);
		memcpy(disp_info.fb_vir + (size / 8 * 3) + (disp_info.screen_width * i * 4), \
			src->vir_addr + (src->length / 8 * 3) + (src->width * i * 4), src->width * 4);
		memcpy(disp_info.fb_vir + (size / 8 * 4) + (disp_info.screen_width * i * 4), \
			src->vir_addr + (src->length / 8 * 4) + (src->width * i * 4), src->width * 4);
		memcpy(disp_info.fb_vir + (size / 8 * 5) + (disp_info.screen_width * i * 4), \
			src->vir_addr + (src->length / 8 * 5) + (src->width * i * 4), src->width * 4);
		memcpy(disp_info.fb_vir + (size / 8 * 6) + (disp_info.screen_width * i * 4), \
			src->vir_addr + (src->length / 8 * 6) + (src->width * i * 4), src->width * 4);
		memcpy(disp_info.fb_vir + (size / 8 * 7) + (disp_info.screen_width * i * 4), \
			src->vir_addr + (src->length / 8 * 7) + (src->width * i * 4), src->width * 4);
		ionHdle->flush_cache(disp_info.fb_vir, size);
		usleep(20000);
	}

	return 0;
}

static int  block_copy(char *src_addr,int src_width,int src_height,char*dst_addr,image_rect_t *rect)
{
	int i;
	char *src_start = src_addr+((rect->x+src_width*rect->y)<<2);
	char *dst_start = dst_addr+((rect->x+src_width*rect->y)<<2);

	for(i=0;i<rect->h;i++)
	{
		memcpy(dst_start,src_start,rect->w*4);
		dst_start+=(src_width<<2);
		src_start+=(src_width<<2);
	}

	return 0;
}

static int image_show_persianblind_step(image_buffer_t *src,int mode,int step ,int loop)
{
	int i,j, size;
	image_disp_info_t disp_info;
	int fans ;//暂时固定为8叶
	int fan_len;
	int last_fan_len;
	int step_len;
	int steps;
	int last_step_len;

	image.opr.display->disp_info_get(&disp_info);
	size = disp_info.screen_width * disp_info.screen_height * 4;
	image_rect_t rect;

    if (mode == IMAGE_SHOW_PERSIANBLIND_H)
    {
		fans = 8;
        fan_len = disp_info.screen_height / fans;
        last_step_len = disp_info.screen_height % fans;
        step_len = fan_len / 30;
		steps = fan_len/step_len;
		last_fan_len = fan_len%steps;
    }
    else
    {
		fans = 12;
        fan_len = disp_info.screen_width / fans;
        last_fan_len = disp_info.screen_width % fans;
        step_len = fan_len / 30;
		steps = fan_len/step_len;
		last_step_len = fan_len%steps;
    }
	switch(mode)
	{
		case IMAGE_SHOW_PERSIANBLIND_H:
			if(loop)
			{
				for(i=0;i<steps;i++)
				{
					for(j=0;j<fans;j++)
					{
						rect.x = 0;
						rect.y = i*step_len+j*fan_len;
						rect.w = disp_info.screen_width;
						rect.h = step_len;
						block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					}
					ionHdle->flush_cache(disp_info.fb_vir, size);
					usleep(5000);
				}
				if(last_step_len)
				{
					for(j=0;j<fans;j++)
					{
						rect.x = 0;
						rect.y = i*step_len+j*fan_len;
						rect.w = disp_info.screen_width;
						rect.h = last_step_len;
						block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					}
					ionHdle->flush_cache(disp_info.fb_vir, size);
					usleep(5000);
				}
				if(last_fan_len)
				{
					rect.x = 0;
					rect.y = disp_info.screen_height-last_fan_len;
					rect.w = disp_info.screen_width;
					rect.h = last_fan_len;
					block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					ionHdle->flush_cache(disp_info.fb_vir, size);
				}
			}
			else
			{
				steps = step*30/disp_info.screen_height;
				for(i=0;i<steps;i++)
				{
					for(j=0;j<fans;j++)
					{
						rect.x = 0;
						rect.y = i*step_len+j*fan_len;
						rect.w = disp_info.screen_width;
						rect.h = step_len;
						block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					}
					ionHdle->flush_cache(disp_info.fb_vir, size);
					usleep(5000);
				}
				if(last_step_len)
				{
					for(j=0;j<fans;j++)
					{
						rect.x = 0;
						rect.y = i*step_len+j*fan_len;
						rect.w = disp_info.screen_width;
						rect.h = last_step_len;
						block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					}
					ionHdle->flush_cache(disp_info.fb_vir, size);
					usleep(5000);
				}
				if(last_fan_len)
				{
					rect.x = 0;
					rect.y = disp_info.screen_height-last_fan_len;
					rect.w = disp_info.screen_width;
					rect.h = last_fan_len;
					block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					ionHdle->flush_cache(disp_info.fb_vir, size);
				}
			}
			break;
		case IMAGE_SHOW_PERSIANBLIND_V:
			if(loop)
			{
				for(i=0;i<steps;i++)
				{
					for(j=0;j<fans;j++)
					{
						rect.x = i*step_len+j*fan_len;
						rect.y = 0;
						rect.w = step_len;
						rect.h = disp_info.screen_height;
						block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					}
					ionHdle->flush_cache(disp_info.fb_vir,size);
					usleep(5000);
				}
				if(last_step_len != 0)
				{
					for(j=0;j<fans;j++)
					{
						rect.x = i*step_len+j*fan_len;
						rect.y = 0;
						rect.w = last_step_len;
						rect.h = disp_info.screen_height;
						block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					}
					ionHdle->flush_cache(disp_info.fb_vir, size);
					usleep(10000);
				}
				if(last_fan_len)
				{
					rect.x = disp_info.screen_width-last_fan_len;
					rect.y = 0;
					rect.w = last_fan_len;
					rect.h = disp_info.screen_height;
					block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					ionHdle->flush_cache(disp_info.fb_vir, size);
				}
			}
			else
			{
				steps = step*30/disp_info.screen_width;
				for(i=0;i<steps;i++)
				{
					for(j=0;j<fans;j++)
					{
						rect.x = i*step_len+j*fan_len;
						rect.y = 0;
						rect.w = step_len;
						rect.h = disp_info.screen_height;
						block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					}
					ionHdle->flush_cache(disp_info.fb_vir,size);
					usleep(5000);
				}
				if(last_step_len != 0)
				{
					for(j=0;j<fans;j++)
					{
						rect.x = i*step_len+j*fan_len;
						rect.y = 0;
						rect.w = last_step_len;
						rect.h = disp_info.screen_height;
						block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					}
					ionHdle->flush_cache(disp_info.fb_vir, size);
					usleep(10000);
				}
				if(last_fan_len)
				{
					rect.x = disp_info.screen_width-last_fan_len;
					rect.y = 0;
					rect.w = last_fan_len;
					rect.h = disp_info.screen_height;
					block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
					ionHdle->flush_cache(disp_info.fb_vir, size);
				}
			}
			break;
	}
	return 0;
}


static int image_show_persianblind(image_buffer_t *src,int mode)
{
	int i,j, size;
	image_disp_info_t disp_info;
	int fans ;//暂时固定为8叶
	int fan_len;
	int last_fan_len;
	int step_len;
	int steps;
	int last_step_len;

	image.opr.display->disp_info_get(&disp_info);
	size = disp_info.screen_width * disp_info.screen_height * 4;
	image_rect_t rect;

    if (mode == IMAGE_SHOW_PERSIANBLIND_H)
    {
		fans = 8;
        fan_len = disp_info.screen_height / fans;
        last_step_len = disp_info.screen_height % fans;
        step_len = fan_len / 30;
		steps = fan_len/step_len;
		last_fan_len = fan_len%steps;
    }
    else
    {
		fans = 12;
        fan_len = disp_info.screen_width / fans;
        last_fan_len = disp_info.screen_width % fans;
        step_len = fan_len / 30;
		steps = fan_len/step_len;
		last_step_len = fan_len%steps;

    }

	switch(mode)
	{
		case IMAGE_SHOW_PERSIANBLIND_H:
			for(i=0;i<steps;i++)
			{
				for(j=0;j<fans;j++)
				{
					rect.x = 0;
					rect.y = i*step_len+j*fan_len;
					rect.w = disp_info.screen_width;
					rect.h = step_len;
					block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
				}
				ionHdle->flush_cache(disp_info.fb_vir, size);
				usleep(5000);
			}
			if(last_step_len)
			{
				for(j=0;j<fans;j++)
				{
					rect.x = 0;
					rect.y = i*step_len+j*fan_len;
					rect.w = disp_info.screen_width;
					rect.h = last_step_len;
					block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
				}
				ionHdle->flush_cache(disp_info.fb_vir, size);
				usleep(5000);
			}
			if(last_fan_len)
			{
				rect.x = 0;
				rect.y = disp_info.screen_height-last_fan_len;
				rect.w = disp_info.screen_width;
				rect.h = last_fan_len;
				block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
				ionHdle->flush_cache(disp_info.fb_vir, size);
			}
			break;
		case IMAGE_SHOW_PERSIANBLIND_V:
			for(i=0;i<steps;i++)
			{
				for(j=0;j<fans;j++)
				{
					rect.x = i*step_len+j*fan_len;
					rect.y = 0;
					rect.w = step_len;
					rect.h = disp_info.screen_height;
					block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
				}
				ionHdle->flush_cache(disp_info.fb_vir,size);
				usleep(5000);
			}
			if(last_step_len != 0)
			{
				for(j=0;j<fans;j++)
				{
					rect.x = i*step_len+j*fan_len;
					rect.y = 0;
					rect.w = last_step_len;
					rect.h = disp_info.screen_height;
					block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
				}
				ionHdle->flush_cache(disp_info.fb_vir, size);
				usleep(10000);
			}
			if(last_fan_len)
			{
				rect.x = disp_info.screen_width-last_fan_len;
				rect.y = 0;
				rect.w = last_fan_len;
				rect.h = disp_info.screen_height;
				block_copy(src->vir_addr,src->width,src->height,disp_info.fb_vir,&rect);
				ionHdle->flush_cache(disp_info.fb_vir, size);
			}
			break;
	}
	return 0;
}

static int image_show_mosaic_step(image_buffer_t *src,int mode,int step ,int loop)
{
	int ret = 0;
	int i, count = 0;
	int x, y;
	int rand_num;
	char set_flag[MOSAIC_NUM];
	image_disp_info_t disp_info;
	(void)mode;

	image.opr.display->disp_info_get(&disp_info);
	memset(set_flag, 0, sizeof(set_flag));
	if(loop)
	{
		while (count < MOSAIC_NUM) {
			rand_num = rand() % MOSAIC_NUM;
			if (set_flag[rand_num])
				continue;
			count++;
			set_flag[rand_num] = 1;
			x = rand_num / 10;
			y = rand_num % 10;
			for (i = 0; i < disp_info.screen_height / 10; i++) {
				memcpy(disp_info.fb_vir + \
					((disp_info.screen_width * (y * disp_info.screen_height / 10 + i) + (x * disp_info.screen_width / 10)) * 4), \
					src->vir_addr + ((src->width * (y * src->height / 10 + i) + (x * src->width / 10)) * 4), src->width / 10 * 4);
				ionHdle->flush_cache(disp_info.fb_vir + \
					((disp_info.screen_width * (y * disp_info.screen_height / 10 + i) + (x * disp_info.screen_width / 10)) * 4), \
					src->width / 10 * 4);
			}
			usleep(1000);
			if (count % 15 == 0)
				usleep(80000);
		}
	}
	else
	{
		while (count < (step*100/disp_info.screen_height)) {
			rand_num = rand() % MOSAIC_NUM;
			if (set_flag[rand_num])
				continue;
			count++;
			set_flag[rand_num] = 1;
			x = rand_num / 10;
			y = rand_num % 10;
			for (i = 0; i < disp_info.screen_height / 10; i++) {
				memcpy(disp_info.fb_vir + \
					((disp_info.screen_width * (y * disp_info.screen_height / 10 + i) + (x * disp_info.screen_width / 10)) * 4), \
					src->vir_addr + ((src->width * (y * src->height / 10 + i) + (x * src->width / 10)) * 4), src->width / 10 * 4);
				ionHdle->flush_cache(disp_info.fb_vir + \
					((disp_info.screen_width * (y * disp_info.screen_height / 10 + i) + (x * disp_info.screen_width / 10)) * 4), \
					src->width / 10 * 4);
			}
			usleep(1000);
			if (count % 15 == 0)
				usleep(80000);
		}
	}

	return ret;
}


static int image_show_mosaic(image_buffer_t *src,int mode)
{
	int ret = 0;
	int i, count = 0;
	int x, y;
	int rand_num;
	char set_flag[MOSAIC_NUM];
	image_disp_info_t disp_info;
	(void)mode;

	image.opr.display->disp_info_get(&disp_info);
	memset(set_flag, 0, sizeof(set_flag));
	while (count < MOSAIC_NUM) {
		rand_num = rand() % MOSAIC_NUM;
		if (set_flag[rand_num])
			continue;
		count++;
		set_flag[rand_num] = 1;
		x = rand_num / 10;
		y = rand_num % 10;
		for (i = 0; i < disp_info.screen_height / 10; i++) {
			memcpy(disp_info.fb_vir + \
				((disp_info.screen_width * (y * disp_info.screen_height / 10 + i) + (x * disp_info.screen_width / 10)) * 4), \
				src->vir_addr + ((src->width * (y * src->height / 10 + i) + (x * src->width / 10)) * 4), src->width / 10 * 4);
			ionHdle->flush_cache(disp_info.fb_vir + \
				((disp_info.screen_width * (y * disp_info.screen_height / 10 + i) + (x * disp_info.screen_width / 10)) * 4), \
				src->width / 10 * 4);
		}
		usleep(1000);
		if (count % 15 == 0)
			usleep(80000);
	}

	return ret;
}

static int image_show_fill(image_buffer_t *src,unsigned int color)
{
	image_enh_t src_enh[1],dst_enh;

	memset(src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh[0].buf = *src;
	src_enh[0].clip_rect.w = src_enh[0].buf.width;
	src_enh[0].clip_rect.h = src_enh[0].buf.height;
	src_enh[0].clip_rect.x = 0;
	src_enh[0].clip_rect.y = 0;
	src_enh[0].coor.x = 0;
	src_enh[0].coor.y = 0;
	src_enh[0].alpha_mode = IMAGE_ALPHA_GLOBAL;
	
	image.opr.process->fill(src_enh,color);
	/*
	image_disp_info_t disp_info;
	image.opr.display->disp_info_get(&disp_info);
	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	dst_enh.buf.width    = disp_info.disp_rect.w;
	dst_enh.buf.height  = disp_info.disp_rect.h;
	dst_enh.clip_rect.w = dst_enh.buf.width/20;
	dst_enh.clip_rect.h = dst_enh.buf.height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	dst_enh.alpha_mode = IMAGE_ALPHA_PIXEL;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	int w = 40;
	// int cnt=0;
	while(w<=800)
	{

		dst_enh.clip_rect.w = w;
		image.opr.process->fill(&dst_enh,0xffff0000);

		w++;
		usleep(1000);
	}*/
	return 0;
}

static int image_show_clip(image_buffer_t *src_base,image_buffer_t *src)
{
	image_enh_t src_enh[2], dst_enh;

	image_disp_info_t disp_info;

	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh[0].buf = *src_base;  //底图
	src_enh[0].clip_rect.w = src_enh[0].buf.width;
	src_enh[0].clip_rect.h = src_enh[0].buf.height;
	src_enh[0].clip_rect.x = 0;
	src_enh[0].clip_rect.y = 0;
	src_enh[0].coor.x = 0;
	src_enh[0].coor.y = 0;
	src_enh[0].alpha_value = 0xff;
	src_enh[0].alpha_mode = IMAGE_ALPHA_GLOBAL;

	src_enh[1].buf = *src;
	src_enh[1].clip_rect.w = src_enh[1].buf.width;//剪切图
	src_enh[1].clip_rect.h = src_enh[1].buf.height;
	src_enh[1].clip_rect.x = 0;
	src_enh[1].clip_rect.y = 0;
	src_enh[1].coor.x = (src_enh[0].buf.height - src_enh[1].buf.height)/2;
	src_enh[1].coor.y = (src_enh[0].buf.width - src_enh[1].buf.width)/2;
	src_enh[1].alpha_value = 0xff;
	src_enh[1].alpha_mode = IMAGE_ALPHA_GLOBAL;

	image.opr.display->disp_info_get(&disp_info);

	dst_enh.buf = image.dst_next;
	dst_enh.clip_rect.w = dst_enh.buf.width;
	dst_enh.clip_rect.h = dst_enh.buf.height;

	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	dst_enh.alpha_value = 0xff;
	dst_enh.alpha_mode = IMAGE_ALPHA_GLOBAL;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;

	int ret = image.opr.process->alpha_blend(src_enh, &dst_enh, 2);
	//printf("%s: image clip successful! ret = %d\n", __func__,ret);
	usleep(5000);

	return ret;
}

static int image_show_slide_step(image_buffer_t *src,int mode, int step ,int loop)
{
	image_enh_t src_enh[2], dst_enh;
	image_disp_info_t disp_info;

	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh[0].buf = image.dst_previous;
	src_enh[0].clip_rect.w = src_enh[0].buf.width;
	src_enh[0].clip_rect.h = src_enh[0].buf.height;
	src_enh[0].clip_rect.x = 0;
	src_enh[0].clip_rect.y = 0;
	src_enh[0].coor.x = 0;
	src_enh[0].coor.y = 0;
	src_enh[0].alpha_mode = IMAGE_ALPHA_PIXEL;

	src_enh[1].buf = *src;
	src_enh[1].coor.x = 0;
	src_enh[1].coor.y = 0;
	src_enh[1].alpha_mode = IMAGE_ALPHA_PIXEL;

	image.opr.display->disp_info_get(&disp_info);
	 //image.opr.display->dequeue(&phy_addr_temp,&vir_addr_temp);
	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	// dst_enh.buf.phy_addr = (void*)phy_addr_temp;
	// dst_enh.buf.vir_addr = (void*)vir_addr_temp;

	dst_enh.buf.width = disp_info.disp_rect.w;
	dst_enh.buf.height = disp_info.disp_rect.h;
	dst_enh.clip_rect.w = dst_enh.buf.width;
	dst_enh.clip_rect.h = dst_enh.buf.height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	dst_enh.alpha_mode = IMAGE_ALPHA_PIXEL;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;

	switch(mode)
	{
		case IMAGE_SHOW_SLIDE_UP:
			{
				if(loop)
				{
					while (step < src_enh[1].buf.height) {
						step += 3;
						if (step > src_enh[1].buf.height)
							step = src_enh[1].buf.height;

						src_enh[1].clip_rect.w = src_enh[1].buf.width;//新的
						src_enh[1].clip_rect.h = step;
						src_enh[1].clip_rect.x = 0;
						src_enh[1].clip_rect.y = 0;
						src_enh[1].coor.x = src_enh[0].buf.height-step;
						src_enh[1].coor.y = 0;

						// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
						// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
						src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
						src_enh[0].clip_rect.h = src_enh[0].buf.height-step;
						src_enh[0].clip_rect.x = 0;
						src_enh[0].clip_rect.y = step;
						src_enh[0].coor.x = 0;
						src_enh[0].coor.y = 0;
						// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
						// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

						if(step == src_enh[1].buf.height)
						{
							src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
							src_enh[0].clip_rect.h = src_enh[0].buf.height;
							src_enh[0].clip_rect.x = 0;
							src_enh[0].clip_rect.y = 0;
							src_enh[0].coor.x = 0;
							src_enh[0].coor.y = 0;
						}

						image.opr.process->clip(src_enh, &dst_enh, 2);
						usleep(500);
					}
				}
				else
				{
					if (step > src_enh[1].buf.height)
						step = src_enh[1].buf.height;

					src_enh[1].clip_rect.w = src_enh[1].buf.width;//新的
					src_enh[1].clip_rect.h = step;
					src_enh[1].clip_rect.x = 0;
					src_enh[1].clip_rect.y = 0;
					src_enh[1].coor.x = src_enh[0].buf.height-step;
					src_enh[1].coor.y = 0;

					// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
					// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
					src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height-step;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = step;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = 0;
					// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
					// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

					if(step == src_enh[1].buf.height)
					{
						src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
						src_enh[0].clip_rect.h = src_enh[0].buf.height;
						src_enh[0].clip_rect.x = 0;
						src_enh[0].clip_rect.y = 0;
						src_enh[0].coor.x = 0;
						src_enh[0].coor.y = 0;
					}
					image.opr.process->clip(src_enh, &dst_enh, 2);
					usleep(500);
				}
			}
			break;
		case IMAGE_SHOW_SLIDE_DOWN:
			{
				if(loop)
				{
					while (step < src_enh[1].buf.height) {
						step += 3;
						if (step > src_enh[1].buf.height)
							step = src_enh[1].buf.height;

						// src_enh[1].clip_rect.w = src_enh[1].buf.width;
						// src_enh[1].clip_rect.h = step;
						// src_enh[1].clip_rect.x = 0;
						// src_enh[1].clip_rect.y = src_enh[1].buf.height - step;

						src_enh[1].clip_rect.w = src_enh[1].buf.width;//新的
						src_enh[1].clip_rect.h = step;
						src_enh[1].clip_rect.x = 0;
						src_enh[1].clip_rect.y = src_enh[1].buf.height - step;
						src_enh[1].coor.x = 0;
						src_enh[1].coor.y = 0;

						// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
						// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
						src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
						src_enh[0].clip_rect.h = src_enh[0].buf.height-step;
						src_enh[0].clip_rect.x = 0;
						src_enh[0].clip_rect.y = step;
						src_enh[0].coor.x = step;
						src_enh[0].coor.y = 0;
						// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
						// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

						if(step == src_enh[1].buf.height)
						{
							src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
							src_enh[0].clip_rect.h = src_enh[0].buf.height;
							src_enh[0].clip_rect.x = 0;
							src_enh[0].clip_rect.y = 0;
							src_enh[0].coor.x = 0;
							src_enh[0].coor.y = 0;
						}

						image.opr.process->clip(src_enh, &dst_enh, 2);
						usleep(500);
					}
				}
				else
				{
					if (step > src_enh[1].buf.height)
						step = src_enh[1].buf.height;

					// src_enh[1].clip_rect.w = src_enh[1].buf.width;
					// src_enh[1].clip_rect.h = step;
					// src_enh[1].clip_rect.x = 0;
					// src_enh[1].clip_rect.y = src_enh[1].buf.height - step;

					src_enh[1].clip_rect.w = src_enh[1].buf.width;//新的
					src_enh[1].clip_rect.h = step;
					src_enh[1].clip_rect.x = 0;
					src_enh[1].clip_rect.y = src_enh[1].buf.height - step;
					src_enh[1].coor.x = 0;
					src_enh[1].coor.y = 0;

					// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
					// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
					src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height-step;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = step;
					src_enh[0].coor.x = step;
					src_enh[0].coor.y = 0;
					// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
					// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

					if(step == src_enh[1].buf.height)
					{
						src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
						src_enh[0].clip_rect.h = src_enh[0].buf.height;
						src_enh[0].clip_rect.x = 0;
						src_enh[0].clip_rect.y = 0;
						src_enh[0].coor.x = 0;
						src_enh[0].coor.y = 0;
					}

					image.opr.process->clip(src_enh, &dst_enh, 2);
					usleep(500);
				}
			}
			break;
		case IMAGE_SHOW_SLIDE_LEFT:
			if(loop)
			{
				while (step < src_enh[1].buf.width) {
					step += 1;
					if (step > src_enh[1].buf.width)
						step = src_enh[1].buf.width;
	
					// src_enh[1].clip_rect.w = step;
					// src_enh[1].clip_rect.h = src_enh[1].buf.height;
					// src_enh[1].clip_rect.x = 0;
					// src_enh[1].clip_rect.y = 0;
	
					// src_enh[1].coor.x = step;
					// src_enh[1].coor.y = 0;
	
					src_enh[1].clip_rect.w = step;//新的
					src_enh[1].clip_rect.h = src_enh[1].buf.height;
					src_enh[1].clip_rect.x = 0;
					src_enh[1].clip_rect.y = 0;
					src_enh[1].coor.x = 0;
					src_enh[1].coor.y = src_enh[1].buf.width - step;
	
					// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
					// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
					src_enh[0].clip_rect.w = src_enh[0].buf.width-step;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = 0;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = 0;
					// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
					// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);
	
					if(step == src_enh[1].buf.width)
					{
						src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
						src_enh[0].clip_rect.h = src_enh[0].buf.height;
						src_enh[0].clip_rect.x = 0;
						src_enh[0].clip_rect.y = 0;
						src_enh[0].coor.x = 0;
						src_enh[0].coor.y = 0;
					}
					image.opr.process->clip(src_enh, &dst_enh, 2);
					usleep(200);
				}
			}
			else
			{
				if (step > src_enh[1].buf.width)
					step = src_enh[1].buf.width;

				// src_enh[1].clip_rect.w = step;
				// src_enh[1].clip_rect.h = src_enh[1].buf.height;
				// src_enh[1].clip_rect.x = 0;
				// src_enh[1].clip_rect.y = 0;

				// src_enh[1].coor.x = step;
				// src_enh[1].coor.y = 0;

				src_enh[1].clip_rect.w = step;//新的
				src_enh[1].clip_rect.h = src_enh[1].buf.height;
				src_enh[1].clip_rect.x = 0;
				src_enh[1].clip_rect.y = 0;
				src_enh[1].coor.x = 0;
				src_enh[1].coor.y = src_enh[1].buf.width - step;

				// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
				// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
				src_enh[0].clip_rect.w = src_enh[0].buf.width-step;//上一张
				src_enh[0].clip_rect.h = src_enh[0].buf.height;
				src_enh[0].clip_rect.x = 0;
				src_enh[0].clip_rect.y = 0;
				src_enh[0].coor.x = 0;
				src_enh[0].coor.y = 0;
				// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
				// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

				if(step == src_enh[1].buf.width)
				{
					src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = 0;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = 0;
				}
				image.opr.process->clip(src_enh, &dst_enh, 2);
				usleep(200);
			}
			break;
		case IMAGE_SHOW_SLIDE_RIGHT:
			if(loop)
			{
				while (step < src_enh[1].buf.width) {
					step += 1;
					if (step > src_enh[1].buf.width)
						step = src_enh[1].buf.width;
					// src_enh[1].clip_rect.w = step;
					// src_enh[1].clip_rect.h = src_enh[1].buf.height;
					// src_enh[1].clip_rect.x = src_enh[1].buf.width - step;
					// src_enh[1].clip_rect.y = 0;

					src_enh[1].clip_rect.w = step;//新的
					src_enh[1].clip_rect.h = src_enh[1].buf.height;
					src_enh[1].clip_rect.x = src_enh[1].buf.width - step;
					src_enh[1].clip_rect.y = 0;
					src_enh[1].coor.x = 0;
					src_enh[1].coor.y = 0;

					// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
					// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
					src_enh[0].clip_rect.w = src_enh[0].buf.width-step;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height;
					src_enh[0].clip_rect.x = step;
					src_enh[0].clip_rect.y = 0;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = step;
					// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
					// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

					if(step == src_enh[1].buf.width)
					{
						src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
						src_enh[0].clip_rect.h = src_enh[0].buf.height;
						src_enh[0].clip_rect.x = 0;
						src_enh[0].clip_rect.y = 0;
						src_enh[0].coor.x = 0;
						src_enh[0].coor.y = 0;
					}
					image.opr.process->clip(src_enh, &dst_enh, 2);
					usleep(200);
				}
			}
			else
			{
				if (step > src_enh[1].buf.width)
					step = src_enh[1].buf.width;
				// src_enh[1].clip_rect.w = step;
				// src_enh[1].clip_rect.h = src_enh[1].buf.height;
				// src_enh[1].clip_rect.x = src_enh[1].buf.width - step;
				// src_enh[1].clip_rect.y = 0;


				src_enh[1].clip_rect.w = step;//新的
				src_enh[1].clip_rect.h = src_enh[1].buf.height;
				src_enh[1].clip_rect.x = src_enh[1].buf.width - step;
				src_enh[1].clip_rect.y = 0;
				src_enh[1].coor.x = 0;
				src_enh[1].coor.y = 0;

				// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
				// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
				src_enh[0].clip_rect.w = src_enh[0].buf.width-step;//上一张
				src_enh[0].clip_rect.h = src_enh[0].buf.height;
				src_enh[0].clip_rect.x = step;
				src_enh[0].clip_rect.y = 0;
				src_enh[0].coor.x = 0;
				src_enh[0].coor.y = step;
				// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
				// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

				if(step == src_enh[1].buf.width)
				{
					src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = 0;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = 0;
				}

				image.opr.process->clip(src_enh, &dst_enh, 2);

				usleep(200);
			}
			break;
		default:
			return -1;
		break;
	}


	return 0;
}


static int image_show_slide(image_buffer_t *src,int mode)
{
	image_enh_t src_enh[2], dst_enh;
	image_disp_info_t disp_info;
	int step = 0;


	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh[0].buf = image.dst_previous;
	src_enh[0].clip_rect.w = src_enh[0].buf.width;
	src_enh[0].clip_rect.h = src_enh[0].buf.height;
	src_enh[0].clip_rect.x = 0;
	src_enh[0].clip_rect.y = 0;
	src_enh[0].coor.x = 0;
	src_enh[0].coor.y = 0;
	src_enh[0].alpha_mode = IMAGE_ALPHA_PIXEL;

	src_enh[1].buf = *src;
	src_enh[1].coor.x = 0;
	src_enh[1].coor.y = 0;
	src_enh[1].alpha_mode = IMAGE_ALPHA_PIXEL;

	image.opr.display->disp_info_get(&disp_info);
	 //image.opr.display->dequeue(&phy_addr_temp,&vir_addr_temp);
	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	// dst_enh.buf.phy_addr = (void*)phy_addr_temp;
	// dst_enh.buf.vir_addr = (void*)vir_addr_temp;

	dst_enh.buf.width = disp_info.disp_rect.w;
	dst_enh.buf.height = disp_info.disp_rect.h;
	dst_enh.clip_rect.w = dst_enh.buf.width;
	dst_enh.clip_rect.h = dst_enh.buf.height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	dst_enh.alpha_mode = IMAGE_ALPHA_PIXEL;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;

	switch(mode)
	{
		case IMAGE_SHOW_SLIDE_UP:
			while (step < src_enh[1].buf.height) {
				step += 3;
				if (step > src_enh[1].buf.height)
					step = src_enh[1].buf.height;

				src_enh[1].clip_rect.w = src_enh[1].buf.width;//新的
				src_enh[1].clip_rect.h = step;
				src_enh[1].clip_rect.x = 0;
				src_enh[1].clip_rect.y = 0;
				src_enh[1].coor.x = src_enh[0].buf.height-step;
				src_enh[1].coor.y = 0;

				// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
				// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
				src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
				src_enh[0].clip_rect.h = src_enh[0].buf.height-step;
				src_enh[0].clip_rect.x = 0;
				src_enh[0].clip_rect.y = step;
				src_enh[0].coor.x = 0;
				src_enh[0].coor.y = 0;
				// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
				// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

				if(step == src_enh[1].buf.height)
				{
					src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = 0;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = 0;
				}

				image.opr.process->clip(src_enh, &dst_enh, 2);
				usleep(500);
			}
			break;
		case IMAGE_SHOW_SLIDE_DOWN:
			while (step < src_enh[1].buf.height) {
				step += 3;
				if (step > src_enh[1].buf.height)
					step = src_enh[1].buf.height;

				// src_enh[1].clip_rect.w = src_enh[1].buf.width;
				// src_enh[1].clip_rect.h = step;
				// src_enh[1].clip_rect.x = 0;
				// src_enh[1].clip_rect.y = src_enh[1].buf.height - step;

				src_enh[1].clip_rect.w = src_enh[1].buf.width;//新的
				src_enh[1].clip_rect.h = step;
				src_enh[1].clip_rect.x = 0;
				src_enh[1].clip_rect.y = src_enh[1].buf.height - step;
				src_enh[1].coor.x = 0;
				src_enh[1].coor.y = 0;

				// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
				// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
				src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
				src_enh[0].clip_rect.h = src_enh[0].buf.height-step;
				src_enh[0].clip_rect.x = 0;
				src_enh[0].clip_rect.y = step;
				src_enh[0].coor.x = step;
				src_enh[0].coor.y = 0;
				// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
				// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

				if(step == src_enh[1].buf.height)
				{
					src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = 0;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = 0;
				}

				image.opr.process->clip(src_enh, &dst_enh, 2);
				usleep(500);
			}
			break;
		case IMAGE_SHOW_SLIDE_LEFT:
			while (step < src_enh[1].buf.width) {
				step += 1;
				if (step > src_enh[1].buf.width)
					step = src_enh[1].buf.width;

				// src_enh[1].clip_rect.w = step;
				// src_enh[1].clip_rect.h = src_enh[1].buf.height;
				// src_enh[1].clip_rect.x = 0;
				// src_enh[1].clip_rect.y = 0;

				// src_enh[1].coor.x = step;
				// src_enh[1].coor.y = 0;

				src_enh[1].clip_rect.w = step;//新的
				src_enh[1].clip_rect.h = src_enh[1].buf.height;
				src_enh[1].clip_rect.x = 0;
				src_enh[1].clip_rect.y = 0;
				src_enh[1].coor.x = 0;
				src_enh[1].coor.y = src_enh[1].buf.width - step;

				// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
				// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
				src_enh[0].clip_rect.w = src_enh[0].buf.width-step;//上一张
				src_enh[0].clip_rect.h = src_enh[0].buf.height;
				src_enh[0].clip_rect.x = 0;
				src_enh[0].clip_rect.y = 0;
				src_enh[0].coor.x = 0;
				src_enh[0].coor.y = 0;
				// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
				// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

				if(step == src_enh[1].buf.width)
				{
					src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = 0;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = 0;
				}
				image.opr.process->clip(src_enh, &dst_enh, 2);
				usleep(200);
			}
			break;
		case IMAGE_SHOW_SLIDE_RIGHT:
			while (step < src_enh[1].buf.width) {
				step += 1;
				if (step > src_enh[1].buf.width)
					step = src_enh[1].buf.width;
				// src_enh[1].clip_rect.w = step;
				// src_enh[1].clip_rect.h = src_enh[1].buf.height;
				// src_enh[1].clip_rect.x = src_enh[1].buf.width - step;
				// src_enh[1].clip_rect.y = 0;


				src_enh[1].clip_rect.w = step;//新的
				src_enh[1].clip_rect.h = src_enh[1].buf.height;
				src_enh[1].clip_rect.x = src_enh[1].buf.width - step;
				src_enh[1].clip_rect.y = 0;
				src_enh[1].coor.x = 0;
				src_enh[1].coor.y = 0;

				// printf("clip %d %d %d %d \n",src_enh[1].clip_rect.x,src_enh[1].clip_rect.y,src_enh[1].clip_rect.w,src_enh[1].clip_rect.h);
				// printf("coor %d %d \n",src_enh[1].coor.x,src_enh[1].coor.y);
				src_enh[0].clip_rect.w = src_enh[0].buf.width-step;//上一张
				src_enh[0].clip_rect.h = src_enh[0].buf.height;
				src_enh[0].clip_rect.x = step;
				src_enh[0].clip_rect.y = 0;
				src_enh[0].coor.x = 0;
				src_enh[0].coor.y = step;
				// printf("clip1 %d %d %d %d \n",src_enh[0].clip_rect.x,src_enh[0].clip_rect.y,src_enh[0].clip_rect.w,src_enh[0].clip_rect.h);
				// printf("coor2 %d %d \n",src_enh[0].coor.x,src_enh[0].coor.y);

				if(step == src_enh[1].buf.width)
				{
					src_enh[0].clip_rect.w = src_enh[0].buf.width;//上一张
					src_enh[0].clip_rect.h = src_enh[0].buf.height;
					src_enh[0].clip_rect.x = 0;
					src_enh[0].clip_rect.y = 0;
					src_enh[0].coor.x = 0;
					src_enh[0].coor.y = 0;
				}

				image.opr.process->clip(src_enh, &dst_enh, 2);

				usleep(200);
			}
			break;
		default:
			return -1;
		break;
	}


	return 0;
}

static int image_show_fade_step(image_buffer_t *src,int mode,int step ,int loop)
{
	image_enh_t src_enh[2], dst_enh;
	image_disp_info_t disp_info;
	int alpha = 0;
	(void)mode;
	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh[0].buf = image.dst_previous;
	src_enh[0].clip_rect.w = src_enh[0].buf.width;
	src_enh[0].clip_rect.h = src_enh[0].buf.height;
	src_enh[0].clip_rect.x = 0;
	src_enh[0].clip_rect.y = 0;
	src_enh[0].coor.x = 0;
	src_enh[0].coor.y = 0;
	src_enh[0].alpha_mode = IMAGE_ALPHA_GLOBAL;

	src_enh[1].buf = *src;
	src_enh[1].clip_rect.w = src_enh[1].buf.width;
	src_enh[1].clip_rect.h = src_enh[1].buf.height;
	src_enh[1].clip_rect.x = 0;
	src_enh[1].clip_rect.y = 0;
	src_enh[1].coor.x = 0;
	src_enh[1].coor.y = 0;
	src_enh[1].alpha_mode = IMAGE_ALPHA_GLOBAL;

	image.opr.display->disp_info_get(&disp_info);
	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	dst_enh.buf.width = disp_info.disp_rect.w;
	dst_enh.buf.height = disp_info.disp_rect.h;
	dst_enh.clip_rect.w = dst_enh.buf.width;
	dst_enh.clip_rect.h = dst_enh.buf.height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	dst_enh.alpha_mode = IMAGE_ALPHA_GLOBAL;
	dst_enh.alpha_value = 0xff;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	if(loop)
	{
		while (alpha < 250) {
			alpha += 10;
			src_enh[1].alpha_value = alpha;
			src_enh[0].alpha_value = 0xff - alpha;
			image.opr.process->alpha_blend(src_enh, &dst_enh, 2);
			usleep(40000);
		}
		src_enh[1].alpha_value = 0xff;
		src_enh[0].alpha_value = 0;
		image.opr.process->alpha_blend(src_enh, &dst_enh, 2);
	}
	else
	{
		alpha = step*250/disp_info.screen_height;
		if(alpha < 250)
		{
			src_enh[1].alpha_value = alpha;
			src_enh[0].alpha_value = 0xff - alpha;
			image.opr.process->alpha_blend(src_enh, &dst_enh, 2);
			usleep(40000);
		}
	}
	return 0;
}


static int image_show_fade(image_buffer_t *src,int mode)
{
	image_enh_t src_enh[2], dst_enh;
	image_disp_info_t disp_info;
	int alpha = 0;
	(void)mode;
	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh[0].buf = image.dst_previous;
	src_enh[0].clip_rect.w = src_enh[0].buf.width;
	src_enh[0].clip_rect.h = src_enh[0].buf.height;
	src_enh[0].clip_rect.x = 0;
	src_enh[0].clip_rect.y = 0;
	src_enh[0].coor.x = 0;
	src_enh[0].coor.y = 0;
	src_enh[0].alpha_mode = IMAGE_ALPHA_GLOBAL;

	src_enh[1].buf = *src;
	src_enh[1].clip_rect.w = src_enh[1].buf.width;
	src_enh[1].clip_rect.h = src_enh[1].buf.height;
	src_enh[1].clip_rect.x = 0;
	src_enh[1].clip_rect.y = 0;
	src_enh[1].coor.x = 0;
	src_enh[1].coor.y = 0;
	src_enh[1].alpha_mode = IMAGE_ALPHA_GLOBAL;

	image.opr.display->disp_info_get(&disp_info);
	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	dst_enh.buf.width = disp_info.disp_rect.w;
	dst_enh.buf.height = disp_info.disp_rect.h;
	dst_enh.clip_rect.w = dst_enh.buf.width;
	dst_enh.clip_rect.h = dst_enh.buf.height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.coor.x = 0;
	dst_enh.coor.y = 0;
	dst_enh.alpha_mode = IMAGE_ALPHA_GLOBAL;
	dst_enh.alpha_value = 0xff;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;

	while (alpha < 250) {
		alpha += 10;
		src_enh[1].alpha_value = alpha;
		src_enh[0].alpha_value = 0xff - alpha;
		image.opr.process->alpha_blend(src_enh, &dst_enh, 2);
		usleep(40000);
	}
	src_enh[1].alpha_value = 0xff;
	src_enh[0].alpha_value = 0;
	image.opr.process->alpha_blend(src_enh, &dst_enh, 2);

	return 0;
}

static int image_show_stretch_step(image_buffer_t *src,int mode,int step ,int loop)
{
	image_disp_info_t disp_info;
	image_enh_t src_enh, dst_enh;
	
	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	image.opr.display->disp_info_get(&disp_info);

	src_enh.buf = *src;
	src_enh.clip_rect.w = src_enh.buf.width;
	src_enh.clip_rect.h = src_enh.buf.height;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;
	src_enh.alpha_mode = 0;

	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	dst_enh.buf.comp = src->comp;
	dst_enh.buf.width = disp_info.screen_width;
	dst_enh.buf.height = disp_info.screen_height;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.alpha_mode = 0;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;

	switch(mode)
	{
		case IMAGE_SHOW_STRETCH_UP:
			if(loop)
			{
				while (step < dst_enh.buf.height) {
					step += 10;
					if (step > dst_enh.buf.height) {
						step = dst_enh.buf.height;
					}
					dst_enh.clip_rect.x = 0;
					dst_enh.clip_rect.y = dst_enh.buf.height-step;
					dst_enh.clip_rect.w = dst_enh.buf.width;
					dst_enh.clip_rect.h = step;
					image.opr.process->scaler(&src_enh, &dst_enh);
					usleep(5000);
				}
			}
			else
			{
				if (step > dst_enh.buf.height) {
					step = dst_enh.buf.height;
				}
				dst_enh.clip_rect.x = 0;
				dst_enh.clip_rect.y = dst_enh.buf.height-step;
				dst_enh.clip_rect.w = dst_enh.buf.width;
				dst_enh.clip_rect.h = step;
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		case IMAGE_SHOW_STRETCH_DOWN:
			if(loop)
			{
				while (step < dst_enh.buf.height) {
					step += 10;
					if (step > dst_enh.buf.height) {
						step = dst_enh.buf.height;
					}
					dst_enh.clip_rect.x = 0;
					dst_enh.clip_rect.y = 0;
					dst_enh.clip_rect.w = dst_enh.buf.width;
					dst_enh.clip_rect.h = step;
					image.opr.process->scaler(&src_enh, &dst_enh);
					usleep(5000);
				}
			}
			else
			{
				if (step > dst_enh.buf.height) {
					step = dst_enh.buf.height;
				}
				dst_enh.clip_rect.x = 0;
				dst_enh.clip_rect.y = 0;
				dst_enh.clip_rect.w = dst_enh.buf.width;
				dst_enh.clip_rect.h = step;
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		case IMAGE_SHOW_STRETCH_LEFT:
			if(loop)
			{
				while (step < dst_enh.buf.width) {
					step += 10;
					if (step > dst_enh.buf.width) {
						step = dst_enh.buf.width;
					}
					dst_enh.clip_rect.x = dst_enh.buf.width-step;
					dst_enh.clip_rect.y = 0;
					dst_enh.clip_rect.w = step;
					dst_enh.clip_rect.h = dst_enh.buf.height;
					image.opr.process->scaler(&src_enh, &dst_enh);
					usleep(5000);
				}
			}
			else
			{
				if (step > dst_enh.buf.width) {
					step = dst_enh.buf.width;
				}
				dst_enh.clip_rect.x = dst_enh.buf.width-step;
				dst_enh.clip_rect.y = 0;
				dst_enh.clip_rect.w = step;
				dst_enh.clip_rect.h = dst_enh.buf.height;
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		case IMAGE_SHOW_STRETCH_RIGHT:
			if(loop)
			{
				while (step < dst_enh.buf.width) {
					step += 10;
					if (step > dst_enh.buf.width) {
						step = dst_enh.buf.width;
					}
					dst_enh.clip_rect.w = step;
					dst_enh.clip_rect.h = dst_enh.buf.height;
					image.opr.process->scaler(&src_enh, &dst_enh);
					usleep(5000);
				}
			}
			else
			{
				if (step > dst_enh.buf.width) {
					step = dst_enh.buf.width;
				}
				dst_enh.clip_rect.w = step;
				dst_enh.clip_rect.h = dst_enh.buf.height;
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		default:
			break;

	}
	return 0;
}


static int image_show_stretch(image_buffer_t *src,int mode)
{
	image_disp_info_t disp_info;
	image_enh_t src_enh, dst_enh;
	int step = 0;

	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	image.opr.display->disp_info_get(&disp_info);

	src_enh.buf = *src;
	src_enh.clip_rect.w = src_enh.buf.width;
	src_enh.clip_rect.h = src_enh.buf.height;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;
	src_enh.alpha_mode = 0;

	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	dst_enh.buf.comp = src->comp;
	dst_enh.buf.width = disp_info.screen_width;
	dst_enh.buf.height = disp_info.screen_height;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.alpha_mode = 0;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;

	switch(mode)
	{
		case IMAGE_SHOW_STRETCH_UP:
			while (step < dst_enh.buf.height) {
				step += 10;
				if (step > dst_enh.buf.height) {
					step = dst_enh.buf.height;
				}
				dst_enh.clip_rect.x = 0;
				dst_enh.clip_rect.y = dst_enh.buf.height-step;
				dst_enh.clip_rect.w = dst_enh.buf.width;
				dst_enh.clip_rect.h = step;
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		case IMAGE_SHOW_STRETCH_DOWN:
			while (step < dst_enh.buf.height) {
				step += 10;
				if (step > dst_enh.buf.height) {
					step = dst_enh.buf.height;
				}
				dst_enh.clip_rect.x = 0;
				dst_enh.clip_rect.y = 0;
				dst_enh.clip_rect.w = dst_enh.buf.width;
				dst_enh.clip_rect.h = step;
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		case IMAGE_SHOW_STRETCH_LEFT:
			while (step < dst_enh.buf.width) {
				step += 10;
				if (step > dst_enh.buf.width) {
					step = dst_enh.buf.width;
				}
				dst_enh.clip_rect.x = dst_enh.buf.width-step;
				dst_enh.clip_rect.y = 0;
				dst_enh.clip_rect.w = step;
				dst_enh.clip_rect.h = dst_enh.buf.height;
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		case IMAGE_SHOW_STRETCH_RIGHT:
			while (step < dst_enh.buf.width) {
				step += 10;
				if (step > dst_enh.buf.width) {
					step = dst_enh.buf.width;
				}
				dst_enh.clip_rect.w = step;
				dst_enh.clip_rect.h = dst_enh.buf.height;
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		default:
			break;

	}
	return 0;
}

static int image_show_zoom_step(image_buffer_t *src,int mode,int step ,int loop)
{
	image_disp_info_t disp_info;
	image_enh_t src_enh, dst_enh;
	
	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	image.opr.display->disp_info_get(&disp_info);

	src_enh.buf = *src;
	src_enh.clip_rect.w = src_enh.buf.width;
	src_enh.clip_rect.h = src_enh.buf.height;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;
	src_enh.alpha_mode = 0;

	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	dst_enh.buf.comp = src->comp;
	dst_enh.buf.width = disp_info.screen_width;
	dst_enh.buf.height = disp_info.screen_height;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.alpha_mode = 0;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;

	switch(mode)
	{
		case IMAGE_SHOW_ZOOM_IN:
			if(loop)
			{
				while (step < src_enh.buf.width) {
					step += 10;
					if (step > src_enh.buf.width) {
						step = src_enh.buf.width;
					}
					dst_enh.clip_rect.w = dst_enh.buf.width;
					dst_enh.clip_rect.h = dst_enh.buf.height;
					dst_enh.clip_rect.x = 0;
					dst_enh.clip_rect.y = 0;

					src_enh.clip_rect.w = step;
					src_enh.clip_rect.h = src_enh.buf.height * src_enh.clip_rect.w / src_enh.buf.width;
					src_enh.clip_rect.x = (src_enh.buf.width - src_enh.clip_rect.w) / 2;
					src_enh.clip_rect.y = (src_enh.buf.height - src_enh.clip_rect.h) / 2;
					//printf("step = %d\n",step);
					image.opr.process->scaler(&src_enh, &dst_enh);
					//printf("%d %d %d %d\n",src_enh.clip_rect.x,src_enh.clip_rect.y,src_enh.clip_rect.w,src_enh.clip_rect.h);
					usleep(5000);

				}
			}
			else
			{
				if (step > src_enh.buf.width) {
					step = src_enh.buf.width;
				}
				dst_enh.clip_rect.w = dst_enh.buf.width;
				dst_enh.clip_rect.h = dst_enh.buf.height;
				dst_enh.clip_rect.x = 0;
				dst_enh.clip_rect.y = 0;

				src_enh.clip_rect.w = step;
				src_enh.clip_rect.h = src_enh.buf.height * src_enh.clip_rect.w / src_enh.buf.width;
				src_enh.clip_rect.x = (src_enh.buf.width - src_enh.clip_rect.w) / 2;
				src_enh.clip_rect.y = (src_enh.buf.height - src_enh.clip_rect.h) / 2;
				//printf("step = %d\n",step);
				image.opr.process->scaler(&src_enh, &dst_enh);
				//printf("%d %d %d %d\n",src_enh.clip_rect.x,src_enh.clip_rect.y,src_enh.clip_rect.w,src_enh.clip_rect.h);
				usleep(5000);
			}
			break;
		case IMAGE_SHOW_ZOOM_OUT:
			if(loop)
			{
				while (step < dst_enh.buf.width) {
					step += 10;
					if (step > dst_enh.buf.width) {
						step = dst_enh.buf.width;
					}
					dst_enh.clip_rect.w = step;
					dst_enh.clip_rect.h = src_enh.clip_rect.h * dst_enh.clip_rect.w / src_enh.clip_rect.w;
					dst_enh.clip_rect.x = (dst_enh.buf.width - dst_enh.clip_rect.w) / 2;
					dst_enh.clip_rect.y = (dst_enh.buf.height - dst_enh.clip_rect.h) / 2;
					//printf("%d %d %d %d\n",dst_enh.clip_rect.x,dst_enh.clip_rect.y,dst_enh.clip_rect.w,dst_enh.clip_rect.h);
					image.opr.process->scaler(&src_enh, &dst_enh);
					usleep(5000);
				}
			}
			else
			{
				if (step > dst_enh.buf.width) {
					step = dst_enh.buf.width;
				}
				dst_enh.clip_rect.w = step;
				dst_enh.clip_rect.h = src_enh.clip_rect.h * dst_enh.clip_rect.w / src_enh.clip_rect.w;
				dst_enh.clip_rect.x = (dst_enh.buf.width - dst_enh.clip_rect.w) / 2;
				dst_enh.clip_rect.y = (dst_enh.buf.height - dst_enh.clip_rect.h) / 2;
				//printf("%d %d %d %d\n",dst_enh.clip_rect.x,dst_enh.clip_rect.y,dst_enh.clip_rect.w,dst_enh.clip_rect.h);
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		default:
		break;
	}

	return 0;
}


static int image_show_zoom(image_buffer_t *src,int mode)
{
	image_disp_info_t disp_info;
	image_enh_t src_enh, dst_enh;
	int step = 40;

	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	image.opr.display->disp_info_get(&disp_info);

	src_enh.buf = *src;
	src_enh.clip_rect.w = src_enh.buf.width;
	src_enh.clip_rect.h = src_enh.buf.height;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;
	src_enh.alpha_mode = 0;

	dst_enh.buf.phy_addr = disp_info.fb_phy;
	dst_enh.buf.vir_addr = disp_info.fb_vir;
	dst_enh.buf.comp = src->comp;
	dst_enh.buf.width = disp_info.screen_width;
	dst_enh.buf.height = disp_info.screen_height;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.alpha_mode = 0;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;

	switch(mode)
	{
		case IMAGE_SHOW_ZOOM_IN:
			while (step < src_enh.buf.width) {
				step += 10;
				if (step > src_enh.buf.width) {
					step = src_enh.buf.width;
				}
				dst_enh.clip_rect.w = dst_enh.buf.width;
				dst_enh.clip_rect.h = dst_enh.buf.height;
				dst_enh.clip_rect.x = 0;
				dst_enh.clip_rect.y = 0;

				src_enh.clip_rect.w = step;
				src_enh.clip_rect.h = src_enh.buf.height * src_enh.clip_rect.w / src_enh.buf.width;
				src_enh.clip_rect.x = (src_enh.buf.width - src_enh.clip_rect.w) / 2;
				src_enh.clip_rect.y = (src_enh.buf.height - src_enh.clip_rect.h) / 2;
				//printf("step = %d\n",step);
				image.opr.process->scaler(&src_enh, &dst_enh);
				//printf("%d %d %d %d\n",src_enh.clip_rect.x,src_enh.clip_rect.y,src_enh.clip_rect.w,src_enh.clip_rect.h);
				usleep(5000);

			}
			break;
		case IMAGE_SHOW_ZOOM_OUT:
			while (step < dst_enh.buf.width) {
				step += 10;
				if (step > dst_enh.buf.width) {
					step = dst_enh.buf.width;
				}
				dst_enh.clip_rect.w = step;
				dst_enh.clip_rect.h = src_enh.clip_rect.h * dst_enh.clip_rect.w / src_enh.clip_rect.w;
				dst_enh.clip_rect.x = (dst_enh.buf.width - dst_enh.clip_rect.w) / 2;
				dst_enh.clip_rect.y = (dst_enh.buf.height - dst_enh.clip_rect.h) / 2;
				//printf("%d %d %d %d\n",dst_enh.clip_rect.x,dst_enh.clip_rect.y,dst_enh.clip_rect.w,dst_enh.clip_rect.h);
				image.opr.process->scaler(&src_enh, &dst_enh);
				usleep(5000);
			}
			break;
		default:
		break;
	}

	return 0;
}

static int image_scaler_to_disp_rect(image_buffer_t *src, image_buffer_t *dst)
{
	image_disp_info_t disp_info;
	image_enh_t src_enh, dst_enh;

	image.opr.display->disp_info_get(&disp_info);
	dst->comp = src->comp;
	dst->width = disp_info.disp_rect.w;
	dst->height = disp_info.disp_rect.h;
	dst->length = dst->width * dst->height * dst->comp;
	dst->fmt = IMAGE_FORMAT_ARGB8888;
	dst->rotate_angle  = 0;
    dst->scaler_ratito = 100;/*NOTE:reset all para*/
	memset(&src_enh, 0, sizeof(src_enh));
	memset(&dst_enh, 0, sizeof(dst_enh));

	src_enh.buf = *src;
	src_enh.clip_rect.w = src->width;
    src_enh.clip_rect.h = src->height;

	dst_enh.buf = *dst;
    dst_enh.clip_rect.w = dst->width;
    dst_enh.clip_rect.h = dst->height;

	return image.opr.process->scaler(&src_enh, &dst_enh);
}

int image_disp_rect_set(image_rect_t *rect)
{
	image_rect_t full_screen_rect;
	image_disp_info_t disp_info;

	if (rect == IMAGE_FULL_SCREEN) {
		image.opr.display->disp_info_get(&disp_info);
		full_screen_rect.x = 0;
		full_screen_rect.y = 0;
		full_screen_rect.w = disp_info.screen_width;
		full_screen_rect.h = disp_info.screen_height;
		//print_zxf("x:%d  y:%d  w:%d  h:%d",full_screen_rect.x,full_screen_rect.y,full_screen_rect.w,full_screen_rect.h);
		return image.opr.display->rect_set(&full_screen_rect);
	} else {
		return image.opr.display->rect_set(rect);
	}
}

int image_disp_cache_enable(int enable)
{
	return image.opr.display->disp_cache_enable(enable);
}

int image_disp_info_get(image_disp_info_t *disp_info)
{
	return image.opr.display->disp_info_get(disp_info);
}

int image_rotate(image_rotate_angle_t rotate_angle)
{
	int ret;
	image_disp_info_t disp_info;
	image_rect_t disp_rect, src_crop_rect;
	image_rotate_angle_t rotate_angle_relative;	/* rotate relative to last one */

	image_dst_buffer_switch();
	
	rotate_angle_relative = (int)(rotate_angle - image.dst_previous.rotate_angle) < 0 ? \
		(rotate_angle - image.dst_previous.rotate_angle + 4) : (rotate_angle - image.dst_previous.rotate_angle);

	rotate_angle_relative = (int)(rotate_angle + IMAGE_DEF_ROTATE) > 3 ? \
		(IMAGE_ROTATE_0) : (image_rotate_angle_t)(rotate_angle + IMAGE_DEF_ROTATE);

	ret = image.opr.process->rotate(&image.src,&image.full_buf, rotate_angle_relative);
	if (ret	!= 0) {
		printf("%s: image rotate failed!\n", __func__);
		return ret;
	}
	
	sunxi_image_rotate_scaler_standardized(&image.full_buf,rotate_angle_relative);

	ret = image.opr.process->rotate(&image.src,&image.dst_next, rotate_angle_relative);

	if (ret	!= 0) {
		printf("%s: image rotate failed!\n", __func__);
		return ret;
	}
	sunxi_image_rotate_fullsrceen_standardized(&image.dst_next,rotate_angle_relative);

	image_show_fill(&image.dst_next,0xcc000000);
	
	ret = image_show_clip(&image.dst_next,&image.full_buf);
	if(ret<0)
	{
		printf("%s: image_show_clip failed!\n", __func__);
		goto err;
	}

	image.opr.display->disp_info_get(&disp_info);
	disp_rect.w = (image.dst_next.width > disp_info.screen_width) ? disp_info.screen_width : image.dst_next.width;
	disp_rect.h = (image.dst_next.height > disp_info.screen_height) ? disp_info.screen_height : image.dst_next.height;
	disp_rect.x = (disp_info.screen_width - disp_rect.w) / 2;
	disp_rect.y = (disp_info.screen_height - disp_rect.h) / 2;
	image_disp_rect_set(&disp_rect);

	src_crop_rect.x = (image.dst_next.width - disp_rect.w) / 2;
	src_crop_rect.y = (image.dst_next.height - disp_rect.h) / 2;
	src_crop_rect.w = disp_rect.w;
	src_crop_rect.h = disp_rect.h;
	image.opr.display->display(&image.dst_next, &src_crop_rect);

	image.dst_next.rotate_angle = rotate_angle;
	//printf("image change rotate =%d\n",image.dst_next.rotate_angle);
err:
	return ret;
}

int image_fill(void)
{
	return 0;
}

int image_move(int x, int y)
{
	int ret;
	image_disp_info_t disp_info;
	image_rect_t disp_rect;
	int src_x, src_y;

	if ((x == 0) && (y == 0))
		return 0;

	ret = image.opr.display->disp_info_get(&disp_info);
	disp_rect = disp_info.src_crop_rect;

	src_x = disp_info.src_crop_rect.x + x;
	if (((src_x + disp_info.src_crop_rect.w) <= image.dst_next.width) && (src_x >= 0))
		disp_rect.x = src_x;

	src_y = disp_info.src_crop_rect.y + y;
	if (((src_y + disp_info.src_crop_rect.h) <= image.dst_next.height) && (src_y >= 0))
		disp_rect.y = src_y;

	ret = image.opr.display->src_crop_rect_set(&disp_rect);

	return ret;
}

int image_scaler(int *ratio_percent)
{
	image_disp_info_t disp_info;
	image_enh_t src_enh, dst_enh;
	image_rect_t disp_rect, src_crop_rect;
	unsigned int scaler_width, scaler_height;
	int ret;

	if(*ratio_percent == image.dst_next.scaler_ratito){
		return 0;
	}
	
	ret = image.opr.process->rotate(&image.src,&image.full_buf, IMAGE_DEF_ROTATE);
	if (ret	!= 0) {
		printf("%s: image rotate failed!\n", __func__);
		return ret;
	}
	
	sunxi_image_rotate_scaler_standardized(&image.full_buf,IMAGE_DEF_ROTATE);

	ret = image.opr.process->rotate(&image.src,&image.dst_next, IMAGE_DEF_ROTATE);

	if (ret	!= 0) {
		printf("%s: image rotate failed!\n", __func__);
		return ret;
	}
	sunxi_image_rotate_fullsrceen_standardized(&image.dst_next,IMAGE_DEF_ROTATE);

	image_show_fill(&image.dst_next,0xcc000000);
	
	ret = image_show_clip(&image.dst_next,&image.full_buf);
	if(ret<0)
	{
		printf("%s: image_show_clip failed!\n", __func__);
		goto err;
	}
	#if 1
    scaler_width = ((*ratio_percent)+100) * image.dst_next.width / 100;
	scaler_height = ((*ratio_percent)+100) * image.dst_next.height / 100;
	//printf("scaler_width = %d,scaler_height = %d\n",scaler_width,scaler_height);
	if(sunxi_image_scaler_fullsrceen_standardized(&image.dst_next,scaler_width,scaler_height) < 0){
			printf("sunxi_image_scaler_adapt failed\n");
			return -1;
	}
	//printf("dst_next.w = %d,dst_next.h = %d\n",image.dst_next.width,image.dst_next.height);
	image_disp_rect_set(IMAGE_FULL_SCREEN);//设置显示区域
	src_crop_rect.x = 0;
	src_crop_rect.y = 0;
	src_crop_rect.w = image.dst_next.width;
	src_crop_rect.h = image.dst_next.height;////设置图片裁剪区域
	ret = image.opr.display->display(&image.dst_next, &src_crop_rect);
	//printf("ret = %d\n",ret);

	image.dst_next.scaler_ratito = *ratio_percent;
	//printf("image scaler change! = %d\n",image.dst_next.scaler_ratito);
	#else
	scaler_width = ((*ratio_percent)/2+100) * image.dst_previous.width / 100;
	scaler_height = ((*ratio_percent)/2+100) * image.dst_previous.height / 100;

	src_enh.buf = image.dst_previous;
	src_enh.clip_rect.w = src_enh.buf.width;
	src_enh.clip_rect.h = src_enh.buf.height;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;

	dst_enh.buf.phy_addr = image.dst_next.phy_addr;
	dst_enh.buf.vir_addr = image.dst_next.vir_addr;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	dst_enh.buf.width = scaler_width;
	dst_enh.buf.height = scaler_height;
	dst_enh.buf.comp = src_enh.buf.comp;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.w = scaler_width;
	dst_enh.clip_rect.h = scaler_height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	image.opr.process->scaler(&src_enh, &dst_enh);

	image.dst_next.width = scaler_width;
	image.dst_next.height = scaler_height;
	image.dst_next.length = image.dst_next.width * image.dst_next.height * image.dst_next.comp;
	image.opr.display->disp_info_get(&disp_info);
	disp_rect.w = (scaler_width > disp_info.screen_width) ? disp_info.screen_width : scaler_width;
	disp_rect.h = (scaler_height > disp_info.screen_height) ? disp_info.screen_height : scaler_height;
	disp_rect.x = (disp_info.screen_width - disp_rect.w) / 2;
	disp_rect.y = (disp_info.screen_height - disp_rect.h) / 2;
	image_disp_rect_set(&disp_rect);

	src_crop_rect.x = (scaler_width - disp_rect.w) / 2;
	src_crop_rect.y = (scaler_height - disp_rect.h) / 2;
	src_crop_rect.w = disp_rect.w;
	src_crop_rect.h = disp_rect.h;
	image.opr.display->display(&image.dst_next, &src_crop_rect);
	*ratio_percent = scaler_height * 100 / image.dst_previous.height;
	image.dst_next.scaler_ratito = *ratio_percent;
	printf("image scaler change! = %d\n",image.dst_next.scaler_ratito);
	#endif
	return 0;
err:
	return ret;
}


int image_effect_scaler_move(int *ratio_percent,int x_off ,int y_off)
{
	image_disp_info_t disp_info;
	image_enh_t src_enh, dst_enh;
	image_rect_t disp_rect, src_crop_rect;
	unsigned int scaler_width, scaler_height;
	int ret;
	
	ret = image.opr.process->rotate(&image.src,&image.full_buf, IMAGE_DEF_ROTATE);
	if (ret	!= 0) {
		printf("%s: image rotate failed!\n", __func__);
		return ret;
	}
	
	sunxi_image_rotate_scaler_standardized(&image.full_buf,IMAGE_DEF_ROTATE);

	ret = image.opr.process->rotate(&image.src,&image.dst_next, IMAGE_DEF_ROTATE);

	if (ret	!= 0) {
		printf("%s: image rotate failed!\n", __func__);
		return ret;
	}
	sunxi_image_rotate_fullsrceen_standardized(&image.dst_next,IMAGE_DEF_ROTATE);

	image_show_fill(&image.dst_next,0xcc000000);
	
	ret = image_show_clip(&image.dst_next,&image.full_buf);
	if(ret<0)
	{
		printf("%s: image_show_clip failed!\n", __func__);
		goto err;
	}
	#if 1
    scaler_width = ((*ratio_percent)+100) * image.dst_next.width / 100;
	scaler_height = ((*ratio_percent)+100) * image.dst_next.height / 100;
	//printf("scaler_width = %d,scaler_height = %d\n",scaler_width,scaler_height);
	if(sunxi_image_scaler_fullsrceen_move_standardized(&image.dst_next,scaler_width,scaler_height,x_off,y_off) < 0){
			printf("sunxi_image_scaler_adapt failed\n");
			return -1;
	}
	//printf("dst_next.w = %d,dst_next.h = %d\n",image.dst_next.width,image.dst_next.height);
	image_disp_rect_set(IMAGE_FULL_SCREEN);//设置显示区域
	src_crop_rect.x = 0;
	src_crop_rect.y = 0;
	src_crop_rect.w = image.dst_next.width;
	src_crop_rect.h = image.dst_next.height;////设置图片裁剪区域
	ret = image.opr.display->display(&image.dst_next, &src_crop_rect);
	//printf("ret = %d\n",ret);

	image.dst_next.scaler_ratito = *ratio_percent;
	//printf("image scaler change! = %d\n",image.dst_next.scaler_ratito);
	#else
	scaler_width = ((*ratio_percent)/2+100) * image.dst_previous.width / 100;
	scaler_height = ((*ratio_percent)/2+100) * image.dst_previous.height / 100;

	src_enh.buf = image.dst_previous;
	src_enh.clip_rect.w = src_enh.buf.width;
	src_enh.clip_rect.h = src_enh.buf.height;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;

	dst_enh.buf.phy_addr = image.dst_next.phy_addr;
	dst_enh.buf.vir_addr = image.dst_next.vir_addr;
	dst_enh.buf.fmt = IMAGE_FORMAT_ARGB8888;
	dst_enh.buf.width = scaler_width;
	dst_enh.buf.height = scaler_height;
	dst_enh.buf.comp = src_enh.buf.comp;
	dst_enh.buf.length = dst_enh.buf.width * dst_enh.buf.height * dst_enh.buf.comp;
	dst_enh.clip_rect.w = scaler_width;
	dst_enh.clip_rect.h = scaler_height;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	image.opr.process->scaler(&src_enh, &dst_enh);

	image.dst_next.width = scaler_width;
	image.dst_next.height = scaler_height;
	image.dst_next.length = image.dst_next.width * image.dst_next.height * image.dst_next.comp;
	image.opr.display->disp_info_get(&disp_info);
	disp_rect.w = (scaler_width > disp_info.screen_width) ? disp_info.screen_width : scaler_width;
	disp_rect.h = (scaler_height > disp_info.screen_height) ? disp_info.screen_height : scaler_height;
	disp_rect.x = (disp_info.screen_width - disp_rect.w) / 2;
	disp_rect.y = (disp_info.screen_height - disp_rect.h) / 2;
	image_disp_rect_set(&disp_rect);

	src_crop_rect.x = (scaler_width - disp_rect.w) / 2;
	src_crop_rect.y = (scaler_height - disp_rect.h) / 2;
	src_crop_rect.w = disp_rect.w;
	src_crop_rect.h = disp_rect.h;
	image.opr.display->display(&image.dst_next, &src_crop_rect);
	*ratio_percent = scaler_height * 100 / image.dst_previous.height;
	image.dst_next.scaler_ratito = *ratio_percent;
	printf("image scaler change! = %d\n",image.dst_next.scaler_ratito);
	#endif
	return 0;
err:
	return ret;
}


int image_show_normal(void)
{
	image_buffer_t dst_tmp;
	
	//image_dst_buffer_switch();//交换两个目标buffer
	dst_tmp = image.dst_next;
	image.dst_next = image.src;
	image.src = dst_tmp;
	image_scaler_to_disp_rect(&image.src, &image.dst_next);//缩放原始数据到next buffer
	image_rect_t crop_rect;

	crop_rect.x = (int)(IMAGE_HOR_RES_MAX -image.dst_next.width)/2;
	crop_rect.y = (int)(IMAGE_VER_RES_MAX -image.dst_next.height)/2;
	crop_rect.w = image.dst_next.width;
	crop_rect.h = image.dst_next.height;
	image.opr.display->display(&image.dst_next, &crop_rect);//设置显示区域和显示数据

	image.dst_next.scaler_ratito = 0;
	image.dst_next.rotate_angle = 0;
	return 0;
}
static int image_show_before(image_show_mode_t mode)
{
	int ret = 0;
	image_buffer_t dst_tmp;
	show_mode = mode;
	
	image_dst_buffer_switch();//交换两个目标buffer

	if(IMAGE_DEF_ROTATE)
	{
		ret = image.opr.process->rotate(&image.src,&image.dst_next, (image_rotate_angle_t)IMAGE_DEF_ROTATE);
		if (ret != 0) {
			printf("%s: image rotate failed!\n", __func__);
			return ret;
		}
		//printf("%s: image rotate successful!\n", __func__);
	}
	else
	{
		dst_tmp = image.dst_next;
		image.dst_next = image.src;
		image.src = dst_tmp;
	}
	if(mode == IMAGE_FULL_SCREEN_FILL)
	{
		image_show_fill(&image.dst_next,0xcc000000);
	}
	return 0;
}


static int image_show_fullsrceen_fade(image_show_mode_t mode)
{
	int ret = 0;
	image_buffer_t dst_tmp;
	show_mode = mode;

	if(IMAGE_DEF_ROTATE)
	{
		ret = image.opr.process->rotate(&image.src,&image.full_buf, (image_rotate_angle_t)IMAGE_DEF_ROTATE);
		if (ret	!= 0) {
			printf("%s: image rotate failed!\n", __func__);
			return ret;
		}
		//printf("%s: image rotate successful!\n", __func__);
	}
	else
	{
		dst_tmp = image.full_buf;
		image.full_buf = image.src;
		image.src = dst_tmp;
	}
	return 0;
}

static int image_show_after(void)
{
	
	/*
	if(image.full_buf.vir_addr)
	{
		ionHdle->pfree(image.full_buf.vir_addr);
		image.full_buf.vir_addr = NULL;
	}*/
	return image_show_clip(&image.dst_next,&image.full_buf);
}
static char * readSrcData(const char *path, int *pLen)
{
    FILE *fp = NULL;
    int ret = 0;
    char *data = NULL;

    fp = fopen(path, "rb");
    if(fp == NULL)
    {
        printf("read jpeg file error, errno(%d)\n", errno);
        return NULL;
    }

    fseek(fp,0,SEEK_END);
    *pLen = ftell(fp);
    rewind(fp);
    data = (char *) malloc (sizeof(char)*(*pLen));

    if(data == NULL)
	{
		printf("malloc memory fail\n");
		fclose(fp);
		return NULL;
	}

    ret = fread (data,1,*pLen,fp);
    if (ret != *pLen)
    {
        printf("read src file fail\n");
        fclose(fp);
        free(data);
        return NULL;
    }

    if(fp != NULL)
    {
        fclose(fp);
    }
    return data;
}


static void NV21toRGBorBGR(const uint8_t *input, int width, int height, uint8_t *output,int isRGB)
{
	int nv_off = width * height;
	int  i, j, y_index = 0;
	int y, u, v;
	int r, g, b, nv_index = 0;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++,++y_index) {
			nv_index = i / 2 * width + j - j % 2;

			y = input[y_index];
			u = input[nv_off + nv_index];
			v = input[nv_off + nv_index + 1];

			r = y + ((351 * (v - 128)) >> 8);  //r
			g = y - ((179 * (v - 128) + 86 * (u - 128)) >> 8); //g
			b = y + ((443 * (u - 128)) >> 8); //b

			r = ((r>255) ? 255 : (r<0) ? 0 : r);
			g = ((g>255) ? 255 : (g<0) ? 0 : g);
			b = ((b>255) ? 255 : (b<0) ? 0 : b);
			if (!isRGB) {
				output[y_index * 3 + 0] = (uint8_t)b;
				output[y_index * 3 + 1] = (uint8_t)g;
				output[y_index * 3 + 2] = (uint8_t)r;
			}
			else {
				output[y_index * 3 + 0] = (uint8_t)r;
				output[y_index * 3 + 1] = (uint8_t)g;
				output[y_index * 3 + 2] = (uint8_t)b;
			}
		}
	}
}

static unsigned char clip_value(unsigned char x,unsigned char min_val,unsigned char  max_val){
    if(x>max_val){
        return max_val;
    }else if(x<min_val){
        return min_val;
    }else{
        return x;
    }
}

static bool YUV420_TO_RGB24(unsigned char *yuvBuf, int w, int h, unsigned char *rgbBuf)
{
    int index_y, index_u, index_v;
    unsigned char y, u, v;
    unsigned char r, g, b;

    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            index_y = i * w + j;
            index_u = w * h + i / 4 * w + j / 2;
            index_v = w * h * 5 / 4 + i / 4 * w + j / 2;

            y = yuvBuf[index_y];
            u = yuvBuf[index_u];
            v = yuvBuf[index_v];           

            b = y + 1.772*(u - 128);                        //B = Y +1.779*(U-128)
            g = y - 0.34413*(u - 128) - 0.71414*(v - 128);  //G = Y-0.3455*(U-128)-0.7169*(V-128)
            r = y + 1.402*(v - 128);                        //R = Y+1.4075*(V-128)

            *(rgbBuf++) = clip_value(r,0,255);
            *(rgbBuf++) = clip_value(g,0,255);
            *(rgbBuf++) = clip_value(b,0,255);
        }
    }

    return true;
}


#define MAX(a ,b) ((a > b) ? a : b)
#define MIN(a ,b) ((a < b) ? a : b)
#define CLAP(a) (MAX((MIN(a, 0xff)), 0x00)) 
static void NV212BGR( unsigned char *imgY, int width, int height, unsigned char *imgDst)
{
	int w, h;
	int shift = 14, offset = 8192;
	int C0 = 22987, C1 = -11698, C2 = -5636, C3 = 29049;
 
	int y1,y2,u1,v1;
 
	unsigned char * pY1 = imgY;
	unsigned char * pY2 = imgY+width;
	unsigned char * pUV = imgY+width*height;
	
	unsigned char * pD1 = imgDst;
	unsigned char * pD2 = imgDst+width*3;
 
	for ( h = 0; h < height; h +=2 )
	{
		for ( w = 0; w < width; w +=2 )
		{
			v1 = *pUV-128;
			pUV++;
			u1 = *pUV-128;
			pUV++;
 
			
			y1 = *pY1;
			y2 = *pY2;
 
			*pD1++ = CLAP(y1+((u1 * C3 + offset) >> shift));
			*pD1++ = CLAP(y1+((u1 * C2 + v1 * C1 + offset) >> shift));
			*pD1++ = CLAP(y1+((v1 * C0 + offset) >> shift));
			*pD2++ = CLAP(y2+((u1 * C3 + offset) >> shift));
			*pD2++ = CLAP(y2+((u1 * C2 + v1 * C1 + offset) >> shift));
			*pD2++ = CLAP(y2+((v1 * C0 + offset) >> shift));
 
			pY1++;
			pY2++;
			y1 = *pY1;
			y2 = *pY2;
 
			*pD1++ = CLAP(y1+((u1 * C3 + offset) >> shift));
			*pD1++ = CLAP(y1+((u1 * C2 + v1 * C1 + offset) >> shift));
			*pD1++ = CLAP(y1+((v1 * C0 + offset) >> shift));
			*pD2++ = CLAP(y2+((u1 * C3 + offset) >> shift));
			*pD2++ = CLAP(y2+((u1 * C2 + v1 * C1 + offset) >> shift));
			*pD2++ = CLAP(y2+((v1 * C0 + offset) >> shift));
			pY1++;
			pY2++;
 
		}
		pY1 += width;
		pY2 += width;
		pD1 += 3*width;
		pD2 += 3*width;
 
	}
}


static int jpegdecoder_init(char const *filename)
{
	JpegDecoder* jpegdecoder = NULL;
    char* srcBuf = NULL;
    int srcBufLen = 0;
	ImgFrame* imgFrame = NULL;
	image_enh_t src_enh, dst_enh;
	image_buffer_t src_buffer;
	return -1;
	if(jpegdecoder == NULL)
	{
		jpegdecoder = JpegDecoderCreate();
	}
    if (NULL == jpegdecoder)
	{
        printf("create jpegdecoder failed\n");
        return -1;
    }
    srcBuf = readSrcData(filename, &srcBufLen);

	JpegDecoderSetDataSourceBuf(jpegdecoder, srcBuf, srcBufLen, JPEG_DECODE_SCALE_DOWN_1, JpegDecodeOutputDataNV21);
	//printf("srcBuf = %p,srcBufLen = %d\n",srcBuf,srcBufLen);
    //JpegDecoderSetDataSourceBuf(jpegdecoder, srcBuf, srcBufLen, JPEG_DECODE_SCALE_DOWN_2, JpegDecodeOutputDataYV12);
    imgFrame = JpegDecoderGetFrame(jpegdecoder);
    if (imgFrame == NULL) {
        printf("JpegDecoderGetFrame fail\n");
        JpegDecoderDestory(jpegdecoder);
        return -1;
    } else {
        //printf("JpegDecoderGetFrame successfully,imgFrame->mWidth = %d,imgFrame->mHeight = %d,imgFrame->mYuvData = %p,imgFrame->mYuvSize = %d\n",
        //    imgFrame->mWidth,imgFrame->mHeight,imgFrame->mYuvData,imgFrame->mYuvSize);
        //printf("imgFrame->mRGB565Data = %p,imgFrame->mRGB565Size = %d\n",imgFrame->mRGB565Data,imgFrame->mRGB565Size);
    }

	if (image.src.vir_addr != NULL) {
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}
	image.src.vir_addr = sunxi_image_palloc(imgFrame->mWidth*imgFrame->mHeight*3);
	NV212BGR(imgFrame->mYuvData, imgFrame->mWidth, imgFrame->mHeight, image.src.vir_addr);
	image.src.comp = 3;
	image.src.width = imgFrame->mWidth;
	image.src.height = imgFrame->mHeight;
	image.src.length = image.src.width * image.src.height * image.src.comp;
	image.src.fmt = IMAGE_FORMAT_BGR888;
	image.src.scaler_ratito = 0;
	image.src.rotate_angle = 0;
	image.src.frame_cnt = 1;
	image.src.delays = NULL;
	image.src.width_or  = image.src.width;
	image.src.height_or = image.src.height;
	image.src.phy_addr = sunxifb_mem_get_phyaddr(image.src.vir_addr);
	image.src.fd = sunxi_image_get_bufferFd(image.src.vir_addr);

	
	if(imgFrame->mYuvData != NULL)
	{
		free(imgFrame->mYuvData);
		imgFrame->mYuvData = NULL;
	}
	if(imgFrame->mRGB565Data != NULL)
	{
		free(imgFrame->mRGB565Data);
		imgFrame->mRGB565Data = NULL;
	}
	memset(imgFrame, 0x00, sizeof(ImgFrame));
	/*
	memset(&src_buffer, 0x00, sizeof(src_buffer));
	memset(&src_enh, 0x00, sizeof(src_enh));

	src_buffer.height = imgFrame->mHeight;
	src_buffer.width = imgFrame->mWidth;
	src_buffer.length = imgFrame->mYuvSize;
	src_buffer.vir_addr = imgFrame->mYuvData;
	src_buffer.fmt = IMAGE_FORMAT_YUV420P;
	src_enh.buf = src_buffer;
	src_enh.clip_rect.x = 0;
	src_enh.clip_rect.y = 0;
	src_enh.clip_rect.w = imgFrame->mWidth;
	src_enh.clip_rect.h = imgFrame->mHeight;

	memset(&dst_enh, 0x00, sizeof(dst_enh));
	image.src.vir_addr = ionHdle->palloc(imgFrame->mWidth * imgFrame->mHeight * 4);
	image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
	image.src.comp = 4;
	image.src.length = imgFrame->mWidth * imgFrame->mHeight * image.src.comp;
	image.src.height = imgFrame->mHeight;
	image.src.width = imgFrame->mWidth;
	image.src.fmt = IMAGE_FORMAT_ABGR8888;
	dst_enh.buf = image.src;
	dst_enh.clip_rect.x = 0;
	dst_enh.clip_rect.y = 0;
	dst_enh.clip_rect.w = imgFrame->mWidth;
	dst_enh.clip_rect.h = imgFrame->mHeight;
	image.opr.process->conver(&src_enh, &dst_enh, 1);

	for(int i=0;i<16;i++)
	{
		printf("dst_enh.vir_addr[%d] = %02x\n",i,((uint8*)(dst_enh.buf.vir_addr))[i]);
	}
	*/
    //JpegDecoderDestory(jpegdecoder);
	return 0;
}
static int is_jpeg(char const *filename)
{
	char *buff = strrchr(filename, '.');
	extern int  SLIB_stricmp(const char * p1_str, const char * p2_str);

	if (SLIB_stricmp((buff + 1), "JPG") == 0 || SLIB_stricmp((buff + 1), "jpg") == 0) {
		return 1;
	}
	/*else if (SLIB_stricmp((buff + 1), "JPEG") == 0 || SLIB_stricmp((buff + 1), "jpeg") == 0) {
		return 1;
	}*/
	else
	{
		return 0;
	}
}
static int is_gif(char const *filename)
{
	char *buff = strrchr(filename, '.');
	extern int  SLIB_stricmp(const char * p1_str, const char * p2_str);

	if (SLIB_stricmp((buff + 1), "GIF") == 0 || SLIB_stricmp((buff + 1), "gif") == 0 ) {
		return 1;
	} else {
		return 0;
	}
}

static int is_png(char const *filename)
{
	char *buff = strrchr(filename, '.');
	extern int  SLIB_stricmp(const char * p1_str, const char * p2_str);

	if (SLIB_stricmp((buff + 1), "PNG") == 0 || SLIB_stricmp((buff + 1), "png") == 0 ) {
		return 1;
	} else {
		return 0;
	}
}

static int is_bmp(char const *filename)
{
	char *buff = strrchr(filename, '.');
	extern int  SLIB_stricmp(const char * p1_str, const char * p2_str);

	if (SLIB_stricmp((buff + 1), "BMP") == 0 || SLIB_stricmp((buff + 1), "bmp") == 0 ) {
		return 1;
	} else {
		return 0;
	}
}

int image_scaler_decode(char *filename, image_buffer_t *buf)
{
	int width = 0,height = 0;
	int comp = 4;
	int ret;
	int parse_err = 0;
	int is_jpg;
	// int is_pro;
	void *data =NULL;
	int png_err = 0;
	int image_format = 0;

	//printf("filename = %s\n",filename);
	if (image.src.vir_addr != NULL)
	{
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}
	#if 1
	image_format = stbi_info_format(filename,&width,&height,&comp);//尝试获取图片信息
	//LV_LOG_USER("stbi_info_format:image_format = %d",image_format);
	if(!image_format)
	{
		parse_err = 1;
	}
	is_jpg = is_jpeg(filename);//jpg带有scalerdown，先算出scalerdown之后的宽高
	//printf("is_jpg = %d\n",is_jpg);
	if(image_format==1)
	{
		int scalerdown = jpg_get_scalerdown(width,height);
		width  = (width +((1<<scalerdown)-1)) >>scalerdown;
		height = (height+((1<<scalerdown)-1)) >>scalerdown;
		comp = 3;
	}
	if(abs(width)*height*comp > DECODE_LIMIT_SIZE)//限制一下解码大小
	{
		printf("image size too large 1!\n");
		parse_err = 1;
		return -1;
	}

	if(!parse_err)//图片检查失败了，显示一张错误图片
	{
		if(image_format==2)
		{
			//printf("run to png\n");
			comp = 4;//不确定解码之后是几个通道，多申请为4通道
			image.src.vir_addr = ionHdle->palloc(width * height * comp);
			image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
			ret = png_decode(filename,image.src.vir_addr,&buf->width,&buf->height,&comp);
			//printf("buf1 w = %d h = %d comp= %d ret = %d\n",buf->width,buf->height,comp,ret);
			if(ret == 0 && buf->width == width && buf->height == height)
			{
				buf->comp = comp;
				buf->length = width * height * comp;
				if(comp == 4)
				{
					buf->fmt = IMAGE_FORMAT_ABGR8888;
				}
				else
				{
					buf->fmt = IMAGE_FORMAT_BGR888;
				}
				buf->scaler_ratito = 0;
				buf->rotate_angle = 0;
				buf->frame_cnt = 1;
				buf->delays = NULL;
				buf->width_or  = buf->width;
				buf->height_or = buf->height;
				buf->vir_addr = image.src.vir_addr;
				buf->phy_addr = image.src.phy_addr;
				goto standardized;
			}
			else
			{
				printf("png free ion");
				ionHdle->pfree(image.src.vir_addr);
			}
			png_err = 1;

		}
		if(image_format==1)
		{
			ret = jpegdecoder_init(filename);//硬件解码暂时不用
			//printf("ret = %d \n",ret);
			if(ret == 0)
			{
				buf->comp = 3;
				buf->length = buf->width * buf->height * buf->comp;
				buf->fmt = IMAGE_FORMAT_BGR888;
				buf->scaler_ratito = 0;
				buf->rotate_angle = 0;
				buf->frame_cnt = 1;
				buf->delays = NULL;
				buf->width_or  = buf->width;
				buf->height_or = buf->height;
				goto standardized;
			}
			else
			{
                //printf("w = %d h = %d c = %d\n",width,height,comp);
				image.src.vir_addr = ionHdle->palloc(width * height * comp);
				//printf("ion addr = 0x%lx\n",image.src.vir_addr);
				image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
				//system("free");
				ret = jpg_decode_sw(filename,image.src.vir_addr,&buf->width,&buf->height,&comp);
                //printf("buf w = %d h = %d ret = %d\n",buf->width,buf->height,ret);
                //printf("image.src.vir_addr = %p\n",image.src.vir_addr);
				if(ret == 0 && buf->width == width && buf->height == height)
				{
					buf->comp = comp;
					buf->length = width * height * comp;
					buf->fmt = IMAGE_FORMAT_BGR888;
					buf->scaler_ratito = 0;
					buf->rotate_angle = 0;
					buf->frame_cnt = 1;
					buf->delays = NULL;
					buf->width_or  = buf->width;
					buf->height_or = buf->height;
					goto standardized;
				}
				else
				{
					printf("jpg free ion");
					ionHdle->pfree(image.src.vir_addr);
					image.src.vir_addr = NULL;
				}
				png_err = 1;
			}
		}
		if(image_format==4)
		{
            //printf("run to bmp\n");
			comp = 4;//不确定解码之后是几个通道，多申请为4通道
			image.src.vir_addr = ionHdle->palloc(width * height * comp);
			image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
			ret = bmp_decode_sw(filename,image.src.vir_addr,&buf->width,&buf->height,&comp);
            //printf("buf1 w = %d h = %d ret = %d\n",buf->width,buf->height,ret);
			if(ret == 0 && buf->width == width && buf->height == height)
			{
				buf->comp = comp;
				buf->length = width * height * comp;
				buf->fmt = IMAGE_FORMAT_ABGR8888;
				buf->scaler_ratito = 0;
				buf->rotate_angle = 0;
				buf->frame_cnt = 1;
				buf->delays = NULL;
				buf->width_or  = buf->width;
				buf->height_or = buf->height;
				goto standardized;
			}
			else
			{
				printf("bmp free ion");
				ionHdle->pfree(image.src.vir_addr);
			}
			png_err = 1;
		}
		else
		{
			png_err = 1;
		}
	}
	#endif
	//非jpg或者jpg解码失败了，用stbimage解码
	{
		//int time2 = get_time();
		int width = 0,height = 0,comp;
		int ret;
		int parse_err = 0;
		ret = stbi_info(filename,&width,&height,&comp);
		if(!ret)
		{
			parse_err = 1;
		}
		if(abs(width)*height*4 > DECODE_LIMIT_SIZE)
		{
			printf("image size too large!\n");
			parse_err = 1;
		}
		if(png_err == 1)
		{
			parse_err = 1;
		}
		if(!parse_err)
		{
			data = stbi_load(filename, (int *)&buf->width, (int *)&buf->height, (int *)&buf->comp, 4);/*先直接解码图片，后续可以先解析图片信息再决定要不要解码*/
		}
		else
		{
			//data = stbi_load("/usr/res/image/error.png", (int *)&buf->width, (int *)&buf->height, (int *)&buf->comp, 4);/*先直接解码图片，后续可以先解析图片信息再决定要不要解码*/
			printf("stbi_load fail!\n");
		}
		//printf("langaojie get decode time = %d us\n",get_time()-time2);
		//printf("[%d]langaojie test w = %d h = %d chn = %d\n\n",__LINE__,buf->width,buf->height, buf->comp);
		if (data)
		{
			image.src.vir_addr = ionHdle->palloc(buf->width * buf->height * 4);
			if (image.src.vir_addr != NULL)
			{
				image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
				image.src.fd = ionHdle->get_bufferFd(image.src.vir_addr);
				buf->comp = 4;
				buf->length = buf->width * buf->height * buf->comp;
				buf->fmt = IMAGE_FORMAT_ABGR8888;
				buf->scaler_ratito = 0;
				buf->rotate_angle = 0;
				buf->frame_cnt = 1;
				buf->delays = NULL;
				buf->width_or  = buf->width;
				buf->height_or = buf->height;
				//int time1 = get_time();
				memcpy((void *)buf->vir_addr, data, buf->length);
				//printf("langaojie get memcpy time = %d us\n",get_time()-time1);
			}
		}
		else
		{
			return -1;
		}
	}
	if(data)
	{
		free(data);
		data =NULL;
	}

standardized:
	//printf("standardized\n");
	sunxi_image_scaler_standardized(buf);
	return 0;
}


int image_decode(char *filename, image_buffer_t *buf)
{
	int width = 0,height = 0;
	int comp = 4;
	int ret;
	int parse_err = 0;
	int is_jpg;
	// int is_pro;
	void *data =NULL;
	int png_err = 0;
	int image_format = 0;

	//printf("filename = %s\n",filename);
	if (image.src.vir_addr != NULL)
	{
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}
	#if 1
	image_format = stbi_info_format(filename,&width,&height,&comp);//尝试获取图片信息
	//LV_LOG_USER("stbi_info_format:image_format = %d",image_format);
	if(!image_format)
	{
		parse_err = 1;
	}
	is_jpg = is_jpeg(filename);//jpg带有scalerdown，先算出scalerdown之后的宽高
	//printf("is_jpg = %d\n",is_jpg);
	if(image_format==1)
	{
		int scalerdown = jpg_get_scalerdown(width,height);
		width  = (width +((1<<scalerdown)-1)) >>scalerdown;
		height = (height+((1<<scalerdown)-1)) >>scalerdown;
		comp = 3;
	}
	if(abs(width)*height*comp > DECODE_LIMIT_SIZE)//限制一下解码大小
	{
		printf("image size too large 1!\n");
		parse_err = 1;
		return -1;
	}

	if(!parse_err)//图片检查失败了，显示一张错误图片
	{
		if(image_format==2)
		{
			//printf("run to png\n");
			comp = 4;//不确定解码之后是几个通道，多申请为4通道
			image.src.vir_addr = ionHdle->palloc(width * height * comp);
			image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
			ret = png_decode(filename,image.src.vir_addr,&buf->width,&buf->height,&comp);
			//printf("buf1 w = %d h = %d comp= %d ret = %d\n",buf->width,buf->height,comp,ret);
			if(ret == 0 && buf->width == width && buf->height == height)
			{
				buf->comp = comp;
				buf->length = width * height * comp;
				if(comp == 4)
				{
					buf->fmt = IMAGE_FORMAT_ABGR8888;
				}
				else
				{
					buf->fmt = IMAGE_FORMAT_BGR888;
				}
				buf->scaler_ratito = 0;
				buf->rotate_angle = 0;
				buf->frame_cnt = 1;
				buf->delays = NULL;
				buf->width_or  = buf->width;
				buf->height_or = buf->height;
				buf->vir_addr = image.src.vir_addr;
				buf->phy_addr = image.src.phy_addr;
				goto standardized;
			}
			else
			{
				printf("png free ion");
				ionHdle->pfree(image.src.vir_addr);
			}
			png_err = 1;

		}
		if(image_format==1)
		{
			ret = jpegdecoder_init(filename);//硬件解码暂时不用
			//printf("ret = %d \n",ret);
			if(ret == 0)
			{
				buf->comp = 3;
				buf->length = buf->width * buf->height * buf->comp;
				buf->fmt = IMAGE_FORMAT_BGR888;
				buf->scaler_ratito = 0;
				buf->rotate_angle = 0;
				buf->frame_cnt = 1;
				buf->delays = NULL;
				buf->width_or  = buf->width;
				buf->height_or = buf->height;
				goto standardized;
			}
			else
			{
                //printf("w = %d h = %d c = %d\n",width,height,comp);
				image.src.vir_addr = ionHdle->palloc(width * height * comp);
				//printf("ion addr = 0x%lx\n",image.src.vir_addr);
				image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
				//system("free");
				ret = jpg_decode_sw(filename,image.src.vir_addr,&buf->width,&buf->height,&comp);
                //printf("buf w = %d h = %d ret = %d\n",buf->width,buf->height,ret);
                //printf("image.src.vir_addr = %p\n",image.src.vir_addr);
				if(ret == 0 && buf->width == width && buf->height == height)
				{
					buf->comp = comp;
					buf->length = width * height * comp;
					buf->fmt = IMAGE_FORMAT_BGR888;
					buf->scaler_ratito = 0;
					buf->rotate_angle = 0;
					buf->frame_cnt = 1;
					buf->delays = NULL;
					buf->width_or  = buf->width;
					buf->height_or = buf->height;
					goto standardized;
				}
				else
				{
					printf("jpg free ion");
					ionHdle->pfree(image.src.vir_addr);
					image.src.vir_addr = NULL;
				}
				png_err = 1;
			}
		}
		if(image_format==4)
		{
            //printf("run to bmp\n");
			comp = 4;//不确定解码之后是几个通道，多申请为4通道
			image.src.vir_addr = ionHdle->palloc(width * height * comp);
			image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
			ret = bmp_decode_sw(filename,image.src.vir_addr,&buf->width,&buf->height,&comp);
            //printf("buf1 w = %d h = %d ret = %d\n",buf->width,buf->height,ret);
			if(ret == 0 && buf->width == width && buf->height == height)
			{
				buf->comp = comp;
				buf->length = width * height * comp;
				buf->fmt = IMAGE_FORMAT_ABGR8888;
				buf->scaler_ratito = 0;
				buf->rotate_angle = 0;
				buf->frame_cnt = 1;
				buf->delays = NULL;
				buf->width_or  = buf->width;
				buf->height_or = buf->height;
				goto standardized;
			}
			else
			{
				printf("bmp free ion");
				ionHdle->pfree(image.src.vir_addr);
			}
			png_err = 1;
		}
		else
		{
			png_err = 1;
		}
	}
	#endif
	//非jpg或者jpg解码失败了，用stbimage解码
	{
		//int time2 = get_time();
		int width = 0,height = 0,comp;
		int ret;
		int parse_err = 0;
		ret = stbi_info(filename,&width,&height,&comp);
		if(!ret)
		{
			parse_err = 1;
		}
		if(abs(width)*height*4 > DECODE_LIMIT_SIZE)
		{
			printf("image size too large!\n");
			parse_err = 1;
		}
		if(png_err == 1)
		{
			parse_err = 1;
		}
		if(!parse_err)
		{
			data = stbi_load(filename, (int *)&buf->width, (int *)&buf->height, (int *)&buf->comp, 4);/*先直接解码图片，后续可以先解析图片信息再决定要不要解码*/
		}
		else
		{
			//data = stbi_load("/usr/res/image/error.png", (int *)&buf->width, (int *)&buf->height, (int *)&buf->comp, 4);/*先直接解码图片，后续可以先解析图片信息再决定要不要解码*/
			printf("stbi_load fail!\n");
		}
		//printf("langaojie get decode time = %d us\n",get_time()-time2);
		//printf("[%d]langaojie test w = %d h = %d chn = %d\n\n",__LINE__,buf->width,buf->height, buf->comp);
		if (data)
		{
			image.src.vir_addr = ionHdle->palloc(buf->width * buf->height * 4);
			if (image.src.vir_addr != NULL)
			{
				image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
				image.src.fd = ionHdle->get_bufferFd(image.src.vir_addr);
				buf->comp = 4;
				buf->length = buf->width * buf->height * buf->comp;
				buf->fmt = IMAGE_FORMAT_ABGR8888;
				buf->scaler_ratito = 0;
				buf->rotate_angle = 0;
				buf->frame_cnt = 1;
				buf->delays = NULL;
				buf->width_or  = buf->width;
				buf->height_or = buf->height;
				//int time1 = get_time();
				memcpy((void *)buf->vir_addr, data, buf->length);
				//printf("langaojie get memcpy time = %d us\n",get_time()-time1);
			}
		}
		else
		{
			return -1;
		}
	}
	if(data)
	{
		free(data);
		data =NULL;
	}

standardized:
	//printf("standardized\n");
	image_standardized(buf);
	return 0;
}

/*解码一张图片，解码信息存放于buf中*/
/*gif图片使用jpg解码方式解码，只获取第一帧数据，显示时再完全解码*/
int image_decode1(char const *filename, image_buffer_t *buf)
{
	unsigned char *data = NULL;

	if (image.src.vir_addr != NULL) {
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}
//	if (is_jpeg(filename)) {
	if (0) {
		jpegdecoder_init(filename);/*硬件解码jpg，输出格式为YV12，暂时不使用*/
	} else {
		if(0)//is_gif(filename))/*解码完成之后，把第一帧数据标准化，用作显示缩略图*/
		{
			printf("run to gif decode!");
			int width,height,frame_cnt,comp;
			int srcBufLen=0;
			const unsigned char *srcBuf;
			int *delays;//帧间隔，单位ms

			srcBuf = (const unsigned char *)readSrcData(filename, &srcBufLen);
			data = stbi_load_gif_from_memory(srcBuf, srcBufLen, &delays, &width,&height,&frame_cnt,&comp,0);/*解码库只支持内存方式加载gif*/
			//printf("gif w = %d h = %d frame_cnt = %d comp = %d\n",width,height,frame_cnt,comp);
			if(data && width*height*comp*frame_cnt <= 800*1280*4){/*暂时限制gif最大为800*1280*/
				image.src.vir_addr = ionHdle->palloc(buf->width * buf->height * 4);
				if (image.src.vir_addr != NULL) {
					image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
					buf->comp = 4;
					buf->length = buf->width * buf->height * buf->comp;
					buf->fmt = IMAGE_FORMAT_ABGR8888;
					buf->scaler_ratito = 0;
					buf->rotate_angle = 0;
					buf->frame_cnt = frame_cnt;
					buf->delays = delays;
					//int time1 = get_time();
					memcpy((void *)buf->vir_addr, data, buf->length);
					//printf("langaojie get memcpy time = %d us\n",get_time()-time1);

				}
			}
		}
		else
		{
			//int time2 = get_time();
			int width = 0,height = 0,comp;
			int ret;
			int parse_err = 0;
			ret = stbi_info(filename,&width,&height,&comp);
			if(!ret)
			{
				parse_err = 1;
			}
			if(abs(width)*height*4 > DECODE_LIMIT_SIZE)
			{
				printf("image size too large!\n");
				parse_err = 1;
			}
			if(!parse_err)
			{
				data = stbi_load(filename, (int *)&buf->width, (int *)&buf->height, (int *)&buf->comp, 4);/*先直接解码图片，后续可以先解析图片信息再决定要不要解码*/
			}
			else
			{
				data = stbi_load("/usr/res/image/error.png", (int *)&buf->width, (int *)&buf->height, (int *)&buf->comp, 4);/*先直接解码图片，后续可以先解析图片信息再决定要不要解码*/
			}
			//printf("langaojie get decode time = %d us\n",get_time()-time2);
			//printf("langaojie test w = %d h = %d chn = %d\n\n",buf->width,buf->height, buf->comp);
			if (data)
			{
				image.src.vir_addr = ionHdle->palloc(buf->width * buf->height * 4);
				if (image.src.vir_addr != NULL)
				{
					image.src.phy_addr = ionHdle->cpu_get_phyaddr(image.src.vir_addr);
					image.src.fd = ionHdle->get_bufferFd(image.src.vir_addr);
					buf->comp = 4;
					buf->length = buf->width * buf->height * buf->comp;
					buf->fmt = IMAGE_FORMAT_ABGR8888;
					buf->scaler_ratito = 0;
					buf->rotate_angle = 0;
					buf->frame_cnt = 1;
					buf->delays = NULL;
					buf->width_or  = buf->width;
					buf->height_or = buf->height;
					//int time1 = get_time();
					memcpy((void *)buf->vir_addr, data, buf->length);
					//printf("langaojie get memcpy time = %d us\n",get_time()-time1);
				}
			}
		}
		if(data)
		{
			free(data);
		}
	}

	if (image.src.vir_addr == NULL)
	{
		printf("%s width:%d, height:%d comp:%d too big!\n", __FUNCTION__, buf->width, buf->height, buf->comp);
		return -1;
	}
	//int time1 = get_time();
	//image_standardized(buf);
	sunxi_image_scaler_standardized(buf);
	//printf("langaojie get standar time = %d us\n",get_time()-time1);
	if(0)
	{
		char filename[100];
		sprintf(filename,"/mnt/exUDISK/decode_data_%d_%d_argb.bin",buf->width, buf->height);
		image_save_file(buf,filename);

	}

    return 0;
}

int image_show_single(image_buffer_t *buf,image_show_mode_t mode)
{
	image_rect_t crop_rect;
	(void)mode;
	//image_show_before();
	if(0)
	{
		char filename[100];
		sprintf(filename,"/mnt/exUDISK/bin/disp_data_%d_%d_argb.bin",image.dst_next.width, image.dst_next.height);
		image_save_file(&image.dst_next,filename);

	}
	crop_rect.x = (IMAGE_VER_RES_MAX -image.dst_next.width)/2;
	crop_rect.y = (IMAGE_HOR_RES_MAX -image.dst_next.height)/2;
	crop_rect.w = image.dst_next.width;
	crop_rect.h = image.dst_next.height;
	image.opr.display->display(&image.dst_next, &crop_rect);//设置显示区域和显示数据
	return 0;
}

int image_effect_show(char *filename, image_show_mode_t showmode ,image_effect_show_mode_t mode)
{
	int ret;
	image_disp_info_t disp_info;
	image.opr.display->disp_info_get(&disp_info);
	
	show_mode = showmode;
	if(image_scaler_decode(filename, &image.src) < 0){
		printf("image_decode failed\n");
		return -1;
	}
	if(show_mode == IMAGE_FULL_SCREEN_SCLAER)
	{
		//printf("src.w = %d,src.h = %d\n",image.src.width,image.src.height);
		if(image_show_before(show_mode) < 0)
		{
			printf("image_show_before failed\n");
			return -1;
		}
		//printf("dst_next.w = %d,dst_next.h = %d\n",image.dst_next.width,image.dst_next.height);
		if(sunxi_image_scaler_adapt_standardized(&image.dst_next,disp_info.disp_rect.w,disp_info.disp_rect.h) < 0){
				printf("sunxi_image_scaler_adapt failed\n");
				return -1;
		}
	}
	else
	{
		image_dst_buffer_switch();//交换两个目标buffer
		ret = image.opr.process->rotate(&image.src,&image.full_buf, IMAGE_DEF_ROTATE);
		if (ret	!= 0) {
			printf("%s: image rotate failed!\n", __func__);
			return ret;
		}
		
		sunxi_image_rotate_scaler_standardized(&image.full_buf,IMAGE_DEF_ROTATE);

		ret = image.opr.process->rotate(&image.src,&image.dst_next, IMAGE_DEF_ROTATE);

		if (ret	!= 0) {
			printf("%s: image rotate failed!\n", __func__);
			return ret;
		}
		sunxi_image_rotate_fullsrceen_standardized(&image.dst_next,IMAGE_DEF_ROTATE);

		image_show_fill(&image.dst_next,0xcc000000);
		
		ret = image_show_clip(&image.dst_next,&image.full_buf);
		if(ret<0)
		{
			printf("%s: image_show_clip failed!\n", __func__);
			return -1;
		}
	}
	
	if(mode == IMAGE_SHOW_RANDOM)
	{
		mode = rand()%(IMAGE_SHOW_MAX-3)+2;//去掉normal random和max三个选项，向后偏移2，只选择特效。

	}
	//printf("effect = %d\n",mode);
	switch (mode) {
		case IMAGE_SHOW_SLIDE_UP:
		case IMAGE_SHOW_SLIDE_DOWN:
		case IMAGE_SHOW_SLIDE_LEFT:
		case IMAGE_SHOW_SLIDE_RIGHT:
			image_show_slide(&image.dst_next,mode);
			break;

		case IMAGE_SHOW_STRETCH_UP:
		case IMAGE_SHOW_STRETCH_DOWN:
		case IMAGE_SHOW_STRETCH_LEFT:
		case IMAGE_SHOW_STRETCH_RIGHT:
			image_show_stretch(&image.dst_next,mode);
			break;

		case IMAGE_SHOW_ZOOM_IN:
		case IMAGE_SHOW_ZOOM_OUT:
			image_show_zoom(&image.dst_next,mode);
			break;

		case IMAGE_SHOW_FADE:
			image_show_fade(&image.dst_next,mode);
			break;

		case IMAGE_SHOW_PERSIANBLIND_H:
		case IMAGE_SHOW_PERSIANBLIND_V:
			image_show_persianblind(&image.dst_next,mode);
			break;

		case IMAGE_SHOW_MOSIAC:
			image_show_mosaic(&image.dst_next,mode);
			break;

		default:
			image_show_single(&image.dst_next,mode);
			break;
	}
	/*对于gif图片，只有第一帧数据做特效，其余的正常播放。播放完毕后，显示回第一帧数据*/
	// if(image.src.frame_cnt > 1)
	// {

	// }
	return 0;
}

int image_effect_scroll_prepare(char *filename)
{
	int ret;
	image_disp_info_t disp_info;
	image.opr.display->disp_info_get(&disp_info);

	if(image_scaler_decode(filename, &image.src) < 0){
		printf("image_decode failed\n");
		return -1;
	}
	if(show_mode == IMAGE_FULL_SCREEN_SCLAER)
	{
		//printf("src.w = %d,src.h = %d\n",image.src.width,image.src.height);
		if(image_show_before(show_mode) < 0)
		{
			printf("image_show_before failed\n");
			return -1;
		}
		//printf("dst_next.w = %d,dst_next.h = %d\n",image.dst_next.width,image.dst_next.height);
		if(sunxi_image_scaler_adapt_standardized(&image.dst_next,disp_info.disp_rect.w,disp_info.disp_rect.h) < 0){
				printf("sunxi_image_scaler_adapt failed\n");
				return -1;
		}
	}
	else
	{
		image_dst_buffer_switch();//交换两个目标buffer
		
		ret = image.opr.process->rotate(&image.src,&image.full_buf, IMAGE_DEF_ROTATE);
		if (ret	!= 0) {
			printf("%s: image rotate failed!\n", __func__);
			return ret;
		}
		
		sunxi_image_rotate_scaler_standardized(&image.full_buf,IMAGE_DEF_ROTATE);

		ret = image.opr.process->rotate(&image.src,&image.dst_next, IMAGE_DEF_ROTATE);

		if (ret	!= 0) {
			printf("%s: image rotate failed!\n", __func__);
			return ret;
		}
		sunxi_image_rotate_fullsrceen_standardized(&image.dst_next,IMAGE_DEF_ROTATE);

		image_show_fill(&image.dst_next,0xcc000000);
		
		ret = image_show_clip(&image.dst_next,&image.full_buf);
		if(ret<0)
		{
			printf("%s: image_show_clip failed!\n", __func__);
			return -1;
		}
	}
	return 0;
}

int image_effect_scroll_reset(void)
{
	int ret;
	image_buffer_t dst_tmp;

	dst_tmp = image.dst_previous;
	image.dst_previous = image.dst_next;
	image.dst_next = dst_tmp;

	return 0;
}


int image_effect_scroll_show(image_effect_show_mode_t mode , int step ,int loop)
{
	int ret;
	if(mode == IMAGE_SHOW_RANDOM)
	{
		mode = rand()%(IMAGE_SHOW_MAX-3)+2;//去掉normal random和max三个选项，向后偏移2，只选择特效。
	}
	//printf("effect = %d\n",mode);
	switch (mode) {
		case IMAGE_SHOW_SLIDE_UP:
		case IMAGE_SHOW_SLIDE_DOWN:
		case IMAGE_SHOW_SLIDE_LEFT:
		case IMAGE_SHOW_SLIDE_RIGHT:
			image_show_slide_step(&image.dst_next,mode, step,loop);
			break;

		case IMAGE_SHOW_STRETCH_UP:
		case IMAGE_SHOW_STRETCH_DOWN:
		case IMAGE_SHOW_STRETCH_LEFT:
		case IMAGE_SHOW_STRETCH_RIGHT:
			image_show_stretch_step(&image.dst_next,mode, step,loop);
			break;

		case IMAGE_SHOW_ZOOM_IN:
		case IMAGE_SHOW_ZOOM_OUT:
			image_show_zoom_step(&image.dst_next,mode, step,loop);
			break;

		case IMAGE_SHOW_FADE:
			image_show_fade_step(&image.dst_next,mode, step,loop);
			break;

		case IMAGE_SHOW_PERSIANBLIND_H:
		case IMAGE_SHOW_PERSIANBLIND_V:
			image_show_persianblind_step(&image.dst_next,mode, step,loop);
			break;

		case IMAGE_SHOW_MOSIAC:
			image_show_mosaic_step(&image.dst_next,mode, step,loop);
			break;

		default:
			image_show_single(&image.dst_next,mode);
			break;
	}
	return 0;
}



int image_show_multi1(image_buffer_t *buf)
{
	// int width,height,frame_cnt,comp;
	//		int srcBufLen;
	//		char *srcBuf;
	//		int *delays;//帧间隔，单位ms

	//		srcBuf = readSrcData(filename, &srcBufLen);
	//		data = stbi_load_gif_from_memory(srcBuf, srcBufLen, &delays, &width,&height,&frame_cnt,&comp,0);/*解码库只支持内存方式加载gif*/

	//		image_rect_t crop_rect;
	//		image_buffer_t buf_tmp;
	//		crop_rect.x = 0;
	//		crop_rect.y = 0;
	//		crop_rect.w = width;
	//		crop_rect.h = height;

	//		buf_tmp.width = width;
	//		buf_tmp.height = height;
	//		buf_tmp.comp = 4;
	//		buf_tmp.length = width *height * buf_tmp.comp;
	//		buf_tmp.fmt = IMAGE_FORMAT_ABGR8888;
	//		buf_tmp.scaler_ratito = 0;
	//		buf_tmp.rotate_angle = 0;
	//		buf_tmp.vir_addr = ionHdle->palloc(buf_tmp.width * buf_tmp.height * 4);
	//		buf_tmp.phy_addr = ionHdle->cpu_get_phyaddr(buf_tmp.vir_addr);
	//		int i;
	//		for(i=0;i<frame_cnt;i++)
	//		{
	//			int *temp = delays;
	//			printf("i = %d data = %p\n",i,data+buf_tmp.length*i);
	//			memcpy(buf_tmp.vir_addr,data+buf_tmp.length*i,buf_tmp.length);
	//			image.opr.display->display(&buf_tmp, &crop_rect);//设置显示区域和显示数据
	//			{
	//				char filename[100];
	//				sprintf(filename,"/mnt/exUDISK/bin/gif_data_%d_%d_%dargb.bin",buf_tmp.width, buf_tmp.height,i);
	//				image_save_file(&buf_tmp,filename);

	//			}
	//			usleep((*temp)*1000);
	//			//memset(buf_tmp.vir_addr,0xff,buf_tmp.length);
	//			//usleep((1000)*1000);
	//			temp ++;
	//		}

	return 0;
}

static int show_multi_pthread(void *arg)
{
	return 0;
}
int image_show_multi(image_buffer_t *buf)
{
	// ret = pthread_create(&image_mgr.gif_id, NULL, show_multi_pthread, NULL);
	// if (ret != 0) {
	//	printf("%s: pthread create fail!\n", __func__);
	// }
	 return 0;
}

/*显示一张图片*/
int image_show(const char *filename, image_show_mode_t mode)
{
	int ret;
	image_rect_t crop_rect;
	image_disp_info_t disp_info;
	image.opr.display->disp_info_get(&disp_info);

	show_mode = mode;
	if(mode == IMAGE_FULL_SCREEN_SCLAER)
	{
		if(image_scaler_decode(filename, &image.src) < 0){
				printf("image_decode failed\n");
				return -1;
		}

		//printf("src.w = %d,src.h = %d\n",image.src.width,image.src.height);
		if(image_show_before(show_mode) < 0)
		{
			printf("image_show_before failed\n");
			return -1;
		}
		//printf("dst_next.w = %d,dst_next.h = %d\n",image.dst_next.width,image.dst_next.height);
		if(sunxi_image_scaler_adapt_standardized(&image.dst_next,disp_info.disp_rect.w,disp_info.disp_rect.h) < 0){
				printf("sunxi_image_scaler_adapt failed\n");
				return -1;
		}
		//printf("dst_next.w = %d,dst_next.h = %d\n",image.dst_next.width,image.dst_next.height);
		image_disp_rect_set(IMAGE_FULL_SCREEN);//设置显示区域
		crop_rect.x = 0;
		crop_rect.y = 0;
		crop_rect.w = image.dst_next.width;
		crop_rect.h = image.dst_next.height;////设置图片裁剪区域
		ret = image.opr.display->display(&image.dst_next, &crop_rect);
		//printf("ret = %d\n",ret);
	}
	else if(mode == IMAGE_FULL_SCREEN_FILL)
	{
		/*
		if(image_decode(filename, &image.src) < 0){
			printf("image_decode failed\n");
			return -1;
		}
		//printf("src.w = %d,src.h = %d\n",image.src.width,image.src.height);
		if(image_show_before(mode) < 0)
		{
			printf("image_show_before failed\n");
			return -1;
		}
		else
		{
			//printf("dst_next.w = %d,dst_next.h = %d\n",image.dst_next.width,image.dst_next.height);
		}
		
		if(image_scaler_decode(filename, &image.src) < 0){
			printf("image_decode failed\n");
			return -1;
		}
		//printf("src.w = %d,src.h = %d\n",image.src.width,image.src.height);
		if(image_show_fullsrceen_fade(mode) < 0)
		{
			printf("image_show_fullsrceen_fade failed\n");
			return -1;
		}
		else
		{
			//printf("full_buf.w = %d,full_buf.h = %d\n",image.full_buf.width,image.full_buf.height);
			if(image_show_after()<0)
			{
				printf("image_show_after error\n");
				return -1;
			}
			else
			{
				//printf("image_show_after successful\n");
			}
		}*/
		image_dst_buffer_switch();//交换两个目标buffer
	
		if(image_scaler_decode(filename, &image.src) < 0){
			printf("image_decode failed\n");
			return -1;
		}

		ret = image.opr.process->rotate(&image.src,&image.full_buf, IMAGE_DEF_ROTATE);
		if (ret	!= 0) {
			printf("%s: image rotate failed!\n", __func__);
			return ret;
		}
		
		sunxi_image_rotate_scaler_standardized(&image.full_buf,IMAGE_DEF_ROTATE);

		ret = image.opr.process->rotate(&image.src,&image.dst_next, IMAGE_DEF_ROTATE);

		if (ret	!= 0) {
			printf("%s: image rotate failed!\n", __func__);
			return ret;
		}
		sunxi_image_rotate_fullsrceen_standardized(&image.dst_next,IMAGE_DEF_ROTATE);

		image_show_fill(&image.dst_next,0xcc000000);
		
		ret = image_show_clip(&image.dst_next,&image.full_buf);
		if(ret<0)
		{
			printf("%s: image_show_clip failed!\n", __func__);
			return -1;
		}
		if(0)
		{
			printf("full_buf.w = %d,full_buf.h = %d\n",image.full_buf.width,image.full_buf.height);
			crop_rect.x = (disp_info.disp_rect.w -image.full_buf.width)/2;
			crop_rect.y = (disp_info.disp_rect.h -image.full_buf.height)/2;
			crop_rect.w = image.full_buf.width;
	        crop_rect.h = image.full_buf.height;
			printf("crop_rect.x = %d,crop_rect.y = %d\n",crop_rect.x,crop_rect.y);
			printf("crop_rect.w = %d,crop_rect.h = %d\n",crop_rect.w,crop_rect.h);
			image.opr.display->rect_set(&crop_rect);//设置显示区域
			crop_rect.x = 0;
			crop_rect.y = 0;
			crop_rect.w = image.full_buf.width;
	        crop_rect.h = image.full_buf.height;////设置图片裁剪区域
			int ret = image.opr.display->display(&image.full_buf, &crop_rect);
			printf("ret = %d\n",ret);
		}
		else
		{
			//printf("dst_next.w = %d,dst_next.h = %d\n",image.dst_next.width,image.dst_next.height);
			image_disp_rect_set(IMAGE_FULL_SCREEN);//设置显示区域
			crop_rect.x = 0;
			crop_rect.y = 0;
			crop_rect.w = image.dst_next.width;
	        crop_rect.h = image.dst_next.height;////设置图片裁剪区域
			ret = image.opr.display->display(&image.dst_next, &crop_rect);
			//printf("ret = %d\n",ret);
		}
	}
    else
    {
        if(image_scaler_decode(filename, &image.src) < 0){
                printf("image_decode failed\n");
                return -1;
        }

        //printf("src.w = %d,src.h = %d\n",image.src.width,image.src.height);

        image_disp_rect_set(IMAGE_FULL_SCREEN);//设置显示区域
        crop_rect.x = 0;
        crop_rect.y = 0;
        crop_rect.w = image.src.width;
        crop_rect.h = image.src.height;////设置图片裁剪区域
        ret = image.opr.display->display(&image.src, &crop_rect);
    }

	#if 0
	
	else if(mode == IMAGE_SHOW_MODE_THUMB)
	{
		if(image_show_before(mode) < 0)
		{
			printf("image_show_before failed\n");
			return -1;
		}
		crop_rect.x = 0;
		crop_rect.y = 0;
		crop_rect.w = image.dst_next.width;
        crop_rect.h = image.dst_next.height;
		printf("crop_rect.w = %d,crop_rect.h = %d\n",crop_rect.w,crop_rect.h);
		image.opr.display->display(&image.dst_next, &crop_rect);//设置显示区域和显示数据
	}
	else i(mode == IMAGE_SHOW_MODE_NORMAL){
		if(image.src.frame_cnt == 1){
			//image_show_single();
		}else{
			//image_show_multi(filename);
		}
	}
	#endif
	return 0;
}

int image_get_thumb(char const *filename, image_show_mode_t mode)
{
	return 0;
}

int image_get_width(void)
{
	return image.src.width_or;
}
int image_get_height(void)
{
	return image.src.height_or;
}

int image_display_opr_register(image_display_t *display)
{
	if (image.opr.display == NULL)
		image.opr.display = display;

	return 0;
}

int image_process_opr_register(image_process_t *process)
{
	if (image.opr.process == NULL)
		image.opr.process = process;

	return 0;
}

int image_init(void)
{
	printf("image_init !!!\n");
	int ret;
	image_disp_info_t disp_info;

	memset(&image, 0, sizeof(image));
	show_mode = IMAGE_FULL_SCREEN_SCLAER;
	ionHdle = (struct SunxiMemOpsS *)sunxifb_mem_get_fd();
	//ionHdle = GetMemAdapterOpsS();
	//ret = ionHdle->open();
	if (ionHdle == NULL) {
		printf("open ION error: %d\n", ret);
		goto ion_err;
	}

	image_display_opr_init();
	image_process_opr_init();

	ret = image.opr.display->init();
	if (ret != 0) {
		printf("%s: display init failed! ret = %d\n", __func__, ret);
		goto display_err;
	}
	ret = image.opr.process->init();
	if (ret != 0) {
		printf("%s: process init failed! ret = %d\n", __func__, ret);
		goto process_err;
	}
    #if 0
	image.opr.display->disp_info_get(&disp_info);
	image.dst_previous.vir_addr = ionHdle->palloc(disp_info.screen_width * disp_info.screen_height * 4);
	//printf("palloc finish vir_addr:%p\n",image.dst_previous.vir_addr);
	image.dst_previous.phy_addr = ionHdle->cpu_get_phyaddr(image.dst_previous.vir_addr);
	//printf("cpu_get_phyaddr finish:%p\n",image.dst_next.phy_addr);
	image.dst_previous.fd = ionHdle->get_bufferFd(image.dst_previous.vir_addr);
	//printf("get_bufferFd finish fd= %d\n",image.dst_previous.fd);
	image.dst_next.vir_addr = ionHdle->palloc(disp_info.screen_width * disp_info.screen_height * 4);
	//printf("palloc finish vir_addr:%p\n",image.dst_next.vir_addr);
	image.dst_next.phy_addr = ionHdle->cpu_get_phyaddr(image.dst_next.vir_addr);
	//printf("cpu_get_phyaddr finish:%p\n",image.dst_next.phy_addr);
	image.dst_next.fd = ionHdle->get_bufferFd(image.dst_next.vir_addr);

	image.full_buf.vir_addr = ionHdle->palloc(disp_info.screen_width * disp_info.screen_height * 4);
	//printf("palloc finish vir_addr:%p\n",image.full_buf.vir_addr);
	image.full_buf.phy_addr = ionHdle->cpu_get_phyaddr(image.full_buf.vir_addr);
	//printf("cpu_get_phyaddr finish:%p\n",image.full_buf.phy_addr);
	image.full_buf.fd = ionHdle->get_bufferFd(image.full_buf.vir_addr);
	//printf("get_bufferFd finish fd= %d\n",image.full_buf.fd);
    #endif
	return 0;
process_err:
	
display_err:
	image.opr.display->exit();
ion_err:
	return ret;
}

int image_exit(void)
{
	image.opr.display->exit();
	image.opr.process->exit();
    #if 0
	if (image.dst_next.vir_addr != NULL) {
		ionHdle->pfree(image.dst_next.vir_addr);
		image.dst_next.vir_addr = NULL;
	}
	if (image.src.vir_addr != NULL) {
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}
	if (image.dst_previous.vir_addr != NULL) {
		ionHdle->pfree(image.dst_previous.vir_addr);
		image.dst_previous.vir_addr = NULL;
	}
	if (image.full_buf.vir_addr != NULL) {
		ionHdle->pfree(image.full_buf.vir_addr);
		image.full_buf.vir_addr = NULL;
	}
    #endif
	printf("image_exit !!!\n");
	return 0;
}


int sunxi_image_init(void)
{
	int ret;
	//printf("sunxi_image_init !!!\n");
	memset(&image, 0, sizeof(image));
	show_mode = IMAGE_FULL_SCREEN_SCLAER;
	ionHdle = (struct SunxiMemOpsS *)sunxifb_mem_get_fd();
	//ionHdle = GetMemAdapterOpsS();
	//ret = ionHdle->open();
	if (ionHdle == NULL) {
		printf("open ION error: %d\n", ret);
		goto ion_err;
	}

	image_process_opr_init();
	ret = image.opr.process->init();
	if (ret != 0) {
		printf("%s: process init failed! ret = %d\n", __func__, ret);
		goto process_err;
	}
	return 0;
process_err:
ion_err:
	return ret;
}

int sunxi_image_exit(void)
{
	image.opr.process->exit();
	//printf("sunxi_image_exit !!!\n");
	return 0;
}

void *sunxi_image_decode(char *path)
{
    lv_img_dsc_t *imgdata = NULL;
    unsigned char *data = NULL;

	//printf("filename = %s\n",path);
    if (image_scaler_decode(path, &image.src) != 0) {
        printf("image_decode fail!\n");
        return NULL;
    }
	//printf("image.src.width=%d , image.src.height=%d\n",image.src.width,image.src.height);
    imgdata = (lv_img_dsc_t*)sunxifb_mem_alloc(sizeof(lv_img_dsc_t),"sunxi_image_decode");
    data =(unsigned char *)sunxifb_mem_alloc(image.src.width * image.src.height * BYTE_PER_PIXEL,"sunxi_image_decode");
    lv_memcpy(data,image.src.vir_addr,image.src.length);
	
	if (image.src.vir_addr != NULL) {
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}
    imgdata->header.w = image.src.width;
    imgdata->header.h = image.src.height;
    imgdata->header.always_zero = 0;
    if (BYTE_PER_PIXEL == 4) {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    } else {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    }
    imgdata->data_size = image.src.width * image.src.height * BYTE_PER_PIXEL;
    imgdata->data = data;
    return imgdata;
}

void *sunxi_image_decode_scaler(char *path,unsigned int scaler_w,unsigned int scaler_h)
{
    lv_img_dsc_t *imgdata = NULL;
    unsigned char *data = NULL;
	int ret =-1;

	//printf("filename = %s\n",path);
    if (image_scaler_decode(path, &image.src) != 0) {
        printf("image_decode fail!\n");
        return NULL;
    }
	//sunxi_image_scaler(&image.src,scaler_w,scaler_h);
	ret =sunxi_image_scaler_adapt(&image.src,scaler_w,scaler_h);
	if(ret <0)
	{
		print_zxf("sunxi_image_scaler_adapt fail!!!");
		 return NULL;
	}
	//printf("image.src.width=%d , image.src.height=%d\n",image.src.width,image.src.height);

    imgdata = (lv_img_dsc_t*)sunxifb_mem_alloc(sizeof(lv_img_dsc_t),"sunxi_image_decode");
    data =(unsigned char *)sunxifb_mem_alloc(image.src.width * image.src.height * BYTE_PER_PIXEL,"sunxi_image_decode");
    lv_memcpy(data,image.src.vir_addr,image.src.length);
	
	if (image.src.vir_addr != NULL) {
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}

    imgdata->header.w = image.src.width;
    imgdata->header.h = image.src.height;
    imgdata->header.always_zero = 0;
    if (BYTE_PER_PIXEL == 4) {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    } else {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    }
    imgdata->data_size = image.src.width * image.src.height * BYTE_PER_PIXEL;
    imgdata->data = data;

    return imgdata;
}

void *sunxi_image_decode_scaler_zoom(char *path,unsigned int zoom)
{
    lv_img_dsc_t *imgdata = NULL;
    unsigned char *data = NULL;

	//printf("filename = %s\n",path);
    if (image_scaler_decode(path, &image.src) != 0) {
        printf("image_decode fail!\n");
        return NULL;
    }
	sunxi_image_scaler_zoom(&image.src,&zoom);
	//printf("image.src.width=%d , image.src.height=%d\n",image.src.width,image.src.height);
	
    imgdata = (lv_img_dsc_t*)sunxifb_mem_alloc(sizeof(lv_img_dsc_t),"sunxi_image_decode");
    data =(unsigned char *)sunxifb_mem_alloc(image.src.width * image.src.height * BYTE_PER_PIXEL,"sunxi_image_decode");
    lv_memcpy(data,image.src.vir_addr,image.src.length);
	
	if (image.src.vir_addr != NULL) {
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}

    imgdata->header.w = image.src.width;
    imgdata->header.h = image.src.height;
    imgdata->header.always_zero = 0;
    if (BYTE_PER_PIXEL == 4) {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    } else {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    }
    imgdata->data_size = image.src.width * image.src.height * BYTE_PER_PIXEL;
    imgdata->data = data;

    return imgdata;
}

void *sunxi_image_decode_scaler_adapt(char *path, unsigned int w, unsigned int h)
{
	lv_img_dsc_t *imgdata = NULL;
    unsigned char *data = NULL;
	int ret =-1;

	//printf("filename = %s\n",path);
    if (image_scaler_decode(path, &image.src) != 0) {
        printf("image_decode fail!\n");
        return NULL;
    }
	ret =sunxi_image_scaler_adapt(&image.src,w,h);
	if(ret <0)
	{
		print_zxf("sunxi_image_scaler_adapt fail!!!");
		 return NULL;
	}
	//printf("image.src.width=%d , image.src.height=%d\n",image.src.width,image.src.height);
	
    imgdata = (lv_img_dsc_t*)sunxifb_mem_alloc(sizeof(lv_img_dsc_t),"sunxi_image_decode");
    data =(unsigned char *)sunxifb_mem_alloc(image.src.width * image.src.height * BYTE_PER_PIXEL,"sunxi_image_decode");
    lv_memcpy(data,image.src.vir_addr,image.src.length);
	
	if (image.src.vir_addr != NULL) {
		ionHdle->pfree(image.src.vir_addr);
		image.src.vir_addr = NULL;
	}

    imgdata->header.w = image.src.width;
    imgdata->header.h = image.src.height;
    imgdata->header.always_zero = 0;
    if (BYTE_PER_PIXEL == 4) {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    } else {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    }
    imgdata->data_size = image.src.width * image.src.height * BYTE_PER_PIXEL;
    imgdata->data = data;

    return imgdata;
}

int sunxi_image_free(void *buf)
{
    lv_img_dsc_t *imgdata = (lv_img_dsc_t*)buf;
    if (imgdata->data) {
        sunxifb_mem_free(&(imgdata->data),"sunxi_image_free");
    }
    if (imgdata) {
        sunxifb_mem_free(&imgdata,"sunxi_image_free");
    }
    return 0;
}
void *sunxi_image_create(unsigned int width,unsigned int height)
{
    lv_img_dsc_t *imgdata = NULL;
	unsigned char *data = NULL;

    imgdata = (lv_img_dsc_t*)sunxifb_mem_alloc(sizeof(lv_img_dsc_t),"sunxi_image_decode");
    data =(unsigned char *)sunxifb_mem_alloc(width * height * BYTE_PER_PIXEL,"sunxi_image_decode");

    imgdata->header.w = width;
    imgdata->header.h = height;
    imgdata->header.always_zero = 0;
    if (BYTE_PER_PIXEL == 4) {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    } else {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    }
    imgdata->data_size = width * height * BYTE_PER_PIXEL;
    imgdata->data = data;

    return imgdata;
}
int  image_decode_thumb(void *buf,char *path,unsigned int scaler_w,unsigned int scaler_h)
{
	void *listImage =NULL;
	lv_img_dsc_t *imageData = (lv_img_dsc_t*)buf;

	listImage = sunxi_image_decode_scaler(path, scaler_w, scaler_h);
	if(listImage !=NULL)
	{
		lv_img_dsc_t *Image = (lv_img_dsc_t*)listImage;
		imageData->header = Image->header;
		imageData->data_size = Image->data_size;
		lv_memset(imageData->data,0,imageData->data_size);
		lv_memcpy(imageData->data,Image->data,Image->data_size);
		sunxi_image_free(listImage);
		listImage = NULL;
		return 0;
	}
	return -1;
}

void* sunxi_image_standardized(image_buffer_t *buf,unsigned int scaler_w,unsigned int scaler_h)
{
	image_enh_t src_enh, dst_enh;
	image_buffer_t dst;
	int ret;
	lv_img_dsc_t *imgdata = NULL;
    unsigned char *data = NULL;
	
	sunxi_image_scaler_standardized(buf); 
	if(sunxi_image_scaler_adapt(buf,scaler_w,scaler_h)!=0) 
	{  
		printf("sunxi_image_scaler_adapt failed\n"); 
		return imgdata; 
	}
    imgdata = (lv_img_dsc_t*)sunxifb_mem_alloc(sizeof(lv_img_dsc_t),"sunxi_image_decode");
    data =(unsigned char *)sunxifb_mem_alloc(buf->width * buf->height * BYTE_PER_PIXEL,"sunxi_image_decode");
	lv_memcpy(data,buf->vir_addr,buf->length);
	if(buf->vir_addr)
	{
		ionHdle->pfree(buf->vir_addr);
		buf->vir_addr = NULL;
	}
	
    imgdata->header.w = buf->width;
    imgdata->header.h = buf->height;
    imgdata->header.always_zero = 0;
    if (BYTE_PER_PIXEL == 4) {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    } else {
        imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    }
    imgdata->data_size = buf->width * buf->height * BYTE_PER_PIXEL;
    imgdata->data = data;

    return imgdata;
}

void* sunxi_image_palloc(int size)
{
	return ionHdle->palloc(size);
}

void sunxi_image_pfree(void* ptr)
{
	ionHdle->pfree(ptr);
}

void* sunxi_image_get_phyaddr(void* viraddr)
{
	ionHdle->cpu_get_phyaddr(viraddr);
}

int sunxi_image_get_bufferFd(void* viraddr)
{
	return ionHdle->get_bufferFd(viraddr);
}

#endif
