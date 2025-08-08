#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <stddef.h>

typedef struct {
    double *theta;
    size_t n_features;
} LinearRegression;

LinearRegression* lr_create(size_t n_features);

double lr_predict(const LinearRegression *lr, const double *features);

void lr_free(LinearRegression *lr);

#endif 
