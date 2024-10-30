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
    
//////////////////////////////// Macros ////////////////////////////////////////
    
//////////////////////////////// Prototypes ////////////////////////////////////
    
void adc_init(void);
void adc_read(uint8_t *, uint8_t *);
float adc_temp_convert(float);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

