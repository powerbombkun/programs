/**
 * @file   xfft.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-11 23:20:15
 *
 * @brief
 *
 */
#ifndef _XFFT_H
#define _XFFT_H
#include "type.h"
#include "macro.h"
#include "fft.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief FFT処理を行う関数
     *
     * @param[in] p_data  データポインタ
     * @param[in] n_data  データ個数
     * @param[out] re realパートデータ
     * @param[out] im imagパートデータ
     * @param[in] bitsize ビットサイズ
     *
     */
    void fft_frame(short* p_data,int n_data,double* re,double* im,int bitsize);

#ifdef __cplusplus
}
#endif

#endif /* _XFFT_H */
