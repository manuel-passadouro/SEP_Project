/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "bsp/adc.h"
#include "bsp/lcd.h"
#include "bsp/timer_1ms.h"
#include "bsp/buttons.h"
#include "bsp/leds.h"
 
#include "io_mapping.h"
#include "spi_bridge.h"
#include "uart_bridge.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************
extern void SYS_Initialize ( void ) ;
static void BlinkAliveEventHandler( void );
static void SpiSendEventHandler( void );
static void ScreenUpdateEventHandler( void );

static volatile bool toggleBlinkAlive = false;
static volatile bool send_spi_flag = false;
static volatile bool allowScreenUpdate = true; 

// *****************************************************************************
// *****************************************************************************
// Section: Main Loop
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    
    uint8_t uart_bytes_recieved; 
    char uart_rx_buff[RX_MAX_SIZE] = {0};
    char uart_tx_buff[TX_MAX_SIZE] = {0};
    char cmd = 0;
    /* Call the System Initialize routine*/
    SYS_Initialize();   
    spi_init_master();
    uart1_init();
    
    /* To determine how the LED and Buttons are mapped to the actual board
     * features, please see io_mapping.h. */
    LED_Enable ( LED_BLINK_ALIVE );
    LED_Enable ( LED_BUTTON_PRESSED );

    BUTTON_Enable ( BUTTON_DEMO );
    BUTTON_Enable ( BUTTON_TEMP );
    BUTTON_Enable ( BUTTON_PROX );
    BUTTON_Enable ( BUTTON_RGB );
    
    
    /* Get a timer event once every 100ms for the blink alive. */
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_1MS );
    TIMER_RequestTick( &BlinkAliveEventHandler, 100 );
    TIMER_RequestTick( &SpiSendEventHandler, 100 );
    TIMER_RequestTick( &ScreenUpdateEventHandler, 170 );
    
    /* Clear the screen */
    printf( "\f" );
    
    while ( 1 )
{
        
        if (allowScreenUpdate == true) //check screen refresh rate
        {
            allowScreenUpdate = false; //Clear screen refresh flag
            printf("MOSI: 0X%02x      MISO: 0X%02x 0X%02x\r\n", cmd, (unsigned char)uart_tx_buff[2], (unsigned char)uart_tx_buff[1]);

        }

        if (toggleBlinkAlive == true)
        {
            //Poll UART (non-blocking)           
            uart_bytes_recieved = uart1_read(uart_rx_buff, sizeof(uart_rx_buff));
           
            if (uart_bytes_recieved != 0){                         //If command was sent, reply with data
                cmd = uart_rx_buff[0];
                uart_tx_buff[0] = cmd;
                spi_master_handle(cmd, uart_tx_buff);              //Put sensor data in tx buffer
                uart1_write(uart_tx_buff, sizeof(uart_tx_buff));
            }
                 
            LED_Toggle(LED_BLINK_ALIVE);
            toggleBlinkAlive = false;
        }
        
        
        /* To determine how the LED and Buttons are mapped to the actual board
         * features, please see io_mapping.h. */
        
        //Debug SPI with devboard buttons
        if(BUTTON_IsPressed( BUTTON_TEMP ) == true)   //S3 button
        {       
            if(send_spi_flag == true){
                send_spi_flag = false;
                cmd = 'A';
                //Send command via SPI
                uart_tx_buff[0] = cmd;
                spi_master_handle(cmd, uart_tx_buff); //Put sensor data in tx buffer                             
            }
            
        }
       
        if(BUTTON_IsPressed( BUTTON_PROX ) == true)   //S6 button
        {
            if(send_spi_flag == true){
                send_spi_flag = false;
                cmd = 'B';
                //Send command via SPI
                uart_tx_buff[0] = cmd;
                spi_master_handle(cmd, uart_tx_buff); //Put sensor data in tx buffer
            }
        }
        
        if(BUTTON_IsPressed( BUTTON_RGB ) == true)    //S5 button
        {
            if(send_spi_flag == true){
                send_spi_flag = false;
                cmd = 'D';
                //Send command via SPI
                uart_tx_buff[0] = cmd;
                spi_master_handle(cmd, uart_tx_buff); //Put sensor data in tx buffer
            }
        }
        
    }
}

static void BlinkAliveEventHandler(void)
{    
    toggleBlinkAlive = true;
}

static void SpiSendEventHandler(void)
{    
   send_spi_flag = true;
}

static void ScreenUpdateEventHandler(void)
{
    allowScreenUpdate = true;
}

