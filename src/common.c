#include "common.h"

void* x_malloc(size_t size)
{
    return malloc(size);
}

void x_free(void* ptr)
{
    free(ptr);
}
