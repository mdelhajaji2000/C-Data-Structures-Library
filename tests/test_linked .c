#include <assert.h>
#include <stddef.h>

#include "../API/Doubly_Linked_List.h"
#include "../API/linked_list.h"
#include "../API/stack.h"
#include "../API/vector.h"

int main(void)
{
    int value = 42;
    void *item = NULL;

    item = &value;
    assert(Vector_GetAt(NULL, 0, &item) == VECTOR_INVALID_ARGUMENT);
    assert(item == NULL);

    Vector *vector = NULL;
    assert(Vector_Create(1, 0, &vector) == VECTOR_INVALID_ARGUMENT);
    assert(vector == NULL);
    assert(Vector_Create(0, sizeof(value), &vector) == VECTOR_SUCCESS);
    assert(vector != NULL);
    assert(Vector_PushBack(vector, &value) == VECTOR_SUCCESS);
    assert(Vector_GetAt(vector, 0, &item) == VECTOR_SUCCESS);
    assert(*(int *)item == value);
    Vector_Destroy(vector);

    LinkedList *list = NULL;
    assert(List_Create(0, &list) == LS_INVALID_ARGUMENT);
    assert(list == NULL);
    item = &value;
    assert(List_GetFirst(NULL, &item) == LS_INVALID_ARGUMENT);
    assert(item == NULL);
    assert(List_Create(sizeof(value), &list) == LS_SUCCESS);
    assert(list != NULL);
    assert(List_PushBack(list, &value) == LS_SUCCESS);
    assert(List_GetFirst(list, &item) == LS_SUCCESS);
    assert(*(int *)item == value);
    assert(List_GetAt(list, 1, &item) == LS_INDEX_OUT_OF_RANGE);
    assert(item == NULL);
    assert(List_Destroy(list) == LS_SUCCESS);

    DLinkedList *dlist = NULL;
    assert(DList_Create(0, &dlist) == D_LS_INVALID_ARGUMENT);
    assert(dlist == NULL);
    item = &value;
    assert(DList_GetFirst(NULL, &item) == D_LS_INVALID_ARGUMENT);
    assert(item == NULL);
    assert(DList_Create(sizeof(value), &dlist) == D_LS_SUCCESS);
    assert(dlist != NULL);
    assert(DList_PushBack(dlist, &value) == D_LS_SUCCESS);
    assert(DList_GetLast(dlist, &item) == D_LS_SUCCESS);
    assert(*(int *)item == value);
    assert(DList_PopFront(dlist) == D_LS_SUCCESS);
    assert(DList_GetSize(dlist) == 0);
    assert(DList_GetFirst(dlist, &item) == D_LS_EMPTY);
    assert(item == NULL);
    assert(DList_PopBack(dlist) == D_LS_EMPTY);
    assert(DList_Destroy(dlist) == D_LS_SUCCESS);

    Stack *stack = NULL;
    assert(Stack_Create(sizeof(value), NULL) == SS_INVALID_ARGUMENT);
    assert(Stack_Create(0, &stack) == SS_INVALID_ARGUMENT);
    assert(stack == NULL);
    assert(Stack_Create(sizeof(value), &stack) == SS_SUCCESS);
    assert(stack != NULL);
    assert(Stack_Destroy(stack) == SS_SUCCESS);

    return 0;
}
