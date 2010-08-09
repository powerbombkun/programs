#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 128

uint32_t getFileSize(const char* file)
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

uint32_t    getFileLineNum(const char* file)
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

int16_t getMaxAmp(const int16_t* p_data,int32_t n_data)
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

const char* getFileName(const char* file)
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

int32_t splitString(const char* str,const char* separator,char* first,char* second)
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


