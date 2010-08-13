/**
 * @file   xfft.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-14 01:44:57
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
     *        n個数分のバッファがre,imそれぞれで必要
     *
     * @param[in] p_data  データポインタ
     * @param[in] n  データ個数
     * @param[out] re realパートデータ
     * @param[out] im imagパートデータ
     * @param[in] bitsize ビットサイズ
     *
     */
    void xfft(int16_t* p_data,int32_t n,double* re,double* im,int32_t bitsize);
    /**
     * @brief IFFT処理を指定したデータ個数で行う関数
     *
     * @param[in] re realパートデータ
     * @param[in] im imagパートデータ
     * @param[out] p_data  データポインタ
     * @param[in] n  データ個数
     * @param[in] bitsize ビットサイズ
     *
     */
    void xifft(double* re,double* im,int16_t* p_buffer,int32_t n,int32_t bitsize);


#ifdef __cplusplus
}
#endif

#endif /* _XFFT_H */
