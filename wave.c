#include "wave.h"
#include <stdlib.h>
#include <string.h>
#include "macro.h"

int32_t readFileWaveHdr(const char* file,wave_t* p_wave)
{
  FILE*      fp  = NULL;
  int32_t ret = FAILED;

  fp = fopen(file,"rb");
  if(fp != NULL)
  {
    ret = skipWaveHdr(&fp,p_wave);
    fclose(fp);
  }
  return ret;
}

int32_t skipWaveHdr(FILE** p_fp,wave_t* p_wave)
{
  int32_t ret = FAILED;
  char       buff[5] = {0};

  if((*p_fp != NULL) && (p_wave != NULL))
  {
    fread(buff,sizeof(char),4,*p_fp);
    if(strncmp(buff,"RIFF",4) == 0)
    {
      fread(buff,sizeof(char),4,*p_fp);
      fread(buff,sizeof(char),4,*p_fp);
      if(strncmp(buff,"WAVE",4) == 0)
      {
        fread(buff,sizeof(char),4,*p_fp);
        if(strncmp(buff,"fmt ",4) == 0)
        {
          char* p_fmt;
          fread(&p_wave->fmtsize,sizeof(int32_t),1,*p_fp);

          p_fmt = (char*)malloc(p_wave->fmtsize);
          fread(p_fmt,sizeof(char),p_wave->fmtsize,*p_fp);
          p_wave->ch = *(int16_t*)&p_fmt[2];
          p_wave->samplingrate = *(int32_t*)&p_fmt[4];
          p_wave->bitspersample = *(int16_t*)&p_fmt[14];
          free(p_fmt);

          fread(buff,sizeof(char),4,*p_fp);
          if(strncmp(buff,"data",4) == 0)
          {
            fread(&p_wave->datasize,sizeof(int32_t),1,*p_fp);
            ret             = SUCCESS;
          }
        }
      }
    }
  }
  return ret;
}


int32_t writeWaveHdr(FILE** p_fp,wave_t* p_wave)
{
  int32_t ret = FAILED;
  if((*p_fp != NULL) && (p_wave != NULL))
  {
    int32_t i32_buff = 0;
    int16_t i16_buff = 0;

    fwrite("RIFF",sizeof(char),sizeof("RIFF"),*p_fp);
    i32_buff = p_wave->datasize + 44 - 8;
    fwrite("WAVE",sizeof(char),sizeof("WAVE"),*p_fp);
    fwrite("fmt ",sizeof(char),sizeof("fmt "),*p_fp);
    fwrite(&p_wave->fmtsize,sizeof(int32_t),1,*p_fp);
    fwrite(&p_wave->type,sizeof(int16_t),1,*p_fp);
    fwrite(&p_wave->ch,sizeof(int16_t),1,*p_fp);
    fwrite(&p_wave->samplingrate,sizeof(int32_t),1,*p_fp);
    i32_buff = p_wave->samplingrate * p_wave->ch;
    fwrite(&i32_buff,sizeof(int32_t),1,*p_fp);
    i16_buff = sizeof(int16_t);
    fwrite(&i16_buff,sizeof(int16_t),1,*p_fp);
    fwrite(&p_wave->bitspersample,sizeof(int16_t),1,*p_fp);
    fwrite("data",sizeof(char),sizeof("data"),*p_fp);
    fwrite(&p_wave->datasize,sizeof(int32_t),1,*p_fp);

    ret = SUCCESS;
  }
  return ret;
}
