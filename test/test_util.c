
/**
 * @file   test_ringbuffer.c
 * @author Junsei Takahashi
 * @date   last update 2010-10-01 22:53:35
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
static void test_normal_get_max_amp();
static void test_normal_get_file_name();
static void test_err_get_file_name();
static void test_normal_split_string();
static void test_err_split_string_non_sep();
static void test_normal_trim();
static void test_normal_byte_reverse();
/* test cases */
CU_TestInfo test_util_array[] = {
    {"normal_get_max_amp",    test_normal_get_max_amp},
    {"normal_get_file_name",    test_normal_get_file_name},
    {"err_get_file_name",    test_err_get_file_name},
    {"normal_split_string",    test_normal_split_string},
    {"err_split_string_non_sep",    test_err_split_string_non_sep},
    {"normal_trim",    test_normal_trim},
    {"normal_byte_reverse",    test_normal_byte_reverse},
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
test_normal_get_max_amp()
{
    int16_t val_array[] = {0,512,16384,8192};
    int16_t max_val = get_max_amp(val_array,ARRAY_SIZE(val_array));
    CU_ASSERT_EQUAL(16384,max_val);
}

static void
test_normal_get_file_name()
{
    const char* p = get_file_name(__FILE__);
    CU_ASSERT_PTR_NOT_NULL(p)
    CU_ASSERT_STRING_EQUAL(p,"test_util.c");
}

static void
test_err_get_file_name()
{
    CU_ASSERT_PTR_EQUAL(NULL,get_file_name(" "));
}

static void
test_normal_split_string()
{
    int32_t ret;
    char first[128] = {0};
    char second[128] = {0};
    ret = split_string("TEST:0",":",first,second);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_STRING_EQUAL("TEST",first);
    CU_ASSERT_STRING_EQUAL("0",second);
}

static
void test_err_split_string_non_sep()
{
    int32_t ret;
    char first[128] = {0};
    char second[128] = {0};
    ret = split_string("TEST 0",":",first,second);
    CU_ASSERT_EQUAL(ret,FAILURE);
}

static void
test_normal_trim()
{
    char* str = "  TEST  ";
    CU_ASSERT_STRING_EQUAL(trim(str),"TEST  ");
}

static void
test_normal_byte_reverse()
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
