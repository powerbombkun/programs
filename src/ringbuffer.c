#include "ringbuffer.h"
#include "macro.h"
#include "common.h"
/**
 * @struct ringbuffer_t
 * @brief  リングバッファーの内部データ管理用構造体
 */
typedef struct
{
    uint8_t* p_buffer;
    int32_t  n_buffer;
    int32_t  readCounter;
    int32_t  writeCounter;
    int32_t  data_length;
}ringbuffer_t;

ringbuffer_handle ringbuffer_create(uint32_t n_buffer)
{
    ringbuffer_t* This;
    This = (ringbuffer_t*)x_malloc(sizeof(ringbuffer_t));
    if(This != NULL)
    {
        This->n_buffer = n_buffer;
        This->p_buffer = (uint8_t*)x_malloc(This->n_buffer);
        if(This->p_buffer != NULL)
        {
            This->readCounter  = 0;
            This->writeCounter = 0;
            This->data_length  = 0;
            return (ringbuffer_handle)This;
        }
        free(This);
    }
    return NULL;
}

void              ringbuffer_delete(ringbuffer_handle h_obj)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    SAFE_FREE(This->p_buffer);
    SAFE_FREE(This);
}

void              ringbuffer_initialize(ringbuffer_handle h_obj)
{
    int           i;
    ringbuffer_t* This = (ringbuffer_t*)h_obj;

    for(i = 0;i < This->n_buffer;i++)
    {
        This->p_buffer[i] = 0;
    }
    This->readCounter  = 0;
    This->writeCounter = 0;
    This->data_length  = 0;
}

int32_t ringbuffer_get_data_size(ringbuffer_handle h_obj)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    return This->data_length;
}

int32_t ringbuffer_get_buffer_size(ringbuffer_handle h_obj)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    return This->n_buffer;
}

int32_t ringbuffer_get_data(ringbuffer_handle h_obj,uint8_t* p_buffer, int32_t n_buffer)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    int32_t       ret  = FAILURE;
    int32_t       size = ringbuffer_get_data_size(h_obj);

    if(n_buffer <= size)
    {
        int i;
        for(i = 0;i < n_buffer;i++)
        {
            if ( This->readCounter == This->n_buffer )
            {
                This->readCounter = 0;
            }
            *(p_buffer+i) = *(This->p_buffer + This->readCounter);
            This->readCounter++;
            This->data_length--;
        }
        ret = SUCCESS;
    }
    return ret;
}

int32_t ringbuffer_set_data(ringbuffer_handle h_obj,const uint8_t* p_data, int32_t n_data)
{
    ringbuffer_t* This = (ringbuffer_t*)h_obj;
    int32_t       ret  = FAILURE;
    int32_t       rest = This->n_buffer - ringbuffer_get_data_size(h_obj);

    if(rest >= n_data)
    {
        int i;
        for (i = 0; i<n_data; i++ )
        {
            if ( This->writeCounter >= This->n_buffer )
            {
                This->writeCounter = 0;
            }
            *(This->p_buffer + This->writeCounter) = *(p_data + i);
            This->writeCounter++;
            This->data_length++;
        }
        ret = SUCCESS;
    }
    return ret;
}

