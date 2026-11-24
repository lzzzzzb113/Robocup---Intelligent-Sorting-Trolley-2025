//
// Created by 32827 on 2024/1/10.
//

#ifndef YZL_SOFTPORT_H
#define YZL_SOFTPORT_H
#include "yzl.h"
#if USE_SOFT_PORT

#if YZL_USE_GPIO_WITH_HAL
typedef struct{
    uint16_t pin;
    GPIO_TypeDef *port;
}YZL_GPIO;
#define YLGPIO(x) (yz_hal_gpio_port=x.port;yz_hal_gpio_pin=x.pin);
#define YLHIGH(x) HAL_GPIO_WritePin(x.port,x.pin,GPIO_PIN_SET)
#define YLLOW(x) HAL_GPIO_WritePin(x.port,x.pin,GPIO_PIN_RESET)
#else
#include "yzf_gpio.h"
typedef struct{
    YZF_GPIO_PIN pin;
    YZF_GPIO_POINTER port;
}YZL_GPIO;
#define YLGPIO(x) YGPIO(x.port)YPIN(x.pin)
#define YLHIGH(x) yzf_gpio_set_1(x.port,x.pin)
#define YLLOW(x) yzf_gpio_set_0(x.port,x.pin)
#endif


#ifdef __cplusplus
extern "C" {
#endif

void yzl_softport_delayUS(__IO uint32_t ulCount);

void yzl_softport_delayMS(__IO uint32_t ulCount);

#ifdef __cplusplus
}
#endif

///@deprecated
#define delay_ms(x) yzl_softport_delayMS(x)
#define delay_us(x) yzl_softport_delayUS(x)
// #define delay_ms(x) yzl_clock_delay_ms(x)
// #define delay_us(x) yzl_clock_delay_us(x)

#endif
#endif //STM32OSCOVER_YZL_SOFTPORT_H
