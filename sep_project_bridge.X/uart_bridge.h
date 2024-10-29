/* 
 * File:   uart_bridge.h
 * Author: mpass
 *
 * Created on 18 de Outubro de 2024, 16:04
 */

#ifndef UART_BRIDGE_H
#define	UART_BRIDGE_H

#ifdef	__cplusplus
extern "C" {
#endif
  
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h> 
#include <xc.h>

//#define UART_BR 103 //Baudrate = (FCY/((16*9600))-1 = 103, for uart baudrate = 9600 (low speed)
#define UART_BR 51 //Baudrate = (FCY/((16*19200))-1 = 103, for uart baudrate = 19200 (low speed)
#define TX_MAX_SIZE 10 //Max nunmber of bytes to send
#define RX_MAX_SIZE 10 //Max nunmber of bytes to send
    
void uart1_init(void);
//void uart1_write(char);
void uart1_write(char*, uint8_t);
//char uart1_read(void);
uint8_t uart1_read(char* , uint8_t);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_BRIDGE_H */

