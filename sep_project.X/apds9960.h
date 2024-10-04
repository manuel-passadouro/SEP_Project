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

//Config Registers
#define PIHT_ADDR 0x8B //Proximity interrupt high threshold (R/W)
#define ENABLE_ADDR 0x80 //Enable Interrupts and states (R/W)
#define CONTROL_ADDR 0x8F //Gain control (R/W)
#define GCONFIG1_ADDR 0xA2 //Gesture config 1 (R/W)
#define GCONFIG3_ADDR 0xAA //Gesture config 3 (R/W)
#define GCONFIG4_ADDR 0xAB //Gesture config 4 (R/W)

//Data Registers
#define ID_ADDR 0x94 //Sensro ID (R)
#define PDATA_ADDR 0x9C //Proximty Data (R)
#define CDATAH_ADDR 0x95 //High byte of clear channel data (R)
#define CDATAL_ADDR 0x94 //Low byte of clear channel data (R)
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
uint8_t apds9960_get_prox();

#ifdef	__cplusplus
}
#endif

#endif	/* APDS9960_H */

