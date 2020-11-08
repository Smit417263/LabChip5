/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{init, inc, dec, reset, wait,wait2} state;

unsigned char button0;
unsigned char button1;

unsigned char tempB;


void Tick(){
	button0 = ~PINA & 0x01;
	button1 = ~PINA & 0x02;

	switch(state){ // Transitions
		case init:
			if(!button0 && !button1){
				state = init;
			}
			else if(button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = reset;
			}
			break;
		case inc:
			if(button0 && button1){
				state = reset;
			}
			else{
				state = wait2;
			}
			break;
		case dec:
			if(button0 && button1){
				state = reset;
			}
			else{
				state = wait2;
			}
			break;
		case reset:
			if(!button0 && !button1){
				state = init;
			}
			else if (button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = reset;
			}
			break;
		case wait:
			if(button0 && button1){
				state = reset;
			}
			else if(button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else{
				state = wait;
			}
			break;
		case wait2:
			if(!button0 && !button1){
				state = wait;
			}
			else if(button0 && button1){
				state = reset;
			}
			else{
				state = wait2;
			}
			break;

	}
	switch(state){ // State actions
		case init:
			break;
		case inc:
			if(tempB < 9){
				tempB = tempB << 1;
			}
			else{
				tempB = 0x01;
			}
			break;
		case dec:
		//	if(tempC > 0){
		//		tempC = tempC - 1;
		//	}
			break;
		case reset:
			tempB = 0;
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00; 
				

	state = init;
	tempB = 0x01;

	while (1){
	button0 = ~PINA & 0x01;
	button1 = ~PINA & 0x02;
        Tick();
	PORTB = tempB;

	}

	return 0;
}
