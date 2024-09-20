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

/**
  Section: Defines
*/

#define VREF_MV 3500           // Reference voltage in millivolts (3500 mV)
#define ADC_MAX_VALUE 1023     // Max ADC value for a 10-bit ADC
#define KELVIN_OFFSET 27315    // Offset to convert from Kelvin to Celsius (273.15 * 100)

/**
  Section: Function Declarations
*/

void delay_ms(unsigned int milliseconds) {
    unsigned int i;
    for (i = 0; i < milliseconds; i++) {
        __delay32(16000);  // Assuming 16 MHz Fcy (instruction clock)
    }
}



void ADC_Init(void) {
   ANSB = 0x0003; // Set RB3/AN5 as analog pin
   AD1CON1 = 0x0070; // SSRC bitfield is set to 0b111 to set internal counter sampling
   AD1CHS = 0x0005; // Connect RB3/AN5 as CH0 input
   AD1CSSL = 0; // Disable scan for all channels
   AD1CON3 = 0x0F00; // Sample time = 15Tad, Tad = Tcy
   AD1CON2 = 0x0004; // Set AD1IF after every 2 samples
   AD1CON1bits.ADON = 1; // Turn ADC on
}
   
/**
 * @brief Perform reading with ADC.
 *
 * @param[in] Void
 * @return Integer with 10 ADC result (2 sample avarage).
 */
int ADC_Read(void) {
    int adcValue;
    int dummy;
    IFS0bits.AD1IF = 0; // Clear ADC interrupt flaggthy
    AD1CON1bits.ASAM = 1; // Auto start sampling for 31Tad
    while (!IFS0bits.AD1IF); // Wait until the two conversions were performed
    AD1CON1bits.ASAM = 0; // Stop sample/convert
    adcValue = ADC1BUF0; // Retrieve first sample
    adcValue += *((&ADC1BUF0) + 1); //retrieve next sample (next buffer)
    adcValue = adcValue >> 1;
    
    return adcValue;
}

/**
 * @brief Converts an ADC value to Celsius temperature.
 *
 * @param[in] adcValue The ADC value to be converted. This is an integer
 *                     representing the raw ADC reading. 
 * @return The temperature in degrees Celsius, calculated from the ADC value.
 */
float adcValueToCelsius(float adcValue) {
    
    float adc_temp_k;
    float adc_temp_c; 
    
    adc_temp_k = (adcValue/1024) * 3300;
    adc_temp_c = adc_temp_k - 273.15;
    
    return adc_temp_c;
}



/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    ADC_Init();  // Initialize the ADC

    float adc_temp; // Variable to store the ADC conversion results
    float adc_out;
    float dummy;
    // Configure RB8 as a digital output
    TRISBbits.TRISB6 = 0;   // Set RB8 as output
    LATBbits.LATB6 = 1;     // Set initial state to low (LED off)
    
    while (1)
    {
        // Add your application code
        
        //ADC input
            
        adc_out = ADC_Read();
        adc_temp = adcValueToCelsius((float)adc_out);
        dummy = adc_temp;
    }

    return 1;
}
/**
 End of File
*/

