/**
 * @file   test_algorithm.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-05 00:12:26
 *
 * @brief test suite for test_algorithm.c
 */
#include "CUnit/CUnit.h"
#include "algorithm.h"
#include <stdlib.h>
#include "type.h"
#include "macro.h"
/*  input file path */
/* static values */
/* global func */
int setup_test_algorithm();
int teardown_test_algorithm();
/* static func */
static void test_normal_quick_sort();
static void test_err_quick_sort_same_val();
static void test_err_quick_sort_idx_reverse();
/* test cases */
CU_TestInfo test_algorithm_array[] = {
    {"normal_quick_sort",    test_normal_quick_sort},
    {"err_quick_sort_same_val",    test_err_quick_sort_same_val},
    {"err_quick_sort_idx_reverse",    test_err_quick_sort_idx_reverse},
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
void test_normal_quick_sort()
{
    size_t i;
    int32_t ary[] = {0,10,1,9,2,8,3,7,4,6,5};
    int32_t ref[] = {0,1,2,3,4,5,6,7,8,9,10};
    quick_sort(ary,0,ARRAY_SIZE(ary)-1);

    for(i = 0;i < ARRAY_SIZE(ary);i++)
    {
        CU_ASSERT_EQUAL(ref[i],ary[i]);
    }
}

static
void test_err_quick_sort_same_val()
{
    size_t i;
    int32_t ary[] = {0,0,0,0,0};
    int32_t ref[] = {0,0,0,0,0};
    quick_sort(ary,0,ARRAY_SIZE(ary)-1);

    for(i = 0;i < ARRAY_SIZE(ary);i++)
    {
        CU_ASSERT_EQUAL(ref[i],ary[i]);
    }
}

static
void test_err_quick_sort_idx_reverse()
{
    size_t i;
    int32_t ary[] = {0,10,1,9,2,8,3,7,4,6,5};
    int32_t ref[] = {0,10,1,9,2,8,3,7,4,6,5};
    quick_sort(ary,ARRAY_SIZE(ary)-1,0);

    for(i = 0;i < ARRAY_SIZE(ary);i++)
    {
        CU_ASSERT_EQUAL(ref[i],ary[i]);
    }
}
