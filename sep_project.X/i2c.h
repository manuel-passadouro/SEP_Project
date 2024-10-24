/* 
 * File:   i2c.h
 * Author: mpass
 *
 * Created on 4 de Outubro de 2024, 12:21
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/system.h"
//#define FCY 16000000UL
#include <libpic30.h>
#include <stdbool.h>
    
#define I2C_SLAVE_ADDR_READ 0x73
#define I2C_SLAVE_ADDR_WRITE 0x72

#define I2C_READ 1
#define I2C_WRITE 0
    
void i2c_master_init(void);
void startCondition(void);
void stopCondition(void);
uint8_t writeByte(uint8_t);
uint8_t readByte(void);


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

