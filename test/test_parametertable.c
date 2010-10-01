/**
 * @file   test_parametertable.c
 * @author Junsei Takahashi
 * @date   last update 2010-10-01 23:11:41
 *
 * @brief test suite for test_parametertable.c
 */
#include "test_common.h"
#include "parametertable.h"
/* define */
#define KEY_NUM 128
/*  input file path */
/* static values */
/* global func */
int setup_test_parametertable();
int teardown_test_parametertable();
/* static func */
static parametertable_handle hParameterTable;
static void test_normal_initialize();
static void test_normal_store();
static void test_normal_w_store();
static void test_normal_re_store();
static void test_normal_fetch();
static void test_normal_re_sotre_fetch();
static void test_normal_write_file();
static void test_normal_read_file();
/* test cases */
CU_TestInfo test_parametertable_array[] = {
    {"normal_initialize",    test_normal_initialize},
    {"normal_store",    test_normal_store},
    {"normal_w_store",    test_normal_w_store},
    {"normal_re_store",    test_normal_re_store},
    {"normal_fetch",    test_normal_fetch},
    {"normal_re_sotre_fetch",    test_normal_re_sotre_fetch},
    {"normal_write_file",    test_normal_write_file},
    {"normal_read_file",    test_normal_read_file},
    CU_TEST_INFO_NULL
};

int
setup_test_parametertable()
{
    hParameterTable = parametertable_create(KEY_NUM);
    if(hParameterTable == NULL)
    {
        CU_FAIL_FATAL("parametertable_create failed");
    }
   return 0;
}

int
teardown_test_parametertable()
{
    parametertable_delete(hParameterTable);
    return 0;
}

static void
test_normal_initialize()
{
    int32_t ret;
    int32_t val;
    int32_t ref = 128;
    parametertable_initialize(hParameterTable);
    ret = parametertable_store(hParameterTable,"TEST",ref);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    ret = parametertable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(val,ref);
    parametertable_initialize(hParameterTable);
    ret = parametertable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,FAILURE);
}

static void
test_normal_store()
{
    int32_t ret;
    parametertable_initialize(hParameterTable);
    ret = parametertable_store(hParameterTable,"TEST",128);
    CU_ASSERT_EQUAL(ret,SUCCESS);
}

static void
test_normal_w_store()
{
    int32_t ret;
    parametertable_initialize(hParameterTable);
    parametertable_store(hParameterTable,"TEST",128);
    ret = parametertable_store(hParameterTable,"HOGE",256);
    CU_ASSERT_EQUAL(ret,SUCCESS);
}

static void
test_normal_re_store()
{
    int32_t ret;
    parametertable_initialize(hParameterTable);
    parametertable_store(hParameterTable,"TEST",128);
    ret = parametertable_store(hParameterTable,"TEST",256);
    CU_ASSERT_EQUAL(ret,SUCCESS);
}


static void
test_normal_fetch()
{
    int32_t ret;
    int32_t ref = 128;
    int32_t val;
    parametertable_initialize(hParameterTable);
    parametertable_store(hParameterTable,"TEST",ref);
    ret = parametertable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(ref,val);
}

static void
test_normal_re_sotre_fetch()
{
    int32_t ret;
    int32_t ref = 256;
    int32_t val;
    parametertable_initialize(hParameterTable);
    parametertable_store(hParameterTable,"TEST",128);
    parametertable_store(hParameterTable,"TEST",256);
    ret = parametertable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(ref,val);
}

static void
test_normal_write_file()
{
    int32_t ret;
    parametertable_initialize(hParameterTable);
    parametertable_store(hParameterTable,"TEST",128);
    parametertable_store(hParameterTable,"HOGE",256);
    ret = parametertable_write_file(hParameterTable,TEMP_FILE);
    CU_ASSERT_EQUAL(ret,SUCCESS);
}

static void
test_normal_read_file()
{
    int32_t ret;
    int32_t val;
    parametertable_initialize(hParameterTable);
    parametertable_store(hParameterTable,"TEST",128);
    parametertable_store(hParameterTable,"HOGE",256);
    parametertable_write_file(hParameterTable,TEMP_FILE);
    parametertable_initialize(hParameterTable);
    ret = parametertable_read_file(hParameterTable,TEMP_FILE);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    ret = parametertable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(128,val);
    ret = parametertable_fetch(hParameterTable,"HOGE",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(256,val);
}
