/*
 * Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
 * All rights reserved.
 *
 * File : Vpimage.h
 * Description : Vpimage
 * History :
 *
 */

#ifndef _VP_IMAGE_H_
# define _VP_IMAGE_H_

# include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* video_frame_image_scaler(char* in_file,unsigned int startframenum ,unsigned int width,unsigned int height);
int video_decode_thumb(void *buf,char *path,unsigned int startframe,unsigned int width,unsigned int height);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

