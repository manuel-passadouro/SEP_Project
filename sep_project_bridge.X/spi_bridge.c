/* 
 * File:   spi_bridge.c
 * Author: mpass
 *
 * Created on 18 de Outubro de 2024, 16:50
 */

#include "spi_bridge.h"

void spi_init_master(void){
    
    SPI1CON1Lbits.SPIEN = 0; // Disable the SPI peripheral during configuration
    IFS0bits.SPI1IF = 0; // Clear the SPI peripheral interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the SPI peripheral interrupt flag    
    SPI1CON1bits.DISSCK = 0; // Enable generation of SCK signal
    SPI1CON1bits.DISSDO = 0; // Enable generation of SDO signal
    SPI1CON1bits.MODE16 = 0; // Set 8-bit mode
    SPI1CON1bits.SMP = 0; // Input data sampled at mid-bit
    SPI1CON1bits.CKP = 0; // Idle is SCK low
    SPI1CON1bits.CKE = 1; // Data changes on SCK falling edge
    SPI1BRGL = 79; // Baud rate divisor FCY/100k
    SPI1CON1bits.MSTEN = 1; // Set for master mode
    SPI1CON2 = 0; // Fully disable frame mode
    
    //Configure pins PPS and disable analog functionality
    
    //Disable analog functionality
    ANSGbits.ANSELG6 = 0; //Disable analog on RG6
    ANSGbits.ANSELG7 = 0; //Disable analog on RG7
    ANSGbits.ANSELG8 = 0; //Disable analog on RG8
    ANSGbits.ANSELG9 = 0; //Disable analog on RG9
    
    
    TRISGbits.TRISG6 = 0; //pin 10 CLK (output)
    TRISGbits.TRISG7 = 1; //pin 11 MISO (input)
    TRISGbits.TRISG8 = 0; //pin 12 MOSI (output)
    TRISGbits.TRISG9 = 0; //pin 14 CS (output)
    
    RPINR20bits.SDI1R  = 26; // MISO RP26 (SDI1)
    RPOR9bits.RP19R  = 7;    // MOSI RP19 (7 = SDO1)
    RPOR10bits.RP21R  = 8;    // SPI Clock RP21 (8 = SCK1OUT)
    
    LATGbits.LATG9 = 1; //Set CS high, enable slave
            
    SPI1CON1Lbits.SPIEN = 1; // enable SPI port, clear status
}

uint8_t spi_master_rw(uint8_t mosi_byte){
    SPI1BUFL = mosi_byte;               // write to buffer for TX
    while(!SPI1STATLbits.SPIRBF);       // wait for transfer to complete
    return SPI1BUFL;                    // read the received value 
}


void spi_master_handle(uint8_t mosi_cmd, char *output_buffer) {
    
    uint8_t miso_dummy;
    uint8_t bytes_to_read = 0;              // Determine how many bytes to read based on command
    uint8_t buff_idx = 0;
    
    LATGbits.LATG9 = 0;                     //Set CS (active low))
    delay_nop(2000);                        // Delays for 1000 instruction cycles (125 ms)
    
    // Send command
    miso_dummy = spi_master_rw(mosi_cmd);

    // Send additional dummy byte
    miso_dummy = spi_master_rw(DUMMY);

    // Determine the number of bytes to read based on the command
    switch (mosi_cmd) {
        case 'A':
            bytes_to_read = 2;              // Temperature data (2 bytes)
            break;
        case 'B':
            bytes_to_read = 2;              // Proximity data (1 byte)
            break;
        case 'C':
            bytes_to_read = 2;              // Light data (2 bytes)
            break;
        case 'D':
            bytes_to_read = 6;              // RGB data (6 bytes)
            break;
        case 'E':
            bytes_to_read = 2;  // Gesture data (1 byte)
            break;
        default:
            bytes_to_read = 2;  // Default case (1 byte)
            break;
    }

    // Retrieve data bytes from the slave into the output buffer
    for (buff_idx = 1; buff_idx < bytes_to_read + 1; buff_idx++) {
        output_buffer[buff_idx] = spi_master_rw(DUMMY);  // Store Slave response in buffer (start in second position)
        delay_nop(2000);
        //output_buffer[buff_idx] = 0xBB;
    }
    output_buffer[buff_idx] = '\n'; //Place newline to mark end of uart message
    buff_idx ++;
    output_buffer[buff_idx] = '\0'; //Place terminator after data

    LATGbits.LATG9 = 1;    // CS
    
    return bytes_to_read;  // Return the number of bytes read into the buffer
}
