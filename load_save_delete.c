#include <stdio.h>
#include "load_save_delete.h"

#define MAX_MATRICES 100
#define MAX_DIM 100

int num_matrices = 0;
int m[MAX_DIM], n[MAX_DIM];
int arr[MAX_MATRICES][100][100];
int indices[100];
int result_counts = 0;
int result[MAX_MATRICES][100][100];

void save_matrix(int arr[][100], int rows, int cols) {
    if (result_counts < MAX_MATRICES) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[result_counts][i][j] = arr[i][j];
            }
        }
        result_counts++;
        printf("Matrix saved. Total saved matrices: %d\n", result_counts);
    } else {
        printf("Maximum number of saved matrices reached. Cannot save more.\n");
    }
}

void load_matrix(int arr[][100], int *rows, int *cols, int index) {
    if (index >= 0 && index < result_counts) {
        *rows = m[indices[0]];
        *cols = n[indices[0]];
        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                arr[i][j] = result[index][i][j];
            }
        }
        printf("Matrix loaded from result %d.\n", index + 1);
    } else {
        printf("Invalid index. No matrix loaded.\n");
    }
}

void view_saved_matrices() {
    if (result_counts == 0) {
        printf("No matrices saved.\n");
        return;
    }
    
    for (int i = 0; i < result_counts; i++) {
        printf("\nMatrix %d: (%dx%d)\n", i+1, m[indices[0]], n[indices[0]]);
        print2DArray(result[i], m[indices[0]], n[indices[0]]);
    }
}

void delete_saved_matrix(int index) {
    if (index >= 0 && index < result_counts) {
        for (int i = index; i < result_counts - 1; i++) {
            for (int j = 0; j < m[indices[0]]; j++) {
                for (int k = 0; k < n[indices[0]]; k++) {
                    result[i][j][k] = result[i + 1][j][k];
                }
            }
        }
        result_counts--;
        printf("Matrix deleted. Remaining saved matrices: %d\n", result_counts);
    } else {
        printf("Invalid index. No matrix deleted.\n");
    }
}

void delete_input_matrix(int arr[][100][100], int m[], int n[], int *num_matrices, int index) {
    if (index < 0 || index >= *num_matrices) {
        printf("Invalid matrix index. No matrix deleted.\n");
        return;
    }

    // Shift all matrices after the deleted one
    for (int i = index; i < *num_matrices - 1; i++) {
        for (int j = 0; j < m[i+1]; j++) {
            for (int k = 0; k < n[i+1]; k++) {
                arr[i][j][k] = arr[i+1][j][k];
            }
        }
        m[i] = m[i+1];
        n[i] = n[i+1];
    }

    (*num_matrices)--;
    printf("Matrix at index %d deleted. Total matrices: %d\n", index + 1, *num_matrices);
}

void load_save_delete(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int choice, index;
    do {
        printf("\n--- Load, Save, and Delete Matrices ---\n");
        printf("1. Load matrix from result\n");
        printf("2. Save matrix to result\n");
        printf("3. Delete matrices\n");
        printf("4. Delete result\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                if (result_counts == 0) {
                    printf("No results available to load.\n");
                } else {
                    printf("Enter the index of the result to load (0-%d): ", result_counts - 1);
                    scanf("%d", &index);
                    if (index < 0 || index >= result_counts) {
                        printf("Invalid result index.\n");
                    } else {
                        if (*num_matrices >= MAX_MATRICES) {
                            printf("Cannot load more matrices. Maximum limit reached.\n");
                        } else {
                            m[*num_matrices] = m[indices[0]];
                            n[*num_matrices] = n[indices[0]];
                            for (int i = 0; i < m[indices[0]]; i++) {
                                for (int j = 0; j < n[indices[0]]; j++) {
                                    arr[*num_matrices][i][j] = result[index][i][j];
                                }
                            }
                            (*num_matrices)++;
                            printf("Result loaded as matrix %d.\n", *num_matrices);
                        }
                    }
                }
                break;
            case 2:
                if (*num_matrices == 0) {
                    printf("No matrices available to save.\n");
                } else {
                    printf("Enter the index of the matrix to save (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                    index--;
                    if (index < 0 || index >= *num_matrices) {
                        printf("Invalid matrix index.\n");
                    } else {
                        if (result_counts >= MAX_MATRICES) {
                            printf("Cannot save more results. Maximum limit reached.\n");
                        } else {
                            for (int i = 0; i < m[index]; i++) {
                                for (int j = 0; j < n[index]; j++) {
                                    result[result_counts][i][j] = arr[index][i][j];
                                }
                            }
                            result_counts++;
                            printf("Matrix saved as result %d.\n", result_counts);
                        }
                    }
                }
                break;
            case 3: 
                if (num_matrices == 0) {
                    printf("No matrices to delete.\n");
                } else {
                    int index;
                    printf("Enter the index of the matrix to delete (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                    if (index < 0 || index > *num_matrices) {
                        printf("Invalid matrix index.\n");
                    } else if (index == *num_matrices) {
                        *num_matrices = 0;
                        printf("All matrices deleted.\n");
                    } else {
                        delete_input_matrix(arr, m, n, num_matrices, index - 1);
                    }
                }
                break;
            case 4:
                result_counts = 0;
                printf("All results deleted.\n");
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}