/**
 * @file   type.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-07-29 00:47:16
 *
 * @brief  プログラムの標準型定義
 *
 */
#ifndef _TYPE_H
#define _TYPE_H

#include <stdint.h>
#ifndef _STDINT_H
typedef unsigned char  uint8_t;
typedef signed char    int8_t;
typedef unsigned short uint16_t;
typedef short          int16_t;
typedef unsigned int   uint32_t;
typedef int            int32_t;
#endif

#define FALSE 0
#define TRUE 1

#endif /* _TYPE_H */
