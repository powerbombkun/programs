/**
 * @file   macro.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-22 19:56:17
 *
 * @brief  汎用マクロ集
 *
 */
#ifndef _MACRO_H
#define _MACRO_H

#define ARRAY_SIZE(A)        (sizeof(A)/sizeof(A[0]))
#define MAX(x, y)            ((x) >= (y) ? (x) : (y))
#define MIN(x, y)            ((x) <= (y) ? (x) : (y))
#define ABS(x)               ((x) < 0 ? (-(x)) : (x))
#define SUCCESS              0
#define FAILED               -1
#define MAX_FILE_PATH_LENGTH 1024

#define MAIN main

#endif /* _MACRO_H */
