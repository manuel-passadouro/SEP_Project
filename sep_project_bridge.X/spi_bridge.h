/* 
 * File:   spi_bridge.h
 * Author: mpass
 *
 * Created on 18 de Outubro de 2024, 16:50
 */

#ifndef SPI_BRIDGE_H
#define	SPI_BRIDGE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h> 
#include <xc.h>
    
#define SPI_DIR_SDO TRISGbits.TRISG8 //pin 12
#define SPI_DIR_CLK TRISGbits.TRISG6 //pin 10
#define SPI_DIR_SDI TRISGbits.TRISG7 //pin 11
#define SPI_DIR_CS TRISGbits.TRISG9  //pin 14

#define SPI_CS LATGbits.LATG9

#define DUMMY 0xAA

void spi_init_master(void);
uint8_t spi_master_rw(uint8_t);
void spi_master_handle(uint8_t , char *);


#ifdef	__cplusplus
}
#endif

#endif	/* SPI_BRIDGE_H */

