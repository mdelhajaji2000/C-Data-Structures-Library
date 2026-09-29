#include "..\API\linked_list.h"
#include <stdio.h>
#include <stdbool.h>

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

static bool _Is_List_Empty(void* L)
{
    return L == NULL;
}

size_t List_GetSize(LinkedList* L)
{
    
}

LinkedList* List_Create()
{

}
