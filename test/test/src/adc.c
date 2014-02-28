/*
 * adc.c
 *
 *  Created on: 2014��2��26��
 *      Author: zhy_jll
 */
#include "adc.h"
__IO uint16_t ADCConvertedValue;
//#define ADC1_DR_Address    ((u32)0x40012400+0x4c)

void Adc1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_config();
}

void ADC1_GPIO_Config(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 ,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1,ENABLE);
	 RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);

}

void ADC1_Mode_config()
{
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32)&ADCConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);


	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


// #include "adc.h"
//
//void ADC1_Configuration(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	ADC_InitTypeDef ADC_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
//
//	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //��Ƶ����6ʱ��Ϊ72M/6=12MHz
//	Delay_us(1000);
//
//	/* Configure PC.01 (ADC Channel10)��PC.02 (ADC Channel11) as analog input -------------------------*/
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	ADC_DeInit(ADC1);
//
//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //����ADC�����ڶ���ģʽ
//	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;  //ɨ��ͨ��ģʽ
//	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//����������ģʽ
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	 //���������ģ��ת��
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	  //�������ұ߶���
//	ADC_InitStructure.ADC_NbrOfChannel = 2;	  //�������еĳ��ȣ�ADCͨ������Ŀ1����ΧΪ1~16��
//	ADC_Init(ADC1, &ADC_InitStructure);
//
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
//
//	ADC_DMACmd(ADC1, ENABLE); //ʹ��ADC1��DMA���� ��ԭ��ADC��û�еģ�ע�����
//
//	/* Enable ADC1 */
//	ADC_Cmd(ADC1, ENABLE);
//
//	/* Enable ADC1 reset calibaration register */
//	ADC_ResetCalibration(ADC1);		//����ָ����ADC��У׼�Ĵ���
//	/* Check the end of ADC1 reset calibration register */
//	while(ADC_GetResetCalibrationStatus(ADC1));	   //��ȡADC����У׼�Ĵ�����״̬
//	/* Start ADC1 calibaration */
//	ADC_StartCalibration(ADC1);		 //��ʼָ��ADC��У׼״̬
//	/* Check the end of ADC1 calibration */
//	while(ADC_GetCalibrationStatus(ADC1));	//�ȴ�У׼AD����
//}
//
//
//
//void DMA_Configuration(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
//{
//    DMA_InitTypeDef DMA_InitStructure;
//
// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMAʱ��
//
//    DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
//
//	//DMA1_MEM_LEN=cndtr;//����ͨ�����ݳ���
//	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA�������ַ
//	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�򣬴����跢�͵��ڴ�  DMA_CCRXλ4
//	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //�������ݿ��Ϊ16λ
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //�ڴ����ݿ��Ϊ16λ
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //������ѭ������ģʽ
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ�
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
//	DMA_Init(DMA_CHx, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
//
//}

































