#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef void*     RingBuffer_Handle;
    /**
     * @brief リングバッファーオブジェクトの構築
     */
    RingBuffer_Handle RingBuffer_create(uint32_t n_buffer);
    /**
     * @brief リングバッファーオブジェクトの消滅
     *
     * @param[in] h_obj RingBufferオブジェクトハンドル
     *
     */
    void              RingBuffer_delete(RingBuffer_Handle h_obj);
    /**
     * @brief リングバッファーの中身を捨てる
     *
     * @param[in] h_obj RingBufferオブジェクトハンドル
     *
     */
    void              RingBuffer_initialize(RingBuffer_Handle h_obj);
    /**
     * @brief リングバッファー内のデータサイズを取得するメソッド
     * @param[in] h_obj RingBufferオブジェクトハンドル
     *
     * @retval データサイズ
     */
    int32_t           RingBuffer_getDataSize(RingBuffer_Handle h_obj);
    /**
     * @brief リングバッファーのサイズを取得するメソッド
     * @param[in] h_obj RingBufferオブジェクトハンドル
     *
     * @retval バッファーサイズ
     */
    int32_t           RingBuffer_getBufferSize(RingBuffer_Handle h_obj);
    /**
     * @brief リングバッファーからデータを取得するメソッド
     *
     * @param[in] h_obj RingBufferオブジェクトハンドル
     * @param[in] p_buffer データ取得用バッファーのポインタ
     * @param[in] n_buffer データ取得用バッファーのサイズ
     *
     * @retval SUCCESS 成功
     * @retval FAILED  失敗
     */
    int32_t           RingBuffer_getData(RingBuffer_Handle h_obj,uint8_t* p_buffer, int32_t n_buffer);
    /**
     * @brief リングバッファーへデータをセットするメソッド
     *
     * @param[in] p_data データ設定用バッファーのポインタ
     * @param[in] n_data データ設定用バッファーのサイズ
     *
     * @retval SUCCESS 成功
     * @retval FAILED  失敗
     */
    int32_t           RingBuffer_setData(RingBuffer_Handle h_obj,uint8_t* p_data, int32_t n_data);

#ifdef __cplusplus
}
#endif

#endif
