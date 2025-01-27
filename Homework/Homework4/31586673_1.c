#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void radix_sort(unsigned long long A[], unsigned int n, unsigned int k) {
    unsigned long long buck1[MAX], buck2[MAX];
    unsigned long long mask;
    unsigned int counter1, counter2;

    for (int d = 0; d < k; d++) {
        mask = 1ULL << d;
        counter1 = counter2 = 0;
        for (int i = 0; i < n; i++) {
            if ((A[i] & mask) == 0) {
                buck1[counter1++] = A[i];
            }
	    else {
                buck2[counter2++] = A[i];
            }
        }
        for (int i = 0; i < counter1; i++) {
            A[i] = buck1[i];
        }
        for (int i = 0; i < counter2; i++) {
            A[counter1 + i] = buck2[i];
        }
    }
}

void radix_sort_signed(long long A[], int n, int k) {
    long long positive[MAX], negative[MAX];
    int posCount = 0, negCount = 0;

    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            positive[posCount++] = A[i];
        }
	else {
            negative[negCount++] = ~A[i];
        }
    }

    radix_sort((unsigned long long*)positive, posCount, k);
    radix_sort((unsigned long long*)negative, negCount, k);

    for (int i = negCount - 1; i >= 0; i--) {
        A[negCount - i - 1] = ~negative[i];
    }
    for (int i = 0; i < posCount; i++) {
        A[negCount + i] = positive[i];
    }
}

int main() {
    int n;
    float numbers[MAX];
    long long int int_numbers[MAX];

    printf("Enter the number of floats (max 100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid input. Please enter a number between 1 and 100.\n");
        return 1;
    }

    while (getchar() != '\n');

    printf("Enter %d float numbers separated by spaces:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%f", &numbers[i]) != 1) {
            printf("Invalid number entered. Program terminating.\n");
            return 1;
        }

        int_numbers[i] = (long long)(numbers[i] * 1000000);
    }

    radix_sort_signed(int_numbers, n, sizeof(long long) * 8);

    for (int i = 0; i < n; i++) {
        numbers[i] = int_numbers[i] / 1000000.0;
    }

    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%.6f\n", numbers[i]);
    }
    return 0;
}
