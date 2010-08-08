/**
 * @file   test_parametertable.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-08 23:06:18
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
static ParameterTable_Handle hParameterTable;
static void test_normal_initialize();
static void test_normal_store();
static void test_normal_w_store();
static void test_normal_re_store();
static void test_normal_fetch();
static void test_normal_re_sotre_fetch();
static void test_normal_writeFile();
static void test_normal_readFile();
/* test cases */
CU_TestInfo test_parametertable_array[] = {
    {"normal_initialize",    test_normal_initialize},
    {"normal_store",    test_normal_store},
    {"normal_w_store",    test_normal_w_store},
    {"normal_re_store",    test_normal_re_store},
    {"normal_fetch",    test_normal_fetch},
    {"normal_re_sotre_fetch",    test_normal_re_sotre_fetch},
    {"normal_writeFile",    test_normal_writeFile},
    {"normal_readFile",    test_normal_readFile},
    CU_TEST_INFO_NULL
};

int
setup_test_parametertable()
{
    hParameterTable = ParameterTable_create(KEY_NUM);
    if(hParameterTable == NULL)
    {
        CU_FAIL_FATAL("ParameterTable_create failed");
    }
   return 0;
}

int
teardown_test_parametertable()
{
    ParameterTable_delete(hParameterTable);
    return 0;
}

static void
test_normal_initialize()
{
    int32_t ret;
    int32_t val;
    int32_t ref = 128;
    ParameterTable_initialize(hParameterTable);
    ret = ParameterTable_store(hParameterTable,"TEST",ref);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    ret = ParameterTable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(val,ref);
    ParameterTable_initialize(hParameterTable);
    ret = ParameterTable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,FAILURE);
}

static void
test_normal_store()
{
    int32_t ret;
    ParameterTable_initialize(hParameterTable);
    ret = ParameterTable_store(hParameterTable,"TEST",128);
    CU_ASSERT_EQUAL(ret,SUCCESS);
}

static void
test_normal_w_store()
{
    int32_t ret;
    ParameterTable_initialize(hParameterTable);
    ParameterTable_store(hParameterTable,"TEST",128);
    ret = ParameterTable_store(hParameterTable,"HOGE",256);
    CU_ASSERT_EQUAL(ret,SUCCESS);
}

static void
test_normal_re_store()
{
    int32_t ret;
    ParameterTable_initialize(hParameterTable);
    ParameterTable_store(hParameterTable,"TEST",128);
    ret = ParameterTable_store(hParameterTable,"TEST",256);
    CU_ASSERT_EQUAL(ret,SUCCESS);
}


static void
test_normal_fetch()
{
    int32_t ret;
    int32_t ref = 128;
    int32_t val;
    ParameterTable_initialize(hParameterTable);
    ParameterTable_store(hParameterTable,"TEST",ref);
    ret = ParameterTable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(ref,val);
}

static void
test_normal_re_sotre_fetch()
{
    int32_t ret;
    int32_t ref = 256;
    int32_t val;
    ParameterTable_initialize(hParameterTable);
    ParameterTable_store(hParameterTable,"TEST",128);
    ParameterTable_store(hParameterTable,"TEST",256);
    ret = ParameterTable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(ref,val);
}

static void
test_normal_writeFile()
{
    int32_t ret;
    char    file[MAX_FILE_PATH_LENGTH];
    sprintf(file,"%s/test_parametertable.txt",TEST_DIR);
    ParameterTable_initialize(hParameterTable);
    ParameterTable_store(hParameterTable,"TEST",128);
    ParameterTable_store(hParameterTable,"HOGE",256);
    ret = ParameterTable_writeFile(hParameterTable,file);
    CU_ASSERT_EQUAL(ret,SUCCESS);
}

static void
test_normal_readFile()
{
    int32_t ret;
    int32_t val;
    char    file[MAX_FILE_PATH_LENGTH];
    sprintf(file,"%s/test_parametertable.txt",TEST_DIR);
    ParameterTable_initialize(hParameterTable);
    ParameterTable_store(hParameterTable,"TEST",128);
    ParameterTable_store(hParameterTable,"HOGE",256);
    ParameterTable_writeFile(hParameterTable,file);
    ParameterTable_initialize(hParameterTable);
    ret = ParameterTable_readFile(hParameterTable,file);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    ret = ParameterTable_fetch(hParameterTable,"TEST",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(128,val);
    ret = ParameterTable_fetch(hParameterTable,"HOGE",&val);
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_EQUAL(256,val);
}
