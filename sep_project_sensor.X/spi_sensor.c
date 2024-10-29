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

uint8_t spi_slave_rw(uint8_t miso_byte){
    SPI1BUFL = miso_byte;               // write to buffer for TX
    while(!SPI1STATLbits.SPIRBF);       // wait for transfer to complete
    return SPI1BUFL;                    // read the received value 
}


void spi_slave_handle(){  
    
    uint8_t mosi_cmd;
    uint8_t mosi_dummy;
    uint8_t miso_data;
    uint8_t miso_data_low;
    uint8_t miso_data_high;
    
    //Recive Master Command (Send Dummy)
    mosi_cmd = spi_slave_rw(DUMMY);
          
    //Recieve Master Dummy (Send Dummy)
    mosi_dummy = spi_slave_rw(DUMMY);
    
    /* slave output options
     * A0 - temp data (2 bytes)
     * B0 - prox data (1 byte)
     * B1 - light data (2 bytes)
     * B2 - RGB data (6 bytes)
     * B3 - Gesture data (1 byte?)
     * (...)
     */
    
    switch (mosi_cmd) {
        case 'A':
            //Get data from buffer    
            miso_data_low = sensor_buffer.temp_data_low;
            miso_data_high = sensor_buffer.temp_data_high;
            //Send data bytes
            mosi_dummy = spi_slave_rw(miso_data_low);
            mosi_dummy = spi_slave_rw(miso_data_high);
           
            break;

        case 'B':
            //Get data from buffer
            miso_data_low = sensor_buffer.prox_data_low;
            miso_data_high = sensor_buffer.prox_data_high;
            //Send data bytes
            mosi_dummy = spi_slave_rw(miso_data_low);
            mosi_dummy = spi_slave_rw(miso_data_high);

            break;

        case 'C':
            //Get data from buffer
            miso_data_low = sensor_buffer.light_data_low;
            miso_data_high = sensor_buffer.light_data_high;
            //Send data bytes
            mosi_dummy = spi_slave_rw(miso_data_low);
            mosi_dummy = spi_slave_rw(miso_data_high);

            break;

        case 'D':
            //Get data from buffer
            miso_data_low = sensor_buffer.red_data_low;
            miso_data_high = sensor_buffer.red_data_high;
            //Send data bytes
            mosi_dummy = spi_slave_rw(miso_data_low);
            mosi_dummy = spi_slave_rw(miso_data_high);
            
            miso_data_low = sensor_buffer.green_data_low;
            miso_data_high = sensor_buffer.green_data_high;
            //Send data bytes
            mosi_dummy = spi_slave_rw(miso_data_low);
            mosi_dummy = spi_slave_rw(miso_data_high);
            
            miso_data_low = sensor_buffer.blue_data_low;
            miso_data_high = sensor_buffer.blue_data_high;
            //Send data bytes
            mosi_dummy = spi_slave_rw(miso_data_low);
            mosi_dummy = spi_slave_rw(miso_data_high);

            break;

        default:

            break;
    }
         
    return;    
}

