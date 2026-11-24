//
// Created by 32827 on 2023/11/18.
//
#include "yzf_exti.h"
YZF_RESULT yzf_exti_interrupt_enable(uint8_t exti_line){
    EXTI->IMR1|= (1 << exti_line);
    return YZF_OK;
}
YZF_RESULT yzf_exti_interrupt_disable(uint8_t exti_line){
    EXTI->IMR1&= ~(1 << exti_line);
    return YZF_OK;
};
/**
 * 事件分发开启,如硬件i2c,spi等都需要
 * */
YZF_RESULT yzf_exti_interrupt_event_enable(uint8_t exti_line){
    EXTI->EMR1|= (1 << exti_line);
    return YZF_OK;
}
YZF_RESULT yzf_exti_interrupt_event_disable(uint8_t exti_line){
    EXTI->EMR1&= ~(1 << exti_line);
    return YZF_OK;
}
/**
 * 上升沿中断响应
 * */
YZF_RESULT yzf_exti_interrupt_rise_enable(uint8_t exti_line){
    EXTI->RTSR1|= (1 << exti_line);
    return YZF_OK;
}
YZF_RESULT yzf_exti_interrupt_rise_disable(uint8_t exti_line){
    EXTI->RTSR1&= ~(1 << exti_line);
    return YZF_OK;
}
/**
 * 下降沿中断响应
 * */
YZF_RESULT yzf_exti_interrupt_fall_enable(uint8_t exti_line){
    EXTI->FTSR1|= (1 << exti_line);
    return YZF_OK;
}
YZF_RESULT yzf_exti_interrupt_fall_disable(uint8_t exti_line){
    EXTI->FTSR1&= ~(1 << exti_line);
    return YZF_OK;
}
/**
 * 软件中断
 * */
YZF_RESULT yzf_exti_interrupt_software_post(uint8_t exti_line){
    EXTI->SWIER1|= (1 << exti_line);
    return  YZF_OK;
}
YZF_RESULT yzf_exti_interrupt_software_clear(uint8_t exti_line){
    EXTI->SWIER1 &= ~(1 << exti_line);
    return  YZF_OK;
}
/**
 * 中断标志位
 * */
YZF_BOOL yzf_exti_interrupt_flag_get(uint8_t exti_line){
    if(EXTI->PR1&(1 << exti_line)){
        return YZF_TRUE;
    }else{
        return YZF_FALSE;
    }
}
YZF_RESULT yzf_exti_interrupt_flag_clear(uint8_t exti_line){
    EXTI->PR1 |= EXTI_PR1_PR0;
    return  YZF_OK;
}