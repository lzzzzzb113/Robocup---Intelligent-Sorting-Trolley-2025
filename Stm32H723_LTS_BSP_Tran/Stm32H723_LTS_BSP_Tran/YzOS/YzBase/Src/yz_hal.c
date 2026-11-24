//
// Created by 32827 on 2023/12/10.
//
#include "yz_hal.h"
#if YZF_USE_WITH_HAL
YZ_HAL_INIT(i2c1,I2C_HandleTypeDef*,hi2c,y_hi2c1)

YZ_HAL_INIT(spi1,SPI_HandleTypeDef*,hspi,y_hspi1)

YZ_HAL_INIT(spi3,SPI_HandleTypeDef*,hspi,y_hspi3)

YZ_HAL_INIT(uart1,UART_HandleTypeDef*,huart,y_huart1)

YZ_HAL_INIT(sdmmc1,SD_HandleTypeDef*,hsd,y_hsd1)

//YZ_HAL_INIT(tim6,TIM_HandleTypeDef*,tim,y_tim6)

//YZ_HAL_INIT(adc1,ADC_HandleTypeDef*,hadc,y_hadc1)

//YZ_HAL_INIT(dac1,DAC_HandleTypeDef*,hdac,y_hdac1)

GPIO_TypeDef *yz_hal_gpio_port;
uint16_t yz_hal_gpio_pin;
#endif