#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef void*     RingBuffer_Handle;
    /**
     * @brief �����O�o�b�t�@�[�I�u�W�F�N�g�̍\�z
     */
    RingBuffer_Handle RingBuffer_create(uint32_t n_buffer);
    /**
     * @brief �����O�o�b�t�@�[�I�u�W�F�N�g�̏���
     *
     * @param[in] h_obj RingBuffer�I�u�W�F�N�g�n���h��
     *
     */
    void              RingBuffer_delete(RingBuffer_Handle h_obj);
    /**
     * @brief �����O�o�b�t�@�[�̒��g���̂Ă�
     *
     * @param[in] h_obj RingBuffer�I�u�W�F�N�g�n���h��
     *
     */
    void              RingBuffer_initialize(RingBuffer_Handle h_obj);
    /**
     * @brief �����O�o�b�t�@�[���̃f�[�^�T�C�Y���擾���郁�\�b�h
     * @param[in] h_obj RingBuffer�I�u�W�F�N�g�n���h��
     *
     * @retval �f�[�^�T�C�Y
     */
    int32_t           RingBuffer_getDataSize(RingBuffer_Handle h_obj);
    /**
     * @brief �����O�o�b�t�@�[�̃T�C�Y���擾���郁�\�b�h
     * @param[in] h_obj RingBuffer�I�u�W�F�N�g�n���h��
     *
     * @retval �o�b�t�@�[�T�C�Y
     */
    int32_t           RingBuffer_getBufferSize(RingBuffer_Handle h_obj);
    /**
     * @brief �����O�o�b�t�@�[����f�[�^���擾���郁�\�b�h
     *
     * @param[in] h_obj RingBuffer�I�u�W�F�N�g�n���h��
     * @param[in] p_buffer �f�[�^�擾�p�o�b�t�@�[�̃|�C���^
     * @param[in] n_buffer �f�[�^�擾�p�o�b�t�@�[�̃T�C�Y
     *
     * @retval SUCCESS ����
     * @retval FAILED  ���s
     */
    int32_t           RingBuffer_getData(RingBuffer_Handle h_obj,uint8_t* p_buffer, int32_t n_buffer);
    /**
     * @brief �����O�o�b�t�@�[�փf�[�^���Z�b�g���郁�\�b�h
     *
     * @param[in] p_data �f�[�^�ݒ�p�o�b�t�@�[�̃|�C���^
     * @param[in] n_data �f�[�^�ݒ�p�o�b�t�@�[�̃T�C�Y
     *
     * @retval SUCCESS ����
     * @retval FAILED  ���s
     */
    int32_t           RingBuffer_setData(RingBuffer_Handle h_obj,uint8_t* p_data, int32_t n_data);

#ifdef __cplusplus
}
#endif

#endif
