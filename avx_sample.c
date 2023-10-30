#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

void avx_add(float *a, float *b, float *result, int loop_count) {
    for (int i = 0; i < loop_count; i++) {
        __m256 avx_a = _mm256_loadu_ps(a);
        __m256 avx_b = _mm256_loadu_ps(b);
        __m256 avx_result = _mm256_add_ps(avx_a, avx_b);
        _mm256_storeu_ps(result, avx_result);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <loop_count>\n", argv[0]);
        return 1;
    }

    int loop_count = atoi(argv[1]);

    float a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float b[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    float result[8] = {0};

    clock_t start = clock();
    avx_add(a, b, result, loop_count);
    clock_t end = clock();

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Result:\n");
    for (int i = 0; i < 8; i++) {
        printf("%f ", result[i]);
    }
    printf("\n");

    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}


# gcc -mavx -o avx_sample avx_sample.c
# ./avx_sample 100000000
