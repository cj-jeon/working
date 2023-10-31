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

// gcc -mavx -o avx_sample avx_sample.c
// ./avx_sample 100000000



$ cat gather_avx2_example.c
//gcc -mavx2 gather_avx2_example.c -o gather_avx2_example

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define SIZE 1000000

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <loop_count>\n", argv[0]);
        return 1;
    }

    int loop_count = atoi(argv[1]);

    float *data = (float *)aligned_alloc(32, SIZE * sizeof(float));
    float *gathered_data = (float *)aligned_alloc(32, SIZE * sizeof(float));
    float sum = 0.0f;

    // Initialize data array
    for (int i = 0; i < SIZE; i++) {
        data[i] = (float)(rand() % 100);
    }

    clock_t start = clock();

    for (int loop = 0; loop < loop_count; loop++) {
        // Gather data using AVX2
        for (int i = 0; i < SIZE; i += 8) {
            __m256i indices = _mm256_set_epi32(i, i + 1, i + 2, i + 3, i + 4, i + 5, i + 6, i + 7);
            __m256 gathered = _mm256_i32gather_ps(data, indices, 4);
            _mm256_store_ps(gathered_data + i, gathered);
        }

        // Calculate sum
        sum = 0.0f;
        for (int i = 0; i < SIZE; i++) {
            sum += gathered_data[i];
        }
    }

    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sum: %.2f\n", sum);
    printf("Elapsed time: %.2f seconds\n", elapsed_time);

    free(data);
    free(gathered_data);

    return 0;
}
