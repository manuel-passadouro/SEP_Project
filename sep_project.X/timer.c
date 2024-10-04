/* 
 * File:   timer.h
 * Author: mpass
 *
 * Created on 3 de Outubro de 2024, 14:50
 */

#include "timer.h"

volatile int timer1_flag = 0;  // Global flag for Timer1 interrupt

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
 
    IFS0bits.T1IF = 0;      //Clear Interrupt Flag
    timer1_flag = 1;
}

void timer1_init(void) {
    
    TMR1 = 0;                   //Clear Timer 1
    PR1 = 605;                  //Timer period (1210 = 10s)
        
    T1CONbits.TON = 0;          // Disable timer for config
    T1CONbits.TCS = 1;          // 0 = Use FOSC/2, 1 = Use other clock
    T1CONbits.TECS= 0b10;       // Use LPRC (31 kHz)
    T1CONbits.TCKPS = 0b11;     // Prescaler 1:256
    
    IFS0bits.T1IF = 0;          // Clear interrupt flag
    IEC0bits.T1IE = 1;          // Enable timer interrupt
    IPC0bits.T1IP = 4;          // Timer1 Interrupt Priority (default = 4)

    T1CONbits.TON = 1;          // Enable timer
}
