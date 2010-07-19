/**
 * @file   util.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-20 01:38:03
 *
 * @brief  プログラムで使用する汎用関数類
 *
 */
#ifndef _UTIL_H
#define _UTIL_H
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif
  /**
   * @brief ファイルサイズを取得する関数
   * @param[in] file	ファイルパス
   * @retval 0以上 ファイルサイズ
   * @retval -1 エラー
   */
  uint32_t getFileSize(const char* file);
  /**
   * @brief 最大振幅レベルを取得する関数
   * @param[in] pData 音声データ
   * @param[in] nData 音声データのサンプル数
   * @retval 最大振幅レベル
   */
  int16_t getMaxAmp(const int16_t* p_data,int32_t n_data);
  /**
   * @brief ファイル名を取得します
   *
   * @param[in] file_path ファイルのフルパス
   *
   * @retval ファイル名の文字列
   */
  const char* getFileName(const char* file);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_H */
