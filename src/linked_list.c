#include "..\API\linked_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "..\memory\memory.h"

#define _LIST_STATUS_PRINTER(status, function_name)                     \
    do                                                                  \
    {                                                                   \
        switch (status)                                                 \
        {                                                               \
        case LS_SUCCESS:                                                \
            fprintf(stderr, "[INFO] at [%s]: SUCCESS\n", function_name); \
            break;                                                      \
        case LS_ALLOCATION_FAILURE:                                     \
            fprintf(stderr, "[ERROR] at [%s]: ALLOCATION FAILURE\n", function_name); \
            break;                                                      \
        case LS_DATA_ALLOCATION_FAILURE:                                \
            fprintf(stderr, "[ERROR] at [%s]: DATA ALLOCATION FAILURE\n", function_name); \
            break;                                                      \
        case LS_INVALID_ARGUMENT:                                       \
            fprintf(stderr, "[ERROR] at [%s]: INVALID ARGUMENT\n", function_name); \
            break;                                                      \
        case LS_EMPTY:                                                  \
            fprintf(stderr, "[ERROR] at [%s]: LIST IS EMPTY\n", function_name); \
            break;                                                      \
        case LS_INDEX_OUT_OF_RANGE:                                     \
            fprintf(stderr, "[ERROR] at [%s]: INDEX OUT OF RANGE\n", function_name); \
            break;                                                      \
        default:                                                        \
            fprintf(stderr, "[ERROR] at [%s]: UNKNOWN LIST STATUS\n", function_name); \
            break;                                                      \
        }                                                               \
    } while (0)

typedef struct 
{
    void* _data;
    void* _next;
}_node;

struct LinkedList
{
    size_t _element_size;
    size_t _size;
    _node* _head;
    _node* _tail;
};

size_t List_GetSize(const LinkedList* L)
{
    if (L != NULL)
    {
        return L->_size;
    }

    _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_GetSize");
    return 0;
}

bool List_Is_Empty(LinkedList *List)
{
    return List->_size == 0;
}

LinkedList* List_Create(size_t element_size)
{
    if (element_size == 0)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_Create");
        return NULL;
    }
    LinkedList *List = (LinkedList *)ds_malloc(sizeof(LinkedList));
    if (List == NULL)
    {
        _LIST_STATUS_PRINTER(LS_ALLOCATION_FAILURE, "List_Create");
        return NULL;
    }

    List->_element_size = element_size;
    List->_head = NULL;
    List->_tail = NULL;
    List->_size = 0;
    return List;
}

LinkedListStatus List_Destroy(LinkedList *List)
{
    if (List == NULL)
        return LS_SUCCESS;

    _node *current = List->_head;

    while (current != NULL)
    {
        _node *next = current->_next;

        ds_free(current->_data);
        ds_free(current);

        current = next;
    }

    ds_free(List);

    return LS_SUCCESS;
}

LinkedListStatus List_PushFront(LinkedList *List, void* value)
{
    if (List == NULL || value == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_PushFront");
        return LS_INVALID_ARGUMENT;
    }

    _node* node_ToPush = ds_malloc(sizeof(_node));
    if (node_ToPush == NULL)
    {
        _LIST_STATUS_PRINTER(LS_ALLOCATION_FAILURE, "List_PushFront");
        return LS_ALLOCATION_FAILURE;
    }
    node_ToPush->_data = ds_malloc(List->_element_size);
    if (node_ToPush->_data == NULL)
    {
        _LIST_STATUS_PRINTER(LS_DATA_ALLOCATION_FAILURE, "List_PushFront");
        ds_free(node_ToPush);
        return LS_DATA_ALLOCATION_FAILURE;
    }

    memcpy(node_ToPush->_data, value, List->_element_size);

    if (List->_tail == NULL)
        List->_tail = node_ToPush;

    node_ToPush->_next = List->_head;
    List->_head = node_ToPush;
    List->_size++;
    return LS_SUCCESS;
}

LinkedListStatus List_PushBack(LinkedList *List, void *value)
{
    if (List == NULL || value == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_PushBack");
        return LS_INVALID_ARGUMENT;
    }

    _node* node_toPush = ds_malloc(sizeof(_node));
    if (node_toPush == NULL)
    {
        _LIST_STATUS_PRINTER(LS_ALLOCATION_FAILURE, "List_PushBack");
        return LS_ALLOCATION_FAILURE;
    }

    node_toPush->_data = ds_malloc(List->_element_size);
    if (node_toPush->_data == NULL)
    {
        _LIST_STATUS_PRINTER(LS_DATA_ALLOCATION_FAILURE, "List_PushBack");
        ds_free(node_toPush);
        return LS_DATA_ALLOCATION_FAILURE;
    }

    memcpy(node_toPush->_data, value, List->_element_size);
    node_toPush->_next = NULL;

    if (List->_tail == NULL)
    {
        List->_head = node_toPush;
        List->_tail = node_toPush;
    }
    else
    {
        List->_tail->_next = node_toPush;
        List->_tail = node_toPush;
    }

    List->_size++;
    return LS_SUCCESS;
}

void* List_GetLast(const LinkedList* List)
{
    if (List == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_GetLast");
        return NULL;
    }
    if (List->_tail == NULL)
    {
        _LIST_STATUS_PRINTER(LS_EMPTY, "List_GetLast");
        return NULL;
    }
    return List->_tail->_data;
}

void* List_GetFirst(const LinkedList* List)
{
    if (List == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_GetFirst");
        return NULL;
    }
    if (List->_head == NULL)
    {
        _LIST_STATUS_PRINTER(LS_EMPTY, "List_GetFirst");
        return NULL;
    }
    return List->_head->_data;
}

bool List_IsLast(const LinkedList *List, const void* element)
{
    if (List == NULL || element == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_IsLast");
        return false;
    }
    if (List->_tail == NULL)
    {
        _LIST_STATUS_PRINTER(LS_EMPTY, "List_IsLast");
        return false;
    }
    return element == List->_tail->_data;
}

void* List_GetAt(LinkedList* List, size_t index)
{
    if (List == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_GetAt");
        return NULL;
    }
    if (List->_tail == NULL)
    {
        _LIST_STATUS_PRINTER(LS_EMPTY, "List_GetAt");
        return NULL;
    }
    if (index >= List->_size)
    {
        _LIST_STATUS_PRINTER(LS_INDEX_OUT_OF_RANGE, "List_GetAt");
        return NULL;
    }

    _node* current = List->_head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->_next;
    }
    
    return current->_data;
}

LinkedListStatus List_DeleteAt(LinkedList *List, size_t index)
{
    if (List == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_DeleteAt");
        return LS_INVALID_ARGUMENT;
    }
    if (index >= List->_size)
    {
        _LIST_STATUS_PRINTER(LS_INDEX_OUT_OF_RANGE, "List_DeleteAt");
        return LS_INDEX_OUT_OF_RANGE;
    }

    _node *previous = NULL;
    _node *current = List->_head;
    for (size_t i = 0; i < index; i++)
    {
        previous = current;
        current = current->_next;
    }

    if (previous == NULL)
        List->_head = current->_next;
    else
        previous->_next = current->_next;

    if (current == List->_tail)
        List->_tail = previous;

    ds_free(current->_data);
    ds_free(current);
    List->_size--;

    if (List->_size == 0)
    {
        List->_head = NULL;
        List->_tail = NULL;
    }

    return LS_SUCCESS;
}

LinkedListStatus List_PopBack(LinkedList *List)
{
    if (List == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_PopBack");
    }
    return List_DeleteAt(List, List->_size - 1);
}

LinkedListStatus List_PopFront(LinkedList *List)
{
    return List_DeleteAt(List ,0);
}

LinkedListStatus List_Clear(LinkedList* List)
{
    if (List == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_Clear");
        return LS_INVALID_ARGUMENT;
    }

    _node *current = List->_head;
    _node *next = NULL;
    while (current != NULL)
    {
        next = current->_next;
        ds_free(current->_data);
        ds_free(current);
        current = next;
    }
    
    List->_head = NULL;
    List->_tail = NULL;
    List->_size = 0;
    return LS_SUCCESS;
}

size_t List_Find(const LinkedList* List, const void* value)
{
    if (List == NULL || value == NULL)
    {
        _LIST_STATUS_PRINTER(LS_INVALID_ARGUMENT, "List_Find");
        return SIZE_MAX;
    }

    size_t index = 0;
    const _node* current = List->_head;
    while (current != NULL)
    {
        if (memcmp(current->_data, value, List->_element_size) == 0)
            return index;

        current = current->_next;
        index++;
    }

    return SIZE_MAX;
}
