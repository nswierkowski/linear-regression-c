#include <stdio.h>
#include <stdlib.h>
#include "csv_reader.h"
#include "linear_regression.h"
#include "gradient_descent.h"
#include "utils.h"

#define LEARNING_RATE 0.01
#define ITERATIONS 1000

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <csv_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *csv_file = argv[1];

    /* 1. Load CSV data */
    CSVData *data = csv_read(csv_file);
    if (!data) {
        fprintf(stderr, "Error: Failed to read CSV file '%s'\n", csv_file);
        return EXIT_FAILURE;
    }

    if (data->cols < 2) {
        fprintf(stderr, "Error: CSV must have at least one feature and one target column\n");
        csv_free(data);
        return EXIT_FAILURE;
    }

    size_t n_features = data->cols; /* includes bias term in model */

    /* 2. Create Linear Regression model */
    LinearRegression *lr = lr_create(n_features);
    if (!lr) {
        fprintf(stderr, "Error: Failed to allocate LinearRegression model\n");
        csv_free(data);
        return EXIT_FAILURE;
    }

    /* 3. Train model with Gradient Descent */
    if (gradient_descent(lr, data, LEARNING_RATE, ITERATIONS) != 0) {
        fprintf(stderr, "Error: Gradient descent failed\n");
        lr_free(lr);
        csv_free(data);
        return EXIT_FAILURE;
    }

    /* 4. Print final parameters */
    utils_print_vector("Final parameters: ", lr->theta, n_features);

    /* 5. Compute and print training error */
    double *predictions = malloc(data->rows * sizeof(double));
    if (!predictions) {
        fprintf(stderr, "Error: Memory allocation failed for predictions\n");
        lr_free(lr);
        csv_free(data);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < data->rows; i++) {
        predictions[i] = lr_predict(lr, data->data[i]);
    }

    double *targets = malloc(data->rows * sizeof(double));
    if (!targets) {
        fprintf(stderr, "Error: Memory allocation failed for targets\n");
        free(predictions);
        lr_free(lr);
        csv_free(data);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < data->rows; i++) {
        targets[i] = data->data[i][data->cols - 1]; /* last column = target */
    }

    double mse = utils_mse(predictions, targets, data->rows);
    printf("Training MSE: %.6f\n", mse);

    /* 6. Cleanup */
    free(predictions);
    free(targets);
    lr_free(lr);
    csv_free(data);

    return EXIT_SUCCESS;
}
