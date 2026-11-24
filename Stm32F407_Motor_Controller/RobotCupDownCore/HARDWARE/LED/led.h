#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED端口定义
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 

//

#define BY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)	 //是(0)否(1)是干扰站 1
#define BY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10) //是(1)否(0)放完球   2
#define BY3 		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) //是(1)否(0)分类完   3
//IO发                 1                              0
#define JT1(x) do{x?GPIO_SetBits(GPIOF,GPIO_Pin_0): GPIO_ResetBits(GPIOF,GPIO_Pin_0);}while(0) //是(1)否(0)到二维码 4
#define JT2(x) do{x?GPIO_SetBits(GPIOF,GPIO_Pin_2): GPIO_ResetBits(GPIOF,GPIO_Pin_2);}while(0) //开左(0)/右门(1)    5
#define JT3(x) do{x?GPIO_SetBits(GPIOF,GPIO_Pin_12): GPIO_ResetBits(GPIOF,GPIO_Pin_12);}while(0)//是(1)否(0)停放完  6

#define JT(x)  do{x?GPIO_SetBits(GPIOF,GPIO_Pin_9): GPIO_ResetBits(GPIOF,GPIO_Pin_9);}while(0)

void LED_Init(void);//初始化		 
void Gpio_Init(void);
void Iotx_init(void);
void Iorx_init(void);
void Led0(int  b);
#endif
