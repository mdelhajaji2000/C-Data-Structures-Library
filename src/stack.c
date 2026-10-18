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
        case SS_LS_INDEX_OUT_OF_RANGE:                                     \
            fprintf(stderr, "[ERROR] at [%s]: LINKED LIST INDEX OUT OF RANGE\n", function_name); \
            break;                                                         \
        default:                                                           \
            fprintf(stderr, "[ERROR] at [%s]: UNKNOWN STACK STATUS\n", function_name); \
            break;                                                         \
        }                                                                  \
    } while (0)

struct Stack {
    LinkedList *_base_List;
    void* _Top;
};

static StackStatus _Status_Translator(LinkedListStatus LS_STATUS)
{
    switch (LS_STATUS)
    {
    case LS_SUCCESS:
        return SS_SUCCESS;
    case LS_ALLOCATION_FAILURE:
        return SS_LS_ALLOCATION_FAILURE;
    case LS_EMPTY:
        return SS_EMPTY;
    case LS_INVALID_ARGUMENT:
        return SS_INVALID_ARGUMENT;
    case LS_DATA_ALLOCATION_FAILURE:
        return SS_LS_NODE_ALLOCATION_FAILURE;
    case LS_INDEX_OUT_OF_RANGE:
        return SS_LS_INDEX_OUT_OF_RANGE;
    default:
        return SS_INVALID_ARGUMENT;
    }
}


StackStatus Stack_Create(size_t element_size, Stack **out_Stack)
{
    *out_Stack = NULL;
    if (element_size == 0 || out_Stack == NULL)
    {
        _STACK_STATUS_PRINTER(SS_INVALID_ARGUMENT, "Stack_Create");
        return SS_INVALID_ARGUMENT;
    }
    Stack *stack = ds_malloc(sizeof(Stack));
    if (stack == NULL)
    {
        _STACK_STATUS_PRINTER(SS_ALLOCATION_FAILURE, "Stack_Create");
        return SS_ALLOCATION_FAILURE;
    }
    LinkedList* List = NULL;
    StackStatus status = _Status_Translator(List_Create(element_size, &List));
    if (status == SS_SUCCESS)
    {
        stack->_base_List = List;
        stack->_Top = NULL;
        *out_Stack = stack;
        return SS_SUCCESS;
    }
    ds_free(stack);

    return status;
}