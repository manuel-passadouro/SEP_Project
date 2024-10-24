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

#define FOSC 8000000UL
#define FCY (FOSC/2)    // System Clock speed

#include <libpic30.h>
    
//#define T1CK 35000UL                   //Timer1 Clock speed
#define CLEAR_WDT __builtin_clrwdt()     //WDT Reset macro
//#define ENTER_SLEEP __builtin_pwrsav(0); // Sleep mode


#ifdef	__cplusplus
}
#endif

#endif	/* SYS_CONFIG_H */

