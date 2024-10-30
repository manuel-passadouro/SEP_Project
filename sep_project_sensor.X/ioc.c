/* 
 * File:   ioc.h
 * Author: mpass
 *
 * Created on 24 de Outubro de 2024, 12:18
 */

#include "ioc.h"

// SPI1 ISR example
void __attribute__((__interrupt__, auto_psv)) _IOCInterrupt(void) {
    
    // Clear the interrupt flag
    IFS1bits.IOCIF = 0;       // Clear interrupt flag
    //SPI Comunication
    spi_slave_handle();
  }

void ioc_init(){
    //Interrupt On Change Setup
    
    PADCONbits.IOCON = 1;   // Enables the IoC functionality for all pins
    IOCPBbits.IOCPB14 = 0;  // Disables rising edge detection
    IOCNBbits.IOCNB14 = 1;  // Enables falling edge detection
    IOCFBbits.IOCFB14 = 0;  // Clear the individual interrupt flag for RA1
    IFS1bits.IOCIF = 0;     // Clear overall IoC interrupt flag
    IPC4bits.IOCIP = 4;     // Configure the IoC interrupts priority to value 1
    IEC1bits.IOCIE = 1;     // Enable the IoC interrupts
    INTCON2bits.GIE = 1;    //Enables Global Interrupt
}
