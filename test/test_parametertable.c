
/**
 * @file   test_parametertable.c
 * @author Junsei Takahashi
 * @date   last update 2010-07-29 23:39:45
 *
 * @brief test suite for test_parametertable.c
 */
#include "CUnit/CUnit.h"
#include "util/parametertable.h"
#include <stdlib.h>
#include "util/type.h"
#include "util/macro.h"
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
static void test_normal_fetch();
/* test cases */
CU_TestInfo test_parametertable_array[] = {
    {"normal_initialize",    test_normal_initialize},
    {"normal_store",    test_normal_store},
    {"normal_fetch",    test_normal_fetch},
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
    ParameterTable_initialize(hParameterTable);
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
