
/**
 * @file   test_ringbuffer.c
 * @author Junsei Takahashi
 * @date   last update 2010-07-23 00:59:20
 *
 * @brief test suite for test_ringbuffer.c
 */
#include "CUnit/CUnit.h"
#include "ringbuffer.h"
#include <stdlib.h>
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
/* test cases */
CU_TestInfo test_ringbuffer_array[] = {
  {"normal_initialize",    test_normal_initialize},
  {"normal_getDataSize",    test_normal_getDataSize},
  {"normal_getBufferSize",    test_normal_getBufferSize},
  CU_TEST_INFO_NULL
};

int
setup_test_ringbuffer()
{
  hRingBuffer = RingBuffer_create(RINGBUFFER_SIZE);
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
    RingBuffer_initialize(hRingBuffer);
}

static void
test_normal_getDataSize()
{
    RingBuffer_getDataSize(hRingBuffer);
}

static void
test_normal_getBufferSize()
{
    RingBuffer_getBufferSize(hRingBuffer);
}
