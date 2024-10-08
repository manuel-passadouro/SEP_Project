/* 
 * File:   adc.h
 * Author: mpass
 *
 * Created on 1 de Outubro de 2024, 10:45
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "sys_config.h"
    
#define VREF_MV 3200           // Reference voltage in millivolts (3500 mV)
#define ADC_MAX_VALUE 1023     // Max ADC value for a 10-bit ADC
#define KELVIN_OFFSET 27315    // Offset to convert from Kelvin to Celsius (273.15 * 100)
    
//////////////////////////////// Prototypes ////////////////////////////////////
    
void adc_init(void);
uint16_t adc_read(void);
float adc_temp_convert(float);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

