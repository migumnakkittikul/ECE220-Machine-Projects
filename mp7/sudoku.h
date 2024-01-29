#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

// Function: is_val_in_row
int is_val_in_row(const int val, const int i, const int sudoku[9][9]);

// Function: is_val_in_col
int is_val_in_col(const int val, const int i, const int sudoku[9][9]);

// Function: is_val_in_3x3_zone
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]);

// Function: is_val_valid
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]);

// Function: solve_sudoku
int solve_sudoku(int sudoku[9][9]);

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9]);

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]);

// Check 3x3 zone whether val exist
int CheckBox(int row, int col, const int val, const int sudoku[9][9]);
// Delcaration of the function that checks whether Any Cell on the soduku board has value 0 at sudoku[row,column]
int findZeroCoordinate(int returnCell[2], const int sudoku[9][9]);
// Declaration of the function that checks whether the Sudoku board is filled
int check_sudoku_filled(const int sudoku[9][9]);
#endif