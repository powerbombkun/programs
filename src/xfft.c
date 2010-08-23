#include "xfft.h"
#include <stdlib.h>
#include <math.h>
#include "fft.h"

/**
 * @typedef fft_window_t型enum
 *
 * @brief 窓掛け用の窓のID
 */
typedef enum
{
    HAMMING,                    /** ハミング窓 */
    BLACKMAN,                   /** ブラックマン窓 */
    HANNING,                    /** ハニング窓 */
    NONE,
} fft_window_t;
/**
 * @brief 回転子を取得する関数
 *
 * @param[in] bitsize   処理ビットサイズ
 *
 */
static double getW(int32_t datasize);
/**
 * @brief 窓関数の係数を取得する関数
 *
 * @param[in] type 窓掛けを行う窓の種類
 * @param[in] w 回転子
 * @param[in] i インデックス
 *
 */
static double getWindowRate(fft_window_t type,double w,int32_t i);
/**
 * @brief FFTの前処理用の窓掛けを行う関数
 *
 * @param[in] bitsize   処理ビットサイズ
 *
 */
static void window(double* re,double* im,int32_t     bitsize);

static double getW(int32_t datasize)
{
    return (2.0 * PI / (double)datasize);
}

static double getWindowRate(fft_window_t type,double w,int32_t i)
{
    double rate;
    if(type == HAMMING)
    {
        rate = 0.54 - (0.46 * (double)cos(w*i));
    }
    else if(type == BLACKMAN)
    {
        rate = 0.42 - (0.5 * (double)cos(w*i)) + (0.08 * (double)cos(2.0*w*i));
    }
    else if(type == HANNING)
    {
        rate = 0.5 - (0.5 * (double)cos(w*i));
    }
    else
    {
        rate = 1.0;
    }
    return rate;
}

static void window(double* re,double* im,int32_t     bitsize)
{
    int32_t i        = 0;
    int32_t datasize = 1 << bitsize;
    double  w        = getW(datasize);

    for(i = 0;i < datasize;i++)
    {
        double rate   = getWindowRate(HANNING,w,i);
        re[i] *= rate;
        im[i] *= rate;
    }
}


int32_t xfft(int16_t* p_data,int32_t n_data,double* re,double* im,int32_t     bitsize)
{
    int     i;
    int     j;
    int32_t ret          = FAILURE;
    double  overlap_rate = 0.5;
    int32_t datasize     = 1 << bitsize;
    int32_t framesize    = datasize * overlap_rate;
    int32_t n_loop       = (n_data / framesize) - 1;
    double* re_buf       = (double*)calloc(framesize,sizeof(double));
    double* im_buf       = (double*)calloc(framesize,sizeof(double));
    if((re != NULL) && (im != NULL))
    {
        for(i = 0;i < n_loop;i++)
        {
            for(j = 0;j < datasize;j++)
            {
                re[j] = (double)p_data[j];
                im[j] = 0;
            }
            window(re,im,bitsize);
            fft(re,im,bitsize);

            for(j = 0;j < framesize;j++)
            {
                re[j]     += re_buf[j];
                im[j]     += im_buf[j];
                re_buf[j]  = re[j+framesize];
                im_buf[j]  = im[j+framesize];
            }

            p_data += framesize;
            re     += framesize;
            im     += framesize;
        }
        ret = SUCCESS;
    }
    SAFE_FREE(re_buf);
    SAFE_FREE(im_buf);
    return ret;
}

void xifft(double* re,double* im,int16_t* p_buffer,int32_t n_buffer,int32_t     bitsize)
{
    int i;
    int j;
    int32_t datasize = 1 << bitsize;
    int32_t n_loop   = n_buffer / datasize;
    for(i = 0;i < n_loop;i++)
    {
        ifft(re,im,bitsize);
        for(j = 0;j < datasize;j++)
        {
            p_buffer[j] = (int16_t)re[j];
        }
        p_buffer += datasize;
        re       += datasize;
        im       += datasize;
    }
}

int32_t xspectrum(int16_t* p_data,int32_t n_data,double* p_spectrum,int32_t     bitsize)
{
    int     i;
    int     j;
    int32_t ret      = FAILURE;
    int32_t datasize = 1 << bitsize;
    double* re       = (double*)malloc(datasize * sizeof(double));
    double* im       = (double*)malloc(datasize * sizeof(double));
    if((re != NULL) && (im != NULL))
    {
        int     n_loop   = n_data / datasize;
        for(i = 0;i < n_loop;i++)
        {
            for(j = 0;j < datasize;j++)
            {
                re[j] = (double)p_data[j];
                im[j] = 0;
            }
            fft(re,im,bitsize);
            spectrum(re,im,datasize,p_spectrum);

            p_spectrum += datasize;
            p_data     += datasize;
        }
        ret = SUCCESS;
    }
    SAFE_FREE(re);
    SAFE_FREE(im);
    return ret;
}
