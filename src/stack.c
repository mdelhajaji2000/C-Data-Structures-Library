#include "..\memory\memory.h"
#include "..\API\linked_list.h"
#include "..\API\stack.h"


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
    case LS_INTERNAL_ERROR:
        return SS_INTERNAL_ERROR;
    default:
        return SS_INTERNAL_ERROR;
    }
}


StackStatus Stack_Create(size_t element_size, Stack **out_stack)
{
    if (out_stack == NULL)
    {
        return SS_INVALID_ARGUMENT;
    }
    *out_stack = NULL;
    if (element_size == 0)
    {
        return SS_INVALID_ARGUMENT;
    }

    Stack *stack = ds_malloc(sizeof(Stack));
    if (stack == NULL)
    {
        return SS_ALLOCATION_FAILURE;
    }
    LinkedList *list = NULL;
    StackStatus status = _Status_Translator(List_Create(element_size, &list));
    if (status == SS_SUCCESS)
    {
        stack->_base_List = list;
        stack->_Top = NULL;
        *out_stack = stack;
        return SS_SUCCESS;
    }
    ds_free(stack);

    return status;
}

StackStatus Stack_Destroy(Stack *stack)
{
    if (stack == NULL)
    {
        return SS_SUCCESS;
    }

    StackStatus status = _Status_Translator(List_Destroy(stack->_base_List));
    if (status != SS_SUCCESS)
    {
        return status;
    }

    ds_free(stack);
    return SS_SUCCESS;
}
