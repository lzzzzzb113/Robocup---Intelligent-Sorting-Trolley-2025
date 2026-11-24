//
// Created by 32827 on 2023/11/15.
//

#ifndef YZF_H
#define YZF_H
#include <stdio.h>
#include "inttypes.h"
#include "yzf_basic_ram.h"

#define YZF_ON 1
#define YZF_OFF 0
#define YZF_NULL 255U
#define YZF_NULL_PTR 0

#define YZF_USE_WITH_HAL YZF_ON

#define ARM_MATH_CM7

#include "stm32h7xx.h"
#if YZF_USE_WITH_HAL //用于兼容F103之外的
#include "stm32h7xx_hal.h"
#define YZF_PIN_CONV(x) ((uint16_t)0x0001 << x)
#endif

enum YZF_BOOL{
    YZF_FALSE = 0,
    YZF_TRUE = 1
};

enum YZF_STATUS{
    YZF_OK=0,
    YZF_ERROR,          ///未知错误
    YZF_NOT_INIT,       ///成员变量未初始化
    YZF_NOT_FOUND,      ///所选参数/配置未找到
    YZF_CRC_ERROR,      ///CRC校验错误
    YZF_CLOCK_NOT_READY, ///时钟未就绪
    YZF_HANDLER_NOT_FINISH,  ///处理函数未结束
    YZF_NOTHING          ///空闲
};

typedef enum{
    FLAG_OFF,
    FLAG_ON
} YZF_FLAG;

typedef enum YZF_STATUS YZF_RESULT;
typedef enum YZF_BOOL YZF_BOOL;

void YZF_ERROR_HANDLE(YZF_RESULT error);



#define YZF_CHECK YZF_ON

#if YZF_CHECK
#define YZF_CHECK_PARAM(n) if((int)n==YZF_NULL){return YZF_NOT_INIT;};
#define YZF_CHECK_RETURN(n) if(n!=YZF_OK){YZF_ERROR_HANDLE(n);};
#else
#define YZF_CHECK_PARAM(n) ;
#define YZF_CHECK_RETURN(n) n
#endif

#define YZF_FLAG_BIT_C(Reg,mask,isClear) ((Reg & mask) != 0 ? (isClear?(Reg&= ~mask) : 0,YZF_TRUE) :YZF_FALSE)
#define YZF_FLAG_BIT(Reg,mask) ((Reg & mask) != 0 ? YZF_TRUE :YZF_FALSE)
#define YZF_ENABLE(Reg,mask) (Reg |= mask)
#define YZF_DISABLE(Reg,mask) (Reg &= ~mask)
#define YZF_MODIFY_REG(Reg,mask,value,offset) (Reg = (Reg & ~ (mask)) | ((value) << offset & (mask)))

///------------------- GPIO -----------------------
enum YZF_PIN{
    YZF_PIN_0 = 0U,
    YZF_PIN_1 = 1U,
    YZF_PIN_2 = 2U,
    YZF_PIN_3 = 3U,
    YZF_PIN_4 = 4U,
    YZF_PIN_5 = 5U,
    YZF_PIN_6 = 6U,
    YZF_PIN_7 = 7U,
    YZF_PIN_8 = 8U,
    YZF_PIN_9 = 9U,
    YZF_PIN_10 = 10U,
    YZF_PIN_11 = 11U,
    YZF_PIN_12 = 12U,
    YZF_PIN_13 = 13U,
    YZF_PIN_14 = 14U,
    YZF_PIN_15 = 15U,
    YZF_PIN_UNKnow = 16U
};
typedef GPIO_TypeDef* YZF_GPIO_POINTER;
typedef USART_TypeDef* YZF_UART_POINTER;
typedef I2C_TypeDef* YZF_I2C_POINTER;
typedef SPI_TypeDef* YZF_SPI_POINTER;
typedef SPI_HandleTypeDef *YZF_HAL_SPI_POINTER;
typedef TIM_TypeDef* YZF_TIM_POINTER;
typedef ADC_TypeDef* YZF_ADC_POINTER;
typedef DAC_TypeDef* YZF_DAC_POINTER;
//    typedef DMA_Channel_TypeDef * YZF_DMA_CHANNEL_POINTER;
typedef DMA_TypeDef* YZF_DMA_POINTER;
typedef DMA_Stream_TypeDef * YZF_DMA_CHANNEL_POINTER;//suit to STM32F407
typedef DMAMUX_ChannelStatus_TypeDef * YZF_DMAMUX_STATUS_POINTER;//suit to STM32H723
typedef DMAMUX_Channel_TypeDef * YZF_DMAMUX_CHANNEL_POINTER;//suit to STM32H723
typedef enum YZF_PIN YZF_GPIO_PIN;//suit to STM32H723
///------------------------------------------------
#endif //YZFRAME_YZF_H
