/**
 * @file   dbconv.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-11 23:33:33
 *
 * @brief
 *
 */
#ifndef _DBCONV_H
#define _DBCONV_H
#include "type.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief リニアデータをデシベル値に変換します。
     *
     * @param[in] pow_a  リニアデータA
     * @param[in] pow_b  リニアデータB
     *
     * @retval デシベル値
     */
    double linear2db(int32_t pow_a,int32_t pow_b);
    /**
     * @brief デシベル値をリニアデータに変換します。
     *
     * @param[in] db  デシベル値
     * @param[in] max_linear リニアデータの最大値(この値を0dBとして換算)
     *
     * @retval リニアデータ
     */
    int32_t db2linear(double db,int32_t max_linear);
#ifdef __cplusplus
}
#endif


#endif
