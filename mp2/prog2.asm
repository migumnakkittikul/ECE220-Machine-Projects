.ORIG x3000

; Group partners: hmei7, sirapop3, kp38
; This program takes in the user input. It pushes the integer inputed until it finds an operator. 
; Then it will operate the previous 2 numbers in the stack by popping them out into R3 and R4. Then, 
; the program will store the result of operation in the stack and move on to read the next number 
; in the user's input. The program will print 'Invalid' if the user's input is not correctly input:
; typing an operator or an equal sign before typing at least 2 numbers.

; temporary registers: R1,R2
READINPUT
    GETC                ; Read Input From Keyboard
    ST R0, SAVE_R0      ; Save Value of R0

CHECK_EQUAL
    AND R1, R1, #0      ; Clear Temp R1
    LD R1, INV_EQ_ASC   ; Load Inverse of Equal + 1 to R1
    ADD R0, R0, R1      ; ADD, See if Equal Sign Found
    BRz CHECK_RESULT    ; 
    BRnzp CHECK_SPACE   ;
    
CHECK_RESULT
    LD R0, SAVE_R0      ; Restore R0
    OUT
    AND R1, R1, #0      ; Clear R1 for using as a temporary holder
    AND R2, R2, #0      ; Clear R2 for using as a temporary holder
    LD R1, STACK_TOP    ; Load the address of STACK_TOP into R1 
    LD R2, STACK_START  ; Load the address of STACK_END into R2
    NOT R1, R1          ; Two's complementing R1
    ADD R1, R1, #1      ; 
    ADD R1, R2, R1      ; Comparing R2-R1
    ADD R1, R1, #-1     ; Compare with 2
    BRnp  PRINT_INVALID ; If there is less than 2 items in the stack, branch to PRINT_INVALID
    BRnzp PRINT_RESULT  ;

INV_EQ_ASC .FILL xFFC3  ; Inverse of Equal Sign + 1
SAVE_R0    .BLKW #1     ; Store R0 in New Memory Address 

CHECK_SPACE
    LD R0, SAVE_R0      ; Restore R0
    AND R1, R1, #0      ; Clear R1 the temporary register
    ADD R1, R1, #15     ; 
    ADD R1, R1, #15     ; 
    ADD R1, R1, #2      ; Add 32 to R1
    NOT R1, R1          ; Not(R1) 
    ADD R1, R1, #1      ; Add R1 by 1 to complete two's complementing
    ST R0, SAVE_R0      ; Store R0 Before Modifying
    ADD R0, R0, R1      ; ADD If Result 0 Is Space
    BRz PRINT_SPACE     ; Branch Back to READINPUT if Space
    LD R0, SAVE_R0      ; Restore R0
    BRnzp CHECK_NUMBER  ;

PRINT_SPACE
    LD R0, SAVE_R0 	    ; Load ASCII Value of R0 to Print
    OUT                 ; Print Space
    BRnzp READINPUT     ; Back to Reading User Input

CHECK_NUMBER
    LD R1, TC_ONE       ; load '1' into R1
    ST R0, SAVE_R0      ; Store R0 Before Modifying
    ADD R0,R1,R0        ; Branch is Result 0
    BRn OPERATOR_CHECK  ; check whether the number is less than the lower bound of '1'
    LD R0, SAVE_R0      ; load back input
    AND R1,R1,#0        ; clear R1
    LD R1, TC_NINE      ; LOAD '9' into R1
    ST R0, SAVE_R0      ; Save R0 before Modifying
    ADD R0,R1,R0        ; Branch when 
    BRp OPERATOR_CHECK  ; check whether the number is more than the higher bound
    LD R0, SAVE_R0      ; load back input
    OUT
    AND R1,R1,#0        ; clear R1
    LD R1, TC_ZERO      ;
    ADD R0,R0,R1        ; subtract '0'
    JSR PUSH            ;
    BRnzp READINPUT     ;

    
OPERATOR_CHECK          ; When an operator is found, branch to the operator's function.
                        ; Within each operator functions, we invoke JSR TWOITEMS to check items and pop them into R3 and R4.
    LD R0, SAVE_R0      ; load back the input
    LD R1, TC_PLUS      ; load 'plus' into R1
    ADD R0,R1,R0        ;
    BRz PLUS            ; if input is +, jump to check 2 items in stack
    AND R1,R1,#0        ; clear R1
    LD R0, SAVE_R0      ; load back the input
    LD R1, TC_MINUS     ; load 'plus' into R1
    ADD R0,R1,R0        ;
    BRz MIN             ; if input is -, jump to check 2 items in stack
    AND R1,R1,#0        ; clear R1
    LD R0, SAVE_R0      ; load back the input
    LD R1, TC_MULT      ; load 'mult' into R1
    ADD R0,R1,R0        ;
    BRz MUL             ; if input is *, jump to check 2 items in stack
    AND R1,R1,#0        ; clear R1
    LD R0, SAVE_R0      ; load back the input
    LD R1, TC_DIVIDE    ; load 'divide' into R1
    ADD R0,R1,R0        ;
    BRz DIV             ; if input is /, jump to check 2 items in stack
    AND R1,R1,#0        ; clear R1
    LD R0, SAVE_R0      ; load back the input
    LD R1, TC_POW       ; load 'power' into R1
    ADD R0,R1,R0        ;
    BRz EXP             ; if input is ^, jump to check 2 items in stack
    AND R1,R1,#0        ; clear R1
    BRnzp PRINT_INVALID

TWOITEMS ; CALL TWOITEMS in Each Operation
;work in progress
    ST R7, SAVE_R7      ; Store R7
    AND R1, R1, #0      ; Clear R1 for using as a temporary holder
    AND R2, R2, #0      ; Clear R2 for using as a temporary holder
    LD R1, STACK_TOP    ; Load the address of STACK_TOP into R1 
    LD R2, STACK_START  ; Load the address of STACK_END into R2
    NOT R1, R1          ; Two's complementing R1
    ADD R1, R1, #1      ; 
    ADD R1, R2, R1      ; Comparing R2-R1
    ADD R1, R1, #-2
    BRn  PRINT_INVALID  ; If there is less than 2 items in the stack, branch to PRINT_INVALID
    AND R3, R3, #0      ; Clear R3 for holding the value from POP
    AND R4, R4, #0      ; Clear R4 for holding the value from POP
    
    JSR POP             ; Invoke POP subroutine
    ADD R3, R3, R0      ; 
    JSR POP
    ADD R4, R4, R0      ;
    LD R7, SAVE_R7      ; Restore R7
    RET



PLUS
    LD R0, SAVE_R0 	    ;
    OUT                 ; Print out '+' sign
    JSR TWOITEMS        ; Jump to check if there are at least two items in the stack
    AND R0, R0, #0      ; Clear R0 for holding the result of addition
    ADD R0, R3, R4      ; Put R4+R3 into R0
    BRnzp OPERATOR_DONE ; Branch to OPERATOR_DONE to push the result into the stack
    
MIN	
    LD R0, SAVE_R0 	    ;
    OUT                 ; Print out the '-' subtraction sign
	JSR TWOITEMS        ; Jumo to check if there are at least two items in the stack
    AND R0, R0, #0      ; Clear R0 for Output
    NOT R3, R3          ; Not R4 to prepare R4-R3
    ADD R3, R3, #1      ; +1 cause we subtract
    ADD R0, R3, R4      ; R4-R3
    BRnzp OPERATOR_DONE
    
MUL	
	LD R0, SAVE_R0 	    ;
    OUT                 ; Print out the '*' multiplication sign
	JSR TWOITEMS        ; Jump to check if there are at least 2 items in the stack
    AND R0, R0, #0      ; Clear R0 for holding the result
MUL_LOOP
    ADD R4, R4, #0      ; R3xR4, R4 is the counter for how many times R3 adds itself
    BRz OPERATOR_DONE   ; When R4 is 0 we are done Adding
    ADD R0, R0, R3      ; R0 stores the result each time R4 -1
    ADD R4, R4, #-1     ; R4 Counter Decrement
    BRnzp MUL_LOOP

DIV	
	LD R0, SAVE_R0 	    ;
    OUT
    JSR TWOITEMS        ; Jump to check if there are at least 2 items in the stack
    AND R0, R0, #0      ; Clear R0 for quotient holder
    AND R1, R1, #0      ; Clear R1 for temporary register use
    ADD R1, R1, R3      ; Put R3 into R1
    NOT R1, R1          ; 
    ADD R1, R1, #1      ; Two's complementing R1 that is holding R3
 DIV_LOOP
    
    ADD R4, R4, R1      ; nth time division 
    BRn OPERATOR_DONE   ; If the numerator is smaller than the denominator, division is done, branch to OPERATOR_DONE.
    ADD R0, R0, #1      ; Increase the quotient by 1 when a division is successful
    BRnzp DIV_LOOP      ; Loop back 3 lines to continue dividing

OPERATOR_DONE
    JSR PUSH            ; Invoke PUSH subroutine
    BRnzp READINPUT     ; Branch back to read the next char in the input

EXP 
    LD R0, SAVE_R0 	    ;
    OUT                 ; Print out the '^' exponential sign
    JSR TWOITEMS        ; get base and exponent from the stack
    AND R0, R0, #0      ; clear R0
    ADD R5,R4,#0        ; use R5 to store the counter for exponent
    ADD R3,R3,#-1       ; -1 for loop purpose
    ST R5, SAVE_R5      ; save R5

POW_LOOP
    ADD R0,R0,R4        ; multiply
    ADD R5,R5,#-1       ; decrement R5
    BRz POW_NEXT        ; if R5 is zero, branch to POW_NEXT
    BRnzp POW_LOOP      ; Branch to POW_LOOP

POW_NEXT
    LD R5, SAVE_R5      ; load back the value of R5 for decrementation
    AND R4,R4,#0        ; clear R4
    ADD R4,R0,#0        ; put R0 into R4
    AND R0,R0,#0        ; clear R0
    ADD R3,R3,#-1       ; decrement R3
    BRz POW_DONE        ; if the counter R3 is 0, branch to POW_DONE
    BRnzp POW_LOOP      ; Branch to POW_LOOP

POW_DONE
    ADD R0,R4,#0        ; Put R4 into R0
    BRnzp OPERATOR_DONE ; Branch to OPERATOR_DONE


PRINT_INVALID           ; Since the input is invalid, clear all the registers
    AND R2, R2, #0      ; Clear R2
    AND R1, R1, #0      ; Clear R1
    AND R3, R3, #0      ; Clear R3
    ADD R1, R1, #15     ; Add R1 with 18 for printing 'Invalid'
    ADD R1, R1, #3
    LD R2, STR_ADR      ; Load the content at STR_ADR

LOOP 
    AND R0, R0, #0      ; Clear R0
    LDR R3, R2, #0      ; Load the content at address R2 into R3
    ADD R0, R0, R3      ; Add R0 with R3
    OUT                 ; Print out R0
    ADD R2, R2, #1      ; Add R2 by 1
    ADD R1, R1, #-1     ; Decrease R1 by 1
    BRzp LOOP           ; Branch to LOOP
    BRnzp DONE          ; Branch back to DONE


PRINT_RESULT   
    JSR POP             ; Jump to POP
    AND R5, R5, #0      ; Clear R5
    ADD R5, R5, R0      ; Add R5 with R0
    AND R3, R3, #0      ; Clear R3
    AND R2, R2, #0      ; Clear r0
    ADD R3, R0, R3      ; R3 = R0
    AND R1, R1, #0      ; Digit Counter is 4
	ADD R1, R1, #4      ; Add R1 with #4

CHECK_DIG	
	BRnz DONE
NEXT_DIG	
	AND R0, R0, #0      ; Digit Vaue Register
	ADD R2, R2, #4      ; Bit Counter is 4
CHECK_BIT
	ADD R2, R2, #0      ; Set Bit Counter for Branch
	BRnz BITS_DONE      ; Check if Less than 4 bits 
	ADD R0, R0, #0      ; Digital Shift Left
	ADD R3, R3, #0      ; Set R3 before Branch
	BRzp DIG_ZERO
DIG_ONE
	ADD R0, R0, R0      ; Shift Left Digit
	ADD R0, R0, #1      ; Put 1 in most right 
	ADD R3, R3, R3      ; Shift R3 to the next digit
	ADD R2, R2, #-1     ; Decrement Bit Counter
	BRnzp CHECK_BIT
DIG_ZERO   
	ADD R3, R3, R3      ; Shift R3 to the next digit
	ADD R0, R0, R0      ; Shift Left Digit
	ADD R2, R2, #-1     ; Decrement Bit Counter
	BRnzp CHECK_BIT
BITS_DONE 
	ADD R0, R0, #-9     ; Starts Converting to ASCII Value
	BRnz ASCII_NUM      ; Branch to ASCII_NUM
ASCII_LETTER	
	ADD R0, R0, #9      ; Add back #9 to R0
	ADD R0, R0, #15     ; Add 'A' - 10 (55)
	ADD R0, R0, #15     ; 
	ADD R0, R0, #15     ;	
	ADD R0, R0, #10     ; Add R0 by 10
	OUT                 ; Print R0
	ADD R1, R1, #-1     ; Decrease R1 by 1
	BRnzp CHECK_DIG     ; Branch to CHECK_DIG
ASCII_NUM
	ADD R0, R0, #9      ; Restore R0 Value
	ADD R0, R0, #15     ; Add '0' (48)
	ADD R0, R0, #15     ;
	ADD R0, R0, #15     ;
	ADD R0, R0, #3      ; Add R0 by 3
	OUT                 ; Print R0
	ADD R1, R1, #-1     ; Decrease R1 by 1
	BRnzp CHECK_DIG     ; Branch to CHECK_DIG

PUSH	
	ST R3, PUSH_SaveR3	; save R3
	ST R4, PUSH_SaveR4	; save R4
	AND R5, R5, #0		; Clear R5
	LD R3, STACK_END	; Load the address of STACK_END into R3
	LD R4, STACK_TOP	; Load the address of STACK_TOP into R4
	ADD R3, R3, #-1		; Decrease R3 by 1
	NOT R3, R3		    ; NOT(R3)
	ADD R3, R3, #1		; Add R3 by 1
	ADD R3, R3, R4		; Add R3 with R4
	BRz OVERFLOW		; stack is full
	STR R0, R4, #0		; no overflow, store value in the stack
	ADD R4, R4, #-1		; move top of the stack
	ST R4, STACK_TOP	; store top of stack pointer
	BRnzp DONE_PUSH		; Branch to DONE_PUSH
OVERFLOW
	ADD R5, R5, #1		; Add R5 by 1
DONE_PUSH
	LD R3, PUSH_SaveR3	; Restore R3
	LD R4, PUSH_SaveR4	; Restore R4
	RET                 ; back to the pc where it came from


PUSH_SaveR3	.BLKW #1	; Initialize a holder for R3
PUSH_SaveR4	.BLKW #1	; Initialize a holder for R4


POP	
	ST R3, POP_SaveR3	; save R3
	ST R4, POP_SaveR4	; save R3
	AND R5, R5, #0		; clear R5
	LD R3, STACK_START	; R3 is Stack Start Memory
	LD R4, STACK_TOP	; Load R4 From Stack Top Pointer
	NOT R3, R3		    ; 2's complement 
	ADD R3, R3, #1		; ADD R3 by 1
	ADD R3, R3, R4		; ADD R4 - R3 = 0 means underflow
	BRz UNDERFLOW		; Branch to UNDERFLOW
	ADD R4, R4, #1		; Add R4 by 1
	LDR R0, R4, #0		; Load the content at R4 into R0
	ST R4, STACK_TOP	; Store R4 to STACK_TOP
	BRnzp DONE_POP		; Branch to DONE_POP
UNDERFLOW
	ADD R5, R5, #1		; Increase R5 by 1
DONE_POP
	LD R3, POP_SaveR3	; Restore R3
	LD R4, POP_SaveR4	; Restore R4
	RET


POP_SaveR3	.BLKW #1	; a holder for R3
POP_SaveR4	.BLKW #1	; a holder for R4
STACK_END	.FILL x3FF0	; STACK_END address
STACK_START	.FILL x4000	; STACK_START address
STACK_TOP	.FILL x4000	; STACK_TOP address


DONE            HALT
STR_ADR        .FILL STRING 
STRING         .STRINGZ "Invalid Expression"    ; STRING label for "Invalid Expression"

SAVE_R7        .BLKW #1      ; a saver for R7

TC_ZERO        .FILL xFFD0 ;
TC_ONE         .FILL xFFCF ; zero +1 for invert purposes 
TC_NINE        .FILL xFFC7 ; nine +1 for invert purposes

TC_PLUS        .FILL xFFD5 ; 2's comp '+' xFFD5
TC_MINUS       .FILL xFFD3 ; 2's comp '-' xFFD3
TC_MULT        .FILL xFFD6 ; 2's comp '*' xFFD6
TC_DIVIDE      .FILL xFFD1 ; 2's comp '/' xFFD1
TC_POW         .FILL xFFA2 ; 2's comp '^' xFFA2

THIRTY_TWO     .FILL x0020 ; ascii for 'space'

SAVE_R5        .BLKW #1    ; save the value of R5

.END

