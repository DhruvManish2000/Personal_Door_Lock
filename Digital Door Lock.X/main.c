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
#include <avr/io.h>
#include <util/delay.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    // Initialize port PB0 to output
    DDRB |= (1<<DDB0);
    
    while(1) {
        // Turn on pull-up on PB0 (output 1)
        PORTB |= (1<<PORTB0);
        _delay_ms(1000);
        // Turn off pull-up on PB0 (output 0)
        PORTB &= ~(1<<PORTB0);
        _delay_ms(1000);
    }
    return (EXIT_SUCCESS);
}

