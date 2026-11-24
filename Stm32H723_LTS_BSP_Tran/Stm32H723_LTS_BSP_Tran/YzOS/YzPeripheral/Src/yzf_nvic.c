//
// Created by 32827 on 2023/11/18.
//
#include "yzf_nvic.h"

YZF_RESULT yzf_nvic_irq_enable(uint16_t irq_num){
    NVIC->ISER[irq_num / 32]= 0b1UL <<(irq_num%32);
    return YZF_OK;
}
YZF_RESULT yzf_nvic_irq_disable(uint16_t irq_num){
    NVIC->ICER[irq_num / 32]= 0b1UL <<(irq_num%32);
    return YZF_OK;
}
/**
 * 设置是否挂起标志位
 * */
YZF_RESULT yzf_nvic_irq_post_sign(uint16_t irq_num){
    NVIC->ISPR[irq_num / 32]= 0b1UL <<(irq_num%32);
    return YZF_OK;
}
YZF_RESULT yzf_nvic_irq_clear_sign(uint16_t irq_num){
    NVIC->ICPR[irq_num / 32]= 0b1UL <<(irq_num%32);
    return YZF_OK;
}
/**
 * 激活位寄存器查看
 * */
YZF_BOOL yzf_nvic_irq_is_working(uint16_t irq_num){
    return (NVIC->IABR[irq_num / 32]&(0b1UL <<(irq_num%32)))==0?YZF_FALSE:YZF_TRUE;
}
/**
 * 设置优先级
 * */
YZF_RESULT yzf_nvic_irq_set_priority(uint16_t irq_num, uint8_t priority){
    NVIC->IP[irq_num]=priority;
    return YZF_OK;
}
/**
 * 设置中断优先级
 * */
YZF_RESULT yzf_nvic_irq_set_priority_group(uint8_t mode){
    SCB->AIRCR=(0x05FA0000|(SCB->AIRCR&~(0b111<<SCB_AIRCR_PRIGROUP_Pos)));
    SCB->AIRCR|=(0x05FA0000|(mode<<SCB_AIRCR_PRIGROUP_Pos));
    return YZF_OK;
}