#include "xfft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

static void fft_window(double* p_s,int bitsize);

static void fft_obj_frame(short* p_data,double* re,double* im,short* p_ovl,int bitsize);

static void fft_window(double* p_s,int bitsize)
{
    int    i        = 0;
    int    datasize = 1 << bitsize;
    double a        = 2.0 * PI / datasize;
    for(i = 0;i < datasize;i++)
    {
        double rate  = 0.5 - (0.5 * (double)cos(a*i));
        p_s[i]      *= rate;
    }
}


static void fft_obj_frame(short* p_data,double* re,double* im,short* p_ovl,int bitsize)
{
    int datasize  = 1 << bitsize;
    int framerate = datasize >> 1;
    int i;
    /** 後ろ半分を前半分へコピー */
    memcpy(&p_ovl[0],&p_ovl[framerate],framerate);
    /** 入力データを後半半分へコピー */
    memcpy(&p_ovl[framerate],p_data,framerate);

    for(i = 0;i < datasize;i++)
    {
        re[i] = (double)p_ovl[i];
        im[i] = 0;
    }

    fft_window(re,bitsize);
    fft(re,im,bitsize);
}

void fft_frame(short* p_data,int n_data,double* re,double* im,int bitsize)
{
    int     i;
    int     datasize  = 1 << bitsize;
    int     framerate = datasize >> 1;
    int     n_loop    = n_data / framerate;
    short*  p_ovl = (short*)malloc(datasize);
    memset(p_ovl,0,datasize*sizeof(short));
    for(i = 0;i < n_loop;i++)
    {
        fft_obj_frame(p_data,re,im,p_ovl,bitsize);
        p_data += framerate;
        re     += framerate;
        im     += framerate;
    }
    SAFE_FREE(p_ovl);
}

void ifft_frame(double* re,double* im,short* p_buffer,int n_buffer,int bitsize)
{
    int     i,j;
    int     datasize  = 1 << bitsize;
    int     framerate = datasize >> 1;
    int     n_loop    = n_data / framerate;
    for(i = 0;i < n_loop;i++)
    {
        ifft(re,im,bitsize);
        for(j = 0;j < framerate;j++)
        {
            *p_buffer++ = (short)re[j];
        }
        re     += framerate;
        im     += framerate;
    }
}

