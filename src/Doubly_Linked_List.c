#include "..\API\Doubly_Linked_List.h"
#include "..\memory\memory.h"

#include <stdio.h>

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
