/*
 * adc.c
 *
 *  Created on: 2014Äê2ÔÂ26ÈÕ
 *      Author: zhy_jll
 */
#include "adc.h"
__IO uint32_t ADCConvertedValue[2];
__IO uint32_t ADC_DualConvertedValueTab[16];
#define ADC1_DR_Address    ((uint32_t)0x4001244C)

void Adc1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_config();
}

void ADC1_GPIO_Config(void)
{

	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 ,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1|RCC_APB2Periph_ADC2|RCC_APB2Periph_GPIOC,ENABLE);
	 RCC_ADCCLKConfig(RCC_PCLK2_Div8);

	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_4;
	 GPIO_Init(GPIOC,&GPIO_InitStructure);

}

void ADC1_Mode_config()
{

	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADCConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 2;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode =  DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1,&ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,2,ADC_SampleTime_55Cycles5);

	ADC_DMACmd(ADC1,ENABLE);

/*   INIT ADC2*/
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_Init(ADC2,&ADC_InitStructure);

	ADC_RegularChannelConfig(ADC2,ADC_Channel_10,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC2,ADC_Channel_14,2,ADC_SampleTime_55Cycles5);

	ADC_ExternalTrigConvCmd(ADC2, ENABLE);


	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

	ADC_Cmd(ADC2,ENABLE);
	ADC_ResetCalibration(ADC2);
	while(ADC_GetResetCalibrationStatus(ADC2));
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2));
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



































