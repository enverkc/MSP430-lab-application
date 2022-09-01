#include <msp430.h>
#define GREENLED BIT6
void configWDT(void){
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
}
void configADC(void){
ADC10CTL0 = SREF_0+ ADC10SHT_2 + ADC10ON;/*VCC and Vss reference Voltage*/
ADC10CTL1 = INCH_3; //channel A5
ADC10AE0 = BIT3; //P1.3 ADC option selected
}
void configPins(void){
P1DIR |= GREENLED; // Set P1.6 to output direction
P1SEL |= GREENLED;
}
void configClock(void){
BCSCTL1 = CALBC1_16MHZ; // Set DCO to 16MHz
DCOCTL = CALDCO_16MHZ;
}
void configTimer(void){
TA0CTL = TASSEL_2 + MC_1 + TAIE;// SMCLK/8, upmode
TA0CCR0 = 1023;// PWM Period
TA0CCR1 = 1;// TACCR1 PWM Duty Cycle
TACCTL1 = OUTMOD_7;// TACCR1 reset/set
}
#pragma vector = TIMER0_A1_VECTOR;
interrupt void timer (void){
ADC10CTL0 |= ENC + ADC10SC;// Sampling and conversion start
TA0CCR1 = ADC10MEM;//storing ADC data at ADC10MEM register
}
int main(void)
{
configWDT();//Calling configWDT function
configClock();//Calling configClock function
configADC();//Calling configADC function
configPins();//Calling configPins function
configTimer();//Calling configTimer function
__bis_SR_register(CPUOFF + GIE);// LPM0, ADC10_ISR will force exit
while(1)
;
return 0;
}
