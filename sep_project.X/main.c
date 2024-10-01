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
#define FCY 16000000UL
#include <libpic30.h>
#include <stdbool.h>

/**
  Section: Defines
*/

#define I2C_SLAVE_ADDR_READ 0x73
#define I2C_SLAVE_ADDR_WRITE 0x72

#define I2C_READ 1
#define I2C_WRITE 0

#define ID_ADDR 0x94 //Sensro ID (R)

//Config Registers
#define PIHT_ADDR 0x8B //Proximity interrupt high threshold (R/W)
#define ENABLE_ADDR 0x80 //Enable Interrupts and states (R/W)
#define CONTROL_ADDR 0x8F //Gain control (R/W)
#define GCONFIG1_ADDR 0xA2 //Gesture config 1 (R/W)
#define GCONFIG3_ADDR 0xAA //Gesture config 3 (R/W)
#define GCONFIG4_ADDR 0xAB //Gesture config 4 (R/W)

//Data Registers
#define PDATA_ADDR 0x9C //Proximty Data (R)
#define CDATAH_ADDR 0x95 //High byte of clear channel data (R)
#define CDATAL_ADDR 0x94 //Low byte of clear channel data (R)
#define GSTATUS_ADDR 0xAF //Gesture Status
#define GFIFO_U_ADDR 0xFC //Gesture FIFO UP
#define GFIFO_D_ADDR 0xFD //Gesture FIFO DOWN
#define GFIFO_L_ADDR 0xFE //Gesture FIFO LEFT
#define GFIFO_R_ADDR 0xFF //Gesture FIFO RIGHT




/**
  Section: Function Declarations
*/

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
    // Limpa a flag de interrupção
    IFS0bits.T1IF = 0;

    // Código que será executado a cada x segundos
    
}

void Timer1_Init(void) {

     // 0 = 0
    T1CONbits.TON = 1;          // 1- Liga o Timer1
    // T1CONbits.TSYNC          // 2 - TCS = 0
    T1CONbits.TCS = 0;          // Usa o clock interno (Fosc/4)
     // 3 = 0
    T1CONbits.TCKPS = 0b11;     // 5,4 -  Prescaler 1:256
    T1CONbits.TGATE = 0;        // 6 - Modo de gate desligado
     // 7 = 0
     // T1CONbits.TECS=             // 9,8 - timer type
     // 12,11,10 = 0
    T1CONbits.TSIDL = 0;        // 13- Idle
     // 14 = 0
    T1CONbits.TON = 0;          // 15- Desliga o Timer1 enquanto configura
    


    PR1 = y;                 // Definir o período do Timer1 (x segundos)
    TMR1 = 0;                   // Zera o contador do Timer1

    IPC0bits.T1IP = 4;          // Prioridade da interrupção do Timer1
    IFS0bits.T1IF = 0;          // Limpa a flag de interrupção do Timer1
    IEC0bits.T1IE = 1;          // Habilita a interrupção do Timer1

    T1CONbits.TON = 1;          // 15- Ligar o Timer1 enquanto configura
 
}

void delay_ms(unsigned int milliseconds) {
    unsigned int i;
    for (i = 0; i < milliseconds; i++) {
        __delay32(16000);  // Assuming 16 MHz Fcy (instruction clock)
    }
}

 

void i2c_master_init(void){
    
    I2C1CONLbits.I2CEN = 0; // Disable I2C peripheral during setup
    I2C1CONLbits.A10M = 0; // 7 bit address mode
    I2C1BRG = 0x12; // 400KHz (FCY = 16 MHz)
    
    // Configure I2C pins on pre-defined IOs
    //ANSBbits.ANSB8 = 0;
    ANSBbits.ANSB9 = 0; //Disable analog on RB9
  
    TRISBbits.TRISB8 = 1;    // Set RB8 (SCL1) as input
    TRISBbits.TRISB9 = 1;    // Set RB9 (SDA1) as input
    ODCBbits.ODCB8 = 1;      // Set RB8 (SCL1) as open-drain
    ODCBbits.ODCB9 = 1;      // Set RB9 (SDA1) as open-drain
    
    I2C1CONLbits.I2CEN = 1; //enable I2C1
}

void startCondition(){
    
    I2C1CONLbits.SEN = 1; // Initiate the start condition on SDA and SCL pins
    while(I2C1CONLbits.SEN ); // Wait till sequence is completed
} 
void stopCondition(){
    
    I2C1CONLbits.PEN = 1; // Initiate the stop condition on SDA and SCL pins
    while(I2C1CONLbits.PEN); // Wait till sequence is completed
} 

uint8_t writeByte(uint8_t data){
    
    //startCondition();
    I2C1TRN = data; // Move data to the I2CxTRN register, transmission starts right after
    __delay_ms(20); // Wait till a complete byte is transmitted
    
    if(!I2C1STATbits.ACKSTAT){ // Check for the slave acknowledge
        return 0; // No error code
    }
    return -1; // Error code
    
    
} 

uint8_t readByte(){
    
    I2C1CONLbits.RCEN = 1; // Assert the receive enable bit
    __delay_ms(20); // Wait till a complete byte is transmitted
    if(I2C1STATbits.RBF){// Check if the receive buffer is full
        return I2C1RCV; // Return the received data
    }    
    return -1; // Error code
} 


/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    i2c_master_init();
    
    uint8_t read_data;
    uint8_t als_high_byte;
    uint8_t als_low_byte;
    uint8_t test_data;
    uint8_t gstatus_data;
    uint8_t sensor_gain = 0x03; //2 = 16x ASL gain
    uint8_t enable_byte = 0x47; //Enable Gesture, Prox, ALS.
    uint8_t gconfig1_byte = 0x00; //Enable gesture interrupts and exit mask.
    uint8_t gconfig4_byte = 0x01; //Enable gesture engine.
    
    
    
    bool start_flag = 0;
    bool g_valid = 0;

    
    // Configure RB8 as a digital output
    TRISBbits.TRISB6 = 0;   // Set RB8 as output
    LATBbits.LATB6 = 1;     // Set initial state to low (LED off)
    
    
    while (1)
    {
              
        //Get ID from sensor
        //LATBbits.LATB6 = 0;
        if (!start_flag){
            //Enable proximity and light detection
            startCondition(); //Start write procedure
            writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
            writeByte(ENABLE_ADDR); //send register address
            writeByte(enable_byte);
            stopCondition(); //End write procedure
            
            //Set snesor gain
            startCondition(); //Start write procedure
            writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
            writeByte(CONTROL_ADDR); //send register address
            writeByte(sensor_gain);
            stopCondition(); //End write procedure
            
            /*
             * //Set ADC time
            startCondition(); //Start write procedure
            writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
            writeByte(CONTROL_ADDR); //send register address
            writeByte(sensor_gain);
            stopCondition(); //End write procedure
             */
            
            startCondition(); //Start write procedure
            writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
            writeByte(GCONFIG1_ADDR); //send register address
            writeByte(gconfig1_byte);
            stopCondition(); //End write procedure
            
            startCondition(); //Start write procedure
            writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
            writeByte(GCONFIG4_ADDR); //send register address
            writeByte(gconfig4_byte);
            stopCondition(); //End write procedure
            
            start_flag = 1;
        }
        
        
        //Read Ambient light data
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
        
        startCondition(); //Start write procedure
        writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
        writeByte(GSTATUS_ADDR); //send register address
        stopCondition(); //End write procedure
        
        startCondition(); //Start read procedure
        writeByte(I2C_SLAVE_ADDR_READ); //send read address
        gstatus_data = readByte();
        g_valid = gstatus_data & 1;
        stopCondition(); //End read procedure
        
        if(g_valid){
            startCondition(); //Start write procedure
            writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
            writeByte(GFIFO_U_ADDR); //send register address
            stopCondition(); //End write procedure

            startCondition(); //Start read procedure
            writeByte(I2C_SLAVE_ADDR_READ); //send read address
            test_data = readByte();
            stopCondition(); //End read procedure
            
            __delay_ms(10);
            
            startCondition(); //Start write procedure
            writeByte(I2C_SLAVE_ADDR_WRITE); //send write address
            writeByte(GSTATUS_ADDR); //send register address
            stopCondition(); //End write procedure

            startCondition(); //Start read procedure
            writeByte(I2C_SLAVE_ADDR_READ); //send read address
            gstatus_data = readByte();
            g_valid = gstatus_data & 1;
            stopCondition(); //End read procedure
            
            if(test_data){
                //LATBbits.LATB6 = 1;
                LATBbits.LATB6 ^= 1;  // Toggle LATB6
            }
            
            //LATBbits.LATB6 = 1;
        }
        else{
            LATBbits.LATB6 ^= 1;  // Toggle LATB6
        }
        
             
        //LATBbits.LATB6 = 1; 
        __delay_ms(10);
          
        
    }

    return 1;
}
/**
 End of File
*/

