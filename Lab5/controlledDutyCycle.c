#include <msp430g2553.h>
void main( void )
{
WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer. BCSCTL1=CALBC1_1MHZ;
DCOCTL=CALDCO_1MHZ;//Set the DCO clock frequency as 1MHz
BCSCTL2 |= DIVS_3;
P1DIR |= BIT6; //Set P1.6 (Green LED) as an output
P1SEL |= BIT6; //Set The Green LED PWM
TA0CCR0 = (31250 -1); // Set the PWM period 2 seconds
TA0CCR1 = 6250; // Set duty cycle 20% (31250/5)
TA0CCTL1 = OUTMOD_7; // Set the output mode as Reset / Set
TA0CTL = (TASSEL_2 | ID_3 | MC_1 | TACLR | TAIE); /* Set the TIMER_A control*/
//to SMCLK, divider 1, count(up) mode, clear, interrupt enabled
_BIS_SR( GIE ); // Enable global interrupts
while( 1 ); //The while loop which is endless
}
// Timer0 A1 interrupt service routine
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR( void )
{
static int counter = 0; // The counter of cycle
TA0CTL &= ~TAIFG; // Interrupt flag is cleared
if( ++counter >=5 ) // 10sec
{
TA0CCR1 += 6250; // Adding 20% in existing value
if( TA0CCR1 >= 37500 ) // Reaching 100% duty cycle
{
TA0CCR1 = 6250; //Back to %20
}
counter=0;
}
}
