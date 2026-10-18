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
    SS_LS_NODE_ALLOCATION_FAILURE = -6,
    SS_LS_INDEX_OUT_OF_RANGE = -7,
    SS_INTERNAL_ERROR = -8
} StackStatus;

StackStatus Stack_Create(size_t element_size, Stack **out_stack);
StackStatus Stack_Destroy(Stack *stack);
