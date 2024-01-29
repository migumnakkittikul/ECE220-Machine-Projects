#include "sudoku.h"
// hmei7, kp38, sirapop3
// This program functions to solve the sudoku game. There are 5 main functions that are used in this program.
// The first function is is_val_in_row. It checks whether the variable val has already existed in the row of array.
// The second function is_val_in_col does the same thing as the first function except it checks the columns.
// The third function is_val_in_3x3_zone checks whether where the cell is in which box and whether or not it is detected in the box.
// The fourth function is_val_valid checks the 3 rules of the game, preventing the program to write the same number in the same row/col and no same number in the same box.
// The function solve_sudoku focus on the approach of backtracking to see whether the sudoku board is filled up after every input, if
// not we find an empty cell that is available to fill in. Then we start inputting numbers 1-9 while also making
// sure if they are valid by calling the is_val_valid function. Then, then we call the solve_sudoku function within the same (let's say we are at sudoku[0][0])
// iteration to check if it is filled. If not, we keep filling up the board, until in some cases where the value we initially
// put on the board is not the correct solution, we would jump back to the inital board and replace with 0 at that inital position sudoku[0][0]
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
// int *returnCell;
// returnCell = (int *)malloc(2 * sizeof(int));
int is_val_in_row(const int val, const int i, const int sudoku[9][9])
{

  assert(i >= 0 && i < 9); // if the row is beyond the bound, exit the program with error
  int j;                   // define int j
  for (j = 0; j < 9; j++)  // loop through the row
  {
    if (sudoku[i][j] == val) // if the value at i,j is equal to val, return 1
    {
      return 1;
    }
  }
  // BEG TODO

  return 0; // program return 0 if the value isn't equal to val
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9])
{

  assert(j >= 0 && j < 9);
  int k;                  // define the variable k
  for (k = 0; k < 9; k++) // loop through the column
  {
    if (sudoku[k][j] == val) // if the value at k,j is equal to val, return 1
    {
      return 1;
    }
  }

  // BEG TODO

  return 0;
  // END TODO
}
// Check If this 3x3 Zone already has the Value the user wants to input
int CheckBox(int row, int col, const int val, const int sudoku[9][9])
{
  int i;                          // define variable i
  int j;                          // define variable j
  for (i = row; i < row + 3; i++) // loop through the row in 3 in order to check each box of the board
  {
    for (j = col; j < col + 3; j++) // loop through the column in 3 in order to check each box of the board
    {
      if (sudoku[i][j] == val) // if found that the value at i,j is equal to val, return 1, else return 0
      {                        // If value exists on 3x3 zone, return 1
        return 1;
      }
    }
  }
  return 0; // Else return 0
}
// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9])
{

  assert(i >= 0 && i < 9);
  int rowOffset; // row offset for the starting coordinate of each box
  int colOffset; // col offset for the starting coordinate of each box
  if (0 <= i && i <= 2)
  {                // // if the row index is within the top-left box
    rowOffset = 0; // set row equal to zero
  }
  else if (3 <= i && i <= 5)
  {                // if the row index is within the mid-left box
    rowOffset = 3; // rowOffset = 3
  }
  else if (6 <= i && i <= 8)
  {                // if the row index is within the bottom-left box
    rowOffset = 6; // rowOffset = 6
  }
  // BEG TODO
  if (0 <= j && j <= 2)
  {                // if the col index is within the top-mid box
    colOffset = 0; // colOffset = 0
  }
  else if (3 <= j && j <= 5)
  {                // if the col index is within the top-mid box
    colOffset = 3; // colOffset = 3
  }
  else if (6 <= j && j <= 8)
  {                // if the col index is within the top-mid box
    colOffset = 6; // colOffset = 6
  }
  if ((CheckBox(rowOffset, colOffset, val, sudoku)) == 1)
  {
    return 1; // if the function CheckBox is true, return1
  }
  else
  {
    return 0; // else return 0
  }

  // BEG TODO
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.

int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9])
{

  assert(i >= 0 && i < 9 && j >= 0 && j < 9);
  int rowChecker = is_val_in_row(val, i, sudoku);         // Store Boolean of Whether Value is in Row is True in rowChecker.
  int colChecker = is_val_in_col(val, j, sudoku);         // Store Boolean of Whether Value is in Column is True in colChecker.
  int boxChecker = is_val_in_3x3_zone(val, i, j, sudoku); // Store Boolean of Whether Value is in the 3 by 3 box is True in boxChecker.

  if (rowChecker == 0 && colChecker == 0 && boxChecker == 0) // If Value not in row, column, or box, then we return 1 meaning the Value is Valid in that position
  {
    return 1;
  }
  else // Else return false since the value cannot be placed in that position
  {
    return 0;
  }

  // END TODO
}
// findZeroCoordinate inputs an Array that we Store the indexes of the row and column that has the Value 0 in it checking row by row
int findZeroCoordinate(int returnCell[], const int sudoku[9][9])
{
  int i, j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if (sudoku[i][j] == 0) // If Value 0 is found, then we set the Array index 0 to the row and the Array index 1 to the column
      {
        returnCell[0] = i;
        returnCell[1] = j;
      }
    }
  }
  return 0; // Return 0 to indicadte the end of this function
}
// Check Sudoku board row by row if any value is equal to 0, if so Return False/0, else return True/1
int check_sudoku_filled(const int sudoku[9][9])
{
  int i;
  int j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if (sudoku[i][j] == 0) // Return 0 if Value 0 is Found to Indicate the Board is not yet filled
      {
        return 0;
      }
    }
  }
  return 1; // Return 1 when no 0 is found on the board, meaning the Boradi sn ot yet filled
}
// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9])
{
  int returnCell[2]; // initialize returnCell holder
  int i, j;
  // BEG TODO.
  if (check_sudoku_filled(sudoku) == 1) // check if the sudoku board is filled with numbers not 0, return 1 if true
  {
    return 1; // return 1 when the whole board is filled with numbers
  }
  else
  {
    findZeroCoordinate(returnCell, sudoku); // find the coordinate that holds 0 (unfilled) and store the row index in returnCell[0] and column index in returnCell[1]
    i = returnCell[0];
    j = returnCell[1];
  }

  for (int num = 1; num <= 9; num++) // loop through the number 1 to 9 for filling a particular coordinate
  {

    if (is_val_valid(num, i, j, sudoku)) // if the current num is distinct in the current row, column, and box, then fill it in the current coordinate
    {
      sudoku[i][j] = num;
      if (solve_sudoku(sudoku)) // if the sudoku is solved, return 1 (true).
      {
        return 1;
      }
      sudoku[i][j] = 0; // if not reset the current cell to 0
    }
  }
  return 0; // else return false and back track
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9])
{
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}