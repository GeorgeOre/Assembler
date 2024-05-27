; Fibonacci Test Code

; Define the configuration bits
    list        p=16F877A 
    include     "p16f877a.inc"

; Configuration bits settings
    __config    _CP_OFF & _WDT_OFF & _BODEN_OFF & _PWRTE_ON & _HS_OSC & _LVP_OFF

; Define constants
    cBLOCK       equ 20h         ; Start of general-purpose RAM

; Define variables
    cFIB_ARRAY   equ cBLOCK      ; Fibonacci array starting address
    cCOUNTER     equ cBLOCK + 10 ; Loop counter
    cTEMP1       equ cBLOCK + 11 ; Temporary storage
    cTEMP2       equ cBLOCK + 12 ; Temporary storage

; Main program
    org 0x00
    goto START

; Interrupt vector
    org 0x04
    retfie

; Program start
START:
    ; Initialize the first two Fibonacci numbers
    clrf cFIB_ARRAY             ; Fibonacci[0] = 0
    movlw 1
    movwf cFIB_ARRAY + 1        ; Fibonacci[1] = 1

    ; Initialize loop counter
    movlw 8
    movwf cCOUNTER              ; Loop counter = 8 (for Fibonacci[2] to Fibonacci[9])

COMPUTE_FIB:
    ; Load Fibonacci[n-1] into cTEMP1
    movf cFIB_ARRAY + 1, W
    movwf cTEMP1

    ; Load Fibonacci[n-2] into cTEMP2
    movf cFIB_ARRAY, W
    movwf cTEMP2

    ; Calculate Fibonacci[n] = Fibonacci[n-1] + Fibonacci[n-2]
    addwf cTEMP2, F
    movf cTEMP2, W
    movwf cFIB_ARRAY + 2

    ; Shift the array for the next iteration
    movf cFIB_ARRAY + 1, W
    movwf cFIB_ARRAY
    movf cFIB_ARRAY + 2, W
    movwf cFIB_ARRAY + 1

    ; Decrement the loop counter
    decf cCOUNTER, F
    btfss STATUS, Z             ; If counter is zero, exit loop
    goto COMPUTE_FIB

    ; End of program
    goto $

    end


