/**
 * @file   util.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-23 22:49:18
 *
 * @brief  汎用関数類
 *
 */
#ifndef _UTIL_H
#define _UTIL_H
#include "type.h"
#include "macro.h"

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
     * @brief ファイルの行数を取得します
     * @param[in] file	ファイルパス
     * @retval 0以上 行数
     * @retval -1 エラー
     */
    uint32_t    getFileLineNum(const char* file);
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
     * @retval SUCCESS 成功
     * @retval FAILURE 失敗
     *
     */
    int32_t splitString(const char* str,const char* separator,char* first,char* second);
    /**
     * @brief 文字列の頭の空白を削除した位置のポインタを返します
     *
     * @param[in] str 編集対象文字列
     *
     * @retval 編集後の文字列ポインタ
     */
    char* trim(char* str);
    /**
     * @brief ファイルからデータを取得します
     *
     * @param[in] file ファイル名
     * @param[ou] p_buffer　データ取得用バッファ
     * @param[in] size　バッファサイズ
     *
     * @retval　取得したデータサイズ
     */
    uint32_t readFromFile(const char* file,void* p_buffer,int32_t size);
    /**
     * @brief　ファイルへデータを書き込みます
     *
     * @param[in] file ファイル名
     * @param[ou] p_buffer　書き込みデータ
     * @param[in] size　データサイズ
     *
     * @retval　書き込んだデータサイズ
     */
    uint32_t writeToFile(const char* file,void* p_data,int32_t size);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_H */
