#include "real.h"
#include <stdio.h>
#include <stdlib.h>

static FieldInfo* real_info = NULL;

static void print_real(void* elem){
    printf("%.2f", *(double*)elem);
}

static void add_real(void* res, void* a, void* b){
    *(double*)res = *(double*)a + *(double*)b;
}

static void multiply_real(void* res, void* a, void* b){
    *(double*)res = *(double*)a * *(double*)b;
}

static void* copy_real(void* elem) {
    double* p = (double*)malloc(sizeof(double));
    *p = *(double*)elem;
    return p;
}

static void free_real(void* elem){
    free(elem);
}

const FieldInfo* get_real_field_info(void){
    if (real_info == NULL){
        real_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        real_info->size = sizeof(double);
        real_info->print = print_real;
        real_info->add = add_real;
        real_info->multiply = multiply_real;
        real_info->copy = copy_real;
        real_info->free = free_real;
        real_info->name = "real";
    }
    return real_info;
}