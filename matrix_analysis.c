#include <stdio.h>
#include "matrix_analysis.h"

int is_symmetric(int arr[][100], int m, int n) {
    if (m != n) {
        return 0; // Non-square matrices can't be symmetric
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i][j] != arr[j][i]) {
                return 0; // Not symmetric
            }
        }
    }
    return 1; // Symmetric
}

int is_orthogonal(int arr[][100], int m, int n) {
    if (m != n)
        return 0;
    
    int transposed[100][100];
    transpose(arr, m, n);

    int product[100][100];
    int indices[2] = {0, 1};  // Indices for the original matrix and its transpose
    int temp_arr[2][100][100];
    
    // Copy the original matrix and its transpose to temp_arr
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            temp_arr[0][i][j] = arr[i][j];
            temp_arr[1][i][j] = transposed[i][j];
        }
    }

    multiply_matrices(temp_arr, &m, &n, indices, 2, product);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j && arr[i][j] != 1) return 0;
            if (i != j && arr[i][j] != 0) return 0;
        }
    }
    return 1;
}

void analysis_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int choice, index;
    do {
        printf("\n--- Matrix Analysis ---\n");
        printf("1. Check for symmetry\n");
        printf("2. Check for orthogonality\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the index of the matrix to check for symmetry (1-%d): ", *num_matrices);
                scanf("%d", &index);
                while (index < 0 || index >= *num_matrices) {
                    printf("Invalid matrix index.\n");
                    printf("Enter the index of the matrix to check for symmetry (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                }
                if (is_symmetric(arr[index], m[index], n[index])) {
                    printf("Matrix %d is symmetric.\n", index + 1);
                } else {
                    printf("Matrix %d is not symmetric.\n", index + 1);
                }
                break;
            case 2:
                printf("Enter the index of the matrix to check for orthogonality (1-%d): ", *num_matrices);
                scanf("%d", &index);
                while (index < 0 || index >= *num_matrices) {
                    printf("Invalid matrix index.\n");
                    printf("Enter the index of the matrix to check for orthogonality (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                }
                index--;
                if (is_orthogonal(arr[index], m[index], n[index])) {
                    printf("Matrix %d is orthogonal.\n", index + 1);
                } else {
                    printf("Matrix %d is not orthogonal.\n", index + 1);
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}