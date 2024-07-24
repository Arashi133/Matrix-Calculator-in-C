#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_MATRICES 100
#define MAX_DIM 100

int num_matrices = 0;
int m[MAX_DIM], n[MAX_DIM];
int arr[MAX_MATRICES][100][100];
int max, min;
int indices[100];
int result_counts = 0;
int result[MAX_MATRICES][100][100];

void initializeArray(int arr[][100], int n, int m, int min, int max) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = min + rand() % (max - min + 1);
}

void input2DArray(int arr[][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Input value of arr[%d][%d]: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
}

void print2DArray(int arr[][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

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

void search_and_print_matrix(int num_matrices, int search_index) {
    if (search_index < 1 || search_index > num_matrices) {
        printf("Invalid matrix number. Please enter a number between 1 and %d.\n", num_matrices);
    } else {
        printf("Matrix %d:\n", search_index);
        print2DArray(arr[search_index - 1], m[search_index - 1], n[search_index - 1]);
    }
}

void transpose(int arr[][100], int m, int n) {
    int result[100][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[j][i] = arr[i][j];
        }
    }
    print2DArray(result, n, m);
}

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

void adjointMatrix(int arr[][100], int m, int n, int *rank, int adjoint[][100]) {
    if (m == n) {
        if (n == 1) {
            adjoint[0][0] = 1;
            return;
        }

        int temp[100][100];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
            int subRow = 0;
                for (int row = 0; row < n; row++) {
                if (row == i) continue; // Skip the excluded row
            
                int subCol = 0;
                for (int col = 0; col < n; col++) {
                    if (col == j) continue; // Skip the excluded column
                    temp[subRow][subCol] = arr[row][col];
                    subCol++;
                }
            subRow++;
        }
            adjoint[j][i] = (int)pow(-1, i+j) * determinant(temp, n - 1, n - 1, &rank);
            }
        }
    }
}

void inverseMatrix(int arr[][100], int m, int n) {
    float inverse_arr[100][100];
    int adjoint[100][100];
    int rank = findRank(arr, m, n);
    float det = determinant(&arr[0][0], m, n, &rank);
    if (m != n || det == 0)
        printf("This matrix doesn't have an inverse one.\n");
    else {
        adjointMatrix(arr, m, n, &rank, adjoint);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                inverse_arr[i][j] = adjoint[i][j] / (float)(det);
    }

    //In ma tran nghich dao
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", inverse_arr[i][j]);
        }
        printf("\n");
    }
}

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

int is_symmetric(int arr[][100], int m, int n) {
    if (m != n) {
        return 0; // Non-square matrices can't be symmetric
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i][j] != arr[j][i]) {
                return 0; // Not symmetric
            }
        }
    }
    return 1; // Symmetric
}

int is_orthogonal(int arr[][100], int m, int n) {
    if (m != n)
        return 0;
    
    int transposed[100][100];
    transpose(arr, m, n);

    int product[100][100];
    int indices[2] = {0, 1};  // Indices for the original matrix and its transpose
    int temp_arr[2][100][100];
    
    // Copy the original matrix and its transpose to temp_arr
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            temp_arr[0][i][j] = arr[i][j];
            temp_arr[1][i][j] = transposed[i][j];
        }
    }

    multiply_matrices(temp_arr, &m, &n, indices, 2, product);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j && arr[i][j] != 1) return 0;
            if (i != j && arr[i][j] != 0) return 0;
        }
    }
    return 1;
}

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

void input_generation_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    if (*num_matrices == 0) {
        printf("Enter the number of matrices you want to work with (max %d): ", MAX_MATRICES);
        scanf("%d", num_matrices);
        if (*num_matrices > MAX_MATRICES) {
            *num_matrices = MAX_MATRICES;
            printf("Number of matrices set to maximum allowed: %d\n", MAX_MATRICES);
        }
    }

    int matrices_left = *num_matrices;
    int choice;
    do {
        printf("\n--- Input/Generation Menu ---\n");
        printf("1. Input matrices manually\n");
        printf("2. Generate random matrices\n");
        printf("3. Generate identity matrix\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (*num_matrices >= MAX_MATRICES && (choice == 1 || choice == 2 || choice == 3)) {
            printf("Maximum number of matrices (%d) reached. Cannot add more matrices.\n", MAX_MATRICES);
            continue;
        }

        switch(choice) {
            case 1:
                printf("Enter dimensions for matrix %d (m n): ", *num_matrices - matrices_left + 1);
                scanf("%d %d", &m[*num_matrices - matrices_left], &n[*num_matrices - matrices_left]);
                input2DArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left]);
                print2DArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left]);
                (*num_matrices)++;
                matrices_left--;
                break;
            case 2:
                int max, min;
                printf("Enter dimensions for matrix %d (m n): ", *num_matrices - matrices_left + 1);
                scanf("%d %d", &m[*num_matrices - matrices_left], &n[*num_matrices - matrices_left]);
                printf("Enter min and max values: ");
                scanf("%d %d", &min, &max);
                while (min > max) {
                    printf("Enter min and max values (min < max): ");
                    scanf("%d %d", &min, &max);
                }
                initializeArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left], min, max);
                print2DArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left]);
                (*num_matrices)++;
                matrices_left--;
                break;
            case 3:
                int size;
                printf("Enter size of identity matrix: ");
                scanf("%d", &size);
                m[*num_matrices - matrices_left] = n[*num_matrices - matrices_left] = size;
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        if (i != j)
                            arr[*num_matrices - matrices_left][i][j] = 0;
                        else 
                            arr[*num_matrices - matrices_left][i][j] = 1;
                    }
                }
                (*num_matrices)++;
                matrices_left--;
                printf("Identity matrix of size %d generated.\n", size);
                print2DArray(arr[*num_matrices - matrices_left], m[*num_matrices - matrices_left], n[*num_matrices - matrices_left]);
                break;
            case 0:
                if (matrices_left > 0) {
                    printf("Warning: Not all matrices have been input. %d matrices left.\n", matrices_left);
                    printf("Do you want to continue to main menu? (1: Yes, 0: No): ");
                    int confirm;
                    scanf("%d", &confirm);
                    if (confirm == 0) {
                        choice = -1;  // Continue the loop
                    }
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        if (choice != 0) {
            printf("Matrix %d added. Total matrices: %d/%d\n", *num_matrices, *num_matrices, MAX_MATRICES);
        }

    } while (choice != 0);
}

void view_search_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int choice;
    do {
        printf("\n--- View/Search Menu ---\n");
        printf("1. View all matrices\n");
        printf("2. Search and view specific matrix\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                for (int k = 0; k < *num_matrices; k++) {
                    printf("Matrix %d:\n", k + 1);
                    print2DArray(arr[k], m[k], n[k]);
                }
                break;
            case 2:
                if (*num_matrices == 0) {
                    printf("No matrices to print. Please input matrices first.\n");
                } else {
                    int num_search;
                    printf("How many matrices do you want to find? ");
                    scanf("%d", &num_search);
                    for (int i = 0; i < num_search; i++) {
                        int search_index;
                        printf("Index of matrix which is need to be found: ");
                        scanf("%d", &search_index);
                        search_and_print_matrix(*num_matrices, search_index);
                    }
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
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

void analysis_menu(int arr[][100][100], int m[], int n[], int *num_matrices) {
    int choice, index;
    do {
        printf("\n--- Matrix Analysis ---\n");
        printf("1. Check for symmetry\n");
        printf("2. Check for orthogonality\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the index of the matrix to check for symmetry (1-%d): ", *num_matrices);
                scanf("%d", &index);
                while (index < 0 || index >= *num_matrices) {
                    printf("Invalid matrix index.\n");
                    printf("Enter the index of the matrix to check for symmetry (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                }
                if (is_symmetric(arr[index], m[index], n[index])) {
                    printf("Matrix %d is symmetric.\n", index + 1);
                } else {
                    printf("Matrix %d is not symmetric.\n", index + 1);
                }
                break;
            case 2:
                printf("Enter the index of the matrix to check for orthogonality (1-%d): ", *num_matrices);
                scanf("%d", &index);
                while (index < 0 || index >= *num_matrices) {
                    printf("Invalid matrix index.\n");
                    printf("Enter the index of the matrix to check for orthogonality (1-%d): ", *num_matrices);
                    scanf("%d", &index);
                }
                index--;
                if (is_orthogonal(arr[index], m[index], n[index])) {
                    printf("Matrix %d is orthogonal.\n", index + 1);
                } else {
                    printf("Matrix %d is not orthogonal.\n", index + 1);
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
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

void help_menu() {
    int choice;
    do {
        printf("\n--- Help Menu ---\n");
        printf("1. View instructions\n");
        printf("2. About the calculator\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nInstructions:\n");
                printf("1. Start by inputting or generating matrices.\n");
                printf("2. Use the various menus to perform operations on your matrices.\n");
                printf("3. Always enter matrix indices starting from 1.\n");
                printf("4. For operations involving multiple matrices, ensure dimensions are compatible.\n");
                printf("5. Use the View/Search menu to check your matrices at any time.\n");
                break;
            case 2:
                printf("\nAbout the Matrix Calculator:\n");
                printf("This is a comprehensive matrix calculator that allows you to perform\n");
                printf("various operations on matrices, including basic arithmetic, properties\n");
                printf("calculation, transformations, and solving systems of linear equations.\n");
                printf("It's a project with C language, which is used for my porfolio.\n");
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}

void print_main_menu() {
    printf("\n=== Matrix Calculator Menu ===\n");
    printf("1. Matrix Input/Generation\n");
    printf("2. View/Search Matrices\n");
    printf("3. Basic Matrix Operations\n");
    printf("4. Matrix Properties\n");
    printf("5. Matrix Transformations\n");
    printf("6. Elementary Row Operations\n");
    printf("7. Matrix Analysis\n");
    printf("8. Solve The System Of Equations\n");
    printf("9. Load/ Save/ Delete Matrices\n");
    printf("10. Help\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void main_menu() {
    int choice;
    do {
        print_main_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1: input_generation_menu(arr, m, n, &num_matrices); break;
            case 2: view_search_menu(arr, m, n, &num_matrices); break;
            case 3: basic_operations_menu(arr, m, n, &num_matrices); break;
            case 4: properties_menu(arr, m, n, &num_matrices); break;
            case 5: transformations_menu(arr, m, n, &num_matrices); break;
            case 6: row_operations_menu(arr, m, n, &num_matrices); break;
            case 7: analysis_menu(arr, m, n, &num_matrices); break;
            case 8: solve_equations(arr, m, n, &num_matrices); break;
            case 9: load_save_delete(arr, m, n, &num_matrices); break;
            case 10: help_menu(); break;
            case 0: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    main_menu();
    return 0;
}

