#include <msp430g2553.h>
void main( void )
{
WDTCTL = (WDTPW | WDTHOLD); // Stop watchdog timer.
BCSCTL1=CALBC1_1MHZ; //Set the DCO clock frequency as 1MHz
DCOCTL=CALDCO_1MHZ;
BCSCTL2 |= DIVS_3; // period=8/1MHz
P1DIR |= BIT6; //Set P1.6 (Green LED) as an output
P1SEL |= BIT6; //Set The Green LED PWM
TA0CCR0 = 31250; //Set The PWM period to 2s(31250*8*8us=2s)
TA0CCR1 = 7813; //Set Pulse Width 0.5s(((31250/4)*8*8us)=0.5s)
TA0CCTL1 = OUTMOD_7; //Set the output mode as Reset/Set Mode.
TA0CTL = (TASSEL_2 + MC_1 + ID_3); //Set the TIMER_A control to //SMCLK, 1MHz and count (up) mode.
while(1); //The while loop which is endless
}
