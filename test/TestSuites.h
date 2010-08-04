/**
 * @file   TestSuites.h
 * @author Junsei Takahashi
 * @date   last update 2010-08-04 22:47:38
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
 * ringbuffer
 */
extern CU_TestInfo test_ringbuffer_array[];
int setup_test_ringbuffer();
int teardown_test_ringbuffer();
/**
 * parametertable
 */
extern CU_TestInfo test_parametertable_array[];
int setup_test_parametertable();
int teardown_test_parametertable();
/**
 * platform
 */
extern CU_TestInfo test_platform_array[];
int setup_test_platform();
int teardown_test_platform();
/**
 * algorithm
 */
extern CU_TestInfo test_algorithm_array[];
int setup_test_algorithm();
int teardown_test_algorithm();

/**
 * テストスイート配列
 *
 * @brief テスト実行対象となるテストスイート
 */
static CU_SuiteInfo suites_array[] = {
   {"test_util", setup_test_util, teardown_test_util, test_util_array},
   {"test_ringbuffer", setup_test_ringbuffer, teardown_test_ringbuffer, test_ringbuffer_array},
   {"test_parametertable", setup_test_parametertable, teardown_test_parametertable, test_parametertable_array},
   {"test_platform", setup_test_platform, teardown_test_platform, test_platform_array},
   {"test_algorithm", setup_test_algorithm, teardown_test_algorithm, test_algorithm_array},

   CU_SUITE_INFO_NULL
};
#endif /* _TESTSUITES_H */
