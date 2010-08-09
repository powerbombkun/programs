/**
 * @file   platform.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-09 20:24:47
 *
 * @brief
 *
 */
#ifndef _PLATFORM_H
#define _PLATFORM_H
#include "type.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 構造体メンバの位置までのオフセットを返す */
#define OFFSET_OF(type, member)      ((size_t)&((type*)0)->member)
/* 指定した型のアライメントを返す */
#define ALIGNMENT_OF(type)    OFFSET_OF(struct { char a; type b; }, b)

    /**
     * @brief int型のbit数を取得する関数
     *
     * @retval bit数
     */
    int int_bits(void);
    /**
     * @brief リトルエンディアン環境か判定する関数
     *
     * @retval 1 リトルエンディアン
     *         0 ビッグエンディアン
     */
    int is_little_endian(void);
    /**
     * @brief ビット反転を行う関数
     *
     * @param[in] data   データのポインタ
     * @param[in] n_byte データ個数
     *
     */
    void byte_reverse(void* data,int n_byte);



#ifdef __cplusplus
}
#endif

#endif /* _PLATFORM_H */
