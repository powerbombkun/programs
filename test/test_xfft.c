/**
 * @file   test_xfft.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-14 02:34:53
 *
 * @brief test suite for test_xfft.c
 */
#include "test_common.h"
#include "xfft.h"
#include <math.h>

#define FFT_SIZE 1024
/*  input file path */
/* static values */
/* global func */
int setup_test_xfft();
int teardown_test_xfft();
/* static func */
static void test_normal_xfft();
/* test cases */
CU_TestInfo test_xfft_array[] = {
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
test_normal_xfft()
{
    size_t i;
    short data[FFT_SIZE] = {0};
    short ref[FFT_SIZE] = {0};
    double re[FFT_SIZE]  = {0};
    double im[FFT_SIZE]  = {0};

    for(i = 0; i < ARRAY_SIZE(re); i++)
    {
        data[i] = i;
    }
    xfft(data,ARRAY_SIZE(data),re,im,8);
    xifft(re,im,data,ARRAY_SIZE(data),8);

    for(i = 256; i < 512; i++)
    {
        CU_ASSERT_EQUAL((int)data[i],(int)i);
    }
}

