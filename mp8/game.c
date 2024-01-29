#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


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
    
    int width, height;  // Initialize Variable for width and height to be stored
    fscanf(fileptr, "%d %d\n",&height, &width); // Reads width and height from the file by searching for decimal
    fgetc(fileptr); //Gets rid of the newline on the first line after width and height
    // Set width and height to the width & height found from scannng the file
    maze->width = width;
    maze->height = height;
    
    int i, j;
    // Allocate memory for Row Pointer in cells
    maze->cells = malloc(sizeof(maze->cells)*height);
    // Allocate memory for each roww using the width (column needed each row)
    for (i=0; i<height; i++){
        maze->cells[i] = malloc(sizeof(maze->cells[i])*width);
    }
    char temp; // temp variable to store scanned characters 
    // Loop through the maze to find E and S
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            fscanf(fileptr, "%c", &temp);
            maze->cells[i][j] = temp;
            if(maze->cells[i][j]=='S'){ // If S found, then set start Row and Column to existing i, j
                maze->startRow = i;
                maze->startColumn = j;
                
            }
            if(maze->cells[i][j]=='E'){ //If E found, then set start Row and Column to existing i, j
                maze->endRow = i;
                maze->endColumn = j;
            } // else do nothing
        }
        fscanf(fileptr, "%c", &temp); //Gets rid of the newline at the end of each row
    }
    fclose(fileptr);
    return maze;
    
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
    for(i=0; i<(maze->height); i++){
        free(maze->cells[i]);
    }
    // Free the memory allocated for the cells
    free(maze->cells);
    // Free the memory allocated for the whole maze
    free(maze);
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
    if (col<0 || row<0 || row>=maze->height || col>=maze->width){
        return 0;
    }

    if (maze->cells[row][col] != ' ' && maze->cells[row][col] != 'S' && maze->cells[row][col] != 'E'){
        return 0;
    }
    
    if(maze->cells[row][col] == 'E'){
        if(maze->startRow >= 0 && maze->startRow < maze->height && maze->startColumn >= 0 && maze->startColumn < maze->width){
            maze->cells[maze->startRow][maze->startColumn] = 'S';
        }
        return 1;
    }
    
    maze->cells[row][col] = '*';

    if(solveMazeDFS(maze, col, row-1) || solveMazeDFS(maze, col+1, row) || solveMazeDFS(maze, col, row+1) || solveMazeDFS(maze, col-1, row)){
        return 1;
    }

    maze->cells[row][col] = ' ';
    return 0;
}
