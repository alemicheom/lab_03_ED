/* 
 * File:   slave_03.c
 * Author: aleja
 *
 * Created on August 5, 2022, 11:37 AM
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

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#include "spi_03.h"
#include "oscilador_01.h"
#include "tmr0_01.h"
void setup(void);

uint8_t cont_slave = 0;
uint8_t cont_slave_2 = 0; 

void __interrupt() isr (void){
    if (PIR1bits.SSPIF){

            cont_slave = spiRead();      
            cont_slave_2 = cont_slave << 1; 
            }
            PIR1bits.SSPIF = 0;             // Limpiamos bandera de interrupci n?

        return;
}

void main(void) {
    setup();
    
    while (1){
    PORTD = cont_slave;
    
    }
}

void setup(void){
    TRISC4 = 1;
    TRISD = 0;
    
    int_osc_MHz(4);
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
  
    spiInit(SPI_SLAVE_SS_DIS, SPI_DATA_SAMPLE_END, SPI_CLOCK_IDLE_HIGH, SPI_ACTIVE_2_IDLE);
    
}
