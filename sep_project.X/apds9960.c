/* 
 * File:   apds9960.c
 * Author: mpass
 *
 * Created on 4 de Outubro de 2024, 12:34
 */


#include "apds9960.h"

void apds9960_init(){
    //Enable proximity and light detection
    startCondition(); //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
    writeByte(ENABLE_ADDR); //send register address
    writeByte(ENABLE_BYTE);
    stopCondition(); //End write procedure

    //Set snesor gain
    startCondition(); //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
    writeByte(CONTROL_ADDR); //send register address
    writeByte(GAIN_BYTE);
    stopCondition(); //End write procedure

    /*
     * //Set ADC time
    startCondition(); //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
    writeByte(CONTROL_ADDR); //send register address
    writeByte(ADC_TIME_BYTE);
    stopCondition(); //End write procedure
     */

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

uint8_t apds9960_get_prox(){
    
    uint8_t prox_data = 0;
    startCondition(); //Start write procedure
    writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
    writeByte(PDATA_ADDR); //send register address
    stopCondition(); //End write procedure

    startCondition(); //Start read procedure
    writeByte(I2C_SLAVE_ADDR_READ); //send read address
    prox_data = readByte();
    stopCondition(); //End read procedure
    return prox_data;
};
        
