/* 
 * File:   defines.h
 * Author: Max Eberle and Dhruv Pranlal
 *
 * Created on June 2, 2023, 9:21 PM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */

/* CPU frequency */
#define F_CPU 1000000UL

/* UART baud rate */
#define UART_BAUD  9600

/* HD44780 LCD port connections */
#define HD44780_RS D, 0
#define HD44780_RW D, 1
#define HD44780_E  D, 2
/* The data bits have to be not only in ascending order but also consecutive. */
#define HD44780_D4 D, 4

/* Whether to read the busy flag, or fall back to
   worst-time delays. */
#define USE_BUSY_BIT 1
