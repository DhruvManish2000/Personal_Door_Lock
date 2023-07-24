/* 
 * File:   main.c
 * Author: Max Eberle and Dhruv Pranlal
 *
 * Created on May 23, 2023, 12:46 PM
 * 
 * Summary: Project on the ATMega328P that uses keypad input (from pushbuttons) 
 * to enter a code that is displayed on an HD44780 based LCD. The correct code
 * unlocks a door by sending a signal to activate a DC motor.
 * 
 */

#include "defines.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

#define MAX_SIZE 16 // Character limit of one LCD line
/*
 * 
 */

FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

// Function prototypes
void port_init();
int code_attempt(uint8_t *buffer, int count);
void check_code(uint8_t *code, uint8_t *input, int size);
void unlock_door();

//void set_code(uint8_t *code, int size); // Set code function


int main(int argc, char** argv) {
    
    // Initialize ports
    port_init();
    
    // Initialize LCD
    lcd_init();
    
//    int input_counter;
//    int code_size = 4;
//    int input_size;
    
    // Test code
    port_init();
    lcd_init(); // we have it inside the while(1) so it reinitializes the variables again and rewrites from start otherwise it would keep on calling fprintf and just write infinitely
    fprintf (& lcd_str , " Hell \x1b\xc0 World");
    DDRB |= (1<<DDB1);

    while (1) {
        
        if (!(PINC & (1 << PINC0))) { // '1' is pressed

            PORTB |= (1 << PORTB1);
        } else {
              PORTB &= ~(1 << PORTB1);
        }
    }
    
//    uint8_t code[code_size] = {1,1,1,1}; // Hard-coded the password for now
    
    // Set password
//    uint8_t code[code_size] = {0};
//    set_code(code, code_size);
//    code_size = sizeof(code)/sizeof(code[0]);
    
    /*
    while(1) {
        
        // Display "Code + Enter:" on LCD - maybe use a function?
        
        uint8_t input[MAX_SIZE] = {0};
        input_counter = 0;
        
        input_size = code_attempt(input, input_counter);
        
        if (input_size == code_size) {
            
            check_code(code, input, code_size);
        }
        else {
            
            // [Function to display incorrect message]
        }
    } 
    */
    
    return (0);
}

void port_init() {
    
    // Initialize keypad ports to input
    DDRC &= ~(1<<DDC0); // Keypad '1'
    DDRC &= ~(1<<DDC1); // Keypad '2'
    DDRC &= ~(1<<DDC2); // Keypad '3'
    DDRC &= ~(1<<DDC3); // Keypad '4'
    DDRC &= ~(1<<DDC4); // Keypad '5'
    DDRC &= ~(1<<DDC5); // Keypad '6'
    
    DDRB &= ~(1<<DDB0); // Keypad '7'
    DDRB &= ~(1<<DDB1); // Keypad '8'
    DDRB &= ~(1<<DDB2); // Keypad '9'
    
    DDRD &= ~(1<<DDD2); // Keypad '0'
    DDRD &= ~(1<<DDD3); // Keypad 'ENTER'
    
    // Initialize motor signal ports to output
    DDRB |= (1<<DDB6); // Motor+
    DDRB |= (1<<DDB7); // Motor-
    
    // Turn on keypad port pull-ups (active high)
    PORTC |= (1<<PORTC0);
    PORTC |= (1<<PORTC1);
    PORTC |= (1<<PORTC2);
    PORTC |= (1<<PORTC3);
    PORTC |= (1<<PORTC4);
    PORTC |= (1<<PORTC5);
    
    PORTB |= (1<<PORTB0);
    PORTB |= (1<<PORTB1);
    PORTB |= (1<<PORTB2);
    
    PORTD |= (1<<PORTD2);
    PORTD |= (1<<PORTD3);
    
    // Set motor signal ports to output low
    PORTB &= ~(1<<PORTB6);
    PORTB &= ~(1<<PORTB7);
    
    return;
}

int code_attempt(uint8_t *buffer, int count) {
    
    /* This function takes the memory location of 'buffer' so it can edit the
     * 'input' array values in the main function
     */
    
    int input_size = 0;
    
    while (count < MAX_SIZE) {
        
        if (!(PIND & (1<<PIND3))) { // 'ENTER' is pressed
            _delay_ms(250);
            input_size = count;
            count = MAX_SIZE; 
            break;
            // This way, the length of the code can be variable and the program
            // doesn't continue until the 'ENTER' key is pressed
        }
        
        if (!(PIND & (1<<PIND2))) { // '0' is pressed
            _delay_ms(250);
            buffer[count] = 0;
            // [Function to display '0' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINC & (1<<PINC0))) { // '1' is pressed
            _delay_ms(250);
            buffer[count] = 1;
            // [Function to display '1' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINC & (1<<PINC1))) { // '2' is pressed
            _delay_ms(250);
            buffer[count] = 2;
            // [Function to display '2' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINC & (1<<PINC2))) { // '3' is pressed
            _delay_ms(250);
            buffer[count] = 3;
            // [Function to display '3' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINC & (1<<PINC3))) { // '4' is pressed
            _delay_ms(250);
            buffer[count] = 4;
            // [Function to display '4' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINC & (1<<PINC4))) { // '5' is pressed
            _delay_ms(250);
            buffer[count] = 5;
            // [Function to display '5' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINC & (1<<PINC5))) { // '6' is pressed
            _delay_ms(250);
            buffer[count] = 6;
            // [Function to display '6' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINB & (1<<PINB0))) { // '7' is pressed
            _delay_ms(250);
            buffer[count] = 7;
            // [Function to display '7' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINB & (1<<PINB1))) { // '8' is pressed
            _delay_ms(250);
            buffer[count] = 8;
            // [Function to display '8' in the 'count' position of the LCD]
            count++;
        }
        
        if (!(PINB & (1<<PINB2))) { // '9' is pressed
            _delay_ms(250);
            buffer[count] = 9;
            // [Function to display '9' in the 'count' position of the LCD]
            count++;
        }
    }
    
    return input_size;
}

void check_code(uint8_t *code, uint8_t *input, int size) {
    
    int correct = 0;
    
    for (int i = 0; i < size; i++ ) {

        if (input[i] != code[i]) {

            // [Function to display incorrect message]
            break;
        }
        else {
            correct++;
            continue;
        }
    }
    
    if (correct == size) {
        
        // [Function to display correct message]
        // Ask if user wants to reset code
        // If yes, function to reset code
        
        unlock_door();
    }
    
    return;
}

void unlock_door() {
    
    // Set PD6 and PD7 to oscillate so motor driver unlocks door
    _delay_ms(10000); // 10 second delay
    // Set PD6 and PD7 to oscillate so motor driver locks door
    
    return;
}

//void set_code(uint8_t *code, int size) {
//    
//    // Function to set/reset code
//    return;
//}