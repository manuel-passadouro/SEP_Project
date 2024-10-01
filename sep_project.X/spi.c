/* 
 * File:   spi.c
 * Author: mpass
 *
 * Created on 1 de Outubro de 2024, 13:15
 */

#include "spi.h"

void spi_init_master(void){
    
    SPI1CON1BITS
    SPI1sta
    SPI1STATbits.SPIEN = 0; // Disable the SPI peripheral during configuration
    IFS0bits.SPI1IF = 0; // Clear the SPI peripheral interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the SPI peripheral interrupt flag
    SPI1CON1bits.DISSCK = 0; // Enable generation of SCK signal
    SPI1CON1bits.DISSDO = 0; // Enable generation of SDO signal
    SPI1CON1bits.MODE16 = 0; // Set 8-bit mode
    SPI1CON1bits.SMP = 0; // Input data sampled at mid-bit
    SPI1CON1bits.CKP = 0; // Idle is SCK low
    SPI1CON1bits.CKE = 1; // Data changes on SCK falling edge
    SPI1CON1bits.SPRE = 4; // Secondary prescaler = 4:1
    SPI1CON1bits.PPRE = 2; // Primary prescaler = 4:1 (1 MHz if FCY = 16 MHz)
    SPI1CON1bits.MSTEN = 1; // Set for master mode
    SPI1CON2 = 0; // Fully disable frame mode
    // Missing code // Configure pins PPS and disable analog functionality
    SPI1STATbits.SPIEN = 1; // enable SPI port, clear status
}

void spi_write(uint8_t data_out){
    
    SPI1BUF = data_out;
}

uint8_t spi_read(void){
    
    uint8_t data_in;
    
    while(!SPI1STATbits.SPIRBF); // wait for transfer to complete
    data_in = SPI1BUF; // read the received value
    
    return data_in;
}

