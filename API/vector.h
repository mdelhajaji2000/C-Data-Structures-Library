#pragma once


#include <stddef.h>
#include "..\memory\memory.h"

typedef struct Vector Vector;

size_t Vector_GetSize(const Vector *v);

size_t Vector_GetCapacity(const Vector *v);

size_t Vector_GetElementSize(const Vector *v);

Vector *Vector_Create(size_t size, size_t element_size);

void *Vector_GetAt(Vector *v, size_t index);