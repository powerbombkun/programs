/**
 * @file   test_dbconv.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-08 15:46:35
 *
 * @brief test suite for test_dbconv.c
 */
#include "test_common.h"
#include "dbconv.h"
/*  input file path */
/* static values */
/* global func */
int setup_test_dbconv();
int teardown_test_dbconv();
/* static func */
static void test_normal_linear2db();
static void test_normal_db2linear();
/* test cases */
CU_TestInfo test_dbconv_array[] = {
    {"normal_linear2db",    test_normal_linear2db},
    {"normal_db2linear",    test_normal_db2linear},
    CU_TEST_INFO_NULL
};

int
setup_test_dbconv()
{
    return 0;
}

int
teardown_test_dbconv()
{
    return 0;
}

static
void test_normal_linear2db()
{
    size_t i;
    int16_t linear_array[] = {32767,16384,8192,4096};
    int16_t ref_db_array[] = {0,-6,-12,-18};
    for(i = 0;i < ARRAY_SIZE(linear_array);i++)
    {
        float db = linear2db(linear_array[i]);
        CU_ASSERT_EQUAL(ref_db_array[i],(int16_t)db);
    }
}

static
void test_normal_db2linear()
{
    size_t i;
    float db_array[] = {0,-6,-12,-18};
    int16_t ref_linear_array[] = {32767,16422,8230,4125};

    for(i = 0;i < ARRAY_SIZE(db_array);i++)
    {
        int16_t linear = db2linear(db_array[i]);
        CU_ASSERT_EQUAL(ref_linear_array[i],linear);
    }
}


