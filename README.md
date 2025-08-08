# Linear Regression in C

## Overview
This project is a from-scratch implementation of Linear Regression in C 
using batch gradient descent for parameter optimization.  
It supports reading data from a CSV file, training the model, and printing the learned parameters  
and training error.

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

### **2. Run all tests**
```bash
make run_tests
```

### **2. Run main project**
```bash
make run_project CSV=path/to/your.csv
```

## Dataset Format

The CSV file should:
- Contain numeric values only
- Have at least 1 feature column and 1 target column
- The last column is interpreted as the target variable


