#include "..\API\Doubly_Linked_List.h"
#include "..\memory\memory.h"

#include <stdio.h>

#define _D_LIST_STATUS_PRINTER(status, function_name)                         \
    do                                                                        \
    {                                                                         \
        switch (status)                                                       \
        {                                                                     \
        case D_LS_SUCCESS:                                                    \
            fprintf(stderr, "[INFO] at [%s]: SUCCESS\n", function_name);     \
            break;                                                            \
        case D_LS_ALLOCATION_FAILURE:                                        \
            fprintf(stderr, "[ERROR] at [%s]: ALLOCATION FAILURE\n", function_name); \
            break;                                                            \
        case D_LS_DATA_ALLOCATION_FAILURE:                                   \
            fprintf(stderr, "[ERROR] at [%s]: DATA ALLOCATION FAILURE\n", function_name); \
            break;                                                            \
        case D_LS_INVALID_ARGUMENT:                                          \
            fprintf(stderr, "[ERROR] at [%s]: INVALID ARGUMENT\n", function_name); \
            break;                                                            \
        case D_LS_EMPTY:                                                     \
            fprintf(stderr, "[ERROR] at [%s]: LIST IS EMPTY\n", function_name); \
            break;                                                            \
        case D_LS_INDEX_OUT_OF_RANGE:                                        \
            fprintf(stderr, "[ERROR] at [%s]: INDEX OUT OF RANGE\n", function_name); \
            break;                                                            \
        default:                                                              \
            fprintf(stderr, "[ERROR] at [%s]: UNKNOWN LIST STATUS\n", function_name); \
            break;                                                            \
        }                                                                     \
    } while (0)

