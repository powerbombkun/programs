/**
 * @file   xfft.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-13 23:01:05
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
     * @brief FFT処理を指定したデータ個数で行う関数
     *
     * @param[in] p_data  データポインタ
     * @param[in] n_data  データ個数
     * @param[out] re realパートデータ
     * @param[out] im imagパートデータ
     * @param[in] bitsize ビットサイズ
     *
     */
    void fftFrame(int16_t* p_data,int32_t n_data,double* re,double* im,int32_t bitsize);
    /**
     * @brief IFFT処理を指定したデータ個数で行う関数
     *
     * @param[in] re realパートデータ
     * @param[in] im imagパートデータ
     * @param[out] p_data  データポインタ
     * @param[in] n_data  データ個数
     * @param[in] bitsize ビットサイズ
     *
     */
    void ifftFrame(double* re,double* im,int16_t* p_buffer,int32_t n_buffer,int32_t bitsize);

#ifdef __cplusplus
}
#endif

#endif /* _XFFT_H */
