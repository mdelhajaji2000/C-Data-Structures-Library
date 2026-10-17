#pragma once

#include <stdlib.h>

typedef struct Stack Stack;

typedef enum {
    SS_SUCCESS = 0,
    SS_ALLOCATION_FAILURE = -1,
    SS_DATA_ALLOCATION_FAILURE = -2,
    SS_INVALID_ARGUMENT = -3,
    SS_EMPTY = -4,
    SS_LS_ALLOCATION_FAILURE = -5,
    SS_LS_NODE_ALLOCATION_FAILURE = -6
} StackStatus;

Stack* Stack_Create(size_t element_size);