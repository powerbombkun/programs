/**
 * @file   algorithm.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-31 22:44:16
 *
 * @brief
 *
 */
#ifndef _ALGORITHM_H
#define _ALGORITHM_H
#include "type.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief クイックソートを行う関数。
     *        データを昇順に整列します。
     *
     * @param[in] array   整列対象配列のポインタ
     * @param[in] n       整列対象配列の長さ
     *
     */
    void q_sort(int32_t* array,int32_t n);
    /**
     * @brief バブルソートを行う関数
     *
     * @param[in] array   整列対象配列のポインタ
     * @param[in] n       整列対象配列の長さ
     *
     */
    void b_sort(int32_t* array,int32_t n);
    /**
     * @brief ２分探索処理関数
     *        事前に探索対象配列をソートする必要があります
     *
     * @param[in] array   探索対象配列のポインタ
     * @param[in] n       整列対象配列の長さ
     * @param[in] val     探索対象数値
     *
     * @retval 0以上 配列のインデックス
     * @retval -1    探索対象数値が見つからなかった
     */
    int32_t binary_search(const int32_t* array,int32_t n,int32_t val);

#ifdef __cplusplus
}
#endif

#endif /* _ALGORITHM_H */
