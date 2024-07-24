#ifndef LOAD_SAVE_DELETE_H
#define LOAD_SAVE_DELETE_H

void save_matrix(int arr[][100], int rows, int cols);
void load_matrix(int arr[][100], int *rows, int *cols, int index);
void view_saved_matrices();
void delete_saved_matrix(int index);
void delete_input_matrix(int arr[][100][100], int m[], int n[], int *num_matrices, int index);
void load_save_delete(int arr[][100][100], int m[], int n[], int *num_matrices);

#endif // LOAD_SAVE_DELETE_H
