/**
 * @file   common.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-09-27 21:51:20
 *
 * @brief  標準関数のラッパー関数
 *
 */
#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief malloc関数のラッパー関数
     *
     * @param[in] size    確保するメモリーサイズ
     *
     * @retval 成功 確保したメモリーのポインタ
     * @retval 失敗 NULL
     */
    void* x_malloc(size_t size);
    /**
     * @brief free関数のラッパー関数
     *
     * @param[in] ptr    開放するメモリーのポインタ
     *
     */
    void x_free(void* ptr);

#define SAFE_FREE(p)  { if(p) x_free(p); p = NULL; }

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H */
