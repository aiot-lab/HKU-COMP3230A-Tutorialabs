// file: c_matrix.c
#include <stdio.h>
#include <stdlib.h>

typedef int **matrix_t;

void print_matrix(matrix_t matrix, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// pass in the matrix by giving the address of the pointer to the rows
void empty_matrix(matrix_t matrix, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    int n_col = 10, n_row = 10, i, j;
    // malloc the rows
    matrix_t matrix = (matrix_t)malloc(sizeof(int *) * n_row);
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
    print_matrix(matrix, n_row, n_col);
    empty_matrix(matrix, n_row, n_col);
    print_matrix(matrix, n_row, n_col);

    // free the columns
    for (i = 0; i < n_row; i++) {
        free(matrix[i]);
    }
    // free the rows
    free(matrix);
    
    return 0;
}