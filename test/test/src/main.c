/*
 * main.c
 *
 *  Created on: 2014年2月21日
 *      Author: zhy_jll
 */
//
#include "stm32f10x.h"
#include "led.h"
//#include "lcd.h"
//#include "delay.h"
#include "sys.h"
#include "adc.h"
#include "systick.h"
#include "uart.h"
#include "stdio.h"

extern __IO uint16_t ADCConvertedValue;

 int main(void)
 {

//	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
//	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//	 wchar_t ch[]="this is a test" ;

//	 char ch[]="zhanghongyan xihuan jianglingling! ";
//	 uint16_t k[3]={100,15,20};
//	 __IO uint16_t value[1];
	LED_Init();			     //LED端口初始化]
	SysTick_Init();
	Adc1_Init();
//	LCD_Init();
//
//	POINT_COLOR=RED;
//	LCD_ShowString(30,50,"STM32&ECLIPSE");
//	LCD_ShowString(30,70,"-------------------------");
//	LCD_ShowString(30,90,"ZhangHongYan");
//	LCD_ShowString(30,110,"2014/02/22");
//
//	LCD_ShowString(60,150,"ADC_CH0_VOL:0.000V");
	Uart_Config();

		while(1)
	{
			Delay_us(25000);
			LED1(ON);		 //  这里使用了位带操作，也可以使用 GPIO_ResetBits(GPIOA,GPIO_Pin_8);
			LED2(OFF); 		//	 也可以使用   GPIO_SetBits(GPIOD,GPIO_Pin_2);
			Delay_us(25000);
			LED1(OFF);             //	 也可以使用	  GPIO_SetBits(GPIOA,GPIO_Pin_8);
     		LED2(ON);			 // 也可以使用	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;
//    		Send_Char(ch);
 //    		value[0] = ADCConvertedValue;
//    		Send_Data(value,1);
    		USART_SendData(USART1,ADCConvertedValue);
    		while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);
	}
 }




