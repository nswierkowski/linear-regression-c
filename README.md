# Linear Regression in C

## Overview
This project is a **from-scratch implementation of Linear Regression in C**  
using **batch gradient descent** for parameter optimization.  
It supports reading data from a CSV file, training the model, and printing the learned parameters  
and training error.

The design follows **clean code principles**:
- Separation into logical modules (`csv_reader`, `gradient_descent`, `linear_regression`, `utils`)
- Clear header/source file structure
- Memory safety (avoiding leaks, undefined behavior)
- Error handling at each step

---

## Project Structure
```
linear_regression_c/
│
├── include/                  
│   ├── csv_reader.h
│   ├── linear_regression.h
│   ├── gradient_descent.h
│   ├── utils.h
│   └── config.h
│
├── src/                     
│   ├── csv_reader.c
│   ├── linear_regression.c
│   ├── gradient_descent.c
│   ├── utils.c
│   └── main.c
│
├── data/                     
│   └── sample.csv
│
├── tests/                  
│   ├── test_csv_reader.c
│   └── test_gradient_descent.c
│
├── Makefile                  
└── README.md
```
---

## Features
- **CSV Reader** – Loads numeric datasets into memory (`double**` format).
- **Linear Regression** – Predicts using multiple features (last column = target).
- **Gradient Descent** – Optimizes parameters to minimize Mean Squared Error (MSE).
- **Utilities** – Vector printing, MSE calculation, zeroing arrays.
- **Unit Tests** – Verify CSV reading and model training.

---

## Building & Running

### **Prerequisites**
- GCC (or any C11-compliant compiler)
- Make
- `math.h` (for `fabs`, `pow`, etc. — part of standard library)

---

### **1. Build everything**
```bash
make
```

### **2.Run all tests **
```bash
make run_tests
```

### **2.Run main project **
```bash
make run_project CSV=path/to/your.csv
```

## Dataset Format

The CSV file should:
- Contain numeric values only
- Have at least 1 feature column and 1 target column
- The last column is interpreted as the target variable

## Future Improvements

- Command-line arguments for learning rate, iterations, and bias handling.
- Feature normalization for better convergence.
- Mini-batch or stochastic gradient descent.
- Save/load trained model parameters.
- Better error reporting for malformed CSVs.




