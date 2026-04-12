#include "vector.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

struct Vector{
    void* data;
    size_t size;
    size_t capacity;
    const FieldInfo* info;
};

Vector* vector_create(const FieldInfo* info){
    if (!info){
        set_error(ERROR_NULL_VECTOR, "Cannot create vector with NULL FieldInfo");
        return NULL;
    }
    
    Vector* v = (Vector*)malloc(sizeof(Vector));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->info = info;
    return v;
}

void vector_destroy(Vector* v){
    if (!v) return;
    
    if (v->info->free) {
        for (size_t i = 0; i < v->size; i++) {
            char* elem = (char*)v->data + i * v->info->size;
            v->info->free(elem);
        }
    }
    
    free(v->data);
    free(v);
}

static void expand(Vector* v){
    if (v->size >= v->capacity){
        if (v->capacity == 0){
            v->capacity = 4;
        } else{
            v->capacity = v->capacity * 2;
        }
        v->data = realloc(v->data, v->capacity * v->info->size);
    }
}

void vector_push_back(Vector* v, void* elem){
    if (!v){
        set_error(ERROR_NULL_VECTOR, "Cannot push to NULL vector");
        return;
    }
    if (!elem){
        set_error(ERROR_NULL_ELEMENT, "Cannot push NULL element");
        return;
    }
    
    expand(v);
    char* dest = (char*)v->data + v->size * v->info->size;
    memcpy(dest, elem, v->info->size);
    v->size++;
}

void* vector_get(Vector* v, size_t index){
    if (!v){
        set_error(ERROR_NULL_VECTOR, "Cannot get from NULL vector");
        return NULL;
    }
    if (index >= v->size){
        set_error(ERROR_OUT_OF_BOUNDS, "Index out of bounds");
        return NULL;
    }
    return (char*)v->data + index * v->info->size;
}

size_t vector_size(Vector* v){
    return v ? v->size : 0;
}


void vector_reserve(Vector* v, size_t new_capacity){
    if (!v) return;
    if (new_capacity > v->capacity){
        v->data = realloc(v->data, new_capacity * v->info->size);
        v->capacity = new_capacity;
    }
}

Vector* vector_add(Vector* a, Vector* b){
    if (!a || !b){
        set_error(ERROR_NULL_VECTOR, "Cannot add NULL vectors");
        return NULL;
    }
    
    if (a->info != b->info){
        set_error(ERROR_DIFFERENT_TYPES, "Cannot add vectors of different types");
        return NULL;
    }
    
    if (a->size != b->size){
        set_error(ERROR_DIFFERENT_SIZES, "Cannot add vectors of different sizes");
        return NULL;
    }
    
    Vector* result = vector_create(a->info);
    vector_reserve(result, a->size);
    result->size = a->size;
    
    for (size_t i = 0; i < a->size; i++) {
        char* dest = (char*)result->data + i * result->info->size;
        void* elem_a = vector_get(a, i);
        void* elem_b = vector_get(b, i);
        result->info->add(dest, elem_a, elem_b);
    }
    
    return result;
}

void* dot_product(Vector* a, Vector* b){
    if (!a || !b){
        set_error(ERROR_NULL_VECTOR, "Cannot compute dot product of NULL vectors");
        return NULL;
    }
    
    if (a->info != b->info){
        set_error(ERROR_DIFFERENT_TYPES, "Cannot compute dot product of different types");
        return NULL;
    }
    
    if (a->size != b->size){
        set_error(ERROR_DIFFERENT_SIZES, "Cannot compute dot product of different sizes");
        return NULL;
    }
    
    void* result = malloc(a->info->size);
    memset(result, 0, a->info->size);
    
    for (size_t i = 0; i < a->size; i++){
        void* elem_a = vector_get(a, i);
        void* elem_b = vector_get(b, i);
        
        void* product = malloc(a->info->size);
        a->info->multiply(product, elem_a, elem_b);
        a->info->add(result, result, product);
        free(product);
    }
    
    return result;
}


const FieldInfo* vector_get_info(Vector* v){
    return v ? v->info : NULL;
}

size_t vector_capacity(Vector* v){
    return v ? v->capacity : 0;
}