/* 
 * File:   utils.h
 * Author: mpass
 *
 * Created on 24 de Outubro de 2024, 13:53
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include"sys_config.h"
    
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
} sensor_buffer_struct;

extern volatile sensor_buffer_struct sensor_buffer;


void test_sleep(void);
void led_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

