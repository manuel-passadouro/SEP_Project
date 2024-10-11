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

#define SPI_DIR_SDO TRISGbits.TRISG8 //pin 12
#define SPI_DIR_CLK TRISGbits.TRISG6 //pin 10
#define SPI_DIR_SDI TRISGbits.TRISG7 //pin 11
#define SPI_DIR_CS TRISGbits.TRISG9  //pin 14

#define SPI_CS LATGbits.LATG9

#define DUMMY 0xAA

#define CMD_SHOW_TEMP 0xA0
#define CMD_SHOW_PROX 0xB0
#define CMD_SHOW_LIGHT 0xB1

void spi_init_master(void){
    
   
    SPI1CON1Lbits.SPIEN = 0; // Disable the SPI peripheral during configuration
    IFS0bits.SPI1IF = 0; // Clear the SPI peripheral interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the SPI peripheral interrupt flag    
    SPI1CON1bits.DISSCK = 0; // Enable generation of SCK signal
    SPI1CON1bits.DISSDO = 0; // Enable generation of SDO signal
    SPI1CON1bits.MODE16 = 0; // Set 8-bit mode
    SPI1CON1bits.SMP = 0; // Input data sampled at mid-bit
    SPI1CON1bits.CKP = 0; // Idle is SCK low
    SPI1CON1bits.CKE = 1; // Data changes on SCK falling edge
    SPI1BRGL = 79; // Baud rate divisor FCY/100k
    SPI1CON1bits.MSTEN = 1; // Set for master mode
    SPI1CON2 = 0; // Fully disable frame mode
    
    //Configure pins PPS and disable analog functionality
    
    //Disable analog functionality
    ANSGbits.ANSELG6 = 0; //Disable analog on RG6
    ANSGbits.ANSELG7 = 0; //Disable analog on RG7
    ANSGbits.ANSELG8 = 0; //Disable analog on RG8
    ANSGbits.ANSELG9 = 0; //Disable analog on RG9
    
    
    TRISGbits.TRISG6 = 0; //pin 10 CLK (output)
    TRISGbits.TRISG7 = 1; //pin 11 MISO (input)
    TRISGbits.TRISG8 = 0; //pin 12 MOSI (output)
    TRISGbits.TRISG9 = 0; //pin 14 CS (output)
    
    RPINR20bits.SDI1R  = 26; // MISO RP26 (SDI1)
    RPOR9bits.RP19R  = 7;    // MOSI RP19 (7 = SDO1)
    RPOR10bits.RP21R  = 8;    // SPI Clock RP21 (8 = SCK1OUT)
    
    LATGbits.LATG9 = 1; //Set CS high, enable slave
            
    SPI1CON1Lbits.SPIEN = 1; // enable SPI port, clear status
}

uint8_t spi_master_rw(uint8_t data_out){
    
    uint8_t miso_dummy;
    
    SPI1BUFL = data_out; // write to buffer for TX
    while(!SPI1STATLbits.SPIRBF); // wait for transfer to complete
    miso_dummy = SPI1BUFL; // read the received value
    
    SPI1BUFL = DUMMY; // write to buffer for TX (dummy)
    while(!SPI1STATLbits.SPIRBF); // wait for transfer to complete
    miso_dummy = SPI1BUFL; // read the received value
    
    SPI1BUFL = DUMMY; // write to buffer for TX
    while(!SPI1STATLbits.SPIRBF); // wait for transfer to complete
    return SPI1BUFL; // read the received value
    
}

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
    
    
    /* Call the System Initialize routine*/
    SYS_Initialize ( );
    
    spi_init_master();
    
    /* To determine how the LED and Buttons are mapped to the actual board
     * features, please see io_mapping.h. */
    LED_Enable ( LED_BLINK_ALIVE );
    LED_Enable ( LED_BUTTON_PRESSED );

    BUTTON_Enable ( BUTTON_DEMO );
    BUTTON_Enable ( BUTTON_TEMP );
    BUTTON_Enable ( BUTTON_PROX );
    
    
    /* Get a timer event once every 100ms for the blink alive. */
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_1MS );
    TIMER_RequestTick( &BlinkAliveEventHandler, 500 );
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
    
    while ( 1 )
{
        if (allowScreenUpdate == true) //check screen refresh rate
        {
            allowScreenUpdate = false; //Clear screen refresh flag
            printf("MOSI: 0X%02x      DataIn: 0X%02x\r\n", spi_data_out, spi_data_in);
        }

        if (toggleBlinkAlive == true)
        {
            LED_Toggle(LED_BLINK_ALIVE);
            toggleBlinkAlive = false;
        }
        
        /*
        if(spi_send_flag == true)
        {
            spi_send_flag = false;
            //Send data via SPI
            LATGbits.LATG9 = 0;
            spi_data_in = spi_write_byte(spi_data_out);
            LATGbits.LATG9 = 1;   
            
        }
        */
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

