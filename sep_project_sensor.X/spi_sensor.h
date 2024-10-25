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
    
#define DUMMY 0xAA

//extern volatile uint8_t spi_data_out[12];

typedef struct {
    uint8_t temp_data_high;   // High byte of temperature data
    uint8_t temp_data_low;    // Low byte of temperature data

    uint8_t prox_data_high;        // Proximity data (1 byte)
    uint8_t prox_data_low;        // Proximity data (1 byte)

    uint8_t light_data_high;  // High byte of light data
    uint8_t light_data_low;   // Low byte of light data

    uint8_t red_data_high;    // High byte of red data
    uint8_t red_data_low;     // Low byte of red data

    uint8_t green_data_high;  // High byte of green data
    uint8_t green_data_low;   // Low byte of green data

    uint8_t blue_data_high;   // High byte of blue data
    uint8_t blue_data_low;    // Low byte of blue data
} SPIDataOut;

extern volatile uint8_t spi_data_in;
extern volatile SPIDataOut spi_data_out;


void spi_init_slave(void);
void spi_slave_handle(void);
uint8_t spi_slave_rw(uint8_t) ;


#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

