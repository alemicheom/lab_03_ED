#include <xc.h>
#include "tmr0_01.h"

void tmr0_init (uint8_t prescaler){
    OPTION_REGbits.T0CS = 0;
    INTCONbits.T0IE = 1;                        // int para tmr0 
    INTCONbits.T0IF = 0;
    
    switch (prescaler){
        case 0:
            OPTION_REGbits.PSA = 1;             // disable prescaler para TMR0
            break;
        case 2:
            OPTION_REGbits.PSA = 0;
            OPTION_REGbits.PS = 0b000;          // 1:2
            break;
        case 4:
            OPTION_REGbits.PSA = 0;
            OPTION_REGbits.PS = 0b001;          // 1:4
            break;
        case 8:
            OPTION_REGbits.PSA = 0;
            OPTION_REGbits.PS = 0b010;          // 1:8
            break;
        case 16:
            OPTION_REGbits.PSA = 0;
            OPTION_REGbits.PS = 0b011;          // 1:16
            break;
        case 32:
            OPTION_REGbits.PSA = 0;
            OPTION_REGbits.PS = 0b100;          // 1:32
            break;
        case 64:
            OPTION_REGbits.PSA = 0;
            OPTION_REGbits.PS = 0b101;          // 1:64
            break;
        case 128:
            OPTION_REGbits.PSA = 0;
            OPTION_REGbits.PS = 0b110;          // 1:128
            break; 
        case 256:
            OPTION_REGbits.PSA = 0;
            OPTION_REGbits.PS = 0b111;          // 1:256
            break;
      
    }
    TMR0= tmr0_valor; 
}

void tmr0_reload(void){
    INTCONbits.T0IF = 0;
    TMR0 = tmr0_valor; 
}

