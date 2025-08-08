CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = src/csv_reader.c src/linear_regression.c src/gradient_descent.c src/utils.c
TESTS = test_csv_reader test_gradient_descent
TARGET = linear_regression
CSV = data/sample.csv

.PHONY: all clean run_tests run_project

all: $(TARGET) $(TESTS)

$(TARGET): $(SRC) src/main.c
	$(CC) $(CFLAGS) $(SRC) src/main.c -o $@ -lm

test_csv_reader: src/csv_reader.c tests/test_csv_reader.c
	$(CC) $(CFLAGS) src/csv_reader.c tests/test_csv_reader.c -o $@ -lm

test_gradient_descent: $(SRC) tests/test_gradient_descent.c
	$(CC) $(CFLAGS) $(SRC) tests/test_gradient_descent.c -o $@ -lm

run_tests: $(TESTS)
	@echo "Running CSV Reader test..."
	@./test_csv_reader
	@echo "Running Gradient Descent test..."
	@./test_gradient_descent

run_project: $(TARGET)
	@echo "Running Linear Regression on $(CSV)"
	@./$(TARGET) $(CSV)

clean:
	rm -f $(TESTS) $(TARGET)
