/**
 * @file   fft.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-13 22:53:14
 *
 * @brief
 *
 */
#ifndef _FFT_H
#define _FFT_H
#include "type.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief FFT処理を行う関数
     *
     * @param[in][out] re realパートデータ
     * @param[in][out] im imagパートデータ
     * @param[in] bitsize ビットサイズ
     *
     */
    void fft(double* re,double* im,int32_t     bitsize);
    /**
     * @brief 逆FFT処理を行う関数
     *
     * @param[in][out] re realパートデータ
     * @param[in][out] im imagパートデータ
     * @param[in] bitsize ビットサイズ
     *
     */
    void ifft(double* re,double* im,int32_t     bitsize);
    /**
     * @brief パワースペクトルを計算する関数
     *
     * @param[in] re  realパートデータ
     * @param[in] im  imagパートデータ
     * @param[in] n データ個数
     * @param[out] power   パワースペクトル
     *
     */
    void spectrum(double* re,double* im,int32_t n,double* power);

#ifdef __cplusplus
}
#endif

#endif /* _FFT_H */
