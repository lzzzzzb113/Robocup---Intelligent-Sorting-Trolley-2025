#ifndef __encoder_H
#define __encoder_H
#include "sys.h"
#include "stm32f4xx.h"
#include "usartx.h"
#include "delay.h"
#include "moto.h"
// LA 20.788
//pid �ṹ��
typedef struct pid_weizhi{float kp,ki,kd;}pidw;

#define  LB2  18.6318//20.12
#define  LB1  18.6318
#define  LA  18.6318//20.4
#define  LL  0
#define  Ll  15.03
#define  Lr1  16.77  //19.268
#define  Lr2  15.03  //19.268

#define  DH   0.01 //�ߵ�ƫ����ֵ
#define  DH2  0.003 //�ߵ�ƫ����ֵ
#define  BZ   10    //�ߵ�����ֵ
#define  FX   5000    //�ߵ�����
#define  JJ   2000


#define ENCODER_TIMER   TIM3  // Encoder unit connected to TIM3
#define ENCODER_IRQn   TIM3_IRQn
#define ENCODER_RCC_TIMER   RCC_APB1Periph_TIM3
#define ENCODER_GPIO_AF   GPIO_AF_TIM3


#define ENCODER_RCC_GPIO1   RCC_AHB1Periph_GPIOC
#define ENCODER_RCC_GPIO2   RCC_AHB1Periph_GPIOA
#define ENCODER_RCC_GPIO3   RCC_AHB1Periph_GPIOB
#define ENCODER_RCC_GPIO4   RCC_AHB1Periph_GPIOB
#define ENCODER_GPIO1   GPIOC    //TIM8
#define ENCODER_GPIO2   GPIOA    //TIM5
#define ENCODER_GPIO3   GPIOB    //TIM3
#define ENCODER_GPIO4   GPIOB    //TIM4



#define ENCODER_TIM_PERIOD 0xffff//���ֵԤ��Ƶ��65536-1
#define MAX_COUNT          10000//10000Ҳ����1ms�ڲ��ᳬ��10000������

#define circle_score_left1  (u16)(360/2200.0*TIM_GetCounter(TIM4))//���left
#define circle_score_right1 (u16)(360/2220.0*TIM_GetCounter(TIM3))
//���left   �ұ�right

void Encoder_Tim8_Init(void);   // PC6   PC7
void Encoder_Tim5_Init(void);   // PA0   PA1
void Encoder_Tim3_Init(void);   // PB4   PB5
void Encoder_Tim4_Init(void);   // PB6   PB7
void EncoderRead_TIM2(u16 arr, u16 psc);
void TickCount_TIM6();

void TIM8_UP_TIM13_IRQHandler(void);
void TIM5_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);
int read_encoder(void);
int Read_Encoder(u8 TIMX);

//u16  Enc_GetCount(void);
void Reset_Encoder(float encoder_num,int Speed);//Ȧ��  �ٶ�	
void Reset_Encoder_Run(u8 encoder_mode,float encoder_num,int left_speed,int right_speed);











#endif

