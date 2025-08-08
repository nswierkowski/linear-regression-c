#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <stddef.h>

/*
 * LinearRegression:
 *  - theta: parameter vector (length = n_features)
 *  - n_features: number of model parameters, including bias term
 *
 * Note:
 *  For dataset with F input features, n_features = F + 1 (bias + weights)
 */
typedef struct {
    double *theta;
    size_t n_features;
} LinearRegression;

/*
 * Allocate and initialize a new LinearRegression model.
 *
 * Params:
 *   n_features: number of parameters (must be > 0)
 * Returns:
 *   Pointer to model on success, NULL on failure.
 *
 * All theta values are initialized to 0.0.
 */
LinearRegression* lr_create(size_t n_features);

/*
 * Predict output for a single feature vector.
 *
 * Params:
 *   lr: model
 *   features: array of F doubles (excluding bias term)
 * Returns:
 *   Predicted value.
 *
 * Note: This automatically adds x0 = 1 for bias in prediction.
 */
double lr_predict(const LinearRegression *lr, const double *features);

/*
 * Free a LinearRegression object created by lr_create().
 */
void lr_free(LinearRegression *lr);

#endif /* LINEAR_REGRESSION_H */
