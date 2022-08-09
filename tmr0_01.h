/* 
 * File:   tmr0_01.h
 * Author: aleja
 *
 * Created on July 26, 2022, 5:13 PM
 */

#ifndef TMR0_01_H
#define	TMR0_01_H

#include <xc.h>
#define _XTAL_FREQ 4000000
#define tmr0_valor 158
void tmr0_init (uint8_t prescaler);
void tmr0_reload(void);

#endif
