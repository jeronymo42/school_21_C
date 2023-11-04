#include <stdio.h>
#define NMAX 10

int end;

int input(int *a);
void output(int *a, int k);
void quick_sort(int *a, int first, int last);
void swap(int *a, int *b);
void copy(int *a, int *b);
int LEFT(int i);
int RIGHT(int i);
void heapify(int *a, int i);
void BuildHeap(int *a);
void heapsort(int *a, int n);

int main() {
    int data[NMAX];
    int data2[NMAX];
    int first = 0;
    int last = 9;
    int k;
    int n = 10;

    k = input(data);
    copy(data2, data);
    heapsort(data, n);
    quick_sort(data2, first, last);
    output(data, k);
    output(data2, k);
    return 0;
}

int input(int *a) {
    int k = 0;
    for (int i = 0; i < 10; i++) {
        if (scanf("%d", &a[i]) != 1) {
            k = -1;
            break;
        }
    }
    return k;
}

void output(int *a, int k) {
    if (k != -1) {
        for (int i = 0; i < 10; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    } else
        printf("n/a");
}

void quick_sort(int *a, int first, int last) {
    if (first < last) {
        int left = first, right = last, middle = a[(left + right) / 2];
        do {
            while (a[left] < middle) left++;
            while (a[right] > middle) right--;
            if (left <= right) {
                swap(&a[left], &a[right]);
                left++;
                right--;
            }
        } while (left <= right);
        quick_sort(a, first, right);
        quick_sort(a, left, last);
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void copy(int *a, int *b) {
    for (int i = 0; i < 10; i++) {
        a[i] = b[i];
    }
}

int LEFT(int i) { return (2 * i + 1); }

int RIGHT(int i) { return (2 * i + 2); }

void heapify(int *a, int i) {
    int left = LEFT(i);
    int right = RIGHT(i);
    int largest = i;

    if (left < end && a[left] > a[i]) largest = left;
    if (right < end && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, largest);
    }
}

void BuildHeap(int *a) {
    int i = (end - 2) / 2;
    while (i >= 0) {
        heapify(a, i--);
    }
}

void heapsort(int *a, int n) {
    end = n;
    BuildHeap(a);
    while (end != 1) {
        swap(&a[0], &a[end - 1]);
        end--;
        heapify(a, 0);
    }
}