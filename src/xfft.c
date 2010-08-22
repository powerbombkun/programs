#include "xfft.h"
#include "fft.h"

void xfft(int16_t* p_data,int32_t n_data,double* re,double* im,int32_t     bitsize)
{
    int i;
    int j;
    int datasize = 1 << bitsize;
    int n_loop   = n_data / datasize;
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
    int datasize = 1 << bitsize;
    int n_loop   = n_buffer / datasize;
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
