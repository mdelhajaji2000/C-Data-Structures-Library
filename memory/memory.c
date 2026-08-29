#include <stdlib.h>

#include "memory.h"

void* ds_malloc(size_t size)
{
    return malloc(size);
}

void* ds_calloc(size_t count, size_t size)
{
    return calloc(count, size);
}

void* ds_realloc(void* ptr, size_t size)
{
    return realloc(ptr, size);
}

void ds_free(void* ptr)
{
    free(ptr);
}