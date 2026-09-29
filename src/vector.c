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

#define _VECTOR_STATUS_PRINTER(status, function_name)                  \
    do                                                                 \
    {                                                                  \
        switch (status)                                                \
        {                                                              \
        case VECTOR_SUCCESS:                                           \
            fprintf(stderr, "[INFO] at [%s]: SUCCESS\n", function_name); \
            break;                                                     \
        case VECTOR_ALLOCATION_FAILURE:                                \
            fprintf(stderr, "[ERROR] at [%s]: ALLOCATION FAILURE\n", function_name); \
            break;                                                     \
        case VECTOR_DATA_ALLOCATION_FAILURE:                           \
            fprintf(stderr, "[ERROR] at [%s]: DATA ALLOCATION FAILURE\n", function_name); \
            break;                                                     \
        case VECTOR_INVALID_ARGUMENT:                                   \
            fprintf(stderr, "[ERROR] at [%s]: INVALID ARGUMENT\n", function_name); \
            break;                                                     \
        case VECTOR_INDEX_OUT_OF_RANGE:                                \
            fprintf(stderr, "[ERROR] at [%s]: INDEX OUT OF RANGE\n", function_name); \
            break;                                                     \
        case VECTOR_REALLOCATION_FAILURE:                              \
            fprintf(stderr, "[ERROR] at [%s]: REALLOCATION FAILURE\n", function_name); \
            break;                                                     \
        case VECTOR_SIZE_OVERFLOW:                                      \
            fprintf(stderr, "[ERROR] at [%s]: SIZE OVERFLOW\n", function_name); \
            break;                                                     \
        case VECTOR_EMPTY:                                              \
            fprintf(stderr, "[ERROR] at [%s]: VECTOR IS EMPTY\n", function_name); \
            break;                                                     \
        default:                                                       \
            fprintf(stderr, "[ERROR] at [%s]: UNKNOWN VECTOR STATUS\n", function_name); \
            break;                                                     \
        }                                                              \
    } while (0)

static bool _Is_Vector_Valid(const Vector *v)
{
    return v != NULL;
}

size_t Vector_GetSize(const Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_GetSize");
        return 0;
    }
    return v->_size;
}

size_t Vector_GetCapacity(const Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_GetCapacity");
        return 0;
    }
    return v->_capacity;
}

size_t Vector_GetElementSize(const Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_GetElementSize");
        return 0;
    }
    return v->_element_size;
}

Vector *Vector_Create(size_t size, size_t element_size)
{
    if (element_size == 0)
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_Create");
        return NULL;
    }
    if (size > SIZE_MAX / element_size)
    {
        _VECTOR_STATUS_PRINTER(VECTOR_SIZE_OVERFLOW, "Vector_Create");
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
            _VECTOR_STATUS_PRINTER(VECTOR_DATA_ALLOCATION_FAILURE, "Vector_Create");
        }
    }
    else
    {
        _VECTOR_STATUS_PRINTER(VECTOR_ALLOCATION_FAILURE, "Vector_Create");
        return NULL;
    }
    
    return v;
}


void *Vector_GetAt(Vector *v, size_t index)
{
    if (!_Is_Vector_Valid(v))
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_GetAt");
        return NULL;
    }
    if (v->_data == NULL)
    {
        _VECTOR_STATUS_PRINTER(VECTOR_EMPTY, "Vector_GetAt");
        return NULL;
    }
    if (index >= v->_size)
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INDEX_OUT_OF_RANGE, "Vector_GetAt");
        return NULL;
    }

    return (char *)v->_data + (index * v->_element_size);
}


VectorStatus Vector_SetAt(Vector *v, size_t index, void* value)
{
    if (v == NULL || v->_data == NULL || value == NULL)
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_SetAt");
        return VECTOR_INVALID_ARGUMENT;
    }
    
    if (index >= v->_size)
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INDEX_OUT_OF_RANGE, "Vector_SetAt");
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
            _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_PushBack");
        return VECTOR_INVALID_ARGUMENT;
    }

    size_t index = v->_size;

    if (index >= v->_capacity)
    {
        void *value_saver = ds_malloc(v->_element_size);
        if (value_saver == NULL)
        {
            _VECTOR_STATUS_PRINTER(VECTOR_ALLOCATION_FAILURE, "Vector_PushBack");
            return VECTOR_ALLOCATION_FAILURE;
        }

        memcpy(value_saver, value, v->_element_size);

        VectorStatus status = _Vector_resize(v);
        if (status != VECTOR_SUCCESS)
        {
            ds_free(value_saver);
            _VECTOR_STATUS_PRINTER(status, "Vector_PushBack");
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
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_Destroy");
        return;
    }

    ds_free(v->_data);
    ds_free(v);
}

void Vector_Clear(Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_Clear");
        return;
    }

    v->_size = 0;
}

VectorStatus Vector_PopBack(Vector *v)
{
    if (!_Is_Vector_Valid(v))
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_PopBack");
        return VECTOR_INVALID_ARGUMENT;
    }

    if (v->_size == 0)
    {
        _VECTOR_STATUS_PRINTER(VECTOR_EMPTY, "Vector_PopBack");
        return VECTOR_EMPTY;
    }

    v->_size--;

    return VECTOR_SUCCESS;
}

VectorStatus Vector_Resize(Vector *v, size_t new_size)
{
    if (!_Is_Vector_Valid(v))
    {
        _VECTOR_STATUS_PRINTER(VECTOR_INVALID_ARGUMENT, "Vector_Resize");
        return VECTOR_INVALID_ARGUMENT;
    }

    while (new_size > v->_capacity)
    {
        VectorStatus status = _Vector_resize(v);
        if (status != VECTOR_SUCCESS)
        {
            _VECTOR_STATUS_PRINTER(status, "Vector_Resize");
            return status;
        }
    }

    v->_size = new_size;
    return VECTOR_SUCCESS;
}
