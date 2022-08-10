/*
 * File:   main_03.c
 * Author: aleja
 *
 * Created on August 5, 2022, 10:48 AM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <stdio.h>
#include <stdlib.h>




// librerías 
#include <xc.h>
#include "spi_03.h"
#include "tmr0_01.h"
#include "oscilador_01.h"
#include "LCD_02.h"

#define FLAG_SPI 0x0F
#define RS RE1
#define EN RE2
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
//variables 


uint8_t POT_1 = 0;
uint8_t POT_2 = 0;
uint8_t valor_pots = 0;
uint8_t bandera = 0;

uint8_t unit_POT_1 = 0;
uint8_t dec_POT_1 = 0;
uint8_t unit_POT_2 = 0;
uint8_t dec_POT_2 = 0;


//Prototipos de función 
unsigned short map(uint8_t val, uint8_t in_min, uint8_t in_max, 
            unsigned short out_min, unsigned short out_max);

unsigned short valor_POT_1 = 0;
unsigned short valor_POT_2 = 0;
char s[];


void main(void) {
    TRISD = 0; 
    PORTD = 0; 
    TRISC = 0b00010000;
    
    TRISE = 0;
    
    INTCONbits.T0IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    //funciones de configuración 
    
    int_osc_MHz (2);           // oscilador en 4 MHz 
    tmr0_init (256);           // preescaler de 256 para tmr0             
    spiInit(SPI_MASTER_OSC_DIV4,SPI_DATA_SAMPLE_MIDDLE,SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
   
    Lcd_Init();                 // función para pantalla LCD
    Lcd_Clear();
    Lcd_Set_Cursor(1,1); 
    Lcd_Write_String("  POT1    POT2"); 
           

    while (1){  
        
        spiWrite(FLAG_SPI);                         // enviar valor para empezar comunicación con Slave
        spiReceiveWait();       
        PORTCbits.RC2 = 1;                          // habilitar el esclavo 
        __delay_ms(10);  
        PORTCbits.RC2 = 0;                          // deshabilitar el esclavo 
        __delay_ms(10);
        spiReceiveWait(); 
        valor_pots = spiRead();                     // guardar en valor_pots valor de ADC de los pots 
        __delay_ms(10);

        bandera = 0b00000001 & valor_pots;          // bandera para diferenciar valor de POT1 y POT2 
        if (bandera == 1){
            POT_1 = valor_pots;                      
            valor_POT_1 = map(POT_1, 1, 255, 0, 500);      // enteros y decimales de POT1  
            unit_POT_1 = valor_POT_1/100;
            dec_POT_1 = valor_POT_1-unit_POT_1*100;
        }
        else if (bandera == 0) {
            POT_2 = valor_pots;                     
            valor_POT_2 = map(POT_2, 0, 254, 0, 500);      // enteros y decimales de POT2
            unit_POT_2 = valor_POT_2/100;
            dec_POT_2 = valor_POT_2-unit_POT_2*100;
        }

        sprintf(s, "  %d.%d    %d.%d ", unit_POT_1, dec_POT_1, unit_POT_2, dec_POT_2); 
        Lcd_Set_Cursor(2,1);    
        Lcd_Write_String(s);    
          
 
    }
}
   


unsigned short map(uint8_t x, uint8_t x0, uint8_t x1,
            unsigned short y0, unsigned short y1){
    return (unsigned short)(y0+((float)(y1-y0)/(x1-x0))*(x-x0));
}
