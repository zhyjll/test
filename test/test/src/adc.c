/*
 * adc.c
 *
 *  Created on: 2014年2月26日
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
//	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //分频因子6时钟为72M/6=12MHz
//	Delay_us(1000);
//
//	/* Configure PC.01 (ADC Channel10)，PC.02 (ADC Channel11) as analog input -------------------------*/
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	ADC_DeInit(ADC1);
//
//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //设置ADC工作在独立模式
//	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;  //扫描通道模式
//	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//工作在连续模式
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	 //软件触发来模数转换
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	  //数据向右边对齐
//	ADC_InitStructure.ADC_NbrOfChannel = 2;	  //规则序列的长度，ADC通道的数目1（范围为1~16）
//	ADC_Init(ADC1, &ADC_InitStructure);
//
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
//
//	ADC_DMACmd(ADC1, ENABLE); //使能ADC1的DMA传输 ，原本ADC上没有的，注意添加
//
//	/* Enable ADC1 */
//	ADC_Cmd(ADC1, ENABLE);
//
//	/* Enable ADC1 reset calibaration register */
//	ADC_ResetCalibration(ADC1);		//重置指定的ADC的校准寄存器
//	/* Check the end of ADC1 reset calibration register */
//	while(ADC_GetResetCalibrationStatus(ADC1));	   //获取ADC重置校准寄存器的状态
//	/* Start ADC1 calibaration */
//	ADC_StartCalibration(ADC1);		 //开始指定ADC的校准状态
//	/* Check the end of ADC1 calibration */
//	while(ADC_GetCalibrationStatus(ADC1));	//等待校准AD结束
//}
//
//
//
//void DMA_Configuration(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
//{
//    DMA_InitTypeDef DMA_InitStructure;
//
// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA时钟
//
//    DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值
//
//	//DMA1_MEM_LEN=cndtr;//保存通道数据长度
//	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设基地址
//	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA内存基地址
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从外设发送到内存  DMA_CCRX位4
//	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //外设数据宽度为16位
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //内存数据宽度为16位
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作在循环缓存模式
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
//	DMA_Init(DMA_CHx, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
//
//}

































