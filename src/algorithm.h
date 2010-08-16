/**
 * @file   algorithm.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-16 23:46:25
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

#ifdef __cplusplus
}
#endif

#endif /* _ALGORITHM_H */
