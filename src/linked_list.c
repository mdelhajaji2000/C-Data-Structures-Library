#include "..\API\linked_list.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "..\memory\memory.h"



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

    return 0;
}

bool List_Is_Empty(const LinkedList *List)
{
    if (List == NULL)
    {
        return false;
    }
    return List->_size == 0;
}

LinkedListStatus List_Create(size_t element_size, LinkedList **out_list)
{
    if (out_list == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    *out_list = NULL;
    if (element_size == 0)
    {
        return LS_INVALID_ARGUMENT;
    }
    LinkedList *List = (LinkedList *)ds_malloc(sizeof(LinkedList));
    if (List == NULL)
    {
        return LS_ALLOCATION_FAILURE;
    }

    List->_element_size = element_size;
    List->_head = NULL;
    List->_tail = NULL;
    List->_size = 0;
    *out_list = List;
    return LS_SUCCESS;
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
        return LS_INVALID_ARGUMENT;
    }

    _node* node_ToPush = ds_malloc(sizeof(_node));
    if (node_ToPush == NULL)
    {
        return LS_ALLOCATION_FAILURE;
    }
    node_ToPush->_data = ds_malloc(List->_element_size);
    if (node_ToPush->_data == NULL)
    {
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
        return LS_INVALID_ARGUMENT;
    }

    _node* node_toPush = ds_malloc(sizeof(_node));
    if (node_toPush == NULL)
    {
        return LS_ALLOCATION_FAILURE;
    }

    node_toPush->_data = ds_malloc(List->_element_size);
    if (node_toPush->_data == NULL)
    {
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

LinkedListStatus List_GetLast(const LinkedList* List, void **out_value)
{
    if (out_value == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    *out_value = NULL;
    if (List == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    if (List->_tail == NULL)
    {
        return LS_EMPTY;
    }
    *out_value = List->_tail->_data;
    return LS_SUCCESS;
}

LinkedListStatus List_GetFirst(const LinkedList* List, void **out_value)
{
    if (out_value == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    *out_value = NULL;
    if (List == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    if (List->_head == NULL)
    {
        return LS_EMPTY;
    }
    *out_value = List->_head->_data;
    return LS_SUCCESS;
}

bool List_IsLast(const LinkedList *List, const void* element)
{
    if (List == NULL || element == NULL)
    {
        return false;
    }
    if (List->_tail == NULL)
    {
        return false;
    }
    return element == List->_tail->_data;
}

LinkedListStatus List_GetAt(LinkedList* List, size_t index, void **out_value)
{
    if (out_value == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    *out_value = NULL;
    if (List == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    if (List->_tail == NULL)
    {
        return LS_EMPTY;
    }
    if (index >= List->_size)
    {
        return LS_INDEX_OUT_OF_RANGE;
    }

    _node* current = List->_head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->_next;
    }
    
    *out_value = current->_data;
    return LS_SUCCESS;
}

LinkedListStatus List_DeleteAt(LinkedList *List, size_t index)
{
    if (List == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    if (index >= List->_size)
    {
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
        return LS_INVALID_ARGUMENT;
    }

    if (List->_size == 0)
    {
        return LS_EMPTY;
    }

    return List_DeleteAt(List, List->_size - 1);
}

LinkedListStatus List_PopFront(LinkedList *List)
{
    if (List == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }

    if (List->_size == 0)
    {
        return LS_EMPTY;
    }

    return List_DeleteAt(List, 0);
}

LinkedListStatus List_Clear(LinkedList* List)
{
    if (List == NULL)
    {
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

size_t List_Find(const LinkedList* List, const void* value,
int (*compare)(const void*, const void*))
{
    if (List == NULL || value == NULL || compare == NULL)
    {
        return SIZE_MAX;
    }

    size_t index = 0;
    const _node* current = List->_head;
    while (current != NULL)
    {
        if (compare(current->_data, value) == 0)
            return index;

        current = current->_next;
        index++;
    }

    return SIZE_MAX;
}

LinkedListStatus List_PushAt(LinkedList *List, size_t index, void* value)
{
    if (List == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }
    if (index > List->_size)
    {
        return LS_INDEX_OUT_OF_RANGE;
    }
    if (value == NULL)
    {
        return LS_INVALID_ARGUMENT;
    }

    if (index == 0)
        return List_PushFront(List, value);
    else if (index == List->_size)
        return List_PushBack(List, value);

    _node* NodeToInsert = ds_malloc(sizeof(_node));
    if (NodeToInsert == NULL)
    {
        return LS_ALLOCATION_FAILURE;
    }

    NodeToInsert->_data = ds_malloc(List->_element_size);
    if (NodeToInsert->_data == NULL)
    {
        ds_free(NodeToInsert);
        return LS_DATA_ALLOCATION_FAILURE;
    }

    memcpy(NodeToInsert->_data, value, List->_element_size);
    _node* current = List->_head;
    for (size_t i = 0; i < index - 1; i++)
    {
        current = current->_next;
    }

    NodeToInsert->_next = current->_next;
    current->_next = NodeToInsert;
    List->_size++;
    return LS_SUCCESS;
}
