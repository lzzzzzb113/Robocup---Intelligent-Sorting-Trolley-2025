#include "usartx.h"
SEND_DATA Send_Data;
RECEIVE_DATA Receive_Data;
u8 ttl_receive;
u8 Fd_data[64];
u8 Fd_rsimu[64];
u8 Fd_rsahrs[56];
int rs_imutype = 0;
int rs_ahrstype = 0;
extern int Time_count;
/**************************************************************************
函数功能：串口1发送数据
入口参数：无
返回  值：无
**************************************************************************/
void USART1_SEND(void)
{
	unsigned char i = 0;

	for (i = 0; i < 24; i++)
	{
		usart1_send(Send_Data.buffer[i]);
	}
}
/**************************************************************************
函数功能：串口3发送数据
入口参数：无
返回  值：无
**************************************************************************/
void USART3_SEND(void)
{
	unsigned char i = 0;
	for (i = 0; i < 24; i++)
	{
		usart3_send(Send_Data.buffer[i]);
	}
}

/**************************************************************************
函数功能：串口1初始化
入口参数：无
返 回 值：无
**************************************************************************/
void uart1_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // Enable the gpio clock //使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 高速50MHZ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  // 上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);			  // 初始化

	// UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	// Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	// Subpriority //子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	// Enable the IRQ channel //IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// Initialize the VIC register with the specified parameters
	// 根据指定的参数初始化VIC寄存器
	NVIC_Init(&NVIC_InitStructure);

	// USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound;										// Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// A stop bit //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								// Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// Sending and receiving mode //收发模式
	USART_Init(USART1, &USART_InitStructure);										// Initialize serial port 1 //初始化串口1

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(USART1, ENABLE);					   // Enable serial port 1 //使能串口1
}
/**************************************************************************
函数功能：串口2初始化
入口参数：无
返回  值：无
**************************************************************************/
void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  // Enable the gpio clock  //使能GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 高速50MHZ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  // 上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);			  // 初始化

	// UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	// Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// Subpriority //子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	// Enable the IRQ channel //IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// Initialize the VIC register with the specified parameters
	// 根据指定的参数初始化VIC寄存器
	NVIC_Init(&NVIC_InitStructure);

	// USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound;										// Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// A stop bit //一个停止
	USART_InitStructure.USART_Parity = USART_Parity_No;								// Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// Sending and receiving mode //收发模式
	USART_Init(USART2, &USART_InitStructure);										// Initialize serial port 2 //初始化串口2

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(USART2, ENABLE);					   // Enable serial port 2 //使能串口2
}
/**************************************************************************
函数功能：串口3初始化
入口参数：无
返回  值：无
**************************************************************************/
void uart3_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  // Enable the gpio clock  //使能GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); // Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 高速50MHZ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  // 上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);			  // 初始化

	// UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	// Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	// Enable the IRQ channel //IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// Initialize the VIC register with the specified parameters
	// 根据指定的参数初始化VIC寄存器
	NVIC_Init(&NVIC_InitStructure);

	// USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound;										// Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// A stop bit //一个停止
	USART_InitStructure.USART_Parity = USART_Parity_No;								// Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// Sending and receiving mode //收发模式
	USART_Init(USART3, &USART_InitStructure);										// Initialize serial port 3 //初始化串口3

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(USART3, ENABLE);					   // Enable serial port 3 //使能串口3
}
/**************************************************************************
函数功能：串口5初始化
入口参数：无
返回  值：无
**************************************************************************/
void uart5_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// PC12 TX
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // Enable the gpio clock  //使能GPIO时钟
														  // PD2 RX
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // Enable the gpio clock  //使能GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); // Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 高速50MHZ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  // 上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);			  // 初始化

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 高速50MHZ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  // 上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);			  // 初始化

	// UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	// Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	// Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	// Enable the IRQ channel //IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// Initialize the VIC register with the specified parameters
	// 根据指定的参数初始化VIC寄存器
	NVIC_Init(&NVIC_InitStructure);

	// USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound;										// Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// A stop bit //一个停止
	USART_InitStructure.USART_Parity = USART_Parity_No;								// Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// Sending and receiving mode //收发模式
	USART_Init(UART5, &USART_InitStructure);										// Initialize serial port 5 //初始化串口5
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);									// Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(UART5, ENABLE);														// Enable serial port 5 //使能串口5
}
/**************************************************************************
函数功能：串口6初始化
入口参数：无
返回  值：无
**************************************************************************/
void uart6_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  // Enable the gpio clock  //使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE); // Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	  // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 高速50MHZ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  // 上拉
	GPIO_Init(GPIOG, &GPIO_InitStructure);			  // 初始化

	// UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	// Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	// Enable the IRQ channel //IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// Initialize the VIC register with the specified parameters
	// 根据指定的参数初始化VIC寄存器
	NVIC_Init(&NVIC_InitStructure);

	// USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound;										// Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// A stop bit //一个停止
	USART_InitStructure.USART_Parity = USART_Parity_No;								// Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// Sending and receiving mode //收发模式
	USART_Init(USART6, &USART_InitStructure);										// Initialize serial port 3 //初始化串口3

	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE); // Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(USART6, ENABLE);					   // Enable serial port 3 //使能串口3
}

/**************************************************************************
Function: Serial port 1 sends data
Input   : The data to send
Output  : none
函数功能：串口1发送数据
入口参数：要发送的数据
返回  值：无
**************************************************************************/
void usart1_send(u8 data)
{
	USART1->DR = data;
	while ((USART1->SR & 0x40) == 0)
		;
}
/**************************************************************************
函数功能：串口2发送数据
入口参数：要发送的数据
返回  值：无
**************************************************************************/
void usart2_send(u8 data)
{
	USART2->DR = data;
	while ((USART2->SR & 0x40) == 0)
		;
}
/**************************************************************************
函数功能：串口3发送数据
入口参数：要发送的数据
返回  值：无
**************************************************************************/
void usart3_send(u8 data)
{
	USART3->DR = data;
	while ((USART3->SR & 0x40) == 0)
		;
}

/**************************************************************************
函数功能：串口5发送数据
入口参数：要发送的数据
返回  值：无
**************************************************************************/
void Uart5Send(unsigned char *p_data, unsigned int uiSize) // 串口2数据发送
{
	unsigned int i;
	for (i = 0; i < uiSize; i++)
	{
		while (USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET)
			;							  // 判断数据发送是否完成
		USART_SendData(UART5, *p_data++); // 串口2数据发送
	}
	while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET)
		;
}
/**************************************************************************
函数功能：计算要发送/接收的数据校验结果
入口参数：Count_Number：校验的前几位数；Mode：0-对接收数据进行校验，1-对发送数据进行校验
返回  值：校验结果
**************************************************************************/
u8 Check_Sum(unsigned char Count_Number, unsigned char Mode)
{
	unsigned char check_sum = 0, k;

	// Validate the data to be sent
	// 对要发送的数据进行校验
	if (Mode == 1)
		for (k = 0; k < Count_Number; k++)
		{
			check_sum = check_sum ^ Send_Data.buffer[k];
		}

	// Verify the data received
	// 对接收到的数据进行校验
	if (Mode == 0)
		for (k = 0; k < Count_Number; k++)
		{
			check_sum = check_sum ^ Receive_Data.buffer[k];
		}
	return check_sum;
}
