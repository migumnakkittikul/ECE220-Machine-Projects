/* group members: kp38, hmei7, sirapop3 */
/* This program simulates the Game of Life. We write 3 functions that each have their purpose. The first function would return the current number of live cells on the board.*/
/* We used for loops and if statements to implement the required conditions and finally return the final value of live cells. */
/* The second function is called in order to update the board according to the initial 4 conditions given in the instructions. */
/* We create a new duplicate board in order to not alter with the values when calling other functions. Then, we update the board according to the rules by using for loops, conditions and arrays.*/
/* The third function checks whether the board has been updated in order to know when should the program ends */
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
#include <stdlib.h>

int countLiveNeighbor(int *board, int boardRowSize, int boardColSize, int row, int col)
{

  int live_neighbor = 0; // initialize the number of live cells to 0
  for (int i = row - 1; i <= row + 1; i++)
  { // check from row-1 to row+1 inclusive
    if (i <= boardRowSize - 1 && i >= 0)
    { // check whether within the row boundary
      for (int j = col - 1; j <= col + 1; j++)
      { // check from col-1 to col+1 inclusive
        if (j <= boardColSize - 1 && j >= 0)
        { // check whether within the col boundary
          if ((i * boardColSize + j) != (row * boardColSize + col))
          { // if the cell isn't at the current row and col location
            if (board[i * boardColSize + j] == 1)
            {                  // if the cell is alive
              live_neighbor++; // increment the number of live cell
            }
          }
        }
      }
    }
  }
  return live_neighbor; // return the number of live cell
}

/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int *board, int boardRowSize, int boardColSize)
{
  int aliveNeighbor;                              // initialize an int variable to hold the number of alive neighbour
  int originalBoard[boardRowSize * boardColSize]; // initialize an array with the same size as board to hold the original array before editing
  for (int k = 0; k < (boardRowSize * boardColSize); k++)
  {                                  // for loop to copy the before-updated board to the originalBoard array
    originalBoard[k] = board[k]; // copy cell-by-cell for each loop
  }

  for (int i = 0; i < boardRowSize; i++)
  { // traversing through the row of the board
    for (int j = 0; j < boardColSize; j++)
    {                                                                                     // traversing through the column of the board
      aliveNeighbor = countLiveNeighbor(originalBoard, boardRowSize, boardColSize, i, j); // assigning the number of live neighbour in the aliveNeighbor variable
      if (aliveNeighbor < 2 || aliveNeighbor > 3)                                         // check whether the number of alive neighbor is less than two or greater than three
      {
        board[(i * boardColSize + j)] = 0; // if there is less than 2 alive neighbors or more than 3 alive neithbors, the cell dies
      }
      else if (aliveNeighbor == 3) // check whether there are 3 alive neighbors
      {
        board[(i * boardColSize + j)] = 1; // dead cell become alive if have 3 alive neighbors
      }
    }
  }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.a
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int *board, int boardRowSize, int boardColSize)
{
  int comparisonHolder[boardRowSize * boardColSize]; // initialize an holder array with the same size as board
  for (int k = 0; k < (boardRowSize * boardColSize); k++)
  {                                     // for loop to copy the original board into the comparisonHolder
    comparisonHolder[k] = board[k]; // copy each element into the comparisonHolder as the for loop traverses through the board
  }
  updateBoard(comparisonHolder, boardRowSize, boardColSize); // call the updateBoard function to update the board of the game of life to the next generation

  for (int i = 0; i < (boardRowSize * boardColSize); i++)
  { // for loop to check if there is any change made by the updateBoard function called
    if (board[i] != comparisonHolder[i])
    {           // compare cell-by-cell the updated board with the comparsionHolder which hold the previous generation of the board
      return 0; // return 0 if there was a change
    }
  }
  return 1; // return 1 if there was no change
}
