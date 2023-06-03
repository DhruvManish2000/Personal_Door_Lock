/* 
 * File:   main.c
 * Author: Max Eberle and Dhruv Pranlal
 *
 * Created on May 23, 2023, 12:46 PM
 * 
 * Project on the ATMega328P
 */

#define F_CPU 1000000UL
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <defines.h>
#include <hd44780.h>
#include <lcd.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
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
    
    // Setup LCD
    lcd_init();
    
    while(1) {
        
        if(!(PINC & (1<<PINC0))) { // 1 is pressed
            _delay_ms(500);
            lcd_putchar(1);
        }
        else if(!(PINC & (1<<PINC1))) { // 2 is pressed
            _delay_ms(500);
            lcd_putchar(2);
        }
        else if(!(PINC & (1<<PINC2))) { // 3 is pressed
            _delay_ms(500);
            lcd_putchar(3);
        }
        else if(!(PINC & (1<<PINC3))) { // 4 is pressed
            _delay_ms(500);
            lcd_putchar(4);
        }
        else if(!(PINC & (1<<PINC4))) { // 5 is pressed
            _delay_ms(500);
            lcd_init();
        }
        
    }
    
    return (EXIT_SUCCESS);
}

