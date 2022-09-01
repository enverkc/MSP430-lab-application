#include <msp430.h>
#include <math.h>
#include <string.h>
unsigned int y=0;
volatile char x[]={"hello world"};//Example data
unsigned int i=0;
unsigned int a=0;
unsigned int b=0;
unsigned int count=0; unsigned int lenght=0;
void main(void)
{
WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
P1DIR |= 0XFF;
P2DIR |=0X01;
BCSCTL1 = CALBC1_12MHZ;//Set internal clock to 12MHz
DCOCTL = CALDCO_12MHZ;
TACCR0 = 400;//Count up to 400, then send interrupt signal.
TACCTL0 |= CCIE;//Timer interrupt enabled.
  TACTL = TASSEL_2 + MC_1 +TAIE; /* Timer A control set to SMCLK,
//+TACLR , out up mode and interrupt enable */
_bis_SR_register(LPM1_bits+GIE); //LPM1 selected to keep clock sources on...
_no_operation();
while(1); // waiting here during interrupts on.
}
#pragma vector=TIMER0_A0_VECTOR //Timer
interrupt void Timer_A(void)
{
if(y==0) //sending clock signal to external device
{
y=1;
P2OUT |=0x01; //P1.0 pin will be logical high
}
else
{
y=0;
P2OUT &= ~0x01; //P1.0 pin will be logical low so we generate a period which frequency is equal to 15000 Hz.This clock signal is STROBE
} while (x[lenght] != '\0')
{ lenght++;
} if (count<lenght+2)
{
a=(int)x[i]%16;//We convert a ASCII character to hex number.
b=((int)x[i]-a)/16;
if (a==0)
{
P1OUT &= ~0x0F;
}
else if (a==1)
{
P1OUT &= ~0x0E;
P1OUT |= 0x01;
}
else if (a==2)
{
P1OUT &= ~0x0D;
P1OUT |= 0x02;
}
else if(a==3)
{
P1OUT &= ~0x0C;
P1OUT |= 0x03;
} else if(a==4)
{
P1OUT &= ~0x0B;
P1OUT |= 0x04;
}
else if(a==5)
{
P1OUT &= ~0x0A;
  P1OUT |= 0x05;
}
else if(a==6)
{
P1OUT &= ~0x09;
P1OUT |= 0x06;
}
else if(a==7)
{
P1OUT &= ~0x08;
P1OUT |= 0x07;
}
else if(a==8)
{
P1OUT &= ~0x07;
P1OUT |= 0x08;
}
else if(a==9)
{
P1OUT &= ~0x06;
P1OUT |= 0x09;
}
else if(a==10)
{
P1OUT &= ~0x05;
P1OUT |= 0x0A;
}
else if(a==11)
{
P1OUT &= ~0x04;
P1OUT |= 0x0B;
}
else if(a==12)
{
P1OUT &= ~0x03;
P1OUT |= 0x0C;
}
else if(a==13)
{
P1OUT &= ~0x02;
P1OUT |= 0x0D;
}
else if(a==14)
{
P1OUT &= ~0x01;
P1OUT |= 0x0E;
}
else if(a==15)
{
P1OUT |= 0x0F;
}
if (b==0)
{
P1OUT &= ~0xF0;
}
  else if (b==1)
{
P1OUT &= ~0xE0;
P1OUT |= 0x10;
}
else if (b==2)
{
P1OUT &= ~0xD0;
P1OUT |= 0x20;
}
else if(b==3)
{
P1OUT &= ~0xC0;
P1OUT |= 0x30;
} else if(b==4)
{
P1OUT &= ~0xB0;
P1OUT |= 0x40;
}
else if(b==5)
{
P1OUT &= ~0xA0;
P1OUT |= 0x50;
}
else if(b==6)
{
P1OUT &= ~0x90;
P1OUT |= 0x60;
}
else if(b==7)
{
P1OUT &= ~0x80;
P1OUT |= 0x7;
}
else if(b==8)
{
P1OUT &= ~0x70;
P1OUT |= 0x80;
}
else if(b==9)
{
P1OUT &= ~0x60;
P1OUT |= 0x90;
}
else if(b==10)
{
P1OUT &= ~0x50;
P1OUT |= 0xA0;
}
else if(b==11)
{
P1OUT &= ~0x40;
P1OUT |= 0xB0;
}
else if(b==12)
{
P1OUT &= ~0x30;
P1OUT |= 0xC0;
}
else if(b==13)
{
P1OUT &= ~0x20;
P1OUT |= 0xD0;
}
else if(b==14)
{
P1OUT &= ~0x10;
P1OUT |= 0xE0;
}
else if(b==15)
{
P1OUT |= 0xF0;
}
count++;
i++;
}
else
{
a=0;
b=0;
P1OUT &=0X00;
P1DIR &=0X00;
}
TA0CTL &= ~TAIFG; //TimerA Interrupt Flag cleared.
}
