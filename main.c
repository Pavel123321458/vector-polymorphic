#include "vector.h"
#include "real.h"
#include "complex.h"
#include "error.h"
#include "print.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

Vector* current_vector = NULL;
Vector* current_vector2 = NULL;

void print_menu(void){
    printf("\n========== MENU ==========\n");
    printf("1. Create real vector\n");
    printf("2. Create complex vector\n");
    printf("3. Add element to vector\n");
    printf("4. Print vector\n");
    printf("5. Get element by index\n");
    printf("6. Vector size\n");
    printf("7. Create second vector\n");
    printf("8. Vector addition\n");
    printf("9. Dot product\n");
    printf("10. Destroy vectors\n");
    printf("11. Run all tests\n");
    printf("0. Exit\n");
    printf("==========================\n");
    printf("Your choice: ");
}

void print_last_error(void){
    Error err = get_error();
    if(err.code != ERROR_NONE){
        printf("ERROR [%d]: %s\n", err.code, err.message);
    }
}

int main(void){
    int choice;
    
    printf("=== VECTOR PROGRAM ===\n");
    printf("Use menu to test vector operations\n");
    
    do{
        print_menu();
        scanf("%d", &choice);
        while(getchar() != '\n');
        
        switch(choice){
            case 1:{
                if(current_vector){
                    vector_destroy(current_vector);
                    current_vector = NULL;
                }
                current_vector = vector_create(get_real_field_info());
                if(current_vector){
                    printf("Real vector created\n");
                }
                else{
                    print_last_error();
                }
                break;
            }
            
            case 2:{
                if(current_vector){
                    vector_destroy(current_vector);
                    current_vector = NULL;
                }
                current_vector = vector_create(get_complex_field_info());
                if(current_vector){
                    printf("Complex vector created\n");
                }
                else{
                    print_last_error();
                }
                break;
            }
            
            case 3:{
                if(!current_vector && !current_vector2){
                    printf("No vectors created\n");
                    break;
                }
                
                int vec_choice;
                printf("Select vector (1-first, 2-second): ");
                scanf("%d", &vec_choice);
                while(getchar() != '\n');
                
                Vector* target = NULL;
                if(vec_choice == 1){
                    target = current_vector;
                    if(!target){
                        printf("First vector not created\n");
                        break;
                    }
                }
                else if(vec_choice == 2){
                    target = current_vector2;
                    if(!target){
                        printf("Second vector not created\n");
                        break;
                    }
                }
                else{
                    printf("Invalid choice\n");
                    break;
                }
                
                int type;
                printf("Element type (1-real, 2-complex): ");
                scanf("%d", &type);
                while(getchar() != '\n');
                
                if(type == 1){
                    double val;
                    printf("Enter real number: ");
                    scanf("%lf", &val);
                    while(getchar() != '\n');
                    vector_push_back(target, &val);
                    if(has_error()){
                        print_last_error();
                    }
                    else{
                        printf("Element added\n");
                    }
                }
                else if(type == 2){
                    double real, imag;
                    printf("Enter real part: ");
                    scanf("%lf", &real);
                    printf("Enter imaginary part: ");
                    scanf("%lf", &imag);
                    while(getchar() != '\n');
                    double complex z = real + imag * I;
                    vector_push_back(target, &z);
                    if(has_error()){
                        print_last_error();
                    }
                    else{
                        printf("Element added\n");
                    }
                }
                break;
            }
            
            case 4:{
                if(!current_vector && !current_vector2){
                    printf("No vectors created\n");
                    break;
                }
                
                int vec_choice;
                printf("Select vector to print (1-first, 2-second): ");
                scanf("%d", &vec_choice);
                while(getchar() != '\n');
                
                Vector* target = NULL;
                if(vec_choice == 1){
                    target = current_vector;
                }
                else if(vec_choice == 2){
                    target = current_vector2;
                }
                
                if(!target){
                    printf("Vector not created\n");
                    break;
                }
                
                printf("Vector: ");
                print_vector(target);
                printf("\n");
                break;
            }
            
            case 5:{
                if(!current_vector && !current_vector2){
                    printf("No vectors created\n");
                    break;
                }
                
                int vec_choice;
                printf("Select vector (1-first, 2-second): ");
                scanf("%d", &vec_choice);
                while(getchar() != '\n');
                
                Vector* target = NULL;
                if(vec_choice == 1){
                    target = current_vector;
                }
                else if(vec_choice == 2){
                    target = current_vector2;
                }
                
                if(!target){
                    printf("Vector not created\n");
                    break;
                }
                
                size_t index;
                printf("Enter index: ");
                scanf("%zu", &index);
                while(getchar() != '\n');
                void* elem = vector_get(target, index);
                if(has_error()){
                    print_last_error();
                }
                else if(elem){
                    printf("Element: ");
                    const FieldInfo* info = vector_get_info(target);
                    if(info && info->print){
                        info->print(elem);
                    }
                    printf("\n");
                }
                break;
            }
            
            case 6:{
                if(!current_vector && !current_vector2){
                    printf("No vectors created\n");
                    break;
                }
                
                int vec_choice;
                printf("Select vector (1-first, 2-second): ");
                scanf("%d", &vec_choice);
                while(getchar() != '\n');
                
                Vector* target = NULL;
                if(vec_choice == 1){
                    target = current_vector;
                }
                else if(vec_choice == 2){
                    target = current_vector2;
                }
                
                if(!target){
                    printf("Vector not created\n");
                    break;
                }
                
                printf("Vector size: %zu\n", vector_size(target));
                break;
            }
            
            case 7:{
                int type;
                printf("Create second vector (1-real, 2-complex): ");
                scanf("%d", &type);
                while(getchar() != '\n');
                
                if(current_vector2){
                    vector_destroy(current_vector2);
                    current_vector2 = NULL;
                }
                
                if(type == 1){
                    current_vector2 = vector_create(get_real_field_info());
                }
                else{
                    current_vector2 = vector_create(get_complex_field_info());
                }
                
                if(current_vector2){
                    printf("Second vector created\n");
                    printf("Use option 3 to add elements to it\n");
                }
                else{
                    print_last_error();
                }
                break;
            }
            
            case 8:{
                if(!current_vector || !current_vector2){
                    printf("Need two vectors (create second vector first)\n");
                    break;
                }
                Vector* sum = vector_add(current_vector, current_vector2);
                if(has_error()){
                    print_last_error();
                }
                if(sum){
                    printf("First vector: ");
                    print_vector(current_vector);
                    printf("\n");
                    printf("Second vector: ");
                    print_vector(current_vector2);
                    printf("\n");
                    printf("Sum: ");
                    print_vector(sum);
                    printf("\n");
                    vector_destroy(sum);
                }
                break;
            }
            
            case 9:{
                if(!current_vector || !current_vector2){
                    printf("Need two vectors (create second vector first)\n");
                    break;
                }
                void* dot = dot_product(current_vector, current_vector2);
                if(has_error()){
                    print_last_error();
                }
                if(dot){
                    printf("First vector: ");
                    print_vector(current_vector);
                    printf("\n");
                    printf("Second vector: ");
                    print_vector(current_vector2);
                    printf("\n");
                    printf("Dot product: ");
                    const FieldInfo* info = vector_get_info(current_vector);
                    if(info && info->print){
                        info->print(dot);
                    }
                    printf("\n");
                    free(dot);
                }
                break;
            }
            
            case 10:{
                if(current_vector){
                    vector_destroy(current_vector);
                    current_vector = NULL;
                    printf("First vector destroyed\n");
                }
                if(current_vector2){
                    vector_destroy(current_vector2);
                    current_vector2 = NULL;
                    printf("Second vector destroyed\n");
                }
                if(!current_vector && !current_vector2){
                    printf("No vectors to destroy\n");
                }
                break;
            }
            
            case 11:{
                run_all_tests();
                break;
            }
            
            case 0:{
                printf("Exiting...\n");
                break;
            }
            
            default:{
                printf("Invalid choice\n");
                break;
            }
        }
    } while(choice != 0);
    
    if(current_vector){
        vector_destroy(current_vector);
    }
    if(current_vector2){
        vector_destroy(current_vector2);
    }
    
    return 0;
}