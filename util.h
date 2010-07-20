/**
 * @file   util.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-20 21:59:21
 *
 * @brief  汎用関数類
 *
 */
#ifndef _UTIL_H
#define _UTIL_H
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief ファイルサイズ取得関数
     * @param[in] file	ファイルパス
     * @retval 0以上 ファイルサイズ
     * @retval -1 エラー
     */
    uint32_t    getFileSize(const char* file);
    /**
     * @brief 最大振幅レベル取得関数
     * @param[in] pData 符号付き16bitデータ
     * @param[in] nData 16bitデータ個数
     * @retval 最大振幅レベル
     */
    int16_t     getMaxAmp(const int16_t* p_data,int32_t n_data);
    /**
     * @brief ファイル名の取得
     *
     * @param[in] file ファイルパス
     *
     * @retval ファイル名文字列
     */
    const char* getFileName(const char* file);
    /**
     * @brief 文字列をseparatorで指定した文字で分割します
     *
     * @param[in] str 入力文字列
     * @param[in] separator 分割文字列
     * @param[out] first １つ目の文字列
     * @param[out] second ２つ目の文字列
     *
     */
    void splitString(const char* str,const char* separator,char* first,char* second);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_H */
