#include <stdio.h>
#include <stdlib.h>
#include "../include/csv_reader.h"

static void print_csv_data(const CSVData *csv) {
    printf("Rows: %zu, Cols: %zu\n", csv->rows, csv->cols);
    for (size_t i = 0; i < csv->rows; i++) {
        printf("Row %zu:", i);
        for (size_t j = 0; j < csv->cols; j++) {
            printf(" %g", csv->data[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    const char *test_file = "data/sample.csv";

    CSVData *csv = csv_read(test_file);
    if (!csv) {
        fprintf(stderr, "Failed to read %s\n", test_file);
        return EXIT_FAILURE;
    }

    print_csv_data(csv);

    csv_free(csv);
    return EXIT_SUCCESS;
}