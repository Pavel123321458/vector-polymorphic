#include "print.h"
#include <stdio.h>


void print_vector(Vector* v){
    if (!v){
        printf("NULL");
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < vector_size(v); i++){
        void* elem = vector_get(v, i);
        const FieldInfo* info = vector_get_info(v);
        if (info && info->print){
            info->print(elem);
        }
        if (i < vector_size(v) - 1){
            printf(", ");
        }
    }
    printf("]");
}