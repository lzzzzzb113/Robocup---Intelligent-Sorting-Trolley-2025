#include "led.h"

void Gpio_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; // 定义结构体GPIO_InitStructure

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE); // 使能PB端口时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);                                               // 使能GPIOF时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // 上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);             // GBIOB初始化

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // 上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);             // GBIOB初始化

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // 上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);             // GBIOC初始化

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // 上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);             // GBIOF初始化
}

void Iotx_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); // 使能PF端口时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // 上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);             // GBIOF初始化

  GPIO_ResetBits(GPIOF, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_12);
}
void Iorx_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE, ENABLE); // 使能GPIOA,GPIOE时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_10; // KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;            // 普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;      // 100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOE, &GPIO_InitStructure); // 初始化GPIOE2,3,4

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;         // KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;       // 普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure); // 初始化GPIOE2,3,4
}
void Led0(int b)
{
  if (b == 0)
  {
    GPIO_SetBits(GPIOF, GPIO_Pin_9);
  }
  else
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_9);
  }
}
