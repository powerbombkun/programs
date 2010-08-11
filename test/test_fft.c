/**
 * @file   test_fft.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-11 22:28:26
 *
 * @brief test suite for test_fft.c
 */
#include "test_common.h"
#include "fft.h"
#include <math.h>

#define FFT_SIZE 256
/*  input file path */
/* static values */
/* global func */
int setup_test_fft();
int teardown_test_fft();
/* static func */
static void test_normal_fft();
/* test cases */
CU_TestInfo test_fft_array[] = {
    {"normal_fft",    test_normal_fft},
    CU_TEST_INFO_NULL
};

int
setup_test_fft()
{
    return 0;
}

int
teardown_test_fft()
{
    return 0;
}

static void
test_normal_fft()
{
    size_t i;

    double re[FFT_SIZE] = {0};
    double im[FFT_SIZE] = {0};

    for(i = 0; i < ARRAY_SIZE(re); i++)
    {
        re[i] = sin(((double)i/(double)256)* (double)2.0 * (double)3.14);
        im[i] = 0;
    }

    fft(re,im,8);

    ifft(re,im,8);

    i = 0;
}
