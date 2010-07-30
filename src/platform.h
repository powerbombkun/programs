/**
 * @file   platform.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-30 22:24:44
 *
 * @brief
 *
 */
#ifndef _PLATFORM_H
#define _PLATFORM_H

/* 構造体メンバの位置までのオフセットを返す */
#define OFFSET_OF(type, member)      ((size_t)&((type*)0)->member)
/* 指定した型のアライメントを返す */
#define ALIGNMENT_OF(type)    OFFSET_OF(struct { char a; type b; }, b)

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief int型のbit数を取得する関数
     *
     * @retval bit数
     */
    int int_bits();
    /**
     * @brief リトルエンディアン環境か判定する関数
     *
     * @retval 1 リトルエンディアン
     *         0 ビッグエンディアン
     */
    int is_little_endian();
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
