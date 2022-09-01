#include <msp430.h>
#define MOTOR1 BIT1
#define MOTOR2 BIT2
#define PWM BIT6
unsigned int a=0; //Global initizilization
unsigned int direction=1; //Global initizilization
void configWDT(void)
{
WDTCTL = WDTPW | WDTHOLD; // Stop WDT
}
void configClock(void)
{
DCOCTL = CALDCO_16MHZ; // Set DCO to 16MHz
BCSCTL1 = CALBC1_16MHZ; // Frequency set to 16MHZ
}
void configADC(void)
{
ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
ADC10CTL1 = INCH_0; // Analog read from P1.0
ADC10AE0 |= BIT0; // Analog value read from P1.0
}
void configTimer(void)
{
TA0CTL = TASSEL_2 + MC_1 + TAIE; // SMCLK/8, upmode
TA0CCR0=1024; // PWM Period
TA0CCR1 = 1; // TACCR1 PWM Duty Cycle
TA0CCTL1 |= OUTMOD_7; // TACCR1 reset/set
}
void main(void)
{
configWDT(); //Calling configWDT function
configClock(); //Calling configClock function
configADC(); //Calling configADC function
configTimer(); //Calling configTimer function
P1OUT &= 0x00; // P1OUT register cleared
P1DIR &= 0x00; // P1DIR register cleared
P1DIR |= MOTOR1 +PWM + MOTOR2; // Set P1.1, P1.2 P1.6 to output direction
P1SEL |= PWM; // Select PWM functioning for P1.6.
P1REN |= BIT3; // Enable internal pull-up/down resistors
P1OUT |= MOTOR1+BIT3; // P1.3 Pull up configuration set.P1.1 Output is High.
P1OUT &= ~MOTOR2; // P1.5 Output is LOW.
P1IFG &= ~BIT3; // P1.3 IFG cleared
P1IES |= BIT3; // P1.3 Hi/lo edge
P1IE |= BIT3; // P1.3 Interrupt is enabled
__bis_SR_register(LPM0_bits+GIE); // LPM0, ADC10_ISR will force exit, Global Interrupt Enabled
while(1) // Infinite Loop
;
}
#pragma vector=PORT1_VECTOR // P1.3 Switch Interrupt
__interrupt void Port_1(void)
{
__delay_cycles(500);
a=1;
if(direction==1)
{
direction=0;
}
else
{
direction=1;
}
__delay_cycles(500);
if(a==1) // Direction Control
{
a=0;
TA0CCR1=0; // PWM is TA0CCR1/TA0CCR0 so PWM is set to 0 for new direction
__delay_cycles(500);
if(direction==1) // Direction control
{
P1OUT |= MOTOR1;
P1OUT &= ~MOTOR2;
}
else
{
P1OUT |= MOTOR2;
P1OUT &= ~MOTOR1;
}
}
P1IFG &=~BIT3; // Flag Cleared
}
#pragma vector= TIMER0_A1_VECTOR // Watchdog Timer ISR
__interrupt void timer(void)
{
ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
TA0CCR1 = ADC10MEM;//storing ADC data at ADC10MEM register
TA0CTL &= ~TAIFG;
}
