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
 * @param[in] type    窓掛けを行う窓の種類
 * @param[out] p_s     処理データ
 * @param[in] bitsize   処理ビットサイズ
 *
 */
static void windowFFT(double* re,double* im,int32_t     bitsize,BOOL f_inverse);

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

static void windowFFT(double* re,double* im,int32_t     bitsize,BOOL f_inverse)
{
    int32_t i        = 0;
    int32_t datasize = 1 << bitsize;
    double  w        = getW(datasize);
    double  rate;

    if(!f_inverse)
    {
        fft(re,im,bitsize);
    }
    for(i = 0;i < datasize;i++)
    {
        rate   = getWindowRate(HANNING,w,i);
        re[i] *= rate;
        im[i] *= rate;
    }
    if(f_inverse)
    {
        ifft(re,im,bitsize);
    }
}


void fftFrame(int16_t* p_data,int32_t n_data,double* re,double* im,int32_t bitsize)
{
    int32_t   i;
    int32_t   j;
    int32_t   datasize  = 1 << bitsize;
    int32_t   framerate = datasize >> 1;
    int32_t   n_loop    = n_data / framerate;
    int16_t* p_ovl     = (int16_t*)calloc(datasize,sizeof(int16_t));
    double*   p_ovl_re  = (double*)calloc(datasize,sizeof(double));
    double*   p_ovl_im  = (double*)calloc(datasize,sizeof(double));

    for(i = 0;i < n_loop;i++)
    {
        /** 時間軸上でのオーバラップ処理 */
        memcpy(&p_ovl[0],&p_ovl[framerate],framerate*sizeof(int16_t)); /** 後ろ半分のデータを前へコピー */
        memcpy(&p_ovl[framerate],p_data,framerate*sizeof(int16_t)); /** 新規のデータを後ろ半分へコピー */
        for(j = 0;j < datasize;j++)
        {
            re[j] = (double)p_ovl[j];
            im[j] = 0;
        }
        /** 窓掛け & FFT処理 */
        windowFFT(re,im,bitsize,FALSE);
        /** 周波数軸上でのオーバラップ処理 */
        for(j = 0;j < framerate;j++)
        {
            /** 前半半分に前回処理時の後半半分を加算 */
            re[j] += p_ovl_re[j];
            im[j] += p_ovl_im[j];
        }
        /** 後半半分をバッファへコピー */
        memcpy(p_ovl_re,&re[framerate],framerate*sizeof(double));
        memcpy(p_ovl_im,&im[framerate],framerate*sizeof(double));

        p_data += framerate;
        re     += framerate;
        im     += framerate;
    }
    SAFE_FREE(p_ovl);
    SAFE_FREE(p_ovl_re);
    SAFE_FREE(p_ovl_im);
}

void ifftFrame(double* re,double* im,int16_t* p_buffer,int32_t n_buffer,int32_t bitsize)
{
    int32_t i;
    int32_t datasize  = 1 << bitsize;
    int32_t n_loop    = n_buffer / datasize;
    for(i = 0;i < n_loop;i++)
    {
        windowFFT(re,im,bitsize,TRUE);
        for(i = 0;i < datasize;i++)
        {
            *p_buffer++ = (int16_t)re[i];
        }
        re += datasize;
        im += datasize;
    }
}



