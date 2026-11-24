//
// Created by 32827 on 2024/1/11.
//

#ifndef YZDEF_H
#define YZDEF_H
#include "yzf.h"


#define YZ_COLOR_MODE_RGB565 0
#define YZ_COLOR_MODE_RGB888 1
#define YZ_COLOR_MODE_RGBA8888 2
#define YZ_COLOR_MODE_BlackAndWhite 3


//驱动另外适配

#define YZ_SCREEN_DRIVER_NONE 0
#define YZ_SCREEN_DRIVER_ILI9341 1
#define YZ_SCREEN_DRIVER_I2C_1306 2
#define YZ_SCREEN_DRIVER_TLI4384 3
#define YZ_SCREEN_DRIVER_ST7735S 4

#define YZ_SCREEN_TOUCH_DRIVER_NONE 0
#define YZ_SCREEN_TOUCH_DRIVER_XPT2046 1
#define YZ_SCREEN_TOUCH_DRIVER_GT911 2

#define ON 1
#define OFF 0
#define NULL_PTR 0

#define YZ_CHECK_SIZE_OVER(dataType, nBytes) \
							typedef char SC_EQ_##dataType[(sizeof(dataType) <= (nBytes)) ? 1 : -1]  //检查数据大小

typedef struct {
    uint32_t baseAddress;
    uint32_t size;
    void* (*pMalloc)(size_t size);
    void (*pFree)(void* ptr);
} YZ_MemManger;
#endif //YZDEF_H
