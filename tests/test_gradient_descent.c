#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../include/linear_regression.h"
#include "../include/gradient_descent.h"
#include "../include/csv_reader.h"

#define TOLERANCE 1e-3

static CSVData* generate_test_data(size_t m) {
    CSVData *data = malloc(sizeof(CSVData));
    if (!data) return NULL;

    data->rows = m;
    data->cols = 2; 
    data->data = malloc(m * sizeof(double*));
    if (!data->data) {
        free(data);
        return NULL;
    }

    for (size_t i = 0; i < m; i++) {
        data->data[i] = malloc(2 * sizeof(double));
        if (!data->data[i]) {
            for (size_t k = 0; k < i; k++) free(data->data[k]);
            free(data->data);
            free(data);
            return NULL;
        }
        double x = (double)i;     
        double y = 2.0 + 3.0 * x;  
        data->data[i][0] = x;
        data->data[i][1] = y;
    }
    return data;
}

int main(void) {
    size_t m = 20;
    CSVData *data = generate_test_data(m);
    if (!data) {
        fprintf(stderr, "Failed to generate test data\n");
        return 1;
    }

    LinearRegression *lr = lr_create(2);
    if (!lr) {
        csv_free(data);
        return 1;
    }

    int r = gradient_descent(lr, data, 0.01, 3000);
    if (r != 0) {
        fprintf(stderr, "Gradient descent failed\n");
        lr_free(lr);
        csv_free(data);
        return 1;
    }

    printf("Learned parameters:\n");
    printf("theta[0] (bias)   = %.6f\n", lr->theta[0]);
    printf("theta[1] (weight) = %.6f\n", lr->theta[1]);

    if (fabs(lr->theta[0] - 2.0) > TOLERANCE ||
        fabs(lr->theta[1] - 3.0) > TOLERANCE) {
        fprintf(stderr, "Test FAILED: learned parameters deviate too much\n");
        lr_free(lr);
        csv_free(data);
        return 1;
    }

    printf("Test PASSED: parameters match expected values within tolerance %.e\n", TOLERANCE);

    lr_free(lr);
    csv_free(data);
    return 0;
}
