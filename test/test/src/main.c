/*
 * main.c
 *
 *  Created on: 2014年2月21日
 *      Author: zhy_jll
 */

#include "stm32f10x.h"
#include "led.h"
#include "sys.h"
#include "adc.h"
#include "systick.h"
#include "uart.h"
#include "stdio.h"
#include "unistd.h"
#include "DS1820.h"
#include "OneWire.h"
#include "LCD5110.h"


#define  Channel_Number 2 // 通道数的宏定义
u16  AD_Digital_Value[Channel_Number];					//AD采样值
float AD_Analog_Value[Channel_Number];					//AD模拟电压值
#define MaxDevices 1
uint64_t ADRESS[MaxDevices];

 int main(void)
 {
	 char s[]="woaijianglingling";
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	LED_Init();			     //LED端口初始化]
	SysTick_Init();
	LCD_init();
	Delay_us(500);
	LCD_clear();
		while(1)
	{

			Delay_us(500000);
			LED1(ON);		 //  这里使用了位带操作，也可以使用 GPIO_ResetBits(GPIOA,GPIO_Pin_8);
			LED2(OFF); 		//	 也可以使用   GPIO_SetBits(GPIOD,GPIO_Pin_2);
//
//	        LCD_write_chinese(10,0,0);
//	        LCD_write_chinese(22,0,1);
//	        LCD_write_chinese(34,0,2);
//	        LCD_write_chinese(46,0,3);
//	        LCD_write_chinese(58,0,4);
//	        LCD_write_chinese(70,0,5);
//
//	        LCD_write_String(0,2,s);
			LCD_write_Picture(tu);
			Delay_us(500000);
			LED1(OFF);             //	 也可以使用	  GPIO_SetBits(GPIOA,GPIO_Pin_8);
     		LED2(ON);			 // 也可以使用	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;
	}
 }




