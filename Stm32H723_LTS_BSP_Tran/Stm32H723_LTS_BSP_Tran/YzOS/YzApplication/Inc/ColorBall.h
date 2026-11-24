//
// Created by 32827 on 2025/10/5.
//

#ifndef STM32H723_LTS_BSP_TRAN_COLORBALL_H
#define STM32H723_LTS_BSP_TRAN_COLORBALL_H

#include "yzl_i2c_tcs34727.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    uint8_t r,g,b;
} BallColor;

typedef struct {
    BallColor color;
    char colorTag;
    YZF_BOOL isInside;
    YZF_BOOL isOut;
} BallInfo;

typedef struct {
    BallInfo balls[10];
    int leftDoorIndex;
    int rightDoorIndex;
} BallList;

void InitBallList(BallList *list);
void MoveBallList(BallList *list,int i);

extern BallColor colors[10];
extern char ColorResult[10];
extern int nowIndex;
extern BallList ballList;
void classifyBalls(BallColor balls[10], char result[10]);

void getBallColor();
YZF_RESULT checkColorSensor();
YZF_RESULT checkBallAllIn();
#ifdef __cplusplus
}
#endif
#endif //STM32H723_LTS_BSP_TRAN_COLORBALL_H
