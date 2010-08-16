/**
 * @file   test_algorithm.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-17 00:10:04
 *
 * @brief test suite for test_algorithm.c
 */
#include "test_common.h"
#include "algorithm.h"
/*  input file path */
/* static values */
/* global func */
int setup_test_algorithm();
int teardown_test_algorithm();
/* static func */
static void test_normal_q_sort();
static void test_err_q_sort_same_val();
static void test_normal_b_sort();
static void test_normal_binary_search();
/* test cases */
CU_TestInfo test_algorithm_array[] = {
    {"normal_q_sort",    test_normal_q_sort},
    {"err_q_sort_same_val",    test_err_q_sort_same_val},
    {"normal_b_sort",    test_normal_b_sort},
    {"normal_binary_search",    test_normal_binary_search},
    CU_TEST_INFO_NULL
};

int
setup_test_algorithm()
{
    return 0;
}

int
teardown_test_algorithm()
{
    return 0;
}

static
void test_normal_q_sort()
{
    size_t i;
    int32_t ary[] = {0,10,1,9,2,8,3,7,4,6,5};
    int32_t ref[] = {0,1,2,3,4,5,6,7,8,9,10};
    q_sort(ary,ARRAY_SIZE(ary));

    for(i = 0;i < ARRAY_SIZE(ary);i++)
    {
        CU_ASSERT_EQUAL(ref[i],ary[i]);
    }
}

static
void test_err_q_sort_same_val()
{
    size_t i;
    int32_t ary[] = {0,0,0,0,0};
    int32_t ref[] = {0,0,0,0,0};
    q_sort(ary,ARRAY_SIZE(ary));

    for(i = 0;i < ARRAY_SIZE(ary);i++)
    {
        CU_ASSERT_EQUAL(ref[i],ary[i]);
    }
}

static
void test_normal_b_sort()
{
    size_t i;
    int32_t ary[] = {0,10,1,9,2,8,3,7,4,6,5};
    int32_t ref[] = {0,1,2,3,4,5,6,7,8,9,10};
    b_sort(ary,ARRAY_SIZE(ary));

    for(i = 0;i < ARRAY_SIZE(ary);i++)
    {
        CU_ASSERT_EQUAL(ref[i],ary[i]);
    }
}

static
void test_normal_binary_search()
{
    int32_t ary[] = {0,1,2,3,4,5,6,7,8,9,10};
    int32_t idx = binary_search(ary,ARRAY_SIZE(ary),7);
    CU_ASSERT_EQUAL(idx,7);
}
