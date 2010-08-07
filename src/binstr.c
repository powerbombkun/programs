#include "binstr.h"
#include <stdio.h>
#include <stdlib.h>

int32_t bin2str(const uint8_t* p_bin,int32_t n_bin,char* p_buffer,int32_t n_buffer)
{
    int i;
    int32_t ret = FAILURE;
    if(n_buffer > (n_bin*2))
    {
        for(i = 0;i < n_bin;i++)
        {
            sprintf(p_buffer++,"%x",((p_bin[i] & 0xF0)>> 4));
            sprintf(p_buffer++,"%x",(0x0F & p_bin[i]));
        }
        ret = SUCCESS;
    }
    return ret;
}

int32_t str2bin(const char* p_str,int32_t len,uint8_t* p_buffer,int32_t n_buffer)
{
    int i;
    int32_t ret = FAILURE;
    if(n_buffer >= (len/2))
    {
        for(i = 0;i < (len/2);i++)
        {
            char s[] = {p_str[2*i],p_str[2*i+1]};
            *p_buffer++ = strtol(s,NULL,16);
        }
        ret = SUCCESS;
    }
    return ret;
}
