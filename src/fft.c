#include "fft.h"
#include <malloc.h>
#include <math.h>

#define PI 3.14159265

/**
 * @brief ビット反転した配列を返します
 *
 * @param[in] n 配列の個数(2の階乗個)
 * @param[in] a ビット反転対象配列
 *
 */
static void bit_reverse(int32_t n, double* a);

static void bit_reverse(int32_t n, double* a)
{
    int32_t i, j, k;
    i = 0;
    for (j = 1; j < n - 1; j++)
    {
        k = n >> 1;
        while (k <= i)
        {
            i = i - k;
            k = k >> 1;
        }
        i = i + k;
        if (j < i)
        {
            SWAP(double,a[j],a[i]);
        }
    }
}

void fft(double* re,double* im,int32_t     bitsize)
{
    int32_t i,j;
    int32_t stage;
    int32_t datasize = 1 << bitsize;

    bit_reverse(datasize,re);
    bit_reverse(datasize,im);

    for (stage = 1; stage <= bitsize; stage++)
    {
        int32_t type;
        double  wRe, wIm;
        double  uRe, uIm;
        double  tempwRe,tempwIm;
        double  tempRe, tempIm;
        int32_t butterflydist = 1 << stage;
        int32_t numType       = butterflydist >> 1;
        int32_t butterflysize = butterflydist >> 1;

        wRe = 1.0;
        wIm = 0.0;
        uRe = cos(PI / butterflysize);
        uIm = -sin(PI / butterflysize);

        for (type = 0; type < numType; type++)
        {
            for (j = type; j < datasize; j += butterflydist)
            {
                int32_t jp;
                jp      = j + butterflysize;
                tempRe  = re[jp] * wRe - im[jp] * wIm;
                tempIm  = re[jp] * wIm + im[jp] * wRe;
                re[jp]  = re[j] - tempRe;
                im[jp]  = im[j] - tempIm;
                re[j]  += tempRe;
                im[j]  += tempIm;
            }
            tempwRe = wRe * uRe - wIm * uIm;
            tempwIm = wRe * uIm + wIm * uRe;
            wRe = tempwRe;
            wIm = tempwIm;
        }
    }
}

void ifft(double* re,double* im,int32_t     bitsize)
{
    int i;
    int size = 1 << bitsize;
    double fac = 1.0 / size;

    for (i = 0; i < size; i++)
    {
        im[i] = -im[i];
    }

    fft(re,im,bitsize);

    for (i = 0; i < size; i++)
    {
        re[i] = re[i] * fac;
        im[i] = -(im[i] * fac);
    }
}


void spectrum(double* re,double* im,int n,double* power)
{
    int i;
    for(i = 0;i < n;i++)
    {
        power[i] = sqrt((re[i]*re[i])+(im[i]*im[i]));
    }
}
