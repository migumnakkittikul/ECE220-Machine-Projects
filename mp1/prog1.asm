;sirapop3
; this LC3 program detects the occurence of each string of the english characters as well as special characters in sentences. Then, keep count of the numbers of times they appear. I approach this by using nexsted loops to keep track of looping 27 times (every letter and character) and printing them out by converting ASCII to HEX
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
	AND R0,R0,#0; clear registers, register to be printed out
	AND R1,R1,#0; digit counters
	AND R2,R2,#0; bit counter
	AND R3,R3,#0; the loaded content
	AND R4,R4,#0; used to store address to load into R3
	AND R5,R5,#0; counter to loop 27 times
	AND R6,R6,#0; contains the letters and special characters
	LD R6, LETTER ; load content in LETTER into R6
	LD R4,HIST_ADDR ; load content in HIST_ADDR into R4
        
	
; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; digit counter is -4
    
    ADD R5,R5,#-15; check if the loop goes for 27 times or not "-27"
    ADD R5,R5,#-12;
    
	

START
    LDR R3,R4,#0; load the content at R4 into R3
    ADD R5,R5,#0; 
    BRzp DONE ; check value of the loop 27 times or not
    ST R0, SAVE_R0 ; save R0
    ADD R1,R1,#-4; check if digit counter is less than 4
    AND R0,R0,#0; clear R0
    ADD R0,R6,#0; copy R6 into R0
    OUT ; print the letter
    AND R0,R0,#0; clear R0
    LD R0, SPACE ; load "space" into R0 for printing
    OUT ; print the space
    LD R0, SAVE_R0 ; load back the original R0 value
    
    
CHECKDIGIT
    
    ADD R1,R1,#0; 4 digit counters
    BRzp LOOP27 ; if the loop is less than 27, loop to LOOP27


    AND R0,R0,#0; DIGIT
    AND R2,R2,#0; bits counter
    ADD R2,R2,#-4; Add -5 to R2 to check its value

CHECKBIT

    ADD R2,R2,#0; check the value of R2
    BRz PRINT ; check if bit counter < 4 
   
    ADD R0,R0,R0; shift DIGIT left
    ADD R3,R3,#0;
    BRn TRUE ; branch to true if R3<0
    ADD R0,R0,#0; add 0 to digit
    ADD R3,R3,R3; shift R3 left
    ADD R2,R2,#1; increment bit counter
    BRnzp CHECKBIT ; jump to CHECKBIT

TRUE
    ADD R0,R0,#1; add one to digit
    ADD R3,R3,R3; shift R3 left
    ADD R2,R2,#1; increment bit counter
    BRnzp CHECKBIT ; jump to CHECKBIT

PRINT 
    ADD R0,R0,#-9; check whether R0 is less than or equal to 9
    BRnz PRINTTRUE ;Branch to PRINTTRUE if R0 is less than or equal to 9
    ADD R0,R0,#9; cancel the #9 out as to not altering with the values in the register
    ADD R0,R0,#15; "A-10"
    ADD R0,R0,#15;
    ADD R0,R0,#15;
    ADD R0,R0,#10;
    OUT ; print the bits
    ADD R1,R1,#1; increment digit counter
    BRnzp CHECKDIGIT ; jump to CHECKDIGIT

PRINTTRUE
    ADD R0,R0,#9; add R0 back to not alter value
    ADD R0,R0,#15; add 48
    ADD R0,R0,#15;
    ADD R0,R0,#15;
    ADD R0,R0,#3;
    OUT ; print
    ADD R1,R1,#1; increment digit counter
    BRnzp CHECKDIGIT ; jump to CHECKDIGIT
   
LOOP27
    
    LD R0, NEWLINE ; load the value to print a new line
    OUT ; print
    AND R0,R0,#0; clear R0
    ADD R4,R4,#1; increment to the next memory location to check the next lette
    ADD R5,R5,#1; add 1 to the loop
    ADD R6,R6,#1; increment to the next letter
    BRnzp START ; loop back to START




DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
LETTER		.FILL x0040	; start with the letter "@"
SPACE		.FILL x0020	; the ASCII "space"
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
SAVE_R0		.BLKW #1	; store R0
NEWLINE		.FILL x000A	; store the ascii new line

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
