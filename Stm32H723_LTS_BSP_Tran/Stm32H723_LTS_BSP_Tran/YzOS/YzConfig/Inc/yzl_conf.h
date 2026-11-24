//
// Created by 32827 on 2024/1/26.
//

#ifndef YZL_CONF_H
#define YZL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "yz.h"

#ifdef __cplusplus
}
#endif

#if YZ_USE_WITH_HAL
#define YZL_USE_WITH_HAL ON
#define YZL_USE_GPIO_WITH_HAL (OFF&YZL_USE_WITH_HAL)
#define YZL_USE_SPI_WITH_HAL (OFF&YZL_USE_WITH_HAL)
#endif


/**
 * 管理导入
 * */
#define USE_CLOCK OFF
#define USE_Driver OFF
#define USE_FATFS ON
#define USE_FONT ON
#define USE_MEM_MANAGER ON
#define USE_PERIPHERAL OFF
#define USE_SOFT_PORT ON
#define USE_UI_PORT ON
#define USE_LVGL ON

///YzClock Config
#define YZL_TIMER TIMER1
#define YZL_CLOCK_IRQ TIM2_IRQHandler
///YzSoftPort Config
#define YZL_SOFT_PORT_SPI ON
#define YZL_SOFT_PORT_IIC ON
#define YZL_SOFT_PORT_SCCB OFF
///YzDriver Config
#define ICM42688_SPI_SOFT (OFF&YZL_SOFT_PORT_SPI)

///YzMath Config
#define YZL_MATH_USE_HAL (ON&YZL_USE_WITH_HAL)

///YzLvgl Config

///YzUI Config
#if USE_UI_PORT
#define YZSCREEN ON
#define YZ_SCREEN_DRIVER YZ_SCREEN_DRIVER_ST7735S
//屏幕接口
#define YZ_SCREEN_DRIVER_PORT ui_screen_handler //屏幕驱动接口名称
#define YZ_SCREEN_TOUCH_DRIVER YZ_SCREEN_TOUCH_DRIVER_NONE
#define YZ_SCREEN_MAX_TOUCH 5
#define YZ_SCREEN_HEIGHT 128
#define YZ_SCREEN_WIDTH 128

#define YZL_UI_WIDGET_DATA_SRAM_SIZE (8*4)     //void *的大小
#define YZL_UI_VIEW_DEEP_MAX 10
#define YZL_UI_VIEW_WIDGET_MAX_COUNT 10

//UI Running config
#define YZL_UI_VIEW_POSITION_DEBUG YZF_OFF
#define YZL_UI_TOUCH_DATA_DEBUG YZF_OFF
#define YZL_UI_VIEW_POSITION_DEBUG_COLOR WHITE
#endif

#endif //YZL_CONF_H
