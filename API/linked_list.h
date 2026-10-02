#include <stdlib.h>

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
bool List_Is_Empty(LinkedList *List);
LinkedListStatus List_PushFront(LinkedList *List, void* value);