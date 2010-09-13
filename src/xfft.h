/**
 * @file   xfft.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-09-13 22:57:02
 *
 * @brief
 *
 */
#ifndef _XFFT_H
#define _XFFT_H
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief FFT処理を行う関数
     *        1 << bitsize 分のデータがre,imそれぞれで必要
     *
     * @param[in] p_data データポインタ
     * @param[in] n_data データの個数
     * @param[out] re realパートデータ
     * @param[out] im imagパートデータ
     * @param[in] bitsize ビットサイズ
     *
     */
    void xfft(int16_t* p_data,int32_t n_data,double* re,double* im,int32_t     bitsize);
    /**
     * @brief 逆FFT処理を行う関数
     *        1 << bitsize 分のデータがre,imそれぞれで必要
     *
     * @param[in] re realパートデータ
     * @param[in] im imagパートデータ
     * @param[in] p_buffer バッファポインタ
     * @param[in] n_buffer バッファの個数
     * @param[in] bitsize ビットサイズ
     *
     */
    void xifft(double* re,double* im,int16_t* p_buffer,int32_t n_buffer,int32_t     bitsize);
    /**
     * @brief スペクトルを計算します
     *
     * @param[in] p_data データポインタ
     * @param[in] n_data データの個数
     * @param[out] p_spectrum スペクトルデータ
     * @param[in] bitsize ビットサイズ
     *
     * @retval SUCCESS 成功
     *         FAILURE 失敗
     *
     */
    int32_t xspectrum(int16_t* p_data,int32_t n_data,double* p_spectrum,int32_t     bitsize);

#ifdef __cplusplus
}
#endif

#endif /* _XFFT_H */




