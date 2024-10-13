/* 
 * File:   uart.h
 * Author: mpass
 *
 * Created on 11 de Outubro de 2024, 16:20
 */
#include <xc.h>

void UART1_Init(unsigned long baudrate) {
    unsigned int brg_val;
    
    // Set Baud Rate based on Fcy (assuming Fcy = 16 MHz)
    brg_val = (unsigned int)((16000000 / (16 * baudrate)) - 1);
    
    U1MODEbits.UARTEN = 0;  // Disable UART1 while setting it up
    U1MODEbits.BRGH = 0;    // Standard speed mode (16x baud rate)
    
    U1BRG = brg_val;        // Set baud rate generator value
    
    // Configure TX/RX pins as digital inputs/outputs
    TRISBbits.TRISB7 = 1;   // Set RB7 as input (RX)
    TRISBbits.TRISB6 = 0;   // Set RB6 as output (TX)
    
    // Configure the UART1 mode (8 data bits, no parity, 1 stop bit)
    U1MODEbits.PDSEL = 0;   // 8-bit data, no parity
    U1MODEbits.STSEL = 0;   // 1 stop bit
    
    // Enable transmission and reception
    U1STAbits.UTXEN = 1;    // Enable transmission
    U1STAbits.URXEN = 1;    // Enable reception
    
    // Clear interrupt flags for TX and RX
    IFS0bits.U1TXIF = 0;
    IFS0bits.U1RXIF = 0;
    
    // Enable UART1
    U1MODEbits.UARTEN = 1;  // Enable UART1
}
