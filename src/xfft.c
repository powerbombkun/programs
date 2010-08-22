#include "xfft.h"
#include <stdlib.h>
#include "fft.h"

void xfft(int16_t* p_data,int32_t n_data,double* re,double* im,int32_t     bitsize)
{
    int i;
    int j;
    int32_t datasize = 1 << bitsize;
    int32_t n_loop   = n_data / datasize;
    for(i = 0;i < n_loop;i++)
    {
        for(j = 0;j < datasize;j++)
        {
            re[j] = (double)p_data[j];
            im[j] = 0;
        }
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
            re         += datasize;
            im         += datasize;
        }
        ret = SUCCESS;
    }
    SAFE_FREE(re);
    SAFE_FREE(im);
    return ret;
}
