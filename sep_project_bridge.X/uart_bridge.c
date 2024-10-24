/* 
 * File:   uart_bridge.c
 * Author: mpass
 *
 * Created on 18 de Outubro de 2024, 16:04
 */

#include "uart_bridge.h"

void uart1_init(){
      
    //UART1 module config
    U1MODEbits.STSEL = 0;   // 1-Stop bit
    U1MODEbits.PDSEL = 0;   // No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0;   // Auto-Baud disabled
    U1MODEbits.BRGH = 0;    // Standard-Speed mode
    U1BRG = UART_BR;        // BRG = (FCY/((16*9600)=)-1 = 103  , uart baudrate = 9600 (low speed)
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IEC0bits.U1TXIE = 0;    // Enable UART TX interrupt
    U1MODEbits.UARTEN = 1;  // Enable UART
    U1STAbits.UTXEN = 1;    // Enable UART TX
    //U1STAbits.URXEN = 1;  // Enable UART RX (not needed???)
    
    //PPS for UART1 TX and RX
    
    //Disable analog functionality
    //No analog on RFx pins
    RPINR18bits.U1RXR = 10; // U1RX on pin 49 (RP10/RF4)   
    RPOR8bits.RP17R = 3; // U1TX on pin 50 (RP17/RF5)
    
}

void uart1_write(char data)
{
    //while(U1STAbits.UTXBF); // Wait while the transmit buffer is full
    U1TXREG = data;         // Write the data to the transmit register
    while(!(U1STAbits.TRMT));
}

char uart1_read(void)
{
   //while(!U1STAbits.URXDA); // Wait for the receive buffer to have data
   
   if(U1STAbits.URXDA == 1)
   {
    return U1RXREG;
   }
   else{
       return NULL;
   }      
    //return U1RXREG;          // Read the received data from the buffer
}