//
// Created by 32827 on 2023/11/25.
//
#include "yzf_dma.h"
//传输错误标志
YZF_RESULT yzf_dma_clear_all_flag(YZF_DMA_POINTER dma,uint8_t channel){
    if(channel<4){
        dma->LIFCR=0xFF << (channel)*8;
    }else{
        dma->HIFCR=0xFF << (channel-4)*8;
    }
    return YZF_OK;
}
YZF_BOOL yzf_dma_flag_TE(YZF_DMA_POINTER dma,uint8_t channel){
    switch (channel) {
        case 0:
            return ((dma->LISR & (0b1 << DMA_LISR_TEIF0_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 1:
            return ((dma->LISR & (0b1 << DMA_LISR_TEIF1_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 2:
            return ((dma->LISR & (0b1 << DMA_LISR_TEIF2_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 3:
            return ((dma->LISR & (0b1 << DMA_LISR_TEIF3_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 4:
            return ((dma->HISR & (0b1 << DMA_HISR_TEIF4_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 5:
            return ((dma->HISR & (0b1 << DMA_HISR_TEIF5_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 6:
            return ((dma->HISR & (0b1 << DMA_HISR_TEIF6_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 7:
            return ((dma->HISR & (0b1 << DMA_HISR_TEIF7_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        default:
            return YZF_FALSE;
    }
}
//半传输标志
YZF_BOOL yzf_dma_flag_HT(YZF_DMA_POINTER dma,uint8_t channel){
    switch (channel) {
        case 0:
            return ((dma->LISR & (0b1 << DMA_LISR_HTIF0_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 1:
            return ((dma->LISR & (0b1 << DMA_LISR_HTIF1_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 2:
            return ((dma->LISR & (0b1 << DMA_LISR_HTIF2_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 3:
            return ((dma->LISR & (0b1 << DMA_LISR_HTIF3_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 4:
            return ((dma->HISR & (0b1 << DMA_HISR_HTIF4_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 5:
            return ((dma->HISR & (0b1 << DMA_HISR_HTIF5_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 6:
            return ((dma->HISR & (0b1 << DMA_HISR_HTIF6_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 7:
            return ((dma->HISR & (0b1 << DMA_HISR_HTIF7_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        default:
            return YZF_FALSE;
    }
}
//传输完成标志
YZF_BOOL yzf_dma_flag_TC(YZF_DMA_POINTER dma,uint8_t channel){
    switch (channel) {
        case 0:
            return ((dma->LISR & (0b1 << DMA_LISR_TCIF0_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 1:
            return ((dma->LISR & (0b1 << DMA_LISR_TCIF1_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 2:
            return ((dma->LISR & (0b1 << DMA_LISR_TCIF2_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 3:
            return ((dma->LISR & (0b1 << DMA_LISR_TCIF3_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 4:
            return ((dma->HISR & (0b1 << DMA_HISR_TCIF4_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 5:
            return ((dma->HISR & (0b1 << DMA_HISR_TCIF5_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 6:
            return ((dma->HISR & (0b1 << DMA_HISR_TCIF6_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 7:
            return ((dma->HISR & (0b1 << DMA_HISR_TCIF7_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        default:
            return YZF_FALSE;
    }
}
//全局中断标志
YZF_BOOL yzf_dma_flag_DME(YZF_DMA_POINTER dma,uint8_t channel){
    switch (channel) {
        case 0:
            return ((dma->LISR & (0b1 << DMA_LISR_DMEIF0_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 1:
            return ((dma->LISR & (0b1 << DMA_LISR_DMEIF1_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 2:
            return ((dma->LISR & (0b1 << DMA_LISR_DMEIF2_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 3:
            return ((dma->LISR & (0b1 << DMA_LISR_DMEIF3_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 4:
            return ((dma->HISR & (0b1 << DMA_HISR_DMEIF4_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 5:
            return ((dma->HISR & (0b1 << DMA_HISR_DMEIF5_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 6:
            return ((dma->HISR & (0b1 << DMA_HISR_DMEIF6_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        case 7:
            return ((dma->HISR & (0b1 << DMA_HISR_DMEIF7_Pos)) == 0) ? YZF_FALSE : YZF_TRUE;
        default:
            return YZF_FALSE;
    }
}
//传输错误标志清除
YZF_RESULT yzf_dma_clear_flag_TEIF(YZF_DMA_POINTER dma,uint8_t channel){
    switch (channel) {
        case 0:
            dma->LIFCR = (0b1 << DMA_LIFCR_CTEIF0_Pos);
            break;
        case 1:
            dma->LIFCR = (0b1 << DMA_LIFCR_CTEIF1_Pos);
            break;
        case 2:
            dma->LIFCR = (0b1 << DMA_LIFCR_CTEIF2_Pos);
            break;
        case 3:
            dma->LIFCR = (0b1 << DMA_LIFCR_CTEIF3_Pos);
            break;
        case 4:
            dma->HIFCR = (0b1 << DMA_HIFCR_CTEIF4_Pos);
            break;
        case 5:
            dma->HIFCR = (0b1 << DMA_HIFCR_CTEIF5_Pos);
            break;
        case 6:
            dma->HIFCR = (0b1 << DMA_HIFCR_CTEIF6_Pos);
            break;
        case 7:
            dma->HIFCR = (0b1 << DMA_HIFCR_CTEIF7_Pos);
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}
//半传输标志清除
YZF_RESULT yzf_dma_clear_flag_HTIF(YZF_DMA_POINTER dma,uint8_t channel){
    switch (channel) {
        case 0:
            dma->LIFCR = (0b1 << DMA_LIFCR_CHTIF0_Pos);
            break;
        case 1:
            dma->LIFCR = (0b1 << DMA_LIFCR_CHTIF1_Pos);
            break;
        case 2:
            dma->LIFCR = (0b1 << DMA_LIFCR_CHTIF2_Pos);
            break;
        case 3:
            dma->LIFCR = (0b1 << DMA_LIFCR_CHTIF3_Pos);
            break;
        case 4:
            dma->HIFCR = (0b1 << DMA_HIFCR_CHTIF4_Pos);
            break;
        case 5:
            dma->HIFCR = (0b1 << DMA_HIFCR_CHTIF5_Pos);
            break;
        case 6:
            dma->HIFCR = (0b1 << DMA_HIFCR_CHTIF6_Pos);
            break;
        case 7:
            dma->HIFCR = (0b1 << DMA_HIFCR_CHTIF7_Pos);
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}
//传输完成标志清除
YZF_RESULT yzf_dma_clear_flag_TCIF(YZF_DMA_POINTER dma,uint8_t channel){
    switch (channel) {
        case 0:
            dma->LIFCR = (0b1 << DMA_LIFCR_CTCIF0_Pos);
            break;
        case 1:
            dma->LIFCR = (0b1 << DMA_LIFCR_CTCIF1_Pos);
            break;
        case 2:
            dma->LIFCR = (0b1 << DMA_LIFCR_CTCIF2_Pos);
            break;
        case 3:
            dma->LIFCR = (0b1 << DMA_LIFCR_CTCIF3_Pos);
            break;
        case 4:
            dma->HIFCR = (0b1 << DMA_HIFCR_CTCIF4_Pos);
            break;
        case 5:
            dma->HIFCR = (0b1 << DMA_HIFCR_CTCIF5_Pos);
            break;
        case 6:
            dma->HIFCR = (0b1 << DMA_HIFCR_CTCIF6_Pos);
            break;
        case 7:
            dma->HIFCR = (0b1 << DMA_HIFCR_CTCIF7_Pos);
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}
//全局中断标志清除
YZF_RESULT yzf_dma_clear_flag_DMEIF(YZF_DMA_POINTER dma,uint8_t channel){
    switch (channel) {
        case 0:
            dma->LIFCR = (0b1 << DMA_LIFCR_CDMEIF0_Pos);
            break;
        case 1:
            dma->LIFCR = (0b1 << DMA_LIFCR_CDMEIF1_Pos);
            break;
        case 2:
            dma->LIFCR = (0b1 << DMA_LIFCR_CDMEIF2_Pos);
            break;
        case 3:
            dma->LIFCR = (0b1 << DMA_LIFCR_CDMEIF3_Pos);
            break;
        case 4:
            dma->HIFCR = (0b1 << DMA_HIFCR_CDMEIF4_Pos);
            break;
        case 5:
            dma->HIFCR = (0b1 << DMA_HIFCR_CDMEIF5_Pos);
            break;
        case 6:
            dma->HIFCR = (0b1 << DMA_HIFCR_CDMEIF6_Pos);
            break;
        case 7:
            dma->HIFCR = (0b1 << DMA_HIFCR_CDMEIF7_Pos);
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}

//存储器到存储器
YZF_RESULT yzf_dma_mode_mem_mem(YZF_DMA_CHANNEL_POINTER channel){
    YZF_MODIFY_REG(channel->CR, DMA_SxCR_DIR, 0b10,DMA_SxCR_DIR_Pos);
    return YZF_OK;
}
//非存储器到存储器
YZF_RESULT yzf_dma_mode_per_mem(YZF_DMA_CHANNEL_POINTER channel){
    YZF_MODIFY_REG(channel->CR, DMA_SxCR_DIR, 0b00,DMA_SxCR_DIR_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_dma_mode_mem_per(YZF_DMA_CHANNEL_POINTER channel){
    YZF_MODIFY_REG(channel->CR, DMA_SxCR_DIR, 0b01,DMA_SxCR_DIR_Pos);
    return YZF_OK;
}

//设置通道优先级
YZF_RESULT yzf_dma_set_priority(YZF_DMA_CHANNEL_POINTER dma,YZF_DMA_PRIORITY priority){
    dma->CR &= ~(0b11 << DMA_SxCR_PL_Pos);
    dma->CR |= priority << DMA_SxCR_PL_Pos;
    return YZF_OK;
}

//存储器数据宽度
YZF_RESULT yzf_dma_mem_size(YZF_DMA_CHANNEL_POINTER dma,YZF_DMA_SIZE size){
    dma->CR &= ~(0b11 << DMA_SxCR_MSIZE_Pos);
    dma->CR |= size << DMA_SxCR_MSIZE_Pos;
    return YZF_OK;
}
//设备数据宽度
YZF_RESULT yzf_dma_per_size(YZF_DMA_CHANNEL_POINTER dma,YZF_DMA_SIZE size){
    dma->CR &= ~(0b11 << DMA_SxCR_PSIZE_Pos);
    dma->CR |= size << DMA_SxCR_PSIZE_Pos;
    return YZF_OK;
}

//内存是否递增
YZF_RESULT yzf_dma_mode_mem_inc(YZF_DMA_CHANNEL_POINTER dma,YZF_BOOL enable){
    dma->CR &= ~(0b1 << DMA_SxCR_MINC_Pos);
    dma->CR |= enable << DMA_SxCR_MINC_Pos;
    return YZF_OK;
}
//设备是否递增
YZF_RESULT yzf_dma_mode_per_inc(YZF_DMA_CHANNEL_POINTER dma,YZF_BOOL enable){
    dma->CR &= ~(0b1 << DMA_SxCR_PINC_Pos);
    dma->CR |= enable << DMA_SxCR_PINC_Pos;
    return YZF_OK;
}

//循环接收
YZF_RESULT yzf_dma_mode_circular(YZF_DMA_CHANNEL_POINTER dma,YZF_BOOL enable){
    dma->CR &= ~(0b1 << DMA_SxCR_CIRC_Pos);
    dma->CR |= enable << DMA_SxCR_CIRC_Pos;
    return YZF_OK;
}

//传输错误中断
YZF_RESULT yzf_dma_interrupt_TE(YZF_DMA_CHANNEL_POINTER dma,YZF_BOOL enable){
    dma->CR &= ~(0b1 << DMA_SxCR_TEIE_Pos);
    dma->CR |= enable << DMA_SxCR_TEIE_Pos;
    return YZF_OK;
}
//传输完成中断
YZF_RESULT yzf_dma_interrupt_TC(YZF_DMA_CHANNEL_POINTER dma,YZF_BOOL enable){
    dma->CR &= ~(0b1 << DMA_SxCR_TCIE_Pos);
    dma->CR |= enable << DMA_SxCR_TCIE_Pos;
    return YZF_OK;
}
//半传输中断
YZF_RESULT yzf_dma_interrupt_HT(YZF_DMA_CHANNEL_POINTER dma,YZF_BOOL enable){
    dma->CR &= ~(0b1 << DMA_SxCR_HTIE_Pos);
    dma->CR |= enable << DMA_SxCR_HTIE_Pos;
    return YZF_OK;
}
//直接传输错误中断
YZF_RESULT yzf_dma_interrupt_DME(YZF_DMA_CHANNEL_POINTER dma,YZF_BOOL enable){
    dma->CR &= ~(0b1 << DMA_SxCR_DMEIE_Pos);
    dma->CR |= enable << DMA_SxCR_DMEIE_Pos;
    return YZF_OK;
}

YZF_RESULT yzf_dma_enable(YZF_DMA_CHANNEL_POINTER dma){
    dma->CR |= 0b1 << DMA_SxCR_EN_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_dma_disable(YZF_DMA_CHANNEL_POINTER dma){
    dma->CR &= ~(0b1 << DMA_SxCR_EN_Pos);
    return YZF_OK;
}
YZF_BOOL yzf_dma_isDisable(YZF_DMA_CHANNEL_POINTER channel){
    return (channel->CR & (0b1 << DMA_SxCR_EN_Pos)) ? YZF_FALSE : YZF_TRUE;
}

YZF_RESULT yzf_dma_transmit_count(YZF_DMA_CHANNEL_POINTER dma,uint16_t count){
    YZF_MODIFY_REG(dma->NDTR,DMA_SxNDT,count,DMA_SxNDT_Pos);
    return YZF_OK;
}
//设备地址
YZF_RESULT yzf_dma_per_address(YZF_DMA_CHANNEL_POINTER dma,uint32_t address){
    YZF_MODIFY_REG(dma->PAR,DMA_SxPAR_PA,address,DMA_SxPAR_PA_Pos);
    return YZF_OK;
}
//内存地址
YZF_RESULT yzf_dma_mem0_address(YZF_DMA_CHANNEL_POINTER dma,uint32_t address){
    YZF_MODIFY_REG(dma->M0AR,DMA_SxM0AR_M0A,address,DMA_SxM0AR_M0A_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_dma_mem1_address(YZF_DMA_CHANNEL_POINTER dma,uint32_t address){
    YZF_MODIFY_REG(dma->M1AR,DMA_SxM1AR_M1A,address,DMA_SxM1AR_M1A_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_dma_clock_enable(YZF_DMA_POINTER dma){
    switch ((uint32_t)dma) {
        case (uint32_t)DMA1:
            RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
            break;
        case (uint32_t)DMA2:
            RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}
YZF_RESULT yzf_dma_clock_disable(YZF_DMA_POINTER dma){
    switch ((uint32_t)dma) {
        case (uint32_t)DMA1:
            RCC->AHB1ENR&= ~RCC_AHB1ENR_DMA1EN;
            break;
        case (uint32_t)DMA2:
            RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2EN;
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}

YZF_RESULT yzf_dma_fifo_mburst(YZF_DMA_CHANNEL_POINTER channel,YZF_DMA_BURST burst){
    YZF_MODIFY_REG(channel->CR,DMA_SxCR_MBURST,burst,DMA_SxCR_MBURST_Pos);
    return YZF_OK;
}

YZF_RESULT yzf_dma_fifo_pburst(YZF_DMA_CHANNEL_POINTER channel,YZF_DMA_BURST burst){
    YZF_MODIFY_REG(channel->CR,DMA_SxCR_PBURST,burst,DMA_SxCR_PBURST_Pos);
    return YZF_OK;
}
YZF_BOOL yzf_dma_current_buf(YZF_DMA_CHANNEL_POINTER channel){
    return (channel->CR & (0b1 << DMA_SxCR_CT_Pos)) ? YZF_TRUE : YZF_FALSE;
}
YZF_RESULT yzf_dma_double_buf_enable(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL isEnable){
    YZF_MODIFY_REG(channel->CR,DMA_SxCR_DBM,isEnable,DMA_SxCR_DBM_Pos);
    return YZF_OK;
}