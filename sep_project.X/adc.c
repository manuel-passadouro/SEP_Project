/* 
 * File:   adc.h
 * Author: mpass
 *
 * Created on 1 de Outubro de 2024, 10:45
 */

#include "adc.h"

/**
 * @brief Inittialize ADC peripheral.
 *
 * @param[in] Void
 * @return void.
 */
void adc_init(void) {
   
   AD1CON5bits.BGREQ = 1;       // Enable Band Gap Voltage Reference.
   ANCFGbits.VBGEN3 = 1;
   ANSBbits.ANSB3 = 1;          // Set RB3/AN5 as analog pin (sensor output)
   
   AD1CON1 = 0x0070;            // SSRC bitfield is set to 0b111 to set internal counter sampling
   //AD1CON1bits.MODE12 = 1;    //12-bit mode
   //AD1CON2bits.PVCFG = 0b01;  // Use Vref+ as positive voltage reference
   //AD1CON2bits.NVCFG0 = 1;    // Use vref- as negative voltage reference
   
   AD1CHS = 0x0005;             // Connect RB3/AN5 as CH0 input
   AD1CSSL = 0;                 // Disable scan for all channels
   AD1CON3 = 0x0F00;            // Sample time = 15Tad, Tad = Tcy
   AD1CON2 = 0x0004;            // Set AD1IF after every 2 samples
   
   AD1CON1bits.ADON = 1;        // Turn ADC on
}
   
/**
 * @brief Perform reading with ADC.
 *
 * @param[in] Void
 * @return Integer with 10 ADC result (2 sample avarage).
 */
uint16_t adc_read(void) {
    uint16_t adcValue;
    IFS0bits.AD1IF = 0;             // Clear ADC interrupt flag
    AD1CON1bits.ASAM = 1;           // Auto start sampling for 31Tad
    while (!IFS0bits.AD1IF);        // Wait until the two conversions were performed
    AD1CON1bits.ASAM = 0;           // Stop sample/convert
    adcValue = ADC1BUF0;            // Retrieve first sample
    adcValue += *((&ADC1BUF0) + 1); //retrieve next sample (next buffer)
    adcValue = adcValue >> 1;       //Compute average
    
    return adcValue;
}

/**
 * @brief Converts an ADC value to Celsius temperature.
 *
 * @param[in] adcValue The ADC value to be converted. This is an integer
 * (cast to float). 
 * @return The temperature in degrees Celsius, calculated from the ADC value.
 */
float adc_temp_convert(float adcValue) {
    
    float adc_temp_k;
    float adc_temp_c;
    
    adc_temp_k = (adcValue/ADC_MAX_VALUE) * VREF_MV; //Convert 10 bit voltage value to Kelvin (AD592: 1mV/K)
    adc_temp_c = adc_temp_k - 273.15;                //Convert from Kelvin to Celsius
    
    return adc_temp_c;
}


