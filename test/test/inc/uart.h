/*
 * uart.h
 *
 *  Created on: 2014Äê2ÔÂ25ÈÕ
 *      Author: zhy_jll
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
//int fputc(int ch, FILE *f);
void Uart_Config(void);
void Send_Data(uint16_t buff[],int length);
//void Send_Char(char string[],int length);

void Send_Char(char string[]);


#endif /* UART_H_ */
