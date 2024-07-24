#include <stdio.h>
#include "basic_operations.h"

#define MAX_MATRICES 100
int result_counts;
int indices[MAX_MATRICES];
int result[MAX_MATRICES][MAX_MATRICES][MAX_MATRICES];

void plus_matrices(int arr[][100][100], int m[], int n[], int indices[], int num_to_add, int result[][100][100]) {
    if (result_counts >= MAX_MATRICES) {
        printf("Cannot save more results. Maximum limit reached.\n");
        return;
    }

    for (int i = 0; i < m[indices[0]]; i++) {
        for (int j = 0; j < n[indices[0]]; j++) {
            result[result_counts][i][j] = arr[indices[0]][i][j];
            for (int k = 0; k < num_to_add; k++) {
                result[result_counts][i][j] += arr[indices[k]][i][j];
            }
        }
    }
    printf("Addition result saved as result %d.\n", result_counts + 1);
    result_counts++;
}

void substraction_matrices(int arr[][100][100], int m[], int n[], int indices[], int num_to_subtract, int result[][100][100]) {
    if (result_counts >= MAX_MATRICES) {
        printf("Cannot save more results. Maximum limit reached.\n");
        return;
    }
    
    for (int i = 0; i < m[indices[0]]; i++) {
        for (int j = 0; j < n[indices[0]]; j++) {
            result[result_counts][i][j] = arr[indices[0]][i][j];
            for (int k = 1; k < num_to_subtract; k++) {
                result[result_counts][i][j] -= arr[indices[k]][i][j];
            }
        }
    }

    printf("Substraction result saved as result %d.\n", result_counts + 1);
    result_counts++;
}

void multiply_matrices(int arr[][100][100], int m[], int n[], int indices[], int num_to_multiply, int result[][100][100]) {
    int temp[100][100];
    
    if (result_counts >= MAX_MATRICES) {
        printf("Cannot save more results. Maximum limit reached.\n");
        return;
    }
    
    for (int i = 0; i < m[indices[0]]; i++) {
        for (int j = 0; j < n[indices[num_to_multiply-1]]; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < n[indices[0]]; k++) {
                temp[i][j] += arr[indices[0]][i][k] * arr[indices[1]][k][j];
            }
        }
    }
    
    for (int l = 2; l < num_to_multiply; l++) {
        for (int i = 0; i < m[indices[0]]; i++) {
            for (int j = 0; j < n[indices[l]]; j++) {
                result[result_counts][i][j] = 0;
                for (int k = 0; k < n[indices[l-1]]; k++) {
                    result[result_counts][i][j] += temp[i][k] * arr[indices[l]][k][j];
                }
            }
        }
        for (int i = 0; i < m[indices[0]]; i++) {
            for (int j = 0; j < n[indices[l]]; j++) {
                temp[i][j] = result[result_counts][i][j];
            }
        }
    }

    printf("Multiplication result saved as result %d.\n", result_counts + 1);
    result_counts++;
}

void scalar_multiply(int arr[][100], int m, int n, int scalar, int result[][100][100]) {
    if (result_counts >= MAX_MATRICES) {
        printf("Cannot save more results. Maximum limit reached.\n");
        return;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[result_counts][i][j] = scalar * arr[i][j];
        }
    }

    printf("Scalar multiplication result saved as result %d.\n", result_counts + 1);
    result_counts++;
}

void basic_operations_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int choice;
    do {
        printf("\n--- Basic Operations Menu ---\n");
        printf("1. Add matrices\n");
        printf("2. Subtract matrices\n");
        printf("3. Multiply matrices\n");
        printf("4. Scalar multiplication\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if (*num_matrices == 0) {
                    printf("Please input matrices first.\n");
                } else {
                    int num_to_add;
                    printf("Enter the indices of the matrices you want to add (1-%d):\n", *num_matrices);
                    while (num_to_add < 0 || num_to_add >= *num_matrices) {
                        printf("Invalid matrix index.\n");
                        printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                        scanf("%d", &num_to_add);
                    }
                    for (int i = 0; i < num_to_add; i++) {
                        scanf("%d", &indices[i]);
                        indices[i]--;  // Adjust for 0-based indexing
                    }
        
                    // Check if dimensions match
                    for (int i = 1; i < num_to_add; i++) {
                        if (m[indices[i]] != m[indices[0]] || n[indices[i]] != n[indices[0]]) {
                            printf("Error: Matrices must have the same dimensions for addition.\n");
                            break;
                        }
                    }
        
                    plus_matrices(arr, m, n, indices, num_to_add, result);
                    printf("Result of addition:\n");
                    print2DArray(result[result_counts-1], m[indices[0]], n[indices[0]]);
                }
                break;
            case 2:
                if (*num_matrices == 0) {
                    printf("Please input matrices first.\n");
                } else {
                    int num_to_subtract;
                    printf("Enter the indices of the matrices you want to subtraction (1-%d):\n", *num_matrices);
                    while (num_to_subtract < 0 || num_to_subtract >= *num_matrices) {
                        printf("Invalid matrix index.\n");
                        printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                        scanf("%d", &num_to_subtract);
                    }
                    for (int i = 0; i < num_to_subtract; i++) {
                        scanf("%d", &indices[i]);
                        indices[i]--;  // Adjust for 0-based indexing
                    }
        
                    // Check if dimensions match
                    for (int i = 1; i < num_to_subtract; i++) {
                        if (m[indices[i]] != m[indices[0]] || n[indices[i]] != n[indices[0]]) {
                            printf("Error: Matrices must have the same dimensions for subtraction.\n");
                            break;
                        }
                    }
        
                    substraction_matrices(arr, m, n, indices, num_to_subtract, result);
                    printf("Result of subtraction:\n");
                    print2DArray(result[result_counts-1], m[indices[0]], n[indices[0]]);
                }
                break;
            case 3:
                if (*num_matrices == 0) {
                    printf("Please input matrices first.\n");
                } else {
                    int num_to_multiply;
                    printf("Enter the indices of the matrices you want to multiplication (1-%d):\n", *num_matrices);
                    while (num_to_multiply < 0 || num_to_multiply >= *num_matrices) {
                        printf("Invalid matrix index.\n");
                        printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                        scanf("%d", &num_to_multiply);
                    }
                    for (int i = 0; i < num_to_multiply; i++) {
                        scanf("%d", &indices[i]);
                        indices[i]--;  // Adjust for 0-based indexing
                    }
        
                    // Check if dimensions match
                    for (int i = 1; i < num_to_multiply; i++) {
                        if (m[indices[i]] != m[indices[0]] || n[indices[i]] != n[indices[0]]) {
                            printf("Error: Matrices must have the same dimensions for multiplication.\n");
                            break;
                        }
                    }
        
                    multiply_matrices(arr, m, n, indices, num_to_multiply, result);
                    printf("Result of multiplication:\n");
                    print2DArray(result[result_counts-1], m[indices[0]], n[indices[0]]);
                }
                break;
            case 4:
                int index, scalar;
                printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                scanf("%d", &index);
                while (index < 0 || index >= *num_matrices) {
                    printf("Invalid matrix index.\n");
                    printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                }
                index--;
                printf("Enter a scalar: ");
                scanf("%d", &scalar);
                printf("Result of scalar multiplication:\n");
                scalar_multiply(arr[index], m[index], n[index], scalar, result);
                print2DArray(result[result_counts-1], m[index], n[index]);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}