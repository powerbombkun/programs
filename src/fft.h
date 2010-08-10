/**
 * @file   fft.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-10 23:11:38
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
    void fft(double* re,double* im,int     bitsize);

#ifdef __cplusplus
}
#endif

#endif /* _FFT_H */
