#include "wave.h"
#include <stdlib.h>
#include <string.h>
#include "util.h"

typedef struct{
    int32_t fmtsize;                 /*  */
    int16_t ch;                      /*  */
    int16_t type;                    /*  */
    int32_t bitspersample;           /*  */
    int32_t samplingrate;            /*  */
    int32_t datasize;                /*  */
}wave_t;
/**
 * @brief ファイルからWAVEヘッダー情報を読み込みます
 *
 * @param[in] file 入力ファイル
 * @param[out] p_wave wave_t型構造体のポインタ
 *
 * @retval
 */
static int32_t readFileWaveHdr(const char* file,wave_t* p_wave);
/**
 * @brief WAVEヘッダーのファイルポインタを進めます
 *
 * @param[in] p_fp FILEポインタのポインタ
 * @param[out] p_wave wave_t型構造体のポインタ
 *
 * @retval SUCCESS 成功
 * @retval FAILED  失敗
 */
static int32_t skipWaveHdr(FILE** p_fp,wave_t* p_wave);
/**
 * @brief WAVEヘッダーを書き込みます
 *
 * @param[in] p_fp FILEポインタのポインタ
 * @param[in] wave wave_t型構造体のデータ
 *
 * @retval
 */
static int32_t writeWaveHdr(FILE** p_fp,wave_t wave);


static int32_t readFileWaveHdr(const char* file,wave_t* p_wave)
{
    FILE*   fp  = NULL;
    int32_t ret = FAILURE;

    fp = fopen(file,"rb");
    if(fp != NULL)
    {
        ret = skipWaveHdr(&fp,p_wave);
        fclose(fp);
    }
    return ret;
}

static int32_t skipWaveHdr(FILE** p_fp,wave_t* p_wave)
{
    int32_t ret        = FAILURE;
    char       buff[5] = {0};

    if((*p_fp != NULL) && (p_wave != NULL))
    {
        fread(buff,sizeof(char),4,*p_fp);
        if(strncmp(buff,"RIFF",4) == 0)
        {
            fread(buff,sizeof(char),4,*p_fp);
            fread(buff,sizeof(char),4,*p_fp);
            if(strncmp(buff,"WAVE",4) == 0)
            {
                fread(buff,sizeof(char),4,*p_fp);
                if(strncmp(buff,"fmt ",4) == 0)
                {
                    char* p_fmt;
                    fread(&p_wave->fmtsize,sizeof(int32_t),1,*p_fp);

                    p_fmt                 = (char*)malloc(p_wave->fmtsize);
                    fread(p_fmt,sizeof(char),p_wave->fmtsize,*p_fp);
                    p_wave->ch            = *(int16_t*)&p_fmt[2];
                    p_wave->samplingrate  = *(int32_t*)&p_fmt[4];
                    p_wave->bitspersample = *(int16_t*)&p_fmt[14];
                    SAFE_FREE(p_fmt);

                    fread(buff,sizeof(char),4,*p_fp);
                    if(strncmp(buff,"data",4) == 0)
                    {
                        fread(&p_wave->datasize,sizeof(int32_t),1,*p_fp);
                        ret = SUCCESS;
                    }
                }
            }
        }
    }
    return ret;
}


static int32_t writeWaveHdr(FILE** p_fp,wave_t wave)
{
    int32_t ret = FAILURE;
    if(*p_fp != NULL)
    {
        int32_t i32_buff = 0;
        int16_t i16_buff = 0;

        fwrite("RIFF",sizeof(char),sizeof("RIFF"),*p_fp);
        i32_buff = wave.datasize + 44 - 8;
        fwrite("WAVE",sizeof(char),sizeof("WAVE"),*p_fp);
        fwrite("fmt ",sizeof(char),sizeof("fmt "),*p_fp);
        fwrite(&wave.fmtsize,sizeof(int32_t),1,*p_fp);
        fwrite(&wave.type,sizeof(int16_t),1,*p_fp);
        fwrite(&wave.ch,sizeof(int16_t),1,*p_fp);
        fwrite(&wave.samplingrate,sizeof(int32_t),1,*p_fp);
        i32_buff = wave.samplingrate * wave.ch;
        fwrite(&i32_buff,sizeof(int32_t),1,*p_fp);
        i16_buff = sizeof(int16_t);
        fwrite(&i16_buff,sizeof(int16_t),1,*p_fp);
        fwrite(&wave.bitspersample,sizeof(int16_t),1,*p_fp);
        fwrite("data",sizeof(char),sizeof("data"),*p_fp);
        fwrite(&wave.datasize,sizeof(int32_t),1,*p_fp);

        ret = SUCCESS;
    }
    return ret;
}

int32_t pcm2wav(const char* pcm_file,
                const char* wav_file,
                int16_t     ch,
                int32_t     bitspersample,
                int32_t     samplingrate)
{
    int32_t ret        = FAILURE;
    FILE*   fp_in      = fopen(pcm_file,"rb");
    wave_t  wave;
    wave.fmtsize       = 16;
    wave.ch            = ch;
    wave.type          = 1;
    wave.bitspersample = bitspersample;
    wave.samplingrate  = samplingrate;
    wave.datasize      = getFileSize(pcm_file);

    if(fp_in != NULL)
    {
        FILE* fp_out = fopen(wav_file,"wb");
        if(fp_out != NULL)
        {
            unsigned char* p_buffer = (unsigned char*)malloc(wave.datasize);
            if(p_buffer != NULL)
            {
                fread(p_buffer,wave.datasize,sizeof(unsigned char),fp_in);
                ret = writeWaveHdr(&fp_out,wave);
                fwrite(p_buffer,wave.datasize,sizeof(unsigned char),fp_out);
                SAFE_FREE(p_buffer);
                fclose(fp_out);
            }
        }
        fclose(fp_in);
    }
    return ret;
}

int32_t wav2pcm(const char* wav_file,
                const char* pcm_file,
                int16_t*    ch,
                int32_t*    bitspersample,
                int32_t*    samplingrate)
{
    int32_t ret   = FAILURE;
    FILE*   fp_in = fopen(wav_file,"rb");
    wave_t  wave;
    if(fp_in != NULL)
    {
        FILE* fp_out = fopen(pcm_file,"wb");
        if(fp_out != NULL)
        {
            ret                     = skipWaveHdr(&fp_in,&wave);
            unsigned char* p_buffer = (unsigned char*)malloc(wave.datasize);
            if(p_buffer != NULL)
            {
                fread(p_buffer,wave.datasize,sizeof(unsigned char),fp_in);
                fwrite(p_buffer,wave.datasize,sizeof(unsigned char),fp_out);
                SAFE_FREE(p_buffer);
                fclose(fp_out);
                *ch            = wave.ch;
                *bitspersample = wave.bitspersample;
                *samplingrate  = wave.samplingrate;
            }
        }
        fclose(fp_in);
    }
    return ret;
}
