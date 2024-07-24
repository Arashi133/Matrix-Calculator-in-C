#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "menu.h"

#define MAX_DIM 100
#define MAX_MATRICES 100
int num_matrices = 0;
int m[MAX_DIM], n[MAX_DIM];
int arr[MAX_MATRICES][100][100];
int max, min;
int indices[100];
int result_counts = 0;
int result[MAX_MATRICES][100][100];

int main() {
    time_t t;
    srand((unsigned)time(&t));
    main_menu();
    return 0;
}