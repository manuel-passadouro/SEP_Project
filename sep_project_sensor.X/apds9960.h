/* 
 * File:   apds9960.h
 * Author: mpass
 *
 * Created on 4 de Outubro de 2024, 12:34
 */

#ifndef APDS9960_H
#define	APDS9960_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "i2c.h"

//Config Registers (Read/Write)
#define PIHT_ADDR 0x8B //Proximity interrupt high threshold 
#define ENABLE_ADDR 0x80 //Enable Interrupts and states 
#define CONTROL_ADDR 0x8F //Gain control 
#define GCONFIG1_ADDR 0xA2 //Gesture config 1
#define GCONFIG3_ADDR 0xAA //Gesture config 3
#define GCONFIG4_ADDR 0xAB //Gesture config 4

//Data Registers (Read Only)
#define ID_ADDR 0x94 //Sensor ID 
    
#define PDATA_ADDR 0x9C //Proximty Data
#define CDATAH_ADDR 0x95 //High byte of clear channel data
#define CDATAL_ADDR 0x94 //Low byte of clear channel data
#define RDATAL_ADDR 0x96 //Red Data, Low byte
#define RDATAH_ADDR 0x97 //Red Data, High byte
#define GDATAL_ADDR 0x98 //Green Data, Low byte
#define GDATAH_ADDR 0x99 //Green Data, High byte
#define BDATAL_ADDR 0x9A //Blue Data, Low byte
#define BDATAH_ADDR 0x9B //Blue Data, High byte
    
#define GSTATUS_ADDR 0xAF //Gesture Status
#define GFIFO_U_ADDR 0xFC //Gesture FIFO UP
#define GFIFO_D_ADDR 0xFD //Gesture FIFO DOWN
#define GFIFO_L_ADDR 0xFE //Gesture FIFO LEFT
#define GFIFO_R_ADDR 0xFF //Gesture FIFO RIGHT
    
//Sensor config bytes
#define GAIN_BYTE 0x0A //00001010 -> PGAIN x4, AGAIN x16
#define ENABLE_BYTE 0x07 //00000111 -> turn on sensor, enable Prox, ALS.
#define GCONFIG1_BYTE 0X07 //Enable gesture interrupts and exit mask.
#define GCONFIG4_BYTE 0X01 //Enable gesture engine.

void apds9960_init();
void apds9960_get_prox(uint8_t *);
void apds9960_get_light(uint8_t *, uint8_t *);
void apds9960_get_red(uint8_t *, uint8_t *);
void apds9960_get_green(uint8_t *, uint8_t *);
void apds9960_get_blue(uint8_t *, uint8_t *);



#ifdef	__cplusplus
}
#endif

#endif	/* APDS9960_H */

