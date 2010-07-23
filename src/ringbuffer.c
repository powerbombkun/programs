#include "ringbuffer.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    uint8_t* p_buffer;
    int32_t  n_buffer;
    int32_t  readCounter;
    int32_t  writeCounter;
}ringbuffer_t;

RingBuffer_Handle RingBuffer_create(uint32_t n_buffer)
{
    ringbuffer_t* This;
    This = (ringbuffer_t*)malloc(sizeof(ringbuffer_t));

    This->n_buffer   = n_buffer;
    This->p_buffer     = (uint8_t*)malloc(This->n_buffer);
    This->readCounter  = 0;
    This->writeCounter = 0;

    return (RingBuffer_Handle)This;
}

void              RingBuffer_delete(RingBuffer_Handle h_obj)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    free((void*)This->p_buffer);
    free((void*)This);
}

void              RingBuffer_initialize(RingBuffer_Handle h_obj)
{
    int           i;
    ringbuffer_t* This = (ringbuffer_t*)h_obj;

    for(i = 0;i < This->n_buffer;i++)
    {
        This->p_buffer[i] = 0;
    }
    This->readCounter  = 0;
    This->writeCounter = 0;
}

int32_t RingBuffer_getDataSize(RingBuffer_Handle h_obj)
{
    int32_t       size;
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    if ( This->readCounter <= This->writeCounter )
    {
        size = This->writeCounter - This->readCounter;
    }else{
        size = This->n_buffer + This->writeCounter - This->readCounter;
    }
    return size;
}

int32_t RingBuffer_getBufferSize(RingBuffer_Handle h_obj)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    return This->n_buffer;
}

int32_t RingBuffer_getData(RingBuffer_Handle h_obj,uint8_t* p_buffer, int32_t n_buffer)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    int32_t       ret  = FAILURE;
    int32_t       size = RingBuffer_getDataSize(h_obj);

    if(n_buffer <= size)
    {
        int i;
        for(i = 0;i < n_buffer;i++)
        {
            *(p_buffer+i) = *(This->p_buffer + This->readCounter);
            This->readCounter++;

            if ( This->readCounter == This->n_buffer )
            {
                This->readCounter = 0;
            }
        }
        ret = SUCCESS;
    }
    return ret;
}

int32_t RingBuffer_setData(RingBuffer_Handle h_obj,uint8_t* p_data, int32_t n_data)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    int32_t       ret  = FAILURE;
    int32_t       rest = This->n_buffer - RingBuffer_getDataSize(h_obj);

    if(rest >= n_data)
    {
        int i;
        for (i = 0; i<n_data; i++ )
        {
            *(This->p_buffer + This->writeCounter) = *(p_data + i);
            This->writeCounter++;

            if ( This->writeCounter > This->n_buffer )
            {
                This->writeCounter = 0;
            }
        }
        ret = SUCCESS;
    }
    return ret;
}

