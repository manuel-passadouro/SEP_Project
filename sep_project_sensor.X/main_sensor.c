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


#include <libpic30.h>

#include "sys_config.h"
#include "utils.h"
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

volatile sensor_buffer_struct sensor_buffer = {0x00};

/*
                         Main application
 */
int main(void){
    
    float adc_temp;
    float dummy;
    uint8_t raw_temp_high, raw_temp_low;
    uint8_t prox_data;
    uint8_t light_data_high, light_data_low;
    uint8_t red_data_high, red_data_low;
    uint8_t green_data_high, green_data_low;
    uint8_t blue_data_high, blue_data_low;
    
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
       
        //Data aquisition (every x seconds, see timer 1 config)
        if(timer1_flag){
            timer1_flag = 0;                               //Clear Timer 1 Flag 
            
            //Temperature
            adc_read(&raw_temp_high, &raw_temp_low);       //Get temp from ADC
            sensor_buffer.temp_data_low = raw_temp_low;
            sensor_buffer.temp_data_high = raw_temp_high;
            
            //__delay_ms(200); //Delay for ADC integration???
            
            //Proximity 
            apds9960_get_prox(&prox_data);               //Get prox data from APDS9960
            sensor_buffer.prox_data_low = prox_data;
            sensor_buffer.prox_data_high = 0x00;
            
            //Light
            apds9960_get_light(&light_data_high, &light_data_low);               //Get prox data from APDS9960
            sensor_buffer.light_data_low = light_data_low;
            sensor_buffer.light_data_high = light_data_high;
                  
            //Red
            apds9960_get_red(&red_data_high, &red_data_low);               //Get prox data from APDS9960
            sensor_buffer.red_data_low = red_data_low;
            sensor_buffer.red_data_high = red_data_high;
            
            //Green
            apds9960_get_green(&green_data_high, &green_data_low);               //Get prox data from APDS9960
            sensor_buffer.green_data_low = green_data_low;
            sensor_buffer.green_data_high = green_data_high;
            
            //Blue
            apds9960_get_blue(&blue_data_high, &blue_data_low);               //Get prox data from APDS9960
            sensor_buffer.blue_data_low = blue_data_low;
            sensor_buffer.blue_data_high = blue_data_high;
            
            LATBbits.LATB6 ^= 1; //turn on LED, mark acq complete
                
        }
        
        //test_sleep();
        //Prepare for sleep, turn off peripherals?
        //Sleep();
       
        CLEAR_WDT; //Watchdog reset  
    }

    return 1;
}
/**
 End of File
*/

