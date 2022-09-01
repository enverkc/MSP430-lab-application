#include <msp430.h>
int digit1;
int digit2;
int digit3;
int filt[30];
int int_temp;
void print_digit(int digit);//protype of print_digit function
int Average_filt(int temp);//protype of Avarage_filt function
void main(void){
WDTCTL = WDTPW|WDTHOLD; // Stop WDT
BCSCTL1 = CALBC1_16MHZ; //Set DCO to 16 MHz
DCOCTL = CALDCO_16MHZ;
/* Configure ADC Channel */
ADC10CTL1 = INCH_5 + ADC10DIV_3 ; // Channel 5, ADC10CLK/4
ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON; //Vcc & Vss as reference
ADC10AE0 |= BIT5; //P1.5 ADC option
P1DIR |= BIT0+BIT1+BIT2+BIT3+BIT4+BIT6+BIT7; /*Set all pin of port 1 to output except P1.5*/
P2DIR |= BIT0+BIT1+BIT2+BIT3;/*Set all pin of port 1 to output except P1.5*/
P1SEL |= BIT5; // ADC IN
P1OUT |= (BIT0+BIT1+BIT2+BIT3+BIT4+BIT6+BIT7);/*Set all pin of port 1 to logical high except P1.5*/
P2OUT |= (BIT1+BIT2+BIT3);/*Set all pin of port 1 to logical high except P1.5*/
while(1){
__delay_cycles(1000); // Wait for ADC Ref to settle
ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
int_temp=10*((4*ADC10MEM*100)/1023);/*numeric calculation for converting ADC value to celcius */
int_temp=Average_filt(int_temp);/* Calling Avarage_filt function and writing the avarage value to int_temp ineger */
digit1 = (int_temp)%10;//Finding third digit of celcius vaue.
digit2 = (int_temp/10)%10;//Finfing second digit of celcius value.
digit3 = (int_temp/100)%10;//Finfing first digit of celcius value.
P2OUT &= ~(BIT0+BIT1+BIT2+BIT3);//Resetting port2 pin
print_digit(digit3);/*Calling prit_display function and displaying digit 1 */
P2OUT |= (BIT0+BIT1);/*Controlling digit input of display.And turn off the DP(dot) */
__delay_cycles(160000); //10ms delay
P2OUT &= ~(BIT0+BIT1+BIT2+BIT3);
print_digit(digit2);/Calling prit_display function and displaying

digit 2*/
P2OUT |= (BIT2);/*Controlling digit input of display.And turn on the DP(dot) */
__delay_cycles(160000); //10ms delay
P2OUT &= ~(BIT0+BIT1+BIT2+BIT3);
print_digit(digit1);/*Calling prit_display function and displaying digit 3*/
P2OUT |= (BIT0+BIT3);/*Controlling digit input of display.And turn off the DP(dot)*/
__delay_cycles(128000); //8ms delay
}
}
void print_digit(int digit){
/*This fuction uses for display the wanted number on 7 segment display.All pins connected to different LED of seven segment display*/
switch(digit){
case 0:{
P1OUT &= ~ (BIT0+BIT1+BIT2+BIT3+BIT4+BIT6);
P1OUT |= (BIT7);
break;
}
case 1:{
P1OUT &= ~ (BIT1+BIT2);
P1OUT |= (BIT0+BIT3+BIT4+BIT6+BIT7);
break;
}
case 2:{
P1OUT &= ~(BIT0+BIT1+BIT3+BIT4+BIT7);
P1OUT |= (BIT2+BIT6);
break;
}
case 3:{
P1OUT &= ~(BIT0+BIT1+BIT2+BIT3+BIT7);
P1OUT |= (BIT4+BIT6);
break;
}
case 4:{
P1OUT &= ~(BIT1+BIT2+BIT6+BIT7);
P1OUT |= (BIT0+BIT3+BIT4);
break;
}
case 5:{
P1OUT &= ~(BIT0+BIT2+BIT3+BIT6+BIT7);
P1OUT |= (BIT1+BIT4);
break;
}
case 6:{
P1OUT &= ~(BIT0+BIT2+BIT3+BIT4+BIT6+BIT7);
P1OUT |= (BIT1);
break;
}
case 7:{
P1OUT &= ~(BIT0+BIT1+BIT2);
P1OUT |= (BIT3+BIT4+BIT6+BIT7);
break;
}
case 8:{
P1OUT &= ~(BIT0+BIT1+BIT2+BIT3+BIT4+BIT6+BIT7);
break;
}
case 9:{
P1OUT &= ~(BIT0+BIT1+BIT2+BIT3+BIT6+BIT7);
P1OUT |= (BIT4);
break;
}
default:{
break;
}
}//switch-case
}//print-digit-
int Average_filt(int temp){
/*This function calculate the avarege value of temperature.It samples 30 times per seconds.*/
/*It sum all value and divided by 30.For finding the accuate value of temperature*/
int k;
int filt_sum=0;
for(k=0;k<29;k++){
filt[k]=filt[k+1];
}
filt[29]=temp;
filt_sum=0;
for(k=0;k<=29;k++){
filt_sum+=filt[k];
}
temp=filt_sum/30;
return temp;
}
