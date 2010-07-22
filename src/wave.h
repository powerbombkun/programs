/**
 * @file   wave.h
 * @author Junsei Takahashi
 * @date   last update 2010-07-22 19:33:46
 *
 * @brief  WAVEファイルの処理用関数類
 */
#ifndef _WAVE_H
#define _WAVE_H
#include <stdio.h>
#include "type.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief PCM形式のファイルをWAV形式のファイルに変換します
     *
     * @param[in] pcm_file    PCM形式の入力ファイル
     * @param[in] wav_file    WAV形式の出力ファイル
     * @param[in] ch チャンネル数
     * @param[in] bitspersample ビットレート
     * @param[in] samplingrate サンプリング周波数
     *
     * @retval SUCCESS 成功
     *         FAILED  失敗
     */
    int32_t pcm2wav(const char* pcm_file,
                    const char* wav_file,
                    int16_t     ch,
                    int32_t     bitspersample,
                    int32_t     samplingrate);
    /**
     * @brief WAV形式のファイルをPCM形式のファイルに変換します
     *
     * @param[in] wav_file    WAV形式の入力ファイル
     * @param[in] pcm_file    PCM形式の出力ファイル
     * @param[in] ch チャンネル数
     * @param[in] bitspersample ビットレート
     * @param[in] samplingrate サンプリング周波数
     *
     * @retval SUCCESS 成功
     *         FAILED  失敗
     */
    int32_t wav2pcm(const char* wav_file,
                    const char* pcm_file,
                    int16_t*    ch,
                    int32_t*    bitspersample,
                    int32_t*    samplingrate);

#ifdef __cplusplus
}
#endif


#endif /* _WAVE_H */
