#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "..\API\vector.h"
#include "..\memory\memory.h"



struct Vector
{
    void *_data;
    size_t _size;
    size_t _capacity;
    size_t _element_size;
};

static bool _Is_Vector_Valid(const Vector *v)
{
    return v != NULL;
}

size_t Vector_GetSize(const Vector *v)
{
    if (!_Is_Vector_Valid(v))
        return 0;
    return v->_size;
}

size_t Vector_GetCapacity(const Vector *v)
{
    if (!_Is_Vector_Valid(v))
        return 0;
    return v->_capacity;
}

size_t Vector_GetElementSize(const Vector *v)
{
    if (!_Is_Vector_Valid(v))
        return 0;
    return v->_element_size;
}

Vector *Vector_Create(size_t size, size_t element_size)
{
    if (element_size == 0)
    {
        fprintf(stderr, "[ERROR] at [Vector_Create] : INVALID ARGUMENT {require : element_size > 0}");
        return NULL;
    }
    if (size > SIZE_MAX / element_size)
    {
        fprintf(stderr, "[ERROR] at [Vector_Create] : ALLOCATION SIZE OVERFLOW\n");
        return NULL;
    }
    Vector *v = (Vector *)ds_malloc(sizeof(Vector));
    if (v != NULL)
    {
        if (size > 0)
            v->_data = ds_malloc(size * element_size);
        else
        {
            v->_data = NULL;
            v->_size = 0;
            v->_element_size = element_size;
            v->_capacity = 0;
            return v;
        }
            
        if (v->_data != NULL)
        {
            v->_size = 0;
            v->_capacity = size;
            v->_element_size = element_size;
        }
        else
        {
            ds_free(v);
            v = NULL;
            fprintf(stderr, "[ERROR] at [Vector_Create] : VECTOR DATA ALLOCATION FAILURE");
        }
    }
    else
    {
        fprintf(stderr, "[ERROR] at [Vector_Create] : VECTOR ALLOCATION FAILURE");
        return NULL;
    }
    
    return v;
}


void *Vector_GetAt(Vector *v, size_t index)
{
    if (v == NULL || v->_data == NULL)
    {
        fprintf(stderr, "\n-[ERROR] at [Vector_GetAt] : INVALID ARGUMENTS");
        return NULL;
    }
    if (index >= v->_size)
    {
        fprintf(stderr, "\n-[ERROR] at [Vector_GetAt] : INDEX OUT OF RANGE");
        return NULL;
    }

    return (char *)v->_data + (index * v->_element_size);
}


VectorStatus Vector_SetAt(Vector *v, size_t index, void* value)
{
    if (v == NULL || v->_data == NULL || value == NULL)
    {
        fprintf(stderr, "\n-[ERROR] at [Vector_SetAt] : INVALID ARGUMENTS-\n");
        return VECTOR_INVALID_ARGUMENT;
    }
    
    if (index >= v->_size)
    {
        fprintf(stderr, "[ERROR] at [Vector_SetAt] : INDEX OUT OF RANGE");
        return VECTOR_INDEX_OUT_OF_RANGE;
    }

    void* destination = (char *)v->_data + index * v->_element_size;
    memcpy(destination, value, v->_element_size);
    return VECTOR_SUCCESS;
}

static VectorStatus _Vector_resize(Vector *v)
{
    size_t _new_capacity;
    if (v->_capacity == 0)
        _new_capacity = 1;
    else
    {
        if (v->_capacity > SIZE_MAX / 2)
            return VECTOR_REALLOCATION_FAILURE;
        _new_capacity = v->_capacity * 2;
    }

    if (_new_capacity > SIZE_MAX / v->_element_size)
        return VECTOR_REALLOCATION_FAILURE;

    void* _new_data = ds_realloc(v->_data, _new_capacity * v->_element_size);
    if (_new_data != NULL)
    {
        v->_data = _new_data;
        v->_capacity = _new_capacity;
        return VECTOR_SUCCESS;
    }

    return VECTOR_REALLOCATION_FAILURE;
}

VectorStatus Vector_PushBack(Vector *v, void* value)
{
    if (v == NULL || value == NULL)
    {
        fprintf(stderr, "[ERROR] at [Vector_PushBack] : INVALID ARGUMENTS");
        return VECTOR_INVALID_ARGUMENT;
    }

    size_t index = v->_size;

    if (index >= v->_capacity)
    {
        void *value_saver = ds_malloc(v->_element_size);
        if (value_saver == NULL)
        {
            fprintf(stderr, "[ERROR] at [Vector_PushBack]: TEMPORARY ALLOCATION FAILURE\n");
            return VECTOR_ALLOCATION_FAILURE;
        }

        memcpy(value_saver, value, v->_element_size);

        VectorStatus status = _Vector_resize(v);
        if (status != VECTOR_SUCCESS)
        {
            ds_free(value_saver);
            fprintf(stderr, "[ERROR] at [Vector_PushBack]: REALLOCATION FAILURE\n");
            return status;
        }

        void *destination =
            (char *)v->_data + index * v->_element_size;
        memcpy(destination, value_saver, v->_element_size);

        ds_free(value_saver);
    }
    else
    {
        void *destination =
            (char *)v->_data + index * v->_element_size;
        memcpy(destination, value, v->_element_size);
    }

    v->_size++;
    return VECTOR_SUCCESS;
}

void Vector_Clear(Vector *v)
{
    if (v == NULL)
        return;

    ds_free(v->_data);
    ds_free(v);
}
