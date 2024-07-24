#include <stdio.h>
#include "matrix_properties.h"

void eliminate_matrices(int arr[][100], int m, int n) {
    int eliminate[100][100];
    //Sao chep ma tran goc
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            eliminate[i][j] = arr[i][j];

    for (int i = 0; i < m; i++) {
        if (eliminate[i][i] == 0) {
            return;
        }
        for (int j = 0; j < m; j++) {
            if (j != i) {
                float ratio = (float)eliminate[j][i] / eliminate[i][i];
                for (int k = 0; k < n; k++) {
                    eliminate[j][k] -= ratio * eliminate[i][k];
                }
            }
        }
    }
    
    //In ma tran
    print2DArray(eliminate, m, n);
}

void eliminate_Gauss_matrices(int (*eliminate)[][100], int m, int n) {
    int eliminate_Gauss[100][100];
    //Sao chep ma tran goc
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            eliminate_Gauss[i][j] = (*eliminate)[i][j];

    //Chuan hoa dong
    for (int i = 0; i < m; i++) {
        float factor = eliminate_Gauss[i][i];
        for (int j = 0; j < n; j++) {
            eliminate_Gauss[i][j] /= factor;
        }
    }

    //In ma tran dang bac thang
    print2DArray(eliminate_Gauss, m, n);
}

int findRank(int arr[][100], int m, int n) {
    int rank = 0;
    
    for (int i = 0; i < m; i++) {
        int nonzeroRow = -1;

        //Tim gia tri khac 0 gan nhat tai dong dang xu ly
        for (int j = 0; j < n; j++) {
            if (arr[i][j] != 0) {
                nonzeroRow = i;
                break;
            }
        }

        //nonzeroRow khac -1 thi rank tang 1 don vi va thuc hien thuat toan tim dang ma tran bac thang
        if (nonzeroRow != -1) {
            rank++;
            eliminate_matrices(arr, m, n);
        }
    }

    return rank;
}

int determinant(int (*eliminate)[][100], int m, int n, int *rank){
    if (m != n) {
        printf("Cannot calculate the determinant of this matrix.\n");
        return 0;
    } else if (*rank < n) {
        return 0;
    } else {
        int det = 1;
        for (int i = 0; i < m; i++){
            det = det * (*eliminate)[i][i];
        }
        return det;
    }
}

void properties_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int choice, index;
    do {
        printf("\n--- Matrix Properties ---\n");
        printf("1. Calculate determinant\n");
        printf("2. Calculate trace\n");
        printf("3. Transpose matrix\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                scanf("%d", &index);
                while (index < 0 || index >= *num_matrices) {
                    printf("Invalid matrix index.\n");
                    printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                }
                index--;
                if (m[index] != n[index]) {
                    printf("Determinant can only be calculated for square matrices.\n");
                } else {
                    int rank = findRank(arr[index], m[index], n[index]);
                    int det = determinant(arr[index], m[index], n[index], &rank);
                    printf("Determinant of matrix %d is: %d\n", index + 1, det);
                }
                break;
            case 2:
                printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                scanf("%d", &index);
                while (index < 0 || index >= *num_matrices) {
                    printf("Invalid matrix index.\n");
                    printf("Enter the index of the matrix (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                }
                index--;
                if (m[index] != n[index]) {
                    printf("Trace can only be calculated for square matrices.\n");
                } else {
                    int trace = 0;
                    for (int i = 0; i < m[index]; i++) {
                        trace += arr[index][i][i];
                    }
                    printf("Trace of matrix %d is: %d\n", index + 1, trace);
                }
                break;
            case 3:
                printf("Enter the index of the matrix to transpose (1-%d): ", *num_matrices);
                scanf("%d", &index);
                while (index < 0 || index >= *num_matrices) {
                    printf("Invalid matrix index.\n");
                    printf("Enter the index of the matrix to transpose (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                }
                index--;
                transpose(arr[index], m[index], n[index]);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}
