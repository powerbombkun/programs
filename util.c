#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t get_file_size(const char* file)
{
    FILE*   fp;
    uint32_t fsize = 0;

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

void split_string(const char* str,const char* separator,char* first,char* second)
{
    const char* p_sep = strstr(str,separator);
    int n = p_sep - str;
    strncpy(first,str,n);
    first[n] = '\0';
    strcpy(second,++p_sep);
}
