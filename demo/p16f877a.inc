;***************************************************************************
; p16f877a.inc
; Processor: PIC16F877A
; Assembler: USA
; Assembler Syntax: MPASM
; 
; This file includes the special function register and bit definitions
; for the PIC16F877A microcontroller.
;***************************************************************************

; Register Definitions

INDF        equ     0x00
TMR0        equ     0x01
PCL         equ     0x02
STATUS      equ     0x03
FSR         equ     0x04
PORTA       equ     0x05
PORTB       equ     0x06
PORTC       equ     0x07
PORTD       equ     0x08
PORTE       equ     0x09
PCLATH      equ     0x0A
INTCON      equ     0x0B
PIR1        equ     0x0C
PIR2        equ     0x0D
TMR1L       equ     0x0E
TMR1H       equ     0x0F
T1CON       equ     0x10
TMR2        equ     0x11
T2CON       equ     0x12
SSPBUF      equ     0x13
SSPCON      equ     0x14
CCPR1L      equ     0x15
CCPR1H      equ     0x16
CCP1CON     equ     0x17
RCSTA       equ     0x18
TXREG       equ     0x19
RCREG       equ     0x1A
CCPR2L      equ     0x1B
CCPR2H      equ     0x1C
CCP2CON     equ     0x1D
ADRESH      equ     0x1E
ADCON0      equ     0x1F
OPTION_REG  equ     0x81
TRISA       equ     0x85
TRISB       equ     0x86
TRISC       equ     0x87
TRISD       equ     0x88
TRISE       equ     0x89
PIE1        equ     0x8C
PIE2        equ     0x8D
PCON        equ     0x8E
SSPCON2     equ     0x91
PR2         equ     0x92
SSPADD      equ     0x93
SSPSTAT     equ     0x94
TXSTA       equ     0x98
SPBRG       equ     0x99
CMCON       equ     0x9C
CVRCON      equ     0x9D
ADRESL      equ     0x9E
ADCON1      equ     0x9F
EEDATA      equ     0x10C
EEADR       equ     0x10D
EEDATH      equ     0x10E
EEADRH      equ     0x10F

; Bit Definitions

; STATUS Register
IRP         equ     7
RP1         equ     6
RP0         equ     5
TO          equ     4
PD          equ     3
Z           equ     2
DC          equ     1
C           equ     0

; INTCON Register
GIE         equ     7
PEIE        equ     6
TMR0IE      equ     5
INTE        equ     4
RBIE        equ     3
TMR0IF      equ     2
INTF        equ     1
RBIF        equ     0

; OPTION_REG Bits
RBPU        equ     7
INTEDG      equ     6
T0CS        equ     5
T0SE        equ     4
PSA         equ     3
PS2         equ     2
PS1         equ     1
PS0         equ     0

; TRIS Registers
TRISA       equ     0x85
TRISB       equ     0x86
TRISC       equ     0x87
TRISD       equ     0x88
TRISE       equ     0x89

; General-purpose register definitions (add more if needed)
GPR0        equ     0x20   ; General-purpose register 0
GPR1        equ     0x21   ; General-purpose register 1
GPR2        equ     0x22   ; General-purpose register 2
GPR3        equ     0x23   ; General-purpose register 3
GPR4        equ     0x24   ; General-purpose register 4
GPR5        equ     0x25   ; General-purpose register 5
GPR6        equ     0x26   ; General-purpose register 6
GPR7        equ     0x27   ; General-purpose register 7

;***************************************************************************
; End of file
;***************************************************************************