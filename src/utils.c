#include "../include/utils.h"
#include <stdio.h>
#include <math.h>

void utils_print_vector(const char *label, const double *v, size_t n) {
    if (label) printf("%s", label);
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%.6f", v[i]);
        if (i + 1 < n) printf(", ");
    }
    printf("]\n");
}

double utils_mse(const double *predictions, const double *targets, size_t m) {
    if (!predictions || !targets || m == 0) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < m; i++) {
        double diff = predictions[i] - targets[i];
        sum += diff * diff;
    }
    return sum / (double)m;
}

void utils_zero_vector(double *v, size_t n) {
    if (!v) return;
    for (size_t i = 0; i < n; i++) {
        v[i] = 0.0;
    }
}
