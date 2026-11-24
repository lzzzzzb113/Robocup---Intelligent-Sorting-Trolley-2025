#ifndef _HD_H
#define _HD_H

#include "system.h"
//右灰度
#define HL3 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4) 
#define HL1	    GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)	
#define HL4 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3) 
#define HL2   	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)	

//左灰度
#define HD2	    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)	
#define HD4 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
#define HD1 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13) 
#define HD3   	GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12)	

//后灰度
#define HHD1 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)  //后左灰度
#define HHD2 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)  //后右灰度

void HD_Init(void);	

#endif