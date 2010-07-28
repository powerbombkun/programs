
/**
 * @file   test_ringbuffer.c
 * @author Junsei Takahashi
 * @date   last update 2010-07-28 23:47:16
 *
 * @brief test suite for test_ringbuffer.c
 */
#include "CUnit.h"
#include "ringbuffer.h"
#include <stdlib.h>
#include "type.h"
#include "macro.h"
/* define */
#define RINGBUFFER_SIZE (1024)
/*  input file path */
/* static values */
/* global func */
int setup_test_ringbuffer();
int teardown_test_ringbuffer();
/* static func */
static RingBuffer_Handle hRingBuffer;
static void test_normal_initialize();
static void test_normal_getDataSize();
static void test_normal_getBufferSize();
static void test_normal_getData();
static void test_normal_setData();
/* test cases */
CU_TestInfo test_ringbuffer_array[] = {
  {"normal_initialize",    test_normal_initialize},
  {"normal_getDataSize",    test_normal_getDataSize},
  {"normal_getBufferSize",    test_normal_getBufferSize},
  {"normal_getData", test_normal_getData},
  {"normal_setData", test_normal_setData},
  CU_TEST_INFO_NULL
};

int
setup_test_ringbuffer()
{
    hRingBuffer = RingBuffer_create(RINGBUFFER_SIZE);
    if(hRingBuffer == NULL)
    {
        CU_FAIL_FATAL("RingBuffer_create failed");
    }

    return 0;
}

int
teardown_test_ringbuffer()
{
    RingBuffer_delete(hRingBuffer);
    return 0;
}

static void
test_normal_initialize()
{
    uint8_t data_array[RINGBUFFER_SIZE];
    int32_t size;
    RingBuffer_initialize(hRingBuffer);
    RingBuffer_setData(hRingBuffer,data_array,ARRAY_SIZE(data_array));
    RingBuffer_initialize(hRingBuffer);

    size = RingBuffer_getDataSize(hRingBuffer);

    CU_ASSERT_EQUAL(size,0);
}

static void
test_normal_getDataSize()
{
    uint8_t data_array[RINGBUFFER_SIZE];
    int32_t size;
    RingBuffer_initialize(hRingBuffer);
    RingBuffer_setData(hRingBuffer,data_array,ARRAY_SIZE(data_array));
    size = RingBuffer_getDataSize(hRingBuffer);

    CU_ASSERT_EQUAL(size,ARRAY_SIZE(data_array));
}

static void
test_normal_getBufferSize()
{
    int32_t size;
    size = RingBuffer_getBufferSize(hRingBuffer);

    CU_ASSERT_EQUAL(size,RINGBUFFER_SIZE);
}

static void
test_normal_getData()
{
    int i;
    int32_t ret;
    uint8_t data_array[] = {0,1,2,3};
    uint8_t buf_array[4];
    int32_t size;

    RingBuffer_initialize(hRingBuffer);
    RingBuffer_setData(hRingBuffer,data_array,ARRAY_SIZE(data_array));
    size = RingBuffer_getDataSize(hRingBuffer);
    ret = RingBuffer_getData(hRingBuffer,buf_array,ARRAY_SIZE(buf_array));

    CU_ASSERT_EQUAL(ret,SUCCESS);

    for(i = 0;i < size;i++)
    {
        CU_ASSERT_EQUAL(data_array[i],buf_array[i]);
    }

    size = RingBuffer_getDataSize(hRingBuffer);
    CU_ASSERT_EQUAL(size,0);
}

static void
test_normal_setData()
{
    int32_t ret;
    uint8_t data_array[] = {0,1,2,3};

    RingBuffer_initialize(hRingBuffer);
    ret = RingBuffer_setData(hRingBuffer,data_array,ARRAY_SIZE(data_array));

    CU_ASSERT_EQUAL(ret,SUCCESS);
}
