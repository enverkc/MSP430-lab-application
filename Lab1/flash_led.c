#include<msp430.h>
int main ( void){
WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
P1DIR |= 0x40 ; // Set P1.6 to output direction
P1REN |= 0x08 ; // Set P1.3 to input direction
P1OUT |= 0X08 ; // Set P1.3 to pull-up congiguration
while (1){
if ( (P1IN & BIT3 ) ) { // I f button is open (P1 .3 HIGH)
P1OUT = P1OUT & ~BIT6 ; // . . . turn it off.
}
else {
P1OUT = P1OUT | BIT6 ; // . . . else turn on LED
}}}
