#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include "linear_regression.h"
#include "csv_reader.h"

int gradient_descent(
    LinearRegression *lr,
    const CSVData *data,
    double alpha,
    unsigned int iterations
);

#endif  
