#ifndef __MOTO_H
#define	__MOTO_H

#include "usart.h"
#include "encoder.h"
#include "led.h"
#include "oled.h"
typedef struct PID
{
  float KP;
	float KI;
	float KD;
}pidz;

#define KPP  0
#define KII  0
#define KDD  0
#define ny  1

/**************************************************************************
函数功能：pwm初始化
入口参数：arr：设为一个时钟频率的最大值  psc： 预分频值
**************************************************************************/
void Set_PWM(int motor1,int motor2,int motot3,int motor4);
void TIM1_GPIO_Config(void);
void Dianji_Tim1_Config(uint16_t arr,uint16_t psc);
void TIM10_CH1Init(u16 psc,u16 arr);
/**************************************************************************
函数功能：电机方向速度控制
形式：包装函数
**************************************************************************/
void moto(int mode); //电机正反转控制
/*  各电机方向控制  */
void left1(int NN);  //左前A
void left2(int NN);  //左后B
void right1(int NN); //右前D
void right2(int NN); //右后C
/*  各电机速度控制  */
void left1_v(int vv);   //左前A
void left2_v(int vv);   //左后B
void right1_v(int vv);  //右前D
void right2_v(int vv);  //右后C
/* -----------小车移动----------- */
/*  前进  */
void go_stright();
/*  后退  */
void go_back();
/*  左转  */
void turn_left(int lr);
/*  右转  */
void turn_right(int lr);
/*  左转  */
void turn_left2(int lr);
/*  右转  */
void turn_right2(int lr);
/*  左平移  */
void go_left();
/*  右平移  */
void go_right();

void stop(int a);

void gb(float S,int A,int a,int lr);//前进后退距离控制

void lr(float S,int A,int a,int lr);//左右平移距离控制


//左/右平移
void ll (int lr)  ;
void rr (int lr)  ;

//前进后退
void bb (int lr)  ;
void gg (int lr)  ;

void huidu(int hh);//灰度十字光标定位

void tly(float tag);//陀螺仪调整

void tlyjz(float tag);//陀螺仪角度调整

void jinhuo(void);//后灰度进货检测

void Go_crazy(void);//”疯狂吧“右程序

void Go_roar(void);//”咆哮吧“左程序

void PIDJZ(void);//PID校准测试

int Velocity_A(int TargetVelocity, int CurrentVelocity);
int Velocity_B(int TargetVelocity, int CurrentVelocity);

int Position_PID (int position,int target);

#endif
