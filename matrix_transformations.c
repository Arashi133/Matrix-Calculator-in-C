#include <stdio.h>
#include "matrix_transformations.h"

void transpose(int arr[][100], int m, int n) {
    int result[100][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[j][i] = arr[i][j];
        }
    }
    print2DArray(result, n, m);
}

void transformations_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int index;
    printf("Enter the index of the matrix to inverse (1-%d): ", *num_matrices);
    scanf("%d", &index);
    while (index < 0 || index >= *num_matrices) {
        printf("Invalid matrix index.\n");
        printf("Enter the index of the matrix to inverse (1-%d): ", *num_matrices);
        scanf("%d", &index);
    }
    index--;
    printf("Inverse matrix of matrix %d is: \n", index + 1);
    inverseMatrix(arr[index], m[index], n[index]);
}