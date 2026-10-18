#include "..\API\Doubly_Linked_List.h"
#include "..\memory\memory.h"

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



DLinkedListStatus DList_Create(size_t element_size, DLinkedList **out_list)
{
    if (out_list == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    *out_list = NULL;
    if (element_size == 0)
    {
        return D_LS_INVALID_ARGUMENT;
    }

    DLinkedList* DList = ds_malloc(sizeof(DLinkedList));
    if (DList == NULL)
    {
        return D_LS_ALLOCATION_FAILURE;
    }

    DList->_size = 0;
    DList->_element_size = element_size;
    DList->_tail = NULL;
    DList->_head = NULL;

    *out_list = DList;
    return D_LS_SUCCESS;
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
        return 0;
    }

    return DList->_size;
}

size_t DList_GetElementSize(const DLinkedList *DList)
{
    if (DList == NULL)
    {
        return 0;
    }

    return DList->_element_size;
}

DLinkedListStatus DList_GetFirst(const DLinkedList *DList, void **out_value)
{
    if (out_value == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    *out_value = NULL;
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }

    if (DList->_head == NULL)
    {
        return D_LS_EMPTY;
    }

    *out_value = DList->_head->_data;
    return D_LS_SUCCESS;
}

DLinkedListStatus DList_GetLast(const DLinkedList* DList, void **out_value)
{
    if (out_value == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    *out_value = NULL;
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }

    if (DList->_tail == NULL)
    {
        return D_LS_EMPTY;
    }

    *out_value = DList->_tail->_data;
    return D_LS_SUCCESS;
}

DLinkedListStatus DList_GetAt(const DLinkedList* DList, size_t index, void **out_value)
{
    if (out_value == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    *out_value = NULL;
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    if (index >= DList->_size)
    {
        return D_LS_INDEX_OUT_OF_RANGE;
    }

    _node* current = DList->_head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->_next;
    }

    *out_value = current->_data;
    return D_LS_SUCCESS;
}

DLinkedListStatus DList_PushFront(DLinkedList *DList, void* value)
{
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    if (value == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }

    _node* NodToInsert = ds_malloc(sizeof(_node));
    if (NodToInsert == NULL)
    {
        return D_LS_ALLOCATION_FAILURE;
    }
    NodToInsert->_data = ds_malloc(DList->_element_size);
    if (NodToInsert->_data == NULL)
    {
        ds_free(NodToInsert);
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
        return D_LS_INVALID_ARGUMENT;
    }
    if (value == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }

    _node* NodToInsert = ds_malloc(sizeof(_node));
    if (NodToInsert == NULL)
    {
        return D_LS_ALLOCATION_FAILURE;
    }
    NodToInsert->_data = ds_malloc(DList->_element_size);
    if (NodToInsert->_data == NULL)
    {
        ds_free(NodToInsert);
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

DLinkedListStatus DList_InsertAt(DLinkedList* DList, void* value, size_t index)
{
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    if (value == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    if (index > DList->_size)
    {
        return D_LS_INDEX_OUT_OF_RANGE;
    }
    if (index == 0)
        return DList_PushFront(DList, value);
    if (index == DList->_size)
        return DList_PushBack(DList, value);

    _node* NodeToInsert = ds_malloc(sizeof(_node));
    if (NodeToInsert == NULL)
    {
        return D_LS_ALLOCATION_FAILURE;
    }
    NodeToInsert->_data = ds_malloc(DList->_element_size);
    if (NodeToInsert->_data == NULL)
    {
        ds_free(NodeToInsert);
        return D_LS_DATA_ALLOCATION_FAILURE;
    }
    memcpy(NodeToInsert->_data, value, DList->_element_size);

    _node* current = DList->_head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->_next;
    }

    NodeToInsert->_next = current;
    NodeToInsert->_prev = current->_prev;
    _node* curr_prev = current->_prev;
    curr_prev->_next = NodeToInsert;
    current->_prev = NodeToInsert;
    DList->_size++;

    return D_LS_SUCCESS;
}

DLinkedListStatus DList_PopFront(DLinkedList* DList)
{
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    if (DList->_head == NULL)
        return D_LS_EMPTY;

    if (DList->_head == DList->_tail)
    {
        ds_free(DList->_head->_data);
        ds_free(DList->_head);
        DList->_head = NULL;
        DList->_tail = NULL;
        DList->_size--;
        return D_LS_SUCCESS;
    }

    _node* NodeToDelete = DList->_head;
    _node* New_Head = DList->_head->_next;
    New_Head->_prev = NULL;
    ds_free(NodeToDelete->_data);
    ds_free(NodeToDelete);
    DList->_head = New_Head;
    DList->_size--;
    return D_LS_SUCCESS;
}

DLinkedListStatus DList_PopBack(DLinkedList* DList)
{
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    if (DList->_tail == NULL)
        return D_LS_EMPTY;

    if (DList->_head == DList->_tail)
    {
        ds_free(DList->_tail->_data);
        ds_free(DList->_tail);
        DList->_head = NULL;
        DList->_tail = NULL;
        DList->_size--;
        return D_LS_SUCCESS;
    }

    _node* NodeToDelete = DList->_tail;
    _node* NewTail = DList->_tail->_prev;
    NewTail->_next = NULL;
    ds_free(NodeToDelete->_data);
    ds_free(NodeToDelete);
    DList->_tail = NewTail;
    DList->_size--;
    return D_LS_SUCCESS;
}

DLinkedListStatus DList_DeleteAt(DLinkedList* DList, size_t index)
{
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }
    if (index >= DList->_size)
    {
        return D_LS_INDEX_OUT_OF_RANGE;
    }

    if (DList->_head == NULL)
        return D_LS_SUCCESS;

    if (index == 0)
        return DList_PopFront(DList);
    else if (index == DList->_size - 1)
        return DList_PopBack(DList);

    _node* currrent = DList->_head;
    for (size_t i = 0; i < index; i++)
    {
        currrent = currrent->_next;
    }

    _node* curr_next = currrent->_next;
    _node* curr_prev = currrent->_prev;
    curr_next->_prev = curr_prev;
    curr_prev->_next = curr_next;
    ds_free(currrent->_data);
    ds_free(currrent);
    DList->_size--;
    return D_LS_SUCCESS;
}

DLinkedListStatus DList_Clear(DLinkedList* DList)
{
    if (DList == NULL)
    {
        return D_LS_INVALID_ARGUMENT;
    }

    _node* current = DList->_head;
    while (current != NULL)
    {
        _node* next = current->_next;
        ds_free(current->_data);
        ds_free(current);
        current = next;
    }

    DList->_head = NULL;
    DList->_tail = NULL;
    DList->_size = 0;

    return D_LS_SUCCESS;
}
