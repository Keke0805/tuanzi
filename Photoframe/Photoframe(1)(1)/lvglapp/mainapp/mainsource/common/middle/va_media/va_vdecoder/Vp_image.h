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

# include <openssl/e_os2.h>
# include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* video_frame_image_scaler(char* in_file,unsigned int startframenum ,unsigned int width,unsigned int height);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

