/**
 * @file   macro.h
 * @author Junsei Takahashi
 *
 * @date   last update 2010-08-06 23:18:28
 *
 * @brief  汎用マクロ集
 *
 */
#ifndef _MACRO_H
#define _MACRO_H

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A) (sizeof(A)/sizeof(A[0]))
#endif

#ifndef MAX
#define MAX(x, y)            ((x) >= (y) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x, y)            ((x) <= (y) ? (x) : (y))
#endif

#ifndef ABS
#define ABS(x) ((x) < 0 ? (-(x)) : (x))
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

#ifndef MAIN
#define MAIN                 main
#endif

#define MAX_FILE_PATH_LENGTH 1024

#define SWAP(type,a,b) { type temp = a; a = b; b = temp; }

#define SAFE_FREE(p)  { if(p) free(p); p = NULL; }

#endif /* _MACRO_H */
