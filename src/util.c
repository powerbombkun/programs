#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"

#define MAX_BUFFER_SIZE 128

uint32_t get_file_size(const char* file)
{
    FILE*   fp;
    uint32_t fsize = -1U;

    fp = fopen(file,"rb");
    if(fp != NULL)
    {
        int firstpos = ftell(fp);
        fseek(fp, 0, SEEK_END );
        fsize = ftell(fp);
        fseek(fp, firstpos, SEEK_SET );
        fclose(fp);
    }
    return fsize;
}

uint32_t    get_file_line_num(const char* file)
{
    FILE*   fp;
    uint32_t n_line = -1U;

    fp = fopen(file,"r");
    if(fp != NULL)
    {
        char buf[MAX_BUFFER_SIZE];
        n_line = 0;
        while(fgets(buf,sizeof(buf),fp)) n_line++;
        fclose(fp);
    }
    return n_line;
}

int16_t get_max_amp(const int16_t* p_data,int32_t n_data)
{
    int i;
    int16_t level = 0;
    if(p_data != NULL)
    {
        for(i = 0;i < n_data;i++)
        {
            level = MIN(0x7FFF,MAX(level,abs(p_data[i])));
        }
    }
    return level;
}

const char* get_file_name(const char* file)
{
    const char* pName = NULL;
#ifdef _WIN32
    const char* delim = "\\";
#else
    const char* delim = "/";
#endif
    if(file != NULL)
    {
        int32_t length = strlen(file);
        int i;
        for(i = length;i > 0;i--)
        {
            if(file[i] == *delim)
            {
                pName = &file[i+1];
                break;
            }
        }
    }
    return pName;
}

int32_t split_string(const char* str,const char* separator,char* first,char* second)
{
    int32_t ret = FAILURE;
    const char* p_sep = strstr(str,separator);
    if(p_sep != NULL)
    {
        int n = p_sep - str;
        strncpy(first,str,n);
        first[n] = '\0';
        strcpy(second,++p_sep);
        ret = SUCCESS;
    }
    return ret;
}

char* trim(char* str)
{
    /* 前スペースを除いた先頭を探す */
    while(*str == ' ') str++;
    return str;
}

uint32_t read_from_file(const char* file,void* p_buffer,int32_t size)
{
    uint32_t n = 0;
    FILE* fp;
    fp = fopen(file,"rb");
    if(fp != NULL)
    {
        n = fread(p_buffer,sizeof(uint8_t),size,fp);
        fclose(fp);
    }
    return n;
}

uint32_t write_to_file(const char* file,void* p_data,int32_t size)
{
    uint32_t n = 0;
    FILE* fp;
    fp = fopen(file,"wb");
    if(fp != NULL)
    {
        n = fwrite(p_data,sizeof(uint8_t),size,fp);
        fclose(fp);
    }
    return n;
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
