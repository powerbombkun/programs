/**
 * @file   ringbuffer.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-10-01 23:14:01
 *
 * @brief
 *
 */
#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef void*     ringbuffer_handle;
    /**
     * @brief リングバッファーオブジェクトの構築
     *
     * @retval NULL以外 オブジェクトハンドル
     * @retval NULL     オブジェクの構築に失敗
     */
    ringbuffer_handle ringbuffer_create(uint32_t n_buffer);
    /**
     * @brief リングバッファーオブジェクトの消滅
     *
     * @param[in] h_obj ringbufferオブジェクトハンドル
     *
     */
    void              ringbuffer_delete(ringbuffer_handle h_obj);
    /**
     * @brief リングバッファーの中身を捨てる
     *
     * @param[in] h_obj ringbufferオブジェクトハンドル
     *
     */
    void              ringbuffer_initialize(ringbuffer_handle h_obj);
    /**
     * @brief リングバッファー内のデータサイズを取得するメソッド
     *
     * @param[in] h_obj ringbufferオブジェクトハンドル
     *
     * @retval データサイズ
     */
    int32_t           ringbuffer_get_data_size(ringbuffer_handle h_obj);
    /**
     * @brief リングバッファーのサイズを取得するメソッド
     *
     * @param[in] h_obj ringbufferオブジェクトハンドル
     *
     * @retval バッファーサイズ
     */
    int32_t           ringbuffer_get_buffer_size(ringbuffer_handle h_obj);
    /**
     * @brief リングバッファーからデータを取得するメソッド
     *
     * @param[in] h_obj ringbufferオブジェクトハンドル
     * @param[in] p_buffer データ取得用バッファーのポインタ
     * @param[in] n_buffer データ取得用バッファーのサイズ
     *
     * @retval SUCCESS 成功
     * @retval FAILURE 失敗
     */
    int32_t           ringbuffer_get_data(ringbuffer_handle h_obj,uint8_t* p_buffer, int32_t n_buffer);
    /**
     * @brief リングバッファーへデータをセットするメソッド
     *
     * @param[in] h_obj ringbufferオブジェクトハンドル
     * @param[in] p_data データ設定用バッファーのポインタ
     * @param[in] n_data データ設定用バッファーのサイズ
     *
     * @retval SUCCESS 成功
     * @retval FAILURE 失敗
     */
    int32_t           ringbuffer_set_data(ringbuffer_handle h_obj,const uint8_t* p_data, int32_t n_data);

#ifdef __cplusplus
}
#endif

#endif
