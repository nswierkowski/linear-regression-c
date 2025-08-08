#define _POSIX_C_SOURCE 200809L 

#include "../include/csv_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

static char *read_line(FILE *f) {
    if (!f) return NULL;
    size_t cap = 256;
    size_t len = 0;
    char *buf = malloc(cap);
    if (!buf) return NULL;

    int c;
    while ((c = fgetc(f)) != EOF) {
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) { free(buf); return NULL; }
            buf = tmp;
        }
        buf[len++] = (char)c;
        if (c == '\n') break;
    }

    if (len == 0) { free(buf); return NULL; } 
    buf[len] = '\0';
    return buf;
}

static char *trim_inplace(char *s) {
    if (!s) return s;

    while (*s && isspace((unsigned char)*s)) s++;

    if (*s == '\0') return s;

    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) { *end = '\0'; end--; }
    return s;
}

static char *extract_next_token(const char **sp) {
    const char *p = *sp;

    while (*p && *p != '\n' && isspace((unsigned char)*p)) p++;
    if (*p == '\0' || *p == '\n' || *p == '\r') { *sp = p; return NULL; }

    size_t cap = 64, len = 0;
    char *buf = malloc(cap);
    if (!buf) return NULL;

    if (*p == '"') {
        p++;
        while (*p && *p != '"') {
            if (len + 1 >= cap) {
                cap *= 2;
                char *t = realloc(buf, cap);
                if (!t) { free(buf); return NULL; }
                buf = t;
            }
            if (*p == '\\' && *(p + 1) != '\0') {
                p++;
                buf[len++] = *p++;
            } else {
                buf[len++] = *p++;
            }
        }
        if (*p == '"') p++; 
        while (*p && *p != ',' && *p != '\n' && isspace((unsigned char)*p)) p++;
        if (*p == ',') p++;
    } else {
        while (*p && *p != ',' && *p != '\n' && *p != '\r') {
            if (len + 1 >= cap) {
                cap *= 2;
                char *t = realloc(buf, cap);
                if (!t) { free(buf); return NULL; }
                buf = t;
            }
            buf[len++] = *p++;
        }
        if (*p == ',') p++;
        while (len > 0 && isspace((unsigned char)buf[len - 1])) len--;
    }

    buf[len] = '\0';

    char *trimmed = trim_inplace(buf);

    if (trimmed != buf) {
        size_t newlen = strlen(trimmed);
        memmove(buf, trimmed, newlen + 1);
    }

    *sp = p;
    return buf;
}

static int is_line_numeric(const char *line, size_t *out_n_tokens) {
    const char *p = line;
    size_t count = 0;

    while (1) {
        char *tok = extract_next_token(&p);
        if (!tok) break;
        if (tok[0] == '\0') { free(tok); return 0; } 
        char *endptr = NULL;
        errno = 0;
        strtod(tok, &endptr);
        if (endptr == tok) { free(tok); return 0; } 
        free(tok);
        count++;
    }

    if (out_n_tokens) *out_n_tokens = count;
    return 1;
}

/* Parse line into an array of doubles. On success returns 0 and sets *out_values
 * (malloc'd array) and *out_count. Caller must free *out_values.
 *
 * Returns:
 *   0   success
 *  -1   memory allocation failure
 *  -2   empty token found (malformed)
 *  -3   non-numeric token found
 */
static int parse_line_to_doubles(const char *line, double **out_values, size_t *out_count) {
    const char *p = line;
    size_t cap = 8;
    size_t n = 0;
    double *vals = malloc(cap * sizeof(double));
    if (!vals) return -1;

    while (1) {
        char *tok = extract_next_token(&p);
        if (!tok) break;
        if (tok[0] == '\0') { free(tok); free(vals); return -2; }

        errno = 0;
        char *endptr = NULL;
        double v = strtod(tok, &endptr);
        if (endptr == tok) { free(tok); free(vals); return -3; }

        if (n >= cap) {
            cap *= 2;
            double *tmp = realloc(vals, cap * sizeof(double));
            if (!tmp) { free(tok); free(vals); return -1; }
            vals = tmp;
        }
        vals[n++] = v;
        free(tok);
    }

    if (n == 0) {
        free(vals);
        *out_values = NULL;
        *out_count = 0;
        return 0;
    }

    double *shr = realloc(vals, n * sizeof(double));
    if (shr) vals = shr;

    *out_values = vals;
    *out_count = n;
    return 0;
}

CSVData* csv_read(const char *filename) {
    if (!filename) {
        fprintf(stderr, "csv_read: filename is NULL\n");
        return NULL;
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("csv_read: fopen");
        return NULL;
    }

    CSVData *csv = malloc(sizeof(CSVData));
    if (!csv) {
        fclose(f);
        return NULL;
    }
    csv->data = NULL;
    csv->rows = 0;
    csv->cols = 0;

    size_t rows_cap = 16;
    csv->data = malloc(rows_cap * sizeof(double*));
    if (!csv->data) {
        free(csv);
        fclose(f);
        return NULL;
    }

    char *line = NULL;
    int header_skipped = 0;

    while ((line = read_line(f)) != NULL) {
        int only_ws = 1;
        for (const char *t = line; *t; t++) {
            if (!isspace((unsigned char)*t)) { only_ws = 0; break; }
        }
        if (only_ws) { free(line); continue; }

        size_t tokens = 0;
        if (is_line_numeric(line, &tokens)) {
            double *vals = NULL;
            size_t cnt = 0;
            int r = parse_line_to_doubles(line, &vals, &cnt);
            free(line);

            if (r != 0) {
                fprintf(stderr, "csv_read: failed parsing first data line\n");
                fclose(f);
                free(csv->data);
                free(csv);
                return NULL;
            }

            csv->cols = cnt;
            csv->data[csv->rows++] = vals;
            break; 
        } else {
            free(line);
            header_skipped = 1;
            break;
        }
    }

    while ((line = read_line(f)) != NULL) {
        int only_ws = 1;
        for (const char *t = line; *t; t++) {
            if (!isspace((unsigned char)*t)) { only_ws = 0; break; }
        }
        if (only_ws) { free(line); continue; }

        double *vals = NULL;
        size_t cnt = 0;
        int r = parse_line_to_doubles(line, &vals, &cnt);
        free(line);

        if (r == -2) {
            fprintf(stderr, "csv_read: empty token encountered in data\n");
            fclose(f);
            csv_free(csv);
            return NULL;
        } else if (r == -3) {
            fprintf(stderr, "csv_read: non-numeric token encountered in data\n");
            fclose(f);
            csv_free(csv);
            return NULL;
        } else if (r != 0) {
            fprintf(stderr, "csv_read: memory error parsing data row\n");
            fclose(f);
            csv_free(csv);
            return NULL;
        }

        if (cnt == 0) {
            free(vals); 
            continue;
        }

        if (csv->cols == 0) {
            csv->cols = cnt;
        } else if (cnt != csv->cols) {
            fprintf(stderr, "csv_read: inconsistent column count: expected %zu, got %zu\n",
                    csv->cols, cnt);
            free(vals);
            fclose(f);
            csv_free(csv);
            return NULL;
        }

        if (csv->rows >= rows_cap) {
            rows_cap *= 2;
            double **tmp = realloc(csv->data, rows_cap * sizeof(double*));
            if (!tmp) {
                free(vals);
                fclose(f);
                csv_free(csv);
                return NULL;
            }
            csv->data = tmp;
        }
        csv->data[csv->rows++] = vals;
    }

    fclose(f);

    if (csv->rows == 0) {
        fprintf(stderr, "csv_read: no numeric data rows found in file\n");
        free(csv->data);
        free(csv);
        return NULL;
    }

    double **shr = realloc(csv->data, csv->rows * sizeof(double*));
    if (shr) csv->data = shr;

    return csv;
}


void csv_free(CSVData *csv) {
    if (!csv) return;
    if (csv->data) {
        for (size_t i = 0; i < csv->rows; ++i) {
            free(csv->data[i]);
        }
        free(csv->data);
    }
    free(csv);
}
