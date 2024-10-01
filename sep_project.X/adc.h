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
    
//#include <libpic30.h>
#include "mcc_generated_files/system.h"
    
#define VREF_MV 3100           // Reference voltage in millivolts (3500 mV)
#define ADC_MAX_VALUE 1023     // Max ADC value for a 10-bit ADC
#define KELVIN_OFFSET 27315    // Offset to convert from Kelvin to Celsius (273.15 * 100)
    
//////////////////////////////// Prototypes ////////////////////////////////////
    
void ADC_Init(void);
int ADC_Read(void);
float adcValueToCelsius(float);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

