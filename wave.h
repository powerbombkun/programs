/**
 * @file   wave.h
 * @author Junsei Takahashi
 * @date   last update 2010-07-20 21:48:31
 *
 * @brief  WAVEファイルの処理用関数類
 */
#ifndef _WAVE_H
#define _WAVE_H
#include <stdio.h>
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct{
    int32_t fmtsize;                 /*  */
    int16_t ch;                      /*  */
    int16_t type;                    /*  */
    int32_t bitspersample;           /*  */
    int32_t samplingrate;            /*  */
    int32_t datasize;                /*  */
  }wave_t;
  /**
   * @brief ファイルからWAVEヘッダー情報を読み込みます
   *
   * @param[in] file 入力ファイル
   * @param[out] pWAVE wave_t型構造体のポインタ
   *
   * @retval
   */
  int32_t readFileWaveHdr(const char* file,wave_t* p_wave);
  /**
   * @brief WAVEヘッダーのファイルポインタを進めます
   *
   * @param[in] pfp FILEポインタのポインタ
   * @param[out] pWAVE wave_t型構造体のポインタ
   *
   * @retval
   */
  int32_t skipWaveHdr(FILE** p_fp,wave_t* p_wave);
  /**
   * @brief WAVEヘッダーを書き込みます
   *
   * @param[in] pfp FILEポインタのポインタ
   * @param[in] pWAVE wave_t型構造体のポインタ
   *
   * @retval
   */
  int32_t writeWaveHdr(FILE** p_fp,wave_t* p_wave);

#ifdef __cplusplus
}
#endif


#endif /* _WAVE_H */
