/*
 * main.c
 *
 *  Created on: 2014��2��21��
 *      Author: zhy_jll
 */
//
#include "stm32f10x.h"
#include "led.h"
#include "lcd.h"
//#include "delay.h"
#include "sys.h"
#include "adc.h"
#include "systick.h"
#include "uart.h"
#include "stdio.h"

extern __IO uint16_t ADCConvertedValue;


#define  Channel_Number 2 // ͨ�����ĺ궨��
u16  AD_Digital_Value[Channel_Number];					//AD����ֵ
float AD_Analog_Value[Channel_Number];					//ADģ���ѹֵ

 int main(void)
 {
	 u8 i;
	 u16 data;
	 u16 k=2500;
	 char ch[]="wosi";
	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
//	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	 wchar_t ch[]="this is a test" ;
//	 char ch[]="zhanghongyan xihuan jianglingling! ";
//	 uint16_t k[3]={100,15,20};
//	 __IO uint16_t value[1];
	LED_Init();			     //LED�˿ڳ�ʼ��]
	SysTick_Init();
	Adc1_Init();
	LCD_Init();
	Uart_Config();
//	ADC1_Configuration();
	Delay_us(500);
//	DMA_Configuration(DMA1_Channel1,(u32)&ADC1->DR,(u32)AD_Digital_Value,Channel_Number );//DMA1ͨ��1������ΪADC1��
//
	POINT_COLOR=RED;
	LCD_ShowString(30,50,"STM32&ECLIPSE");
	LCD_ShowString(30,70,"-------------------------");
	LCD_ShowString(30,90,"ZhangHongYan");
	LCD_ShowString(30,110,"2014/02/22");



//	DMA_Cmd(DMA1_Channel1, ENABLE);//����DMAͨ��
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//�������ADת��

		while(1)
	{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);//�������ADת��
			while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//�ȴ�ת������
		    while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//�ȴ�������ɷ����һλ�������׶�ʧ
			DMA_ClearFlag(DMA1_FLAG_TC1); //���ͨ�� 1 ������ɱ�־
			ADC_SoftwareStartConvCmd(ADC1, DISABLE);//�������ADת��
//			 for( i=0;i<Channel_Number;i++)
//					{
//						AD_Analog_Value[i]=(float)AD_Digital_Value[i]*(3.3/4096);
//					}
//			 LCD_ShowString(60,150,"ADC_CH0_VOL:0.000V");
//			LCD_ShowNum(156,130,k,4,16);//��ʾADC1ͨ��1��ֵ��Ҳ������������0-4095
			Delay_us(500000);
			LED1(ON);		 //  ����ʹ����λ��������Ҳ����ʹ�� GPIO_ResetBits(GPIOA,GPIO_Pin_8);
			LED2(OFF); 		//	 Ҳ����ʹ��   GPIO_SetBits(GPIOD,GPIO_Pin_2);
			Delay_us(500000);
			LED1(OFF);             //	 Ҳ����ʹ��	  GPIO_SetBits(GPIOA,GPIO_Pin_8);
     		LED2(ON);			 // Ҳ����ʹ��	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;

     		data = (ADCConvertedValue&0xff00);
//     		data>>=8;
//     		ch[0] = data;
//    		USART_SendData(USART1,data);
//     		while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);

     		data = (ADCConvertedValue&0x00ff);
//     		ch[1]=data;
//     		Send_Char(ch);
//     		USART_SendData(USART1,data);
//     		while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);
     		Send_Num(ADCConvertedValue);

	}
 }




