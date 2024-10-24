/* 
 * File:   utils.c
 * Author: mpass
 *
 * Created on 24 de Outubro de 2024, 13:53
 */

#include "utils.h"


void test_sleep(){
    
    uint8_t i = 0;
    
    Sleep();
    while(i < 5){
        LATBbits.LATB6 ^= 1;
        __delay_ms(200);
        i++;
    }
    i=0;
    while(i < 5){
        LATBbits.LATB6 ^= 1;
        __delay_ms(500);
        i++;
    }   
}

void led_init(){
    TRISBbits.TRISB6 = 0;   // Set RB6 as digital output
    LATBbits.LATB6 = 1;     // Set initial state to high (LED on)
}