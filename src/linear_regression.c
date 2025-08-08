#include "../include/linear_regression.h"
#include <stdlib.h>
#include <stdio.h>

LinearRegression* lr_create(size_t n_features) {
    if (n_features == 0) {
        fprintf(stderr, "lr_create: n_features must be > 0\n");
        return NULL;
    }

    LinearRegression *lr = malloc(sizeof(LinearRegression));
    if (!lr) {
        fprintf(stderr, "lr_create: memory allocation failed\n");
        return NULL;
    }

    lr->theta = calloc(n_features, sizeof(double));
    if (!lr->theta) {
        fprintf(stderr, "lr_create: memory allocation failed\n");
        free(lr);
        return NULL;
    }

    lr->n_features = n_features;
    return lr;
}

double lr_predict(const LinearRegression *lr, const double *features) {
    if (!lr || !lr->theta || !features) {
        fprintf(stderr, "lr_predict: invalid parameters\n");
        return 0.0;
    }

    double result = lr->theta[0];

    for (size_t j = 0; j < lr->n_features - 1; ++j) {
        result += lr->theta[j + 1] * features[j];
    }

    return result;
}

void lr_free(LinearRegression *lr) {
    if (!lr) return;
    free(lr->theta);
    free(lr);
}
