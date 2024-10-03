/* 
 * File:   sys_config.h
 * Author: mpass
 *
 * Created on 1 de Outubro de 2024, 12:42
 */

#ifndef SYS_CONFIG_H
#define	SYS_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif
    


/**
  Section: Included Files
*/
//#include "mcc_generated_files/system.h"
#include <xc.h>
#include <p24FJ256GA702.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xc.h"
#include "stdint.h"
#include "adc.h"

#define FOSC 8000000UL
#define FCY (FOSC/2) // Clock speed

#include <libpic30.h>


#ifdef	__cplusplus
}
#endif

#endif	/* SYS_CONFIG_H */

