#ifndef _OLED_H
#define _OLED_H

#include "sys.h"
//#include "bmp.h"

#define	I2C_SCL_SET()  GPIO_WriteBit(GPIOA,GPIO_Pin_6,1);
#define I2C_SCL_CLR()  GPIO_WriteBit(GPIOA,GPIO_Pin_6,0);
#define I2C_SDA_SET()  GPIO_WriteBit(GPIOA,GPIO_Pin_7,1);
#define I2C_SDA_CLR()  GPIO_WriteBit(GPIOA,GPIO_Pin_7,0);
#define I2C_SDA_Read() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)

#define I2C_Ack2    0
#define I2C_NO_Ack2 1
#define OLED_CMD   0
#define OLED_DATA  1

void OLED_GPIO_Init(void);
static void I2C_Start(void);
static void I2C_Stop(void);
static unsigned char I2C_Wait_Ack(void);
static void I2C_WriteByte(unsigned char I2C_Byte);
static void OLED_Write_Cmd(unsigned char cmd);
static void OLED_Write_Data(unsigned char data);
void OLED_WR_Byte(unsigned char data,unsigned char cmd);
void OLED_Set_Pos(unsigned char x,unsigned char y);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_Clear(void);
void OLED_Init(void);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char Char);
void OLED_ShowStr(unsigned char x,unsigned char y,unsigned char *ch);
unsigned int OLED_Pow(unsigned char m,unsigned char n);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size);
void OLED_ShowChinese(unsigned char x,unsigned char y,unsigned char NO);
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t sizex,uint8_t sizey,uint8_t BMP[],uint8_t mode);
void Oled_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Refresh(void);
void Send_Byte(uint8_t dat);
#endif

