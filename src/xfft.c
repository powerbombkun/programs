#include "xfft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

typedef enum
{
    HAMMING,                    /** ハミング窓 */
    BLACKMAN,                   /** ブラックマン窓 */
    HANNING,                    /** ハニング窓 */
} fft_window_t;

/**
 * @brief 回転子を取得します
 *
 * @param[in] bitsize   処理ビットサイズ
 *
 */
static double getW(int datasize);
/**
 * @brief FFTの前処理用の窓掛けを行う関数
 *
 * @param[in] type    窓掛けを行う窓の種類
 * @param[out] p_s     処理データ
 * @param[in] bitsize   処理ビットサイズ
 *
 */
static void fftWindow(fft_window_t type,double* p_s,int datasize);

static void fftProcess(short* p_data,double* re,double* im,int32_t     bitsize);

static double getW(int datasize)
{
    return (2.0 * PI / (double)datasize);
}

static void fftWindow(fft_window_t type,double* p_s,int datasize)
{
    int    i = 0;
    double w = getW(datasize);
    for(i = 0;i < datasize;i++)
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
        p_s[i] *= rate;
    }
}

static void fftProcess(short* p_data,double* re,double* im,int32_t     bitsize)
{
    int i;
    int datasize = 1 << bitsize;
    for(i = 0;i < datasize;i++)
    {
        re[i] = (double)p_data[i];
        im[i] = 0;
    }
    fftWindow(HANNING,re,datasize);
    fft(re,im,bitsize);
}


void fftFrame(short* p_data,int n_data,double* re,double* im,int bitsize)
{
    int    i;
    int    datasize  = 1 << bitsize;
    int    framerate = datasize >> 1;
    int    n_loop    = n_data / framerate;
    short* p_ovl     = (short*)malloc(datasize*sizeof(short));
    memset(p_ovl,0,datasize*sizeof(short));
    for(i = 0;i < n_loop;i++)
    {
        memcpy(&p_ovl[0],&p_ovl[framerate],framerate);
        memcpy(&p_ovl[framerate],p_data,framerate);

        fftProcess(p_ovl,re,im,bitsize);

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
        ifft(re,im,bitsize);
        for(j = 0;j < framerate;j++)
        {
            *p_buffer++ = (short)re[j];
        }
        re += framerate;
        im += framerate;
    }
}



