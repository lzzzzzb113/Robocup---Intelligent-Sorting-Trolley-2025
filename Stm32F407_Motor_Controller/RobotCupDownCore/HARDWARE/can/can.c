#include "can.h"
#include "system.h"
u8 rximu[64];
u8 rxahrs[56];
u8 rxinsgps[80];
CanRxMsg RxMsg;
u8 rxbuf[8];
u8 rxcan_nine[10][8];
u8 can_send=0;
u8 can_init=0;
u8 can_rece=0;
u8 last_flag=0;
u8 count0=0;
long long can_imu=0;
float tmp1=0;
int imutype =0;
int ahrstype =0;
unsigned char tmpacc;

IMUData_Packet_t IMUData_Packet;
AHRSData_Packet_t AHRSData_Packet;
/**************************************************************************
Function: CAN1 initialization
Input   : tsjw：Resynchronize the jump time unit, Scope: 1 ~ 3;
 			    tbs2：Time unit of time period 2, range :1~8;
 			    tbs1：Time unit of time period 1, range :1~16;
 			    brp ：Baud rate divider, range :1 to 1024;(We're actually going to add 1, which is 1 to 1024) tq=(brp)*tpclk1
 			    mode：0, normal mode;1. Loop mode;
Output  : 0- Initialization successful;Other - initialization failed
Note: none of the entry parameters (except mode) can be 0
函数功能：CAN1初始化
入口参数：tsjw：重新同步跳跃时间单元，范围:1~3;
 			    tbs2：时间段2的时间单元，范围:1~8;
 			    tbs1：时间段1的时间单元，范围:1~16;
 			    brp ：波特率分频器，范围:1~1024;(实际要加1,也就是1~1024) tq=(brp)*tpclk1
 			    mode：0,普通模式;1,回环模式;
返回  值：0-初始化成功; 其他-初始化失败
注意：入口参数(除了mode)均不能为0
波特率/Baud rate=Fpclk1/((tbs1+tbs2+1)*brp)，Fpclk1为36M
                =42M/((3+2+1)*6)
						    =1M
**************************************************************************/
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	u16 i=0;
 	if(tsjw==0||tbs2==0||tbs1==0||brp==0)return 1;
	tsjw-=1; //Subtract 1 before setting //先减去1.再用于设置
	tbs2-=1;
	tbs1-=1;
	brp-=1;

	//使能相关时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能PORTB时钟	                   											 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能CAN1时钟	
	//初始化GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化PB8 PB9
//	//引脚复用映射配置
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_CAN1); //GPIOB8复用为CAN1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_CAN1); //GPIOB9复用为CAN1

	CAN1->MCR=0x0000;	//Exit sleep mode (setting all bits to 0 at the same time) //退出睡眠模式(同时设置所有位为0)
	CAN1->MCR|=1<<0;	//Request CAN1 to enter initialization mode //请求CAN1进入初始化模式
	while((CAN1->MSR&1<<0)==0)
	{
		i++;
		if(i>100)return 2; //Failed to enter initialization mode //进入初始化模式失败
	}
	//Non-time triggered communication mode
	//非时间触发通信模式
	CAN1->MCR|=0<<7;
  //Software automatic offline management	
	//软件自动离线管理
	CAN1->MCR|=0<<6;	
	//Sleep mode is awakened by software (clear CAN1- >;
  //睡眠模式通过软件唤醒(清除CAN1->MCR的SLEEP位)	
	CAN1->MCR|=0<<5;
	//Disallow automatic message transmission
  //禁止报文自动传送	
	CAN1->MCR|=1<<4;
	//Messages are not locked, the new overwrites the old
  //报文不锁定,新的覆盖旧的	
	CAN1->MCR|=0<<3;
	//The priority is determined by the message identifier	
  //优先级由报文标识符决定  
	CAN1->MCR|=0<<2;
  //Clear the original Settings	
  //清除原来的设置	
	CAN1->BTR=0x00000000; 
	//Mode set to 0, normal mode;1. Loop mode;
	//模式设置 0,普通模式;1,回环模式;
	CAN1->BTR|=mode<<30;
  //Resynchronization jump width (TSJW) is TSJW +1 time unit	
	//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位
	CAN1->BTR|=tsjw<<24; 
  //Tbs2= Tbs2 +1 time unit	
	//Tbs2=tbs2+1个时间单位
	CAN1->BTR|=tbs2<<20; 
	//Tbs1= Tbs1 +1 time unit	
  //Tbs1=tbs1+1个时间单位	
	CAN1->BTR|=tbs1<<16;
	//Frequency division coefficient (Fdiv) is brp +1, boulder rate: Fpclk1/((Tbs1+Tbs2+1)*Fdiv)
  //分频系数(Fdiv)为brp+1，波特率:Fpclk1/((Tbs1+Tbs2+1)*Fdiv)
	CAN1->BTR|=brp<<0;  
  //Request CAN1 to exit initialization mode	
  //请求CAN1退出初始化模式			
	CAN1->MCR&=~(1<<0);	  
	while((CAN1->MSR&1<<0)==1)
	{
		i++;
		if(i>0XFFF0)return 3; //Failed to exit initialization mode //退出初始化模式失败
	}
	/*** Filter initialization || 过滤器初始化 ***/
	//Filter groups work in initialization mode
	//过滤器组工作在初始化模式
	CAN1->FMR|=1<<0;	
	//Filter 0 is not active
  //过滤器0不激活	
	CAN1->FA1R&=~(1<<0);	
	//The filter bit width is 32 bits
  //过滤器位宽为32位	
	CAN1->FS1R|=1<<0; 
	//Filter 0 works in identifier masking bit mode
  //过滤器0工作在标识符屏蔽位模式	
	CAN1->FM1R|=0<<0;	
	//Filter 0 is associated with FIFO0
  //过滤器0关联到FIFO0	
	CAN1->FFA1R|=0<<0;	
  //32 bit ID	
	//32位ID
	CAN1->sFilterRegister[0].FR1=0X00000000;
	//32-bit MASK
	//32位MASK
	CAN1->sFilterRegister[0].FR2=0X00000000;
	//Activation filter 0
	//激活过滤器0
	CAN1->FA1R|=1<<0;	
	//Filter group enters normal mode
  //过滤器组进入正常模式	
	CAN1->FMR&=0<<0;			

#if CAN1_RX0_INT_ENABLE
  //Enable to interrupt reception //使能中断接收
	
	//FIFO0消息挂号中断允许
	CAN1->IER|=1<<1;			
	
	//Configure CAN to receive interrupts
	//配置CAN接收中断
  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  //Preemption priority	
	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Son priority
	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  //IRQ channel enablement
	//IRQ通道使能	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  //Initializes the VIC register according to the specified parameters 
	//根据指定的参数初始化VIC寄存器	
	NVIC_Init(&NVIC_InitStructure);	

  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
#endif
	return 0;
}   
/**************************************************************************
Function: CAN sends data
Input   : id:Standard ID(11 bits)/ Extended ID(11 bits +18 bits)
			    ide:0, standard frame;1, extension frames
			    rtr:0, data frame;1, remote frame
			    len:Length of data to be sent (fixed at 8 bytes, valid data is 6 bytes in time-triggered mode) 
			    *dat:Pointer to the data
Output  : 0~3, mailbox number. 0xFF, no valid mailbox
函数功能：CAN发送数据
入口参数：id:标准ID(11位)/扩展ID(11位+18位)	    
			    ide:0,标准帧;1,扩展帧
			    rtr:0,数据帧;1,远程帧
			    len:要发送的数据长度(固定为8个字节,在时间触发模式下,有效数据为6个字节)
			    *dat:数据指针.
返回  值：0~3,邮箱编号.0XFF,无有效邮箱
**************************************************************************/
u8 CAN1_Tx_Msg(u32 id,u8 ide,u8 rtr,u8 len,u8 *dat)
{	   
	u8 mbox;	  
	if(CAN1->TSR&(1<<26))mbox=0;		  //Mailbox 0 is empty //邮箱0为空
	else if(CAN1->TSR&(1<<27))mbox=1;	//Mailbox 1 is empty //邮箱1为空
	else if(CAN1->TSR&(1<<28))mbox=2;	//Mailbox 2 is empty //邮箱2为空
	else return 0XFF;					        //No empty mailbox, cannot send //无空邮箱,无法发送 
	
	CAN1->sTxMailBox[mbox].TIR=0; //Clear the previous Settings //清除之前的设置		
	if(ide==0) //The standard frame //标准帧
	{
		id&=0x7ff; //Take the low 11 bit STDID //取低11位stdid
		id<<=21;		  
	}else	//Extend the frame //扩展帧
	{
		id&=0X1FFFFFFF; //Take a low 32-bit extid //取低32位extid
		id<<=3;									   
	}
	CAN1->sTxMailBox[mbox].TIR|=id;		 
	CAN1->sTxMailBox[mbox].TIR|=ide<<2;	  
	CAN1->sTxMailBox[mbox].TIR|=rtr<<1;
	len&=0X0F; //Get lower 4 bits //得到低四位
	CAN1->sTxMailBox[mbox].TDTR&=~(0X0000000F);
	CAN1->sTxMailBox[mbox].TDTR|=len;	//Set the DLC	//设置DLC
	//The data to be sent is stored in the mailbox
	//待发送数据存入邮箱
	CAN1->sTxMailBox[mbox].TDHR=(((u32)dat[7]<<24)|
								((u32)dat[6]<<16)|
 								((u32)dat[5]<<8)|
								((u32)dat[4]));
	CAN1->sTxMailBox[mbox].TDLR=(((u32)dat[3]<<24)|
								((u32)dat[2]<<16)|
 								((u32)dat[1]<<8)|
								((u32)dat[0]));
	CAN1->sTxMailBox[mbox].TIR|=1<<0; //Request to send mailbox data//请求发送邮箱数据
	return mbox;
}
/**************************************************************************
Function: Get the send status
Input   : Mbox: mailbox number
Output  : 0, hang;0X05, send failed;0X07, successful transmission
函数功能：获得发送状态
入口参数：mbox：邮箱编号
返回  值：0,挂起;0X05,发送失败;0X07,发送成功
**************************************************************************/
u8 CAN1_Tx_Staus(u8 mbox)
{	
	u8 sta=0;					    
	switch (mbox)
	{
		case 0: 
			sta |= CAN1->TSR&(1<<0);			   //RQCP0
			sta |= CAN1->TSR&(1<<1);			   //TXOK0
			sta |=((CAN1->TSR&(1<<26))>>24); //TME0
			break;
		case 1: 
			sta |= CAN1->TSR&(1<<8)>>8;		   //RQCP1
			sta |= CAN1->TSR&(1<<9)>>8;		   //TXOK1
			sta |=((CAN1->TSR&(1<<27))>>25); //TME1	   
			break;
		case 2: 
			sta |= CAN1->TSR&(1<<16)>>16;	   //RQCP2
			sta |= CAN1->TSR&(1<<17)>>16;	   //TXOK2
			sta |=((CAN1->TSR&(1<<28))>>26); //TME2
			break;
		default:
			sta=0X05; //Wrong email number, failed //邮箱号不对,失败
		break;
	}
	return sta;
} 
/**************************************************************************
Function: Returns the number of packets received in FIFO0/FIFO1
Input   : Fifox: FIFO number (0, 1)
Output  : Number of packets in FIFO0/FIFO1
函数功能：得到在FIFO0/FIFO1中接收到的报文个数
入口参数：fifox：FIFO编号（0、1）
返回  值：FIFO0/FIFO1中的报文个数
**************************************************************************/
u8 CAN1_Msg_Pend(u8 fifox)
{
	if(fifox==0)return CAN1->RF0R&0x03; 
	else if(fifox==1)return CAN1->RF1R&0x03; 
	else return 0;
}
/**************************************************************************
Function: Receive data
Input   : fifox：Email
		    	id:Standard ID(11 bits)/ Extended ID(11 bits +18 bits)
			    ide:0, standard frame;1, extension frames 
			    rtr:0, data frame;1, remote frame
			    len:Length of data received (fixed at 8 bytes, valid at 6 bytes in time-triggered mode)
			    dat:Data cache
Output  : none
函数功能：接收数据
入口参数：fifox：邮箱号
		    	id:标准ID(11位)/扩展ID(11位+18位)
			    ide:0,标准帧;1,扩展帧
			    rtr:0,数据帧;1,远程帧
			    len:接收到的数据长度(固定为8个字节,在时间触发模式下,有效数据为6个字节)
			    dat:数据缓存区
返回  值：无 
**************************************************************************/
void CAN1_Rx_Msg(u8 fifox,u32 *id,u8 *ide,u8 *rtr,u8 *len,u8 *dat)
{	   
	*ide=CAN1->sFIFOMailBox[fifox].RIR&0x04; //Gets the value of the identifier selection bit //得到标识符选择位的值  
 	if(*ide==0) //Standard identifier //标准标识符
	{
		*id=CAN1->sFIFOMailBox[fifox].RIR>>21;
	}else	     //Extended identifier //扩展标识符
	{
		*id=CAN1->sFIFOMailBox[fifox].RIR>>3;
	}
	*rtr=CAN1->sFIFOMailBox[fifox].RIR&0x02;	//Gets the remote send request value //得到远程发送请求值
	*len=CAN1->sFIFOMailBox[fifox].RDTR&0x0F; //Get the DLC //得到DLC
 	//*fmi=(CAN1->sFIFOMailBox[FIFONumber].RDTR>>8)&0xFF; //Get the FMI //得到FMI
	//Receive data //接收数据
	dat[0]=CAN1->sFIFOMailBox[fifox].RDLR&0XFF;
	dat[1]=(CAN1->sFIFOMailBox[fifox].RDLR>>8)&0XFF;
	dat[2]=(CAN1->sFIFOMailBox[fifox].RDLR>>16)&0XFF;
	dat[3]=(CAN1->sFIFOMailBox[fifox].RDLR>>24)&0XFF;    
	dat[4]=CAN1->sFIFOMailBox[fifox].RDHR&0XFF;
	dat[5]=(CAN1->sFIFOMailBox[fifox].RDHR>>8)&0XFF;
	dat[6]=(CAN1->sFIFOMailBox[fifox].RDHR>>16)&0XFF;
	dat[7]=(CAN1->sFIFOMailBox[fifox].RDHR>>24)&0XFF;    
  if(fifox==0)CAN1->RF0R|=0X20;      //Free the FIFO0 mailbox //释放FIFO0邮箱
	else if(fifox==1)CAN1->RF1R|=0X20; //Free the FIFO1 mailbox //释放FIFO1邮箱	 
}
/**************************************************************************
Function: CAN receives interrupt service function, conditional compilation
Input   : none
Output  : none
函数功能：CAN接收中断服务函数，条件编译
入口参数：无
返回  值：无 
**************************************************************************/
#if CAN1_RX0_INT_ENABLE	//Enable RX0 interrupt //使能RX0中断	    
void CAN1_RX0_IRQHandler(void)
{
	u8 i,k;
	static u8 imu_flag=0;
	static u8 acc_flag=0;

  static u8 Count_can=0;
	static u8 last_num=0;
	CAN_Receive(CAN1,CAN_FIFO0, &RxMsg);
  can_rece=1;
	
	if(RxMsg.Data[0]==0xFC && last_num==0xFD) //判断有帧头帧尾，上一帧数据的帧尾在这一帧帧头之前
	{
		Count_can=1;	
		if((RxMsg.Data[1]==TYPE_IMU)&&(RxMsg.Data[2]==IMU_LEN))   
			imu_flag=1;
		if((RxMsg.Data[1]==TYPE_AHRS)&&(RxMsg.Data[2]==AHRS_LEN)) acc_flag=1;
	}
	last_num=RxMsg.Data[7];

	if(Count_can)  //确认数据有效，开始接收数据
	{
		 for(i=0;i<8;i++)
		{ 
			rxcan_nine[Count_can-1][i]=RxMsg.Data[i];	 //将原始数据存放至二维数组中
		}
	  Count_can=Count_can+1;
	}
	
	if(imu_flag==1 && Count_can==IMU_CAN)
	{
		Count_can=0;
	  imu_flag=0;
		imutype=1;
		for(k=0;k<(IMU_CAN-1);k++)
		{
			for(i=0;i<8;i++)
			{
				rximu[i+(k*8)]=rxcan_nine[k][i];  //将本帧数据保存至rximu数组中
			}
		}
	}
	if(acc_flag==1 && Count_can==AHRS_CAN)
	{
		Count_can=0;
		acc_flag=0;
		ahrstype=1;
		for(k=0;k<(AHRS_CAN-1);k++)
		{
			for(i=0;i<8;i++)
			{
				rxahrs[i+(k*8)]=rxcan_nine[k][i];  //将本帧数据保存至rximu数组中
			}
		}
	}
	//0x41
	if(rxcan_nine[0][1]==TYPE_INSGPS&&rxcan_nine[0][2]==INSGPS_LEN)  //10 这里只判断类型，不保存数据，因为没用到这个类型的数据
	{
		imutype=3;
		if(Count_can==INSGPS_CAN) 
		{
			Count_can=0;
		}
	}
}
/*************
实现16进制的can数据转换成浮点型数据
****************/
u8 Can_Hex2Dec(void)
{
	 if(ahrstype==1)
	{
		if(rxahrs[1]==TYPE_AHRS&&rxahrs[2]==AHRS_LEN)
		{		
		AHRSData_Packet.RollSpeed=DATA_Trans(rxahrs[7],rxahrs[8],rxahrs[9],rxahrs[10]);       //横滚角速度
		AHRSData_Packet.PitchSpeed=DATA_Trans(rxahrs[11],rxahrs[12],rxahrs[13],rxahrs[14]);   //俯仰角速度
		AHRSData_Packet.HeadingSpeed=DATA_Trans(rxahrs[15],rxahrs[16],rxahrs[17],rxahrs[18]); //偏航角速度
			
    AHRSData_Packet.Roll=DATA_Trans(rxahrs[19],rxahrs[20],rxahrs[21],rxahrs[22]);      //横滚角
		AHRSData_Packet.Pitch=DATA_Trans(rxahrs[23],rxahrs[24],rxahrs[25],rxahrs[26]);     //俯仰角
		AHRSData_Packet.Heading=DATA_Trans(rxahrs[27],rxahrs[28],rxahrs[29],rxahrs[30]);	 //偏航角
			
		AHRSData_Packet.Qw=DATA_Trans(rxahrs[31],rxahrs[32],rxahrs[33],rxahrs[34]);  //四元数
		AHRSData_Packet.Qx=DATA_Trans(rxahrs[35],rxahrs[36],rxahrs[37],rxahrs[38]);
		AHRSData_Packet.Qy=DATA_Trans(rxahrs[39],rxahrs[40],rxahrs[41],rxahrs[42]);
		AHRSData_Packet.Qz=DATA_Trans(rxahrs[43],rxahrs[44],rxahrs[45],rxahrs[46]);
		AHRSData_Packet.Timestamp=timestamp(rxahrs[47],rxahrs[48],rxahrs[49],rxahrs[50]);   //时间戳
		AHRSData2PC();
	

		}
	ahrstype=0;
 }
		if(imutype==1)
	{
		if(rximu[1]==TYPE_IMU&&rximu[2]==IMU_LEN)
		{
			
		IMUData_Packet.gyroscope_x=DATA_Trans(rximu[7],rximu[8],rximu[9],rximu[10]);  //角速度
		IMUData_Packet.gyroscope_y=DATA_Trans(rximu[11],rximu[12],rximu[13],rximu[14]);
		IMUData_Packet.gyroscope_z=DATA_Trans(rximu[15],rximu[16],rximu[17],rximu[18]);
			
		IMUData_Packet.accelerometer_x=DATA_Trans(rximu[19],rximu[20],rximu[21],rximu[22]);  //线加速度
		IMUData_Packet.accelerometer_y=DATA_Trans(rximu[23],rximu[24],rximu[25],rximu[26]);
		IMUData_Packet.accelerometer_z=DATA_Trans(rximu[27],rximu[28],rximu[29],rximu[30]);

		IMUData_Packet.magnetometer_x=DATA_Trans(rximu[31],rximu[32],rximu[33],rximu[34]);  //磁力计数据
		IMUData_Packet.magnetometer_y=DATA_Trans(rximu[35],rximu[36],rximu[37],rximu[38]);
		IMUData_Packet.magnetometer_z=DATA_Trans(rximu[39],rximu[40],rximu[41],rximu[42]);
			
		IMUData_Packet.Timestamp=timestamp(rximu[55],rximu[56],rximu[57],rximu[58]);   //时间戳

    IMUData2PC();

		}
		imutype=0;
 }
 return 0;
}
/*************
实现16进制的can数据转换成浮点型数据
****************/
float DATA_Trans(u8 Data_1,u8 Data_2,u8 Data_3,u8 Data_4)
{
  u32 transition_32;
	float tmp=0;
	int sign=0;
	int exponent=0;
	float mantissa=0;
  transition_32 = 0;
  transition_32 |=  Data_4<<24;   
  transition_32 |=  Data_3<<16; 
	transition_32 |=  Data_2<<8;
	transition_32 |=  Data_1;
  sign = (transition_32 & 0x80000000) ? -1 : 1;//符号位
	//先右移操作，再按位与计算，出来结果是30到23位对应的e
	exponent = ((transition_32 >> 23) & 0xff) - 127;
	//将22~0转化为10进制，得到对应的x系数 
	mantissa = 1 + ((float)(transition_32 & 0x7fffff) / 0x7fffff);
	tmp=sign * mantissa * pow(2, exponent);
	return tmp;
}
long long timestamp(u8 Data_1,u8 Data_2,u8 Data_3,u8 Data_4)
{
  u32 transition_32;
  transition_32 = 0;
  transition_32 |=  Data_4<<24;   
  transition_32 |=  Data_3<<16; 
	transition_32 |=  Data_2<<8;
	transition_32 |=  Data_1;
	return transition_32;
}
#endif

/**************************************************************************
Function: CAN1 sends a set of data (fixed format :ID 0X601, standard frame, data frame)
Input   : msg:Pointer to the data
    			len:Data length (up to 8)
Output  : 0, success, others, failure;
函数功能：CAN1发送一组数据(固定格式:ID为0X601,标准帧,数据帧)
入口参数：msg:数据指针
    			len:数据长度(最大为8)
返回  值：0,成功，其他,失败;
**************************************************************************/
u8 CAN1_Send_Msg(u8* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;	  	 						       
  mbox=CAN1_Tx_Msg(0X601,0,0,len,msg);   
	while((CAN1_Tx_Staus(mbox)!=0X07)&&(i<0XFFF))i++; //Waiting for the end of sending //等待发送结束
	if(i>=0XFFF)return 1; //Send failure //发送失败
	return 0;	//Send a success //发送成功									
}
/**************************************************************************
Function: The CAN1 port receives data queries
Input   : Buf: The data cache
Output  : 0, number of data received, other, length of data received
函数功能：CAN1口接收数据查询
入口参数：buf:数据缓存区
返回  值：0,无数据被收到，其他,接收的数据长度
**************************************************************************/
u8 CAN1_Receive_Msg(u8 *buf)
{		   		   
	u32 id;
	u8 ide,rtr,len; 
	if(CAN1_Msg_Pend(0)==0)return 0;			   //No data received, exit directly //没有接收到数据,直接退出 	 
  	CAN1_Rx_Msg(0,&id,&ide,&rtr,&len,buf); //Read the data //读取数据
    if(id!=0x12||ide!=0||rtr!=0)len=0;		 //Receive error //接收错误	   
	return len;	
}
/**************************************************************************
Function: Can1 sends a set of data tests
Input   : msg:Pointer to the data
			    len:Data length (up to 8)
Output  : 0, success, 1, failure
函数功能：CAN1发送一组数据测试
入口参数：msg:数据指针
			    len:数据长度(最大为8)
返回  值：0,成功，1,失败
**************************************************************************/
u8 CAN1_Send_MsgTEST(u8* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;	  	 						       
    mbox=CAN1_Tx_Msg(0X701,0,0,len,msg);   
	while((CAN1_Tx_Staus(mbox)!=0X07)&&(i<0XFFF))i++; //Waiting for the end of sending //等待发送结束
	if(i>=0XFFF)return 1;	//Send failure //发送失败
	return 0;	//Send a success //发送成功
}
/**************************************************************************
Function: Sends an array to the given ID
Input   : id：ID no.
			    msg：The transmitted data pointer
Output  : 0, success, 1, failure
函数功能：给给定的id发送一个数组的命令
入口参数：id：ID号
			    msg：被输送数据指针
返回  值：0,成功，1,失败
**************************************************************************/
u8 CAN1_Send_Num(u32 id,u8* msg)
{
	u8 mbox;
	u16 i=0;	  	 						       
  mbox=CAN1_Tx_Msg(id,0,0,8,msg);   
	while((CAN1_Tx_Staus(mbox)!=0X07)&&(i<0XFFF))i++; //Waiting for the end of sending //等待发送结束
	if(i>=0XFFF)return 1;	//Send failure //发送失败
	return 0;
}
