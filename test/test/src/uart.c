/*
 * uart.c
 *
 *  Created on: 2014Äê2ÔÂ25ÈÕ
 *      Author: zhy_jll
 */

#include "uart.h"

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

void Send_Char(char string[])
{
	int length = strlen(string);
	int ch[length];
	uint16_t buff[length];
	int i;
	int a;
	for(i=0;i<length;i++)
	{
		ch[i]=string[i];
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
	char ch[7];
//	uint16_t data;
//	data = buff & 0x0fff;
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
	ch[4]='\n';
	ch[5]='\0';
//	sprintf(ch,"%d",data);
//	ch[4]='\n';
	Send_Char(ch);
}



void Send_Float(uint16_t buff)
{
	char s[10];
	float AD_Analog_Value;
	AD_Analog_Value=(float)buff/4096*3.3;
	sprintf(s,"%f",AD_Analog_Value); // float to char
	s[5]=' ';
	s[6]=' ';
	s[7]='\n';
	Send_Char(s);
}

//int _write (int fd, char *ptr, int len)
//{
//  /* Write "len" of char from "ptr" to file id "fd"
//   * Return number of char written.
//   * Need implementing with UART here. */
//	int i;
//	char ch[]="woshizhang";
//	for(i=0;i<5;i++)
//	{
//		ptr[i]=0;
//		USART_SendData(USART1,ch[i]);
////		while( USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
//	}
//  return len;
//}
