/*
 * main.c
 *
 *  Created on: 2014年2月21日
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
#include "unistd.h"

extern __IO uint16_t ADCConvertedValue;


#define  Channel_Number 2 // 通道数的宏定义
u16  AD_Digital_Value[Channel_Number];					//AD采样值
float AD_Analog_Value[Channel_Number];					//AD模拟电压值

 int main(void)
 {
	 float temp;
	 u16 k;
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
//	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//	 wchar_t ch[]="this is a test" ;
//	 char ch[]="zhanghongyan xihuan jianglingling! ";
//	 uint16_t k[3]={100,15,20};
//	 __IO uint16_t value[1];
	LED_Init();			     //LED端口初始化]
	SysTick_Init();
	Adc1_Init();
	LCD_Init();
	Uart_Config();
//	ADC1_Configuration();
	Delay_us(500);
//	DMA_Configuration(DMA1_Channel1,(u32)&ADC1->DR,(u32)AD_Digital_Value,Channel_Number );//DMA1通道1；外设为ADC1；
//
	POINT_COLOR=RED;
	LCD_ShowString(30,50,(const u8 *)"STM32&ECLIPSE");
	LCD_ShowString(30,70,(const u8 *)"-------------------------");
	LCD_ShowString(30,90,(const u8 *)"JiangLingLing");
	LCD_ShowString(30,110,(const u8 *)"2014/02/22");

	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,(const u8 *)"ADC_CH0_VAL:");
	LCD_ShowString(60,150,(const u8 *)"ADC_CH0_VOL:0.000V");

//	DMA_Cmd(DMA1_Channel1, ENABLE);//启动DMA通道
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件启动AD转换

		while(1)
	{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件启动AD转换
//			while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//等待转换结束
		    while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//等待传输完成否则第一位数据容易丢失
			DMA_ClearFlag(DMA1_FLAG_TC1); //清除通道 1 传输完成标志
			ADC_SoftwareStartConvCmd(ADC1, DISABLE);//软件启动AD转换


			Delay_us(500000);
			LED1(ON);		 //  这里使用了位带操作，也可以使用 GPIO_ResetBits(GPIOA,GPIO_Pin_8);
			LED2(OFF); 		//	 也可以使用   GPIO_SetBits(GPIOD,GPIO_Pin_2);
			Delay_us(500000);
			LED1(OFF);             //	 也可以使用	  GPIO_SetBits(GPIOA,GPIO_Pin_8);
     		LED2(ON);			 // 也可以使用	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;

     		k=ADCConvertedValue;
     		LCD_ShowNum(156,130,k,4,16);

     		temp=(float)k/4095*3.3;
     		k=temp;
     		Send_Num(k);
     		LCD_ShowNum(156,150,k,1,16);//显示电压值
    		temp=temp-k;
    		temp=temp*1000;
    		k=temp;
    		LCD_ShowNum(172,150,k,3,16);







    		Delay_us(5);
//     		Send_Float(ADCConvertedValue);
//     		printf("woshizhanghongyan\n");
//     		 printf("Hello, world!");

	}
 }




