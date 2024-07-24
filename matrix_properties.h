#ifndef MATRIX_PROPERTIES_H
#define MATRIX_PROPERTIES_H

void eliminate_matrices(int arr[][100], int m, int n);
void eliminate_Gauss_matrices(int (*eliminate)[][100], int m, int n);
int findRank(int arr[][100], int m, int n);
int determinant(int (*eliminate)[][100], int m, int n, int *rank);
void properties_menu(int arr[][100][100], int m[], int n[], int *num_matrices);

#endif // MENUMATRIX_PROPERTIES_H_H
