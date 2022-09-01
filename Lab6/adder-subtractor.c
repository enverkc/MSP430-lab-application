#include<msp430g2553.h>
#definecontrol BIT7 // Control pin
#define A0 BIT4 // LSB of A is taken P1.4
#define A1 BIT5 // MSB of A is taken P1.5
#define B0 BIT0 // LSB of B is taken P2.0
#define B1 BIT1 // MSB of B is taken P2.1
unsignedint A; // First number.
unsignedint B; // Second number.
void configWDT(void);
void configPins(void);
void main()
{
configWDT();
configPins();
while(1)
{
if(P1IN & A1) // MSB of A is 1
{
if(P1IN & A0) // LSB of A is 1
{
A &= 0x00;
A |= 0x03; //MSB and LSB are 1, A is 3.
}
else// LSB of A is 0
{
A &= 0x00; // Resetvalue of A
A |= 0x02; // MSB is 1 and LSB is 0, A is 2.
}
}
else// MSB of A is 0.
{
if(P1IN & A0) // LSB of A is 1.
{
A &= 0x00; // Resetvalue of A
A |= 0x01; // MSB is 0 and LSB is 1, A is 1 .
}
else// LSB of A is 0.
{
A &= 0x00; // Resetvalue of A
A |= 0x00; // MSB and LSB are 0, A is 0.
}
} // Calculation of thenumber B
if(P2IN & B1) // MSB of B is 1
{
if(P2IN & B0) // LSB of B is 1
{
B &= 0x00; // Resetvalue of B
B |= 0x03; // MSB and LSB are 1, B is 3.
}
else// MSB of B is 0.
{
B &= 0x00; // Resetvalue of B
B |= 0x02; // MSB is 1 and LSB is 0 B is 2.
}
}
else//MSB of B is 0.
{
if(P2IN & B0) // LSB of B is 1.
{
B &= 0x00; // Resetvalue of B
B |= 0x01; // MSB is 0 and LSB is 1, B is 2.
}
else// LSB of B is 0.
{
B &= 0x00; // Resettingthevalue of B
B |=0x00; // MSB and LSB are 0, B is 0.
}
}
if(( P1IN &control)) // Control Switch is ON.
{
P1OUT&= 0x00; // Alloutputs of thefirst port havebeenreset.
P1OUT |= A+B; // Whencontrolswitch is ON designbehaves as 2-bit adder.
__delay_cycles(1000000);
6
}
else// Control Switch position is OFF.
{
if(A >= B)
{
P1OUT&= 0x00; // Alloutputs of thefirst port havebeenreset.
P1OUT |= A-B; // Whencontrolswitch is OFF designbehaves as 2-bit subtractor.
__delay_cycles(1000000);
}
else
{
P1OUT |= 0xFF; //Turnoffthe 7-Segment Display.
P1OUT&= ~BIT6; //turnoffGreen LED
__delay_cycles(1000000);
}
}
}
}
void configPins(void)
{
P1DIR |= BIT3+BIT2+BIT1+BIT0+BIT6; // Set P1.0, P1.1, P1.2, P1.3, P1.6,
P1REN |= control+A0+A1;
P1OUT |= control+A0+A1; // P1.0 , P1.1 outputs.
P2REN |= +B0+B1;
P2OUT |= +B0+B1; // P2.0 , P2.1 outputs.
}
void configWDT(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdogtimer
}
