#include <stdio.h>
#include <stdlib.h>
/* Team: sirapop3, hmei7,  kp38 */
/* Our approach relies in hardcoding the 1st term to print 1, then using a for loop to calculate Coefficient. Our calculation method 
is the same as the equation given on the webpage where we multiply the previous coefficient result with the current value calculatead by the equation
and storing that in the Coefficient variable. We finish by printing that Coefficient value. The For loop iterate till all coefficient terms are 
printed */
int main()
{
  unsigned long row;  /*Row is n for the row index*/ 
  unsigned long i ;   /*i for the ith term starting at 0*/
  unsigned long CEF = 1; /* CEF is the variable for coefficients*/
  printf("Enter a row index: "); /* Prompt to ask user for inputing the row index they want*/
  scanf("%lu", &row);            /* Stores user input into variable row*/
  int k = row; /*Number of coefficient is always 1 more than row index number*/
  for (i=0; i<=k; i++){ /*For loop to print (row+1) number of terms */ 
    if(i>0){            /* First value has to manually printed to be 1*/
      CEF = CEF * (row + 1 - i) / i; /* Equation given on the course website*/
    }
    printf("%lu ", CEF); /* Prints coefficient value*/
  }
  printf("\n"); /* go to next line*/
  return 0;

}
