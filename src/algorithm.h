/**
 * @file   algorithm.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-05 00:01:23
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
     * @param[in] left    整列対象の左端のインデックス
     * @param[in] right   整列対象の右端のインデックス
     *
     */
    void quick_sort(int32_t* array,int32_t left,int32_t right);

#ifdef __cplusplus
}
#endif

#endif /* _ALGORITHM_H */
