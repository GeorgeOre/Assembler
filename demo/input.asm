; Fibonacci Test Code

; Define the configuration bits
;    list        p=16F877A THIS IS A MICROCHIP FEATURE AND WILL NOT BE INCLUDED
    .include     "demo/p16f877a.inc"

; Configuration bits settings
;    __config    _CP_OFF & _WDT_OFF & _BODEN_OFF & _PWRTE_ON & _HS_OSC & _LVP_OFF

; Define constants
    cBLOCK       .equ 20h         ; Start of general-purpose RAM

; Define variables
    cFIB_ARRAY   .equ cBLOCK      ; Fibonacci array starting address
    cCOUNTER     .equ cBLOCK + 10 ; Loop counter
    cTEMP1       .equ cBLOCK + 11 ; Temporary storage
    cTEMP2       .equ cBLOCK + 12 ; Temporary storage

; Main program
     .org 0x00
     goto START         ;ACTUAL RUNNING CODE*********************************

; Interrupt vector
     .org 0x04
     retfie         ;ACTUAL RUNNING CODE*********************************

; Program start
START:
    ; Initialize the first two Fibonacci numbers
     clrf cFIB_ARRAY             ; Fibonacci[0] = 0         ;ACTUAL RUNNING CODE*********************************
     movlw 1         ;ACTUAL RUNNING CODE*********************************
     movwf cFIB_ARRAY + 1        ; Fibonacci[1] = 1         ;ACTUAL RUNNING CODE*********************************

    ; Initialize loop counter
     movlw 8         ;ACTUAL RUNNING CODE*********************************
     movwf cCOUNTER              ; Loop counter = 8 (for Fibonacci[2] to Fibonacci[9])         ;ACTUAL RUNNING CODE*********************************

COMPUTE_FIB:
    ; Load Fibonacci[n-1] into cTEMP1

;GEORGE ADDED A DEF FOR W FOR TESTING PURPOSES
;     W     .EQU     0

     movf cFIB_ARRAY + 1, W         ;ACTUAL RUNNING CODE*********************************
     movwf cTEMP1         ;ACTUAL RUNNING CODE*********************************

    ; Load Fibonacci[n-2] into cTEMP2
     movf cFIB_ARRAY, W         ;ACTUAL RUNNING CODE*********************************
     movwf cTEMP2         ;ACTUAL RUNNING CODE*********************************

    ; Calculate Fibonacci[n] = Fibonacci[n-1] + Fibonacci[n-2]
     addwf cTEMP2, F         ;ACTUAL RUNNING CODE*********************************
     movf cTEMP2, W         ;ACTUAL RUNNING CODE*********************************
     movwf cFIB_ARRAY + 2         ;ACTUAL RUNNING CODE*********************************

    ; Shift the array for the next iteration
     movf cFIB_ARRAY + 1, W         ;ACTUAL RUNNING CODE*********************************
     movwf cFIB_ARRAY         ;ACTUAL RUNNING CODE*********************************
     movf cFIB_ARRAY + 2, W         ;ACTUAL RUNNING CODE*********************************
     movwf cFIB_ARRAY + 1         ;ACTUAL RUNNING CODE*********************************

    ; Decrement the loop counter
     decf cCOUNTER, F         ;ACTUAL RUNNING CODE*********************************
     btfss STATUS, Z             ; If counter is zero, exit loop         ;ACTUAL RUNNING CODE*********************************
     goto COMPUTE_FIB         ;ACTUAL RUNNING CODE*********************************

    ; End of program
;     goto $ DO LATER ALSO

;     end DO LATER

; FEATURES TO BE IMPLEMENTED
;   - memory access
;   - .org
;   - configs
;   - end and goto $

;2804
;0009
;0120
;3001
;00A1
;3008
;00AA
;072C
;082C
;00A2
;0821
;00A0
;0822
;032A
;1C03
;280E
;
;
;
;
;
;
;
