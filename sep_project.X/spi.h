/* 
 * File:   spi.h
 * Author: mpass
 *
 * Created on 1 de Outubro de 2024, 13:15
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "sys_config.h"
    
//SPI slave pins
//MOSI pin 22 RP/RB11
//MISO pin 23 RP/RB12
//CLK pin 24 RP/RB13
//CS pin 25 RP/RB14

extern volatile int spi_data_out;
extern volatile int spi_data_in;

void spi_init_slave(void);
uint8_t spi_write_byte(uint8_t) ;


#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

