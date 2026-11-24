//
// Created by 32827 on 2025/10/5.
//

#include "ColorBall.h"
#include "yzl_iconv.h"
#include "ff.h"
#include "yz_tim.h"
#include "yzl_font.h"
#include "yzl_softport.h"

/**
 * 传入十个球的颜色，返回对应球颜色的字符'r','y'
 *
 * */
void classifyBalls(BallColor balls[10], char result[10]) {
    // 定义标准颜色
    typedef struct {
        uint8_t r, g, b;
        char code;
    } StdColor;
    StdColor stds[5] = {
            {255, 255, 255, 'w'},  // 白色
            {255, 0, 0, 'r'},      // 红色
            {255, 255, 0, 'y'},    // 黄色
            {0, 255, 0, 'g'},      // 绿色
            {0, 0, 255, 'b'}       // 蓝色
    };

    // 存储每个球到每个标准颜色的距离平方
    int ball_distances[10][5];
    // 存储每个球的排序颜色索引（按距离从小到大）
    int ball_sorted_indices[10][5];

    // 计算每个球与标准颜色的距离平方，并排序颜色索引
    for (int i = 0; i < 10; i++) {
        // 计算距离平方
        for (int j = 0; j < 5; j++) {
            int dr = balls[i].r - stds[j].r;
            int dg = balls[i].g - stds[j].g;
            int db = balls[i].b - stds[j].b;
            ball_distances[i][j] = dr * dr + dg * dg + db * db;
        }
        // 初始化颜色索引
        int indices[5] = {0, 1, 2, 3, 4};
        // 使用冒泡排序对索引基于距离平方进行排序
        for (int a = 0; a < 4; a++) {
            for (int b = 0; b < 4 - a; b++) {
                if (ball_distances[i][indices[b]] > ball_distances[i][indices[b + 1]]) {
                    int temp = indices[b];
                    indices[b] = indices[b + 1];
                    indices[b + 1] = temp;
                }
            }
        }
        // 存储排序后的索引
        for (int j = 0; j < 5; j++) {
            ball_sorted_indices[i][j] = indices[j];
        }
    }

    // 初始化分配：每个球分配到最近的标准颜色
    int assignment[10];
    int count[5] = {0};
    for (int i = 0; i < 10; i++) {
        assignment[i] = ball_sorted_indices[i][0];
        count[assignment[i]]++;
    }

    // 调整分配：确保每种颜色恰好有两个球
    int needs_adjustment = 1;
    while (needs_adjustment) {
        needs_adjustment = 0;
        for (int j = 0; j < 5; j++) {
            if (count[j] > 2) {
                needs_adjustment = 1;
                // 找到颜色j中距离最远的球
                int farthest_ball = -1;
                int max_dist = -1;
                for (int i = 0; i < 10; i++) {
                    if (assignment[i] == j) {
                        if (ball_distances[i][j] > max_dist) {
                            max_dist = ball_distances[i][j];
                            farthest_ball = i;
                        }
                    }
                }
                // 为该球找到下一个有空位（计数小于2）的颜色
                int new_color = -1;
                for (int k = 1; k < 5; k++) {
                    int candidate = ball_sorted_indices[farthest_ball][k];
                    if (count[candidate] < 2) {
                        new_color = candidate;
                        break;
                    }
                }
                // 如果未找到（理论上不会发生），则强制找到第一个计数小于2的颜色
                if (new_color == -1) {
                    for (int jj = 0; jj < 5; jj++) {
                        if (count[jj] < 2) {
                            new_color = jj;
                            break;
                        }
                    }
                }
                // 重新分配球
                count[j]--;
                assignment[farthest_ball] = new_color;
                count[new_color]++;
                break; // 调整后重新检查计数
            }
        }
    }

    // 将分配结果转换为字符代码
    for (int i = 0; i < 10; i++) {
        result[i] = stds[assignment[i]].code;
    }
}

BallColor colors[10];
BallList ballList;
void InitBallList(BallList *list){
    list->leftDoorIndex = 0;
    list->rightDoorIndex = 5;
    for(int i=0;i<10;i++){
        ballList.balls[i].color = (BallColor){0,0,0};
        ballList.balls[i].isInside = YZF_FALSE;
        ballList.balls[i].isOut = YZF_FALSE;
    }
}
void MoveBallList(BallList *list,int i){
    if(i>0){
        yzf_gpio_set_1(GPIOD,YZF_PIN_11);
        yz_tim_pwm_data_set(TIM4,4,1000*1000/1000/2-1,1000*1000/1000-1);
        yz_tim_pwm_with_count_fast(TIM4,4,TIM8,(uint32_t)320*i);
        while(yz_tim_pwm_with_count_is_finish(TIM8)==YZF_FALSE){}
        list->leftDoorIndex= ((list->leftDoorIndex-i)+10)%10;
        list->rightDoorIndex= ((list->rightDoorIndex-i)+10)%10;
    }else if(i<0){
        yzf_gpio_set_0(GPIOD,YZF_PIN_11);
        yz_tim_pwm_data_set(TIM4,4,1000*1000/1000/2-1,1000*1000/1000-1);
        yz_tim_pwm_with_count_fast(TIM4,4,TIM8,(uint32_t)320*(-i));
        while(yz_tim_pwm_with_count_is_finish(TIM8)==YZF_FALSE){}
        list->leftDoorIndex= ((list->leftDoorIndex-i)+10)%10;
        list->rightDoorIndex= ((list->rightDoorIndex-i)+10)%10;
    }
}

YZF_BOOL ColorSensorBus1Check[3]={YZF_FALSE,YZF_FALSE,YZF_TRUE};
uint8_t ColorSensorBus1Address[3]={0x48|0x7,0x48|0x6,0x48|0x5};
YZF_BOOL ColorSensorBus2Check[3]={YZF_FALSE,YZF_FALSE};
uint8_t ColorSensorBus2Address[3]={0x48|0x4,0x48|0x3};

int BallIndexMap(BallList *list,uint8_t colorSensorAddress){
    if(colorSensorAddress==(0x48|0x7)){
        return ((list->leftDoorIndex-1)+10)%10;
    }else if(colorSensorAddress==(0x48|0x6)){
        return ((list->leftDoorIndex-2)+10)%10;
    }else if(colorSensorAddress==(0x48|0x5)){
        return ((list->leftDoorIndex-3)+10)%10;
    }else if(colorSensorAddress==(0x48|0x4)){
        return ((list->leftDoorIndex+3)+10)%10;
    }else if(colorSensorAddress==(0x48|0x3)){
        return ((list->leftDoorIndex+2)+10)%10;
    }else{
        return -1;
    }
}

YZF_BOOL ColorBallInSide(uint8_t rgb[3]){
    int rgbDist= rgb[0]*rgb[0]+rgb[1]*rgb[1]+rgb[2]*rgb[2];
    if(rgbDist>128*128){
        return YZF_TRUE;
    }else{
        return YZF_FALSE;
    }
}

YZF_RESULT checkBallAllIn(){
    for(int i=0;i<3;i++){
        uint8_t rgb[3];
        //address 0x48 | 0bXXX , 跳线帽接上表示 1
        uint8_t cmd = 0xD0;
        yz_i2c_add7_transmit(I2C4,ColorSensorBus1Address[i],&cmd,1);
        yz_i2c_add7_receive(I2C4,ColorSensorBus1Address[i],rgb,3);

        int index=BallIndexMap(&ballList,ColorSensorBus1Address[i]);
        YZF_BOOL inside=ColorBallInSide(rgb);
        if(inside==YZF_TRUE&&ballList.balls[index].isInside==YZF_FALSE){
            ballList.balls[index].color = (BallColor){rgb[0],rgb[1],rgb[2]};
            ballList.balls[index].isInside = inside;
        }
    }

    for(int i=0;i<2;i++){
        uint8_t rgb[3];
        //address 0x48 | 0bXXX , 跳线帽接上表示 1
        uint8_t cmd = 0xD0;
        yz_i2c_add7_transmit(I2C2,ColorSensorBus2Address[i],&cmd,1);
        yz_i2c_add7_receive(I2C2,ColorSensorBus2Address[i],rgb,3);
        int index=BallIndexMap(&ballList,ColorSensorBus2Address[i]);
        YZF_BOOL inside=ColorBallInSide(rgb);

        if(inside==YZF_TRUE&&ballList.balls[index].isInside==YZF_FALSE){
            ballList.balls[index].color = (BallColor){rgb[0],rgb[1],rgb[2]};
            ballList.balls[index].isInside = inside;
        }
    }

    int count = 0;
    for(int i=0;i<10;i++){
        if(ballList.balls[i].isInside==YZF_FALSE){
            count++;
        }
    }
    if(count==0){
        getBallColor();
        for (int i = 0; i < 10; i++) {
            colors[i]=ballList.balls[i].color;
        }
        classifyBalls(colors,ColorResult);
        for (int i = 0; i < 10; i++) {
            ballList.balls[i].colorTag=ColorResult[i];
        }
        return YZF_OK;
    }else if(count<10){
        return YZF_NOT_INIT;
    }else{
        return YZF_ERROR;
    }
}

char ColorResult[10];
int nowIndex=0;
FIL SDFile_RGBCSV;
char CharCSVBuf[128];

YZF_RESULT checkColorSensor(){
    //BUS I2C4 ColorSensor Check
    uint8_t status;
    while(1){
        for(int i=0;i<2;i++){
            yz_i2c_add7_cmd_receive(I2C2,ColorSensorBus2Address[i],0xAA,&status,1);
            HAL_Delay(1);
            if(status==0x66){
                ColorSensorBus2Check[i]=YZF_TRUE;
            }
        }
        for(int i=0;i<3;i++){
            yz_i2c_add7_cmd_receive(I2C4,ColorSensorBus1Address[i],0xAA,&status,1);
            HAL_Delay(1);
            if(status==0x66){
                ColorSensorBus1Check[i]=YZF_TRUE;
            }
        }
        if(ColorSensorBus1Check[0]&&ColorSensorBus1Check[1]&&ColorSensorBus1Check[2]&&ColorSensorBus2Check[0]&&ColorSensorBus2Check[1]){
            break;
        }
    }
    return YZF_ERROR;
}

void getBallColor(){
    delay_ms(1000);
    nowIndex=0;
    for(int i=0;i<3;i++){
        uint8_t rgb[3];
        //address 0x48 | 0bXXX , 跳线帽接上表示 1
        uint8_t cmd = 0xD0;
        yz_i2c_add7_transmit(I2C4,ColorSensorBus1Address[i],&cmd,1);
        yz_i2c_add7_receive(I2C4,ColorSensorBus1Address[i],rgb,3);
        int index=BallIndexMap(&ballList,ColorSensorBus1Address[i]);
        ballList.balls[index].color = (BallColor){rgb[0],rgb[1],rgb[2]};
    }
    for(int i=0;i<2;i++){
        uint8_t rgb[3];
        //address 0x48 | 0bXXX , 跳线帽接上表示 1
        uint8_t cmd = 0xD0;
        yz_i2c_add7_transmit(I2C2,ColorSensorBus2Address[i],&cmd,1);
        yz_i2c_add7_receive(I2C2,ColorSensorBus2Address[i],rgb,3);
        int index=BallIndexMap(&ballList,ColorSensorBus2Address[i]);
        ballList.balls[index].color = (BallColor){rgb[0],rgb[1],rgb[2]};
    }
    MoveBallList(&ballList,2);
    delay_ms(500);
    for(int i=0;i<2;i++){
        uint8_t rgb[3];
        //address 0x48 | 0bXXX , 跳线帽接上表示 1
        uint8_t cmd = 0xD0;
        yz_i2c_add7_transmit(I2C2,ColorSensorBus2Address[i],&cmd,1);
        yz_i2c_add7_receive(I2C2,ColorSensorBus2Address[i],rgb,3);
        int index=BallIndexMap(&ballList,ColorSensorBus2Address[i]);
        ballList.balls[index].color = (BallColor){rgb[0],rgb[1],rgb[2]};
    }
    MoveBallList(&ballList,1);
    delay_ms(300);
    for(int i=0;i<3;i++){
        uint8_t rgb[3];
        //address 0x48 | 0bXXX , 跳线帽接上表示 1
        uint8_t cmd = 0xD0;
        yz_i2c_add7_transmit(I2C4,ColorSensorBus1Address[i],&cmd,1);
        yz_i2c_add7_receive(I2C4,ColorSensorBus1Address[i],rgb,3);
        int index=BallIndexMap(&ballList,ColorSensorBus1Address[i]);
        ballList.balls[index].color = (BallColor){rgb[0],rgb[1],rgb[2]};
    }

    FRESULT retSD = f_open(&SDFile_RGBCSV,yzl_str_format("%s%s/RGB_Ball.csv",YZL_FONT_FF_DRIVER,"data"),FA_WRITE | FA_OPEN_ALWAYS);
    if(retSD!=FR_OK){
        yz_info("RGB_Ball.csv open failed.Code: %d\n",retSD);
        return;
    }
    int byteWriten=0;
    sprintf(CharCSVBuf,"r,g,b,tag\n");
    f_write(&SDFile_RGBCSV, CharCSVBuf, strlen(CharCSVBuf),(UINT *)(&byteWriten));
    BallInfo info;
    for(int i=0;i<10;i++){
        info=ballList.balls[i];
        byteWriten=0;
        sprintf(CharCSVBuf,"%d,%d,%d,%c\n",info.color.r,info.color.g,info.color.b,info.colorTag);
        f_write(&SDFile_RGBCSV, CharCSVBuf, strlen(CharCSVBuf), (UINT *)(&byteWriten));
    }
    f_close(&SDFile_RGBCSV);
}