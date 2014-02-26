///*
// * adc.c
// *
// *  Created on: 2014年2月23日
// *      Author: zhy_jll
// */
//
//#include "adc.h"
//#include "stm32f10x.h"
//extern uint16_t ADC1ConvertedValue;
//
//void Init_Adc()
//{
//
//	RCC_Configuration();
//	GPIO_Configuration();
//
//	/*DMA1 CHANNEL1 CONFIGUARTION*/
//	DMA_InitTypeDef DMA_InitStructure;
//	DMA_DeInit(DMA1_Channel1);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
//	DMA_InitStructure.DMA_PeripheralDataSize = (uint32_t) &ADC1ConvertedValue;
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_BufferSize = 1;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
////	DMA_Cmd(DMA1_Channel1,ENABLE);
//
//	/*ADC1 CONFIGURATION*/
//	ADC_InitTypeDef ADC_InitStructure;
//	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;    //独立模式
//	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//	ADC_InitStructure.ADC_NbrOfChannel = 1;
//	ADC_Init(ADC1,&ADC_InitStructure);
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_28Cycles5 );
//	ADC_DMACmd(ADC1,ENABLE);
//
//	ADC_Cmd(ADC1,ENABLE);
//	ADC_ResetCalibration(ADC1);
//	while(ADC_GetResetCalibrationStatus(ADC1));
//	ADC_StartCalibration(ADC1);
//	while(ADC_GetCalibrationStatus(ADC1));
//	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//}
//
//void RCC_Configuration()
//{
//	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
//
//}
//
//
//void GPIO_Configuration(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//
//  /* Configure PA0(ADC1 Channel0) as analog inputs */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//}
