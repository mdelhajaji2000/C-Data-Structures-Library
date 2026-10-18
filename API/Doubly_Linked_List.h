#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct DLinkedList DLinkedList;

typedef enum {
    D_LS_SUCCESS = 0,
    D_LS_ALLOCATION_FAILURE = -1,
    D_LS_DATA_ALLOCATION_FAILURE = -2,
    D_LS_INVALID_ARGUMENT = -3,
    D_LS_EMPTY = -4,
    D_LS_INDEX_OUT_OF_RANGE = -5,
    D_LS_INTERNAL_ERROR = -6
} DLinkedListStatus;

DLinkedListStatus DList_Create(size_t element_size, DLinkedList **out_list);
DLinkedListStatus DList_Destroy(DLinkedList* DList);
size_t DList_GetSize(const DLinkedList* DList);
size_t DList_GetElementSize(const DLinkedList* DList);
DLinkedListStatus DList_GetFirst(const DLinkedList *DList, void **out_value);
DLinkedListStatus DList_GetLast(const DLinkedList* DList, void **out_value);
DLinkedListStatus DList_GetAt(const DLinkedList* DList, size_t index, void **out_value);
DLinkedListStatus DList_PushFront(DLinkedList *DList, void* value);
DLinkedListStatus DList_PushBack(DLinkedList* DList, void* value);
DLinkedListStatus DList_InsertAt(DLinkedList* DList, void* value, size_t index);
DLinkedListStatus DList_PopFront(DLinkedList* DList);
DLinkedListStatus DList_PopBack(DLinkedList* DList);
DLinkedListStatus DList_DeleteAt(DLinkedList* DList, size_t index);
DLinkedListStatus DList_Clear(DLinkedList* DList);
