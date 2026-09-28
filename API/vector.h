#pragma once

#include <stddef.h>

typedef enum
{
    VECTOR_SUCCESS = 0,
    VECTOR_ALLOCATION_FAILURE = -1,
    VECTOR_DATA_ALLOCATION_FAILURE = -2,
    VECTOR_INVALID_ARGUMENT = -3,
    VECTOR_INDEX_OUT_OF_RANGE = -4,
    VECTOR_REALLOCATION_FAILURE = -5,
    VECTOR_SIZE_OVERFLOW = -6
} VectorStatus;

typedef struct Vector Vector;

size_t Vector_GetSize(const Vector *v);
size_t Vector_GetCapacity(const Vector *v);
size_t Vector_GetElementSize(const Vector *v);

Vector *Vector_Create(size_t capacity, size_t element_size);
void *Vector_GetAt(Vector *v, size_t index);
VectorStatus Vector_SetAt(Vector *v, size_t index, void *value);
VectorStatus Vector_PushBack(Vector *v, void *value);
void Vector_Clear(Vector *v);
