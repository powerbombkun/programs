
/**
 * @file   test_ringbuffer.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-10 00:10:33
 *
 * @brief test suite for test_ringbuffer.c
 */
#include "test_common.h"
#include "util.h"
/*  input file path */
/* static values */
/* global func */
int setup_test_util();
int teardown_test_util();
/* static func */
static void test_normal_getMaxAmp();
static void test_normal_getFileName();
static void test_err_getFileName();
static void test_normal_splitString();
static void test_err_splitString_non_sep();
static void test_normal_trim();
/* test cases */
CU_TestInfo test_util_array[] = {
  {"normal_getMaxAmp",    test_normal_getMaxAmp},
  {"normal_getFileName",    test_normal_getFileName},
  {"err_getFileName",    test_err_getFileName},
  {"normal_splitString",    test_normal_splitString},
  {"err_splitString_non_sep",    test_err_splitString_non_sep},
  {"normal_trim",    test_normal_trim},
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
    int16_t val_array[] = {0,512,16384,8192};
    int16_t max_val = getMaxAmp(val_array,ARRAY_SIZE(val_array));
    CU_ASSERT_EQUAL(16384,max_val);
}

static void
test_normal_getFileName()
{
    const char* p = getFileName(__FILE__);
    CU_ASSERT_PTR_NOT_NULL(p)
    CU_ASSERT_STRING_EQUAL(p,"test_util.c");
}

static void
test_err_getFileName()
{
    CU_ASSERT_PTR_EQUAL(NULL,getFileName(" "));
}

static void
test_normal_splitString()
{
    int32_t ret;
    char first[128] = {0};
    char second[128] = {0};
    ret = splitString("TEST:0",":",first,second);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_STRING_EQUAL("TEST",first);
    CU_ASSERT_STRING_EQUAL("0",second);
}

static
void test_err_splitString_non_sep()
{
    int32_t ret;
    char first[128] = {0};
    char second[128] = {0};
    ret = splitString("TEST 0",":",first,second);
    CU_ASSERT_EQUAL(ret,FAILURE);
}

static void
test_normal_trim()
{
    char* str = "  TEST  ";
    CU_ASSERT_STRING_EQUAL(trim(str),"TEST  ");
}

