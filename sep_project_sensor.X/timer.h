/* 
 * File:   timer.h
 * Author: mpass
 *
 * Created on 3 de Outubro de 2024, 14:50
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "sys_config.h"
   
extern volatile int timer1_flag;
    
void timer1_init(void);



#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

