#ifndef __PNG_DECODE_H__
#define __PNG_DECODE_H__
#ifdef __cplusplus
extern "C" {
#endif
int png_decode(char *filename,void *output_buf,unsigned int *width,unsigned int *height,int *comp);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
