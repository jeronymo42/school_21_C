#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);
void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1) {
        printf("n/a");
        return 1;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
    return 0;
}

int input(int *a, int *n) {
    char c;
    if (scanf("%d", n) != 1 || *n < 0 || *n > NMAX) {
        return 1;
    }

    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) {
            return 1;
        }
    }

    if (scanf("%c", &c) != 1 && (c != '\n' || c != ' ')) {
        return 1;
    }
    return 0;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

int max(int *a, int n) {
    int result = a[0];
    for (int *p = a; p - a < n; p++) {
        if (*p > result) {
            result = *p;
        }
    }
    return result;
}

int min(int *a, int n) {
    int result = a[0];
    for (int *p = a; p - a < n; p++) {
        if (*p < result) {
            result = *p;
        }
    }
    return result;
}

double mean(int *a, int n) {
    double q = 0;
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        q += 1.0;
        sum += (double)*p;
    }
    return sum / q;
}

double variance(int *a, int n) {
    double mean_result = mean(a, n);
    double sum_squares = 0;
    for (int *p = a; p - a < n; p++) {
        sum_squares += ((double)*p - mean_result) * ((double)*p - mean_result);
    }
    return sum_squares / (double)n;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}