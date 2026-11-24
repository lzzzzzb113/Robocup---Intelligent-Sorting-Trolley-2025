//
// Created by 32827 on 2025/3/22.
//
#include "user_cxx.h"
#include "yz_tim.h"
#include "yz_heart.h"
#include "yz_time_area.h"
#include "yzl_transform_segment.h"

#include "ui_main.hpp"

#include "yz_uart.h"
#include "yzl_i2c_bno085.h"
#include "ColorBall.h"

///--------------------- ALL DEFINE ---------------------
YZL_UI_ROOT *uiRoot;
ViewMain *mainMenu;
char *bgImg=(char *)"/MMC/test.565";

int32_t SystemTickCNT=0;
YZF_RESULT SystemTickCount(uint32_t tick){
    SystemTickCNT += tick;
    return YZF_HANDLER_NOT_FINISH;
}

/**************芯片设置命令*********************/
uint8_t SYN_StopCom[] = {0xFD, 0X00, 0X02, 0X02, 0XFD}; //停止合成
uint8_t SYN_SuspendCom[] = {0XFD, 0X00, 0X02, 0X03, 0XFC}; //暂停合成
uint8_t SYN_RecoverCom[] = {0XFD, 0X00, 0X02, 0X04, 0XFB}; //恢复合成
uint8_t SYN_ChackCom[] = {0XFD, 0X00, 0X02, 0X21, 0XDE}; //状态查询
uint8_t SYN_PowerDownCom[] = {0XFD, 0X00, 0X02, 0X88, 0X77}; //进入POWER DOWN 状态命令

//Music:选择背景音乐。0:无背景音乐，1~15：选择背景音乐
void SYN_FrameInfo(uint8_t Music, uint8_t *HZdata)
{
    /****************需要发送的文本**********************************/
    unsigned  char  Frame_Info[50];
    unsigned  char  HZ_Length;
    unsigned  char  ecc  = 0;  			//定义校验字节
    unsigned  int i = 0;
    HZ_Length = strlen((char*)HZdata); 			//需要发送文本的长度

    /*****************帧固定配置信息**************************************/
    Frame_Info[0] = 0xFD ; 			//构造帧头FD
    Frame_Info[1] = 0x00 ; 			//构造数据区长度的高字节
    Frame_Info[2] = HZ_Length + 3; 		//构造数据区长度的低字节
    Frame_Info[3] = 0x01 ; 			//构造命令字：合成播放命令
    Frame_Info[4] = 0x00 | Music << 4 ; //构造命令参数：背景音乐设定

    /*******************校验码计算***************************************/
    for(i = 0; i < 5; i++)   				//依次发送构造好的5个帧头字节
    {
        ecc = ecc ^ (Frame_Info[i]);		//对发送的字节进行异或校验
    }

    for(i = 0; i < HZ_Length; i++)   		//依次发送待合成的文本数据
    {
        ecc = ecc ^ (HZdata[i]); 				//对发送的字节进行异或校验
    }
    /*******************发送帧信息***************************************/
    memcpy(&Frame_Info[5], HZdata, HZ_Length);
    Frame_Info[5 + HZ_Length] = ecc;
    yz_uart_transmit(UART8,Frame_Info, 5 + HZ_Length + 1);
}
///--------------------- ALL DEFINE ---------------------

YZF_RESULT yzl_program_logic_loop();
YZF_RESULT yzl_ui_main_view_boot(){

    //从全局表中取UI_ROOT的地址
    uiRoot=(YZL_UI_ROOT *) yzf_global_data_get(yz_status_sheet_get(YZ_SHEET_POINTER_FOR_UI_ROOT));

    //在UI_ROOT中创建首层View,ViewMenu以显示
    uiRoot->ViewTop++;
    mainMenu=new ViewMain(&YZL_TopView((*uiRoot)),bgImg);

    //在全局表中配置首层View地址
    YZF_GLOBAL_INDEX index=yzf_global_data_add(&YZL_TopView((*uiRoot)));
    yz_status_sheet_set(YZ_SHEET_POINTER_FOR_UI_VIEW,index);

    //在全局表中配置初始化数据指针
    YZF_GLOBAL_INDEX index2=yzf_global_data_add(YZF_NULL_PTR);
    yz_status_sheet_set(YZ_SHEET_POINTER_FOR_UI_VIEW_INIT_DATA,index2);

    yz_heart_process_add(SystemTickCount);

    return YZF_OK;
}

#define COLOR_SENSOR_ENABLE 1
extern "C" void LinkLeft();
extern "C" void LinkRight();

extern "C" YZF_RESULT yzl_ui_init_done(){
#if COLOR_SENSOR_ENABLE
    checkColorSensor();
    InitBallList(&ballList);
#endif
//    LinkLeft();
//    LinkRight();
    SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]自检通过");
    mainMenu->mText6->setTextF((utf8 *) "PASS");
    yzf_global_handler_add(yzl_program_logic_loop);
    return YZF_OK;
}

int32_t loopLastRunning=0;
int32_t loopLastBno085=0;
int ProgramStart = 0;
Quaternion quaternion;
float yaw,pitch,roll;
uint8_t imu_uart_data[]={0x55,0x53,0,0,0,0,1,1};
extern "C" void putBall();
int coo=0;
int cooRes=0;
int cooOrange=0;
YZF_RESULT yzl_program_logic_loop(){
    yz_area_recv_time_update((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART7), SystemTickCNT);
    yz_area_recv_time_update((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART5), SystemTickCNT);
    yz_area_recv_time_update((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(USART1), SystemTickCNT);
    if(SystemTickCNT-loopLastBno085>50){
        loopLastBno085=SystemTickCNT;
        if(yzl_i2c_bno085_data_available(I2C1) == YZF_OK){
            quaternion.x=yzl_i2c_bno085_get_quat_i();
            quaternion.y=yzl_i2c_bno085_get_quat_j();
            quaternion.z=yzl_i2c_bno085_get_quat_k();
            quaternion.w=yzl_i2c_bno085_get_quat_real();
            yzl_i2c_bno085_quat_2_euler(&quaternion, &yaw, &pitch, &roll);
            int kvlaue = (int)((float)(yaw/M_PI)*32768.0);
            imu_uart_data[6]=((uint16_t)kvlaue)&0xFF;
            imu_uart_data[7]=((uint16_t)kvlaue)>>8;
            yz_uart_transmit(UART4, (uint8_t*)imu_uart_data, 8);
//            yz_info("ax: %.3f,ay: %.3f,az: %.3f,gx: %.3f,gy: %.3f,gz: %.3f,yaw: %.3f,pitch: %.3f,roll: %.3f\n",ax,ay,az,gx,gy,gz,yaw,pitch,roll);
//            yz_printf("%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",ax,ay,az,gx*180/M_PI,gy*180/M_PI,gz*180/M_PI,yaw*180/M_PI,pitch*180/M_PI,roll*180/M_PI);
//            mainMenu->mText6->setTextF((utf8 *) "%.3f", yaw * 180 / M_PI);
//            yz_printf("%.3f,%.3f,%.3f\n",yaw*180/M_PI,pitch*180/M_PI,roll*180/M_PI);
            mainMenu->mText4->setTextF((utf8 *) "%.3f",yaw*180/M_PI);
        }
        mainMenu->mText3->setTextF((utf8 *) "%x",USART1->ISR);
        mainMenu->mText6->setTextF((utf8 *) "%x",USART1->CR1);
    }
    if(cooRes){
        mainMenu->mText5->setTextF((utf8 *) "OK");
        yz_uart_transmit(USART1, (uint8_t*)"OK", 2);
        HAL_Delay(100);
        yz_uart_transmit(USART1, (uint8_t*)"OK", 2);
        cooRes=0;
        return YZF_HANDLER_NOT_FINISH;
    }
    if(cooOrange){
        HAL_Delay(100);
        yz_uart_transmit(USART1, (uint8_t*)"CR1", 3);
        SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]无效邮件");
        HAL_Delay(100);
        yz_uart_transmit(USART1, (uint8_t*)"START", 5);
        cooOrange=0;
    }
    if(coo){
        HAL_Delay(100);
        yz_uart_transmit(USART1, (uint8_t*)"CR1", 3);
        putBall();
        coo=0;
    }
#if COLOR_SENSOR_ENABLE
    if((SystemTickCNT-loopLastRunning)>100&&ProgramStart==0){
        loopLastRunning=SystemTickCNT;
        YZF_RESULT result=checkBallAllIn();
        if(result==YZF_OK){
            ProgramStart = 1;
            mainMenu->mText3->setTextF((utf8 *) "%s", ColorResult);
            yz_uart_transmit(USART1, (uint8_t*)"START", 5);
        }else if(result==YZF_NOT_INIT){
            delay_ms(100);
            MoveBallList(&ballList,1);
            delay_ms(200);
        }
    }
#endif
    return YZF_HANDLER_NOT_FINISH;
}
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin==GPIO_PIN_4){
        mainMenu->ButtonUp();
    }else if(GPIO_Pin==GPIO_PIN_3){
        if(yzf_gpio_get(GPIOE,YZF_PIN_4)){
            mainMenu->ButtonEsc();
            return;
        }
        mainMenu->ButtonDown();
    }else if(GPIO_Pin==GPIO_PIN_2){
        mainMenu->ButtonEnter();
    }else if(GPIO_Pin==GPIO_PIN_8){
    }
}
extern "C"{
    char text_now;
    void LinkLeft(){
        yz_tim_pwm_start_and_data_set(TIM2,4,274,499+2000,19999);
        delay_ms(300);
    }
    void LinkRight(){
        yz_tim_pwm_start_and_data_set(TIM2,3,274,499+2000,19999);
        delay_ms(300);
    }
    void disLinkLeft(){
        yz_tim_pwm_start_and_data_set(TIM2,4,274,499,19999);
        delay_ms(300);
    }
    void disLinkRight(){
        yz_tim_pwm_start_and_data_set(TIM2,3,274,499,19999);
        delay_ms(300);
    }
    void OpenLeft(){
        yz_tim_pwm_start_and_data_set(TIM3,1,274,999,19999);
        delay_ms(300);
        yz_tim_pwm_start_and_data_set(TIM3,1,274,999+600,19999);
        delay_ms(300);
    }
    void OpenRight(){
        yz_tim_pwm_start_and_data_set(TIM3,2,274,999+600,19999);
        delay_ms(300);
        yz_tim_pwm_start_and_data_set(TIM3,2,274,999-70,19999);//-70
        delay_ms(300);
    }
    int inTestPrint=1;
    int LeftOrRight=0;//0表示左,1表示右
    void usart1_time(char *text){
        if(strncmp("start",text,5)==0){//1左,2右
            if(text[5]=='1'){
                LeftOrRight=0;
            }else if(text[5]=='2'){
                LeftOrRight=1;
            }
            inTestPrint=0;
            cooRes=1;
            yz_area_recv_time_unlock((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART7));
            yz_area_recv_time_unlock((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART5));
        }
    }

    void testPrint(char *text){
        if(inTestPrint==1||text[0]=='o'){
            if(text[0]=='o'&&inTestPrint == 0){
                inTestPrint = 1;
                cooOrange = 1;
                yz_area_recv_time_lock((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART7));
                yz_area_recv_time_lock((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART5));
            }
            return;
        }
        if(text[0]=='r'||text[0]=='b'||text[0]=='w'||text[0]=='y'||text[0]=='g'){
            inTestPrint = 1;
            text_now=text[0];
            coo=1;
            yz_area_recv_time_lock((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART7));
            yz_area_recv_time_lock((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART5));
        }
    }
    void putBall(){
        if(LeftOrRight==0){
            SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]右");
        }else{
            SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]左");
        }
        int i1=-10,i2=-10;
        if(LeftOrRight==0){
            LinkRight();
            for(int i =0;i<6;i++){
                if(ballList.balls[(ballList.leftDoorIndex+i+10)%10].colorTag==text_now){
                    if(i1==-10){
                        i1=-i;
                    }else if(i2==-10){
                        i2=-i;
                    }
                }
            }
            for(int i =0;i<6;i++){
                if(ballList.balls[(ballList.leftDoorIndex-i+10)%10].colorTag==text_now){
                    if(i1==-10){
                        i1=i;
                    }else if(i2==-10){
                        i2=i;
                    }
                }
            }
            if(abs(i1)>abs(i2)){
                int i=i1;
                i1=i2;
                i2=i;
            }
            MoveBallList(&ballList,i1);
            OpenRight();
            MoveBallList(&ballList,i2-i1);
            OpenRight();
            disLinkRight();
            yz_uart_transmit(USART1, (uint8_t*)"START", 5);
        }else if(LeftOrRight==1){
            LinkLeft();
            for(int i =0;i<6;i++){
                if(ballList.balls[(ballList.rightDoorIndex+i+10)%10].colorTag==text_now){
                    if(i1==-10){
                        i1=-i;
                    }else if(i2==-10){
                        i2=-i;
                    }
                }
            }
            for(int i =0;i<6;i++){
                if(ballList.balls[(ballList.rightDoorIndex-i+10)%10].colorTag==text_now) {
                    if (i1 == -10) {
                        i1 = i;
                    } else if (i2 == -10) {
                        i2 = i;
                    }
                }
            }
            if(abs(i1)>abs(i2)){
                int i=i1;
                i1=i2;
                i2=i;
            }
            mainMenu->mText5->setTextF((utf8 *) "%d,%d", i1, i2);
            MoveBallList(&ballList,i1);
            OpenLeft();
            MoveBallList(&ballList,i2-i1);
            OpenLeft();
            disLinkLeft();
            yz_uart_transmit(USART1, (uint8_t*)"START", 5);
        }
        switch (text_now) {
            case 'w':
                SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]白色邮件投递成功");
                break;
            case 'b':
                SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]蓝色件投递成功");
                break;
            case 'y':
                SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]黄色件投递成功");
                break;
            case 'r':
                SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]红色件投递成功");
                break;
            case 'g':
                SYN_FrameInfo(0,(uint8_t *)"[v16][m1][t5][o0]绿色件投递成功");
                break;
            default:
                break;
        }
        coo=0;
    }
}
