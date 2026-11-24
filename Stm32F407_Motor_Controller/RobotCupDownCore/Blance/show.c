#include "show.h"

/**************************************************************************
**************************************************************************/
void show_task(void *pvParameters)
{
   u32 lastWakeTime = getSysTickCnt();
   while(1)
   {	
		vTaskDelayUntil(&lastWakeTime, F2T(RATE_10_HZ));//This task runs at 10Hz //此任务以10Hz的频率运行
		
	  oled_show(); //Tasks are displayed on the screen //显示屏显示任务
   }
}  
void oled_show(void)
{  
	static int a=1,r,p,y;
	float rad_ro_degree=360/2/3.14159;
	a++;
	OLED_ShowString(0,0,"TYPE:");  
	printf("TYPE:");     
	if(can_rece)
	{OLED_ShowString(40,0,"CAN");  
	printf ("CAN:");}
  else if(ttl_receive)
	{
	OLED_ShowString(40,0,"TTL");
				printf("TTL");
	}
	OLED_ShowNumber(80,0, a,5,12);
			printf("%d\n",a);	
	OLED_ShowString(0,10,"Roll:"); 
	OLED_ShowString(0,25,"Pitch:"); 
	OLED_ShowString(0,40,"Yaw:"); 

	
	
//	if(IMUData_Packet.accelerometer_x<0)	  OLED_ShowString(30,10,"-"),
//													  OLED_ShowNumber(35,10,-((int)(IMUData_Packet.accelerometer_x*1000)),5,12);
//	 else                 	  OLED_ShowString(30,10,"+"),
//													  OLED_ShowNumber(35,10, ((int)(IMUData_Packet.accelerometer_x*1000)),5,12);
//	if(IMUData_Packet.accelerometer_y<0)	  OLED_ShowString(30,25,"-"),
//													  OLED_ShowNumber(35,25,-((int)(IMUData_Packet.accelerometer_y*1000)),5,12);
//	 else                 	  OLED_ShowString(30,25,"+"),
//													  OLED_ShowNumber(35,25,((int)(IMUData_Packet.accelerometer_y*1000)),5,12);
//	if(IMUData_Packet.accelerometer_z<0)	  OLED_ShowString(30,40,"-"),
//													  OLED_ShowNumber(35,40,-((int)(IMUData_Packet.accelerometer_z*1000)),5,12);
//	 else                 	  OLED_ShowString(30,40,"+"),
//													  OLED_ShowNumber(35,40, ((int)(IMUData_Packet.accelerometer_z*1000)),5,12);
		if(AHRSData_Packet.Roll<0)	  
			{OLED_ShowString(50,10,"-"),
			OLED_ShowNumber(55,10,-((int)(AHRSData_Packet.Roll*rad_ro_degree)),5,12);
			printf ("Roll: %d\n",-((int)(AHRSData_Packet.Roll*rad_ro_degree)));
				r=-((int)(AHRSData_Packet.Roll*rad_ro_degree));
				printf ("Roll: %d\n",r);
		}
	 else                 	  
		 {OLED_ShowString(50,10,"+"),
			OLED_ShowNumber(55,10, ((int)(AHRSData_Packet.Roll*rad_ro_degree)),5,12);
		 printf ("Roll: %d\n",((int)(AHRSData_Packet.Roll*rad_ro_degree)));
			 				r=(int)(AHRSData_Packet.Roll*rad_ro_degree);
				printf ("Roll: %d\n",r);
	 }
		 
	if(AHRSData_Packet.Pitch<0)	
	{		
		OLED_ShowString(50,25,"-"),
   OLED_ShowNumber(55,25,-((int)(AHRSData_Packet.Pitch*rad_ro_degree)),5,12);
		printf ("Pitch: %d\n",-((int)(AHRSData_Packet.Pitch*rad_ro_degree)));
						p=-((int)(AHRSData_Packet.Pitch*rad_ro_degree));
				printf ("Roll: %d\n",p);
	}
	 else                 	  
	 {OLED_ShowString(50,25,"+"),
		OLED_ShowNumber(55,25,((int)(AHRSData_Packet.Pitch*rad_ro_degree)),5,12);
		 printf ("Pitch: %d\n",((int)(AHRSData_Packet.Pitch*rad_ro_degree)));
		 						p=(int)(AHRSData_Packet.Pitch*rad_ro_degree);
				printf ("Roll: %d\n",p);
	 }
	if(AHRSData_Packet.Heading<0)	 
	{		OLED_ShowString(30,40,"-"),
		OLED_ShowNumber(55,40,-((int)(AHRSData_Packet.Heading*rad_ro_degree)),5,12);
		printf ("Yaw: %d\n",-((int)(AHRSData_Packet.Heading*rad_ro_degree)));
								y=-((int)(AHRSData_Packet.Heading*rad_ro_degree));
				printf ("Roll: %d\n",y);
	}
	 else                 	 
	 {	OLED_ShowString(50,40,"+"),
			OLED_ShowNumber(55,40, ((int)(AHRSData_Packet.Heading*rad_ro_degree)),5,12);
		 printf ("Yaw: %d\n",((int)(AHRSData_Packet.Heading*rad_ro_degree)));
		 								y=(int)(AHRSData_Packet.Heading*rad_ro_degree);
				printf ("Roll: %d\n",y);
	 }

		OLED_Refresh_Gram();	
}
