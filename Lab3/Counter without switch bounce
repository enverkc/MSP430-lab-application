#include<msp430.h>
volatile int remainder=0;
int main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
P1DIR |= 0x07; // Set P1.0, P1.1, and P1.2 tooutputdirection
P1REN |= 0x08; // Enable P1.5 internal resistance
P1OUT |= 0x10; // Set P1.5 as pull-up resistance mode
P1IES |= BIT5; // P1.5 RisingEdge
P1IFG &= ~BIT5; // P1.5 IFG Cleared
P1IE |= BIT5; // P1.5 InterruptEnabled
_bis_SR_register(LPM4_bits + GIE); // Enter LPM4 w/ interrupt
_no_operation(); // Fordebugger
}
void update_led(void){
if (remainder==0){//ifremainder = 0
P1OUT = P1OUT & ~BIT0; //
P1OUT = P1OUT & ~BIT1;
P1OUT = P1OUT & ~BIT2;
__delay_cycles(500000);
}
else if (remainder==1){//ifremainder = 1
P1OUT = P1OUT | BIT0; //Turn of both
P1OUT = P1OUT & ~BIT1;
P1OUT = P1OUT & ~BIT2;
__delay_cycles(500000);
}
else if (remainder==2){//ifremainder = 2
P1OUT = P1OUT | BIT1;
P1OUT = P1OUT & ~BIT0;
P1OUT = P1OUT & ~BIT2;
__delay_cycles(500000);
}
else if (remainder==3){ //ifremainder = 3
P1OUT = P1OUT | BIT0;
P1OUT = P1OUT | BIT1;
P1OUT = P1OUT & ~BIT2;
__delay_cycles(500000);
}
else if (remainder==4){//ifremainder = 4
P1OUT = P1OUT & ~ BIT0;
P1OUT = P1OUT & ~ BIT1;
P1OUT = P1OUT | BIT2;
__delay_cycles(500000);
}
else if (remainder==5){//ifremainder = 5
P1OUT = P1OUT | BIT0;
P1OUT = P1OUT & ~BIT1;
P1OUT = P1OUT | BIT2;
__delay_cycles(500000);
}
else if (remainder==6){
P1OUT = P1OUT & ~ BIT0; //ifremainder = 6
P1OUT = P1OUT | BIT1;
P1OUT = P1OUT | BIT2;
__delay_cycles(500000);}
else if (remainder==7){
P1OUT = P1OUT | BIT0; //ifremainder = 7, turn on all
P1OUT = P1OUT | BIT1;
P1OUT = P1OUT | BIT2;
__delay_cycles(500000);
}
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1 (void)
{
remainder++;
if(remainder == 8){
remainder = 0; //interrupt is activated.
}
update_led();
P1IFG &= ~BIT5; // P1.5 IFG Cleared
}
