/**
 * @file   parametertable.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-25 21:20:30
 *
 * @brief
 *
 */
#ifndef _PARAMETERTABLE_H
#define _PARAMETERTABLE_H
#include "type.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef void* ParameterTable_Handle;
    /**
     * @brief �p�����[�^�[�e�[�u���I�u�W�F�N�g�̍\�z
     *
     * @retval �I�u�W�F�N�g�n���h��
     */
    ParameterTable_Handle ParameterTable_create();
    /**
     * @brief �p�����[�^�[�e�[�u���I�u�W�F�N�g�̏���
     *
     * @param[in] h_obj �I�u�W�F�N�g�n���h��
     *
     */
    void ParameterTable_delete(ParameterTable_Handle h_obj);
    /**
     * @brief �p�����[�^�[�e�[�u���I�u�W�F�N�g�̏�����
     *
     * @param[in] h_obj �I�u�W�F�N�g�n���h��
     *
     */
    void ParameterTable_initialize(ParameterTable_Handle h_obj);
    /**
     * @brief �����̃p�����[�^�[�e�[�u���֏���o�^���܂�
     *
     * @param[in] h_obj �I�u�W�F�N�g�n���h��
     * @param[in] key   �o�^����L�[
     * @param[in] val   �����l
     *
     * @retval SUCCESS  ����
     *         FAILED   ���s
     */
    int32_t    ParameterTable_entry(ParameterTable_Handle h_obj,
                                    const char*           key,
                                    int32_t               val);

    /**
     * @brief �����̃p�����[�^�[�e�[�u���֒l��ݒ肷��
     *
     * @param[in] h_obj �I�u�W�F�N�g�n���h��
     * @param[in] key   �L�[
     * @param[in] val   �l
     *
     * @retval SUCCESS  ����
     *         FAILED   ���s
     */
    int32_t    ParameterTable_setData(ParameterTable_Handle h_obj,
                                      const char*           key,
                                      int32_t               val);

    /**
     * @brief �����̃p�����[�^�[�e�[�u������l���擾����
     *
     * @param[in] h_obj �I�u�W�F�N�g�n���h��
     * @param[in] key   �L�[
     * @param[out] val   �l
     *
     * @retval SUCCESS  ����
     *         FAILED   ���s
     */
    int32_t    ParameterTable_getData(ParameterTable_Handle h_obj,
                                      const char*           key,
                                      int32_t*              val);

    /**
     * @brief �����̃p�����[�^�[���t�@�C���֏o�͂��܂�
     *
     * @param[in] h_obj �I�u�W�F�N�g�n���h��
     * @param[in] file  �t�@�C���p�X
     *
     * @retval SUCCESS  ����
     *         FAILED   ���s
     */
    int32_t    ParameterTable_writeFile(ParameterTable_Handle h_obj,
                                        const char*           file);

    /**
     * @brief �p�����[�^�[���t�@�C������ǂݍ��݂܂�
     *
     * @param[in] h_obj �I�u�W�F�N�g�n���h��
     * @param[in] file  �t�@�C���p�X
     *
     * @retval SUCCESS  ����
     *         FAILED   ���s
     */
    int32_t    ParameterTable_readFile(ParameterTable_Handle h_obj,
                                       const char*           file);

#ifdef __cplusplus
}
#endif




#endif                                  /* _PARAMETERTABLE_H */
