#include <stdio.h>
#include <stdlib.h>

double count_determinant(double **matrix, int size);
int input_dimension(int *rows, int *cols);
int input_matrix(double **matrix, int rows, int cols);
double **allocate_matrix(int rows, int cols);
void free_matrix(double **matrix, int rows);
void determinant(double **matrix, int size, double *det, int *degree);
void reduce_matrix(double **matrix, int size, int row, int col, double **new_matrix);

int main(void) {
    int rows, cols;

    if (input_dimension(&rows, &cols)) {
        printf("n/a\n");

        return 0;
    }
    double **matrix = allocate_matrix(rows, cols);
    if (!matrix) {
        printf("n/a\n");

        return 0;
    }
    if (input_matrix(matrix, rows, cols)) {
        printf("n/a\n");
        free_matrix(matrix, rows);
        return 0;
    }
    printf("%.6lf", count_determinant(matrix, rows));

    return 0;
}

double count_determinant(double **matrix, int size) {
    double det = 0;
    int degree = 1;

    if (size == 1)
        return matrix[0][0];
    else if (size == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else
        determinant(matrix, size, &det, &degree);

    return det;
}

void determinant(double **matrix, int size, double *det, int *degree) {
    double **new_matrix = allocate_matrix(size - 1, size - 1);

    for (int j = 0; j < size; j++) {
        reduce_matrix(matrix, size, 0, j, new_matrix);
        *det += (*degree * matrix[0][j] * count_determinant(new_matrix, size - 1));
        *degree = -*degree;
    }

    free_matrix(new_matrix, size - 1);
}

void reduce_matrix(double **matrix, int size, int row, int col, double **new_matrix) {
    int offset_row = 0;
    int offset_col = 0;

    for (int i = 0; i < size - 1; i++) {
        if (i == row) offset_row = 1;

        offset_col = 0;

        for (int j = 0; j < size - 1; j++) {
            if (j == col) offset_col = 1;

            new_matrix[i][j] = matrix[i + offset_row][j + offset_col];
        }
    }
}

double **allocate_matrix(int rows, int cols) {
    double **matrix = malloc(sizeof(double *) * rows);
    if (!matrix) return NULL;

    for (int i = 0; i < rows; ++i) {
        matrix[i] = malloc(sizeof(double) * cols);
        if (!matrix[i]) {
            free_matrix(matrix, rows);

            return NULL;
        }
    }

    return matrix;
}

void free_matrix(double **matrix, int rows) {
    for (int i = 0; i < rows; ++i) free(matrix[i]);

    free(matrix);
}

int input_matrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (scanf("%lf", &matrix[i][j]) != 1) return 1;

    return 0;
}

int input_dimension(int *rows, int *cols) {
    if (scanf("%d%d", rows, cols) != 2 || *rows <= 0 || *cols <= 0) return 1;

    return 0;
}
