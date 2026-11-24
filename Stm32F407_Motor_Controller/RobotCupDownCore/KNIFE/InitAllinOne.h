#ifndef __INITALLINONE_H__
#define __INITALLINONE_H__

#include "stm32f4xx.h"
#include "yz_time_area.h"

void NowClockSet(void);

void RecvTimeInit(void);

void RecvTimeUpdate(void);

double Request_YAW(); //获取当前航向角

#endif /* __INITALLINONE_H__ */