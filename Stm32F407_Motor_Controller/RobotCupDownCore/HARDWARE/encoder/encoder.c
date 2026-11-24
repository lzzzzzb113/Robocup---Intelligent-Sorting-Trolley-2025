#include "encoder.h"
/*******************************************************
函数    ：把TIM1初始化为编码器接口模式
入口参数：无
返回值  ：无
********************************************************/
extern float M, H;
extern u32 encoder_A, encoder_B, encoder_C, encoder_D, N, VA, VB, VC, VD;
extern int s1, s2, s3, s4, FLAG1, FLAG2, FLAG3, FLAG4, FLAG5, ss1, ss2, ss3, ss4, llr1, llr2, llr3, llr4, flagtr;
int circle_count_right1 = 0; // 全局变量-圈数
int circle_count_left1 = 0;
int circle_count_right2 = 0; // 全局变量-圈数
int circle_count_left2 = 0;
extern u32 v1, v2, v3, v4, vsum;
int dir1, dir2, dir3, dir4;
volatile int yzsum1=0, yzsum2=0, yzsum3=0, yzsum4 =0; // A,B,C,D的编码器值
extern unsigned char devid;								 // I2C从机地址声明
extern unsigned short int length_aveval, l1, l2, l3, l4; // 用来存储长度数据
// 陀螺仪
extern float fAcc[3], fGyro[3], fAngle[3];
extern float H1, H2, H, HC, HD;
extern int flagtly;
void Encoder_Tim3_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure; // GPIO口的输入模式配置很重要，不正确的话会读不到数据
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(ENCODER_RCC_GPIO3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ENCODER_GPIO3, &GPIO_InitStructure);

	GPIO_PinAFConfig(ENCODER_GPIO3, GPIO_PinSource4, GPIO_AF_TIM3);
	GPIO_PinAFConfig(ENCODER_GPIO3, GPIO_PinSource5, GPIO_AF_TIM3);

	// 定时器设置-------------------------------------------------------------
	TIM_DeInit(ENCODER_TIMER);

	TIM_TimeBaseInitStructure.TIM_Period = 0xffff;					// 2220;	//重装载值 为计数器的值  实测一转计数器值为2230
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0;					// 预分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 时钟分频
	// TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 这里可以自己设置，或使用默认值
	TIM_TimeBaseInit(ENCODER_TIMER, &TIM_TimeBaseInitStructure); // 初始化TIM4

	// 编码器模式设置--------------------------------------------------------------
	TIM_EncoderInterfaceConfig(ENCODER_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 计数模式3

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10; // 滤波器值  15
	TIM_ICInit(ENCODER_TIMER, &TIM_ICInitStructure);

	// 溢出中断设置--------------------------------------------------------------
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	   // 清除标志位
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 更新中断

	NVIC_InitStructure.NVIC_IRQChannel = ENCODER_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Reset counter-----------------------------------------------
	TIM_SetCounter(ENCODER_TIMER, 0); // TIM3->CNT=0
	TIM_Cmd(ENCODER_TIMER, ENABLE);
}

/*******************************************************
函数    ：把TIM4初始化为编码器接口模式
入口参数：无
返回值  ：无
********************************************************/
void Encoder_Tim4_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure; // GPIO口的输入模式配置很重要，不正确的话会读不到数据
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(ENCODER_RCC_GPIO4, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(ENCODER_GPIO4, &GPIO_InitStructure);

	GPIO_PinAFConfig(ENCODER_GPIO4, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(ENCODER_GPIO4, GPIO_PinSource7, GPIO_AF_TIM4);

	// 定时器设置-------------------------------------------------------------
	TIM_DeInit(TIM4);

	TIM_TimeBaseInitStructure.TIM_Period = 0xffff;					// 重装载值 为计数器的值  实测一转计数器值为2230
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0;					// 预分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 时钟分频
	// TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 这里可以自己设置，或使用默认值
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure); // 初始化TIM4

	// 编码器模式设置--------------------------------------------------------------
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 计数模式3  TIM_ICPolarity_Falling  TIM_ICPolarity_Rising

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10; // 滤波器值
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

	// 溢出中断设置--------------------------------------------------------------
	//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM4的更新标志位
	//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许TIM4溢出中断

	TIM_ClearFlag(TIM4, TIM_FLAG_Update);	   // 清除标志位
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); // 更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Reset counter-----------------------------------------------
	TIM_SetCounter(TIM4, 0); // TIM4->CNT=0
	TIM_Cmd(TIM4, ENABLE);
}

// TIM8初始化为编码器接口模式，读取光栅尺数值
void Encoder_Tim8_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); // TIM5时钟使能
	RCC_AHB1PeriphClockCmd(ENCODER_RCC_GPIO1, ENABLE);	 // 使能PORTF时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 光栅尺
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		   // 复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		   // 开漏输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		   // 上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	   // 速度100MHz
	GPIO_Init(ENCODER_GPIO1, &GPIO_InitStructure);		   // 初始化PD

	GPIO_PinAFConfig(ENCODER_GPIO1, GPIO_PinSource6, GPIO_AF_TIM8); // 复用为TIM8
	GPIO_PinAFConfig(ENCODER_GPIO1, GPIO_PinSource7, GPIO_AF_TIM8); // 复用为TIM8

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					// 定时器分频
	TIM_TimeBaseStructure.TIM_Period = 0xffff;					// 自动重装载值 0xFFFF 65535
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);				// 初始化TIM5

	// 编码器模式1 – 根据TI1FP1的电平，计数器在TI2FP2的边沿向上/下计数。
	TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 编码器接口模式配置
	TIM_ICStructInit(&TIM_ICInitStructure);																  // 默认值赋值
	TIM_ICInitStructure.TIM_ICFilter = 10;																  // 滤波 0x0~0xF
	TIM_ICInit(TIM8, &TIM_ICInitStructure);																  // 初始化

	//	TIM_ClearFlag(TIM8, TIM_FLAG_Update);//清除标志位
	//	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE); //更新中断
	TIM_ClearFlag(TIM8, TIM_FLAG_Update);	   // 清除标志位
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE); // 更新中断

	TIM_SetCounter(TIM8, 0); // 计数器清零
	TIM_Cmd(TIM8, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;	 // 添加中断函数
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; // 抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		 // 子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

// TIM5初始化为编码器接口模式，读取光栅尺数值
void Encoder_Tim5_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); // TIM5时钟使能
	RCC_AHB1PeriphClockCmd(ENCODER_RCC_GPIO2, ENABLE);	 // 使能PORTF时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // 光栅尺
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		   // 复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		   // 开漏输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		   // 上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	   // 速度100MHz
	GPIO_Init(ENCODER_GPIO2, &GPIO_InitStructure);		   // 初始化PA

	GPIO_PinAFConfig(ENCODER_GPIO2, GPIO_PinSource0, GPIO_AF_TIM5); // 复用为TIM9
	GPIO_PinAFConfig(ENCODER_GPIO2, GPIO_PinSource1, GPIO_AF_TIM5); // 复用为TIM9

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;					// 定时器分频
	TIM_TimeBaseStructure.TIM_Period = 65535;					// 自动重装载值 0xFFFF 65535
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);				// 初始化TIM5

	// 编码器模式1 – 根据TI1FP1的电平，计数器在TI2FP2的边沿向上/下计数。
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 编码器接口模式配置
	TIM_ICStructInit(&TIM_ICInitStructure);																  // 默认值赋值
	TIM_ICInitStructure.TIM_ICFilter = 10;																  // 滤波 0x0~0xF
	TIM_ICInit(TIM5, &TIM_ICInitStructure);																  // 初始化

	TIM_ClearFlag(TIM5, TIM_FLAG_Update);	   // 清除标志位
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); // 更新中断

	TIM_SetCounter(TIM5, 0); // 计数器清零
	TIM_Cmd(TIM5, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;				 // 添加中断函数
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; // 抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		 // 子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void EncoderRead_TIM2(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitStrue.TIM_Period = arr;
	TIM_TimeBaseInitStrue.TIM_Prescaler = psc;					// 预分频系数，决定每一个计数的时长
	TIM_TimeBaseInitStrue.TIM_CounterMode = TIM_CounterMode_Up; // 计数模式：向上计
	TIM_TimeBaseInitStrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStrue);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_InitStrue.NVIC_IRQChannel = TIM2_IRQn; // 属于 TIM2 中断
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE; // 中断使能
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStrue);

	TIM_Cmd(TIM2, ENABLE);
}

void TickCount_TIM6(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	TIM_TimeBaseInitStrue.TIM_Period = 1000-1;
	TIM_TimeBaseInitStrue.TIM_Prescaler = 84-1;
	TIM_TimeBaseInitStrue.TIM_CounterMode = TIM_CounterMode_Up; // 计数模式：向上计
	TIM_TimeBaseInitStrue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStrue);
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

	NVIC_InitStrue.NVIC_IRQChannel = TIM6_DAC_IRQn; // 属于 TIM2 中断
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE; // 中断使能
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStrue);

	TIM_Cmd(TIM6, ENABLE);
}


extern int SpeedPID_UPDATE(int VA,int VB,int VC,int VD,int sumA,int sumB,int sumC,int sumD);
void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == 1) // 当发生中断时状态寄存器(TIMx_SR)
	{
		v1 = Read_Encoder(8);
		VA = v1;
		v2 = Read_Encoder(5);
		VB = v2;
		v3 = Read_Encoder(3);
		VC = v3;
		v4 = Read_Encoder(4);
		VD = v4;
		yzsum1 += v1;yzsum2 += v2;yzsum3 += v3;yzsum4 += v4;
		if(SpeedPID_UPDATE(VA,VB,VC,VD,yzsum1,yzsum2,yzsum3,yzsum4)==0){
			yzsum1 = 0;
			yzsum2 = 0;
			yzsum3 = 0;
			yzsum4 = 0;
		};
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 状态寄存器(TIMx_SR)的 bit0
}


uint32_t SystemTickCount = 0;
void TIM6_DAC_IRQHandler(void){
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET) // 中断标志位
	{
		SystemTickCount++;
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update); // 清除中断标志位
	}
}
void TickDelay_MS(uint32_t ms){
	uint32_t EndTick = SystemTickCount + ms;
	while(SystemTickCount < EndTick){};
}

volatile int16_t N4 = 0, N3 = 0, N8 = 0, N9 = 0;
void TIM4_IRQHandler(void) // 溢出中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) // 中断标志位
	{
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update); // 清除中断标志位
}

void TIM3_IRQHandler(void) // 溢出中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) // 中断标志位
	{

		// zitai();
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // 清除中断标志位
}

void TIM8_UP_TIM13_IRQHandler(void) // 溢出中断
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) == SET) // 中断标志位
	{
	}
	TIM_ClearITPendingBit(TIM8, TIM_IT_Update); // 清除中断标志位
}

void TIM5_IRQHandler(void) // 溢出中断
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET) // 中断标志位
	{
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update); // 清除中断标志位
}
// TIM_GetCounter(TIM4);//读取计数器的值
// TIM_SetCounter(TIM4,100);//设置计数器的值（自定义值函数）
// Encoder=TIM_GetCounter(TIM4)*2230/360+360*circle_count_right;//当前角度  计算公式  未实验

// 读取定时器计数值
int read_encoder(void)
{
	int encoder_num;
	encoder_num = (int)((int16_t)(TIM4->CNT)); // 这里尤其需要注意数据类型
	TIM_SetCounter(TIM4, 0);
	return encoder_num;
}

// 读取定时器计数值2
int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;
	switch (TIMX)
	{
	case 8:
		Encoder_TIM = (short)TIM8->CNT;
		TIM8->CNT = 0;
		break; // TIM8 -> CNT=0;
	case 5:
		Encoder_TIM = (short)TIM5->CNT;
		TIM5->CNT = 0;
		break;
	case 3:
		Encoder_TIM = (short)TIM3->CNT;
		TIM3->CNT = 0;
		break;
	case 4:
		Encoder_TIM = (short)TIM4->CNT;
		TIM4->CNT = 0;
		break;
	default:
		Encoder_TIM = 0;
	}
	// TIM8 -> CNT=0;TIM5 -> CNT=0;TIM3 -> CNT=0;TIM4 -> CNT=0;
	// if(Encoder_TIM>0xefff)  Encoder_TIM=0xffff-Encoder_TIM;
	// if (Encoder_TIM < 0)
	// 	Encoder_TIM = -Encoder_TIM - LL;
	return Encoder_TIM;
}

// u16   Enc_GetCount(void)  //未调试过此函数
//{
////	static  u16   lastCount = 0;
////	u16  curCount = ENCODER_TIMER->CNT;//获取编码值
////	u32 dAngle = curCount - lastCount;
////	if(dAngle >= MAX_COUNT)
////	{
////			dAngle -= ENCODER_TIM_PERIOD;
////	}
////	else if(dAngle < (-MAX_COUNT))
////	{
////			dAngle += ENCODER_TIM_PERIOD;
////	}
////	lastCount = curCount;
////	return (u16)dAngle;
//}

// Reset_Encoder(2.36,100); 2.36=2圈+360度=2.360=3
void Reset_Encoder(float encoder_num, int Speed) // 圈数  速度
{
	int integer; // 整数
	int decimal; // 小数
	integer = (int)encoder_num;
	decimal = (encoder_num - integer) * 1000;
	TIM_Cmd(TIM2, DISABLE);
#if 1
	TIM_Cmd(TIM3, DISABLE);
	TIM_Cmd(TIM4, ENABLE);
	circle_count_left1 = 0;
	TIM_SetCounter(TIM4, 0); // 设置计数器的值（自定义值函数）
	while (1)
	{
		if (Speed > 90)
		{
			//	high_run(Speed);
		}
		if (Speed <= 90)
		{
			//	slow_run(Speed);
		}
		if ((circle_count_left1 >= integer) && (circle_score_left1 >= decimal))
			break;
	}

	circle_count_left1 = 0;
	TIM_SetCounter(TIM4, 0); // 设置计数器的值（自定义值函数）
	TIM_Cmd(TIM4, DISABLE);
#elif 0

	TIM_Cmd(TIM4, DISABLE);
	TIM_Cmd(TIM3, ENABLE);
	circle_count_right = 0;
	TIM_SetCounter(TIM3, 0); // 设置计数器的值（自定义值函数）
	while (1)
	{
		if (Speed > 90)
		{
			high_run(Speed);
		}
		if (Speed <= 90)
		{
			slow_run(Speed);
		}
		if ((circle_count_right >= integer) && (circle_score_right >= decimal))
			break;
	}

	//	circle_count_right=0;
	TIM_Cmd(TIM3, DISABLE);
#endif
}

void Reset_Encoder_Run(u8 encoder_mode, float encoder_num, int left_speed, int right_speed) // 圈数  速度	不循迹
{
	int integer; // 整数
	int decimal; // 小数
	TIM_Cmd(TIM2, DISABLE);
	integer = (int)encoder_num;
	decimal = (encoder_num - integer) * 1000;
	if (encoder_mode == 1)
	{
		TIM_Cmd(TIM3, ENABLE);
		circle_count_right1 = 0;
		TIM_SetCounter(TIM3, 0); // 设置计数器的值（自定义值函数）
		while (1)
		{
			// Run_differ(left_speed,right_speed);
			if ((circle_count_right1 >= integer) && (circle_score_right1 >= decimal))
				break;
		}
		circle_count_right1 = 0;
		TIM_Cmd(TIM3, DISABLE);
	}
	else if (encoder_mode == 0)
	{
		TIM_Cmd(TIM4, ENABLE);
		circle_count_left1 = 0;
		TIM_SetCounter(TIM4, 0); // 设置计数器的值（自定义值函数）
		while (1)
		{
			// Run_differ(left_speed,right_speed);
			if ((circle_count_left1 >= integer) && (circle_score_left1 >= decimal))
				break;
		}
		//	circle_count_right=0;
		TIM_Cmd(TIM4, DISABLE);
	}
}
