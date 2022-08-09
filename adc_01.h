/* 
 * File:   adc_01.h
 * Author: aleja
 *
 * Created on July 22, 2022, 11:25 AM
 */

#include <xc.h>

#ifndef ADC_01_H
#define	ADC_01_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif



void adc_init (uint8_t adc_cs, uint8_t vref_plus, uint8_t vref_minus);
void adc_start(uint8_t channel);
uint8_t adc_read (void);


#endif

