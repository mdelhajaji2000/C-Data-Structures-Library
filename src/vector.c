#include "..\API\vector.h"


struct Vector
{
    void *_data;
    size_t _size;
    size_t _capaicity;
    size_t _element_size;
};

size_t Vector_GetSize(const Vector *v)
{
    return v->_size;
}

size_t Vector_GetCapacity(const Vector *v)
{
    return v->_capaicity;
}

size_t Vector_GetElementSize(const Vector *v)
{
    return v->_element_size;
}

Vector *Vector_Create(size_t size, size_t element_size)
{
    Vector *v = (Vector *)ds_malloc(sizeof(Vector));
    if (v != NULL)
    {
        v->_data = ds_malloc(size * element_size);
        if (v->_data != NULL)
        {
            v->_size = 0;
            v->_capaicity = size;
            v->_size = 0;
            v->_element_size = element_size;
        }
        else
        {
            ds_free(v);
            v = NULL;
        }
    }
    else
        return NULL;
    
    return v;
}


void *Vector_GetAt(Vector *v, size_t index)
{
    if (v == NULL || v->_data == NULL || index >= v->_capaicity)
        return NULL;

    return (char *)v->_data + (index * v->_element_size);
}

