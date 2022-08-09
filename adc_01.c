#include <xc.h>



#define _XTAL_FREQ 4000000

#include "adc_01.h" 
void adc_init (uint8_t adc_cs, uint8_t vref_plus, uint8_t vref_minus){
    switch(adc_cs){
        case 0:
            ADCON0bits.ADCS = 0b00;         // Fosc/2 
            break;
        case 1:
            ADCON0bits.ADCS = 0b01;         // Fosc/8 
            break;
        case 2:
            ADCON0bits.ADCS = 0b10;         // Fosc/32
            break;
        case 3:
            ADCON0bits.ADCS = 0b11;         // Frc 
            break;
            
    }
    
    ADCON1bits.VCFG0= vref_plus;         // voltage reference bit vref_plus= 0(VSS) vref_plus = 1 (Vref-pin)
    ADCON1bits.VCFG1= vref_minus;        // voltage reference bit vref_minus= 0(VDD) vref_plus = 1 (Vref+pin)
    ADCON1bits.ADFM = 0;                 // justificado a la derecha
    PIE1bits.ADIE = 1;                   // habilitar interrupción de ADC
    PIR1bits.ADIF = 0;                   // clear interrupción de ADC
}

void adc_start(uint8_t channel){
    ADCON0bits.CHS = channel;           // seleccionar channel CHS<3:0>
    ADCON0bits.ADON = 1;                // enable ADC 
    ADCON0bits.GO = 1;                  // Iniciamos proceso de conversión 
}

uint8_t adc_read (void){
    uint8_t adc_final; 
    adc_final = ADRESH;  //concatenar ADRESH con ADRESL
    PIR1bits.ADIF = 0;
    return adc_final;
}