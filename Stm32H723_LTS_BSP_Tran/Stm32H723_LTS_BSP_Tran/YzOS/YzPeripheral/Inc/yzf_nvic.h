//
// Created by 32827 on 2023/11/18.
//

#ifndef YZFRAME_YZF_NVIC_H
#define YZFRAME_YZF_NVIC_H
#include "yzf.h"
#ifdef __cplusplus
extern "C" {
#endif
YZF_RESULT yzf_nvic_irq_enable(uint16_t irq_num);
YZF_RESULT yzf_nvic_irq_disable(uint16_t irq_num);
/**
 * 设置是否挂起标志位
 * */
YZF_RESULT yzf_nvic_irq_post_sign(uint16_t irq_num);
YZF_RESULT yzf_nvic_irq_clear_sign(uint16_t irq_num);
/**
 * 激活位寄存器查看
 * */
YZF_BOOL yzf_nvic_irq_is_working(uint16_t irq_num);
/**
 * 设置优先级
 * */
YZF_RESULT yzf_nvic_irq_set_priority(uint16_t irq_num, uint8_t priority);
/**
 * 设置中断优先级
 * */
YZF_RESULT yzf_nvic_irq_set_priority_group(uint8_t mode);
#ifdef __cplusplus
}
#endif
#endif //YZFRAME_YZF_NVIC_H