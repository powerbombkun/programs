#include "binstr.h"
#include <stdio.h>
#include <stdlib.h>

#define TOP 0
#define BOTTOM TOP+1

int32_t bin2str(const uint8_t* p_bin,int32_t n_bin,char* p_buffer,int32_t n_buffer)
{
    int i,j;
    int32_t ret = FAILURE;
    if(n_buffer >= (n_bin*2))
    {
        for(i = 0;i < n_bin;i++)
        {
            uint8_t code[2];
            code[TOP] = *p_bin >> 4;
            code[BOTTOM] = 0x0F & *p_bin;
            for(j = 0;j < 2;j++)
            {
                if(code[j] <= 0x09)
                {
                    *p_buffer = code[j] + '0';
                }
                else
                {
                    *p_buffer = code[j] + 'A' - 0x0A;
                }
                p_buffer++;
            }
            p_bin++;
        }
        ret = SUCCESS;
    }
    return ret;
}

int32_t str2bin(const char* p_str,int32_t len,uint8_t* p_buffer,int32_t n_buffer)
{
    int i,j;
    int32_t ret = FAILURE;
    if(n_buffer >= (len/2))
    {
        for(i = 0;i < (len/2);i++)
        {
            int code[2];
            for(j = 0;j < 2;j++)
            {
                if('A' <= *p_str && *p_str <= 'F')
                {
                    code[j] = *p_str - 'A' + 10;
                }
                else if('a' <= *p_str && *p_str <= 'f')
                {
                    code[j] = *p_str - 'a' + 10;
                }
                else if('0' <= *p_str && *p_str <= '9')
                {
                    code[j] = *p_str - '0';
                }
                else
                {
                    /** その他の文字に関しては0で埋める */
                    code[j] = 0x00;
                }
                p_str++;
            }
            *p_buffer++ = (uint8_t)(code[TOP]*16+code[BOTTOM]);
        }
        ret = SUCCESS;
    }
    return ret;
}
