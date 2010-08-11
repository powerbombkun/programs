/**
 * @file   test_dbconv.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-11 23:35:32
 *
 * @brief test suite for test_dbconv.c
 */
#include "test_common.h"
#include "dbconv.h"

#define MAX_LINEAR 32767
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
    int32_t linear_array[] = {32767,16384,8192,4096};
    int32_t ref_db_array[] = {0,-6,-12,-18};
    for(i = 0;i < ARRAY_SIZE(linear_array);i++)
    {
        double db = linear2db(linear_array[i],MAX_LINEAR);
        CU_ASSERT_EQUAL(ref_db_array[i],(int32_t)db);
    }
}

static
void test_normal_db2linear()
{
    size_t i;
    double db_array[] = {0,-6,-12,-18};
    int32_t ref_linear_array[] = {32767,16422,8230,4125};

    for(i = 0;i < ARRAY_SIZE(db_array);i++)
    {
        int32_t linear = db2linear(db_array[i],MAX_LINEAR);
        CU_ASSERT_EQUAL(ref_linear_array[i],linear);
    }
}


