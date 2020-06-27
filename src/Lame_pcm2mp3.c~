#include "Lame_pcm2mp3.h"


int initLame(lame_t* lame,int samplerate)
{
    *lame= lame_init();
    lame_set_in_samplerate(*lame,samplerate);
    lame_set_VBR(*lame,vbr_default);
    return lame_init_params(*lame);
}

/*返回值是写入的数据*/
int encode_flush(lame_t* lame,unsigned char * mp3_buffer,const int mp3_buffer_size)
{
    return  lame_encode_flush(*lame,mp3_buffer,mp3_buffer_size);
}

/*返回值是写入的数据*/
int encode_buffer_interleaved(lame_t* lame,short int * pcm_buffer,int readsize,unsigned char * mp3_buffer,const int mp3_buffer_size)
{
    return lame_encode_buffer_interleaved(*lame,pcm_buffer,readsize,mp3_buffer,mp3_buffer_size);
}   

int closelame(lame_t* lame)
{
    return lame_close(*lame);
}

