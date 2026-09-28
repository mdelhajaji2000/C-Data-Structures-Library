#include <stdio.h>
#include "../API/vector.h"


int main()
{
    printf("Program started\n");
    Vector* v = (Vector *)Vector_Create(10, sizeof(int));
    
    for (int i = 0; i < 10; i++)
    {
        Vector_PushBack(v, &(int){i});
    }

    *((int *)Vector_GetAt(v, 5)) = 3333;

    printf("Vector Elements : \n");
    for (int i = 0 ; i < 10; i++)
    {
        printf("v[%d] = %d\n", i, *((int *)Vector_GetAt(v, i)));
    }


    printf("Program End..!\n");
    ds_free(v);
    
    return 0;
}