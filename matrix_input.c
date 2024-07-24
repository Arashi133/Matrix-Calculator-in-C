#include <stdio.h>
#include "matrix_input.h"

#define MAX_MATRICES 100

void initializeArray(int arr[][100], int n, int m, int min, int max) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = min + rand() % (max - min + 1);
}

void input2DArray(int arr[][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Input value of arr[%d][%d]: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
}

void print2DArray(int arr[][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void input_generation_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    if (*num_matrices == 0) {
        printf("Enter the number of matrices you want to work with (max %d): ", MAX_MATRICES);
        scanf("%d", num_matrices);
        if (*num_matrices > MAX_MATRICES) {
            *num_matrices = MAX_MATRICES;
            printf("Number of matrices set to maximum allowed: %d\n", MAX_MATRICES);
        }
    }

    int matrices_left = *num_matrices;
    int choice;
    do {
        printf("\n--- Input/Generation Menu ---\n");
        printf("1. Input matrices manually\n");
        printf("2. Generate random matrices\n");
        printf("3. Generate identity matrix\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (*num_matrices >= MAX_MATRICES && (choice == 1 || choice == 2 || choice == 3)) {
            printf("Maximum number of matrices (%d) reached. Cannot add more matrices.\n", MAX_MATRICES);
            continue;
        }

        switch(choice) {
            case 1:
                printf("Enter dimensions for matrix %d (m n): ", *num_matrices - matrices_left + 1);
                scanf("%d %d", &m[*num_matrices - matrices_left], &n[*num_matrices - matrices_left]);
                input2DArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left]);
                print2DArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left]);
                (*num_matrices)++;
                matrices_left--;
                break;
            case 2:
                int max, min;
                printf("Enter dimensions for matrix %d (m n): ", *num_matrices - matrices_left + 1);
                scanf("%d %d", &m[*num_matrices - matrices_left], &n[*num_matrices - matrices_left]);
                printf("Enter min and max values: ");
                scanf("%d %d", &min, &max);
                while (min > max) {
                    printf("Enter min and max values (min < max): ");
                    scanf("%d %d", &min, &max);
                }
                initializeArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left], min, max);
                print2DArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left]);
                (*num_matrices)++;
                matrices_left--;
                break;
            case 3:
                int size;
                printf("Enter size of identity matrix: ");
                scanf("%d", &size);
                m[*num_matrices - matrices_left] = n[*num_matrices - matrices_left] = size;
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        if (i != j)
                            arr[*num_matrices - matrices_left][i][j] = 0;
                        else 
                            arr[*num_matrices - matrices_left][i][j] = 1;
                    }
                }
                (*num_matrices)++;
                matrices_left--;
                printf("Identity matrix of size %d generated.\n", size);
                print2DArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left]);
                break;
            case 0:
                if (matrices_left > 0) {
                    printf("Warning: Not all matrices have been input. %d matrices left.\n", matrices_left);
                    printf("Do you want to continue to main menu? (1: Yes, 0: No): ");
                    int confirm;
                    scanf("%d", &confirm);
                    if (confirm == 0) {
                        choice = -1;  // Continue the loop
                    }
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        if (choice != 0) {
            printf("Matrix %d added. Total matrices: %d/%d\n", *num_matrices, *num_matrices, MAX_MATRICES);
        }

    } while (choice != 0);
}
