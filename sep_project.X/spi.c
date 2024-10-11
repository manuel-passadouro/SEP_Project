 /* 
 * File:   spi.c
 * Author: mpass
 *
 * Created on 1 de Outubro de 2024, 13:15
 */

#include "spi.h"

//volatile int spi_data_out = 0x00;
volatile int spi_data_out = 0x00;
volatile int spi_data_in = 0x00;

// SPI1 ISR example
void __attribute__((__interrupt__, auto_psv)) _SPI1RXInterrupt(void) {
    // Clear the interrupt flag
    IFS3bits.SPI1RXIF = 0;
    
    // Read the received data
    //spi_data_out++;
    spi_data_in = spi_write_byte(spi_data_out);
    
    LATBbits.LATB6 = 0;

}

void spi_init_slave(){
    
    SPI1CON1bits.SPIEN = 0;  // Disable the SPI peripheral during configuration
    //IFS0bits.SPI1IF = 0;     // Clear the SPI peripheral interrupt flag
    //IPC2bits.SPI1IP = 4;     // Set SPI interrupt priority (1-7, 7 being the highest)
    //IEC0bits.SPI1IE = 1;     // Enable the SPI peripheral interrupt flag
    IFS3bits.SPI1RXIF = 0;
    IEC3bits.SPI1RXIE = 1;
    IPC14bits.SPI1RXIP = 4;
    SPI1IMSKLbits.SPIRBFEN = 1;
    //SPI1STATLbits.SPIROV = 0; //Clear Recieve Overflow bit
    SPI1CON1bits.DISSCK = 0; // Enable generation of SCK signal
    SPI1CON1bits.DISSDO = 0; // Enable generation of SDO signal
    SPI1CON1bits.MODE16 = 0; // Set 8-bit mode
    SPI1CON1bits.SMP = 0;    // Input data sampled at mid-bit
    SPI1CON1bits.CKP = 0;    // Idle is SCK low
    SPI1CON1bits.CKE = 1;    // Data changes on SCK falling edge
    SPI1CON1bits.MSTEN = 0;  // Set for slave mode
    SPI1CON1bits.SSEN = 1;   // Slave Select enable
    SPI1CON2 = 0;            // Fully disable frame mode
    SPI1BUFL = 0;            //Clear Recieve buffer
    
    //Configure pins PPS and disable analog functionality
    
    //Disable analog functionality
    //ANSBbits.ANSB11 = 0;  //RB11 has no analog.
    ANSBbits.ANSB12 = 0;    //Disable analog on RB12
    ANSBbits.ANSB13 = 0;    //Disable analog on RB13
    ANSBbits.ANSB14 = 0;    //Disable analog on RB14
    
    TRISBbits.TRISB11 = 1;  //pin 22 MOSI (input)
    TRISBbits.TRISB12 = 0;  //pin 23 MISO (output)
    TRISBbits.TRISB13 = 1;  //pin 24 CLK (input)
    TRISBbits.TRISB14 = 1;  //pin 25 CS (input)
    
    RPINR20bits.SDI1R = 11; //MOSI pin 22 (RP11)
    
    RPOR6bits.RP12R = 7;    //MISO pin 23 (RP12) (7 = SDO1)
    
    RPINR20bits.SCK1R = 13; //SPI SLAVE Clock Input (SCK1IN) pin 7
       
    RPINR21bits.SS1R = 14;  //SPI SLAVE Select Input (SS1IN) pin 4  
    
    SPI1CON1bits.SPIEN = 1;     // enable SPI port, clear status
    
}


uint8_t spi_write_byte(uint8_t data_out){  
    
    uint8_t data_in;
    
    SPI1BUFL = data_out;            // write to buffer for TX (Dummy)
    while(!SPI1STATLbits.SPIRBF);   // wait for transfer to complete
    data_in = SPI1BUFL;             // read the received value
    
          
    
    return data_in;
    //while(SPI1STATLbits.SPITBF);    // wait for transfer to complete
    
}

