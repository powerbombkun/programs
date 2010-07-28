
/**
 * @file   test_parametertable.c
 * @author Junsei Takahashi
 * @date   last update 2010-07-28 21:50:25
 *
 * @brief test suite for test_parametertable.c
 */
#include "CUnit/CUnit.h"
#include "parametertable.h"
#include <stdlib.h>
#include "type.h"
#include "macro.h"
/* define */
/*  input file path */
/* static values */
/* global func */
int setup_test_parametertable();
int teardown_test_parametertable();
/* static func */
static ParameterTable_Handle hParameterTable;
static void test_normal_initialize();
/* test cases */
CU_TestInfo test_parametertable_array[] = {
    {"normal_initialize",    test_normal_initialize},
    CU_TEST_INFO_NULL
};

int
setup_test_parametertable()
{
    hParameterTable = ParameterTable_create();
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
