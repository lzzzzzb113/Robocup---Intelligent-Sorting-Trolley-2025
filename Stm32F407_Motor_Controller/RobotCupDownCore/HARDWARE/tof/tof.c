#include "tof.h"
#include "delay.h"
 
#include "usart.h"
 
//变量定义
unsigned char devid;
unsigned int i2cread_interval;
unsigned char dirt_send_flag;
unsigned char dirt_detection_flag;
unsigned short int length_val;
unsigned short int length_aveval,l1,l2,l3,l4;
 
 
void UserI2c_Start(void)
{
    USERI2C_SDA_1;
    delay_us(5);
    USERI2C_SCL_1;
    delay_us(5);
    USERI2C_SDA_0;  //START:when CLK is high,DATA change form high to low
    delay_us(5);
    USERI2C_SCL_0;  //钳住I2C总线，准备发送或接收数据
    delay_us(30);  //加30uS延时
}
void UserI2c_Start2(void)
{
    USERI2C_SDA2_1;
    delay_us(5);
    USERI2C_SCL2_1;
    delay_us(5);
    USERI2C_SDA2_0;  //START:when CLK is high,DATA change form high to low
    delay_us(5);
    USERI2C_SCL2_0;  //钳住I2C总线，准备发送或接收数据
    delay_us(30);  //加30uS延时
}
void UserI2c_Start3(void)
{
    USERI2C_SDA3_1;
    delay_us(5);
    USERI2C_SCL3_1;
    delay_us(5);
    USERI2C_SDA3_0;  //START:when CLK is high,DATA change form high to low
    delay_us(5);
    USERI2C_SCL3_0;  //钳住I2C总线，准备发送或接收数据
    delay_us(30);  //加30uS延时
}
void UserI2c_Start4(void)
{
    USERI2C_SDA4_1;
    delay_us(5);
    USERI2C_SCL4_1;
    delay_us(5);
    USERI2C_SDA4_0;  //START:when CLK is high,DATA change form high to low
    delay_us(5);
    USERI2C_SCL4_0;  //钳住I2C总线，准备发送或接收数据
    delay_us(30);  //加30uS延时
}
 
void UserI2c_Stop(void)
{
    USERI2C_SCL_0;
    USERI2C_SDA_0;//STOP:when CLK is high DATA change form low to high
    delay_us(5);
    USERI2C_SCL_1;
    delay_us(5);
    USERI2C_SDA_1;  //发送I2C总线结束信号
    delay_us(5);
 
    delay_us(30);   //加30uS延时
}
void UserI2c_Stop2(void)
{
    USERI2C_SCL2_0;
    USERI2C_SDA2_0;//STOP:when CLK is high DATA change form low to high
    delay_us(5);
    USERI2C_SCL2_1;
    delay_us(5);
    USERI2C_SDA2_1;  //发送I2C总线结束信号
    delay_us(5);
 
    delay_us(30);   //加30uS延时
}
void UserI2c_Stop3(void)
{
    USERI2C_SCL3_0;
    USERI2C_SDA3_0;//STOP:when CLK is high DATA change form low to high
    delay_us(5);
    USERI2C_SCL3_1;
    delay_us(5);
    USERI2C_SDA3_1;  //发送I2C总线结束信号
    delay_us(5);
 
    delay_us(30);   //加30uS延时
}
void UserI2c_Stop4(void)
{
    USERI2C_SCL4_0;
    USERI2C_SDA4_0;//STOP:when CLK is high DATA change form low to high
    delay_us(5);
    USERI2C_SCL4_1;
    delay_us(5);
    USERI2C_SDA4_1;  //发送I2C总线结束信号
    delay_us(5);
 
    delay_us(30);   //加30uS延时
}
 

unsigned char UserI2c_Wait_Ack(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned short int ucErrTime = 0;
    unsigned char RetValue;
 
    //SDA设置为输入
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉 //上拉输入
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
 
    USERI2C_SCL_0;
    delay_us(5);
    USERI2C_SCL_1;
 
    ucErrTime = 10000;
 
    while( ucErrTime-- > 0 )
    {
        if(USERI2C_READ_SDA )
        {
            RetValue = 0;
        }
        else
        {
            RetValue = 1;
            break;
        }
    }
 
    delay_us(1);
    USERI2C_SCL_0;//时钟输出0
 
    //SDA线输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //配置IO的输出速度为50MHz，高低电平状态最高切换频率
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
 
    USERI2C_SDA_0;
    delay_us(30);     //加30uS延时
    return RetValue;
}

unsigned char UserI2c_Wait_Ack2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned short int ucErrTime = 0;
    unsigned char RetValue;
 
    //SDA设置为输入
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉 //上拉输入
    GPIO_Init(I2C_SDA_PORT2, &GPIO_InitStructure);
 
    USERI2C_SCL2_0;
    delay_us(5);
    USERI2C_SCL2_1;
 
    ucErrTime = 10000;
 
    while( ucErrTime-- > 0 )
    {
        if(USERI2C_READ_SDA2 )
        {
            RetValue = 0;
        }
        else
        {
            RetValue = 1;
            break;
        }
    }
 
    delay_us(1);
    USERI2C_SCL2_0;//时钟输出0
 
    //SDA线输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //配置IO的输出速度为50MHz，高低电平状态最高切换频率
    GPIO_Init(I2C_SDA_PORT2, &GPIO_InitStructure);
 
    USERI2C_SDA2_0;
    delay_us(30);     //加30uS延时
    return RetValue;
}
unsigned char UserI2c_Wait_Ack3(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned short int ucErrTime = 0;
    unsigned char RetValue;
 
    //SDA设置为输入
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉 //上拉输入
    GPIO_Init(I2C_SDA_PORT3, &GPIO_InitStructure);
 
    USERI2C_SCL3_0;
    delay_us(5);
    USERI2C_SCL3_1;
 
    ucErrTime = 10000;
 
    while( ucErrTime-- > 0 )
    {
        if(USERI2C_READ_SDA3 )
        {
            RetValue = 0;
        }
        else
        {
            RetValue = 1;
            break;
        }
    }
 
    delay_us(1);
    USERI2C_SCL3_0;//时钟输出0
 
    //SDA线输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //配置IO的输出速度为50MHz，高低电平状态最高切换频率
    GPIO_Init(I2C_SDA_PORT3, &GPIO_InitStructure);
 
    USERI2C_SDA2_0;
    delay_us(30);     //加30uS延时
    return RetValue;
}
unsigned char UserI2c_Wait_Ack4(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned short int ucErrTime = 0;
    unsigned char RetValue;
 
    //SDA设置为输入
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉 //上拉输入
    GPIO_Init(I2C_SDA_PORT4, &GPIO_InitStructure);
 
    USERI2C_SCL4_0;
    delay_us(5);
    USERI2C_SCL4_1;
 
    ucErrTime = 10000;
 
    while( ucErrTime-- > 0 )
    {
        if(USERI2C_READ_SDA4 )
        {
            RetValue = 0;
        }
        else
        {
            RetValue = 1;
            break;
        }
    }
 
    delay_us(1);
    USERI2C_SCL4_0;//时钟输出0
 
    //SDA线输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //配置IO的输出速度为50MHz，高低电平状态最高切换频率
    GPIO_Init(I2C_SDA_PORT4, &GPIO_InitStructure);
 
    USERI2C_SDA4_0;
    delay_us(30);     //加30uS延时
    return RetValue;
}
 
void useri2c_ack(void)
{
    USERI2C_SCL_0;
    USERI2C_SDA_0;
    delay_us(5);
    USERI2C_SCL_1;
    delay_us(5);
    USERI2C_SCL_0;
    delay_us(30);     //加30uS延时
}
void useri2c_ack2(void)
{
    USERI2C_SCL2_0;
    USERI2C_SDA2_0;
    delay_us(5);
    USERI2C_SCL2_1;
    delay_us(5);
    USERI2C_SCL2_0;
    delay_us(30);     //加30uS延时
}
void useri2c_ack3(void)
{
    USERI2C_SCL3_0;
    USERI2C_SDA3_0;
    delay_us(5);
    USERI2C_SCL3_1;
    delay_us(5);
    USERI2C_SCL3_0;
    delay_us(30);     //加30uS延时
}
void useri2c_ack4(void)
{
    USERI2C_SCL4_0;
    USERI2C_SDA4_0;
    delay_us(5);
    USERI2C_SCL4_1;
    delay_us(5);
    USERI2C_SCL4_0;
    delay_us(30);     //加30uS延时
}

void useri2c_nack(void)
{
    USERI2C_SCL_0;
    USERI2C_SDA_1;
    delay_us(5);
    USERI2C_SCL_1;
    delay_us(5);
    USERI2C_SCL_0;
    delay_us(30);     //加30uS延时
}
void useri2c_nack2(void)
{
    USERI2C_SCL2_0;
    USERI2C_SDA2_1;
    delay_us(5);
    USERI2C_SCL2_1;
    delay_us(5);
    USERI2C_SCL2_0;
    delay_us(30);     //加30uS延时
}
void useri2c_nack3(void)
{
    USERI2C_SCL3_0;
    USERI2C_SDA3_1;
    delay_us(5);
    USERI2C_SCL3_1;
    delay_us(5);
    USERI2C_SCL3_0;
    delay_us(30);     //加30uS延时
}
void useri2c_nack4(void)
{
    USERI2C_SCL4_0;
    USERI2C_SDA4_1;
    delay_us(5);
    USERI2C_SCL4_1;
    delay_us(5);
    USERI2C_SCL4_0;
    delay_us(30);     //加30uS延时
}
 
void UserI2c_Send_Byte(unsigned char txd)
{
    unsigned char t;
 
    USERI2C_SCL_0;//拉低时钟开始数据传输
    delay_us(5);
 
    for(t = 0; t < 8; t++)
    {
        if((txd & 0x80) >> 0)
            USERI2C_SDA_1;
        else
            USERI2C_SDA_0;
 
        txd <<= 1;
        delay_us(5);
        USERI2C_SCL_1;
        delay_us(5);
        USERI2C_SCL_0;
    }
}
void UserI2c_Send_Byte2(unsigned char txd)
{
    unsigned char t;
 
    USERI2C_SCL2_0;//拉低时钟开始数据传输
    delay_us(5);
 
    for(t = 0; t < 8; t++)
    {
        if((txd & 0x80) >> 0)
            USERI2C_SDA2_1;
        else
            USERI2C_SDA2_0;
 
        txd <<= 1;
        delay_us(5);
        USERI2C_SCL2_1;
        delay_us(5);
        USERI2C_SCL2_0;
    }
}
void UserI2c_Send_Byte3(unsigned char txd)
{
    unsigned char t;
 
    USERI2C_SCL3_0;//拉低时钟开始数据传输
    delay_us(5);
 
    for(t = 0; t < 8; t++)
    {
        if((txd & 0x80) >> 0)
            USERI2C_SDA3_1;
        else
            USERI2C_SDA3_0;
 
        txd <<= 1;
        delay_us(5);
        USERI2C_SCL3_1;
        delay_us(5);
        USERI2C_SCL3_0;
    }
}
void UserI2c_Send_Byte4(unsigned char txd)
{
    unsigned char t;
 
    USERI2C_SCL4_0;//拉低时钟开始数据传输
    delay_us(5);
 
    for(t = 0; t < 8; t++)
    {
        if((txd & 0x80) >> 0)
            USERI2C_SDA4_1;
        else
            USERI2C_SDA4_0;
 
        txd <<= 1;
        delay_us(5);
        USERI2C_SCL4_1;
        delay_us(5);
        USERI2C_SCL4_0;
    }
}

unsigned char UserI2c_Read_Byte(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char i, receive = 0;
 
    //SDA设置为输入
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
 
    USERI2C_SDA_1;
    USERI2C_SCL_0;
    delay_us(30);
 
    for(i = 0; i < 8; i++ )
    {
        receive <<= 1;
        USERI2C_SCL_1;
        delay_us(5);
 
        if(USERI2C_READ_SDA)
            receive++;
 
        USERI2C_SCL_0;
        delay_us(5);
    }
 
    USERI2C_SCL_0;
 
    //SDA线输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
 
    return receive;
}
unsigned char UserI2c_Read_Byte2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char i, receive = 0;
 
    //SDA设置为输入
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(I2C_SDA_PORT2, &GPIO_InitStructure);
 
    USERI2C_SDA2_1;
    USERI2C_SCL2_0;
    delay_us(30);
 
    for(i = 0; i < 8; i++ )
    {
        receive <<= 1;
        USERI2C_SCL2_1;
        delay_us(5);
 
        if(USERI2C_READ_SDA2)
            receive++;
 
        USERI2C_SCL2_0;
        delay_us(5);
    }
 
    USERI2C_SCL2_0;
 
    //SDA线输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SDA_PORT2, &GPIO_InitStructure);
 
    return receive;
}
unsigned char UserI2c_Read_Byte3(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char i, receive = 0;
 
    //SDA设置为输入
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(I2C_SDA_PORT3, &GPIO_InitStructure);
 
    USERI2C_SDA3_1;
    USERI2C_SCL3_0;
    delay_us(30);
 
    for(i = 0; i < 8; i++ )
    {
        receive <<= 1;
        USERI2C_SCL3_1;
        delay_us(5);
 
        if(USERI2C_READ_SDA3)
            receive++;
 
        USERI2C_SCL3_0;
        delay_us(5);
    }
 
    USERI2C_SCL3_0;
 
    //SDA线输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SDA_PORT3, &GPIO_InitStructure);
 
    return receive;
}
unsigned char UserI2c_Read_Byte4(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char i, receive = 0;
 
    //SDA设置为输入
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(I2C_SDA_PORT4, &GPIO_InitStructure);
 
    USERI2C_SDA4_1;
    USERI2C_SCL4_0;
    delay_us(30);
 
    for(i = 0; i < 8; i++ )
    {
        receive <<= 1;
        USERI2C_SCL4_1;
        delay_us(5);
 
        if(USERI2C_READ_SDA4)
            receive++;
 
        USERI2C_SCL4_0;
        delay_us(5);
    }
 
    USERI2C_SCL4_0;
 
    //SDA线输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SDA_PORT4, &GPIO_InitStructure);
 
    return receive;
}
unsigned char SensorWritenByte(unsigned char Devid, unsigned char *TXBuff, unsigned char SubAdd, unsigned char Size)
{
    unsigned char i = 0;
 
    UserI2c_Start();
 
    UserI2c_Send_Byte( Devid | 0x00 );
 
    if( 0 == UserI2c_Wait_Ack() )
    {
        UserI2c_Stop();
        return 0;
    }
 
    UserI2c_Send_Byte( SubAdd & 0xff );
 
    if( 0 == UserI2c_Wait_Ack() )
    {
        UserI2c_Stop();
        return 0;
    }
 
    for ( i = 0; i < Size; i++)
    {
        UserI2c_Send_Byte( TXBuff[Size - i - 1] );
 
        if( 0 == UserI2c_Wait_Ack() )
        {
            UserI2c_Stop();
            return 0;
        }
    }
 
    UserI2c_Stop();
 
    return 1;
}

unsigned char SensorWritenByte2(unsigned char Devid, unsigned char *TXBuff, unsigned char SubAdd, unsigned char Size)
{
    unsigned char i = 0;
 
    UserI2c_Start2();
 
    UserI2c_Send_Byte2( Devid | 0x00 );
 
    if( 0 == UserI2c_Wait_Ack2() )
    {
        UserI2c_Stop2();
        return 0;
    }
 
    UserI2c_Send_Byte2( SubAdd & 0xff );
 
    if( 0 == UserI2c_Wait_Ack2() )
    {
        UserI2c_Stop2();
        return 0;
    }
 
    for ( i = 0; i < Size; i++)
    {
        UserI2c_Send_Byte2( TXBuff[Size - i - 1] );
 
        if( 0 == UserI2c_Wait_Ack2() )
        {
            UserI2c_Stop2();
            return 0;
        }
    }
 
    UserI2c_Stop2();
 
    return 1;
}
unsigned char SensorWritenByte3(unsigned char Devid, unsigned char *TXBuff, unsigned char SubAdd, unsigned char Size)
{
    unsigned char i = 0;
 
    UserI2c_Start3();
 
    UserI2c_Send_Byte3( Devid | 0x00 );
 
    if( 0 == UserI2c_Wait_Ack3() )
    {
        UserI2c_Stop3();
        return 0;
    }
 
    UserI2c_Send_Byte3( SubAdd & 0xff );
 
    if( 0 == UserI2c_Wait_Ack3() )
    {
        UserI2c_Stop3();
        return 0;
    }
 
    for ( i = 0; i < Size; i++)
    {
        UserI2c_Send_Byte3( TXBuff[Size - i - 1] );
 
        if( 0 == UserI2c_Wait_Ack3() )
        {
            UserI2c_Stop3();
            return 0;
        }
    }
 
    UserI2c_Stop3();
 
    return 1;
}
unsigned char SensorWritenByte4(unsigned char Devid, unsigned char *TXBuff, unsigned char SubAdd, unsigned char Size)
{
    unsigned char i = 0;
 
    UserI2c_Start4();
 
    UserI2c_Send_Byte4( Devid | 0x00 );
 
    if( 0 == UserI2c_Wait_Ack4() )
    {
        UserI2c_Stop4();
        return 0;
    }
 
    UserI2c_Send_Byte4( SubAdd & 0xff );
 
    if( 0 == UserI2c_Wait_Ack4() )
    {
        UserI2c_Stop4();
        return 0;
    }
 
    for ( i = 0; i < Size; i++)
    {
        UserI2c_Send_Byte4( TXBuff[Size - i - 1] );
 
        if( 0 == UserI2c_Wait_Ack4() )
        {
            UserI2c_Stop4();
            return 0;
        }
    }
 
    UserI2c_Stop4();
 
    return 1;
}
unsigned char SensorReadnByte(unsigned char Devid, unsigned char *RXBuff, unsigned char SubAdd, unsigned char Size)
{
    unsigned char i = 0;
 
    UserI2c_Start();
 
//    UserI2c_Send_Byte( Devid | 0x00 ); //实时距离地址
		UserI2c_Send_Byte( Devid | 0x04 );   //滤波距离地址
    if( 0 == UserI2c_Wait_Ack() )
    {
        UserI2c_Stop();
        return 0;
    }
 
    UserI2c_Send_Byte( SubAdd & 0xff );
 
    if( 0 == UserI2c_Wait_Ack() )
    {
        UserI2c_Stop();
        return 0;
    }
 
    UserI2c_Stop();
 
    UserI2c_Start();
    //UserI2c_Send_Byte( Devid | 0x01 ); //实时距离地址
		UserI2c_Send_Byte( Devid | 0x05 );   //滤波距离地址
 
 
    if( 0 == UserI2c_Wait_Ack() )
    {
	//  UserI2c_Stop();
	//    return 0;
    }
 
    for ( i = 0; i < Size; i++)
    {
 
        RXBuff[Size - i - 1] = UserI2c_Read_Byte();
 
        if((i + 1) == Size)
            useri2c_nack();
        else
            useri2c_ack();
 
    }
 
    UserI2c_Stop();
 
    return 1;
}
unsigned char SensorReadnByte2(unsigned char Devid, unsigned char *RXBuff, unsigned char SubAdd, unsigned char Size)
{
    unsigned char i = 0;
 
    UserI2c_Start2();
 
//    UserI2c_Send_Byte( Devid | 0x00 ); //实时距离地址
		UserI2c_Send_Byte2( Devid | 0x04 );   //滤波距离地址
    if( 0 == UserI2c_Wait_Ack2() )
    {
        UserI2c_Stop2();
        return 0;
    }
 
    UserI2c_Send_Byte2( SubAdd & 0xff );
 
    if( 0 == UserI2c_Wait_Ack2() )
    {
        UserI2c_Stop2();
        return 0;
    }
 
    UserI2c_Stop2();
 
    UserI2c_Start2();
    //UserI2c_Send_Byte( Devid | 0x01 ); //实时距离地址
		UserI2c_Send_Byte2( Devid | 0x05 );   //滤波距离地址
 
 
    if( 0 == UserI2c_Wait_Ack2() )
    {
	//  UserI2c_Stop();
	//    return 0;
    }
 
    for ( i = 0; i < Size; i++)
    {
 
        RXBuff[Size - i - 1] = UserI2c_Read_Byte2();
 
        if((i + 1) == Size)
            useri2c_nack2();
        else
            useri2c_ack2();
 
    }
 
    UserI2c_Stop2();
 
    return 1;
}
unsigned char SensorReadnByte3(unsigned char Devid, unsigned char *RXBuff, unsigned char SubAdd, unsigned char Size)
{
    unsigned char i = 0;
 
    UserI2c_Start3();
 
//    UserI2c_Send_Byte( Devid | 0x00 ); //实时距离地址
		UserI2c_Send_Byte3( Devid | 0x04 );   //滤波距离地址
    if( 0 == UserI2c_Wait_Ack3() )
    {
        UserI2c_Stop3();
        return 0;
    }
 
    UserI2c_Send_Byte3( SubAdd & 0xff );
 
    if( 0 == UserI2c_Wait_Ack3() )
    {
        UserI2c_Stop3();
        return 0;
    }
 
    UserI2c_Stop3();
 
    UserI2c_Start3();
    //UserI2c_Send_Byte( Devid | 0x01 ); //实时距离地址
		UserI2c_Send_Byte3( Devid | 0x05 );   //滤波距离地址
 
 
    if( 0 == UserI2c_Wait_Ack3() )
    {
	//  UserI2c_Stop();
	//    return 0;
    }
 
    for ( i = 0; i < Size; i++)
    {
 
        RXBuff[Size - i - 1] = UserI2c_Read_Byte3();
 
        if((i + 1) == Size)
            useri2c_nack3();
        else
            useri2c_ack3();
 
    }
 
    UserI2c_Stop3();
 
    return 1;
}
unsigned char SensorReadnByte4(unsigned char Devid, unsigned char *RXBuff, unsigned char SubAdd, unsigned char Size)
{
    unsigned char i = 0;
 
    UserI2c_Start4();
 
//    UserI2c_Send_Byte( Devid | 0x00 ); //实时距离地址
		UserI2c_Send_Byte4( Devid | 0x04 );   //滤波距离地址
    if( 0 == UserI2c_Wait_Ack4() )
    {
        UserI2c_Stop4();
        return 0;
    }
 
    UserI2c_Send_Byte4( SubAdd & 0xff );
 
    if( 0 == UserI2c_Wait_Ack4() )
    {
        UserI2c_Stop4();
        return 0;
    }
 
    UserI2c_Stop4();
 
    UserI2c_Start4();
    //UserI2c_Send_Byte( Devid | 0x01 ); //实时距离地址
		UserI2c_Send_Byte4( Devid | 0x05 );   //滤波距离地址
 
 
    if( 0 == UserI2c_Wait_Ack4() )
    {
	//  UserI2c_Stop();
	//    return 0;
    }
 
    for ( i = 0; i < Size; i++)
    {
 
        RXBuff[Size - i - 1] = UserI2c_Read_Byte4();
 
        if((i + 1) == Size)
            useri2c_nack4();
        else
            useri2c_ack4();
 
    }
 
    UserI2c_Stop4();
 
    return 1;
}
 
void UserI2c_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(	I2C_SCL_CLK, ENABLE );
    RCC_AHB1PeriphClockCmd(	I2C_SDA_CLK, ENABLE );
	  RCC_AHB1PeriphClockCmd(	I2C_SCL_CLK2, ENABLE );
    RCC_AHB1PeriphClockCmd(	I2C_SDA_CLK2, ENABLE );
	  RCC_AHB1PeriphClockCmd(	I2C_SCL_CLK3, ENABLE );
    RCC_AHB1PeriphClockCmd(	I2C_SDA_CLK3, ENABLE );
	  RCC_AHB1PeriphClockCmd(	I2C_SCL_CLK4, ENABLE );
    RCC_AHB1PeriphClockCmd(	I2C_SDA_CLK4, ENABLE );
 
    GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);
 
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN2;
	  GPIO_Init(I2C_SCL_PORT2, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN2;
    GPIO_Init(I2C_SDA_PORT2, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN3;
	  GPIO_Init(I2C_SCL_PORT3, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN3;
    GPIO_Init(I2C_SDA_PORT3, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN4;
	  GPIO_Init(I2C_SCL_PORT4, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN4;
    GPIO_Init(I2C_SDA_PORT4, &GPIO_InitStructure);
 
 
    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN); 	//SCL 输出高
    GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN); 	//SDA 输出高
		GPIO_SetBits(I2C_SCL_PORT2, I2C_SCL_PIN2); 	//SCL 输出高
    GPIO_SetBits(I2C_SDA_PORT2, I2C_SDA_PIN2); 	//SDA 输出高
		GPIO_SetBits(I2C_SCL_PORT3, I2C_SCL_PIN3); 	//SCL 输出高
    GPIO_SetBits(I2C_SDA_PORT3, I2C_SDA_PIN3); 	//SDA 输出高
		GPIO_SetBits(I2C_SCL_PORT4, I2C_SCL_PIN4); 	//SCL 输出高
    GPIO_SetBits(I2C_SDA_PORT4, I2C_SDA_PIN4); 	//SDA 输出高
/************************/
/**配置TOF内部寄存器*****/
/**代码改于2022/6/1_dpt**/
/************************/
	devid=I2C_DEVID;       //设置I2C从机地址  默认164 0xA4
	
	dirt_send_flag=1;			 //=0串口主动发送 =1串口或者I2C被动读取
	SensorWritenByte(devid,(unsigned char *)&dirt_send_flag, 0x09, 1);      //0x09设置距离发送方式  1 主机去读取  0 模块发送
	delay_ms(100);
		SensorWritenByte2(devid,(unsigned char *)&dirt_send_flag, 0x09, 1);      //0x09设置距离发送方式  1 主机去读取  0 模块发送
	delay_ms(100);
		SensorWritenByte3(devid,(unsigned char *)&dirt_send_flag, 0x09, 1);      //0x09设置距离发送方式  1 主机去读取  0 模块发送
	delay_ms(100);
		SensorWritenByte4(devid,(unsigned char *)&dirt_send_flag, 0x09, 1);      //0x09设置距离发送方式  1 主机去读取  0 模块发送
	delay_ms(100);
	
	dirt_detection_flag=0; //=0滤波值 =1实时值
	SensorWritenByte(devid,(unsigned char *)&dirt_detection_flag, 0x08, 1);  //0x08设置 距离数据模式   1 实时值 0滤波值
	delay_ms(100);	
	SensorWritenByte2(devid,(unsigned char *)&dirt_detection_flag, 0x08, 1);  //0x08设置 距离数据模式   1 实时值 0滤波值
	delay_ms(100);		
	SensorWritenByte3(devid,(unsigned char *)&dirt_detection_flag, 0x08, 1);  //0x08设置 距离数据模式   1 实时值 0滤波值
	delay_ms(100);		
	SensorWritenByte4(devid,(unsigned char *)&dirt_detection_flag, 0x08, 1);  //0x08设置 距离数据模式   1 实时值 0滤波值
	delay_ms(100);			
	
}
