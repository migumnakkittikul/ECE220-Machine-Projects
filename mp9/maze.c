#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/* 
Partners: hmei7, sirapop3, kp38


This program is capable of solving a maze given in a text file. The program, first, allocate a certain size of memory regarding
the size height x width specified at the start of the maze text file. Then, it traverses through the maze text file and copy the 
maze grid into the memory. Then the program calls the function solveMazeDFS() to solve the maze. The function start from the
starting point then move to the next point and check if it is a correct path or not using the conitions specified in the MP9
instructions in the ECE220 webpage. The function is a recursive function, meaning it calls itself repeatedly until it finds that
the maze is unsolvable, returning 0, or the maze is solved, returning 1.

In our createMaze function we open the file for read. We use malloc for memory allocation in the heap for our "maze". Then,  
we allocated memory locations for the cells for rows first then the columns.
We then read the beginning of the text file for its dimensions. With that, we loop through the entire file with the height and width parameter
we read. In the loop, it stores the character read into a tempory local variable, and puts that value on the corresponding location
in the maze, then we check if that value is S or E, if so we assigned that current position to the maze (maze_t type) respectively

The destoryMaze function frees the maze from ow by row, then the cell itself, then the maze

The printMaze function just loops and prints the maze using rows and cols.


*/ 
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    
    FILE *fileptr; //Initialize File Pointer
    fileptr = fopen(fileName, "r"); // Opens file in read mode
    
    maze_t * maze = malloc(sizeof(maze_t)); // Give Memory allocation for the size of the maze_t
    
    int x, y;  // Initialize Variable for width and height to be stored
    fscanf(fileptr, "%d %d",&x, &y); // Reads width and height from thse file by searching for decimal
    fgetc(fileptr); //Gets rid of the newline on the first line after width and height
    // Set width and height to the width & height found from scannng the file
    maze->width = x; // point to the width element in the struct
    maze->height = y;// point to the height element in the struct
    
    int i, j; // define the variables i and j
    // Allocate memory for Row Pointer in cells
    maze->cells = malloc(sizeof(maze->cells)*(maze->height)); // give some memory spaces to cells
    // Allocate memory for each roww using the width (column needed each row)
    for (i=0; i<maze->height; i++){ // loop through the row
        maze->cells[i] = malloc(sizeof(maze->cells[i])*maze->width); // allocate some spaces for cells
    }
    char temp; // temp variable to store scanned characters 
    // Loop through the maze to find E and S
    for(i=0; i<(maze->height); i++){ // loop through the rows
        for(j=0; j<(maze->width); j++){ // loop through the columns
            fscanf(fileptr, "%c", &temp); // take character from the file and put it in temp
            maze->cells[i][j] = temp; // set the cell at i and j to temp
            if(maze->cells[i][j]=='S'){ // If S found, then set start Row and Column to existing i, j
                maze->startRow = i; // point to the element startRow
                maze->startColumn = j; // point to the element startColumn
                
            }
            if(maze->cells[i][j]=='E'){ //If E found, then set start Row and Column to existing i, j
                maze->endRow = i; // element endRow to be equal to i
                maze->endColumn = j; // element endColumn to be equal to j
            } // else do nothing
        }
        fscanf(fileptr, "%c", &temp); //Gets rid of the newline at the end of each row
    }
    fclose(fileptr); // stop reading from the file
    return maze; // return the value

    
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    
    // Free the memory allocated row  by row
    int i; // define the variable i
    for(i=0; i<(maze->height); i++){ // loop through the row
        free(maze->cells[i]); // free each row starting from i = 0
    }
    // Free the memory allocated for the cells
    free(maze->cells); // free the cells first pointer
    // Free the memory allocated for the whole maze
    free(maze); // free the maze second pointer
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j; // define the variables i and j
    for (i = 0; i < (maze->height); i++){ // loop through the row and column
        for (j = 0; j < (maze->width); j++){
            printf("%c", maze->cells[i][j]); // print the cells
        }
        printf("\n"); // print new lines
    }




}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if (col<0 || row<0 || row>(maze->height-1)|| col>(maze->width-1)){      // Check if the current cell is still inbound
        return 0;
    }
    if (maze->cells[row][col] != ' '){ // If not space, Start position, or end, then we know it is not a empty cell, return 0
        if (maze->cells[row][col] != 'S' && maze->cells[row][col] != 'E'){
            return 0;
        }
    }
    
    if(maze->cells[row][col] == 'E'){ // Check if current position is the End
        maze->cells[maze->startRow][maze->startColumn] = 'S'; // Restore S at starting position as it had been marked
        return 1;
    }
    
    maze->cells[row][col] = '*'; // mark the location '*' as a solution

    if(solveMazeDFS(maze, col-1, row) == 1){    // Check the left cell
        return 1;
    }
    
    if(solveMazeDFS(maze, col+1, row) == 1){    // Check the right cell
        return 1;
    }
     
    if(solveMazeDFS(maze, col, row+1)==1){      // Check the above cell
        return 1;
    }

    if(solveMazeDFS(maze, col, row-1)){         // Check the below cell
        return 1;
    }    

    maze->cells[row][col] = '~'; //Mark the current position to be VISITED
    return 0;
}