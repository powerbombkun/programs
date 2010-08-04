#include "platform.h"

int int_bits()
{
    int count = 0;
    unsigned int a =~ 0;
    while(a & 1)
    {
        count++;
        a>>=1;
    }
    return count;
}

int is_little_endian()
{
    int32_t a = 1;
    return *(uint8_t*)&a;
}

void byte_reverse(void* data,int n_byte)
{
    uint8_t* low = (uint8_t*)data;
    uint8_t* high = low + n_byte;
    uint8_t temp;

    while(--high > low)
    {
        temp = *low;
        *low++ = *high;
        *high = temp;
    }
}

