#include "InitAllinOne.h"
double inlock=0.0f,inlock1=0.0f,LIGHT_RIGHT=0.0f,LIGHT_FORWORD=0.0f,inlock4=0.0f,inlock5=0.0f,LIGHT_LEFT=0.0f;
int lock1=1,lock2=1,lock3=1,lock4=1,lock5=1,lock6=1;
double my_atof(const char *str) {
    double result = 0.0;
    double fraction = 0.0;
    double divisor = 1.0;
    int sign = 1;
    int has_fraction = 0;
    int has_digits = 0;
   
    // 跳过前导空白字符（空格、制表符、换行等）
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\f' || *str == '\v') {
        str++;
    }

    // 跳过所有非数字字符，直到找到符号、数字或小数点
    while (*str != '\0' && *str != '+' && *str != '-' && *str != '.' && (*str < '0' || *str > '9')) {
        str++;
    }

    // 处理符号
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
   
    // 处理整数部分
    while (*str >= '0' && *str <= '9') {
        result = result * 10.0 + (*str - '0');
        str++;
        has_digits = 1;
    }

    // 处理小数部分
    if (*str == '.') {
        str++;
        has_fraction = 1;
        while (*str >= '0' && *str <= '9') {
            fraction = fraction * 10.0 + (*str - '0');
            divisor *= 10.0;
            str++;
            has_digits = 1;
        }
    }
    
    // 如果没有遇到任何数字，返回0.0
    if (!has_digits) {
        return 0.0;
    }
    
    // 计算最终结果
    result = result + fraction / divisor;
    
    // 返回带符号的结果
    return sign * result;
}
void NowClockSet(void) // 168MHz
{
    RCC_DeInit();

    // 启用HSE和电源接口时钟
    RCC->CR |= RCC_CR_HSEON; // 开启HSE
    while (!(RCC->CR & RCC_CR_HSERDY))
        ; // 等待HSE就绪

    // 配置电源控制寄存器
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS; // 设置调压器缩放模式

    // 配置闪存预取、指令缓存和数据缓存
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

    // 配置主PLL
    // HSE = 8MHz, PLL_M = 8, PLL_N = 336, PLL_P = 2, PLL_Q = 7
    // PLL_VCO = (HSE / PLL_M) * PLL_N = (8MHz / 8) * 336 = 336MHz
    // SYSCLK = PLL_VCO / PLL_P = 336MHz / 2 = 168MHz
    // USB OTG FS等外设时钟 = PLL_VCO / PLL_Q = 336MHz / 7 = 48MHz
    RCC->PLLCFGR = (8 << RCC_PLLCFGR_PLLM_Pos) |   // PLLM = 8
                   (336 << RCC_PLLCFGR_PLLN_Pos) | // PLLN = 336
                   (0 << RCC_PLLCFGR_PLLP_Pos) |   // PLLP = 2 (00: PLLP=2)
                   (7 << RCC_PLLCFGR_PLLQ_Pos) |   // PLLQ = 7
                   RCC_PLLCFGR_PLLSRC_HSE;         // PLL时钟源选择HSE

    // 开启PLL并等待就绪
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ;

    // 配置总线分频器
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // AHB预分频器 = 1，HCLK = 168MHz
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; // APB1预分频器 = 4，PCLK1 = 42MHz
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; // APB2预分频器 = 2，PCLK2 = 84MHz

    // 选择PLL作为系统时钟源
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
YZ_RECV_TIME UART2_RecvTime;  // UART2
YZ_RECV_TIME UART5_RecvTime;  // UART5接收时间
YZ_RECV_TIME UART6_RecvTime;  // UART6
YZ_RECV_TIME UART1_RecvTime;  // UART1
YZ_RECV_TIME UART3_RecvTime;  // UART1
YZ_RECV_TIME YZ_EXTERN_BLOCK; // 外部块
int16_t YAWRawData;
int YawReqLock = 0;
int lockStart=0;
int flag_run=0,flag_in=0,flag_out=0,flag_UPDOWN=0;
void testPrint1(char *text1)
{
	  if(strncmp(text1,"CR1",3)==0){
        flag_UPDOWN=1;
    }
    // printf("%s",text1);
    if(strncmp(text1,"START",5)==0){
        flag_out=1;
    }
		if(strncmp(text1,"OK",2)==0){
        flag_run=1;
    }
}
void testPrint2(char *text2)
{
    int st = 0;
    while (1)
    {
        if(text2[0] == 'E'){
					lock2 = 2;
					return;
				}
        if (text2[st] == '=')
        {
            st++;
            break;
        }
        st++;
    }
    double i = my_atof(&text2[st])*100;
    // printf("2: %.1f\n", i);
    LIGHT_RIGHT=i;
		lock2 =0; 
}
void testPrint3(char *text3)
{
    int st = 0;
    while (1)
    {
        if (text3[0] == 'E'){
					lock3 = 2;
					return;
				}
        if (text3[st] == '=')
        {
            st++;
            break;
        }
        st++;
    }
    double i = my_atof(&text3[st])*100;
    // printf("3: %.1f\n", i);
    LIGHT_FORWORD=i;
		lock3=0;
}

void testPrint5(char *text)
{   
    if(text[0] == 0x55 && text[1] == 0x53){
        YAWRawData = (text[7]<<8) | text[6];
        if(YawReqLock == 1){
            YawReqLock = 0;
        }
    }
}
void testPrint6(char *text6)
{

    int st = 0;
    while (1)
    {
        if (text6[0] == 'E'){
					lock6 = 2;
					return;
				}
        if (text6[st] == '=')
        {
            st++;
            break;
        }
        st++;
    }
    double i = my_atof(&text6[st])*100;
		// printf("6s: %s\n", text6);
    // printf("6: %.1f\n", i);
    LIGHT_LEFT=i;
		// printf("6c: %.1f\n", LIGHT_LEFT);
		lock6 = 0;
}
void YZ_UART_IT_RECV_listener(YZF_RECV_EVENT event, struct YZF_RECV_AREA *area, YZF_GLOBAL_INDEX dataIndex)
{
    if ((uint32_t)&UART5_RecvTime == (uint32_t)area ||(uint32_t) &UART6_RecvTime == (uint32_t)area || (uint32_t)&UART1_RecvTime == (uint32_t)area || (uint32_t)&UART2_RecvTime ==(uint32_t) area||(uint32_t) &UART3_RecvTime ==(uint32_t) area ||(uint32_t) &YZ_EXTERN_BLOCK == (uint32_t)area)
    {
        switch (event)
        {
        case recv_full:
            yzf_area_recv_add(&YZ_EXTERN_BLOCK.base, *(YZF_RECV_DATA *)yzf_global_data_get(dataIndex));
            return;
        case recv_get:
            *(YZF_RECV_DATA_INDEX *)yzf_global_data_get(dataIndex) = yzf_area_recv_get(&YZ_EXTERN_BLOCK.base);
            return;
        case recv_read_ptr:
            *(YZF_RECV_DATA **)yzf_global_data_get(dataIndex) = yzf_area_recv_get_read_ptr(&YZ_EXTERN_BLOCK.base);
            return;
        case recv_end_ptr:
            *(YZF_RECV_DATA **)yzf_global_data_get(dataIndex) = yzf_area_recv_get_end_ptr(&YZ_EXTERN_BLOCK.base);
            return;
        case recv_del:
            yzf_area_recv_del(&YZ_EXTERN_BLOCK.base, *(YZF_RECV_DATA *)yzf_global_data_get(dataIndex));
            return;
        }
    }
}
extern uint32_t SystemTickCount;
void RecvTimeInit(void)
{
    yzf_area_recv_init(&UART1_RecvTime.base, YZ_UART_IT_RECV_listener);
    yzf_area_recv_init(&UART2_RecvTime.base, YZ_UART_IT_RECV_listener);
    yzf_area_recv_init(&UART3_RecvTime.base, YZ_UART_IT_RECV_listener);
    yzf_area_recv_init(&UART5_RecvTime.base, YZ_UART_IT_RECV_listener);
    yzf_area_recv_init(&UART6_RecvTime.base, YZ_UART_IT_RECV_listener);
    yzf_area_recv_init(&YZ_EXTERN_BLOCK.base, YZ_UART_IT_RECV_listener);
    yz_area_recv_time_init(&UART1_RecvTime, 80, yz_area_recv_time_listener_default, testPrint1);
    yz_area_recv_time_init(&UART2_RecvTime, 100, yz_area_recv_time_listener_default, testPrint2);
    yz_area_recv_time_init(&UART3_RecvTime, 100, yz_area_recv_time_listener_default, testPrint3);
    yz_area_recv_time_init(&UART5_RecvTime, 10, yz_area_recv_time_listener_default, testPrint5);
    yz_area_recv_time_init(&UART6_RecvTime, 100, yz_area_recv_time_listener_default, testPrint6);
    yz_area_recv_time_init(&YZ_EXTERN_BLOCK, 100, yz_area_recv_time_listener_default, testPrint1);
}
void RecvTimeUpdate(void)
{
    yz_area_recv_time_update(&UART1_RecvTime, SystemTickCount);
    yz_area_recv_time_update(&UART2_RecvTime, SystemTickCount);
    yz_area_recv_time_update(&UART3_RecvTime, SystemTickCount);
    yz_area_recv_time_update(&UART5_RecvTime, SystemTickCount);
    yz_area_recv_time_update(&UART6_RecvTime, SystemTickCount);
}

int UART5_IRQHandler(void)
{
    unsigned char ucTemp;
    if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) // 判断是否有数据接收
    {
        ucTemp = USART_ReceiveData(UART5); // 接收数据并赋值
        UART5_RecvTime.yz_recv_listener(&UART5_RecvTime, ucTemp, SystemTickCount);
        USART_ClearITPendingBit(UART5, USART_IT_RXNE); // 把接收到的数据清零
    }
}
int USART6_IRQHandler(void)
{
    unsigned char ucTemp;
    if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET) // 判断是否有数据接收
    {
        ucTemp = USART_ReceiveData(USART6); // 接收数据并赋值
        UART6_RecvTime.yz_recv_listener(&UART6_RecvTime, ucTemp, SystemTickCount);
        USART_ClearITPendingBit(USART6, USART_IT_RXNE); // 把接收到的数据清零
    }
}

void USART1_IRQHandler(void) // 串口1中断服务程序
{
    u8 Res;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // 接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART1); //(USART1->DR);	//读取接收到的数据
        UART1_RecvTime.yz_recv_listener(&UART1_RecvTime, Res, SystemTickCount);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 把接收到的数据清零
    }
}
void USART2_IRQHandler(void) // 右
{
    u8 Res;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // 接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART2); //(USART2->DR);	//读取接收到的数据
        UART2_RecvTime.yz_recv_listener(&UART2_RecvTime, Res, SystemTickCount);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE); // 把接收到的数据清零
    }
}

void USART3_IRQHandler(void) // 左
{
    u8 Res;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) // 接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART3); //(USART3->DR);	//读取接收到的数据
        UART3_RecvTime.yz_recv_listener(&UART3_RecvTime, Res, SystemTickCount);
        USART_ClearITPendingBit(USART3, USART_IT_RXNE); // 把接收到的数据清零
    }
}
int flag_YAW=0;
double YAW_DETA=0.0f;
double fabs(float a){
   if(a<0){
       a=-a;
   }
   return a;
}
double Request_YAW(){    //180°---逆时针---0°/360°---顺时针---180°
    YawReqLock = 1;
    while(YawReqLock);
		flag_YAW++;
    if(flag_YAW==1){
        
        if(((int16_t)YAWRawData)/32768.0*180.0f+180>180){
            YAW_DETA=((int16_t)YAWRawData)/32768.0*180.0f-180;
//			printf("YAW_DETA1:%lf\n",YAW_DETA);
        
        }else{
            YAW_DETA=((int16_t)YAWRawData)/32768.0*180.0f+180;
//			printf("YAW_DETA2:%lf\n",YAW_DETA);
				}  
    }
		return ((int16_t)YAWRawData)/32768.0*180.0f+180-YAW_DETA;
}
