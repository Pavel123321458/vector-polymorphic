#ifdef __cplusplus
extern "C" {
#endif

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct FieldInfo FieldInfo;
typedef struct Vector Vector;

struct FieldInfo{
    size_t size;
    void (*print)(void* elem);
    void (*add)(void* res, void* a, void* b);
    void (*multiply)(void* res, void* a, void* b);
    void* (*copy)(void* elem);
    void (*free)(void* elem);
    const char* name;
};


Vector* vector_create(const FieldInfo* info);
void vector_destroy(Vector* v);
void vector_push_back(Vector* v, void* elem);
void* vector_get(Vector* v, size_t index);
size_t vector_size(Vector* v);
void vector_print(Vector* v);
Vector* vector_add(Vector* a, Vector* b);
void* dot_product(Vector* a, Vector* b);
void vector_reserve(Vector* v, size_t new_capacity);

size_t vector_capacity(Vector* v);

const FieldInfo* vector_get_info(Vector* v);
size_t vector_capacity(Vector* v);

#endif

#ifdef __cplusplus
}
#endif