#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void utils_print_vector(const char *label, const double *v, size_t n);

double utils_mse(const double *predictions, const double *targets, size_t m);

void utils_zero_vector(double *v, size_t n);

#endif 
