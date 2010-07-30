#include "platform.h"

int int_bits()
{
    int count = 0;
    unsigned int a =~ 0;
    while(a)
    {
        if(a & 1) count++;
        a >>= 1;
    }
    return count;
}

int is_little_endian()
{
    int a = 1;
    return *(char*)&a;
}

void byte_reverse(void* data,int n_byte)
{
    unsigned char *low = (unsigned char*)data;
    unsigned char *high = low + n_byte;
    unsigned char temp;

    while(--high > low) {
        // *low と *high を交換する．
        temp = *low;
        *low++ = *high;
        *high = temp;
    }
}

