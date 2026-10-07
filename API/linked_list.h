#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct LinkedList LinkedList;

typedef enum
{
    LS_SUCCESS = 0,
    LS_ALLOCATION_FAILURE = -1,
    LS_DATA_ALLOCATION_FAILURE = -2,
    LS_INVALID_ARGUMENT = -3,
    LS_EMPTY = -4,
    LS_INDEX_OUT_OF_RANGE = -5
} LinkedListStatus;

size_t List_GetSize(const LinkedList* L);
LinkedList* List_Create(size_t element_size);
LinkedListStatus List_Destroy(LinkedList* List);
bool List_Is_Empty(const LinkedList *List);
LinkedListStatus List_PushFront(LinkedList *List, void* value);
LinkedListStatus List_PushBack(LinkedList *List, void *value);
void* List_GetLast(const LinkedList* List);
void* List_GetFirst(const LinkedList* List);
bool List_IsLast(const LinkedList *List, const void* element);
void* List_GetAt(LinkedList* List, size_t index);
LinkedListStatus List_DeleteAt(LinkedList *List, size_t index);
LinkedListStatus List_PopBack(LinkedList *List);
LinkedListStatus List_PopFront(LinkedList *List);
LinkedListStatus List_Clear(LinkedList* List);
size_t List_Find(const LinkedList* List, const void* value,
int (*compare)(const void*, const void*));
LinkedListStatus List_PushAt(LinkedList *List, size_t index, void* value);

#endif /* LINKED_LIST_H */
