/**
 * @file   TestSuites.h
 * @author Junsei Takahashi
 * @date   last update 2010-07-23 00:13:21
 *
 * @brief 本ファイルで宣言したもののみを対象にテストを行う。
 */
#ifndef _TESTSUITES_H
#define _TESTSUITES_H
/**
 * 各テストスイートで用いる関数とテストケース配列の宣言
 */

/**
 * util
 */
extern CU_TestInfo test_util_array[];
int setup_test_util();
int teardown_test_util();
/**
 * テストスイート配列
 *
 * @brief テスト実行対象となるテストスイート
 */
static CU_SuiteInfo suites_array[] = {
   {"test_util", setup_test_util, teardown_test_util, test_util_array},
   CU_SUITE_INFO_NULL
};
#endif /* _TESTSUITES_H */
