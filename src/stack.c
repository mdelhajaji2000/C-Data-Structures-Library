#include "..\memory\memory.h"
#include "..\API\linked_list.h"
#include <stdio.h>

#include "..\API\stack.h"

#define _STACK_STATUS_PRINTER(status, function_name)                       \
    do                                                                     \
    {                                                                      \
        switch (status)                                                    \
        {                                                                  \
        case SS_SUCCESS:                                                   \
            fprintf(stderr, "[INFO] at [%s]: SUCCESS\n", function_name);  \
            break;                                                         \
        case SS_ALLOCATION_FAILURE:                                        \
            fprintf(stderr, "[ERROR] at [%s]: ALLOCATION FAILURE\n", function_name); \
            break;                                                         \
        case SS_DATA_ALLOCATION_FAILURE:                                   \
            fprintf(stderr, "[ERROR] at [%s]: DATA ALLOCATION FAILURE\n", function_name); \
            break;                                                         \
        case SS_INVALID_ARGUMENT:                                          \
            fprintf(stderr, "[ERROR] at [%s]: INVALID ARGUMENT\n", function_name); \
            break;                                                         \
        case SS_EMPTY:                                                     \
            fprintf(stderr, "[ERROR] at [%s]: STACK IS EMPTY\n", function_name); \
            break;                                                         \
        case SS_LS_ALLOCATION_FAILURE:                                     \
            fprintf(stderr, "[ERROR] at [%s]: LINKED LIST ALLOCATION FAILURE\n", function_name); \
            break;                                                         \
        case SS_LS_NODE_ALLOCATION_FAILURE:                                \
            fprintf(stderr, "[ERROR] at [%s]: LINKED LIST NODE ALLOCATION FAILURE\n", function_name); \
            break;                                                         \
        default:                                                           \
            fprintf(stderr, "[ERROR] at [%s]: UNKNOWN STACK STATUS\n", function_name); \
            break;                                                         \
        }                                                                  \
    } while (0)

typedef struct {
    LinkedList *_base_List;
} Stack;

static StackStatus _Status_Translator(LinkedListStatus LS_STATUS)
{
    switch (LS_STATUS)
    {
    case LS_SUCCESS:
        return SS_SUCCESS;
    case LS_ALLOCATION_FAILURE:
        return SS_ALLOCATION_FAILURE;
    case LS_EMPTY:
        return SS_EMPTY;
    case LS_INVALID_ARGUMENT:
        return SS_INVALID_ARGUMENT;
    case LS_DATA_ALLOCATION_FAILURE:
        return SS_DATA_ALLOCATION_FAILURE;
    }
}

Stack* Stack_Create(size_t element_size)
{
    if (element_size == 0)
    {
        _STACK_STATUS_PRINTER(SS_INVALID_ARGUMENT, "Stack_Create");
        return NULL;
    }
    Stack* stack = ds_malloc(sizeof(Stack));
    if ()
}
