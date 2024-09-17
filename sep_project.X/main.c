/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  PIC24FJ256GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"


void delay_ms(unsigned int milliseconds) {
    unsigned int i;
    for (i = 0; i < milliseconds; i++) {
        __delay32(16000);  // Assuming 16 MHz Fcy (instruction clock)
    }
}

void ADC_Init(void) {
    
    //Port Configuration
    TRISBbits.TRISB3 = 1; //RB3/AN5 (pin 7) as input
    ANSBbits.ANSB3 = 1; //RB3/AN5 (pin 7) as analog
    //AD1PCFG = 0xFFDF;  // Configure A/D port, AN5 input pin (RB3)
    
    // ADC Configuration
    AD1CON1bits.ADON = 0;      // Turn off ADC to configure
    AD1CON1bits.FORM = 0;      // Output format as integer
    AD1CON1bits.SSRC = 7;      // Auto-conversion
    AD1CON1bits.ASAM = 0;      // Sampling begins when SAMP bit is set
    
    AD1CON2bits.SMPI = 1;      // Interrupt after 2 conversions (ADC1BUF0)
    
    AD1CON3bits.ADCS = 0;      // ADC Conversion Clock (TAD = Tcy)
    AD1CON3bits.SAMC = 16;     // Auto-sample time = 16*TAD
    
    AD1CHSbits.CH0SA = 5;      // Select AN5 as input channel (RB3 -> AN5)
    
    AD1CON1bits.ADON = 1;      // Turn on ADC
}

void ADC_Init_alt(void) {
   ANSB = 0x0003; // Set RB3/AN5 as analog pin
   AD1CON1 = 0x0070; // SSRC bitfield is set to 0b111 to set internal counter sampling
   AD1CHS = 0x0005; // Connect RB3/AN5 as CH0 input
   AD1CSSL = 0; // Disable scan for all channels
   AD1CON3 = 0x0F00; // Sample time = 15Tad, Tad = Tcy
   AD1CON2 = 0x0004; // Set AD1IF after every 2 samples
   AD1CON1bits.ADON = 1; // Turn ADC on
}
   

int ADC_Read(void) {
    // Start sampling
    delay_ms(1);             // Wait for sampling (adjust as needed)
    AD1CON1bits.SAMP = 1;      // Start sampling
    delay_ms(1);             // Wait for sampling (adjust as needed)
    AD1CON1bits.SAMP = 0;      // Stop sampling, start conversion
    
    // Wait for the conversion to complete
    while (!AD1CON1bits.DONE);
    
    // Return the ADC result from ADC1BUF0
    return ADC1BUF0;
}


/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    ADC_Init_alt();  // Initialize the ADC

    int adcValue; // Variable to store the ADC conversion results
    int dummy;
    
    // Configure RB8 as a digital output
    TRISBbits.TRISB8 = 0;   // Set RB8 as output
    LATBbits.LATB8 = 0;     // Set initial state to low (LED off)
    
    while (1)
    {
        // Add your application code
        
        //LED Blink on pin RB8
        //LATBbits.LATB8 = 1;  // Turn LED on (assuming active high)
        //delay_ms(10);       // Delay 500ms
        
        //LATBbits.LATB8 = 0;  // Turn LED off
        //delay_ms(10);       // Delay 500ms
        
        //ADC input
        IFS0bits.AD1IF = 0; // Clear ADC interrupt flag
        AD1CON1bits.ASAM = 1; // Auto start sampling for 31Tad
        while (!IFS0bits.AD1IF); // Wait until the two conversions were performed
        AD1CON1bits.ASAM = 0; // Stop sample/convert
        adcValue = ADC1BUF0; // Retrieve first sample
        adcValue += *((&ADC1BUF0) + 1);
        adcValue = adcValue >> 2;
        dummy = adcValue;

    }

    return 1;
}
/**
 End of File
*/

