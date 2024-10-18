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

#define UART_BR 103 //Baudrate = (FCY/((16*9600)=)-1 = 103, for uart baudrate = 9600 (low speed)
    
void uart1_init(void);
void uart1_write(char);
char uart1_read(void);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_BRIDGE_H */

