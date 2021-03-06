#include "xfft.h"
#include <stdlib.h>
#include <math.h>
#include "fft.h"
#include "macro.h"
#include "common.h"

/**
 * @typedef fft_window_t型enum
 * @todo 後でHOGE
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
static void window(double* re,double* im,int32_t     bitsize,BOOL f_inverse);

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

static void window(double* re,double* im,int32_t     bitsize,BOOL f_inverse)
{
    int32_t i        = 0;
    int32_t datasize = 1 << bitsize;
    double  w        = getW(datasize);

    if(!f_inverse)
    {
        for(i = 0;i < datasize;i++)
        {
            double rate   = getWindowRate(HANNING,w,i);
            re[i] *= rate;
            im[i] *= rate;
        }
    }
    else
    {
        for(i = 0;i < datasize;i++)
        {
            double rate   = getWindowRate(HANNING,w,i);
            re[i] /= rate;
            im[i] /= rate;
        }
    }
}


void xfft(int16_t* p_data,int32_t n_data,double* re,double* im,int32_t     bitsize)
{
    int     i;
    int     j;
    int32_t datasize     = 1 << bitsize;
    int32_t n_loop       = n_data / datasize;
    for(i = 0;i < n_loop;i++)
    {
        for(j = 0;j < datasize;j++)
        {
            re[j] = (double)p_data[j];
            im[j] = 0;
        }
        window(re,im,bitsize,FALSE);
        fft(re,im,bitsize);
        p_data += datasize;
        re     += datasize;
        im     += datasize;
    }
}

void xifft(double* re,double* im,int16_t* p_buffer,int32_t n_buffer,int32_t     bitsize)
{
    int i;
    int j;
    int32_t datasize = 1 << bitsize;
    int32_t n_loop   = n_buffer / datasize;
    for(i = 0;i < n_loop;i++)
    {
        window(re,im,bitsize,TRUE);
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
    int32_t ret      = FAILURE;
    double* re       = (double*)x_malloc(n_data * sizeof(double));
    double* im       = (double*)x_malloc(n_data * sizeof(double));
    if((re != NULL) && (im != NULL))
    {
        xfft(p_data,n_data,re,im,bitsize);
        spectrum(re,im,n_data,p_spectrum);
        ret = SUCCESS;
    }
    SAFE_FREE(re);
    SAFE_FREE(im);
    return ret;
}
