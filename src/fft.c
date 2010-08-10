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
static void bit_reverse(int n, double* a);

static void bit_reverse(int n, double* a)
{
    int i, j, k;
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

void fft(double* re,double* im,int     bitsize)
{
    int    i,j,stage,type;
    double wRe, wIm, uRe, uIm, tempRe, tempIm;
    int    datasize = 1 << bitsize;
    int    jp;
    bit_reverse(datasize,re);
    bit_reverse(datasize,im);

    for (stage = 1; stage <= bitsize; stage++)
    {
        int butterflydist = 1 << stage;
        int numType       = butterflydist >> 1;
        int butterflysize = butterflydist >> 1;

        wRe = 1.0;
        wIm = 0.0;
        uRe = cos(PI / butterflysize);
        uIm = -sin(PI / butterflysize);

        for (type = 0; type < numType; type++)
        {
            for (j = type; j < datasize; j += butterflydist)
            {
                jp      = j + butterflysize;
                tempRe  = re[jp] * wRe - im[jp] * wIm;
                tempIm  = re[jp] * wIm + im[jp] * wRe;
                re[jp]  = re[j] - tempRe;
                im[jp]  = im[j] - tempIm;
                re[j]  += tempRe;
                im[j]  += tempIm;
            }
            wRe = wRe * uRe - wIm * uIm;
            wIm = wRe * uIm + wIm * uRe;
        }
    }
}
