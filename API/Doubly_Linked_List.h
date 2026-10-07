#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct DLinkedList DLinkedList;

typedef enum {
    D_LS_SUCCESS = 0,
    D_LS_ALLOCATION_FAILURE = -1,
    D_LS_DATA_ALLOCATION_FAILURE = -2,
    D_LS_INVALID_ARGUMENT = -3,
    D_LS_EMPTY = -4,
    D_LS_INDEX_OUT_OF_RANGE = -5
} DLinkedListStatus;

