#include "wave.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "common.h"
#include "macro.h"

#define DEF_WAVE_HDR_SIZE  44
#define DEF_FMT_CHUNK_SIZE 16
#define FMT_ID_PCM         0x01
/**
 * @struct wave_t
 * @brief  WAVEデータ管理用構造体
 */
typedef struct
{
    int16_t ch;                      /*  */
    int16_t bitspersample;           /*  */
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
static int32_t read_file_wave_hdr(const char* file,wave_t* p_wave);
/**
 * @brief WAVEヘッダーのファイルポインタを進めます
 *
 * @param[in] p_fp FILEポインタのポインタ
 * @param[out] p_wave wave_t型構造体のポインタ
 *
 * @retval SUCCESS 成功
 * @retval FAILED  失敗
 */
static int32_t skip_wave_hdr(FILE** p_fp,wave_t* p_wave);
/**
 * @brief WAVEヘッダーを書き込みます
 *
 * @param[in] p_fp FILEポインタのポインタ
 * @param[in] wave wave_t型構造体のデータ
 *
 * @retval
 */
static int32_t write_wave_hdr(FILE** p_fp,wave_t wave);

static int32_t set_wave_hdr(uint8_t* p_buffer,int32_t n_buffer,wave_t wave);

static int32_t read_file_wave_hdr(const char* file,wave_t* p_wave)
{
    FILE*   fp  = NULL;
    int32_t ret = FAILURE;

    fp = fopen(file,"rb");
    if(fp != NULL)
    {
        ret = skip_wave_hdr(&fp,p_wave);
        fclose(fp);
    }
    return ret;
}

static int32_t skip_wave_hdr(FILE** p_fp,wave_t* p_wave)
{
    int32_t ret        = FAILURE;
    char       buff[5] = {0};

    if((*p_fp != NULL) && (p_wave != NULL))
    {
        fread(buff,sizeof(char),4,*p_fp);
        if(strncmp(buff,"RIFF",sizeof("RIFF")) == 0)
        {
            fread(buff,sizeof(char),4,*p_fp);
            fread(buff,sizeof(char),4,*p_fp);
            if(strncmp(buff,"WAVE",sizeof("WAVE")) == 0)
            {
                fread(buff,sizeof(char),4,*p_fp);
                if(strncmp(buff,"fmt ",sizeof("fmt ")) == 0)
                {
                    int32_t fmtsize;
                    char* p_fmt;
                    fread(&fmtsize,sizeof(int32_t),1,*p_fp);

                    p_fmt                 = (char*)x_malloc(fmtsize);
                    fread(p_fmt,sizeof(char),fmtsize,*p_fp);
                    p_wave->ch            = *(int16_t*)&p_fmt[2];
                    p_wave->samplingrate  = *(int32_t*)&p_fmt[4];
                    p_wave->bitspersample = *(int16_t*)&p_fmt[14];
                    SAFE_FREE(p_fmt);

                    fread(buff,sizeof(char),4,*p_fp);
                    if(strncmp(buff,"data",sizeof("data")) == 0)
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


static int32_t write_wave_hdr(FILE** p_fp,wave_t wave)
{
    int32_t ret = FAILURE;
    if(*p_fp != NULL)
    {
        uint8_t hdr[DEF_WAVE_HDR_SIZE];
        ret = set_wave_hdr(hdr,sizeof(hdr),wave);
        fwrite(hdr,sizeof(hdr),1,*p_fp);
    }
    return ret;
}

static int32_t set_wave_hdr(uint8_t* p_buffer,int32_t n_buffer,wave_t wave)
{
    int32_t ret = FAILURE;
    if(DEF_WAVE_HDR_SIZE <= n_buffer)
    {
        memcpy(p_buffer,"RIFF",sizeof("RIFF"));
        *(int32_t*)&p_buffer[4]  = wave.datasize + DEF_WAVE_HDR_SIZE - 8;
        memcpy(&p_buffer[8],"WAVE",sizeof("WAVE"));
        memcpy(&p_buffer[12],"fmt ",sizeof("fmt "));
        *(int32_t*)&p_buffer[16] = DEF_FMT_CHUNK_SIZE;
        *(int16_t*)&p_buffer[20] = FMT_ID_PCM;
        *(int16_t*)&p_buffer[22] = wave.ch;
        *(int32_t*)&p_buffer[24] = wave.samplingrate;
        *(int32_t*)&p_buffer[28] = wave.samplingrate * wave.ch;
        *(int16_t*)&p_buffer[32] = sizeof(int16_t);
        *(int16_t*)&p_buffer[34] = wave.bitspersample;
        memcpy(&p_buffer[36],"data",sizeof("data"));
        *(int32_t*)&p_buffer[40] = wave.datasize;
        ret                      = SUCCESS;
    }
    return ret;
}

int32_t pcm2wav(const char* pcm_file,
                const char* wav_file,
                int16_t     ch,
                int16_t     bitspersample,
                int32_t     samplingrate)
{
    int32_t ret        = FAILURE;
    FILE*   fp_in      = fopen(pcm_file,"rb");
    wave_t  wave;
    wave.ch            = ch;
    wave.bitspersample = bitspersample;
    wave.samplingrate  = samplingrate;
    wave.datasize      = get_file_size(pcm_file);

    if(fp_in != NULL)
    {
        FILE* fp_out = fopen(wav_file,"wb");
        if(fp_out != NULL)
        {
            unsigned char* p_buffer = (unsigned char*)x_malloc(wave.datasize);
            if(p_buffer != NULL)
            {
                fread(p_buffer,wave.datasize,sizeof(unsigned char),fp_in);
                ret = write_wave_hdr(&fp_out,wave);
                if(ret == SUCCESS)
                {
                    fwrite(p_buffer,wave.datasize,sizeof(unsigned char),fp_out);
                }
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
                int16_t*    bitspersample,
                int32_t*    samplingrate)
{
    int32_t ret   = FAILURE;
    FILE*   fp_in = fopen(wav_file,"rb");
    if(fp_in != NULL)
    {
        FILE* fp_out = fopen(pcm_file,"wb");
        if(fp_out != NULL)
        {
            wave_t  wave;
            if(skip_wave_hdr(&fp_in,&wave) == SUCCESS)
            {
                unsigned char* p_buffer = (unsigned char*)x_malloc(wave.datasize);
                if(p_buffer != NULL)
                {
                    fread(p_buffer,wave.datasize,sizeof(unsigned char),fp_in);
                    fwrite(p_buffer,wave.datasize,sizeof(unsigned char),fp_out);
                    SAFE_FREE(p_buffer);
                    fclose(fp_out);
                    *ch            = wave.ch;
                    *bitspersample = wave.bitspersample;
                    *samplingrate  = wave.samplingrate;
                    ret = SUCCESS;
                }
            }
        }
        fclose(fp_in);
    }
    return ret;
}
