//this program find the semiprimes between a range of number
// there are 4 main errors in this code. The first error is that the is_prime function incorrectly return 1 and 0, this is the reverse of the supposed result.
// the second main error is that at line 40 should be k = i/j instead of i%j because we want to find the other number that can divide with i.
// the third main error is that the print_semiprimes function always return 0 because there is no code to change to return 1, so i add the code at line 44.
// the fourth main error is that the output prints the last semiprime twice, which can be fixed by adding a code "break;" to terminate the loop.
#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j; // k = i/j instead of k%j
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1; // if found a semi-prime return 1
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
