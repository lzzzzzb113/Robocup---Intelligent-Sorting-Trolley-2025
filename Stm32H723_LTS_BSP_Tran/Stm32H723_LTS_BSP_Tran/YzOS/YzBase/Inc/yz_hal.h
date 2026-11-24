//
// Created by 32827 on 2023/12/10.
//

#ifndef YZ_HAL_H
#define YZ_HAL_H

#include "yzf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if YZF_USE_WITH_HAL
//函数生成宏
#define YZ_HAL_PARAMS(type,name1) type name1;
#define YZ_HAL_GET(handle,type,name1) type yz_hal_get_##handle(){return name1;}
#define YZ_HAL_SET(handle,type,name1,name2) void yz_hal_set_##handle(type name1){name2=name1;}

#define YZ_HAL_INIT(handle,type,name1,name2) YZ_HAL_PARAMS(type,name2) YZ_HAL_GET(handle,type,name2) YZ_HAL_SET(handle,type,name1,name2)

//方法定义宏
#define YZ_HAL_GET_METHOD(handle,type) type yz_hal_get_##handle();
#define YZ_HAL_SET_METHOD(handle,type,name1) void yz_hal_set_##handle(type name1);
#define YZ_HAL_INIT_METHOD(handle,type,name1) YZ_HAL_GET_METHOD(handle,type) YZ_HAL_SET_METHOD(handle,type,name1)

//定义方法
YZ_HAL_INIT_METHOD(i2c1,I2C_HandleTypeDef*,hi2c)
YZ_HAL_INIT_METHOD(spi1,SPI_HandleTypeDef*,hspi)
YZ_HAL_INIT_METHOD(spi3,SPI_HandleTypeDef*,hspi)
YZ_HAL_INIT_METHOD(uart1,UART_HandleTypeDef*,huart)
YZ_HAL_INIT_METHOD(sdmmc1,SD_HandleTypeDef*,hsd)
//YZ_HAL_INIT_METHOD(tim6,TIM_HandleTypeDef *,tim)
//YZ_HAL_INIT_METHOD(adc1,ADC_HandleTypeDef *,hadc1)
//YZ_HAL_INIT_METHOD(dac1,DAC_HandleTypeDef *,hdac1)


//suit to hal gpio
extern GPIO_TypeDef *yz_hal_gpio_port;
extern uint16_t yz_hal_gpio_pin;
#endif

#ifdef __cplusplus
};
#endif

#endif //STM32F407CLS_YZ_HAL_H
