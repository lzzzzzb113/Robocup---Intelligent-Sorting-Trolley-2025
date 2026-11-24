//
// Created by 32827 on 2024/6/24.
//
#include "yzf_tim.h"
//For H7 Version 275Mhz
YZF_RESULT yzf_tim_open_clock(YZF_TIM_POINTER p_tim){
    switch ((uint32_t)p_tim) {
        case (uint32_t)TIM1:
            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
            break;
        case (uint32_t)TIM2:
            RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
            break;
        case (uint32_t)TIM3:
            RCC->APB1LENR |= RCC_APB1LENR_TIM3EN;
            break;
        case (uint32_t)TIM4:
            RCC->APB1LENR |= RCC_APB1LENR_TIM4EN;
            break;
        case (uint32_t)TIM5:
            RCC->APB1LENR |= RCC_APB1LENR_TIM5EN;
            break;
        case (uint32_t)TIM6:
            RCC->APB1LENR |= RCC_APB1LENR_TIM6EN;
            break;
        case (uint32_t)TIM7:
            RCC->APB1LENR |= RCC_APB1LENR_TIM7EN;
            break;
        case (uint32_t)TIM8:
            RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
            break;
        case (uint32_t)TIM12:
            RCC->APB2ENR |= RCC_APB1LENR_TIM12EN;
            break;
        case (uint32_t)TIM13:
            RCC->APB1LENR |= RCC_APB1LENR_TIM13EN;
            break;
        case (uint32_t)TIM15:
            RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
            break;
        case (uint32_t)TIM16:
            RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
            break;
        case (uint32_t)TIM17:
            RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}

YZF_RESULT yzf_tim_enable(YZF_TIM_POINTER p_tim){
    p_tim->CR1 |= TIM_CR1_CEN;
    return YZF_OK;
}
YZF_RESULT yzf_tim_disable(YZF_TIM_POINTER p_tim){
    p_tim->CR1 &= ~TIM_CR1_CEN;
    return YZF_OK;
}

YZF_RESULT yzf_tim_update_event_disable(YZF_TIM_POINTER p_tim){
    p_tim->CR1 |= TIM_CR1_UDIS;
    return  YZF_OK;
}
YZF_RESULT yzf_tim_update_event_enable(YZF_TIM_POINTER p_tim){
    p_tim->CR1 &= ~TIM_CR1_UDIS;
    return  YZF_OK;
}

YZF_RESULT yzf_tim_update_interrupt_enable(YZF_TIM_POINTER p_tim,YZF_BOOL isEnable){
    if(isEnable){
        p_tim->DIER |= TIM_DIER_UIE;
    }else{
        p_tim->DIER &= ~TIM_DIER_UIE;
    }
    return  YZF_OK;
}

YZF_RESULT yzf_tim_update_source(YZF_TIM_POINTER p_tim, uint8_t source){
    p_tim->CR1 &= ~TIM_CR1_URS;
    p_tim->CR1 |= source<<TIM_CR1_URS_Pos;
    return  YZF_OK;
}
YZF_RESULT yzf_tim_set_dir(YZF_TIM_POINTER p_tim, YZF_BOOL isSub){
    p_tim->CR1 &= ~TIM_CR1_DIR;
    p_tim->CR1 |= isSub<<TIM_CR1_DIR_Pos;
    return  YZF_OK;
}
YZF_RESULT yzf_tim_set_one_pulse_mode(YZF_TIM_POINTER p_tim,YZF_BOOL isOne){
    p_tim->CR1 &= ~TIM_CR1_OPM;
    p_tim->CR1 |= isOne<<TIM_CR1_OPM_Pos;
    return  YZF_OK;
}
YZF_RESULT yzf_tim_set_clock_division(YZF_TIM_POINTER p_tim, uint8_t division){
    p_tim->CR1 &= ~TIM_CR1_CKD;
    p_tim->CR1 |= division<<TIM_CR1_CKD_Pos;
    return  YZF_OK;
}
YZF_RESULT yzf_tim_auto_reload_enable(YZF_TIM_POINTER p_tim){
    p_tim->CR1 |= TIM_CR1_ARPE;
    return  YZF_OK;
}
YZF_RESULT yzf_tim_auto_reload_disable(YZF_TIM_POINTER p_tim){
    p_tim->CR1 &= ~TIM_CR1_ARPE;
    return  YZF_OK;
}

YZF_RESULT yzf_tim_center_align_mode_select(YZF_TIM_POINTER p_tim,uint8_t mode){
    YZF_MODIFY_REG(p_tim->CR1,TIM_CR1_CMS,mode,TIM_CR1_CMS_Pos);
    return  YZF_OK;
}
YZF_BOOL yzf_tim_get_update_interrupt_flag(YZF_TIM_POINTER p_tim,YZF_BOOL isClear){
    YZF_BOOL flag=(p_tim->SR & TIM_SR_UIF)==TIM_SR_UIF;
    if(isClear){
        p_tim->SR &= ~TIM_SR_UIF;
    }
    return flag;
}
YZF_RESULT yzf_tim_create_update_event(YZF_TIM_POINTER p_tim){
    p_tim->EGR |= TIM_EGR_UG;
    return  YZF_OK;
}

YZF_RESULT yzf_tim_set_cnt(YZF_TIM_POINTER p_tim, uint32_t cnt){
    p_tim->CNT = cnt;
    return  YZF_OK;
}
YZF_RESULT yzf_tim_get_cnt(YZF_TIM_POINTER p_tim, uint32_t *cnt){
    *cnt = p_tim->CNT;
    return YZF_OK;
}
YZF_RESULT yzf_tim_set_prescaler(YZF_TIM_POINTER p_tim, uint16_t prescaler){
    p_tim->PSC=prescaler;
    return YZF_OK;
}
YZF_RESULT yzf_tim_get_prescaler(YZF_TIM_POINTER p_tim, uint16_t *prescaler){
    *prescaler=p_tim->PSC;
    return YZF_OK;
}
YZF_RESULT yzf_tim_set_auto_reload_number(YZF_TIM_POINTER p_tim,uint16_t arr){
    p_tim->ARR=arr;
    return YZF_OK;
}
YZF_RESULT yzf_tim_set_auto_reload_number32(YZF_TIM_POINTER p_tim,uint32_t arr){
    p_tim->ARR=arr;
    return YZF_OK;
}
YZF_RESULT yzf_tim_get_auto_reload_number(YZF_TIM_POINTER p_tim,uint16_t *arr){
    *arr=p_tim->ARR;
    return YZF_OK;
}

YZF_RESULT yzf_tim_master_mode_select(YZF_TIM_POINTER p_tim,uint16_t mms){
    YZF_MODIFY_REG(p_tim->CR2,TIM_CR2_MMS,mms,TIM_CR2_MMS_Pos);
    return YZF_OK;
}

YZF_RESULT yzf_tim_trigger_select(YZF_TIM_POINTER p_tim,uint16_t trigger){
    YZF_MODIFY_REG(p_tim->SMCR,0x2 << 20,trigger&0x2 >> 3,20);
    YZF_MODIFY_REG(p_tim->SMCR,0x7 << 4,trigger&0x7,4);
    return YZF_OK;
}

YZF_RESULT yzf_tim_slave_mode_select(YZF_TIM_POINTER p_tim,uint16_t sms){
    YZF_MODIFY_REG(p_tim->SMCR,0x1 << 16,(sms&0x8) >> 3,16);
    YZF_MODIFY_REG(p_tim->SMCR,0x7,sms&0x7,0);
    return YZF_OK;
}

YZF_RESULT yzf_tim_master_slave_mode_enable(YZF_TIM_POINTER p,uint16_t enable){
    YZF_MODIFY_REG(p->SMCR,TIM_SMCR_MSM,enable,TIM_SMCR_MSM_Pos);
    return YZF_OK;
}

YZF_RESULT yzf_tim_out_compare_mode_set(YZF_TIM_POINTER p,uint16_t ch_id,uint16_t mode){
    switch (ch_id) {
        case 1:
            YZF_MODIFY_REG(p->CCMR1,(TIM_CCMR1_OC1M_0|TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1M_2),mode&0x7,TIM_CCMR1_OC1M_Pos);
            YZF_MODIFY_REG(p->CCMR1,TIM_CCMR1_OC1M_3,(mode&0x8) >> 3, 16);
            return YZF_OK;
        case 2:
            YZF_MODIFY_REG(p->CCMR1,(TIM_CCMR1_OC2M_0|TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2M_2),mode&0x7,TIM_CCMR1_OC2M_Pos);
            YZF_MODIFY_REG(p->CCMR1,TIM_CCMR1_OC2M_3,(mode&0x8) >> 3, 24);
            return YZF_OK;
        case 3:
            YZF_MODIFY_REG(p->CCMR2,(TIM_CCMR2_OC3M_0|TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_2),mode&0x7,TIM_CCMR2_OC3M_Pos);
            YZF_MODIFY_REG(p->CCMR2,TIM_CCMR2_OC3M_3,(mode&0x8) >> 3, 16);
            return YZF_OK;
        case 4:
            YZF_MODIFY_REG(p->CCMR2,(TIM_CCMR2_OC4M_0|TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_2),mode&0x7,TIM_CCMR2_OC4M_Pos);
            YZF_MODIFY_REG(p->CCMR2,TIM_CCMR2_OC4M_3,(mode&0x8) >> 3, 24);
            return YZF_OK;
        default:
            return YZF_NOT_FOUND;
    }
}

YZF_RESULT yzf_tim_main_out_enable(YZF_TIM_POINTER p,YZF_BOOL isEnable){
    YZF_MODIFY_REG(p->BDTR,TIM_BDTR_MOE,isEnable,TIM_BDTR_MOE_Pos);
    return YZF_OK;
}

YZF_RESULT yzf_tim_break_enable(YZF_TIM_POINTER p,YZF_BOOL isEnable){
    YZF_MODIFY_REG(p->BDTR,TIM_BDTR_BKE,isEnable,TIM_BDTR_BKE_Pos);
    return YZF_OK;
}

YZF_RESULT yzf_tim_capture_compare_enable(YZF_TIM_POINTER p_tim,uint16_t ch_id,YZF_BOOL isEnable){
    YZF_MODIFY_REG(p_tim->CCER,(0x1UL<<(4*(ch_id-1))),isEnable,(4*(ch_id-1)));
    return YZF_OK;
}
YZF_RESULT yzf_tim_capture_compare_preload_enable(YZF_TIM_POINTER p_tim,uint16_t ch_id,YZF_BOOL isEnable){
    YZF_MODIFY_REG(p_tim->CCER,(0x1UL<<(4*(ch_id-1)+3)),isEnable,(4*(ch_id-1)+1));
    return YZF_OK;
}
YZF_RESULT yzf_tim_capture_compare_data_set(YZF_TIM_POINTER p_tim,uint16_t ch_id,uint32_t data){
    YZF_MODIFY_REG(*(((uint32_t *)&p_tim->CCR1)+(ch_id-1)),TIM_CCR1_CCR1,data,TIM_CCR1_CCR1_Pos);
    return YZF_OK;
}