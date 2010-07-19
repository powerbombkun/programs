/**
 * @file   util.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-20 02:17:10
 *
 * @brief  �ėp�֐���
 *
 */
#ifndef _UTIL_H
#define _UTIL_H
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif
  /**
   * @brief �t�@�C���T�C�Y�擾�֐�
   * @param[in] file	�t�@�C���p�X
   * @retval 0�ȏ� �t�@�C���T�C�Y
   * @retval -1 �G���[
   */
  uint32_t getFileSize(const char* file);
  /**
   * @brief �ő�U�����x���擾�֐�
   * @param[in] pData �����t��16bit�f�[�^
   * @param[in] nData 16bit�f�[�^��
   * @retval �ő�U�����x��
   */
  int16_t getMaxAmp(const int16_t* p_data,int32_t n_data);
  /**
   * @brief �t�@�C�����̎擾
   *
   * @param[in] file �t�@�C���p�X
   *
   * @retval �t�@�C����������
   */
  const char* getFileName(const char* file);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_H */
