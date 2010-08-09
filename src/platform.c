#include "platform.h"

int int_bits(void)
{
    int count = 0;
    unsigned int a =~ 0;
    while(a & 1U)
    {
        count++;
        a>>=1;
    }
    return count;
}

int is_little_endian(void)
{
    int32_t a = 1;
    return *(uint8_t*)&a;
}

void byte_reverse(void* data,int n_byte)
{
    uint8_t* low = (uint8_t*)data;
    uint8_t* high = low + n_byte;

    while(--high > low)
    {
        SWAP(uint8_t,*low,*high);
        low++;
    }
}

