#include "PID.h"
#include "InitAllinOne.h"
#include "yz_time_area.h"
#include "huidu.h"
#include "mykey.h"
/******

******/
extern void TickDelay_MS(uint32_t ms); // 标准定时器实现延迟'
extern int lock1, lock2, lock3, lock4, lock5, lock6;
extern int flag_in, flag_out, flag_run, flag_UPDOWN;
PID_INC_TypeDef left1_pid, right1_pid, left2_pid, right2_pid;
PID_INC_TypeDef x1_pid, x2_pid, x3_pid, x4_pid;
int destSpeed1, destSpeed2, destSpeed3, destSpeed4;
int currentOut1, currentOut2, currentOut3, currentOut4;
int limit1, limit2, limit3, limit4;
int needUpdate = 0;
int XdestSum1 = 0, YdestSum1 = 0;
int XdestSum2 = 0, YdestSum2 = 0;
int XdestSum3 = 0, YdestSum3 = 0;
int XdestSum4 = 0, YdestSum4 = 0;
extern volatile int yzsum1, yzsum2, yzsum3, yzsum4; // A,B,C,D的编码器值
volatile int inRunning = 0;                         // 是否在运行
int x1dest = 0, x2dest = 0, x3dest = 0, x4dest = 0;
int flag_left=0,flag_test=0,flag_right=0;
#define UNIT_X  	2474  
#define UNIT_Y   2495 
#define UNIT_XYL 4940
#define UNIT_XYR 4940
#define UNIT_ROUND 1110
#define speedR_correct 700
#define speedF_correct 700
#define movedelay   1   //100
#define moverounddelay   300//300
#define updowndelay  1800  //2000
#define LIGHTcomparedelay 1   //100
#define angledelay   1    //150
int limitspeed,limitSpeed=2550,speed_limit_maxi,speed_limit_MAXI=15000;//2800,15000;1800,14000
// 前后轮毂外径距离35cm，左右轮毂外径距离28cm,前后轮廓38.4cm,左右轮廓30.6cm
/**
 * @brief 速度环回调接口，在编码器被读取时调用
 *
 * @param VA left1
 * @param VB left2
 * @param VC right1
 * @param VD right2
 * @param sumA left1计数
 * @param sumB left2计数
 * @param sumC right1计数
 * @param sumD right2计数
 * @return int 返回0清除sum计数值
 */
int X_Count = 0;
void SetXSpeed(int x1, int x2, int x3, int x4)
{
    if (x1 > 0)
    {
        left1(1);
    }
    else
    {
        left1(0);
    }
    if (x2 > 0)
    {
        left2(1);
    }
    else
    {
        left2(0);
    }
    if (x3 > 0)
    {
        right2(1);
    }
    else
    {
        right2(0);
    }
    if (x4 > 0)
    {
        right1(1);
    }
    else
    {
        right1(0);
    }
    Set_PWM(abs(x1), abs(x2), abs(x3), abs(x4));
}
void speed_Init(){
    limitspeed=limitSpeed;
    speed_limit_maxi=speed_limit_MAXI;
}
int x1_speed = 0, x2_speed = 0, x3_speed = 0, x4_speed = 0;
int flag_PID_FR = 0;
int SpeedPID_UPDATE(int VA, int VB, int VC, int VD, int sumA, int sumB, int sumC, int sumD)
{
    X_Count++;
    RecvTimeUpdate();
    if (X_Count>3)
    {
				X_Count = 0;
        x1_speed += PID_Inc(x1dest, yzsum1, &x1_pid) * 0.01;
        x2_speed += PID_Inc(x2dest, -yzsum2, &x2_pid) * 0.01;
        x3_speed += PID_Inc(x3dest, yzsum3, &x3_pid) * 0.01;
        x4_speed += PID_Inc(x4dest, yzsum4, &x4_pid) * 0.01;
        if (x1_speed > limitSpeed)
        {
            x1_speed = limitSpeed;
        }
        else if (x1_speed < -limitSpeed)
        {
            x1_speed = -limitSpeed;
        }
        if (x2_speed > limitSpeed)
        {
            x2_speed = limitSpeed;
        }
        else if (x2_speed < -limitSpeed)
        {
            x2_speed = -limitSpeed;
        }
        if (x3_speed > limitSpeed)
        {
            x3_speed = limitSpeed;
        }
        else if (x3_speed < -limitSpeed)
        {
            x3_speed = -limitSpeed;
        }
        if (x4_speed > limitSpeed)
        {
            x4_speed = limitSpeed;
        }
        else if (x4_speed < -limitSpeed)
        {
            x4_speed = -limitSpeed;
        }
        // printf("%d,%d,%d,%d,%d,%d,%d,%d\n",yzsum1,-yzsum2,yzsum3,yzsum4,x1_speed,x2_speed,x3_speed,x4_speed);
//        printf("%d,%d,%d,%d,%d,%d,%d,%d\n",x1dest,yzsum1,x2dest,-yzsum2,x3dest,yzsum3,x4dest,yzsum4);
        // SetXSpeed(x1_speed, x2_speed, x3_speed, x4_speed);
        destSpeed1 = x1_speed;
        destSpeed2 = x2_speed;
        destSpeed3 = x3_speed;
        destSpeed4 = x4_speed;
    }
    if (abs(destSpeed1) < 40)
    {
        destSpeed1 = 0;
    }
    if (abs(destSpeed2) < 40)
    {
        destSpeed2 = 0;
    }
    if (abs(destSpeed3) < 40)
    {
        destSpeed3 = 0;
    }
    if (abs(destSpeed4) < 40)
    {
        destSpeed4 = 0;
    }
    if (destSpeed1 > limitSpeed)
    {
        destSpeed1 = limitSpeed;
    }
    else if (destSpeed1 < -limitSpeed)
    {
        destSpeed1 = -limitSpeed;
    }
    if (destSpeed2 > limitSpeed)
    {
        destSpeed2 = limitSpeed;
    }
    else if (destSpeed2 < -limitSpeed)
    {
        destSpeed2 = -limitSpeed;
    }
    if (destSpeed3 > limitSpeed)
    {
        destSpeed3 = limitSpeed;
    }
    else if (destSpeed3 < -limitSpeed)
    {
        destSpeed3 = -limitSpeed;
    }
    if (destSpeed4 > limitSpeed)
    {
        destSpeed4 = limitSpeed;
    }
    else if (destSpeed4 < -limitSpeed)
    {
        destSpeed4 = -limitSpeed;
    }
    currentOut1 += PID_Inc(destSpeed1, VA, &left1_pid);
    currentOut2 += PID_Inc(destSpeed2, -VB, &left2_pid); // 编码器正反的问题
    currentOut3 += PID_Inc(destSpeed3, VC, &right1_pid);
    currentOut4 += PID_Inc(destSpeed4, VD, &right2_pid);
    if (currentOut1 > limit1)
        currentOut1 = limit1;
    if (currentOut2 > limit2)
        currentOut2 = limit2;
    if (currentOut3 > limit3)
        currentOut3 = limit3;
    if (currentOut4 > limit4)
        currentOut4 = limit4;
    if (currentOut1 < -limit1)
        currentOut1 = -limit1;
    if (currentOut2 < -limit2)
        currentOut2 = -limit2;
    if (currentOut3 < -limit3)
        currentOut3 = -limit3;
    if (currentOut4 < -limit4)
        currentOut4 = -limit4;
    SetXSpeed(currentOut1, currentOut2, currentOut3, currentOut4);

    // printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",destSpeed1,VA,destSpeed2,VB,destSpeed3,VC,destSpeed4,VD,x3dest,yzsum3);
    // printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",destSpeed1,VA,-destSpeed2,-VB,destSpeed3,VC,destSpeed4,VD);
    if (flag_PID_FR == 1 && inRunning == 1 && abs(x1dest - sumA) < speedR_correct && abs(x2dest + sumB) < speedR_correct && abs(x3dest - sumC) < speedR_correct && abs(x4dest - sumD) < speedR_correct)
    {
        inRunning = 0;
        flag_PID_FR = 0;
    }
    else if (flag_PID_FR == 0 && inRunning == 1 && abs(x1dest - sumA) < speedF_correct && abs(x2dest + sumB) < speedF_correct && abs(x3dest - sumC) < speedF_correct && abs(x4dest - sumD) < speedF_correct)
    {
        inRunning = 0;
    }
    // printf("%d,%d,%d,%d,%d,%d,%d,%d\n",x1dest,sumA,x2dest,-sumB,x3dest,sumC,x4dest,sumD);
//     printf("%d,%d\n",x1dest,sumA);
    return 1;
}
void StepX(int x)
{
    limit1 = speed_limit_MAXI;
    limit2 = speed_limit_MAXI;
    limit3 = speed_limit_MAXI;
    limit4 = speed_limit_MAXI;
    x1dest += x;
    x2dest += x;
    x3dest += x;
    x4dest += x;
    inRunning = 1; // 设置为正在运行
}
void StepY(int y)
{
    limit1 = speed_limit_MAXI;
    limit2 = speed_limit_MAXI;
    limit3 = speed_limit_MAXI;
    limit4 = speed_limit_MAXI;
    x1dest += y;
    x2dest += -y;
    x3dest += y;
    x4dest += -y;
    inRunning = 1; // 设置为正在运行
}
void StepXYL(int x)
{
    limit1 = speed_limit_MAXI;
    limit2 = speed_limit_MAXI;
    limit3 = speed_limit_MAXI;
    limit4 = speed_limit_MAXI;
    x2dest += x;
    x4dest += x;
    inRunning = 1; // 设置为正在运行
}
void StepXYR(int x)
{
    limit1 = speed_limit_MAXI;
    limit2 = speed_limit_MAXI;
    limit3 = speed_limit_MAXI;
    limit4 = speed_limit_MAXI;
    x1dest += x;
    x3dest += x;
    inRunning = 1; // 设置为正在运行
}
void StepRound(int x)
{
    flag_PID_FR = 1;
    limit1 = speed_limit_MAXI;
    limit2 = speed_limit_MAXI;
    limit3 = speed_limit_MAXI;
    limit4 = speed_limit_MAXI;
    x1dest += x;
    x2dest += x;
    x3dest -= x;
    x4dest -= x;
    inRunning = 1; // 设置为正在运行
}
void SetLeft1PID(float Kp, float Ki, float Kd)
{
    left1_pid.Kp = Kp;
    left1_pid.Ki = Ki;
    left1_pid.Kd = Kd;
    left1_pid.limMaxInt = limitSpeed;
    left1_pid.limMinInt = -limitSpeed;
}
void SetLeft2PID(float Kp, float Ki, float Kd)
{
    left2_pid.Kp = Kp;
    left2_pid.Ki = Ki;
    left2_pid.Kd = Kd;
    left2_pid.limMaxInt = limitSpeed;
    left2_pid.limMinInt = -limitSpeed;
}
void SetRight1PID(float Kp, float Ki, float Kd)
{
    right1_pid.Kp = Kp;
    right1_pid.Ki = Ki;
    right1_pid.Kd = Kd;
    right1_pid.limMaxInt = limitSpeed;
    right1_pid.limMinInt = -limitSpeed;
}
void SetRight2PID(float Kp, float Ki, float Kd)
{
    right2_pid.Kp = Kp;
    right2_pid.Ki = Ki;
    right2_pid.Kd = Kd;
    right2_pid.limMaxInt = limitSpeed;
    right2_pid.limMinInt = -limitSpeed;
}
void SetX1PID(float Kp, float Ki, float Kd)
{
    x1_pid.Kp = Kp;
    x1_pid.Ki = Ki;
    x1_pid.Kd = Kd;
    x1_pid.limMaxInt = 50000;
    x1_pid.limMinInt = -50000;
}
void SetX2PID(float Kp, float Ki, float Kd)
{
    x2_pid.Kp = Kp;
    x2_pid.Ki = Ki;
    x2_pid.Kd = Kd;
    x2_pid.limMaxInt = 50000;
    x2_pid.limMinInt = -50000;
}
void SetX3PID(float Kp, float Ki, float Kd)
{
    x3_pid.Kp = Kp;
    x3_pid.Ki = Ki;
    x3_pid.Kd = Kd;
    x3_pid.limMaxInt = 50000;
    x3_pid.limMinInt = -50000;
}
void SetX4PID(float Kp, float Ki, float Kd)
{
    x4_pid.Kp = Kp;
    x4_pid.Ki = Ki;
    x4_pid.Kd = Kd;
    x4_pid.limMaxInt = 50000;
    x4_pid.limMinInt = -50000;
}
extern double fabs(float a);
void delay(int x)
{
    TickDelay_MS(x);
}
void DELAY(int x)
{
		TickDelay_MS(x);
    while (inRunning == 1)
    {
    };
}
// 逆时针旋转x°
void Move_Round(int x)
{
    StepRound(UNIT_ROUND * x);
    DELAY(movedelay);
	  if(fabs(x)>75)delay(moverounddelay);
}
double Current1 = 0;
int target = 0;
int Current = 0;
extern double YAW_DETA;
void Move_Angle(int angle)
{ // PD2---usart5-rx;PC12---usart5-tx，根据陀螺仪转动角度
		delay(angledelay);
    Current1 = Request_YAW();
    Current = (int)Current1;
    if (Current % 360 == 0)Current = 0;
    while (Current > 360 || Current < 0){
        if (Current > 360)Current -= 360;
        if (Current < 0)Current += 360;
    }
    if (fabs(angle - Current) < 1)target = 0;
    else target = angle - Current;
    if (target > 180)target = target - 360;
    if (target < -180)target = 360 + target;
    Move_Round(target);
}
// MOVE_Y(y厘米单位级)
void Move_Y(int y)
{
    StepY(UNIT_Y * y);
    DELAY(movedelay);
}
// MOVE_X(x厘米单位级)
void Move_X(int x)
{
    StepX(UNIT_X * x);
    DELAY(movedelay);
}
// x>0,左前方斜向移动；x<0,有后方斜向移动
void Move_XYL(int x)
{
    StepXYL(UNIT_XYL * x);
    DELAY(movedelay);
}
// y>0,右前方斜向移动；y<0,左后方斜向移动
void Move_XYR(int y)
{
    StepXYR(UNIT_XYR * y);
    DELAY(movedelay);
}
char *iSM = "iSM\n";
extern double inlock1, LIGHT_RIGHT, LIGHT_FORWORD, inlock4, inlock5, LIGHT_LEFT;
// inclock2右激光测距，inlock3是前激光，inlock6是左激光
int move = 0;
uint32_t Time = 0;
extern uint32_t SystemTickCount;
void Receive1_USART2()
{ // pd6---usart2-rx;pd5---usart2-tx
    USART2_SendString(iSM, strlen(iSM));
    lock2 = 1;
		Time=SystemTickCount;
    while (lock2 > 0)
    {
        if (lock2 == 2)
        {
            USART2_SendString(iSM, strlen(iSM));
            lock2 = 1;
        }
				if(SystemTickCount-Time==3000)LIGHT_RIGHT=1000;
				
    }
}
void Receive1_USART6()
{ // pg9----usart6-rx;pg14----usart6-tx
    USART6_SendString(iSM, strlen(iSM));
    lock6 = 1;
		Time=SystemTickCount;
    while (lock6 > 0)
    {
        if (lock6 == 2)
        {
            USART6_SendString(iSM, strlen(iSM));
            lock6 = 1;
        }
				if(SystemTickCount-Time==3000)LIGHT_LEFT=1000;
    }
}
void Receive_USART2()
{ // pd6---usart2-rx;pd5---usart2-tx
    USART2_SendString(iSM, strlen(iSM));
    lock2 = 1;
		Time=SystemTickCount;
    while (lock2 > 0)
    {
        if (lock2 == 2)
        {
            USART2_SendString(iSM, strlen(iSM));
            lock2 = 1;
        }
				if(SystemTickCount-Time==3000)LIGHT_RIGHT=1000;
				
    }
}
void Receive_USART3()
{ // pd8----usart3-rx;pd9----usart3-tx
    USART3_SendString(iSM, strlen(iSM));
    lock3 = 1;
		Time=SystemTickCount;
    while (lock3 > 0)
    {
        if (lock3 == 2)
        {
            USART3_SendString(iSM, strlen(iSM));
            lock3 = 1;
        }
    }
}
void Receive1_USART3()
{ // pd8----usart3-rx;pd9----usart3-tx
    USART3_SendString(iSM, strlen(iSM));
    lock3 = 1;
		Time=SystemTickCount;
    while (lock3 > 0)
    {
        if (lock3 == 2)
        {
            USART3_SendString(iSM, strlen(iSM));
            lock3 = 1;
        }
				if(SystemTickCount-Time==2000)LIGHT_FORWORD=29;
    }
}
void Receive_USART6()
{ // pg9----usart6-rx;pg14----usart6-tx
    USART6_SendString(iSM, strlen(iSM));
    lock6 = 1;
		Time=SystemTickCount;
    while (lock6 > 0)
    {
        if (lock6 == 2)
        {
            USART6_SendString(iSM, strlen(iSM));
            lock6 = 1;
        }
				if(SystemTickCount-Time==3000)LIGHT_LEFT=1000;
    }
}
int current = 5, current1 = 5;
void LIGHT12_Current(int Cangle)
{ // 激光调整错误位置
    Move_Angle(Cangle);
		delay(LIGHTcomparedelay);
    Receive_USART2(); // 接收右激光数据
    Receive_USART6(); // 接收左激光数据
    while (LIGHT_RIGHT > 35 && LIGHT_LEFT > 35)
    {
        Move_X(current);
        Receive_USART2(); // 接收右激光数据
        Receive_USART6(); // 接收左激光数据
        if (LIGHT_RIGHT < 35 || LIGHT_LEFT < 35)break;
        Move_X(-2 * current);
        Receive_USART2(); // 接收右激光数据
        Receive_USART6(); // 接收左激光数据
        if (LIGHT_LEFT < 35 || LIGHT_RIGHT < 35)break;
        Move_X(current);
        current = current + 4;
        Move_Angle(Cangle);
				delay(LIGHTcomparedelay);	
    }
}
void LIGHT3_Current(int Cangle)
{
    Move_Angle(Cangle);
		delay(LIGHTcomparedelay);
    Receive_USART3(); // 接收前激光数据
    while (LIGHT_FORWORD > 190)
    {
        Move_Y(current1);
        Receive_USART3();
        if (LIGHT_FORWORD < 190)
            break;
        Move_Y(-2 * current1);
        Receive_USART3();
        if (LIGHT_FORWORD < 190)
            break;
        Move_Y(current1);
        current1 = current1 + 2;
        Move_Angle(Cangle);
				delay(LIGHTcomparedelay);
				delay(100);
    }
}

void LIGHTNOL_Current(int Cangle)
{
    int current1 = 5;
    Move_Angle(Cangle);
		delay(LIGHTcomparedelay);
    Receive_USART6(); // 接收前激光数据
    while (LIGHT_LEFT > 40)
    {
        Move_X(current1);
        Receive_USART6();
        if (LIGHT_LEFT < 40)
            break;
        Move_X(-2 * current1);
        Receive_USART6();
        if (LIGHT_LEFT < 40)
            break;
        Move_X(current1);
        current1 = current1 + 4;
        Move_Angle(Cangle);
				delay(LIGHTcomparedelay);
    }
}
void LIGHTNOR_Current(int Cangle)
{
    int current2 = 5;
    Move_Angle(Cangle);
		delay(LIGHTcomparedelay);
    Receive_USART2(); // 接收右激光数据
    while (LIGHT_RIGHT > 40)
    {
        Move_X(current2);
        Receive_USART2();
        if (LIGHT_RIGHT < 40)
            break;
        Move_X(-2 * current2);
        Receive_USART2();
        if (LIGHT_RIGHT < 40)
            break;
        Move_X(current2);
        current2 = current2 + 4;
        Move_Angle(Cangle);
				delay(LIGHTcomparedelay);
    }
}
void HUIDU_correct(int huiduangle,int huidu_W, int huidu_N, int huidu_movex,int huidu_movey,int hdx,int hdy)
{
    Move_Angle(huiduangle);
		delay(LIGHTcomparedelay);
    while (B == huidu_N)
    {
			Move_X(huidu_movex);
		}
		while (B == huidu_N)
    {
			Move_X(huidu_movex);
		}
		while(L==huidu_N||R==huidu_N){
			if(L==huidu_N&&R==huidu_W)Move_Y(huidu_movey);
			else if(L==huidu_W&&R==huidu_N)Move_Y(-huidu_movey);
			else Move_Y(-huidu_movey);
    }
		while(L==huidu_N||R==huidu_N){
			if(L==huidu_N&&R==huidu_W)Move_Y(huidu_movey);
			else if(L==huidu_W&&R==huidu_N)Move_Y(-huidu_movey);
			else Move_Y(-huidu_movey);
    }
		Move_X(hdx);
		Move_Y(hdy);
		Move_Angle(huiduangle);
		delay(LIGHTcomparedelay);
				while (B == huidu_N)
    {
			Move_X(huidu_movex);
		}
		while(L==huidu_N||R==huidu_N){
			if(L==huidu_N&&R==huidu_W)Move_Y(huidu_movey);
			else if(L==huidu_W&&R==huidu_N)Move_Y(-huidu_movey);
			else Move_Y(-huidu_movey);
    }
}
void Change_Speed(int speedchange,int speedIchange){
	limitSpeed=speedchange;
	speed_limit_MAXI=speedIchange;
}
int k = 1;
void Move_correct(int UDangle, int correct)
{
	Change_Speed(1800,14000);
	TickDelay_MS(updowndelay);
  if (flag_UPDOWN == 1)goto MMM;
  Move_X(k * correct);
	TickDelay_MS(updowndelay);
  if (flag_UPDOWN == 1)goto MMM;
  Move_X(k * (-2) * correct);
	Move_Angle(UDangle);
	TickDelay_MS(updowndelay);
  if (flag_UPDOWN == 1)goto MMM;  
  Move_X(k * correct);
	Change_Speed(limitspeed,speed_limit_maxi);
  k++;
    MMM:
	Move_Angle(UDangle);
	delay(LIGHTcomparedelay);
}
int updown_eq=1;
void communication_updownR(int UDangle, int correct)
{ // 上下层交互
	if(updown_eq==1){
		k = 1, flag_run = 0, flag_out = 0, flag_UPDOWN = 0;
    while (flag_out == 0)
    {						
        if (flag_run == 0){
						flag_UPDOWN = 0;
            USART1_SendString("A", 1);
            TickDelay_MS(200);
						USART1_SendString("C", 1);
        }
		if (flag_UPDOWN == 1)delay(100);
		else if (flag_UPDOWN == 0)Move_correct(UDangle, correct);	  	
    }
    k = 1, flag_run = 0, flag_out = 0, flag_UPDOWN = 0;
	}
}
void communication_updownL(int UDangle, int correct)
{
		if(updown_eq==1){
		k = 1, flag_run = 0, flag_out = 0, flag_UPDOWN = 0;
	  while (flag_out == 0)
    {						
        if (flag_run == 0){
						flag_UPDOWN = 0;
            USART1_SendString("B", 1);
            TickDelay_MS(200);
						USART1_SendString("C", 1);
        }
		if (flag_UPDOWN == 1)delay(100);
		else if (flag_UPDOWN == 0)Move_correct(UDangle, correct);	  		
		}
    k = 1, flag_run = 0, flag_out = 0, flag_UPDOWN = 0;
}
}
int flag_L=1,flag_R=1;
void LIGHT12_COMPARE(int UDangle, int correct)
{
		flag_L=0,flag_R=0;
		delay(LIGHTcomparedelay);
    Receive_USART2(); // 接收右激光数据
    Receive_USART6(); // 接收左激光数据
		if(LIGHT_RIGHT>35&&LIGHT_LEFT>35){
			LIGHT12_Current(UDangle);
			Receive_USART2(); // 接收右激光数据
			Receive_USART6(); // 接收左激光数据
		}
    if (LIGHT_RIGHT > LIGHT_LEFT){
        if(fabs(LIGHT_LEFT - 15.0) > 1.0){
            move = (int)(15 - LIGHT_LEFT);
            Move_Y(move);
        }
        communication_updownL(UDangle, correct);
				flag_L=1;
    }
    else{
		    if(fabs(LIGHT_RIGHT - 15) > 1){
                move = (int)(LIGHT_RIGHT - 15);
                Move_Y(move);
            }
				communication_updownR(UDangle, correct);
				flag_R=1;
    }
}
void LIGHT3_COMPARE(UDangle){ // 激光测距48  98   174
		delay(LIGHTcomparedelay);
    Receive_USART3();
		if(LIGHT_FORWORD>=200){
			LIGHT3_Current(UDangle);
			Receive_USART3(); // 接收前激光数据
		}
    if (110 < LIGHT_FORWORD && LIGHT_FORWORD < 190){
        if(fabs(LIGHT_FORWORD - 156.0) > 1.0){
            move = (int)(LIGHT_FORWORD - 156);
            Move_X(move);
        }
    }
    else if (50<=LIGHT_FORWORD && LIGHT_FORWORD <=110 ){
        if(fabs(LIGHT_FORWORD - 80.0) > 1.0)
        {
            move = (int)(LIGHT_FORWORD - 80);
            Move_X(move);
        }
    }
    else if (LIGHT_FORWORD < 50){
        if(fabs(LIGHT_FORWORD - 30.0) > 1.0)
        {
            move = (int)(LIGHT_FORWORD - 30);
            Move_X(move);
        }
    }
}
int flag2_L=1,flag2_R=1,flag3_L=1,flag3_R=1;
void LIGHT3_COMPAREB_map(int Cangle){ // 激光测距48  98   174
    Receive_USART3();
    if (120 < LIGHT_FORWORD && LIGHT_FORWORD < 200){
        if(fabs(LIGHT_FORWORD - 166.0) > 1.0){
            move = (int)(LIGHT_FORWORD - 166);
            Move_X(move);
        }
				flag3_L=1,flag2_R=0,flag3_R=0;
    }
    else if (70<=LIGHT_FORWORD && LIGHT_FORWORD <=120 ){
        if(fabs(LIGHT_FORWORD - 90.0) > 1.0)
        {
            move = (int)(LIGHT_FORWORD - 90);
            Move_X(move);
        }
				flag3_L=0,flag2_R=0,flag3_R=1;
    }
    else if (LIGHT_FORWORD < 70){
        if(fabs(LIGHT_FORWORD - 40.0) > 1.0)
        {
            move = (int)(LIGHT_FORWORD - 40);
            Move_X(move);
        }
				flag3_L=1,flag3_R=1,flag2_R=1;
    }
}
void LIGHT3_COMPARER_map(int Cangle){ // 激光测距48  98   174
    Receive_USART3();
		Move_Angle(Cangle);
    if (120 < LIGHT_FORWORD && LIGHT_FORWORD < 200){
        if(fabs(LIGHT_FORWORD - 166.0) > 1.0){
            move = (int)(LIGHT_FORWORD - 166);
            Move_X(move);
        }
				flag3_R=1,flag2_L=0,flag3_L=0;
    }
    else if (70<=LIGHT_FORWORD && LIGHT_FORWORD <=120 ){
        if(fabs(LIGHT_FORWORD - 90.0) > 1.0)
        {
            move = (int)(LIGHT_FORWORD - 90);
            Move_X(move);
        }
				flag3_R=0,flag2_L=0,flag3_L=1;
    }
    else if (LIGHT_FORWORD < 70){
        if(fabs(LIGHT_FORWORD - 40.0) > 1.0)
        {
            move = (int)(LIGHT_FORWORD - 40);
            Move_X(move);
        }
				flag3_R=1,flag2_L=1,flag3_L=1;
    }
}
void LIGHTNOL_COMPARE(int UDangle, int correct){
		flag_L=0,flag_R=0;
		delay(LIGHTcomparedelay);
    Receive_USART6(); // 接收左激光数据
		if(LIGHT_LEFT>35){
			LIGHT12_Current(UDangle);
			Receive_USART6(); // 接收左激光数据
		}
    if(fabs(LIGHT_LEFT - 15.0) > 1.0){
        move = (int)(15 - LIGHT_LEFT);
        Move_Y(move);
    }
	communication_updownL(UDangle, correct);
	flag_L=1;
}
void LIGHTNOR_COMPARE(int UDangle, int correct) {
		flag_L=0,flag_R=0;
		delay(LIGHTcomparedelay);
    Receive_USART2(); // 接收右激光数据
		if(LIGHT_RIGHT>35){
			LIGHT12_Current(UDangle);
			Receive_USART2(); // 接收左激光数据
		}
    if(fabs(LIGHT_RIGHT - 15) > 1){
        move = (int)(LIGHT_RIGHT - 15);
        Move_Y(move);
    }
	communication_updownR(UDangle, correct);
	flag_R=1;
}
int k5R=1,k5B=-1,current5=4,flag5=0;
void LIGHT3B_compare5(int Cangle){
		Move_Y(10);
		Receive1_USART3();
		if(fabs(LIGHT_FORWORD-29)>1&&fabs(LIGHT_FORWORD-29)<80)Move_X(LIGHT_FORWORD-29);
		while(LIGHT_FORWORD>70){
			Move_Y(k5B*current5);
			Receive1_USART3();
			Move_Angle(Cangle);
			delay(LIGHTcomparedelay);
			flag5=1;
		}
		if(flag5==1){
			Receive1_USART3();
			if(fabs(LIGHT_FORWORD-29)>1&&fabs(LIGHT_FORWORD-29)<80){
					Move_X(LIGHT_FORWORD-29);
			}
			Move_Y(-15);
			flag5=0;
		}else Move_Y(-10);
		
}
void LIGHT3R_compare5(int Cangle){
		Move_Y(-10);
		Receive1_USART3();
		if(fabs(LIGHT_FORWORD-29)>1&&fabs(LIGHT_FORWORD-29)<80)Move_X(LIGHT_FORWORD-29);
		while(LIGHT_FORWORD>70){
			Move_Y(k5R*current5);
			Receive1_USART3();
			Move_Angle(Cangle);
			delay(LIGHTcomparedelay);
			flag5=1;
		}	
		if(flag5==1){
			Receive1_USART3();
			if(fabs(LIGHT_FORWORD-29)>1&&fabs(LIGHT_FORWORD-29)<80){
					Move_X(LIGHT_FORWORD-29);
			}
			Move_Y(15);
			flag5=0;
		}else Move_Y(10);
		
}
void usekey(){
		while(1){
        // 检测按键是否按下（低电平有效）
        if(GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET)
        {
            // 简单消抖
            delay(20);
            // 再次确认按键是否仍然按下
            if(GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET)
            {
                // 等待按键释放
                while(GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN) == Bit_RESET);
                // 按键已经按下并释放，现在开始执行主程序
                break;
            }
        }
    }
}
void testFINAL(){
    delay(1500);
    Move_X(10);
    Move_Y(20);
    Move_X(-20);
    Move_Y(-10);
    USART6_SendString("iSM", strlen(3));
    USART3_SendString("iLD:0", strlen("iLD:0"));
    USART2_SendString("iLD:0", strlen("iLD:0"));
    Move_Angle(0);
    Move_Angle(180);
    Move_Angle(90);
    Move_Angle(270);
    HUIDU_correct(0,0,1,3,2,0,0);
}
void test_angle(int x){
		delay(2000);
    Move_Angle(0);
    delay(3000);
    Move_Angle(x);
    delay(3000);
    Move_Angle(0);
}
void test_YAW(){
		delay(2000);
    test_angle(45);
    test_angle(90);
    test_angle(135);
    test_angle(180);
    test_angle(225);
    test_angle(270);
    test_angle(315);
    test_angle(360);
}
void test_ANGLE(){
		delay(2000);
    Current1 = Request_YAW();
    //  printf("Current1:%f\n",Current1);
    Move_Round(360);
    Current1 = Request_YAW();
    //  printf("Current1:%f\n",Current1);
}
void test_LIGHT(){
	delay(2000);
    USART6_SendString("iSM", strlen(3));
    USART3_SendString("iLD:0", strlen("iLD:0"));
    USART2_SendString("iLD:0", strlen("iLD:0"));
//	printf("forword\n",LIGHT_FORWORD);
    //	delay(3000);
    //	USART6_SendString("iLD:1", strlen("iLD:1"));
    //	USART6_SendString("iLD:1", strlen("iLD:1"));
    //	USART6_SendString("iLD:1", strlen("iLD:1"));
}
void test_HUIDU(){
		delay(2000);
		HUIDU_correct(0,0,1,3,2,0,0);
}
extern int lockStart;
void testR_map()
{ // 场外看场内起始位置在装球位左侧
    delay(1500);
		Move_Angle(0);
		Move_Y(-39);
    Move_Angle(0);
    Move_X(77); // 从出发点到取球位
    delay(1500);
    Move_Angle(0);
    Move_XYL(42);      // 对齐一号位y轴
		if(updown_eq==1){
			while (flag_out == 0){}; // 等待给上层发1
			flag_out = 0;
		}
    Move_Angle(90); // 顺时针转90
    Move_X(62);     // 一号位(145) Move_X(130);
    LIGHT12_Current(90);
    LIGHT12_COMPARE(90, 4); // 激光测距比较，然后回退到距货站15cm处
		if(flag_L==0){
			Move_XYL(47);
			Move_Angle(180);
			Move_X(29);
		}
		else{
			Move_X(45);
			Move_Angle(180);
			Move_X(82);
		}
		LIGHTNOR_Current(180);
		LIGHTNOR_COMPARE(180,4);
		Move_X(-46);
		Move_Angle(90);
		Move_X(66);
    LIGHT3_Current(90);
    LIGHT3_COMPARER_map(90); // 激光测距比较，到距货站处40||90||166
		Move_XYR(42);
    Move_Angle(90);
    Move_X(25); // 二号位   
    LIGHT12_Current(90);
    LIGHT12_COMPARE(90, 4); // 激光测距比较，然后回退到距货站15cm处
		if(flag3_L==0&&flag2_L==0){
			Move_XYL(40);
			Move_X(43);
		}else{
			Move_X(90);             // 对齐三号位y轴
			Move_Angle(180);
			Move_X(40); // 三号位
		}
		YAW_DETA -= 1;
    LIGHT12_Current(180);
    LIGHT12_COMPARE(180, 4); // 激光测距比较，然后回退到距货站15cm处
    Move_X(80);              // 四号位
		YAW_DETA -= 2;
    LIGHT12_Current(180);
    LIGHT12_COMPARE(180, 4); // 激光测距比较，然后回退到距货站15cm处
		if(flag_L==0){
			Move_XYL(45);
			Move_Angle(270);
		}else{
			Move_X(43);              // 对齐跷跷板&五号位
			Move_Angle(270);
			Move_X(45); // 跳板90
		}
//	  Change_Speed(1400,15000);
    Move_X(107); // 跷跷板90
		YAW_DETA -= 2;
//		Change_Speed(limitspeed,speed_limit_maxi);
		Move_Angle(270);
    Move_X(69);
    LIGHT3R_compare5(270);
    Move_X(54); // 五号位52
    LIGHT12_Current(270);
    LIGHT12_COMPARE(270, 4); // 激光测距比较，然后回退到距货站15cm处
		if(flag_L==0){
			Move_XYL(26);
			Move_X(113);
		}else{
			Move_X(28);
			Move_XYL(30);
			Move_X(80);
		}
    HUIDU_correct(270,0,1,2,2,2,-3);
}

void testB_map()
{ // 场外看场内起始位置在装球位右侧
    // YAW_DETA越小，越向顺时针转
     delay(1500);
		Move_Angle(0);
		Move_Y(39);
    Move_Angle(0);
    Move_X(77); // 从出发点到取球位
    delay(1500);
    Move_Angle(0);
    Move_XYR(40);      // 对齐一号位y轴
		if(updown_eq==1){
			while (flag_out == 0){}; // 等待给上层发1
			flag_out = 0;
		}
    Move_Angle(270); // 顺时针转90
    Move_X(62);     // 一号位(145) Move_X(130);
    LIGHT12_Current(270);
    LIGHT12_COMPARE(270, 4); // 激光测距比较，然后回退到距货站15cm处
		YAW_DETA += 1;
		if(flag_R==0){
			Move_XYR(45);
			Move_Angle(180);
			Move_X(33);
		}
		else{
			Move_X(45);
			Move_Angle(180);
			Move_X(82);
		}
		LIGHTNOL_Current(180);
		LIGHTNOL_COMPARE(180,4);
		Move_X(-46);
		Move_Angle(270);
		Move_X(64);
    LIGHT3_Current(270);
    LIGHT3_COMPAREB_map(270); // 激光测距比较，到距货站处40||90||166
		Move_XYL(38);
    Move_Angle(270);
    Move_X(26); // 二号位   
    LIGHT12_Current(270);
    LIGHT12_COMPARE(270, 4); // 激光测距比较，然后回退到距货站15cm处
		if(flag3_R==0&&flag2_R==0){
			Move_XYR(38);
			Move_X(45);
		}else{
			Move_X(90);             // 对齐三号位y轴
			Move_Angle(180);
			Move_X(40); // 三号位
		}
    LIGHT12_Current(180);
    LIGHT12_COMPARE(180, 4); // 激光测距比较，然后回退到距货站15cm处
    Move_X(80);              // 四号位
		YAW_DETA += 2;
    LIGHT12_Current(180);
    LIGHT12_COMPARE(180, 4); // 激光测距比较，然后回退到距货站15cm处
		YAW_DETA += 2;
		if(flag_R==0){
			Move_XYR(39);
			Move_Angle(90);
		}else{
			Move_X(39);              // 对齐跷跷板&五号位
			Move_Angle(90);
			Move_X(39); // 跳板90
		}
//	  Change_Speed(1400,15000);
    Move_X(113); // 跷跷板90
		YAW_DETA += 2;
//		Change_Speed(limitspeed,speed_limit_maxi);
		Move_Angle(90);
    Move_X(69);
		LIGHT3B_compare5(90);
    Move_X(54); // 五号位52
    LIGHT12_Current(90);
    LIGHT12_COMPARE(90, 4); // 激光测距比较，然后回退到距货站15cm处
		if(flag_R==0){
			Move_XYR(30);
			Move_X(106);
		}else{
			Move_X(26);
			Move_XYR(30);
			Move_X(80);	
		}
    HUIDU_correct(90,0,1,2,2,2,3);
}
int main(void)
{
    NowClockSet();
    systemInit();
    RecvTimeInit();
		HD_Init();
		Mykey_Init();
    speed_Init();
    PID_Init(&left1_pid);
    PID_Init(&left2_pid);
    PID_Init(&right1_pid);
    PID_Init(&right2_pid);
    PID_Init(&x1_pid);
    PID_Init(&x2_pid);
    PID_Init(&x3_pid);
    PID_Init(&x4_pid);
    /**
     * 配置梳理到目前为止 串口1,2,3,5,6被配置为115200
     * 		电机PWM 输出被配置为 	Dianji_Tim1_Config(16800, 0);//168*1000*1000/168000 = 10khz , PWM 满值10k
     *		TIM3,4,5,8 被配置为计数器，获取编码器输入
     * 		TIM2 被配置为定时器，定时读取编码器数值 	EncoderRead_TIM2(50 - 1, 16800 - 1);//168*1000*1000/16800 = 10khz /50 = 200hz
     */
    // 前后轮毂外径距离35cm，左右轮毂外径距离28cm,前后轮廓38.4cm,左右轮廓30.6cm
    // 扫码距离12cm
    ///-------------- PID 设置 ----------------
    SetLeft1PID(16, 4, 0);//8,2,0
    SetLeft2PID(16, 4, 0);
    SetRight1PID(16, 4, 0);
    SetRight2PID(16, 4, 0);

    SetX1PID(8, 1.35, 5);
    SetX2PID(8, 1.35, 5);
    SetX3PID(8, 1.35, 5);
    SetX4PID(8, 1.35, 5);
		updown_eq=1;
		usekey();
//	///-------------- 主函数 ----------------
		testR_map();
		//testRIGHT();
		//testFINAL();
	//   test_ANGLE();
	//		test_HUIDU();
    while (1)
    {
    };
}
