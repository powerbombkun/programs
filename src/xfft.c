#include "xfft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
} fft_window_t;

/**
 * @brief 回転子を取得する関数
 *
 * @param[in] bitsize   処理ビットサイズ
 *
 */
static double getW(int datasize);
/**
 * @brief 窓関数の係数を取得する関数
 *
 * @param[in] type 窓掛けを行う窓の種類
 * @param[in] w 回転子
 * @param[in] i インデックス
 *
 */
static double getSyntesisWindowRate(fft_window_t type,double w,int i);
/**
 * @brief FFTの前処理用の窓掛けを行う関数
 *
 * @param[in] type    窓掛けを行う窓の種類
 * @param[out] p_s     処理データ
 * @param[in] bitsize   処理ビットサイズ
 *
 */
static void syntesisWindowFFT(double* re,double* im,int32_t     bitsize,int f_inverse);

static double getW(int datasize)
{
    return (2.0 * PI / (double)datasize);
}

static double getSyntesisWindowRate(fft_window_t type,double w,int i)
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

static void syntesisWindowFFT(double* re,double* im,int32_t     bitsize,int f_inverse)
{
    int    i        = 0;
    int    datasize = 1 << bitsize;
    double w        = getW(datasize);
    double rate;

    if(!f_inverse)
    {
        for(i = 0;i < datasize;i++)
        {
            rate   = getSyntesisWindowRate(HANNING,w,i);
            re[i] *= rate;
            im[i] *= rate;
        }
        fft(re,im,bitsize);
    }
    else
    {
        ifft(re,im,bitsize);
        for(i = 0;i < datasize;i++)
        {
            rate   = getSyntesisWindowRate(HANNING,w,i);
            re[i] /= rate;
            im[i] /= rate;
        }
    }
}


void fftFrame(short* p_data,int n_data,double* re,double* im,int bitsize)
{
    int    i,j;
    int    datasize  = 1 << bitsize;
    int    framerate = datasize >> 1;
    int    n_loop    = n_data / framerate;
    short* p_ovl     = (short*)malloc(datasize*sizeof(short));
    memset(p_ovl,0,datasize*sizeof(short));
    for(i = 0;i < n_loop;i++)
    {
        memcpy(&p_ovl[0],&p_ovl[framerate],framerate);
        memcpy(&p_ovl[framerate],p_data,framerate);

        for(j = 0;j < datasize;j++)
        {
            re[j] = (double)p_ovl[j];
            im[j] = 0;
        }

        syntesisWindowFFT(re,im,bitsize,FALSE);

        p_data += framerate;
        re     += framerate;
        im     += framerate;
    }
    SAFE_FREE(p_ovl);
}

void ifftFrame(double* re,double* im,short* p_buffer,int n_buffer,int bitsize)
{
    int i,j;
    int datasize  = 1 << bitsize;
    int framerate = datasize >> 1;
    int n_loop    = n_buffer / framerate;
    for(i = 0;i < n_loop;i++)
    {
        syntesisWindowFFT(re,im,bitsize,TRUE);
        for(j = 0;j < framerate;j++)
        {
            *p_buffer++ = (short)re[j];
        }
        re += framerate;
        im += framerate;
    }
}



