#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "logger.h"
#include "macro.h"
/*
 * define
 */
#define MAX_SIZE_OF_LOG_BUFFER 1024
/*
 * static values
 */
/**
 * ���O�̏o�̓X�g���[��
 */
static FILE*        log_stream = NULL;
/**
 * ���O�o�̓t���O (default)
 */
static unsigned int log_flag   = LOG_NONE;
/**
 * @brief getter of log_flag
 */
uint32_t
log_getflag(void)
{
    return log_flag;
}


/**
 * @brief ���K�[�̏�����.
 *        �{�֐����R�[�����Ȃ����(�f�t�H���g)�A
 *        stream = stdout�Alevel=LOG_NONE�ŏ����������.
 *
 * @param[in] stream �o�̓X�g���[��
 * @param[in] flag   ���O�t���O.OR(|)�ŕ����w��\.
 *
 * @retval true  pass
 * @retval false failure
 */
int32_t log_init(const char* file, uint32_t flag)
{
    if(file != NULL)
    {
        log_stream = fopen(file,"w");
        if(log_stream == NULL){
            return 1;
        }
    }
    log_flag = flag;

    return 0;
}



void
log_end()
{
    if(log_stream != NULL)
    {
        fclose(log_stream);
    }
}

/**
 * @brief �W���I�ȃ��O�o�͊֐�
 *
 * @param[in] src_file �{�֐����R�[�������\�[�X�t�@�C����
 * @param[in] line_no  �{�֐����R�[�������s�ԍ�
 * @param[in] level    LogLevel�Œ�`���ꂽ���x��
 * @param[in] fmt      ����
 * @param[in] ...      �ψ������X�g
 */
void logger( const char* src_file,
             const int   line_no,
             log_level_t level,
             const char* msg)
{
    const char* level_string;
    logflag_t   level_flag = LOG_NONE;

    if(msg == NULL){
        LOGGER_FATAL("fmt is NULL!!");
        return;
    }
    if(log_stream == NULL){
        log_stream = stdout;
    }
    switch(level){
    case LOG_LEVEL_FATAL:
        level_flag   = LOG_FATAL;
        level_string = "FATAL";
        break;
    case LOG_LEVEL_ERROR:
        level_flag   = LOG_ERROR;
        level_string = "ERROR";
        break;
    case LOG_LEVEL_WARN:
        level_flag   = LOG_WARN;
        level_string = "WARN ";
        break;
    case LOG_LEVEL_INFO:
        level_flag   = LOG_INFO;
        level_string = "INFO ";
        break;
    default:
        LOGGER_FATAL("logger bug!!");
        return;
    }
    if(log_flag & level_flag)
    {
        fprintf(log_stream, "[%s] %s#%d - %s\n", level_string, src_file, line_no ,msg );
    }
}

