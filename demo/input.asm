; Fibonacci Test Code

; Define the configuration bits
;    list        p=16F877A THIS IS A MICROCHIP FEATURE AND WILL NOT BE INCLUDED
;    include     "p16f877a.inc" TEST THIS LATER

; Configuration bits settings
;    __config    _CP_OFF & _WDT_OFF & _BODEN_OFF & _PWRTE_ON & _HS_OSC & _LVP_OFF
; MAYBE DO THIS LATER

; Define constants

; Define variables

; Main program
;    .org 0x00 SOON
;    goto START ALSO LATER

; Interrupt vector
;    .org 0x04
;    retfie THIS MIGHT BE WAY LATER

; Program start
;START:
    ; Initialize the first two Fibonacci numbers
;    clrf cFIB_ARRAY             ; Fibonacci[0] = 0
    movlw 1
;    movwf cFIB_ARRAY + 1        ; Fibonacci[1] = 1

    ; Initialize loop counter
    movlw 8
;    movwf cCOUNTER              ; Loop counter = 8 (for Fibonacci[2] to Fibonacci[9])

    ; End of program
    ;goto $ DO LATER ALSO

    ;end DO LATER
