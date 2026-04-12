#include "tests.h"
#include "vector.h"
#include "real.h"
#include "complex.h"
#include "error.h"
#include "print.h"
#include <stdio.h>
#include <complex.h>

static void print_last_error(void){
    Error err = get_error();
    if(has_error()){
        printf("ERROR [%d]: %s\n", err.code, err.message);
    }
}

void run_all_tests(void){
    printf("\n========== RUNNING ALL TESTS ==========\n");
    
    printf("\n1. Test vector_create with NULL:\n");
    Vector* test = vector_create(NULL);
    print_last_error();
    if(test == NULL) printf("Correctly rejected NULL\n");
    
    printf("\n2. Test vector_push_back on NULL:\n");
    vector_push_back(NULL, NULL);
    print_last_error();
    
    printf("\n3. Test vector_get on empty vector:\n");
    const FieldInfo* real_info = get_real_field_info();
    Vector* empty = vector_create(real_info);
    vector_get(empty, 0);
    print_last_error();
    vector_destroy(empty);
    
    printf("\n4. Test vector_add with different types:\n");
    Vector* r1 = vector_create(get_real_field_info());
    Vector* c1 = vector_create(get_complex_field_info());
    double x = 1.0;
    double complex z = 1.0 + 1.0 * I;
    vector_push_back(r1, &x);
    vector_push_back(c1, &z);
    Vector* bad = vector_add(r1, c1);
    print_last_error();
    if(bad == NULL) printf("Correctly rejected mixed types\n");
    vector_destroy(r1);
    vector_destroy(c1);
    
    printf("\n5. Test vector_add with different sizes:\n");
    Vector* r2 = vector_create(get_real_field_info());
    Vector* r3 = vector_create(get_real_field_info());
    double a = 1.0, b = 2.0;
    vector_push_back(r2, &a);
    vector_push_back(r3, &b);
    vector_push_back(r3, &b);
    Vector* bad2 = vector_add(r2, r3);
    print_last_error();
    if(bad2 == NULL) printf("Correctly rejected different sizes\n");
    vector_destroy(r2);
    vector_destroy(r3);
    
    printf("\n6. Test dot_product with different types:\n");
    Vector* r4 = vector_create(get_real_field_info());
    Vector* c2 = vector_create(get_complex_field_info());
    double x2 = 1.0;
    double complex z2 = 1.0 + 1.0 * I;
    vector_push_back(r4, &x2);
    vector_push_back(c2, &z2);
    void* dot_bad = dot_product(r4, c2);
    print_last_error();
    if(dot_bad == NULL) printf("Correctly rejected mixed types in dot product\n");
    vector_destroy(r4);
    vector_destroy(c2);
    
    printf("\n7. Test dot_product with different sizes:\n");
    Vector* r5 = vector_create(get_real_field_info());
    Vector* r6 = vector_create(get_real_field_info());
    double x3 = 1.0, x4 = 2.0;
    vector_push_back(r5, &x3);
    vector_push_back(r6, &x4);
    vector_push_back(r6, &x4);
    void* dot_bad2 = dot_product(r5, r6);
    print_last_error();
    if(dot_bad2 == NULL) printf("Correctly rejected different sizes in dot product\n");
    vector_destroy(r5);
    vector_destroy(r6);
    
    printf("\n8. Test vector_get with out of bounds index:\n");
    Vector* r7 = vector_create(get_real_field_info());
    double val = 5.0;
    vector_push_back(r7, &val);
    vector_get(r7, 5);
    print_last_error();
    vector_destroy(r7);
    
    printf("\n9. Test vector_push_back with NULL element:\n");
    Vector* r8 = vector_create(get_real_field_info());
    vector_push_back(r8, NULL);
    print_last_error();
    vector_destroy(r8);
    
    printf("\n10. Test vector_reserve:\n");
    Vector* r9 = vector_create(get_real_field_info());
    vector_reserve(r9, 100);
    printf("Capacity after reserve: %zu\n", vector_capacity(r9));
    vector_destroy(r9);
    
    printf("\n========== TESTS COMPLETE ==========\n");
}