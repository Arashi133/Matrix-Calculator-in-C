#include <stdio.h>
#include <stdlib.h>
#include "matrix_input.h"
#include "view_search.h"
#include "basic_operations.h"
#include "matrix_properties.h"
#include "matrix_transformations.h"
#include "row_operations.h"
#include "matrix_analysis.h"
#include "solve_system.h"
#include "load_save_delete.h"
#include "help.h"

#define MAX_MATRICES 100
#define MAX_DIM 100

int num_matrices = 0;
int m[MAX_DIM], n[MAX_DIM];
int arr[MAX_MATRICES][100][100];
int max, min;
int indices[100];
int result_counts = 0;
int result[MAX_MATRICES][100][100];

void display_menu() {
    printf("\n=== Matrix Calculator Menu ===\n");
    printf("1. Matrix Input/Generation\n");
    printf("2. View/Search Matrices\n");
    printf("3. Basic Matrix Operations\n");
    printf("4. Matrix Properties\n");
    printf("5. Matrix Transformations\n");
    printf("6. Elementary Row Operations\n");
    printf("7. Matrix Analysis\n");
    printf("8. Solve The System Of Equations\n");
    printf("9. Load/Save/Delete Matrices\n");
    printf("10. Help\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void main_menu() {
    int choice;
    do {
        print_main_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1: input_generation_menu(arr, m, n, &num_matrices); break;
            case 2: view_search_menu(arr, m, n, &num_matrices); break;
            case 3: basic_operations_menu(arr, m, n, &num_matrices); break;
            case 4: properties_menu(arr, m, n, &num_matrices); break;
            case 5: transformations_menu(arr, m, n, &num_matrices); break;
            case 6: row_operations_menu(arr, m, n, &num_matrices); break;
            case 7: analysis_menu(arr, m, n, &num_matrices); break;
            case 8: solve_equations(arr, m, n, &num_matrices); break;
            case 9: load_save_delete(arr, m, n, &num_matrices); break;
            case 10: help_menu(); break;
            case 0: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}