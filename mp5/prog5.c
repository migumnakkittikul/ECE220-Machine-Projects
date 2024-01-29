/* Group Member
	hmei7, sirapop3, kp38
    Introduction:
    For set_seed, our code use the approach of sscanf to check how many variable has been fill, and when sscanf outputs 1, it means only 1 variable is 
    filled, then we call the srand function and return 1, if sscanf returns anything other than 1, we return 0 and print invalid seed
    
    For start game we set the solutions to each of the 4 solution pointer variable and store it there. Then we copy that to solution1 - solution4
    accordingly and initalizes the guess_number (counter) to be 0

    For make_guess function, we use check if sscanf outputs 4 indicating filling the 4 integer value input by the user
    Then we checked if all the values are within range, else print invalid input and return 0
    Next, we set the value in range to the corresponding pointer variable given as parameters to the make_guess function
    Then, we check for Perfectly Matched by comparing 1st to the solution 1, 2nd to solution2, and so on. If perfectly matched then we use set
    a individual variable that indicates that it is paired
    Last but not least, we checked for mismatches by going through the condition that when the perfectly matched pair is less than 3, we know
    there could be mismatched pair, and for 3 and 4 perfected matched we returned 1 for valid input and proceed to the next guess
    At the end, we check for pair number that are unmatched with other pairs number that are mismatched and increase mismatch counter.
    After that we return 1 for valid input. 
    
    */


/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
      int seed;     /*  Initialize seed variable*/
      char string[5]; /* Initalize String to unset length*/
      if(sscanf(seed_str, "%d%1s", &seed, string) == 1){ /* Check how many variable have been successfully filled*/
                                                    /* Check whether it is the string array is not filled*/
            srand(seed);                             /* Put the value seed into srand function*/
            return 1;                                /* If string array not filled, then we know int seed has been filled*/
            }
            else{          
                printf("set_seed: invalid seed\n");      /* Print invalid Message*/                         
                return 0;                                /* If the string array is not 0 then we know it has been filled so return 0*/
            }
}
      
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below

/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four)
{   
    *one = 1 + rand() % 8;                              /* add the random value 1-8 to *one */
    *two = 1 + rand() % 8;                              /* add the random value 1-8 to *two */
    *three = 1 + rand() % 8;                            /* add the random value 1-8 to *three */
    *four = 1 + rand() % 8;                             /* add the random value 1-8 to *four */
    //your code here
    guess_number = 0;                                   /*set guess_number to be equal to one */
    solution1 = *one;                                   /* set solution1 to *one */
    solution2 = *two;                                   /* set solution2 to *two */
    solution3 = *three;                                 /* set solution3 to *three */
    solution4 = *four;                                  /* set solution4 to *four */
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
    int perfectMatches = 0;                                                        /*initialize the counter for perfectMatches*/
    int misplacedMatches = 0;                                                      /*initialize the counter for misplacedMatches*/     
    int pair1 = 0;                                                                 /*initialize the counter for paired number at the first position*/
    int pair2 = 0;                                                                 /*initialize the counter for paired number at the second position*/
    int pair3 = 0;                                                                 /*initialize the counter for paired number at the third position*/
    int pair4 = 0;                                                                 /*initialize the counter for paired number at the fourth position*/     
    int w, x, y ,z;
    char post[200];
    if((sscanf(guess_str, "%d %d %d %d %1s", &w, &x, &y, &z, post) == 4 )){        /* use sscanf to load the string guess_str, then put the numbers into w,x,y,z, the extra strings are stored in post*/
        if (w <= 8 && w >= 1){                                                     /* check whether w x y and z are in the range of 1-8 inclusive*/
            if (x <= 8 && x >= 1){
                if (y <= 8 && y >= 1){
                    if (z <= 8 && z >= 1){                                         
                        *one = w;                                                  /* assign the value w to *one */
                        *two = x;                                                  /* assign the value x to *two */
                        *three = y;                                                /* assign the value y to *three */
                        *four = z;                                                 /* assign the value z to *four */
                        
                        if ( *one == solution1){                                   /* check if the inputed number at the first position is a perfect match or not*/ 
                            perfectMatches++;                                      /* increase the perfectMatches counter*/
                            pair1++ ;                                              /* increased the paired position counter*/
                        }
                        if ( *two == solution2){                                   /* check if the inputed number at the second position is a perfect match or not*/
                            perfectMatches++;                                      /* increase the perfectMatches counter*/
                            pair2++ ;                                              /* increased the paired position counter*/
                        }
                        if ( *three == solution3){                                 /* check if the inputed number at the third position is a perfect match or not*/
                            perfectMatches++;                                      /* increase the perfectMatches counter*/
                            pair3++ ;                                              /* increased the paired position counter*/
                        }
                        if ( *four == solution4){                                  /* check if the inputed number at the fouth position is a perfect match or not*/
                            perfectMatches++;                                      /* increase the perfectMatches counter*/
                            pair4++ ;                                              /* increased the paired position counter*/
                        }

                        if (perfectMatches == 4){                                  /* if the guess is perfect match, then return 1 */
                            guess_number++ ;                                       /* increment the guess_number */
                            return 1; // guessed all correctly
                        } else if (perfectMatches == 3){                           /* if not all perfect matches, continue the guess */
                            guess_number++ ;                                       /* increment the guess_number */
                            printf("With guess %d, you got %d perfect matches and %d misplaced matches. \n", guess_number, perfectMatches, misplacedMatches);   /* print the message */
                            return 1;                                              /* return 1 with valid input */
                        } else if (perfectMatches < 3){                            /* check the number has not been paired, check for misplaced matches*/
                            if (pair1 == 0){                                       /* if pair1 has not been paired */
                                if (pair2 == 0 && *one == solution2){              /* if pair 2 is not paired and is equal to solution 2, it has been misplaced */
                                    misplacedMatches++;
                                }
                                else if (pair3 == 0 && *one == solution3){         /* repeat for pair 3 and solution 3 */
                                    misplacedMatches++;                            /* increment misplacedMatches*/
                                }
                                else if (pair4 == 0 && *one == solution4){         /* repeat for pair 4 and solution 4 */
                                    misplacedMatches++;
                                }   
                            }
                            if (pair2 == 0){                                       /* if pair2 has not been paired */
                                if (pair1 == 0 && *two == solution1){              /* if pair 1 is not paired and is equal to solution 1, it has been misplaced */
                                    misplacedMatches++;                            /* increment misplaceMatches */
                                }
                                else if (pair3 == 0 && *two == solution3){         /* repeat for pair 3 and solution 3 */   
                                    misplacedMatches++;
                                }
                                else if (pair4 == 0 && *two == solution4){         /* repeat for pair 4 and solution 4 */
                                    misplacedMatches++;
                                }   
                            }

                            if (pair3 == 0){                                        /* if pair3 has not been paired */
                                if (pair1 == 0 && *three == solution1){             /* if pair 1 is not paired and is equal to solution 1, it has been misplaced */
                                    misplacedMatches++;                             /* increment misplaceMatches */
                                }
                                else if (pair2 == 0 && *three == solution2){       /* repeat for pair 2 and solution 2 */   
                                    misplacedMatches++;
                                }
                                else if (pair4 == 0 && *three == solution4){       /* repeat for pair 4 and solution 4 */   
                                    misplacedMatches++;
                                }   
                            }

                            if (pair4 == 0){                                       /* if pair4 has not been paired */
                                if (pair1 == 0 && *four == solution1){             /* if pair 1 is not paired and is equal to solution 1, it has been misplaced */
                                    misplacedMatches++;                            /* increment misplacedMatches*/
                                }
                                else if (pair2 == 0 && *four == solution2){        /* repeat for pair 2 and solution 2 */   
                                    misplacedMatches++;
                                }
                                else if (pair3 == 0 && *four == solution3){        /* repeat for pair 3 and solution 3 */   
                                    misplacedMatches++;
                                }   
                            }
                            guess_number++;                                        /* increment guess_number*/                       
                            printf("With guess %d, you got %d perfect matches and %d misplaced matches. \n", guess_number, perfectMatches, misplacedMatches);
                            return 1;
                        }else{
                            guess_number++ ;                                       /* increase the guess_number counter*/
                            printf("With guess %d, you got %d perfect matches and %d misplaced matches. \n", guess_number, perfectMatches, misplacedMatches);    /* print out the guess_number, perfectMatches, and misplacedMatches*/
                            return 1;                                              /* return 1 when the user's input is valid*/
                        }
                    }else {                                                                       /* If the user's input did not pass the required condition*/
                        guess_number++ ;                                                            /* increase the guess_number counter*/
                        printf("make_guess: invalid guess\n");                                      /* tell the user that the input is invalid*/
                        return 0;                                                                   /* return value 0 to take a new input*/
            
                    }
                }else{                                                                    /* If the user's input did not pass the required condition*/
                guess_number++;                                                             /* increase the guess_number counter*/
                printf("make_guess: invalid guess\n");                                      /* tell the user that the input is invalid*/
                return 0;                                                                   /* return value 0 to take a new input*/
                }
            }else{                                                                    /* If the user's input did not pass the required condition*/
            guess_number++;                                                             /* increase the guess_number counter*/
            printf("make_guess: invalid guess\n");                                      /* tell the user that the input is invalid*/
            return 0;                                                                   /* return value 0 to take a new input*/
            }
            
      
        }else{                                                                        /* If the user's input did not pass the required condition*/
            guess_number++;                                                             /* increase the guess_number counter*/
            printf("make_guess: invalid guess\n");                                      /* tell the user that the input is invalid*/    
            return 0;                                                                   /* return value 0 to take a new input*/
        }
        

    }else{                                                                            /* If sscanf() != 4*/
        guess_number++;                                                                 /* increase the guess_number counter*/
        printf("make_guess: invalid guess\n");                                          /* tell the user that the input is invalid*/
        return 0;                                                                       /* return value 0 to take a new input*/
    }
    
    

//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
    guess_number++;                                                                    /* increment guess_number */
    printf("make_guess: invalid guess\n");                                             /* print the invalid message */
    return 0;                                                                          /* if invalid return 0 */
}


