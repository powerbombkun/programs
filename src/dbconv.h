/**
 * @file   dbconv.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-05 23:16:24
 *
 * @brief
 *
 */
#ifndef _DBCONV_H
#define _DBCONV_H
#include "type.h"
#include "macro.h"
/**
 * @brief 符号付き16bitのリニアデータをデシベル値に変換します。
 *        デシベル値に関しては符号付き16bitリニアデータの最大値を0dBとして計算。
 *
 * @param[in] linear  リニアデータ
 *
 * @retval デシベル値
 */
float linear2db(int16_t linear);
/**
 * @brief デシベル値を符号付き16bitリニアデータに変換します。
 *
 * @param[in] db  デシベル値
 *
 * @retval リニアデータ
 */
int16_t db2linear(float db);

#endif
