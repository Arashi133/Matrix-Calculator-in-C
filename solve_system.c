#include <stdio.h>
#include "solve_system.h"

void solve_linear_equations(int coefficients[100][100], int y[], int m, int n) {
    float augmented[100][100];
    float eliminated[100][100];
    
    // Create the augmented matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = coefficients[i][j];
        }
        augmented[i][n] = y[i];
    }
    
    // Perform Gaussian elimination
    eliminate_Gauss_matrices(&augmented[0][0], m, n+1);
    
    // Back substitution
    float x[100];
    for (int i = m - 1; i >= 0; i--) {
        x[i] = eliminated[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= eliminated[i][j] * x[j];
        }
    }
    
    // Print solution
    printf("Solution:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %f\n", i+1, x[i]);
    }
}

void solve_equations(int arr[][100][100], int m[], int n[], int *num_matrices) {
    printf("--- Solve The Systems Of Equations ---\n");
    if (*num_matrices == 0) {
        printf("No matrices available. Please input matrices first.\n");
    }

    int index;
    printf("Enter the index of the matrix to use as coefficients (1-%d): ", *num_matrices);
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= *num_matrices) {
        printf("Invalid matrix index.\n");
    }

    if (m[index] != n[index]) {
        printf("This system of equations has no result. \n");
    }

    int y[100];
    printf("Enter the %d y values:\n", m[index]);
    for (int i = 0; i < m[index]; i++) {
        scanf("%d", &y[i]);
    }

    solve_linear_equations(arr[index], y, m[index], n[index]);
}