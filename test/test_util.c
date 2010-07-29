
/**
 * @file   test_ringbuffer.c
 * @author Junsei Takahashi
 * @date   last update 2010-07-29 23:40:49
 *
 * @brief test suite for test_ringbuffer.c
 */
#include "CUnit/CUnit.h"
#include "util/util.h"
#include <stdlib.h>
#include "util/type.h"
#include "util/macro.h"

/*  input file path */
/* static values */
/* global func */
int setup_test_util();
int teardown_test_util();
/* static func */
static void test_normal_getMaxAmp();
static void test_normal_getFileName();
static void test_normal_splitString();
/* test cases */
CU_TestInfo test_util_array[] = {
  {"normal_getMaxAmp",    test_normal_getMaxAmp},
  {"normal_getFileName",    test_normal_getFileName},
  {"normal_splitString",    test_normal_splitString},
  CU_TEST_INFO_NULL
};

int
setup_test_util()
{
  return 0;
}

int
teardown_test_util()
{
  return 0;
}


static void
test_normal_getMaxAmp()
{
    int16_t val_array[] = {0,4096,16384,8192};
    int16_t max_val = getMaxAmp(val_array,ARRAY_SIZE(val_array));
    CU_ASSERT_EQUAL(16384,max_val);
}

static void
test_normal_getFileName()
{
    CU_ASSERT_STRING_EQUAL("util.h",getFileName("../src/util.h"));
}

static void
test_normal_splitString()
{
    char first[128] = {0};
    char second[128] = {0};
    splitString("TEST:0",":",first,second);

    CU_ASSERT_STRING_EQUAL("TEST",first);
    CU_ASSERT_STRING_EQUAL("0",second);
}

