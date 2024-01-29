#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
/*
Partners: Sirapop3, hmei7, kp38

This program convert data in a sparse matrix into a tuple data structure. In the first function, load_tuples(), the program
opens the input matrix file and copy the input file into the memory. The gv_tuples() function traverses through the linked-list
memory or the tuples to find the specified coordinate and return its value. The function set_tuples() adds the inputed coordinates
and value, but it also filters out the input that has 0 value. This allows the output matrix to be a sparse matrix. The function
save_tuples() save the output sparse matrix into an output file for the programmer to compare the output with the correct solution(gole version).
The function destroy_tuples() traverse through the whole tuples and free up the memory inside each tuple. Then it free up the whole
linked list at the end.




*/
sp_tuples *load_tuples(char *input_file)
{

    sp_tuples *mem_ptr = (sp_tuples *)malloc(sizeof(sp_tuples)); // Allocate memory to open the file

    FILE *file_ptr = fopen(input_file, "r"); // Initialize a file pointer to open the test file in READ mode
    if (file_ptr == NULL)
    { // The pointer points to nothing (the file does not exist), prints an error code
        printf("Error: %s not found", input_file);
        return NULL;
    }
    // Initialize a variables to take in the inputing row and column size
    int input_row;
    int input_col;
    fscanf(file_ptr, "%d %d\n", &input_row, &input_col);

    // Initialize different variables establish in this sp_tuples struct
    mem_ptr->m = input_row;      // initialize row
    mem_ptr->n = input_col;      // initialize col
    mem_ptr->nz = 0;             // initialize the value to zero
    mem_ptr->tuples_head = NULL; // initialize the head to null because the list is blank

    int r;          // declare int r
    int c;          // declare int c
    double content; // declare the variable content
    // While the line is not empty, put the input in the format
    while (fscanf(file_ptr, "%d %d %lf\n", &r, &c, &content) == 3)
    {
        set_tuples(mem_ptr, r, c, content); // call the function set_tuples
    }
    if (!feof(file_ptr))
    {
        return NULL; // return null
    }

    fclose(file_ptr); // stop reading the content of the file

    return mem_ptr; // return the pointer
}

double gv_tuples(sp_tuples *mat_t, int row, int col)

{
    // Initilize a node to the head node
    sp_tuples_node *mem_node = mat_t->tuples_head;
    // While this is not the last node, continues traversing through the memory
    while (mem_node != NULL)
    {
        // Find the node at the specified coordinate
        if (mem_node->row == row && mem_node->col == col)
        {
            return mem_node->value; // return the value
        }
        // the node points to the address of the consequent node
        mem_node = mem_node->next;
    }
    return 0;
}

void set_tuples(sp_tuples *mat_t, int row, int col, double value)
{
    sp_tuples_node *prev_node = NULL;                   // initialize pointer of previous node to null
    sp_tuples_node *existing_node = mat_t->tuples_head; // initialize pointer of existing node to the head of the list

    while (existing_node != NULL && (existing_node->row < row || (existing_node->row == row && existing_node->col < col)))
    {
        prev_node = existing_node;           // make previous node equal to the existing node
        existing_node = existing_node->next; // points the existing node to the next value
    }

    if (existing_node != NULL && existing_node->row == row && existing_node->col == col) // update the value of the node if the existing node exists
    {
        if (value == 0) // check the value whether it is equal to 0
        {

            if (prev_node == NULL) // check whether the previous node exists
            {

                mat_t->tuples_head = existing_node->next; // set the head of the list to be equal to next existing node
            }
            else
            {
                prev_node->next = existing_node->next; // set the next previous node to the next existing node
            }
            free(existing_node); // free the memory
            mat_t->nz -= 1;      // decrease the value by 1
        }
        else
        {

            existing_node->value = value; // sest the existing node value to be equal to the input value
        }
    }
    else if (value != 0) // if the value is not equal to 0
    {
        sp_tuples_node *new_node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); // give some memory space
        new_node->row = row;                                                         // initialize row
        new_node->col = col;                                                         // initialize col
        new_node->value = value;                                                     // initialize value
        new_node->next = existing_node;                                              // initialize the existing node

        if (prev_node == NULL) // check whether the previous node is equal to null
        {
            mat_t->tuples_head = new_node; // set the head of the list equal to the new node
        }
        else
        {
            prev_node->next = new_node; // set the previous node to the new node
        }
        mat_t->nz += 1; // increase the value by 1
    }
}
void save_tuples(char *file_name, sp_tuples *mat_t)
{
    FILE *file_ptr2 = fopen(file_name, "w"); // Set in write mode
    fprintf(file_ptr2, "%d %d\n", mat_t->m, mat_t->n);
    sp_tuples_node *nodeptr = mat_t->tuples_head; // Create a node pointer that points to the head of the sparse matrix
    while (nodeptr != NULL)                       // Write the row, col, and value while we are not at the end of the sparse matrix where it points to NULL
    {
        fprintf(file_ptr2, "%d %d %lf\n", nodeptr->row, nodeptr->col, nodeptr->value);
        nodeptr = nodeptr->next; // Set node pointer to the next
    }
    fclose(file_ptr2); // Close file and return nothing
    return;
}

sp_tuples *add_tuples(sp_tuples *matA, sp_tuples *matB)
{
    sp_tuples *matC_ptr = (sp_tuples *)malloc(sizeof(sp_tuples)); // Allocate new space for the new matrix C
    // sp_tuples_node *matCptr = matC->tuples_head

    sp_tuples_node *matAptr = matA->tuples_head; // Create pointer to the head of the matA
    sp_tuples_node *matBptr = matB->tuples_head; // Create pointer to the head of the matB

    matC_ptr->m = matA->m;        // initialize row
    matC_ptr->n = matA->n;        // initialize column
    matC_ptr->nz = 0;             // initialize the value to zero
    matC_ptr->tuples_head = NULL; // initialize the head pointer to null because the linked list is empty

    while (matAptr != NULL) // While we haven't reach the end of matA we set the value at position, row and column of matA to the corresponding spot on matC
    {
        set_tuples(matC_ptr, matAptr->row, matAptr->col, matAptr->value); // call the set_tuples function
        matAptr = matAptr->next;                                          // Set the pointer to the next head in the matrix A
    }
    double current_CValue;  // Initalize a placeholder for the current value of C
    while (matBptr != NULL) // Whhle we avenn't reach the end of matB, add the matB's value onto the matC's value on the corresponding position row and column
    {
        current_CValue = gv_tuples(matC_ptr, matBptr->row, matBptr->col);                  // Get the value of the currentvalue of C at position we are setting for the matrix B right now
        set_tuples(matC_ptr, matBptr->row, matBptr->col, current_CValue + matBptr->value); // Add the current value of C and B at the same position in the matrics
        matBptr = matBptr->next;                                                           // point to the next value
    }

    return matC_ptr; // Return the pointer to the matrix C
}
/*
sp_tuples *mult_tuples(sp_tuples *matA, sp_tuples *matB)
{
    return retmat;
}
*/

void destroy_tuples(sp_tuples *mat_t)
{
    sp_tuples_node *matCptr = mat_t->tuples_head; // Create pointer to the head of the matrix C
    sp_tuples_node *matCnext = NULL;              // Create a pointer that later points to the next head of the matrix C before deleting it
    while (matCptr != NULL)
    {                             // While we haven't reach the end of matrix C, set the next head to the matCnext pointer and free the current node,
        matCnext = matCptr->next; // point to the next value
        free(matCptr);            // free the memory
        matCptr = matCnext;       // update the node at matrix C to the next node at current location
    }
    free(mat_t); // free the list
    return;      // Return nothing
}