#pragma once


#include <stddef.h>
#include "memory\memory.h"

typedef struct Vector Vector;

Vector *Create_Vector(size_t size, size_t element_size);

void *Get_At(size_t index);