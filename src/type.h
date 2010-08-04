/**
 * @file   type.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-04 20:46:35
 *
 * @brief  プログラムの標準型定義
 *
 */
#ifndef _TYPE_H
#define _TYPE_H

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <stdint.h>
#else
typedef unsigned char  uint8_t;
typedef signed char    int8_t;
typedef unsigned short uint16_t;
typedef short          int16_t;
typedef unsigned int   uint32_t;
typedef int            int32_t;
#endif /* defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) */

#ifndef BOOL
#define BOOL int
#endif

#define FALSE 0
#define TRUE 1

#endif /* _TYPE_H */
