#include <msp430.h>
void updateLeds(int remainder);
unsigned int delay =0;
unsigned int remainder = 8;
unsigned int a = 0; // if a value is 0 counts up ,otherwise down.
void main(void)
{
WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
P1OUT &= 0x00; // Initial conditions are zero.
P1DIR &= 0x00;
P1DIR |= 0x07;
P1REN |= BIT5;
P1OUT |= BIT5;
P1IFG &= ~BIT5;
P1IES |= BIT5;
BCSCTL1 = CALBC1_1MHZ;//Set internal clock to 1MHz
DCOCTL = CALDCO_1MHZ;
TACCR0 = 50000;//Count up to 50000, then send interrupt signal.
TACCTL0 |= CCIE;//Timer interrupt enabled.
TACTL = TASSEL_2 + MC_1 +TAIE; /* Timer A control set to SMCLK, +TACLR , out up mode and interrupt enable */
P1IE |= BIT5; // P1.5 Interrupt Enabled
_bis_SR_register(LPM1_bits+GIE); //LPM1 selected to keep clock sources on...
_no_operation();
while(1); // waiting here during interrupts on.
}
#pragma vector=PORT1_VECTOR // Interrupt for controlling switch p1.5.
interrupt void Port_1(void) // This interrupt is active when any kind of switch operation has been done.
{
if(a==0) // for the first case , we change the remainder mode from upward to downward.
{
a=1;
}
else // in this case , we will have upward mode.
{
a=0;
}
P1IFG &= ~BIT5; // Flag cleared
}
#pragma vector=TIMER0_A0_VECTOR //Timer
interrupt void Timer_A(void)
{
if(delay==100) /*5 second delay provided , counted by number of interrupts ,100*50ms= 5 seconds */
{
delay=0;
if(a==0)
{
remainder++; // upward counting
}
else
{
remainder--; // downward counting
}
updateLeds(remainder); //Calling the function that controls LEDs.
}
delay++;
TA0CTL &= ~TAIFG; //TimerA Interrupt Flag cleared.
}
void updateLeds(int remainder)
{
if(remainder==0)
{
remainder=8;
}
switch(remainder % 8)
{
case 0:
P1OUT = P1OUT & ~BIT0; //When button is not pressed both LEDs will be OFF.
P1OUT = P1OUT & ~BIT1;
P1OUT = P1OUT & ~BIT2;
break; case 1:
P1OUT = P1OUT | BIT0; // Only First LED P1.0 is ON.
P1OUT = P1OUT & ~BIT1;
P1OUT = P1OUT & ~BIT2;
break; case 2:
P1OUT = P1OUT & ~BIT0; // Only Second LED P1.1 is ON.
P1OUT = P1OUT | BIT1;
P1OUT = P1OUT & ~BIT2;
break;
case 3:
P1OUT = P1OUT | BIT0; // First and Second LED P1.0-P1.1 is ON.
P1OUT = P1OUT | BIT1;
P1OUT = P1OUT & ~BIT2;
break;
case 4:
P1OUT = P1OUT & ~BIT0; // Only Third LED P1.2 is ON.
P1OUT = P1OUT & ~BIT1;
P1OUT = P1OUT | BIT2;
break;
case 5:
P1OUT = P1OUT | BIT0; // First and Third LED P1.0-P1.2 is ON.
P1OUT = P1OUT & ~BIT1;
P1OUT = P1OUT | BIT2;
break;
case 6:
P1OUT = P1OUT & ~BIT0; // Second and Third LED P1.1-P1.2 is ON.
P1OUT = P1OUT | BIT1;
P1OUT = P1OUT | BIT2;
break; case 7:
P1OUT = P1OUT | BIT0; // All the LEDs are ON.
P1OUT = P1OUT | BIT1;
P1OUT = P1OUT | BIT2; // Set all bits to 1
break;
}
}
