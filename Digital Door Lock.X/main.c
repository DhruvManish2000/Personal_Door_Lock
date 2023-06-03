/* 
 * File:   main.c
 * Author: Max Eberle and Dhruv Pranlal
 *
 * Created on May 23, 2023, 12:46 PM
 * 
 * Project on the ATMega328P
 */

#define F_CPU 1000000UL
#include "defines.h"
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

#define CODE_SIZE 4

/*
 * 
 */

FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

void initialize();
void code_attempt(uint8_t *buffer, int count);
int check_code(uint8_t *code, uint8_t *input, int count);

// Hard-coded the solution for now
uint8_t code[CODE_SIZE] = {1,1,1,1};
int result;

int main(int argc, char** argv) {
    
    // Setup ports
    initialize();
    
    lcd_init();
    
    
    while(1) {
        
        uint8_t input[CODE_SIZE] = {0};
        code_attempt(input, CODE_SIZE);
        result = check_code(code, input, CODE_SIZE);
        
        if(result==CODE_SIZE) { // Correct code entered
            PORTD |= (1<<PORTD3); // Turn on motor to unlock door
        }
        else {
            lcd_init();
        }
    }
    
    return (0);
}

void initialize() {
    // Initialize keypad button ports for input
    DDRC &= ~(1<<DDC0); // SW1
    DDRC &= ~(1<<DDC1); // SW2
    DDRC &= ~(1<<DDC2); // SW3
    DDRC &= ~(1<<DDC3); // SW4
    DDRC &= ~(1<<DDC4); // SW5
//    DDRC &= ~(1<<DDC5); // SW6
//    DDRB &= ~(1<<DDB0); // SW7
//    DDRB &= ~(1<<DDB1); // SW8
//    DDRB &= ~(1<<DDB2); // SW9
//    DDRB &= ~(1<<DDB6); // SW0
//    DDRB &= ~(1<<DDB7); // SW Reset
    
    // Turn on keypad port pull-ups (active high)
    PORTC |= (1<<PORTC0);
    PORTC |= (1<<PORTC1);
    PORTC |= (1<<PORTC2);
    PORTC |= (1<<PORTC3);
    PORTC |= (1<<PORTC4);
//    PORTC |= (1<<PORTC5);
//    PORTB |= (1<<PORTB0);
//    PORTB |= (1<<PORTB1);
//    PORTB |= (1<<PORTB2);
//    PORTB |= (1<<PORTB6);
//    PORTB |= (1<<PORTB7);
    
    //Initialize motor port to output
    DDRD |= (1<<DDD3);
}

void code_attempt(uint8_t *buffer, int count) {
    
    _delay_ms(200);
    
    for(int i=0; i<count; i++) {
        
        while(1) {
            
            if(!(PINC & (1<<PINC0))) { // 1 is pressed
                _delay_ms(200);
                buffer[i] = 1;
                fprintf(stderr, "C \x1b\xc0      \x31");
                break;
            }
            if(!(PINC & (1<<PINC1))) { // 2 is pressed
                _delay_ms(200);
                buffer[i] = 2;
                fprintf(stderr, "C \x1b\xc0      \x32");
                break;
            }
            if(!(PINC & (1<<PINC2))) { // 3 is pressed
                _delay_ms(200);
                buffer[i] = 3;
                fprintf(stderr, "C \x1b\xc0      \x33");
                break;
            }
            if(!(PINC & (1<<PINC3))) { // 4 is pressed
                _delay_ms(200);
                buffer[i] = 4;
                fprintf(stderr, "C \x1b\xc0      \x34");
                break;
            }
            if(!(PINC & (1<<PINC4))) { // 5 is pressed
                _delay_ms(200);
                buffer[i] = 5;
                fprintf(stderr, "C \x1b\xc0      \x35");
                break;
            }
        }
    }
}

int check_code(uint8_t *code, uint8_t *input, int count) {
    
    int k = 0;
    
    for(int i=0; i<count; i++) {
        
        if(code[i] != input[i]) {
            _delay_ms(200);
            lcd_init();
            fprintf(stderr, "C \x1b\xc0      \x58");
            break;
        }
        else {
            k++;
            continue;
        }
    }
    return(k);
}