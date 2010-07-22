/**
 * @file   logger.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-22 01:00:04
 *
 * @brief  プログラム実行時にログを出力するための関数の宣言
 *
 */
#ifndef _LOGGER_H
#define _LOGGER_H
#include <stdio.h>
#include "type.h"
#include "macro.h"

#ifdef WIN32
#include <string.h>
#define __file__ (strrchr(__FILE__,'¥¥' ) + 1 )
#else
#define __file__ (__FILE__)
#endif

#define LOG_NONE  (0x0000ul)    /**  出力なし */
#define LOG_FATAL (0x0001ul)    /**  致命的なエラー出力フラグ */
#define LOG_ERROR (0x0002ul)    /** エラー出力フラグ*/
#define LOG_WARN  (0x0004ul)    /**  警告用ログ出力フラグ*/
#define LOG_INFO  (0x0008ul)    /**  トレース用ログ出力フラグ*/


#ifdef __cplusplus
extern "C" {
#endif
    /**
     * ログ出力フラグ
     * 複数設定する時はOR(|)で指定.
     */
    typedef uint32_t logflag_t;
    /**
     * ログ・レベル
     */
    typedef enum {
        LOG_LEVEL_FATAL,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_WARN,
        LOG_LEVEL_INFO,
    } log_level_t;

    /**
     * @brief getter of log_flag
     */
    uint32_t log_getflag(void);
    /**
     * @brief ロガーの初期化.
     *        本関数をコールしなければ(デフォルト)、
     *        stream = stdout、level=LOG_NONEで初期化される.
     *
     * @param[in] stream 出力ストリーム
     * @param[in] flag   ログフラグ.OR(|)で複数指定可能.
     *
     * @retval SUCCESS pass
     * @retval FAILED  failure
     */
    int32_t  log_init(const char* file, uint32_t flag);

    void log_end();

    /**
     * @brief 標準的なログ出力関数
     *
     * @param[in] src_file 本関数をコールしたソースファイル名
     * @param[in] line_no  本関数をコールした行番号
     * @param[in] level    LogLevelで定義されたレベル
     * @param[in] msg      表示する文字列
     */
    void logger( const char* src_file,
                 const int   line_no,
                 log_level_t level,
                 const char* msg);

#ifdef __cplusplus
}
#endif

/**
 * @brief log4infoを簡略したマクロ関数.
 *
 * @param[in] msg メッセージ
 */
#define LOGGER_INFO(msg)  logger(__file__, __LINE__, LOG_LEVEL_INFO, msg)
/**
 * @brief log4warnを簡略したマクロ関数.
 *
 * @param[in] msg メッセージ
 */
#define LOGGER_WARN(msg)  logger(__file__, __LINE__, LOG_LEVEL_WARN, msg)
/**
 * @brief log4errorを簡略したマクロ関数.
 *
 * @param[in] msg メッセージ
 */
#define LOGGER_ERROR(msg) logger(__file__, __LINE__, LOG_LEVEL_ERROR, msg)
/**
 * @brief log4errorを簡略したマクロ関数.
 *
 * @param[in] msg メッセージ
 */
#define LOGGER_FATAL(msg) logger(__file__, __LINE__, LOG_LEVEL_FATAL, msg)


#endif /* _LOGGER_H */

