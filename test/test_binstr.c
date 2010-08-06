/**
 * @file   test_binstr.c
 * @author Junsei Takahashi
 * @date   last update 2010-08-06 23:44:46
 *
 * @brief test suite for test_binstr.c
 */
#include "CUnit/CUnit.h"
#include "binstr.h"
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024
/*  input file path */
/* static values */
/* global func */
int setup_test_binstr();
int teardown_test_binstr();
/* static func */
static void test_normal_bin2str();
static void test_normal_str2bin();
/* test cases */
CU_TestInfo test_binstr_array[] = {
    {"normal_bin2str",    test_normal_bin2str},
    {"normal_str2bin",    test_normal_str2bin},
    CU_TEST_INFO_NULL
};

int
setup_test_binstr()
{
    return 0;
}

int
teardown_test_binstr()
{
    return 0;
}

static
void test_normal_bin2str()
{
    uint8_t b[] = {0x00,0x09,0x0A,0x0F};
    char* s = "00090A0F";
    char buffer[MAX_BUFFER_SIZE];
    int32_t ret;
    memset(buffer,0,sizeof(buffer));
    ret = bin2str(b,sizeof(b),buffer,sizeof(buffer));
    CU_ASSERT_EQUAL(ret,SUCCESS);
    CU_ASSERT_STRING_EQUAL(buffer,s);
}

static
void test_normal_str2bin()
{
    char* s = "00090A0F";
    uint8_t b[] = {0x00,0x09,0x0A,0x0F};
    uint8_t buffer[MAX_BUFFER_SIZE];
    int32_t ret;
    size_t i;
    memset(buffer,0,sizeof(buffer));
    ret = str2bin(s,strlen(s),buffer,sizeof(buffer));
    CU_ASSERT_EQUAL(ret,SUCCESS);

    for(i = 0;i < ARRAY_SIZE(b);i++)
    {
        CU_ASSERT_EQUAL(b[i],buffer[i]);
    }
}

