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
    {
        return 0;
    }
    return v->_size;
}

size_t Vector_GetCapacity(const Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        return 0;
    }
    return v->_capacity;
}

size_t Vector_GetElementSize(const Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        return 0;
    }
    return v->_element_size;
}

VectorStatus Vector_Create(size_t size, size_t element_size, Vector **out_vector)
{
    if (out_vector == NULL || element_size == 0)
    {
        return VECTOR_INVALID_ARGUMENT;
    }
    *out_vector = NULL;
    if (size > SIZE_MAX / element_size)
    {
        return VECTOR_SIZE_OVERFLOW;
    }
    Vector *v = (Vector *)ds_malloc(sizeof(Vector));
    if (v == NULL)
    {
        return VECTOR_ALLOCATION_FAILURE;
    }
    v->_data = size > 0 ? ds_malloc(size * element_size) : NULL;
    if (size > 0 && v->_data == NULL)
    {
        ds_free(v);
        return VECTOR_DATA_ALLOCATION_FAILURE;
    }
    v->_size = 0;
    v->_capacity = size;
    v->_element_size = element_size;
    *out_vector = v;
    return VECTOR_SUCCESS;
}


VectorStatus Vector_GetAt(Vector *v, size_t index, void **out_value)
{
    if (!_Is_Vector_Valid(v) || out_value == NULL)
    {
        return VECTOR_INVALID_ARGUMENT;
    }
    *out_value = NULL;
    if (v->_data == NULL)
    {
        return VECTOR_EMPTY;
    }
    if (index >= v->_size)
    {
        return VECTOR_INDEX_OUT_OF_RANGE;
    }

    *out_value = (char *)v->_data + (index * v->_element_size);
    return VECTOR_SUCCESS;
}


VectorStatus Vector_SetAt(Vector *v, size_t index, void* value)
{
    if (v == NULL || v->_data == NULL || value == NULL)
    {
        return VECTOR_INVALID_ARGUMENT;
    }
    
    if (index >= v->_size)
    {
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
            return VECTOR_SIZE_OVERFLOW;
        _new_capacity = v->_capacity * 2;
    }

    if (_new_capacity > SIZE_MAX / v->_element_size)
        return VECTOR_SIZE_OVERFLOW;

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
        return VECTOR_INVALID_ARGUMENT;
    }

    size_t index = v->_size;

    if (index >= v->_capacity)
    {
        void *value_saver = ds_malloc(v->_element_size);
        if (value_saver == NULL)
        {
            return VECTOR_ALLOCATION_FAILURE;
        }

        memcpy(value_saver, value, v->_element_size);

        VectorStatus status = _Vector_resize(v);
        if (status != VECTOR_SUCCESS)
        {
            ds_free(value_saver);
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

void Vector_Destroy(Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        return;
    }

    ds_free(v->_data);
    ds_free(v);
}

void Vector_Clear(Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        return;
    }

    v->_size = 0;
}

VectorStatus Vector_PopBack(Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        return VECTOR_INVALID_ARGUMENT;
    }

    if (v->_size == 0)
    {
        return VECTOR_EMPTY;
    }

    v->_size--;

    return VECTOR_SUCCESS;
}

VectorStatus Vector_Resize(Vector *v, size_t new_size)
{
    if (!_Is_Vector_Valid(v))
    {
        return VECTOR_INVALID_ARGUMENT;
    }

    while (new_size > v->_capacity)
    {
        VectorStatus status = _Vector_resize(v);
        if (status != VECTOR_SUCCESS)
        {
            return status;
        }
    }

    v->_size = new_size;
    return VECTOR_SUCCESS;
}
