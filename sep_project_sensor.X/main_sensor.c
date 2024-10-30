/* 
 * File:   main_sensor.c
 * Author: mpass
 *
 * Created on 18 de Outubro de 2024, 16:04
 */

#include "sys_config.h"

#include <libpic30.h>

#include "utils.h"
#include "ioc.h"
#include "adc.h"
#include "timer.h"
#include "spi_sensor.h"
#include "i2c.h"
#include "apds9960.h"


volatile sensor_buffer_struct sensor_buffer = {0x00};

/*
    Main loop
 */
int main(void){
    
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
        
        //Data aquisition (every x seconds, see timer 1 config)
        if(timer1_flag){
            timer1_flag = 0;                                         //Clear Timer 1 Flag 
           
            //Temperature
            adc_read(&raw_temp_high, &raw_temp_low);                 //Get temp from ADC
            sensor_buffer.temp_data_low = raw_temp_low;
            sensor_buffer.temp_data_high = raw_temp_high;
                                
            //Proximity 
            apds9960_get_prox(&prox_data);                           //Get prox data from APDS9960
            sensor_buffer.prox_data_low = prox_data;
            sensor_buffer.prox_data_high = 0x00;
            
            //Light
            apds9960_get_light(&light_data_high, &light_data_low);   //Get prox data from APDS9960
            sensor_buffer.light_data_low = light_data_low;
            sensor_buffer.light_data_high = light_data_high;
                  
            //Red
            apds9960_get_red(&red_data_high, &red_data_low);        //Get prox data from APDS9960
            sensor_buffer.red_data_low = red_data_low;
            sensor_buffer.red_data_high = red_data_high;
            
            //Green
            apds9960_get_green(&green_data_high, &green_data_low);  //Get prox data from APDS9960
            sensor_buffer.green_data_low = green_data_low;
            sensor_buffer.green_data_high = green_data_high;
            
            //Blue
            apds9960_get_blue(&blue_data_high, &blue_data_low);    //Get prox data from APDS9960
            sensor_buffer.blue_data_low = blue_data_low;
            sensor_buffer.blue_data_high = blue_data_high;
            
            LATBbits.LATB6 ^= 1;                                   //toggle LED, mark acq complete
                
        }
                         
        Sleep();    //Enter Low Power State

        CLEAR_WDT;  //Watchdog reset  
    }

    return 1;
}
/**
 End of File
*/

