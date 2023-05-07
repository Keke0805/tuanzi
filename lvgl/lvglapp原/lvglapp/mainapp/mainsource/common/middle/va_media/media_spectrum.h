#ifndef _MEDIA_SPECTRUM_H_
#define _MEDIA_SPECTRUM_H_
#include "player_int.h"
#ifdef _UCHIP_T113
#include "speex/speex_preprocess.h"
#endif

typedef struct spectrum_t{
    #ifdef _UCHIP_T113
	SpeexPreprocessState *speex_spectrum;
	AudioPcmData audio_info;
    #endif
	unsigned char *pdata;
	int ps_size;
	int *ps_buffer;
	int init_flag;

	pthread_mutex_t	spectrum_mutex;
}spectrum_t;

void media_spectrum_destroy(void);
#ifdef _UCHIP_T113
void media_spectrum_init(AudioPcmData *audio_info);
#endif
int  *media_get_spectrum(void);
int media_get_spectrum_size(void);

#endif
