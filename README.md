# Matrix-Calculator-in-C

## Features

- Matrix Input/Generation
- View/Search Matrices
- Basic Matrix Operations (Addition, Subtraction, Multiplication)
- Matrix Properties (Determinant, Trace)
- Matrix Transformations (Inverse, Transpose)
- Elementary Row Operations
- Matrix Analysis (Symmetry, Orthogonality)
- Solve Systems of Linear Equations
- Load/Save/Delete Matrices

## Getting Started

### Prerequisites

- GCC compiler
- Make utility

### Compilation

To compile the program, navigate to the project directory and run:

This will create an executable named `main.c` or `test_full.c`.

## Usage

The program presents a menu-driven interface. Follow the on-screen prompts to perform various matrix operations.

1. Start by inputting or generating matrices.
2. Use the various menus to perform operations on your matrices.
3. Always enter matrix indices starting from 1.
4. For operations involving multiple matrices, ensure dimensions are compatible.
5. Use the View/Search menu to check your matrices at any time.

## Project Structure

- `matrix_calculator.h`: Main header file with function declarations and global variables
- `main.c`: Entry point of the program
- `main_menu.c`: Implementation of the main menu
- `input_generation_menu.c`: Functions for matrix input and generation
- `view_search_menu.c`: Functions for viewing and searching matrices
- `basic_operations_menu.c`: Implementation of basic matrix operations
- `properties_menu.c`: Functions for calculating matrix properties
- `transformations_menu.c`: Implementation of matrix transformations
- `row_operations_menu.c`: Functions for elementary row operations
- `analysis_menu.c`: Implementation of matrix analysis functions
- `solve_equations.c`: Functions for solving systems of linear equations
- `load_save_delete.c`: Implementation of load, save, and delete operations
- `help_menu.c`: Implementation of the help menu
- `matrix_operations.c`: Core matrix operation functions
- `Makefile`: For easy compilation of the project

## Contributing

Contributions to improve the calculator are welcome. Please feel free to submit a Pull Request.

## Acknowledgments

- This project was created as a learning exercise in C programming and matrix operations.
- Special thanks to all contributors and testers who helped improve this calculator.
