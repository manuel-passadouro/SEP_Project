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


#include "sys_config.h"
#include "ioc.h"
#include "adc.h"
#include "timer.h"
#include "spi_sensor.h"
#include "i2c.h"
#include "apds9960.h"

/**
  Section: Defines
*/
//



/**
  Section: Function Declarations
*/
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

/*
                         Main application
 */
int main(void){
    
    float adc_temp;
    float dummy;
    uint16_t adc_out;
  //  uint8_t spi_data_out = 0x00;
   // uint8_t spi_data_in;
    uint8_t prox_data;
    
    //Device Initialization
    led_init();
    ioc_init();
    spi_init_slave();
    timer1_init();
    adc_init();
    i2c_master_init();
    apds9960_init();
    
   
    while (1)
    {
        // Add your application code 
       
        if(timer1_flag){
            timer1_flag = 0; //Clear Timer 1 Flag 
            
            adc_out = adc_read();
            adc_temp = adc_temp_convert(adc_out);
            prox_data = apds9960_get_prox();
            //send temp data in 2 bytes do not convert to float
            //spi_data_out[0] = adc_temp;
            spi_data_out = prox_data;
            
            LATBbits.LATB6 ^= 1; //turn on LED, mark acq complete
                
        }
        
        
        //test_sleep();
        Sleep();
       
        CLEAR_WDT; //Watchdog reset  
    }

    return 1;
}
/**
 End of File
*/

