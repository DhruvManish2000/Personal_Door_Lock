/* 
 * File:   lcd.h
 * Author: Max Eberle and Dhruv Pranlal
 *
 * Created on June 2, 2023, 9:27 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

/*
 * Initialize LCD controller.  Performs a software reset.
 */
void lcd_init(void);

/*
 * Send one character to the LCD.
 */
int	lcd_putchar(char c, FILE *stream);