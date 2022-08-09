#include <xc.h>



#include "oscilador_01.h"

void int_osc_MHz (uint8_t freq){
   
    switch(freq){                           // switch case para cambiar freq
        case 0:
            OSCCONbits.IRCF = 0b100;        // 1 MHz
            break;
        case 1:
            OSCCONbits.IRCF = 0b101;        // 2 MHz
            break;
        case 2:
            OSCCONbits.IRCF = 0b110;        // 4 MHz
            break;
        case 3:
            OSCCONbits.IRCF = 0b111;        // 8 MHz
            break;
    
    OSCCONbits.SCS = 1;                     
    }
}

