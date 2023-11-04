#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_READ_DATA 101
#define ERROR_INPUT_SIZE 102
#define ERROR_ALL_MEMORY 103
// void invert(double **matrix, int n, int m);
// void input(double **matrix, int *n, int *m);
// void output(double **matrix, int n, int m);

int input_size(int *n, int *m);
double **allocate_matrix(int n, int m);
int read_matrix(double **matrix, int rows, int columns);
void print_matrix(double **matrix, int rows, int columns);
void free_matrix(double **data, int n);
// double det(double **matrix, int n, int m);gcc -W
double count_determinant(double **matrix, int size);
void determinant_big_size(double **matrix, int size, double *det, int *degree);
void get_matrix_without_row_and_col(double **matrix, int size, int row, int col, double **new_matrix);
void cofactor(double **num, int f);
void transpose(double **num, double **fac, int r);

int main() {
    double **matrix = NULL;
    int rc = EXIT_SUCCESS;
    int n, m;
    rc = input_size(&n, &m);
    if (!rc) {
        matrix = allocate_matrix(n, m);
        if (matrix == NULL) rc = ERROR_ALL_MEMORY;
    }
    if (!rc) rc = read_matrix(matrix, n, m);
    if (!rc && count_determinant(matrix, n) != 0)
        cofactor(matrix, n);
    else
        printf("n/a");

    return rc;
}

void cofactor(double **num, int f) {
    double **b = NULL, **fac = NULL;
    b = allocate_matrix(f, f);
    fac = allocate_matrix(f, f);
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++) {
        for (p = 0; p < f; p++) {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++) {
                for (j = 0; j < f; j++) {
                    if (i != q && j != p) {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * count_determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);
}

void transpose(double **num, double **fac, int r) {
    int i, j;
    double **b, **inverse, d;
    b = allocate_matrix(r, r);
    inverse = allocate_matrix(r, r);

    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            b[i][j] = fac[j][i];
        }
    }
    d = count_determinant(num, r);
    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            inverse[i][j] = b[i][j] / d;
        }
    }

    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            printf("%lf", inverse[i][j]);
            if (j + 1 != r) printf(" ");
        }
        if (i + 1 != r) printf("\n");
    }
}

int input_size(int *n, int *m) {
    int rc = EXIT_SUCCESS;
    if (!scanf("%d %d", n, m)) rc = ERROR_INPUT_SIZE;
    if (*n <= 0 || *m <= 0 || *n != *m) rc = ERROR_INPUT_SIZE + 1;
    return rc;
}

double **allocate_matrix(int n, int m) {
    double **matrix = malloc(n * sizeof(double *));

    if (matrix == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(m * sizeof(double));

        if (matrix[i] == NULL) {
            free_matrix(matrix, n);
            return NULL;
        }
    }

    return matrix;
}

int read_matrix(double **matrix, int rows, int columns) {
    int flag = EXIT_SUCCESS;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (!flag && !scanf("%lf", &matrix[i][j])) flag = ERROR_READ_DATA;
    return flag;
}

void print_matrix(double **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) printf("%lf ", matrix[i][j]);
        printf("\n");
    }
}

void free_matrix(double **data, int n) {
    for (int i = 0; i < n; i++) free(data[i]);

    free(data);
}

double count_determinant(double **matrix, int size) {
    double det = 0;
    int degree = 1;

    if (size == 1)
        return matrix[0][0];
    else if (size == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else
        determinant_big_size(matrix, size, &det, &degree);

    return det;
}

void determinant_big_size(double **matrix, int size, double *det, int *degree) {
    double **new_matrix = allocate_matrix(size - 1, size - 1);

    for (int j = 0; j < size; j++) {
        get_matrix_without_row_and_col(matrix, size, 0, j, new_matrix);
        *det += (*degree * matrix[0][j] * count_determinant(new_matrix, size - 1));
        *degree = -*degree;
    }

    free_matrix(new_matrix, size - 1);
}

void get_matrix_without_row_and_col(double **matrix, int size, int row, int col, double **new_matrix) {
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
