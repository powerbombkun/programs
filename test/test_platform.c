
/**
 * @file   test_platform.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-08 15:49:44
 *
 * @brief test suite for test_platform.c
 */
#include "test_common.h"
#include "platform.h"
/*  input file path */
/* static values */
/* global func */
int setup_test_platform();
int teardown_test_platform();
/* static func */
static void test_normal_byte_reverse();
/* test cases */
CU_TestInfo test_platform_array[] = {
    {"normal_byte_reverse",    test_normal_byte_reverse},
    CU_TEST_INFO_NULL
};


int
setup_test_platform()
{
    return 0;
}

int
teardown_test_platform()
{
    return 0;
}

static void test_normal_byte_reverse()
{
    size_t i;
    uint8_t ary[] = {0,1,2,3};
    uint8_t ref[] = {3,2,1,0};
    byte_reverse(ary,ARRAY_SIZE(ary));

    for(i = 0;i < ARRAY_SIZE(ary);i++)
    {
        CU_ASSERT_EQUAL(ary[i],ref[i]);
    }
}

