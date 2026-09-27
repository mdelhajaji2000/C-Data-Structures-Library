#include <stdio.h>
#include "../API/vector.h"


int main(void)
{
    printf("Program started\n");
    Vector *v = (Vector *)Vector_Create(10, sizeof(int));
    
    printf("Element size is : %d\n", Vector_GetElementSize(v));
    printf("Capacity is : %d\n", Vector_GetCapacity(v));
    printf("Size is : %d\n", Vector_GetSize(v));

    *((int *)Vector_GetAt(v, 5)) = 12123;
    //printf("Program reach here..!");


    printf("getting Element at index = 5 : \n");
    printf("v[5] = %d", *(int *)Vector_GetAt(v, 5));

    printf("Program End..!");
    return 0;
}