/* 
 * File:   newmain.c
 * Author: dhruvmanish
 *
 * Created on May 20, 2023, 11:21 AM
 */

#include <stdio.h>
#include <stdlib.h>
#define F_CPU 1000000UL 
#include <avr/io.h>
#include <util/delay.h>


/*
 * 
 */
int main(int argc, char** argv) {
    
    
    DDRB |= (1 << DDB0);
    PORTB |= (1 << PORTB0);

    return (EXIT_SUCCESS);
}