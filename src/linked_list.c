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