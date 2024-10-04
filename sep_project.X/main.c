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
#define FOSC = 8000000UL
#define FCY = (FOSC/2)
#include <libpic30.h>
#include <stdbool.h>
#include "i2c.h"
#include "apds9960.h"

/**
  Section: Defines
*/

/**
  Section: Function Declarations
*/


/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    i2c_master_init();
    apds9960_init();
    
    uint8_t prox_byte;
    //uint8_t als_high_byte;
    //uint8_t als_low_byte;
      
    // Configure RB8 as a digital output
    TRISBbits.TRISB6 = 0;   // Set RB8 as output
    LATBbits.LATB6 = 1;     // Set initial state to low (LED off)
    
    
    while (1)
    {
              
        //Read Proximity data (8 bit)
        prox_byte = apds9960_get_prox();
        
        //Read Ambient light data (16 bit)
        /*
        startCondition(); //Start write procedure
        writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
        writeByte(CDATAL_ADDR); //send register address
        stopCondition(); //End write procedure
        
        startCondition(); //Start read procedure
        writeByte(I2C_SLAVE_ADDR_READ); //send read address
        als_low_byte = readByte();
        stopCondition(); //End read procedure
          
        startCondition(); //Start write procedure
        writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
        writeByte(CDATAH_ADDR); //send register address
        stopCondition(); //End write procedure
        
        startCondition(); //Start read procedure
        writeByte(I2C_SLAVE_ADDR_READ); //send read address
        als_high_byte = readByte();
        stopCondition(); //End read procedure
        */
        
        __delay_ms(10);     
    }
    return 1;
}
/**
 End of File
*/

