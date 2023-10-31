#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int search(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1) {
        printf("n/a");
        return 1;
    }
    printf("%d", search(data, n));
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

int search(int *a, int n) {
    int result = 0;
    double mean_result = mean(a, n);
    double sigma = 3 * pow(variance(a, n), 0.5);
    for (int *p = a; p - a < n; p++) {
        if (*p != 0 && *p % 2 == 0) {
            if (*p >= mean_result) {
                if (*p >= mean_result - sigma && *p <= mean_result + sigma) {
                    result = *p;
                }
            }
        }
    }
    return result;
}