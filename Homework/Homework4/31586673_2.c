#include <stdio.h>
#define MAX 100

void radix_sort(unsigned int A[], unsigned int n, unsigned int k) {
    unsigned int buckets[16][MAX];
    unsigned int counts[16];
    unsigned int mask = 0xF;
    unsigned int shift = 0;

    for (int d = 0; d < k/4; d++) {
        for (int i = 0; i < 16; i++) {
            counts[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            unsigned int digit = (A[i] >> shift) & mask;
            buckets[digit][counts[digit]++] = A[i];
        }

        int index = 0;
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < counts[i]; j++) {
                A[index++] = buckets[i][j];
            }
        }
        shift += 4;
    }
}

void radix_sort_signed(int A[], int n, int k) {
    int positive[MAX], negative[MAX];
    int posCount = 0, negCount = 0;

    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            positive[posCount++] = A[i];
        }
        else {
            negative[negCount++] = ~A[i];
        }
    }

    radix_sort((unsigned int*)positive, posCount, k);
    radix_sort((unsigned int*)negative, negCount, k);

    for (int i = negCount - 1; i >= 0; i--) {
        A[negCount - i - 1] = ~negative[i];
    }
    for (int i = 0; i < posCount; i++) {
        A[negCount + i] = positive[i];
    }
}

int main() {
    int n;
    int numbers[MAX];

    printf("Enter the number of integers (max 100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid input. Please enter a number between 1 and 100.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            printf("Invalid input. Please enter integers only.\n");
            return 1;
        }
    }

    radix_sort_signed(numbers, n, 32);

    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", numbers[i]);
    }
    return 0;
}
