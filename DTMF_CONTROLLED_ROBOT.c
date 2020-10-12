/*
LEDs---@------------->PB1
LEDs---@------------->PB2
LEDs---@------------->PB3
LEDs---@------------->PB4
Left Sensor---------->PC3
Right Sensor--------->PC0
Buzzer--------------->PD4
DTMF D0-------------->PB0
DTMF D1-------------->PD7
DTMF D2-------------->PD6
DTMF D3-------------->PB5
RIGHT MOTOR(+)------->PB1
RIGHT MOTOR(-)------->PB2
LEFT MOTOR(-)-------->PB3
LEFT MOTOR(+)-------->PB4
BOOTLoader Condition Check----->PC5(If 0 bootloader section else program execution
							    section of Flash memory)
RESET-------------------------->PC6
Crystal Oscillator------------->PB6 and PB7
VB=Battery Supply
VCC=regulated 5V+
Gnd=Ground(0V)
*/

#define F_CPU 12000000UL
#include<avr/io.h>
#include<util/delay.h>
void wait(float sec)
{
for(int i=0;i<(int)46*sec;i++)
_delay_loop_2(0);
}
int main(void)
{
int d=0;
int b=0;      
DDRB=0b00011110;  //PB1, PB2, PB3, PB4 as output bits connected to motors and PB0 as input bit connected to DTMF decoder IC
DDRD=0b00010000;  //PD7, PD6, PD5 connected to DTMF decoder IC hence input bits and 
				  //PD4 connected to buzzer hence output bit.

while(1)          // infinite loop
{
b=PINB&0b00000001;
d=PIND&0b11100000; 
PORTD &= ~(1<<4);

if(d==0b10000000 && b==0b00000000)          //if Key 2 of cell phone pressed
{
PORTB=0b00010010;    // move straight
}

if(d==0b01000000 && b==0b00000000)          // if Key 4 of cell phone pressed
{
PORTB=0b000010000;    // turn left
PORTD = (1<<4);
wait(0.2);
PORTD &= ~(1<<4);
wait(0.2);
}

if(d==0b11000000 && b==0b00000000)          // if Key 6 of cell phone pressed
{
PORTB=0b00000010;   // turn right
PORTD = (1<<4);
wait(0.2);
PORTD &= ~(1<<4);
wait(0.2);
}

if(d==0b00100000 && b==0b00000000)          // if Key 8 of cell phone pressed
{
PORTB=0b00001100;    // move back
}

if(d==0b00000000 && b==0b00000001)			// if key 1 of cell phone pressed
{
PORTB=0b000010000;	// left turn
PORTD = (1<<4);
wait(0.5);
PORTB=0b00010010;	// move forward                                        
wait(10);
}

if(d==0b10000000 && b==0b00000001)			// if key 3 of cell phone pressed
{
PORTB=0b00000010;	// right turn
PORTD = (1<<4);
wait(0.5);
PORTB=0b00010010;	// move forward
wait(10);
}    

if(d==0b11000000 && b==0b00000001)			// if key 7 of cell phone pressed
{
PORTB=0b00001000;	// left turn in backward direction
PORTD = (1<<4);
wait(0.5);
PORTB=0b00001100;	// move back
wait(10);
}  

if(d==0b00100000 && b==0b00000001)			// if key 9 of cell phone 
{
PORTB=0b00000100;	// right turn in backward direction
PORTD = (1<<4);
wait(0.5);
PORTB=0b00001100;	// move back
wait(10);
}  

if(d==0b01000000 && b==0b00000001)          // if Key 5 of cell phone pressed
{
PORTB=0b00000000;    //stop
}


}   //while closed
}   //main closed
