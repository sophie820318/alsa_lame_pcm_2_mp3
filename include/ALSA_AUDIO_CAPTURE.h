#ifndef    _ALSA_AUDIO_CAPTURE_H
#define    _ALSA_AUDIO_CAPTURE_H

#define LSA_PCM_NEW_HW_PARAMS_API
#include <alsa/asoundlib.h>

#ifdef __cplusplus
extern "C"{
#endif

    typedef struct _get_pcm_audio get_pcm_audio_t;
    struct _get_pcm_audio
     {
         int dir;
         int channels;
         snd_pcm_t *handle;
         snd_pcm_hw_params_t *params;
         unsigned int val;
         snd_pcm_uframes_t frames;
     };
     /* 初始化参数列表*/
     int initAudioCapture(get_pcm_audio_t *audio);
     /* 采集音频*/
     int captureAudio(get_pcm_audio_t *audio, char *buffer);
    /* 关闭音频*/
     int closeCaptureDevice(get_pcm_audio_t *audio);
#ifdef __cplusplus
}
#endif

#endif //_ALSA_AUDIO_CAPTURE_API

