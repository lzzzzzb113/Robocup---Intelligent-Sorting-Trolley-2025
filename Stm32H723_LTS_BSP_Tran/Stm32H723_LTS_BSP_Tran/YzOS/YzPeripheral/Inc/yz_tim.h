//
// Created by 32827 on 2024/7/8.
//

#ifndef YZL_TIM_H
#define YZL_TIM_H
#include "yzf_tim.h"
#include "yzf_gpio.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    YZF_RESULT (*it_irq_handler)(void *pwmCountData);
    YZF_RESULT yz_tim_pwm_count_status;
    YZF_BOOL PWM_COUNT_TIM_OUT_LOCK;
    YZF_TIM_POINTER pwm_out_tim;
    YZF_TIM_POINTER pwm_count_tim;
    uint16_t  pwm_out_ch_id;
} YZF_PWM_COUNT_DATA;

YZF_RESULT yz_tim_pwm_init(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin,uint16_t  ch_af,YZF_TIM_POINTER tim,uint16_t ch_id,uint32_t arr,uint32_t psc,uint32_t ccr);
YZF_RESULT yz_tim_pwm_data_set(YZF_TIM_POINTER tim,uint16_t ch_id,uint32_t ccr,uint32_t arr);
YZF_RESULT yz_tim_pwm_start_and_data_set(YZF_TIM_POINTER tim,uint16_t ch_id,uint32_t psc,uint32_t ccr,uint32_t arr);
YZF_RESULT yz_tim_pwm_deInit(YZF_TIM_POINTER tim,uint16_t ch_id);


extern YZF_PWM_COUNT_DATA TIM8_PWM_COUNT_DATA;
extern YZF_PWM_COUNT_DATA TIM1_PWM_COUNT_DATA;
YZF_RESULT yz_tim_pwm_count_init(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin,uint16_t ch_af,YZF_TIM_POINTER tim,uint16_t ch_id,
                                 uint32_t arr,uint32_t psc,uint32_t ccr,YZF_TIM_POINTER timCountTim,uint32_t count);
/**
 * Now Used for Hal Library
 * */
YZF_RESULT yz_tim_pwm_with_count_fast(YZF_TIM_POINTER tim,uint16_t ch_id,YZF_TIM_POINTER timCountTim,
                                      uint32_t count);
YZF_BOOL yz_tim_pwm_with_count_is_finish(YZF_TIM_POINTER tim);
YZF_RESULT yz_tim_pwm_enable_ch(YZF_TIM_POINTER tim,uint16_t ch_id);
YZF_RESULT yz_tim_pwm_disable_ch(YZF_TIM_POINTER tim,uint16_t ch_id);
#ifdef __cplusplus
}
#endif
#endif //STM32F407RTOS_YZL_TIM_H
