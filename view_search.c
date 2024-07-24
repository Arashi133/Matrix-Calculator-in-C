#include <stdio.h>
#include "view_search.h"

#define MAX_MATRICES 100

void search_and_print_matrix(int num_matrices, int search_index) {
    if (search_index < 1 || search_index > num_matrices) {
        printf("Invalid matrix number. Please enter a number between 1 and %d.\n", num_matrices);
    } else {
        printf("Matrix %d:\n", search_index);
        print2DArray(arr[search_index - 1], m[search_index - 1], n[search_index - 1]);
    }
}

void view_search_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int choice;
    do {
        printf("\n--- View/Search Menu ---\n");
        printf("1. View all matrices\n");
        printf("2. Search and view specific matrix\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                for (int k = 0; k < *num_matrices; k++) {
                    printf("Matrix %d:\n", k + 1);
                    print2DArray(arr[k], m[k], n[k]);
                }
                break;
            case 2:
                if (*num_matrices == 0) {
                    printf("No matrices to print. Please input matrices first.\n");
                } else {
                    int num_search;
                    printf("How many matrices do you want to find? ");
                    scanf("%d", &num_search);
                    for (int i = 0; i < num_search; i++) {
                        int search_index;
                        printf("Index of matrix which is need to be found: ");
                        scanf("%d", &search_index);
                        search_and_print_matrix(*num_matrices, search_index);
                    }
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}