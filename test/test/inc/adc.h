///*
// * adc.h
// *
// *  Created on: 2014Äê2ÔÂ23ÈÕ
// *      Author: zhy_jll
// */
//
//#ifndef ADC_H_
//#define ADC_H_
//#include "stm32f10x.h"
//
//#define ADC1_DR_Address    ((uint32_t)0x4001244C)
//#define ADC3_DR_Address    ((uint32_t)0x40013C4C)
//
//
//void Init_Adc();
//void RCC_Configuration();
//void GPIO_Configuration();
//
//
//#endif /* ADC_H_ */
#ifndef __ADC_H
#define __ADC_H



#include "stm32f10x.h"


void Adc1_Init(void);
void ADC1_Mode_config();
void ADC1_GPIO_Config(void);

#endif
