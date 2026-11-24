#ifndef __SYSTEM_H
#define __SYSTEM_H

// Refer to all header files you need
//引用所有需要用到的头文件
#include "FreeRTOSConfig.h"
//FreeRTOS相关头文件 
//FreeRTOS related header files
#include "FreeRTOS.h"
#include "stm32f4xx.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
//The associated header file for the peripheral 
//外设的相关头文件
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "balance.h"
#include "led.h"
#include "oled.h"
#include "usart.h"
#include "usartx.h"
#include "adc.h"
#include "can.h"
#include "timer.h"
#include "show.h"								   
#include "pstwo.h"
#include "robot_select_init.h"
#include "I2C.h"
#include "MPU6050.h"

#include "exti.h"
#include "delay.h"
#include "led.h"
#include "moto.h"
#include "adc.h"
#include "usart.h"
#include "encoder.h"
#include "key.h"
//#include "tof.h"
#include "HD.h"

#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "hal_drivers.h"
#include "ASCIIProtocol.h"
#include "MODBUSProtocol.h"
#include "HEXProtocol.h"
#include "wit_c_sdk.h"
typedef struct
{
    unsigned char buf[256];
	  int length;
	  bool valid;
	  int type;
}usart_buf_t;

/*
IO口·资源占用：
       ADC：   PA5
编码器电机： PWM     IN2     IN1     EA     EB
		 左前A： PE9     PF11    PC10    PC7    PC6
		 右前D： PE14    PC0     PC1     PB6    PB7
		 左后B： PE11    PB12    PB13    PA0    PA1
		 右后C： PE13    PB1     PB0     PB4    PB5
惯导/陀螺仪：
            U3-TX:  PC12------->RX(黄)
            U3-RX:  PD2 ------->TX(绿)
OLED：
       SCL:  PA6
       SDA:  PA7
激光:  TX         RX
   前(USART6)：PD6->PG14        PD7->PG9
   后：PC8        PC9 
   左(USART3)：PD10->PD8       PD11->PD9
   右(USART2)：PD4->PD5        PD5->PD6
灰度左：
       DOUT1:   PF13  HD4
       DOUT2:   PD14  HD3
       DOUT3:   PG13  HD2
       DOUT4:   PC3   HD1
灰度右：
       DOUT4:   PF3 HL4
       DOUT3:   PF4 HL3
       DOUT2:   PF5 HL2
       DOUT1:   PF6 HL1
			 
IO收发：TX         RX
   涛1：F0    洋1：B10
	 涛2：F2    洋2：E5
	 涛3：F12   洋3：E10
	 

更新：2024/7/14
作者：鲲鲲不鲲
*/


// Enumeration of car types
//小车型号的枚举定义
typedef enum 
{
	Mec_Car = 0, 
	Omni_Car, 
	Akm_Car, 
	Diff_Car, 
	FourWheel_Car, 
	Tank_Car
} CarMode;

//Motor speed control related parameters of the structure
//电机速度控制相关参数结构体
typedef struct  
{
	float Encoder;     //Read the real time speed of the motor by encoder //编码器数值，读取电机实时速度
	float Motor_Pwm;   //Motor PWM value, control the real-time speed of the motor //电机PWM数值，控制电机实时速度
	float Target;      //Control the target speed of the motor //电机目标速度值，控制电机目标速度
	float Velocity_KP; //Speed control PID parameters //速度控制PID参数
	float	Velocity_KI; //Speed control PID parameters //速度控制PID参数
}Motor_parameter;

//Smoothed the speed of the three axes
//平滑处理后的三轴速度
typedef struct  
{
	float VX;
	float VY;
	float VZ;
}Smooth_Control;

/****** external variable definition. When system.h is referenced in other C files, 
        other C files can also use the variable defined by system.c           ******/
/****** 外部变量定义，当其它c文件引用system.h时，也可以使用system.c定义的变量 ******/
extern u8 Flag_Stop;
extern int Divisor_Mode;
extern u8 Car_Mode;
extern int Servo;
extern float RC_Velocity;
extern float Move_X, Move_Y, Move_Z; 
extern float Velocity_KP, Velocity_KI;	
extern Smooth_Control smooth_control;
extern Motor_parameter MOTOR_A, MOTOR_B, MOTOR_C, MOTOR_D;
extern float Encoder_precision;
extern float Wheel_perimeter;
extern float Wheel_spacing; 
extern float Axle_spacing; 
extern float Omni_turn_radiaus; 
extern u8 PS2_ON_Flag, APP_ON_Flag, Remote_ON_Flag, CAN_ON_Flag, Usart1_ON_Flag, Usart5_ON_Flag;
extern u8 Flag_Left, Flag_Right, Flag_Direction, Turn_Flag; 
extern u8 PID_Send;                                            										                 
extern float PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;
extern int Check, Checking, Checked, CheckCount, CheckPhrase1, CheckPhrase2;
extern long int ErrorCode; 

void systemInit(void);
void other_Config(void);
int JL(int a);
void JLF(int a,int A,int S);
void ydjg(void);

/***Macros define***/ /***宏定义***/
//After starting the car (1000/100Hz =10) for seconds, it is allowed to control the car to move
//开机(1000/100hz=10)秒后才允许控制小车进行运动
#define CONTROL_DELAY		1000
//The number of robot types to determine the value of Divisor_Mode. There are currently 6 car types
//机器人型号数量，决定Divisor_Mode的值，目前有6种小车类型
#define CAR_NUMBER    6      
#define RATE_1_HZ		  1
#define RATE_5_HZ		  5
#define RATE_10_HZ		10
#define RATE_20_HZ		20
#define RATE_25_HZ		25
#define RATE_50_HZ		50
#define RATE_100_HZ		100
#define RATE_200_HZ 	200
#define RATE_250_HZ 	250
#define RATE_500_HZ 	500
#define RATE_1000_HZ 	1000
/***Macros define***/ /***宏定义***/

//C library function related header file
//C库函数的相关头文件
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stdarg.h"

#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80
 static void CmdProcess(void);
static void AutoScanSensor(void);
static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
static void Delayms(uint16_t ucMs);
void CopeCmdData(unsigned char ucData);
void cq(void);
#endif 
