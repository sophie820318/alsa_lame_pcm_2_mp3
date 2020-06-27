#include "ALSA_AUDIO_CAPTURE.h"

int initAudioCapture(get_pcm_audio_t *audio) {
    int rc;

    if (audio == NULL) {
        fprintf(stderr, "input audio is NULL\n");
        return -1;
    }

    // open PCM device for recording(captuer)
    rc = snd_pcm_open(&(audio->handle), "default", SND_PCM_STREAM_CAPTURE, 0);
    if (rc < 0) {
        fprintf(stderr, "unable to opren pcm device: %s\n", snd_strerror(rc));
        return -1;
    }

    // Allocate a hardware parameters object
    snd_pcm_hw_params_alloca(&(audio->params));

    // use default values 
    snd_pcm_hw_params_any(audio->handle, audio->params);

    // set the desired hw parameters
    // Interleaced mode
    snd_pcm_hw_params_set_access(audio->handle, audio->params, SND_PCM_ACCESS_RW_INTERLEAVED);

    // signed 16bit little-endian format
    snd_pcm_hw_params_set_format(audio->handle, audio->params, SND_PCM_FORMAT_S16_LE);

    // set double channels
    snd_pcm_hw_params_set_channels(audio->handle, audio->params, audio->channels);

    // 44100 bits/second sampliing rate(CD quality)
    snd_pcm_hw_params_set_rate_near(audio->handle, audio->params, &(audio->val), &(audio->dir));

    // set period size to 32 frames
    snd_pcm_hw_params_set_period_size_near(audio->handle, audio->params, &(audio->frames), &(audio->dir));

    // write the parameters to the device
    rc = snd_pcm_hw_params(audio->handle, audio->params);
    if (rc < 0) {
        fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
        return -1;
    }

    // use a buffer large enough to hold one period
    snd_pcm_hw_params_get_period_size(audio->params, &(audio->frames), &(audio->dir));

    // we want loop for 5s
    snd_pcm_hw_params_get_period_time(audio->params, &(audio->val), &(audio->dir));

    return 0;
}

int captureAudio(get_pcm_audio_t *audio, char *buffer) {
    int rc;

    if (audio == NULL || buffer == NULL)
    {
        fprintf(stderr, "input audio is NULL\n");
        return -1;
    }

    // get device data
    rc = snd_pcm_readi(audio->handle, buffer, audio->frames);
    if (rc == -EPIPE)
    {
        // EPIPE means overrun
        fprintf(stderr, "overrun occurred\n");
        snd_pcm_prepare(audio->handle);
        return -1;
    } 
    else if (rc < 0)
    {
        fprintf(stderr, "read error %s\n", snd_strerror(rc));
        return -1;
    } 
    else if (rc != (int) audio->frames) 
    {
        fprintf(stderr, "short read, raed %d frames\n", rc);
        return -1;
    }
    fprintf(stderr, "captureAudio %d frames\n", rc);
    return rc;
}

int closeCaptureDevice(get_pcm_audio_t *audio) {
    if (audio == NULL) {
        fprintf(stderr, "input audio is NULL\n");
        return -1;
    }
    if(audio->handle != NULL)
   {
      snd_pcm_drain(audio->handle);
      snd_pcm_close(audio->handle);
      return 0;
   }
    return 0;
}
