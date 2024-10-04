/* 
 * File:   i2c.c
 * Author: mpass
 *
 * Created on 4 de Outubro de 2024, 12:21
 */
#include "i2c.h"

void i2c_master_init(void){
    
    I2C1CONLbits.I2CEN = 0; // Disable I2C peripheral during setup
    I2C1CONLbits.A10M = 0; // 7 bit address mode
    I2C1BRG = 0x12; // 400KHz (FCY = 16 MHz)
    
    // Configure I2C pins on pre-defined IOs
    //ANSBbits.ANSB8 = 0;
    ANSBbits.ANSB9 = 0; //Disable analog on RB9
  
    TRISBbits.TRISB8 = 1;    // Set RB8 (SCL1) as input
    TRISBbits.TRISB9 = 1;    // Set RB9 (SDA1) as input
    ODCBbits.ODCB8 = 1;      // Set RB8 (SCL1) as open-drain
    ODCBbits.ODCB9 = 1;      // Set RB9 (SDA1) as open-drain
    
    I2C1CONLbits.I2CEN = 1; //enable I2C1
}

void startCondition(){
    
    I2C1CONLbits.SEN = 1; // Initiate the start condition on SDA and SCL pins
    while(I2C1CONLbits.SEN ); // Wait till sequence is completed
} 
void stopCondition(){
    
    I2C1CONLbits.PEN = 1; // Initiate the stop condition on SDA and SCL pins
    while(I2C1CONLbits.PEN); // Wait till sequence is completed
} 

uint8_t writeByte(uint8_t data){
    
    //startCondition();
    I2C1TRN = data; // Move data to the I2CxTRN register, transmission starts right after
    __delay_ms(20); // Wait till a complete byte is transmitted
    
    if(!I2C1STATbits.ACKSTAT){ // Check for the slave acknowledge
        return 0; // No error code
    }
    return -1; // Error code
    
    
} 

uint8_t readByte(){
    
    I2C1CONLbits.RCEN = 1; // Assert the receive enable bit
    __delay_ms(20); // Wait till a complete byte is transmitted
    if(I2C1STATbits.RBF){// Check if the receive buffer is full
        return I2C1RCV; // Return the received data
    }    
    return -1; // Error code
} 