#include <msp430g2553.h>
#define redLED BIT0
#define greenLED BIT6
#define push BIT3
void configWDT(void);
void configPins(void);
void updateLeds(int count);
int main(void)
{
configWDT(); // watchdog timer stopped.
configPins(); // pins are configured.
int counter= 0;
while(1){
if ((P1IN & push)) {
}
else{
counter= counter + 1;
updateLeds(counter);
__delay_cycles(300000);
}
}
return 0;
}
void configWDT(void){
WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer (prevening reset.)
}
void configPins(void){
P1DIR |= redLED+ greenLED; // leds configured to output direction. 0100 0001
P1REN |= push; // Pull up/Pull down resistors were enabled.
P1OUT |= push; // Pull up configuration is chosen.
}
void updateLeds(int count){
int reminder= count % 4;
if(reminder == 0)
{
P1OUT &= ~greenLED ;
P1OUT &= ~redLED ;
}
else if(reminder == 1){
P1OUT &= ~redLED ;
P1OUT |= greenLED;
}
else if(reminder == 2){
P1OUT |= redLED;
P1OUT &= ~greenLED ;
}else{
P1OUT |= redLED;
P1OUT |= greenLED;
}
}
