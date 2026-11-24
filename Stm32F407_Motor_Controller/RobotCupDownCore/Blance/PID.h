#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct {

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

	/* Derivative low-pass filter time constant */
	float tau;

	/* Output limits */
	float limMin;
	float limMax;
	
	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* Sample time (in seconds) */
	float T;

	/* Controller "memory" */
	float integrator;
	float prevError;			/* Required for integrator */
	float differentiator;
	float prevMeasurement;		/* Required for differentiator */

	/* Controller output */
	float out;

} PIDController;

void  PIDController_Init(PIDController *pid);
float PIDController_Update(PIDController *pid, float setpoint, float measurement);


//PID 结构体
typedef struct
{
  	float Kp;                       //比例系数Proportional
  	float Ki;                       //积分系数Integral
  	float Kd;                       //微分系数Derivative
 
  	float Ek;                       //当前误差
  	float Ek1;                      //前一次误差 e(k-1)
  	float Ek2;                      //再前一次误差 e(k-2)
  	float LocSum;                   //累计积分位置

	float limMinInt;
	float limMaxInt;
}PID_INC_TypeDef;

//pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
/************************************************
函数名称 ： PID_Inc
功    能 ： 增量式PID
参    数 ： SetValue ------ 设置值(期望值)
            ActualValue --- 实际值(反馈值)
            PID ----------- PID数据结构
返 回 值 ： PWM -------- 本次PID增量(+/-)
*************************************************/
float PID_Inc(float SetValue, float ActualValue, PID_INC_TypeDef *PID);
void PID_Init(PID_INC_TypeDef *PID);
#endif
