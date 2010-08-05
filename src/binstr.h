/**
 * @file   binstr.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-05 23:39:19
 *
 * @brief
 *
 */
#ifndef _BINSTR_H
#define _BINSTR_H

#include "type.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief バイナリデータを文字列データに変換する関数。
     *
     * @param[in] p_bin   入力のバイナリデータ
     * @param[in] n_bin   入力のバイナリデータの個数
     * @param[out] p_buffer    出力の文字列データの格納用バッファ
     * @param[in] n_buffer    出力の文字列データの格納用バッファの個数
     *
     * @retval SUCCESS 成功
     *         FAILURE 失敗
     */
    int32_t bin2str(const uint8_t* p_bin,int32_t n_bin,char* p_buffer,int32_t n_buffer);
    /**
     * @brief 文字列データをバイナリデータに変換する関数。
     *
     * @param[in] p_str   入力の文字列データ
     * @param[in] len 入力の文字列データ長
     * @param[out] p_buffer    出力のバイナリデータ格納用バッファ
     * @param[in] n_buffer    出力のバイナリデータ格納用バッファの個数
     *
     * @retval SUCCESS 成功
     *         FAILURE 失敗
     */
    int32_t str2bin(const char* p_str,int32_t len,uint8_t* p_buffer,int32_t n_buffer);

#ifdef __cplusplus
}
#endif

#endif
