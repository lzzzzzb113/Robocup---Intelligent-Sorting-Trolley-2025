#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

#define USART_REC_LEN  			200  
#define EN_USART1_RX 			1		
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; 
extern u16 USART_RX_STA;         			

void uart_init(u32 bound);
void USART1_SendString(u8 *DAT, u8 len);
void USART2_SendString(u8 *DAT, u8 len);
void USART3_SendString(u8 *DAT, u8 len);
void USART6_SendString(u8 *DAT, u8 len);
#endif


