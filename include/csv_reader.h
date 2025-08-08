#ifndef CSV_READER_H
#define CSV_READER_H

#include <stddef.h>

/*
 * Format expectation for this project:
 *   - Each row should contain numeric fields only.
 *   - The last column is expected to be the target (y); earlier columns are features (x1..xn).
 *   - If the file has a header (non-numeric first non-empty line), it will be auto-skipped.
 */
typedef struct {
    double **data;
    size_t rows;
    size_t cols;
} CSVData;

CSVData* csv_read(const char *filename);

void csv_free(CSVData *csv);

#endif 
