#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

void plus_matrices(int arr[][100][100], int m[], int n[], int indices[], int num_to_add, int result[][100][100]);
void substraction_matrices(int arr[][100][100], int m[], int n[], int indices[], int num_to_subtract, int result[][100][100]);
void multiply_matrices(int arr[][100][100], int m[], int n[], int indices[], int num_to_multiply, int result[][100][100]);
void scalar_multiply(int arr[][100], int m, int n, int scalar, int result[][100][100]);
void basic_operations_menu(int arr[][100][100], int m[], int n[], int *num_matrices);

#endif // BASIC_OPERATIONS_H
