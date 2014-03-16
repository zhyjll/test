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
#include "sys.h"
#include "adc.h"
#include "systick.h"
#include "uart.h"
#include "stdio.h"
#include "unistd.h"

extern __IO uint32_t ADCConvertedValue[2];
extern __IO uint32_t ADC_DualConvertedValueTab[16];


#define  Channel_Number 2 // 通道数的宏定义
u16  AD_Digital_Value[Channel_Number];					//AD采样值
float AD_Analog_Value[Channel_Number];					//AD模拟电压值

 int main(void)
 {
	 float temp,Ad_Analog_Value[3];
	 u16 cache[4];
	 u32 cach[16];
	 u8 i;
	 u16 k,m;
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz

	LED_Init();			     //LED端口初始化]
	SysTick_Init();
	Adc1_Init();
	LCD_Init();
	Uart_Config();

	Delay_us(500);

	POINT_COLOR=RED;
	LCD_ShowString(30,50,(const u8 *)"STM32&ECLIPSE");
	LCD_ShowString(30,70,(const u8 *)"-------------------------");
	LCD_ShowString(30,90,(const u8 *)"JiangLingLing");
	LCD_ShowString(30,110,(const u8 *)"2014/02/22");

	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,(const u8 *)"ADC_CH1_VAL:");
	LCD_ShowString(60,150,(const u8 *)"ADC_CH1_VOL:0.000V");
	LCD_ShowString(60,170,(const u8 *)"ADC_CH10_VAL:");
	LCD_ShowString(60,190,(const u8 *)"ADC_CH10_VOL:0.000V");
	LCD_ShowString(60,210,(const u8 *)"ADC_CH2_VAL:");
	LCD_ShowString(60,230,(const u8 *)"ADC_CH2_VOL:0.000V");

	Delay_us(20000);//这个地方特定添加延时 不然显示屏没有显示


		while(1)
	{
			  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

			  /* Test on DMA1 channel1 transfer complete flag */
			  while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
			  /* Clear DMA1 channel1 transfer complete flag */
			  DMA_ClearFlag(DMA1_FLAG_TC1);


			Delay_us(500000);
			LED1(ON);		 //  这里使用了位带操作，也可以使用 GPIO_ResetBits(GPIOA,GPIO_Pin_8);
			LED2(OFF); 		//	 也可以使用   GPIO_SetBits(GPIOD,GPIO_Pin_2);
			Delay_us(500000);
			LED1(OFF);             //	 也可以使用	  GPIO_SetBits(GPIOA,GPIO_Pin_8);
     		LED2(ON);			 // 也可以使用	  GPIO_ResetBits(GPIOD,GPIO_Pin_2) ;


     		for(i=0;i<2;i++)
     		{
     			cach[i] = ADCConvertedValue[i];
     		}

     		cache[0] = cach[0] & 0x0000ffff;    //ADC1-PA1
     		cache[1] = (cach[0]>>16) & 0x0000ffff;  //ADC1-PA2
     		cache[2] = cach[1] & 0x0000ffff;       //ADC2-PC0
     		cache[3] = (cach[1]>>16) & 0x0000ffff;   //ADC2-PC4

     		Send_Num(cache[0]);
     		Send_Num(cache[1]);
     		Send_Num(cache[2]);
     		Send_Num(cache[3]);

     		k=cache[0];
     		LCD_ShowNum(156,130,k,4,16);
     		temp=(float)k/4095*3.3;
     		k=temp;
     		Send_Num(k);
     		LCD_ShowNum(156,150,k,1,16);//显示电压值
    		temp=temp-k;
    		temp=temp*1000;
    		k=temp;
    		LCD_ShowNum(172,150,k,3,16);

    		Delay_us(5000);//这个延时也必须保证足够大，不然显示屏依然不工作
    		m=cache[1];
     		LCD_ShowNum(164,170,m,4,16);
     		temp=(float)m/4095*3.3;
     		m=temp;
     		Send_Num(m);
     		LCD_ShowNum(164,190,m,1,16);//显示电压值
    		temp=temp-m;
    		temp=temp*1000;
    		m=temp;
    		LCD_ShowNum(180,190,m,3,16);
    		Delay_us(5000);//这个延时也必须保证足够大，不然显示屏依然不工作

    		m=cache[2];
    		LCD_ShowNum(156,210,m,4,16);
    		temp=(float)m/4095*3.3;
    		m=temp;
    		Send_Num(m);
    		LCD_ShowNum(156,230,m,1,16);//显示电压值
    		temp=temp-m;
    		temp=temp*1000;
    		m=temp;
    		LCD_ShowNum(172,230,m,3,16);
    		Delay_us(5000);//这个延时也必须保证足够大，不然显示屏依然不工作


	}
 }




