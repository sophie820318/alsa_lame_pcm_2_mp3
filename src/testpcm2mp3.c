#include "ALSA_AUDIO_CAPTURE.h"
#include "Lame_pcm2mp3.h"
#include <signal.h>
#include "stdlib.h"
static int recording;
void stop_recording(int param)
{
    recording = 0;
}
int main()
{
    const char* output = "testpcm2mp3.mp3";
    FILE* mp3File = fopen(output,"wb");
    int samplerate = 44100;
    get_pcm_audio_t* get_pcm_audio =        (get_pcm_audio_t*)malloc(sizeof(get_pcm_audio_t));
    get_pcm_audio->frames = 32;
    get_pcm_audio->val = samplerate;
    get_pcm_audio->channels = 2;
    lame_t lame;
    char* buffer ;
    initLame(&lame,samplerate);
    /*初始化*/
    if(initAudioCapture(get_pcm_audio))
        return -1;
    const int PCM_BUFFER_SIZE = (get_pcm_audio->frames)*4;
	fprintf(stderr, "PCM_BUFFER_SIZE %d\n",PCM_BUFFER_SIZE );
    //enough buffer to hold pcm data
    char* pcm_buffer = (char *)malloc(PCM_BUFFER_SIZE*2);
   
    //const int MP3_BUFFER_SIZE  = PCM_BUFFER_SIZE;
    const int MP3_BUFFER_SIZE  = PCM_BUFFER_SIZE;
    fprintf(stderr, "MP3_BUFFER_SIZE %d\n",MP3_BUFFER_SIZE );
    //What's the relation ship between PCM_BUFFER_SIZE & MP3_BUFFER_SIZE?
    unsigned char* mp3_buffer=(unsigned char *)malloc(MP3_BUFFER_SIZE);
    recording = 1;
    int writesize = 0;
    int capturesize = 0;
    while(recording)
    {
	capturesize = captureAudio(get_pcm_audio,pcm_buffer);
        if(capturesize>0)
        {
            	writesize = encode_buffer_interleaved(&lame,(short int *)pcm_buffer,capturesize,mp3_buffer,MP3_BUFFER_SIZE);
		fprintf(stderr, "encode_buffer_interleaved%d\n",writesize);
		if(writesize>0)
			fwrite(mp3_buffer,writesize,1,mp3File);
        }
        if(signal(SIGINT,stop_recording) == SIG_ERR )
        {
        	fprintf(stderr,"signal failed\n");
        }
    }
    closeCaptureDevice(get_pcm_audio);
    writesize= encode_flush(&lame,mp3_buffer,MP3_BUFFER_SIZE);
    fwrite(mp3_buffer,writesize,1,mp3File);
    closelame(&lame);
    fclose(mp3File);
    return 0;
}
