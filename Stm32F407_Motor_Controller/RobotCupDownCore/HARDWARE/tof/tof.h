#ifndef __TOF_H
#define __TOF_H
#include "sys.h"
 
//   绿线SCL —— PD6
//   蓝线SDA —— PD7
 
 
//管脚宏定义
//前
#define I2C_SCL_PIN            	GPIO_Pin_6
#define I2C_SCL_PORT    		    GPIOD
#define I2C_SCL_CLK       		  RCC_AHB1Periph_GPIOD
 
#define I2C_SDA_PIN             GPIO_Pin_7
#define I2C_SDA_PORT          	GPIOD
#define I2C_SDA_CLK           	RCC_AHB1Periph_GPIOD
//后
#define I2C_SCL_PIN2            GPIO_Pin_8
#define I2C_SCL_PORT2    		    GPIOC
#define I2C_SCL_CLK2       		  RCC_AHB1Periph_GPIOC
 
#define I2C_SDA_PIN2            GPIO_Pin_9
#define I2C_SDA_PORT2          	GPIOC
#define I2C_SDA_CLK2           	RCC_AHB1Periph_GPIOC
//左
#define I2C_SCL_PIN3            GPIO_Pin_10
#define I2C_SCL_PORT3    		    GPIOD
#define I2C_SCL_CLK3       		  RCC_AHB1Periph_GPIOD
 
#define I2C_SDA_PIN3            GPIO_Pin_11
#define I2C_SDA_PORT3          	GPIOD
#define I2C_SDA_CLK3           	RCC_AHB1Periph_GPIOD
//右
#define I2C_SCL_PIN4            GPIO_Pin_4
#define I2C_SCL_PORT4    		    GPIOD
#define I2C_SCL_CLK4      		  RCC_AHB1Periph_GPIOD
 
#define I2C_SDA_PIN4            GPIO_Pin_5
#define I2C_SDA_PORT4          	GPIOD
#define I2C_SDA_CLK4           	RCC_AHB1Periph_GPIOD
 
//IO操作函数
#define USERI2C_SCL_1   	GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN)
#define USERI2C_SCL_0   	GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN)
#define USERI2C_SDA_1   	GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define USERI2C_SDA_0   	GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN)

#define USERI2C_SCL2_1   	GPIO_SetBits(I2C_SCL_PORT2, I2C_SCL_PIN2)
#define USERI2C_SCL2_0   	GPIO_ResetBits(I2C_SCL_PORT2, I2C_SCL_PIN2)
#define USERI2C_SDA2_1   	GPIO_SetBits(I2C_SDA_PORT2, I2C_SDA_PIN2)
#define USERI2C_SDA2_0   	GPIO_ResetBits(I2C_SDA_PORT2, I2C_SDA_PIN2)

#define USERI2C_SCL3_1   	GPIO_SetBits(I2C_SCL_PORT3, I2C_SCL_PIN3)
#define USERI2C_SCL3_0   	GPIO_ResetBits(I2C_SCL_PORT3,I2C_SCL_PIN3)
#define USERI2C_SDA3_1   	GPIO_SetBits(I2C_SDA_PORT3, I2C_SDA_PIN3)
#define USERI2C_SDA3_0   	GPIO_ResetBits(I2C_SDA_PORT3, I2C_SDA_PIN3)

#define USERI2C_SCL4_1   	GPIO_SetBits(I2C_SCL_PORT4, I2C_SCL_PIN4)
#define USERI2C_SCL4_0   	GPIO_ResetBits(I2C_SCL_PORT4, I2C_SCL_PIN4)
#define USERI2C_SDA4_1   	GPIO_SetBits(I2C_SDA_PORT4, I2C_SDA_PIN4)
#define USERI2C_SDA4_0   	GPIO_ResetBits(I2C_SDA_PORT4, I2C_SDA_PIN4)

#define USERI2C_READ_SDA  (GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN))
#define USERI2C_READ_SDA2  (GPIO_ReadInputDataBit(I2C_SDA_PORT2, I2C_SDA_PIN2))
#define USERI2C_READ_SDA3  (GPIO_ReadInputDataBit(I2C_SDA_PORT3, I2C_SDA_PIN3))
#define USERI2C_READ_SDA4  (GPIO_ReadInputDataBit(I2C_SDA_PORT4, I2C_SDA_PIN4))
 
#define I2C_DEVID    			164//0XA4
 
 
//函数声明
void UserI2c_Stop(void);
void UserI2c_Stop2(void);
void UserI2c_Stop3(void);
void UserI2c_Stop4(void);

void UserI2c_Start(void);
void UserI2c_Start2(void);
void UserI2c_Start3(void);
void UserI2c_Start4(void);
 
void UserI2c_Init(void);
 
unsigned char SensorWritenByte(unsigned char Devid, unsigned char *TXBuff, unsigned char SubAdd, unsigned char Size);
unsigned char SensorReadnByte(unsigned char Devid, unsigned char *RXBuff, unsigned char SubAdd, unsigned char Size);
unsigned char SensorWritenByte2(unsigned char Devid, unsigned char *TXBuff, unsigned char SubAdd, unsigned char Size);
unsigned char SensorReadnByte2(unsigned char Devid, unsigned char *RXBuff, unsigned char SubAdd, unsigned char Size);
unsigned char SensorWritenByte3(unsigned char Devid, unsigned char *TXBuff, unsigned char SubAdd, unsigned char Size);
unsigned char SensorReadnByte3(unsigned char Devid, unsigned char *RXBuff, unsigned char SubAdd, unsigned char Size);
unsigned char SensorWritenByte4(unsigned char Devid, unsigned char *TXBuff, unsigned char SubAdd, unsigned char Size);
unsigned char SensorReadnByte4(unsigned char Devid, unsigned char *RXBuff, unsigned char SubAdd, unsigned char Size);
 
 
#endif