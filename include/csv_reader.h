#ifndef CSV_READER_H
#define CSV_READER_H

#include <stddef.h>

/*
 * CSVData
 *   - data: pointer to array of rows; each row is a double array of length `cols`.
 *   - rows: number of data rows
 *   - cols: number of columns per row
 *
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

/* Read CSV file at `filename` and return a CSVData* on success, NULL on failure.
 * The caller must free the returned object using csv_free().
 *
 * On failure, a message will be printed to stderr. Parsing is strict: missing
 * or non-numeric tokens in data rows cause failure.
 */
CSVData* csv_read(const char *filename);

/* Free CSVData returned by csv_read */
void csv_free(CSVData *csv);

#endif /* CSV_READER_H */
