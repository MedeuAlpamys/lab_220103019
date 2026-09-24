#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>

#define STUDENT_ID 220103019ULL
#define N (10000000ULL + ((STUDENT_ID % 10000ULL) * 1000ULL))

static inline uint32_t collatz_steps(uint64_t n) {
    uint32_t steps = 0;
    while (n > 1) {
        if ((n & 1) == 0) n >>= 1;
        else n = 3 * n + 1;
        steps++;
    }
    return steps;
}

int main() {
    printf("Student ID: %llu | Workload N: %llu\n", STUDENT_ID, N);
    int threads_eval[] = {1, 2, 4, 8, 16};
    for (int idx = 0; idx < 5; idx++) {
        int k = threads_eval[idx];
        omp_set_num_threads(k);
        double start = omp_get_wtime();
        uint32_t max_steps = 0;
        #pragma omp parallel for reduction(max:max_steps)
        for (uint64_t i = 1; i <= N; i++) {
            uint32_t s = collatz_steps(i);
            if (s > max_steps) max_steps = s;
        }
        printf("Threads k=%2d | Time: %.6f s\n", k, omp_get_wtime() - start);
    }
    return 0;
}
