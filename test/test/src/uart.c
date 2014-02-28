/*
 * uart.c
 *
 *  Created on: 2014年2月25日
 *      Author: zhy_jll
 */

#include "uart.h"



//int fputc(int ch, FILE *f)
//{
// /* 将 Printf 内容发往串口 */
//
//	USART_SendData(USART1, (unsigned char) ch);
//
//	while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);
//	return (ch);
//}


#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;

};

FILE __stdout;

//重定义fputc函数
int fputc(int ch, FILE *f)
{
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕
    USART1->DR = (u8) ch;
	return ch;
}





void Uart_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);

}


void Send_Data(uint16_t buff[],int length)
{
	int l;
	for(l=0;l<length;l++)
	{
		USART_SendData(USART1,buff[l]);
		while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);
	}

}


//void Send_Char(char string[],int length)
//{
//	int ch[length];
//	uint16_t buff[length];
//	int i;
//	int a;
//	for(i=0;i<length;i++)
//	{
//		a=string[i];
//		ch[i]=a;
//	}
//
//	for(i=0;i<length;i++)
//	{
//		buff[i] = ch[i]&0x00ff;
//		USART_SendData(USART1,buff[i]);
//		while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);
//	}
//
//}


void Send_Char(char string[])
{
	int length = strlen(string);
	int ch[length];
	uint16_t buff[length];
	int i;
	int a;
	for(i=0;i<length;i++)
	{
		a=string[i];
		ch[i]=a;
	}

	for(i=0;i<length;i++)
	{
		buff[i] = ch[i]&0x00ff;
		USART_SendData(USART1,buff[i]);
		while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);
	}
}


void Send_Num(uint16_t buff)
{
	char ch[7]="0000  ";
//	uint16_t buff=3050;
	u8 qianwei,baiwei,shiwei,gewei,c,d;
	u8 i;
	uint16_t b;
	qianwei=buff/1000;
	b=buff%1000;
	baiwei=b/100;
	c=b%100;
	shiwei=c/10;
	d=c%10;
	gewei=d;
	ch[0] = qianwei;
	ch[1] = baiwei;
	ch[2] = shiwei;
	ch[3] = gewei;
	for(i=0;i<4;i++)
		ch[i]=ch[i]+48;
	Send_Char(ch);
}
