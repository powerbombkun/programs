/**
 * @file   test_xfft.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-16 00:55:25
 *
 * @brief test suite for test_xfft.c
 */
#include "test_common.h"
#include "xfft.h"
#include <math.h>

#define FFT_SIZE 512
/*  input file path */
/* static values */
/* global func */
int setup_test_xfft();
int teardown_test_xfft();
/* static func */
static void test_normal_windowFFT();
static void test_normal_xfft();
/* test cases */
CU_TestInfo test_xfft_array[] = {
    {"normal_windowFFT",    test_normal_windowFFT},
    {"normal_xfft",    test_normal_xfft},
    CU_TEST_INFO_NULL
};

int
setup_test_xfft()
{
    return 0;
}

int
teardown_test_xfft()
{
    return 0;
}

static void
test_normal_windowFFT()
{
    size_t i;

    double re[FFT_SIZE] = {0};
    double ref[FFT_SIZE] = {0};
    double im[FFT_SIZE] = {0};

    for(i = 0; i < ARRAY_SIZE(re); i++)
    {
        re[i] = sin(((double)i/(double)256)* (double)2.0 * (double)3.14);
        ref[i] = re[i];
        im[i] = 0;
    }
    windowFFT(re,im,8,FALSE);
    windowFFT(re,im,8,TRUE);
    for(i = 0; i < ARRAY_SIZE(re); i++)
    {
        /* printf("ref = %f re = %f\n",ref[i],re[i]); */
    }
}

static void
test_normal_xfft()
{
    size_t i;
    int16_t data[FFT_SIZE] = {0};
    int16_t ref[FFT_SIZE] = {0};
    double re[FFT_SIZE]  = {0};
    double im[FFT_SIZE]  = {0};

    for(i = 0;i < ARRAY_SIZE(data);i++)
    {
        data[i] = (int16_t)i;
        ref[i] = data[i];
    }

    xfft(data,ARRAY_SIZE(data),re,im,8);
    xifft(re,im,data,ARRAY_SIZE(data),8);

    for(i = 0;i < ARRAY_SIZE(data);i++)
    {
        printf("ref = %d data = %d\n",ref[i],data[i]);
        /* /\* printf("ref = %d\n",ref[i]); *\/ */
        /* if((ref[i] < (re[i] - 5)) || ((re[i] + 5) < ref[i])) */
        /* { */
        /*     /\* CU_FAIL("xfft input output data not equal"); *\/ */
        /* } */
    }
}

