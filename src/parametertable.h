/**
 * @file   parametertable.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-10-01 23:05:02
 *
 * @brief
 *
 */
#ifndef _PARAMETERTABLE_H
#define _PARAMETERTABLE_H
#include "type.h"

#define MAX_KEY_SIZE 256

#ifdef __cplusplus
extern "C" {
#endif

    typedef void* ParameterTable_Handle;
    /**
     * @brief パラメーターテーブルオブジェクトの構築
     *
     * @retval NULL以外 オブジェクトハンドル
     * @retval NULL     オブジェクの構築に失敗
     */
    ParameterTable_Handle parametertable_create(int n_key);
    /**
     * @brief パラメーターテーブルオブジェクトの消滅
     *
     * @param[in] h_obj オブジェクトハンドル
     *
     */
    void parametertable_delete(ParameterTable_Handle h_obj);
    /**
     * @brief パラメーターテーブルオブジェクトの初期化
     *
     * @param[in] h_obj オブジェクトハンドル
     *
     */
    void parametertable_initialize(ParameterTable_Handle h_obj);
    /**
     * @brief 内部のパラメーターテーブルへ情報を登録します
     *
     * @param[in] h_obj オブジェクトハンドル
     * @param[in] key   登録するキー
     * @param[in] val   初期値
     *
     * @retval SUCCESS  成功
     * @retval FAILURE  失敗
     */
    int32_t    parametertable_store(ParameterTable_Handle h_obj,
                                    const char*           key,
                                    int32_t               val);

    /**
     * @brief 内部のパラメーターテーブルから値を取得する
     *
     * @param[in] h_obj オブジェクトハンドル
     * @param[in] key   キー
     * @param[out] val   値
     *
     * @retval SUCCESS  成功
     * @retval FAILURE   失敗
     */
    int32_t    parametertable_fetch(ParameterTable_Handle h_obj,
                                      const char*         key,
                                      int32_t*            val);

    /**
     * @brief 内部のパラメーターをファイルへ出力します
     *
     * @param[in] h_obj オブジェクトハンドル
     * @param[in] file  ファイルパス
     *
     * @retval SUCCESS  成功
     * @retval FAILURE  失敗
     */
    int32_t    parametertable_write_file(ParameterTable_Handle h_obj,
                                        const char*           file);

    /**
     * @brief パラメーターをファイルから読み込みます
     *
     * @param[in] h_obj オブジェクトハンドル
     * @param[in] file  ファイルパス
     *
     * @retval SUCCESS  成功
     * @retval FAILURE  失敗
     */
    int32_t    parametertable_read_file(ParameterTable_Handle h_obj,
                                       const char*           file);

#ifdef __cplusplus
}
#endif

#endif                                  /* _PARAMETERTABLE_H */
