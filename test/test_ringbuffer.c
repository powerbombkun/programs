
/**
 * @file   test_ringbuffer.c
 * @author Junsei Takahashi
 * @date   last update 2010-10-01 23:18:14
 *
 * @brief test suite for test_ringbuffer.c
 */
#include "test_common.h"
#include "ringbuffer.h"
/* define */
#define RINGBUFFER_SIZE (64)
/*  input file path */
/* static values */
/* global func */
int setup_test_ringbuffer();
int teardown_test_ringbuffer();
/* static func */
static ringbuffer_handle hRingBuffer;
static void test_normal_initialize();
static void test_normal_get_data_size();
static void test_normal_get_buffer_size();
static void test_normal_get_data();
static void test_normal_set_data();
/* test cases */
CU_TestInfo test_ringbuffer_array[] = {
  {"normal_initialize",    test_normal_initialize},
  {"normal_get_data_size",    test_normal_get_data_size},
  {"normal_get_buffer_size",    test_normal_get_buffer_size},
  {"normal_get_data", test_normal_get_data},
  {"normal_set_data", test_normal_set_data},
  CU_TEST_INFO_NULL
};

int
setup_test_ringbuffer()
{
    hRingBuffer = ringbuffer_create(RINGBUFFER_SIZE);
    if(hRingBuffer == NULL)
    {
        CU_FAIL_FATAL("ringbuffer_create failed");
    }

    return 0;
}

int
teardown_test_ringbuffer()
{
    ringbuffer_delete(hRingBuffer);
    return 0;
}

static void
test_normal_initialize()
{
    uint8_t data_array[RINGBUFFER_SIZE];
    int32_t size;
    ringbuffer_initialize(hRingBuffer);
    ringbuffer_set_data(hRingBuffer,data_array,ARRAY_SIZE(data_array));
    ringbuffer_initialize(hRingBuffer);

    size = ringbuffer_get_data_size(hRingBuffer);

    CU_ASSERT_EQUAL(size,0);
}

static void
test_normal_get_data_size()
{
    uint8_t data_array[RINGBUFFER_SIZE];
    int32_t size;
    ringbuffer_initialize(hRingBuffer);
    ringbuffer_set_data(hRingBuffer,data_array,ARRAY_SIZE(data_array));
    size = ringbuffer_get_data_size(hRingBuffer);

    CU_ASSERT_EQUAL(size,ARRAY_SIZE(data_array));
}

static void
test_normal_get_buffer_size()
{
    int32_t size;
    size = ringbuffer_get_buffer_size(hRingBuffer);

    CU_ASSERT_EQUAL(size,RINGBUFFER_SIZE);
}

static void
test_normal_get_data()
{
    int i;
    int32_t ret;
    uint8_t data;
    uint8_t buf;

    ringbuffer_initialize(hRingBuffer);
    for(i = 0;i < RINGBUFFER_SIZE*2;i++)
    {
        data = i;

        ringbuffer_set_data(hRingBuffer,&data,1);
        ret = ringbuffer_get_data(hRingBuffer,&buf,1);

        CU_ASSERT_EQUAL(ret,SUCCESS);
        CU_ASSERT_EQUAL(data,buf);
    }
}

static void
test_normal_set_data()
{
    size_t i;
    int32_t ret = SUCCESS;
    uint8_t data_array[RINGBUFFER_SIZE];
    uint8_t buf_array[RINGBUFFER_SIZE/2];
    for(i = 0;i < ARRAY_SIZE(data_array);i++)
    {
        data_array[i] = i;
    }
    ringbuffer_initialize(hRingBuffer);
    ret |= ringbuffer_set_data(hRingBuffer,data_array,ARRAY_SIZE(data_array));
    ret |= ringbuffer_get_data(hRingBuffer,buf_array,ARRAY_SIZE(buf_array));
    ret |= ringbuffer_set_data(hRingBuffer,buf_array,ARRAY_SIZE(buf_array));
    ret |= ringbuffer_get_data(hRingBuffer,buf_array,ARRAY_SIZE(buf_array));
    ret |= ringbuffer_set_data(hRingBuffer,buf_array,ARRAY_SIZE(buf_array));
    CU_ASSERT_EQUAL(ret,SUCCESS);
}
