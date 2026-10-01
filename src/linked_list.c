#include "..\API\linked_list.h"
#include <stdio.h>
#include <stdbool.h>
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