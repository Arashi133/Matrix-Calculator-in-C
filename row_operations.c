#include <stdio.h>
#include "row_operations.h"

void swap_rows(int arr[100][100], int m, int n, int row1, int row2) {
    for (int j = 0; j < n; j++) {
        int temp = arr[row1][j];
        arr[row1][j] = arr[row2][j];
        arr[row2][j] = temp;
    }
}

void multiply_row(int arr[100][100], int n, int row, int scalar) {
    for (int j = 0; j < n; j++) {
        arr[row][j] *= scalar;
    }
}

void add_multiple_of_row(int arr[100][100], int n, int row1, int row2, int scalar) {
    for (int j = 0; j < n; j++) {
        arr[row2][j] += scalar * arr[row1][j];
    }
}

void row_operations_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int choice, index, row1, row2, scalar;
    do {
        printf("\n--- Elementary Row Operations ---\n");
        printf("1. Swap rows\n");
        printf("2. Multiply row by scalar\n");
        printf("3. Add multiple of one row to another\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            printf("Enter the index of the matrix to operate on (1-%d): ", *num_matrices);
            scanf("%d", &index);
            index--;
        }

        switch(choice) {
            case 1:
                printf("Enter the two row numbers to swap: ");
                scanf("%d %d", &row1, &row2);
                row1--; row2--;
                swap_rows(arr[index], m[index], n[index], row1, row2);
                printf("Rows swapped. Updated matrix:\n");
                print2DArray(arr[index], m[index], n[index]);
                break;
            case 2:
                printf("Enter the row number and scalar: ");
                scanf("%d %d", &row1, &scalar);
                row1--;
                multiply_row(arr[index], n[index], row1, scalar);
                printf("Row multiplied. Updated matrix:\n");
                print2DArray(arr[index], m[index], n[index]);
                break;
            case 3:
                printf("Enter source row, target row, and scalar: ");
                scanf("%d %d %d", &row1, &row2, &scalar);
                row1--; row2--;
                add_multiple_of_row(arr[index], n[index], row1, row2, scalar);
                printf("Row operation completed. Updated matrix:\n");
                print2DArray(arr[index], m[index], n[index]);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}