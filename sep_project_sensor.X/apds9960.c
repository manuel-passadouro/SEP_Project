/* 
 * File:   apds9960.c
 * Author: mpass
 *
 * Created on 4 de Outubro de 2024, 12:34
 */


#include "apds9960.h"

void apds9960_init(){
        
    //Set Control bits (recommended before enable)
    startCondition();                 //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  //send write address
    writeByte(CONTROL_ADDR);          //send register address
    writeByte(GAIN_BYTE);
    stopCondition();                  //End write procedure
    
    //Set Enable bits
    startCondition();                 //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  //send write address
    writeByte(ENABLE_ADDR);           //send register address
    writeByte(ENABLE_BYTE);
    stopCondition();                  //End write procedure
    
    //Set ADC time
    startCondition();                 //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  //send write address
    writeByte(ATIME_ADDR);            //send register address
    writeByte(ATIME_BYTE);
    stopCondition();                  //End write procedure
    
    //Set Config 2 (LED boost)
    startCondition();                 //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  //send write address
    writeByte(CONFIG2_ADDR);          //send register address
    writeByte(CONFIG2_BYTE);
    stopCondition();                  //End write procedure

    //Gesture engine enable
    /*
    startCondition(); //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
    writeByte(GCONFIG1_ADDR); //send register address
    writeByte(GCONFIG1_BYTE);
    stopCondition(); //End write procedure

    startCondition(); //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
    writeByte(GCONFIG4_ADDR); //send register address
    writeByte(GCONFIG4_BYTE);
    stopCondition(); //End write procedure
    */
}

void apds9960_get_prox(uint8_t *prox_data){
    
    startCondition();                 //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  //send write address
    writeByte(PDATA_ADDR);            //send register address
    stopCondition();                  //End write procedure

    startCondition();                 //Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   //send read address
    *prox_data = readByte();
    stopCondition();                  //End read procedure
};


void apds9960_get_light(uint8_t *light_data_high, uint8_t *light_data_low) {
    
    startCondition();                 // Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  // Send write address
    writeByte(CDATAH_ADDR);           // Send register address
    stopCondition();                  // End write procedure

    startCondition();                 // Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   // Send read address
    *light_data_high = readByte();    // Store high byte in the passed pointer
    stopCondition();                  // End read procedure
    
    startCondition();                 // Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  // Send write address
    writeByte(CDATAL_ADDR);           // Send register address
    stopCondition();                  // End write procedure

    startCondition();                 // Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   // Send read address
    *light_data_low = readByte();     // Store high byte in the passed pointer
    stopCondition();                  // End read procedure
}

void apds9960_get_red(uint8_t *red_data_high, uint8_t *red_data_low) {
    
    startCondition();                 // Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  // Send write address
    writeByte(RDATAH_ADDR);           // Send register address
    stopCondition();                  // End write procedure

    startCondition();                 // Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   // Send read address
    *red_data_high = readByte();      // Store high byte in the passed pointer
    stopCondition();                  // End read procedure
    
    startCondition();                 // Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  // Send write address
    writeByte(RDATAL_ADDR);           // Send register address
    stopCondition();                  // End write procedure

    startCondition();                 // Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   // Send read address
    *red_data_low = readByte();       // Store high byte in the passed pointer
    stopCondition();                  // End read procedure
}

void apds9960_get_green(uint8_t *green_data_high, uint8_t *green_data_low) {
    
    startCondition();                 // Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  // Send write address
    writeByte(GDATAH_ADDR);           // Send register address
    stopCondition();                  // End write procedure

    startCondition();                 // Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   // Send read address
    *green_data_high = readByte();    // Store high byte in the passed pointer
    stopCondition();                  // End read procedure
    
    startCondition();                 // Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  // Send write address
    writeByte(GDATAL_ADDR);           // Send register address
    stopCondition();                  // End write procedure

    startCondition();                 // Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   // Send read address
    *green_data_low = readByte();     // Store high byte in the passed pointer
    stopCondition();                  // End read procedure
}

void apds9960_get_blue(uint8_t *blue_data_high, uint8_t *blue_data_low) {
    
    startCondition();                 // Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  // Send write address
    writeByte(BDATAH_ADDR);           // Send register address
    stopCondition();                  // End write procedure

    startCondition();                 // Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   // Send read address
    *blue_data_high = readByte();     // Store high byte in the passed pointer
    stopCondition();                  // End read procedure
    
    startCondition();                 // Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE);  // Send write address
    writeByte(BDATAL_ADDR);           // Send register address
    stopCondition();                  // End write procedure

    startCondition();                 // Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ);   // Send read address
    *blue_data_low = readByte();      // Store high byte in the passed pointer
    stopCondition();                  // End read procedure
}

        
