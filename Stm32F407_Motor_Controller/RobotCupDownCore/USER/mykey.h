#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#define KEY_PIN 			GPIO_Pin_15
#define KEY_PORT 			GPIOA
#define KEYL_PIN 			GPIO_Pin_12
#define KEYL_PORT 			GPIOF
#define KEYR_PIN 			GPIO_Pin_2
#define KEYR_PORT 			GPIOF
void Mykey_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    // 配置PA15为输入模式
    GPIO_InitStructure.GPIO_Pin = KEY_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉输入
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = KEYL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉输入
    GPIO_Init(KEYL_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = KEYR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉输入
    GPIO_Init(KEYR_PORT, &GPIO_InitStructure);
}
