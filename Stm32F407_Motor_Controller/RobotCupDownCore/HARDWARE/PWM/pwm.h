#ifndef _PWM_H
#define _PWM_H
#include "sys.h"

/**************************************************************************
函数功能：pwm初始化
入口参数：arr：设为一个时钟频率的最大值  psc： 预分频值
返回  值：无
**************************************************************************/

void TIM5_PWM_Init(u32 arr,u32 psc);
void Set_PWM(int motor1,int motor2,int motot3,int motor4);
void TIM1_GPIO_Config(void);
void Dianji_Tim1_Config(uint16_t arr,uint16_t psc);
void TIM10_CH1Init(u16 psc,u16 arr);
#endif
