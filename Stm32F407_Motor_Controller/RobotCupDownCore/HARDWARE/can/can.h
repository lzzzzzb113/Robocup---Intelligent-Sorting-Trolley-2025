#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
#include "system.h"
 
//CAN1 receives RX0 interrupt enablement
//CAN1接收RX0中断使能
#define CAN1_RX0_INT_ENABLE	1	//0, not enabling;1, can make //0,不使能; 1,使能								    		
typedef struct IMUData_Packet_t{
		float gyroscope_x;          //unit: rad/s
		float gyroscope_y;          //unit: rad/s
		float gyroscope_z;          //unit: rad/s
		float accelerometer_x;      //m/s^2
		float accelerometer_y;      //m/s^2
		float accelerometer_z;      //m/s^2
		float magnetometer_x;       //mG
		float magnetometer_y;       //mG
		float magnetometer_z;       //mG
		float imu_temperature;      //C
		float Pressure;             //Pa
		float pressure_temperature; //C
		u32 Timestamp;          //us
} IMUData_Packet_t;

typedef struct AHRSData_Packet_t
{
	float RollSpeed;   //unit: rad/s
	float PitchSpeed;  //unit: rad/s
	float HeadingSpeed;//unit: rad/s
	float Roll;        //unit: rad
	float Pitch;       //unit: rad
	float Heading;     //unit: rad
	float Qw;//w          //Quaternion
	float Qx;//x
	float Qy;//y
	float Qz;//z
	u32 Timestamp; //unit: us
}AHRSData_Packet_t;
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);
u8 CAN1_Tx_Msg(u32 id,u8 ide,u8 rtr,u8 len,u8 *dat);		
u8 CAN1_Msg_Pend(u8 fifox);							
void CAN1_Rx_Msg(u8 fifox,u32 *id,u8 *ide,u8 *rtr,u8 *len,u8 *dat);
u8 CAN1_Tx_Staus(u8 mbox);  								
u8 CAN1_Send_Msg(u8* msg,u8 len);						
u8 CAN1_Receive_Msg(u8 *buf);						

u8 CAN1_Send_MsgTEST(u8* msg,u8 len);
u8 CAN1_Send_Num(u32 id,u8* msg);

u8 Can_Hex2Dec(void);
float DATA_Trans(u8 Data_1,u8 Data_2,u8 Data_3,u8 Data_4);
long long timestamp(u8 Data_1,u8 Data_2,u8 Data_3,u8 Data_4);

extern IMUData_Packet_t IMUData_Packet;
extern AHRSData_Packet_t AHRSData_Packet;
extern u8 can_init;
extern u8 can_send;
extern u8 can_rece;
void can_data_transition(void);

#endif

















