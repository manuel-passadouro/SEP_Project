/* 
 * File:   utils.c
 * Author: mpass
 *
 * Created on 24 de Outubro de 2024, 13:53
 */

#include "utils.h"


void led_init(){
    TRISBbits.TRISB6 = 0;   // Set RB6 as digital output
    LATBbits.LATB6 = 1;     // Set initial state to high (LED on)
}