#include "complex.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

static FieldInfo* complex_info = NULL;

static void print_complex(void* elem) {
    double complex z = *(double complex*)elem;
    double real = creal(z);
    double imag = cimag(z);
    
    if (imag >= 0)
        printf("%.2f+%.2fi", real, imag);
    else
        printf("%.2f%.2fi", real, imag);
}

static void add_complex(void* res, void* a, void* b) {
    *(double complex*)res = *(double complex*)a + *(double complex*)b;
}

static void multiply_complex(void* res, void* a, void* b) {
    *(double complex*)res = *(double complex*)a * *(double complex*)b;
}

static void* copy_complex(void* elem) {
    double complex* p = (double complex*)malloc(sizeof(double complex));
    *p = *(double complex*)elem;
    return p;
}

static void free_complex(void* elem) {
    free(elem);
}

const FieldInfo* get_complex_field_info(void) {
    if (complex_info == NULL) {
        complex_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        complex_info->size = sizeof(double complex);
        complex_info->print = print_complex;
        complex_info->add = add_complex;
        complex_info->multiply = multiply_complex;
        complex_info->copy = copy_complex;
        complex_info->free = free_complex;
        complex_info->name = "complex";
    }
    return complex_info;
}