#include<msp430.h>
int main ( void){
WDTCTL = WDTPW | WDTHOLD; // Stop watchdog t imer
P1DIR |= 0x40 ; // Set P1 . 6 to output d i r e c t i o n
P1REN |= 0x08 ;
P1OUT |= 0X08 ;
while (1){
if ( (P1IN & BIT3 ) ) { // I f but ton i s open (P1 .3 HIGH)
P1OUT = P1OUT & ~BIT6 ; // . . . turn it off.
}
else {
P1OUT = P1OUT | BIT6 ; // . . . turn on LED
volatile unsigned long i; // Volatile to prevent
i = 50000; // SW Delay
do i--;
while(i != 0); //or we can use __delay_cycles(1000000);
}
}
}
