//
// Created by 32827 on 2023/11/18.
//

#ifndef YZFRAME_YZF_EXTI_H
#define YZFRAME_YZF_EXTI_H
#include "yzf.h"
#ifdef __cplusplus
extern "C" {
#endif
/**
 * 中断响应开启
 * */
YZF_RESULT yzf_exti_interrupt_enable(uint8_t exti_line);
YZF_RESULT yzf_exti_interrupt_disable(uint8_t exti_line);
/**
 * 事件分发开启,如硬件i2c,spi等都需要
 * */
YZF_RESULT yzf_exti_interrupt_event_enable(uint8_t exti_line);
YZF_RESULT yzf_exti_interrupt_event_disable(uint8_t exti_line);
/**
 * 上升沿中断响应
 * */
YZF_RESULT yzf_exti_interrupt_rise_enable(uint8_t exti_line);
YZF_RESULT yzf_exti_interrupt_rise_disable(uint8_t exti_line);
/**
 * 下降沿中断响应
 * */
YZF_RESULT yzf_exti_interrupt_fall_enable(uint8_t exti_line);
YZF_RESULT yzf_exti_interrupt_fall_disable(uint8_t exti_line);
/**
 * 软件中断
 * */
YZF_RESULT yzf_exti_interrupt_software_post(uint8_t exti_line);
YZF_RESULT yzf_exti_interrupt_software_clear(uint8_t exti_line);
/**
 * 中断标志位
 * */
YZF_BOOL yzf_exti_interrupt_flag_get(uint8_t exti_line);
YZF_RESULT yzf_exti_interrupt_flag_clear(uint8_t exti_line);
#ifdef __cplusplus
}
#endif
#endif //YZFRAME_YZF_EXTI_H
