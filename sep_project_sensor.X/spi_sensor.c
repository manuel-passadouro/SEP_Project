 /* 
 * File:   spi.c
 * Author: mpass
 *
 * Created on 1 de Outubro de 2024, 13:15
 */

#include "spi_sensor.h"
#include "utils.h"

//volatile int spi_data_out = 0x00;
//volatile uint8_t spi_data_out[12] = {0x00};
volatile SPIDataOut spi_data_out = {0x00};
volatile uint8_t spi_data_in = 0x00;


// SPI1 ISR example
void __attribute__((__interrupt__, auto_psv)) _IOCInterrupt(void) {
    // Clear the interrupt flag
     IFS1bits.IOCIF = 0;       // Clear interrupt flag
    
    // Read the received data
    //spi_data_out++;
    spi_data_in = spi_slave_rw();
    
    LATBbits.LATB6 = 0;

}


void spi_init_slave(){
    
    SPI1CON1bits.SPIEN = 0;  // Disable the SPI peripheral during configuration
    
    //Use IoC instead of SPI interrupt
    //IFS0bits.SPI1IF = 0;     // Clear the SPI peripheral interrupt flag
    //IPC2bits.SPI1IP = 4;     // Set SPI interrupt priority (1-7, 7 being the highest)
    //IEC0bits.SPI1IE = 1;     // Enable the SPI peripheral interrupt flag
    //IFS3bits.SPI1RXIF = 0;
    //IEC3bits.SPI1RXIE = 0;
    //IPC14bits.SPI1RXIP = 4;
    //SPI1IMSKLbits.SPIRBFEN = 1;
    
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


uint8_t spi_slave_rw(){  
    
    uint8_t mosi_cmd;
    uint8_t mosi_dummy;
    uint8_t miso_data;
    uint8_t miso_data_low;
    uint8_t miso_data_high;
    
    SPI1BUFL = DUMMY;            // write to buffer for TX (Dummy)
    while(!SPI1STATLbits.SPIRBF);   // wait for transfer to complete
    mosi_cmd = SPI1BUFL;             // read the received value
    
    SPI1BUFL = DUMMY;            // write to buffer for TX (Dummy)
    while(!SPI1STATLbits.SPIRBF);   // wait for transfer to complete
    mosi_dummy = SPI1BUFL;             // read the received value
    
    /* slave output options
     * A0 - temp data (2 bytes)
     * B0 - prox data (1 byte)
     * B1 - light data (2 bytes)
     * B2 - red data (2 bytes)
     * B3 - green data (2 bytes)
     * B4 - blue data (2 bytes)
     */
    
    switch (mosi_cmd) {
        case 0xA0:

            miso_data_low = sensor_buffer.temp_data_low; //Send temp
            miso_data_high = sensor_buffer.temp_data_high; //Send temp

            break;

        case 0xB0:

            miso_data_low = sensor_buffer.prox_data_low; //Send prox
            miso_data_high = sensor_buffer.prox_data_high; //Send prox
                       
            break;

        default:

            break;
    }
    
    SPI1BUFL = miso_data_low;            // write to buffer for TX (sensor data)
    while(!SPI1STATLbits.SPIRBF);   // wait for transfer to complete
    mosi_dummy = SPI1BUFL;             // read the received value
           
    return mosi_dummy;
    //while(SPI1STATLbits.SPITBF);    // wait for transfer to complete
    
}

