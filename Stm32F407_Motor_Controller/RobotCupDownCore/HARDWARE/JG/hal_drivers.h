/****************************************************************************************
* Copyright (C), 2020-2030,MyAntenna Tech. Co.,Ltd.
* 文件名： hal_drivers.h
* 描   述：MCU接口驱动定义
* 作   者：pamala           
* 版   本：V1.0
* 日   期: 2020.2.15
*****************************************************************************************/
#ifndef __X_HAL_DRIVERS_H_X__
#define __X_HAL_DRIVERS_H_X__

#include "stm32f4xx_usart.h"
#include "delay.h"

#define  L1MOD_USART   (USART2)   //L1模组串口号
//#define  DEBUG_USART   (USART2)   //调试串口号

#define  DEBUG_USART   (USART1)   //调试串口号


void Init_SysTick(void);              //初始化时钟
void Usart_Write_Bytes(USART_TypeDef* USARTx, unsigned char *pdata, int length);    //串口发送数据
void Usart_PutString(char *str);
void delay_test(void);                 //延时函数
#endif

