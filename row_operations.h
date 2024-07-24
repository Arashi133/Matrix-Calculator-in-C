#ifndef ROW_OPERATIONS_H
#define ROW_OPERATIONS_H

void swap_rows(int arr[100][100], int m, int n, int row1, int row2);
void multiply_row(int arr[100][100], int n, int row, int scalar);
void add_multiple_of_row(int arr[100][100], int n, int row1, int row2, int scalar);
void row_operations_menu(int arr[][100][100], int m[], int n[], int *num_matrices);

#endif // ROW_OPERATIONS_H
