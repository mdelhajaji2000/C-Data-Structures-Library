# C-Data-Structures-Library
A custom-built C library featuring core data structures

## Status based pointer APIs

Operations that return a pointer and can fail with a detailed status return the
status enum for their own module and write the pointer through an output
parameter. Pass the address of a pointer initialized to `NULL`:

```c
Vector *vector = NULL;
VectorStatus status = Vector_Create(8, sizeof(int), &vector);
if (status != VECTOR_SUCCESS) {
    /* Handle the vector-specific error. */
}

void *element = NULL;
status = Vector_GetAt(vector, 0, &element);
if (status == VECTOR_SUCCESS) {
    /* Use element. */
}
```

The same convention applies to `List_Create` and its pointer getters,
`DList_Create` and its pointer getters, `DList_Clear`, and `Stack_Create`.
Each module retains its own status enum. Stack translates linked-list errors
into `StackStatus` values, including separate statuses for list allocation,
node data allocation, and index errors.

`Stack_Destroy` releases a stack and its backing linked list. Vector and list
destroy functions treat a `NULL` handle as a successful no-op.

Queue is not currently present in this repository, so there is no Queue API to
refactor yet.

## Build and run the API tests

With GCC:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -I. "tests/test_linked .c" \
    src/vector.c src/linked_list.c src/Doubly_Linked_List.c src/stack.c \
    memory/memory.c -o test_structures
./test_structures
```
