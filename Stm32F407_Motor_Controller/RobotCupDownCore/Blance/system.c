#include "system.h"
const uint32_t c_uiBaud[10] = {0, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};

void systemInit(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	uart1_init(115200);
	uart2_init(115200);
	uart3_init(115200);
	uart6_init(115200);

	uart5_init(115200);

	Gpio_Init();
	Dianji_Tim1_Config(16800, 0);//168*1000*1000/16800 = 10khz

	Encoder_Tim4_Init();
	Encoder_Tim3_Init();
	Encoder_Tim8_Init();
	
	Encoder_Tim5_Init();
	EncoderRead_TIM2(50 - 1, 16800 - 1);//168*1000*1000/16800 = 10khz /50 = 200hz
	TickCount_TIM6();
}

