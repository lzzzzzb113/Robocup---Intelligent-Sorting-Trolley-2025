#include "PID.h"

void PIDController_Init(PIDController *pid) {

	/* Clear controller variables */
	pid->integrator = 0.0f;
	pid->prevError  = 0.0f;

	pid->differentiator  = 0.0f;
	pid->prevMeasurement = 0.0f;

	pid->out = 0.0f;

}

float PIDController_Update(PIDController *pid, float setpoint, float measurement) {

	/*
	* Error signal
	*/
    float error = setpoint - measurement;


    pid->integrator += error;


    pid->out = pid->Kp * error + pid->Ki * pid->integrator + pid->Kd * (error - pid->prevError);


    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {
        pid->out = pid->limMin;

    }

	/* 存储误差和测量以备后用 */
    pid->prevError       = error;
    pid->prevMeasurement = measurement;

	/* Return controller output */
    return pid->out;

}

void PID_Init(PID_INC_TypeDef *PID){
	PID->Ek1 = 0;
	PID->Ek2 = 0;
	PID->LocSum = 0;
}
float PID_Inc(float SetValue, float ActualValue, PID_INC_TypeDef *PID){
    float PWM;                                  //增量
 
    PID->Ek = SetValue - ActualValue;           //计算当前偏差
    PID->LocSum += PID->Ek;                     //累计误差
    PWM = PID->Kp * (PID->Ek - PID->Ek1) + PID->Ki * PID->Ek + 
    		PID->Kd * (PID->Ek - 2 * PID->Ek1 + PID->Ek2);                                          
                                                //增量式PID控制器                       
    PID->Ek2 = PID->Ek1;
    PID->Ek1 = PID->Ek;

    if(PWM > PID->limMaxInt)
    {
      PWM = PID->limMaxInt;
    }
    else if(PWM < PID->limMinInt)
    {
      PWM = PID->limMinInt;
    }                                           //限幅

    return PWM;
}

//改良过的
/*float PID_Inc(float SetValue, float ActualValue, PID_INC_TypeDef *PID){
    float PWM;                                  //增量
    float kp, ki, kd;
    PID->Ek = SetValue - ActualValue;         //计算当前偏差
    // 将PID参数转换为小数形式
    kp = PID->Kp / 10.0f;
    ki = PID->Ki / 10.0f;
    kd = PID->Kd / 10.0f;
    PWM = = kp * (PID->Ek - PID->Ek1)  // 比例项
             + ki * PID->Ek                   // 积分项
             + kd * (PID->Ek - 2 * PID->Ek1 + PID->Ek2);  // 微分项                      
    PID->Ek2 = PID->Ek1;
    PID->Ek1 = PID->Ek;
    if(PWM > PID->limMaxInt)
    {
      PWM = PID->limMaxInt;
    }
    else if(PWM < PID->limMinInt)
    {
      PWM = PID->limMinInt;
    }                                           //限幅

    return PWM;
}*/


