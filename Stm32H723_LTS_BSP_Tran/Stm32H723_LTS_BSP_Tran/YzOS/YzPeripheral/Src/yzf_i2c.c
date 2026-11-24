//
// Created by 32827 on 2023/11/21.
//
#include "yzf_i2c.h"
YZF_RESULT yzf_i2c_open(YZF_I2C_POINTER i2c){
    switch ((uint32_t)i2c) {
        case (uint32_t)I2C1:
            RCC->APB1LENR |=RCC_APB1LENR_I2C1EN;
            break;
        case (uint32_t)I2C2:
            RCC->APB1LENR |=RCC_APB1LENR_I2C2EN;
            break;
        case (uint32_t)I2C3:
            RCC->APB1LENR |=RCC_APB1LENR_I2C3EN;
            break;
        case (uint32_t)I2C4:
            RCC->APB4ENR |=RCC_APB4ENR_I2C4EN;
            break;
        case (uint32_t)I2C5:
            RCC->APB1LENR |=RCC_APB1LENR_I2C5EN;
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}
//设置起始位
YZF_RESULT yzf_i2c_start(YZF_I2C_POINTER i2c){
    i2c->CR2 |= 0b1 << I2C_CR2_START_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_write_data(YZF_I2C_POINTER i2c,YZF_I2C_DATA data){
    //i2c->DR &= ~(0xFF << I2C_DR_DR_Pos);
    i2c->TXDR = data << I2C_TXDR_TXDATA_Pos;
    return YZF_OK;
}
YZF_I2C_DATA yzf_i2c_read_data(YZF_I2C_POINTER i2c){
    return i2c->RXDR & (0xFF << I2C_RXDR_RXDATA_Pos);
}
YZF_RESULT yzf_i2c_send_address_10(YZF_I2C_POINTER i2c,uint16_t address){
    YZF_MODIFY_REG(i2c->CR2,I2C_CR2_SADD,address,I2C_CR2_SADD_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_send_address_7(YZF_I2C_POINTER i2c,uint8_t address){
    YZF_MODIFY_REG(i2c->CR2,I2C_CR2_SADD,address&0x7F,(I2C_CR2_SADD_Pos+1));
    return YZF_OK;
}
YZF_RESULT yzf_i2c_set_address_7(YZF_I2C_POINTER i2c,uint8_t address,YZF_BOOL EnableCall){
    YZF_MODIFY_REG(i2c->OAR1,I2C_OAR1_OA1EN,0,I2C_OAR1_OA1EN_Pos);//当0时可写入
    YZF_MODIFY_REG(i2c->CR2,I2C_CR2_ADD10,0x0,I2C_CR2_ADD10_Pos);
    YZF_MODIFY_REG(i2c->OAR1,I2C_OAR1_OA1MODE,0,I2C_OAR1_OA1MODE_Pos);
    i2c->OAR1 &= ~(0b1111111 << 1);
    i2c->OAR1 |= address << 1;
    YZF_MODIFY_REG(i2c->OAR1,I2C_OAR1_OA1EN,EnableCall,I2C_OAR1_OA1EN_Pos);
    return YZF_OK;
}
//设置10位地址
YZF_RESULT yzf_i2c_set_address_10(YZF_I2C_POINTER i2c,uint16_t address,YZF_BOOL EnableCall){
    YZF_MODIFY_REG(i2c->OAR1,I2C_OAR1_OA1EN,0,I2C_OAR1_OA1EN_Pos);
    YZF_MODIFY_REG(i2c->CR2,I2C_CR2_ADD10,0x1,I2C_CR2_ADD10_Pos);
    YZF_MODIFY_REG(i2c->OAR1,I2C_OAR1_OA1MODE,1,I2C_OAR1_OA1MODE_Pos);
    i2c->OAR1 &= ~(0b1111111111 << I2C_OAR1_OA1_Pos);
    i2c->OAR1 |= address << I2C_OAR1_OA1_Pos;
    YZF_MODIFY_REG(i2c->OAR1,I2C_OAR1_OA1EN,EnableCall,I2C_OAR1_OA1EN_Pos);
    return YZF_OK;
}

YZF_RESULT yzf_i2c_ack_enable(YZF_I2C_POINTER i2c){
    i2c->CR2 &= ~(0b1 << I2C_CR2_NACK_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_ack_disable(YZF_I2C_POINTER i2c){
    i2c->CR2 |= 0b1 << I2C_CR2_NACK_Pos;
    return YZF_OK;
}
//停止条件产生 记得取消ack
YZF_RESULT yzf_i2c_stop(YZF_I2C_POINTER i2c){
    i2c->CR2  |= 0b1 << I2C_CR2_STOP_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_enable_reload(YZF_I2C_POINTER i2c){
    i2c->CR2 |= 0b1 << I2C_CR2_RELOAD_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_disable_reload(YZF_I2C_POINTER i2c){
    i2c->CR2 &=~ (0b1 << I2C_CR2_RELOAD_Pos);
    return YZF_OK;
}
//禁止时钟延长（从模式）
YZF_RESULT yzf_i2c_disable_clock_stretching(YZF_I2C_POINTER i2c){
    i2c->CR1 &= ~(0b1 << I2C_CR1_NOSTRETCH_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_enable_autoEnd(YZF_I2C_POINTER i2c){
    i2c->CR2 |= 0b1 << I2C_CR2_AUTOEND_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_disable_autoEnd(YZF_I2C_POINTER i2c){
    i2c->CR2 &= ~(0b1 << I2C_CR2_AUTOEND_Pos);
    return YZF_OK;
}
//广播呼叫使能 响应地址00h
YZF_RESULT yzf_i2c_call_enable(YZF_I2C_POINTER i2c){
    i2c->CR1 |= 0b1 << I2C_CR1_GCEN_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_call_disable(YZF_I2C_POINTER i2c){
    i2c->CR1 &= ~(0b1 << I2C_CR1_GCEN_Pos);
    return YZF_OK;
}

YZF_RESULT yzf_i2c_mode_read(YZF_I2C_POINTER i2c){
    YZF_MODIFY_REG(i2c->CR2,I2C_CR2_RD_WRN,1,I2C_CR2_RD_WRN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_mode_write(YZF_I2C_POINTER i2c){
    YZF_MODIFY_REG(i2c->CR2,I2C_CR2_RD_WRN,0,I2C_CR2_RD_WRN_Pos);
    return YZF_OK;
}
//PEC使能
YZF_RESULT yzf_i2c_pec_enable(YZF_I2C_POINTER i2c){
    i2c->CR1 |= 0b1 << I2C_CR1_PECEN_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_pec_disable(YZF_I2C_POINTER i2c){
    i2c->CR1 &= ~(0b1 << I2C_CR1_PECEN_Pos);
    return YZF_OK;
}
//i2c使能
YZF_RESULT yzf_i2c_enable(YZF_I2C_POINTER i2c){
    i2c->CR1 |= 0b1 << I2C_CR1_PE_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_disable(YZF_I2C_POINTER i2c){
    i2c->CR1 &= ~(0b1 << I2C_CR1_PE_Pos);
    return YZF_OK;
}
//DMA请求使能
YZF_RESULT yzf_i2c_rx_dma_enable(YZF_I2C_POINTER i2c){
    i2c->CR1 |= 0b1 << I2C_CR1_RXDMAEN_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_rx_dma_disable(YZF_I2C_POINTER i2c){
    i2c->CR1 &= ~(0b1 << I2C_CR1_RXDMAEN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_tx_dma_enable(YZF_I2C_POINTER i2c){
    i2c->CR1 |= 0b1 << I2C_CR1_TXDMAEN_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_i2c_tx_dma_disable(YZF_I2C_POINTER i2c){
    i2c->CR1 &= ~(0b1 << I2C_CR1_TXDMAEN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_set_cnt(YZF_I2C_POINTER i2c,uint8_t cnt){
    YZF_MODIFY_REG(i2c->CR2,I2C_CR2_NBYTES,cnt,I2C_CR2_NBYTES_Pos);
    return YZF_OK;
}
//双地址使能 只限7为地址模式
YZF_RESULT yzf_i2c_address2_enable(YZF_I2C_POINTER i2c){
    YZF_MODIFY_REG(i2c->OAR2,I2C_OAR2_OA2EN,1,I2C_OAR2_OA2EN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_address2_disable(YZF_I2C_POINTER i2c){
    YZF_MODIFY_REG(i2c->OAR2,I2C_OAR2_OA2EN,0,I2C_OAR2_OA2EN_Pos);
    return YZF_OK;
}
//设置第二个地址
YZF_RESULT yzf_i2c_set_address2(YZF_I2C_POINTER i2c,uint8_t address){
    i2c->OAR2 &= ~(0b1111111 << 1);
    i2c->OAR2 |= address << 1;
    return YZF_OK;
}
//FLAG Timeout
YZF_BOOL yzf_i2c_flag_timeout(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_TIMEOUT_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//FLAG PECERR PEC错误
YZF_BOOL yzf_i2c_flag_PECERR(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_PECERR_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//FLAG OVR 过载或者欠载
YZF_BOOL yzf_i2c_flag_OVR(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_OVR_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//FLAG AF 应答失败
YZF_BOOL yzf_i2c_flag_AF(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_NACKF_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}

YZF_RESULT yzf_i2c_flag_clear_AF(YZF_I2C_POINTER i2c){
    i2c->ICR |= 0b1 << I2C_ICR_NACKCF_Pos;
    return YZF_OK;
}
//FLAG ARLO 应答丢失
YZF_BOOL yzf_i2c_flag_ARLO(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_ARLO_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//FLAG BERR 总线错误
YZF_BOOL yzf_i2c_flag_BERR(YZF_I2C_POINTER i2c){
    return (i2c->ISR  & (0b1 << I2C_ISR_BERR_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//FLAG TC 传输完成
YZF_BOOL yzf_i2c_flag_TxE(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_TXE_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
YZF_BOOL yzf_i2c_flag_TC(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_TC_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
YZF_BOOL yzf_i2c_flag_TxISE(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_TXIS_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//FLAG TB 传输完成
YZF_BOOL yzf_i2c_flag_RxNE(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_RXNE_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//停止条件检测为
YZF_BOOL yzf_i2c_flag_STOPF(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_STOPF_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
YZF_BOOL yzf_i2c_flag_clear_STOPF(YZF_I2C_POINTER i2c){
    i2c->ICR |= 0b1 << I2C_ICR_STOPCF_Pos;
    return YZF_TRUE;
}
//地址已发送/地址匹配
YZF_BOOL yzf_i2c_flag_ADDR(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_ADDR_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//总线繁忙
YZF_BOOL yzf_i2c_flag_BUSY(YZF_I2C_POINTER i2c){
    return (i2c->ISR & (0b1 << I2C_ISR_BUSY_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//分频系数
YZF_RESULT yzf_i2c_set_CCR(YZF_I2C_POINTER i2c,uint16_t ccr){
    YZF_MODIFY_REG(i2c->TIMINGR,I2C_TIMINGR_PRESC,ccr,I2C_TIMINGR_PRESC_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_data_set_time(YZF_I2C_POINTER i2c,uint16_t dataSetTime){
    YZF_MODIFY_REG(i2c->TIMINGR,I2C_TIMINGR_SCLDEL,dataSetTime,I2C_TIMINGR_SCLDEL_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_data_hold_time(YZF_I2C_POINTER i2c,uint16_t dataHoldTime){
    YZF_MODIFY_REG(i2c->TIMINGR,I2C_TIMINGR_SDADEL,dataHoldTime,I2C_TIMINGR_SDADEL_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_high_time(YZF_I2C_POINTER i2c,uint16_t highTime){
    YZF_MODIFY_REG(i2c->TIMINGR,I2C_TIMINGR_SCLH,highTime,I2C_TIMINGR_SCLH_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_i2c_low_time(YZF_I2C_POINTER i2c,uint16_t lowTime){
    YZF_MODIFY_REG(i2c->TIMINGR,I2C_TIMINGR_SCLL,lowTime,I2C_TIMINGR_SCLL_Pos);
    return YZF_OK;
}