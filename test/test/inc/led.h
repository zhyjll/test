/*
 * led.h
 *
 *  Created on: 2014��2��21��
 *      Author: zhy_jll
 */

#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"
//Mini STM32������
//LED��������
//����ԭ��@ALIENTEK
//2012/2/27

//LED�˿ڶ���

#define ON 0
#define OFF 1

#define LED1(a)  if(a)  \
					GPIO_SetBits(GPIOA,GPIO_Pin_8);\
				else    \
					GPIO_ResetBits(GPIOA,GPIO_Pin_8)


#define LED2(a)   if(a)  \
					GPIO_SetBits(GPIOD,GPIO_Pin_2);\
				  else \
					GPIO_ResetBits(GPIOD,GPIO_Pin_2)

void LED_Init(void);//��ʼ��


#endif
