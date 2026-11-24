//
// Created by 32827 on 2023/11/15.
//

#ifndef YZ_GPIO_H
#define YZ_GPIO_H
#include "yzf.h"
#ifdef __cplusplus
extern "C" {
#endif
YZF_RESULT yzf_gpio_open_clock(YZF_GPIO_POINTER gpio);
YZF_RESULT yzf_gpio_close_clock(YZF_GPIO_POINTER gpio);
YZF_RESULT yzf_gpio_set_Pull_Up(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_Pull_Down(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_PP(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_OD(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_AFPP(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_AFOD(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_IN_FLOAT(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_IN_PULL_UP(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_IN_PULL_DOWN(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_IN_ANALOG(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_MIDDLE(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_LOW(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_HIGH(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_0(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_1(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_lock(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_unlock(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_set_af(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin,uint8_t af);
YZF_BOOL yzf_gpio_get(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin);
/**
 * 便捷调用模式
 * 将通过yzf_gpio()指定后可调用便捷方式
 * */
YZF_RESULT yzf_gpio(YZF_GPIO_POINTER gpio);
YZF_RESULT yzf_gpio_pin(YZF_GPIO_PIN pin);
YZF_RESULT yzf_gpio_open_clock_();
YZF_RESULT yzf_gpio_close_clock_();
YZF_RESULT yzf_gpio_set_PP_();
YZF_RESULT yzf_gpio_set_OD_();
YZF_RESULT yzf_gpio_set_AFPP_();
YZF_RESULT yzf_gpio_set_AFOD_();
YZF_RESULT yzf_gpio_set_IN_FLOAT_();
YZF_RESULT yzf_gpio_set_IN_PULL_UP_();
YZF_RESULT yzf_gpio_set_Pull_Up_();
YZF_RESULT yzf_gpio_set_Pull_Down_();
YZF_RESULT yzf_gpio_set_IN_PULL_DOWN_();
YZF_RESULT yzf_gpio_set_IN_ANALOG_();
YZF_RESULT yzf_gpio_set_MIDDLE_();
YZF_RESULT yzf_gpio_set_LOW_();
YZF_RESULT yzf_gpio_set_HIGH_();
YZF_RESULT yzf_gpio_set_0_();
YZF_RESULT yzf_gpio_set_1_();
YZF_RESULT yzf_gpio_lock_();
YZF_RESULT yzf_gpio_unlock_();
YZF_RESULT yzf_gpio_set_af_(uint8_t type);
YZF_BOOL yzf_gpio_get_();
#define YGPIO(n) yzf_gpio(n);
#define YPIN(n) yzf_gpio_pin(n);

#ifdef __cplusplus
}
#endif
#endif //YZ_GPIO_H