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
#include "bsp/rtcc.h"
 
#include "io_mapping.h"
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

static RTCC_DATETIME time;
static RTCC_DATETIME lastTime = {0};
static volatile bool toggleBlinkAlive = false;
static volatile bool send_spi_flag = false;
static volatile bool allowScreenUpdate = true; 

#define MEMCMP_VALUES_IDENTICAL 0

#define CMD_SHOW_TEMP 0xA0
#define CMD_SHOW_PROX 0xB0
#define CMD_SHOW_LIGHT 0xB1


void delay_nop(unsigned int count) {
    while (count--) {
        Nop();  // One NOP takes 1 instruction cycle
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    uint16_t adcResult;
    uint16_t lastAdcResult = 0xFFFF;
    
    uint8_t spi_data_out = 0x76;
    uint8_t spi_data_in = 0x00;
    
    uint8_t letter = 'a';
    /* Call the System Initialize routine*/
    SYS_Initialize();   
    //spi_init_master();
    uart1_init();
    
    /* To determine how the LED and Buttons are mapped to the actual board
     * features, please see io_mapping.h. */
    LED_Enable ( LED_BLINK_ALIVE );
    LED_Enable ( LED_BUTTON_PRESSED );

    BUTTON_Enable ( BUTTON_DEMO );
    BUTTON_Enable ( BUTTON_TEMP );
    BUTTON_Enable ( BUTTON_PROX );
    
    
    /* Get a timer event once every 100ms for the blink alive. */
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_1MS );
    TIMER_RequestTick( &BlinkAliveEventHandler, 100 );
    TIMER_RequestTick( &SpiSendEventHandler, 500 );
    TIMER_RequestTick( &ScreenUpdateEventHandler, 170 );
    
    /* The TIMER_1MS configuration should come before the RTCC initialization as
     * there are some processor modules that require the TIMER_1MS module to be
     * configured before the RTCC module, as the RTCC module is emulated using
     * the TIMER_1MS module. */
    time.bcdFormat = false;
    lastTime.bcdFormat = false;
    RTCC_BuildTimeGet( &time );
    RTCC_Initialize( &time );
    memset(&lastTime,0,sizeof(lastTime)); 
    
    /* Clear the screen */
    printf( "\f" );
    
    //UART config
    
    U1MODEbits.STSEL = 0; // 1-Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud disabled
    U1MODEbits.BRGH = 0; // Standard-Speed mode
    U1BRG = 103; // Baud Rate setting for 9600
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IEC0bits.U1TXIE = 0; // Enable UART TX interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
    
    //PPS for UART1 TX and RX
    
    //Disable analog functionality
    //No analog on RFx pins
    RPINR18bits.U1RXR = 10; // U1RX on pin 49 (RP10/RF4)
    //TRISFbits.TRISF4 = 1; //pin 10 CLK (input)
    
    RPOR8bits.RP17R = 3; // U1TX on pin 50 (RP17/RF5)
    //TRISFbits.TRISF5 = 0; //pin 11 MISO (output)

    //U1TXREG = 0xAA;
    U1MODEbits.UARTEN = 1; // enable UART
    
    /* Wait at least 105 microseconds (1/9600) before sending first char */
    //DELAY_105uS
    //U1TXREG = 'a'; // Transmit one character

    
    while ( 1 )
{
        /*
        while(1){
            //uart1_write('H');
            delay_nop(100000000);
            U1TXREG = 0xAA;         // Write the data to the transmit register
            LED_Toggle(LED_BLINK_ALIVE);     
        }
        */
        
        if (allowScreenUpdate == true) //check screen refresh rate
        {
            allowScreenUpdate = false; //Clear screen refresh flag
            printf("MOSI: 0X%02x      DataIn: 0X%02x\r\n", spi_data_out, spi_data_in);
        }

        if (toggleBlinkAlive == true)
        {
            letter = uart1_read();
            if (letter != NULL){
                uart1_write(letter);
            }
            LED_Toggle(LED_BLINK_ALIVE);
            toggleBlinkAlive = false;
        }
        
        
        /* To determine how the LED and Buttons are mapped to the actual board
         * features, please see io_mapping.h. */
        
        if(BUTTON_IsPressed( BUTTON_TEMP ) == true)
        {       
            //spi_send_flag = true;
            if(send_spi_flag == true){
                send_spi_flag = false;
                spi_data_out = CMD_SHOW_TEMP;
                //Send command via SPI
                LATGbits.LATG9 = 0;
                delay_nop(1000);  // Delays for 1000 instruction cycles
                spi_data_in = spi_master_rw(spi_data_out);
                LATGbits.LATG9 = 1;
            }
            
        }
       
        if(BUTTON_IsPressed( BUTTON_PROX ) == true)
        {
            //spi_send_flag = true;
            if(send_spi_flag == true){
                send_spi_flag = false;
                spi_data_out = CMD_SHOW_PROX;
                //Send command via SPI
                LATGbits.LATG9 = 0;
                delay_nop(1000);  // Delays for 1000 instruction cycles
                spi_data_in = spi_master_rw(spi_data_out);
                LATGbits.LATG9 = 1;
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

