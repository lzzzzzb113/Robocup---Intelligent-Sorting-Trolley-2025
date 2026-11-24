//
// Created by 32827 on 2024/7/8.
//
#include "yz_tim.h"
#include "yzf_nvic.h"
YZF_RESULT yz_tim_pwm_init(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin,uint16_t  ch_af,YZF_TIM_POINTER tim,uint16_t ch_id,uint32_t arr,uint32_t psc,uint32_t ccr){

#if YZL_USE_GPIO_WITH_HAL
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull= GPIO_PULLUP;
    GPIO_InitStruct.Speed= GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pin = YZF_PIN_CONV(pin);
    GPIO_InitStruct.Alternate = ch_af;
    HAL_GPIO_Init(gpio,&GPIO_InitStruct);
#else
    YGPIO(gpio)
    YPIN(pin)
    yzf_gpio_open_clock_();
    yzf_gpio_set_AFPP_();
    yzf_gpio_set_af_(ch_af);
#endif

    yzf_tim_open_clock(tim);
    yzf_tim_out_compare_mode_set(tim,ch_id,0b110);
    yzf_tim_set_prescaler(tim,psc);
    yzf_tim_capture_compare_data_set(tim,ch_id,ccr);
    yzf_tim_capture_compare_enable(tim,ch_id,YZF_TRUE);
    yzf_tim_set_auto_reload_number(tim,arr);
    yzf_tim_auto_reload_enable(tim);

    return YZF_OK;
}
YZF_RESULT yz_tim_pwm_start_and_data_set(YZF_TIM_POINTER tim,uint16_t ch_id,uint32_t psc,uint32_t ccr,uint32_t arr){
    yzf_tim_open_clock(tim);
    yzf_tim_disable(tim);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    yzf_tim_out_compare_mode_set(tim,ch_id,0b110);
    yzf_tim_set_prescaler(tim,psc);
    yzf_tim_capture_compare_data_set(tim,ch_id,ccr);
    yzf_tim_capture_compare_enable(tim,ch_id,YZF_TRUE);
    yzf_tim_set_auto_reload_number(tim,arr);
    yzf_tim_auto_reload_enable(tim);
    yzf_tim_capture_compare_preload_enable(tim,ch_id,YZF_TRUE);
    yzf_tim_main_out_enable(tim,YZF_TRUE);
    yzf_tim_enable(tim);
    return YZF_OK;
}
YZF_RESULT yz_tim_pwm_data_set(YZF_TIM_POINTER tim,uint16_t ch_id,uint32_t ccr,uint32_t arr){
    yzf_tim_disable(tim);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    yzf_tim_set_auto_reload_number(tim,arr);
    yzf_tim_capture_compare_data_set(tim,ch_id,ccr);
    yzf_tim_enable(tim);
    return YZF_OK;
}
YZF_RESULT yz_tim_pwm_deInit(YZF_TIM_POINTER tim,uint16_t ch_id){
    yzf_tim_disable(tim);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    yzf_tim_capture_compare_enable(tim,ch_id,YZF_FALSE);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    yzf_tim_out_compare_mode_set(tim,ch_id,0b000);
    yzf_tim_enable(tim);
    return YZF_OK;
}
YZF_PWM_COUNT_DATA TIM1_PWM_COUNT_DATA={
    .it_irq_handler=YZF_NULL_PTR,
    .yz_tim_pwm_count_status=YZF_OK,
    .PWM_COUNT_TIM_OUT_LOCK=YZF_FALSE,
    .pwm_out_tim=YZF_NULL_PTR,
    .pwm_count_tim=TIM1,
    .pwm_out_ch_id=0
};
YZF_PWM_COUNT_DATA TIM8_PWM_COUNT_DATA={
    .it_irq_handler=YZF_NULL_PTR,
    .yz_tim_pwm_count_status=YZF_OK,
    .PWM_COUNT_TIM_OUT_LOCK=YZF_FALSE,
    .pwm_out_tim=YZF_NULL_PTR,
    .pwm_count_tim=TIM8,
    .pwm_out_ch_id=0
};//for STM32H723 Has TIM8 and TIM1
YZF_RESULT yz_tim_pwm_count_irq_handler(void *pwmCountData){
    YZF_PWM_COUNT_DATA *pwm_count_data=(YZF_PWM_COUNT_DATA*)pwmCountData;
    if(pwm_count_data->yz_tim_pwm_count_status==YZF_HANDLER_NOT_FINISH&&yzf_tim_get_update_interrupt_flag(pwm_count_data->pwm_count_tim,YZF_TRUE)) {
        if (pwm_count_data->pwm_out_tim != YZF_NULL_PTR) {
            yz_tim_pwm_data_set(pwm_count_data->pwm_out_tim, pwm_count_data->pwm_out_ch_id, 200, 199);
            yzf_tim_capture_compare_enable(pwm_count_data->pwm_out_tim,pwm_count_data->pwm_out_ch_id,YZF_FALSE);
            pwm_count_data->yz_tim_pwm_count_status = YZF_OK;
            pwm_count_data->PWM_COUNT_TIM_OUT_LOCK = YZF_FALSE;
        }
    }
    return YZF_OK;
}

YZF_RESULT yz_tim_pwm_count_init(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin,uint16_t ch_af,YZF_TIM_POINTER tim,uint16_t ch_id,
                                 uint32_t arr,uint32_t psc,uint32_t ccr,YZF_TIM_POINTER timCountTim,uint32_t count){
    uint16_t trigger_ch;
#if YZL_USE_GPIO_WITH_HAL
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull= GPIO_PULLUP;
    GPIO_InitStruct.Speed= GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pin = YZF_PIN_CONV(pin);
    GPIO_InitStruct.Alternate = ch_af;
    HAL_GPIO_Init(gpio,&GPIO_InitStruct);
#else
    YGPIO(gpio)
    YPIN(pin)
    yzf_gpio_open_clock_();
    yzf_gpio_set_AFPP_();
    yzf_gpio_set_af_(ch_af);
#endif

    yzf_tim_open_clock(tim);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    yzf_tim_out_compare_mode_set(tim,ch_id,0b110);
    yzf_tim_set_prescaler(tim,psc);
    yzf_tim_capture_compare_data_set(tim,ch_id,ccr);
    yzf_tim_capture_compare_enable(tim,ch_id,YZF_TRUE);
    yzf_tim_set_auto_reload_number(tim,arr);
    yzf_tim_auto_reload_enable(tim);

    yzf_tim_capture_compare_preload_enable(tim,ch_id,YZF_TRUE);

    yzf_tim_main_out_enable(tim,YZF_TRUE);

    yzf_tim_master_mode_select(tim,0b010);
    yzf_tim_master_slave_mode_enable(tim,YZF_TRUE);

    yzf_tim_open_clock(timCountTim);
    yzf_tim_set_prescaler(timCountTim,0);

    yzf_tim_set_dir(timCountTim,YZF_TRUE);
    yzf_tim_set_cnt(timCountTim,count);

    yzf_tim_slave_mode_select(timCountTim,0x7);

    ///STM32H723 特化
    switch ((uint32_t)timCountTim) {
        case (uint32_t) TIM8:
            switch ((uint32_t)tim) {
                case (uint32_t) TIM1:
                    trigger_ch=0b00000;
                    break;
                case (uint32_t) TIM2:
                    trigger_ch=0b00001;
                    break;
                case (uint32_t) TIM4:
                    trigger_ch=0b00010;
                    break;
                case (uint32_t) TIM5:
                    trigger_ch=0b00011;
                    break;
                default:
                    return YZF_ERROR;
            }
            break;
        case (uint32_t) TIM1:
            switch ((uint32_t)tim) {
                case (uint32_t) TIM15:
                    trigger_ch=0b00000;
                    break;
                case (uint32_t) TIM2:
                    trigger_ch=0b00001;
                    break;
                case (uint32_t) TIM3:
                    trigger_ch=0b00010;
                    break;
                case (uint32_t) TIM4:
                    trigger_ch=0b00011;
                    break;
                default:
                    return YZF_ERROR;
            }
            break;
        default:
            return YZF_ERROR;
    }
    yzf_tim_trigger_select(timCountTim,trigger_ch);

    yzf_tim_get_update_interrupt_flag(timCountTim,YZF_TRUE);
    yzf_tim_update_interrupt_enable(timCountTim,YZF_TRUE);

    switch ((uint32_t)timCountTim) {
        case (uint32_t)TIM8:
            yzf_nvic_irq_enable(TIM8_UP_TIM13_IRQn);
            yzf_nvic_irq_set_priority(TIM8_UP_TIM13_IRQn,0);
            break;
        case (uint32_t)TIM1:
            yzf_nvic_irq_enable(TIM1_UP_IRQn);
            yzf_nvic_irq_set_priority(TIM1_UP_IRQn,0);
            break;
        default:
            return YZF_ERROR;
    }

    switch ((uint32_t)timCountTim) {
        case (uint32_t)TIM1:
            TIM1_PWM_COUNT_DATA.it_irq_handler=yz_tim_pwm_count_irq_handler;
            TIM1_PWM_COUNT_DATA.yz_tim_pwm_count_status=YZF_HANDLER_NOT_FINISH;
            TIM1_PWM_COUNT_DATA.pwm_out_tim=tim;
            TIM1_PWM_COUNT_DATA.pwm_count_tim=timCountTim;
            TIM1_PWM_COUNT_DATA.pwm_out_ch_id=ch_id;
            break;
        case (uint32_t) TIM8:
            TIM8_PWM_COUNT_DATA.it_irq_handler=yz_tim_pwm_count_irq_handler;
            TIM8_PWM_COUNT_DATA.yz_tim_pwm_count_status=YZF_HANDLER_NOT_FINISH;
            TIM8_PWM_COUNT_DATA.pwm_out_tim=tim;
            TIM8_PWM_COUNT_DATA.pwm_count_tim=timCountTim;
            TIM8_PWM_COUNT_DATA.pwm_out_ch_id=ch_id;
            break;
        default:
            return YZF_ERROR;
    }


    yzf_tim_enable(timCountTim);
    yzf_tim_enable(tim);
    return YZF_OK;
}

YZF_BOOL yz_tim_pwm_with_count_is_finish(YZF_TIM_POINTER tim){
    switch ((uint32_t)tim) {
        case (uint32_t)TIM1:
            return TIM1_PWM_COUNT_DATA.yz_tim_pwm_count_status==YZF_OK ? YZF_TRUE : YZF_FALSE;
        case (uint32_t)TIM8:
            return TIM8_PWM_COUNT_DATA.yz_tim_pwm_count_status==YZF_OK ? YZF_TRUE : YZF_FALSE;
        default:
            return YZF_FALSE;
    }
}

YZF_RESULT yz_tim_pwm_with_count_fast(YZF_TIM_POINTER tim,uint16_t ch_id,YZF_TIM_POINTER timCountTim,
                                      uint32_t count){
    uint16_t trigger_ch=0b00000;

    if(count == 0){
        return YZF_OK;
    }

    switch ((uint32_t)timCountTim) {
        case (uint32_t)TIM8:
            if(TIM8_PWM_COUNT_DATA.PWM_COUNT_TIM_OUT_LOCK){
                return YZF_ERROR;
            }else{
                TIM8_PWM_COUNT_DATA.PWM_COUNT_TIM_OUT_LOCK=YZF_TRUE;
            }
            break;
        case (uint32_t)TIM1:
            if(TIM1_PWM_COUNT_DATA.PWM_COUNT_TIM_OUT_LOCK){
                return YZF_ERROR;
            }else{
                TIM1_PWM_COUNT_DATA.PWM_COUNT_TIM_OUT_LOCK=YZF_TRUE;
            }
            break;
        default:
            return YZF_ERROR;
    }

    yzf_tim_open_clock(timCountTim);
    yzf_tim_set_prescaler(timCountTim,0);

    yzf_tim_set_dir(timCountTim,YZF_TRUE);
    yzf_tim_set_cnt(timCountTim,count);

    yzf_tim_slave_mode_select(timCountTim,0x7);

    ///STM32H723 特化
    switch ((uint32_t)timCountTim) {
        case (uint32_t) TIM8:
            switch ((uint32_t)tim) {
                case (uint32_t) TIM1:
                    trigger_ch=0b00000;
                    break;
                case (uint32_t) TIM2:
                    trigger_ch=0b00001;
                    break;
                case (uint32_t) TIM4:
                    trigger_ch=0b00010;
                    break;
                case (uint32_t) TIM5:
                    trigger_ch=0b00011;
                    break;
            }
            break;
        case (uint32_t) TIM1:
            switch ((uint32_t)tim) {
                case (uint32_t) TIM15:
                    trigger_ch=0b00000;
                    break;
                case (uint32_t) TIM2:
                    trigger_ch=0b00001;
                    break;
                case (uint32_t) TIM3:
                    trigger_ch=0b00010;
                    break;
                case (uint32_t) TIM4:
                    trigger_ch=0b00011;
                    break;
            }
            break;
        default:
            return YZF_ERROR;
    }
    yzf_tim_trigger_select(timCountTim,trigger_ch);

    yzf_tim_get_update_interrupt_flag(timCountTim,YZF_TRUE);
    yzf_tim_update_interrupt_enable(timCountTim,YZF_TRUE);

    switch ((uint32_t)timCountTim) {
        case (uint32_t)TIM8:
            yzf_nvic_irq_enable(TIM8_UP_TIM13_IRQn);
            yzf_nvic_irq_set_priority(TIM8_UP_TIM13_IRQn,0);
            break;
        case (uint32_t)TIM1:
            yzf_nvic_irq_enable(TIM1_UP_IRQn);
            yzf_nvic_irq_set_priority(TIM1_UP_IRQn,0);
            break;
        default:
            return YZF_ERROR;
    }

    switch ((uint32_t)timCountTim) {
        case (uint32_t)TIM1:
            TIM1_PWM_COUNT_DATA.it_irq_handler=yz_tim_pwm_count_irq_handler;
            TIM1_PWM_COUNT_DATA.yz_tim_pwm_count_status=YZF_HANDLER_NOT_FINISH;
            TIM1_PWM_COUNT_DATA.pwm_out_tim=tim;
            TIM1_PWM_COUNT_DATA.pwm_count_tim=timCountTim;
            TIM1_PWM_COUNT_DATA.pwm_out_ch_id=ch_id;
            break;
        case (uint32_t) TIM8:
            TIM8_PWM_COUNT_DATA.it_irq_handler=yz_tim_pwm_count_irq_handler;
            TIM8_PWM_COUNT_DATA.yz_tim_pwm_count_status=YZF_HANDLER_NOT_FINISH;
            TIM8_PWM_COUNT_DATA.pwm_out_tim=tim;
            TIM8_PWM_COUNT_DATA.pwm_count_tim=timCountTim;
            TIM8_PWM_COUNT_DATA.pwm_out_ch_id=ch_id;
            break;
        default:
            return YZF_ERROR;
    }

    yzf_tim_enable(timCountTim);
    yzf_tim_capture_compare_enable(tim,ch_id,YZF_TRUE);
    yzf_tim_enable(tim);
    return YZF_OK;
}

YZF_RESULT yz_tim_pwm_enable_ch(YZF_TIM_POINTER tim,uint16_t ch_id){
    yzf_tim_capture_compare_enable(tim,ch_id,YZF_TRUE);
    yzf_tim_enable(tim);
    return YZF_OK;
}
YZF_RESULT yz_tim_pwm_disable_ch(YZF_TIM_POINTER tim,uint16_t ch_id){
    yzf_tim_capture_compare_enable(tim,ch_id,YZF_FALSE);
    yzf_tim_disable(tim);
    return YZF_OK;
}