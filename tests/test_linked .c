#include <stdio.h>
#include "../API/Linked_List.h"


int main()
{
    LinkedList *List = List_Create(sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        List_PushFront(List, i);
    }

    
    return 0;
}
