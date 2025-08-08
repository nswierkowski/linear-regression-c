#include "../include/gradient_descent.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int gradient_descent(
    LinearRegression *lr,
    const CSVData *data,
    double alpha,
    unsigned int iterations
) {
    if (!lr || !data || data->rows == 0 || data->cols < 2 || alpha <= 0.0 || iterations == 0) {
        fprintf(stderr, "gradient_descent: invalid parameters\n");
        return -1;
    }

    /* In CSVData:
       - First (cols-1) columns are features
       - Last column is target y
       LinearRegression stores n_features = features + bias term
    */

    size_t m = data->rows;                
    size_t n_features = data->cols - 1;   
    if ((size_t)lr->n_features != (n_features + 1)) { /* +1 for bias term */
        fprintf(stderr, "gradient_descent: model feature count mismatch\n");
        return -1;
    }

    double *gradients = calloc(lr->n_features, sizeof(double));
    if (!gradients) {
        fprintf(stderr, "gradient_descent: memory allocation failed\n");
        return -1;
    }

    for (unsigned int iter = 0; iter < iterations; ++iter) {
        for (size_t j = 0; j < lr->n_features; ++j) {
            gradients[j] = 0.0;
        }

        for (size_t i = 0; i < m; ++i) {
            double prediction = lr->theta[0];
            for (size_t j = 0; j < n_features; ++j) {
                prediction += lr->theta[j + 1] * data->data[i][j];
            }
            double error = prediction - data->data[i][n_features]; 
            
            gradients[0] += error; 
            for (size_t j = 0; j < n_features; ++j) {
                gradients[j + 1] += error * data->data[i][j];
            }
        }

        for (size_t j = 0; j < lr->n_features; ++j) {
            lr->theta[j] -= (alpha / (double)m) * gradients[j];
        }
    }

    free(gradients);
    return 0;
}
