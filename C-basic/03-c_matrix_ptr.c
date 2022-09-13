// file: c_matrix.c
#include <stdio.h>
#include <stdlib.h>
void print_matrix(int **matrix, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int n_col = 5, n_row = 10, i, j;
    int **matrix;
    // malloc the rows
    matrix = (int **)malloc(n_row * sizeof(int *));
    // malloc the columns
    for (i = 0; i < n_row; i++) {
        matrix[i] = (int *)malloc(n_col * sizeof(int));
    }
    // initialize the matrix (col * row)
    for (i = 0; i < n_row; i++) {
        for (j = 0; j < n_col; j++) {
            matrix[i][j] = i * j;
        }
    }
    // print the matrix
    print_matrix(matrix, n_row, n_col);
    
    // free the columns
    for (i = 0; i < n_row; i++) {
        free(matrix[i]);
    }
    // free the rows
    free(matrix);
    return 0;
}