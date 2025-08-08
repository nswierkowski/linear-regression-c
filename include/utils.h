#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/*
 * Print a vector of doubles.
 * label: optional prefix text
 * v: pointer to vector
 * n: length of vector
 */
void utils_print_vector(const char *label, const double *v, size_t n);

/*
 * Compute Mean Squared Error (MSE) between predictions and targets.
 * predictions: array of size m
 * targets: array of size m
 * m: number of elements
 */
double utils_mse(const double *predictions, const double *targets, size_t m);

/*
 * Fill an array with zeros.
 */
void utils_zero_vector(double *v, size_t n);

#endif /* UTILS_H */
