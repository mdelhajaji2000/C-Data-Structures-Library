#include "..\API\Doubly_Linked_List.h"
#include "..\memory\memory.h"

#include <stdio.h>
#include <string.h>

typedef struct _node 
{
    void* _data;
    void* _next;
    void* _prev;
} _node;

typedef struct DLinkedList
{
    _node* _head;
    _node* _tail;
    size_t _element_size;
    size_t _size;
} DLinkedList;

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

DLinkedList* DList_Create(size_t element_size)
{
    if (element_size == 0)
    {
        _D_LIST_STATUS_PRINTER(D_LS_INVALID_ARGUMENT, "DList_Create");
        return NULL;
    }

    DLinkedList* DList = ds_malloc(sizeof(DLinkedList));
    if (DList == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_ALLOCATION_FAILURE, "DList_Create");
        return NULL;
    }

    DList->_size = 0;
    DList->_element_size = element_size;
    DList->_tail = NULL;
    DList->_head = NULL;

    return DList;
}

DLinkedListStatus DList_Destroy(DLinkedList* DList)
{
    if (DList == NULL)
        return D_LS_SUCCESS;

    _node* NodeToDelete = DList->_head;
    _node* NextSaver;
    while (NodeToDelete != NULL)
    {
        NextSaver = NodeToDelete->_next;
        ds_free(NodeToDelete->_data);
        ds_free(NodeToDelete);
        NodeToDelete = NextSaver;
    }
    ds_free(DList);
    
    return D_LS_SUCCESS;
}

size_t DList_GetSize(const DLinkedList *DList)
{
    if (DList == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DListGetSize");
        return 0;
    }

    return DList->_size;
}

size_t DList_GetElementSize(const DLinkedList *DList)
{
    if (DList == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DList_GetElementSize");
        return 0;
    }

    return DList->_element_size;
}

void* DList_GetFirst(const DLinkedList *DList)
{
    if (DList == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DList_GetFirst");
        return NULL;
    }

    if (DList->_head == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DList_GetFirst");
        return NULL;
    }

    return DList->_head->_data;
}

void* DList_GetLast(const DLinkedList* DList)
{
    if (DList == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DList_GetLast");
        return NULL;
    }

    if (DList->_tail == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DList_GetLast");
        return NULL;
    }

    return DList->_tail->_data;
}

void* DList_GetAt(const DLinkedList* DList, size_t index)
{
    if (DList == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DList_GetAt");
        return NULL;
    }
    if (index >= DList->_size)
    {
        _D_LIST_STATUS_PRINTER(D_LS_INDEX_OUT_OF_RANGE, "DList_GetAt");
        return NULL;
    }

    _node* current = DList->_head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->_next;
    }

    return current->_data;
}

DLinkedListStatus DList_PushFront(DLinkedList *DList, void* value)
{
    if (DList == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DList_PushFront");
        return D_LS_EMPTY;
    }
    if (value == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_INVALID_ARGUMENT, "DList_PushFront");
        return D_LS_INVALID_ARGUMENT;
    }

    _node* NodToInsert = ds_malloc(sizeof(_node));
    if (NodToInsert == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_ALLOCATION_FAILURE, "DList_PushFront");
        return D_LS_ALLOCATION_FAILURE;
    }
    NodToInsert->_data = ds_malloc(DList->_element_size);
    if (NodToInsert->_data == NULL)
    {
        ds_free(NodToInsert);
        _D_LIST_STATUS_PRINTER(D_LS_DATA_ALLOCATION_FAILURE, "DList_PushFront");
        return D_LS_DATA_ALLOCATION_FAILURE;
    }
    NodToInsert->_prev = NULL;
    NodToInsert->_next = DList->_head;
    memcpy(NodToInsert->_data, value, DList->_element_size);
    if (DList->_head == NULL)
    {
        DList->_head = NodToInsert;
        DList->_size++;

        DList->_tail = NodToInsert;
        return D_LS_SUCCESS;
    }

    DList->_head->_prev = NodToInsert;

    DList->_head = NodToInsert;
    DList->_size++;

    return D_LS_SUCCESS;
}

DLinkedListStatus DList_PushBack(DLinkedList* DList, void* value)
{
    if (DList == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_EMPTY, "DList_PushBack");
        return D_LS_EMPTY;
    }
    if (value == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_INVALID_ARGUMENT, "DList_PushBack");
        return D_LS_INVALID_ARGUMENT;
    }

    _node* NodToInsert = ds_malloc(sizeof(_node));
    if (NodToInsert == NULL)
    {
        _D_LIST_STATUS_PRINTER(D_LS_ALLOCATION_FAILURE, "DList_PushBack");
        return D_LS_ALLOCATION_FAILURE;
    }
    NodToInsert->_data = ds_malloc(DList->_element_size);
    if (NodToInsert->_data == NULL)
    {
        ds_free(NodToInsert);
        _D_LIST_STATUS_PRINTER(D_LS_DATA_ALLOCATION_FAILURE, "DList_PushBack");
        return D_LS_DATA_ALLOCATION_FAILURE;
    }
    memcpy(NodToInsert->_data, value, DList->_element_size);
    NodToInsert->_next = NULL;
    NodToInsert->_prev = NULL;
    if (DList->_tail == NULL)
    {
        DList->_tail = NodToInsert;
        DList->_head = NodToInsert;
        DList->_size++;
        return D_LS_SUCCESS;
    }

    NodToInsert->_prev = DList->_tail;
    DList->_tail->_next = NodToInsert;
    DList->_tail = NodToInsert;
    DList->_size++;

    return D_LS_SUCCESS;
}