#ifndef  LAME_PCM2MP3_H
#define  LAME_PCM2MP3_H

#include "../3rdparty/lame/include/lame/lame.h"

//以C的形式定义接口
#ifdef __cplusplus
extern "C"{
#endif


int initLame(lame_t* lame,int samplerate);
/*返回值是写入的数据*/
int encode_buffer_interleaved(lame_t* lame,short int * pcm_buffer,int readsize,unsigned char * mp3_buffer,const int mp3_buffer_size);
/*返回值是写入的数据*/
int encode_flush(lame_t* lame,unsigned char * mp3_buffer,const int mp3_buffer_size);

int closelame(lame_t* lame);

#ifdef __cplusplus
}
#endif

#endif //LAME_PCM2MP3_H
