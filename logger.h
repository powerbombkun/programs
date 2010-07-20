/**
 * @file   logger.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-20 22:40:36
 *
 * @brief  �v���O�������s���Ƀ��O���o�͂��邽�߂̊֐��̐錾
 *
 */
#ifndef _LOGGER_H
#define _LOGGER_H
#include <stdio.h>
#include "type.h"

#ifdef WIN32
#include <string.h>
#define __file__ (strrchr(__FILE__,'\\' ) + 1 )
#else
#define __file__ (__FILE__)
#endif

#define LOG_NONE  (0x0000ul)    /**  �o�͂Ȃ� */
#define LOG_FATAL (0x0001ul)    /**  �v���I�ȃG���[�o�̓t���O */
#define LOG_ERROR (0x0002ul)    /** �G���[�o�̓t���O*/
#define LOG_WARN  (0x0004ul)    /**  �x���p���O�o�̓t���O*/
#define LOG_INFO  (0x0008ul)    /**  �g���[�X�p���O�o�̓t���O*/


#ifdef __cplusplus
extern "C" {
#endif
    /**
     * ���O�o�̓t���O
     * �����ݒ肷�鎞��OR(|)�Ŏw��.
     */
    typedef uint32_t logflag_t;
    /**
     * ���O�E���x��
     */
    typedef enum {
        LOG_LEVEL_FATAL,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_WARN,
        LOG_LEVEL_INFO,
    } log_level_t;

    /**
     * @brief getter of log_flag
     */
    uint32_t log_getflag(void);
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
    int32_t  log_init(const char* file, uint32_t flag);

    void log_end();

    /**
     * @brief �W���I�ȃ��O�o�͊֐�
     *
     * @param[in] src_file �{�֐����R�[�������\�[�X�t�@�C����
     * @param[in] line_no  �{�֐����R�[�������s�ԍ�
     * @param[in] level    LogLevel�Œ�`���ꂽ���x��
     * @param[in] msg      �\�����镶����
     */
    void logger( const char* src_file,
                 const int   line_no,
                 log_level_t level,
                 const char* msg);

#ifdef __cplusplus
}
#endif

/**
 * @brief log4info���ȗ������}�N���֐�.
 *
 * @param[in] msg ���b�Z�[�W
 */
#define LOGGER_INFO(msg)  logger(__file__, __LINE__, LOG_LEVEL_INFO, msg)
/**
 * @brief log4warn���ȗ������}�N���֐�.
 *
 * @param[in] msg ���b�Z�[�W
 */
#define LOGGER_WARN(msg)  logger(__file__, __LINE__, LOG_LEVEL_WARN, msg)
/**
 * @brief log4error���ȗ������}�N���֐�.
 *
 * @param[in] msg ���b�Z�[�W
 */
#define LOGGER_ERROR(msg) logger(__file__, __LINE__, LOG_LEVEL_ERROR, msg)
/**
 * @brief log4error���ȗ������}�N���֐�.
 *
 * @param[in] msg ���b�Z�[�W
 */
#define LOGGER_FATAL(msg) logger(__file__, __LINE__, LOG_LEVEL_FATAL, msg)


#endif /* _LOGGER_H */

