#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include "linear_regression.h"
#include "csv_reader.h"

/*
 * Train a LinearRegression model using batch gradient descent.
 *
 * Parameters:
 *   lr         - pointer to initialized LinearRegression (theta set to 0 or prior values)
 *   data       - CSVData, last column is y, others are features (x1..xn)
 *   alpha      - learning rate (must be > 0)
 *   iterations - number of gradient descent steps (> 0)
 *
 * Returns:
 *   0 on success
 *  -1 if invalid parameters
 *
 * Note:
 *   - Adds a bias term automatically (x0 = 1).
 *   - Updates lr->theta in-place.
 */
int gradient_descent(
    LinearRegression *lr,
    const CSVData *data,
    double alpha,
    unsigned int iterations
);

#endif /* GRADIENT_DESCENT_H */
