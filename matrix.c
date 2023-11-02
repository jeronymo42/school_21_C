#include <stdio.h>
#include <stdlib.h>
#define LEN 100

int input(int** matrix, int heigth, int width);
int input_static(int matrix[][LEN]);
void output(int** matrix, int heigth, int width);
void output_static(int matrix[][LEN]);
int** dynamic_array_alloc(int method, int heigth, int width);
void dynamic_array_free(int** matrix, int method, int matrix_height, int matrix_width);

int main() {
    int matrix_height, matrix_width, len_of_array, method;
    int** matrix;
    int static_matrix[LEN][LEN];
    int flag_correct = 0;
    if (scanf("%d", &method) != 1 || method < 1 || method > 4) {
        flag_correct = 1;
    } else if (method > 1) {
        if (scanf("%d", &matrix_height) != 1 || scanf("%d", &matrix_width) != 1) {
            flag_correct = 1;
        } else {
            matrix = dynamic_array_alloc(method, matrix_height, matrix_width);
            if (input(matrix, matrix_height, matrix_width)) {
                flag_correct = 1;
            } else {
                output(matrix, matrix_height, matrix_width);
                dynamic_array_free(matrix, method, matrix_height, matrix_width);
            }
        }
    }
    else {
        if (input_static(static_matrix)) {
            flag_correct = 1;
        } else {
                output_static(static_matrix);
            }

    }
    if (flag_correct) {
        printf("n/a");
        return 1;
    }
    return flag_correct;
}

int input(int** matrix, int heigth, int width) {
    int flag = 0;
    for (int i = 0; i < heigth; i++) {
        if (flag != 1) {
            for (int j = 0; j < width; j++) {
                if (scanf("%d", matrix[i][j]) != 1) {
                    flag = 1;
                    break;
                }
            }
        }
    }
    return flag;
}

int input_static(int matrix[][LEN]) {
    int flag = 0;
    for (int i = 0; i < LEN; i++) {
        if (flag != 1) {
            for (int j = 0; j < LEN; j++) {
                if (scanf("%d", &matrix[i][j]) != 1) {
                    flag = 1;
                    break;
                }
            }
        }
    }
    return flag;
}

void output(int** matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == LEN - 1) {
                printf("%d", matrix[i][j]);
            } else {
            printf("%d ", matrix[i][j]);
            }
        }
        if (i + 1 != height) {
            printf("\n");
        }
    }
}

void output_static(int matrix[][LEN]) {
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            if (j == LEN - 1) {
                printf("%d", matrix[i][j]);
            } else {
            printf("%d ", matrix[i][j]);
            }
        }
        if (i + 1 != LEN) {
            printf("\n");
        }
    }
}

int** dynamic_array_alloc(int method, int matrix_height, int matrix_width) {
    int** array;
    if (method == 2) {
        array = malloc(sizeof(int*) * matrix_height);
        for (int i = 0; i < matrix_height; i++) {
            array[i] = (int*) malloc(sizeof(int) * matrix_width);
        }
    } else if (method == 3) {
        array = malloc(sizeof(int*) * matrix_height);
        int* row = malloc(sizeof(int) * matrix_height * matrix_width);
        for (int i = 0; i < matrix_height; i++) {
            array[i] =  row + matrix_width * i;
        }
    } else if (method == 4) {
        array = malloc(sizeof(int*) * matrix_height + sizeof(int) * matrix_height * matrix_width);
        int* row = (int*) (array + matrix_height);
        for (int i = 0; i < matrix_height; i++) {
            array[i] =  row + matrix_width * i;
        }
    }
    return array;
}

void dynamic_array_free(int** matrix, int method, int matrix_height, int matrix_width) {
    if (method == 2 || method == 3) {
        for (int i = 0; i < matrix_height; i++) {
            free(matrix[i]);
        }
        free(matrix);
    } else {
        free(matrix);
    }
}