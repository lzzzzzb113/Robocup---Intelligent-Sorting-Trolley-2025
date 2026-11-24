#include "moto.h"
#include "system.h"
#include "bmp1.h"
u32 encoder_A = 0, encoder_B = 0, encoder_C = 0, encoder_D = 0, N = 0, VA = 0, VB = 0, VC = 0, VD = 0;


/**************************************************************************
函数功能：电机的PWM控制
定时器：Time1
**************************************************************************/
void TIM1_GPIO_Config(void) // 赋用端口定时器功能
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // RCC_AHB1Periph_GPIOA

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14; // 管脚设置
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);
}

// TIM1做PWM输出
void Dianji_Tim1_Config(uint16_t arr, uint16_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrecture;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); // 使能tim1

	TIM1_GPIO_Config(); // GPIO赋用

	/*开启预分配 重装载值*/
	TIM_TimeBaseInitStrecture.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStrecture.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStrecture.TIM_Prescaler = psc;
	TIM_TimeBaseInitStrecture.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStrecture.TIM_Period = arr;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStrecture);

	/*开启pwm相关配置*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_Cmd(TIM1, ENABLE);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); // 使能预分配
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE); // 使能重装载
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void TIM10_CH1Init(u16 psc, u16 arr)
{

	GPIO_InitTypeDef GPIO_InitTypeDeS;
	TIM_TimeBaseInitTypeDef TIM10_TimeBaseInitTypeDef;
	TIM_OCInitTypeDef PWM_OCInitTypeDef;
	/*结构体定义*/
	NVIC_InitTypeDef NVIC_InitStructure;
	//	/*时钟初始化*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); // GPIO 时钟初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE); // TIM 时钟初始化
	/*GPIO 口模式配置*/
	GPIO_InitTypeDeS.GPIO_Mode = GPIO_Mode_AF; // 复用功能
	GPIO_InitTypeDeS.GPIO_Pin = GPIO_Pin_6;	   // 配置 GPIOF6
	GPIO_Init(GPIOF, &GPIO_InitTypeDeS);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_TIM10); // 复用

	// 定时器模式配置
	TIM10_TimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频
	TIM10_TimeBaseInitTypeDef.TIM_Period = arr;
	TIM10_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up; // 计数模式为向上计数
	TIM10_TimeBaseInitTypeDef.TIM_Prescaler = psc - 1;
	TIM_TimeBaseInit(TIM10, &TIM10_TimeBaseInitTypeDef);
	// PWM 模式配置
	PWM_OCInitTypeDef.TIM_OCMode = TIM_OCMode_PWM1;				// PWM2 模式
	PWM_OCInitTypeDef.TIM_OutputState = TIM_OutputState_Enable; // 使能比较输出
	PWM_OCInitTypeDef.TIM_OCPolarity = TIM_OCPolarity_Low;		// 低电平有效电平
	PWM_OCInitTypeDef.TIM_Pulse = 500;
	TIM_OC1Init(TIM10, &PWM_OCInitTypeDef);

	TIM_ITConfig(TIM10, TIM_IT_CC1, ENABLE); // ③允许定时器10 更新中断
	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM10, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn; // 定时器10中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); // ④初始化 NVIC

	TIM_Cmd(TIM10, ENABLE); // 使能定时器 10
}

void Set_PWM(int motor1, int motor2, int motor3, int motor4)
{

	TIM_SetCompare1(TIM1, motor1);
	TIM_SetCompare2(TIM1, motor2);
	TIM_SetCompare3(TIM1, motor3); // 设置TIM1通道1的占空比  3000/7200
	TIM_SetCompare4(TIM1, motor4);
}
/**************************************************************************
函数功能：电机的正反转
入口参数：mode   mode=0时为正转  mode=1时反转
返回  值：无
**************************************************************************/
extern u32 encoder_A, encoder_B, encoder_C, encoder_D, N, VA, VB, VC, VD;
u32 v1 = 0, v2 = 0, v3 = 0, v4 = 0, vsum = 0, flagtr = 0;
extern int dir1, dir2, dir3, dir4;
extern float M;
void moto(int mode)
{
	if (mode == 1) // 顺时针转动
	{
		GPIO_SetBits(GPIOF, GPIO_Pin_11);	// 高电平      PF11 --- AIN2      1
		GPIO_ResetBits(GPIOC, GPIO_Pin_10); // 低电平}   PC10 --- AIN1      0

		GPIO_SetBits(GPIOB, GPIO_Pin_13);	// 高电平   PB13 --- BIN2       1
		GPIO_ResetBits(GPIOB, GPIO_Pin_12); // 低电平   PB12 --- BIN1       0

		GPIO_SetBits(GPIOB, GPIO_Pin_1);   // 高电平   PB1 --- CIN2       1
		GPIO_ResetBits(GPIOB, GPIO_Pin_0); // 低电平   PB0 --- CIN1       0

		GPIO_SetBits(GPIOC, GPIO_Pin_1);   // 高电平   PC1 --- DIN2       1
		GPIO_ResetBits(GPIOC, GPIO_Pin_0); // 低电平   PC0 --- DIN1       0
	}
	if (mode == 0) // 逆时针转动
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_10);	// 高电平       PC10 --- AIN1     1
		GPIO_ResetBits(GPIOF, GPIO_Pin_11); // 低电平}    PF11 --- AIN2     0

		GPIO_SetBits(GPIOB, GPIO_Pin_12);	// 高电平   PB12 --- BIN1     1
		GPIO_ResetBits(GPIOB, GPIO_Pin_13); // 低电平   PB13 --- BIN2        0

		GPIO_SetBits(GPIOB, GPIO_Pin_0);   // 高电平   PB0 --- CIN1       1
		GPIO_ResetBits(GPIOB, GPIO_Pin_1); // 低电平   PB1 --- CIN2       0

		GPIO_SetBits(GPIOC, GPIO_Pin_0);   // 高电平   PC0 --- DIN1       1
		GPIO_ResetBits(GPIOC, GPIO_Pin_1); // 低电平   PC1 --- DIN2       0
	}
}

void left1(int NN)
{
	if (NN == 0) // 前进
	{
		dir1 = -1;
		GPIO_SetBits(GPIOC, GPIO_Pin_10);	// 高电平       PC10 --- AIN1     1
		GPIO_ResetBits(GPIOF, GPIO_Pin_11); // 低电平}    PF11 --- AIN2     0
	}
	if (NN == 1) // 后退
	{
		dir1 = 1;
		GPIO_SetBits(GPIOF, GPIO_Pin_11);	// 高电平      PF11 --- AIN2      1
		GPIO_ResetBits(GPIOC, GPIO_Pin_10); // 低电平}   PC10 --- AIN1      0
	}
}

void left2(int NN)
{
	if (NN == 0) // 前进
	{
		dir2 = -1;
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	// 高电平   PB12 --- BIN1     1
		GPIO_ResetBits(GPIOB, GPIO_Pin_13); // 低电平   PB13 --- BIN2        0
	}
	if (NN == 1) // 后退
	{
		dir2 = 1;
		GPIO_SetBits(GPIOB, GPIO_Pin_13);	// 高电平   PB13 --- BIN2       1
		GPIO_ResetBits(GPIOB, GPIO_Pin_12); // 低电平   PB12 --- BIN1       0
	}
}

void right1(int NN)
{
	if (NN == 0) // 前进
	{
		dir3 = -1;
		GPIO_SetBits(GPIOC, GPIO_Pin_1);   // 高电平   PC1 --- DIN2       1
		GPIO_ResetBits(GPIOC, GPIO_Pin_0); // 低电平   PC0 --- DIN1       0
	}
	if (NN == 1) // 后退
	{
		dir3 = 1;
		GPIO_SetBits(GPIOC, GPIO_Pin_0);   // 高电平   PC0 --- DIN1       1
		GPIO_ResetBits(GPIOC, GPIO_Pin_1); // 低电平   PC1 --- DIN2       0
	}
}

void right2(int NN)
{
	if (NN == 0) // 前进
	{
		dir4 = -1;
		GPIO_SetBits(GPIOB, GPIO_Pin_1);   // 高电平   PB1 --- CIN2       1
		GPIO_ResetBits(GPIOB, GPIO_Pin_0); // 低电平   PB0 --- CIN1       0
	}
	if (NN == 1) // 后退
	{
		dir4 = 1;
		GPIO_SetBits(GPIOB, GPIO_Pin_0);   // 高电平   PB0 --- CIN1       1
		GPIO_ResetBits(GPIOB, GPIO_Pin_1); // 低电平   PB1 --- CIN2       0
	}
}