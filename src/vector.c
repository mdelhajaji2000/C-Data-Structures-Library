#include "API\vector.h"


struct Vector
{
    void *_data;
    size_t _size;
    size_t _capaicity;
    size_t _element_size;
};

Vector *vector_create(size_t size, size_t element_size)
{
    Vector *v = ds_malloc(sizeof(Vector));
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