//
// Created by 32827 on 2023/11/25.
//

#ifndef YZF_DMA_H
#define YZF_DMA_H
#include "yzf.h"

#ifdef __cplusplus
extern "C" {
#endif

enum YZF_DMA_PRIOR{
    YZF_DMA_LOW=0b00,
    YZF_DMA_MIDDLE=0b01,
    YZF_DMA_HIGH=0b10,
    YZF_DMA_MOST=0b11
};
enum YZF_DMA_SIZE{
    YZF_DMA_BYTE=0b00,
    YZF_DMA_HALF_WORD=0b01,
    YZF_DMA_WORD=0b10,
};
enum YZF_DMA_BURST{
    YZF_DMA_BURST_1=0b00,
    YZF_DMA_BURST_4=0b01,
    YZF_DMA_BURST_8=0b10,
    YZF_DMA_BURST_16=0b11
};
typedef enum YZF_DMA_PRIOR YZF_DMA_PRIORITY;
typedef enum YZF_DMA_SIZE YZF_DMA_SIZE;
typedef enum YZF_DMA_BURST YZF_DMA_BURST;
/**
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_clock_enable(YZF_DMA_POINTER dma);

/**
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_clock_disable(YZF_DMA_POINTER dma);

/**
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_fifo_mburst(YZF_DMA_CHANNEL_POINTER channel,YZF_DMA_BURST burst);

/**
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_fifo_pburst(YZF_DMA_CHANNEL_POINTER channel,YZF_DMA_BURST burst);

/**
 * @description: 获取当前传输的缓冲区
 *
 * @return 0 当前使用DMA_SxM0AR 1 当前使用DMA_SxM1AR
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_dma_current_buf(YZF_DMA_CHANNEL_POINTER channel);

/**
 * @description: 启用双缓冲区
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_double_buf_enable(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL isEnable);


/**
 * @description: 设置通道优先级
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_set_priority(YZF_DMA_CHANNEL_POINTER channel,YZF_DMA_PRIORITY priority);

/**
 * @description: 存储器数据宽度
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mem_size(YZF_DMA_CHANNEL_POINTER channel,YZF_DMA_SIZE size);

/**
 * @description: 设备数据宽度
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_per_size(YZF_DMA_CHANNEL_POINTER channel,YZF_DMA_SIZE size);

/**
 * @description: 内存自动递增
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mode_mem_inc(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL enable);

/**
 * @description: 外设自动递增
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mode_per_inc(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL enable);

/**
 * @description: 循环模式
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mode_circular(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL enable);

/**
 * @description: 存储器到存储器
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mode_mem_mem(YZF_DMA_CHANNEL_POINTER channel);

/**
 * @description: 非外设到存储器
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mode_per_mem(YZF_DMA_CHANNEL_POINTER channel);

/**
 * @description: 存储器到外设
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mode_mem_per(YZF_DMA_CHANNEL_POINTER channel);

/**
 * @description: 设备地址
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_per_address(YZF_DMA_CHANNEL_POINTER channel,uint32_t address);

/**
 * @description: 内存地址0
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mem0_address(YZF_DMA_CHANNEL_POINTER channel,uint32_t address);

/**
 * @description: 内存地址1
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_mem1_address(YZF_DMA_CHANNEL_POINTER channel,uint32_t address);

/**
 * @description: 传输错误中断
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_interrupt_TE(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL enable);

/**
 * @description: 传输完成中断
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_interrupt_TC(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL enable);

/**
 * @description: 半传输完成中断
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_interrupt_HT(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL enable);

/**
 * @description: DME中断
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_interrupt_DME(YZF_DMA_CHANNEL_POINTER channel,YZF_BOOL enable);

/**
 * @description: 传输错误标志清除
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_clear_flag_TEIF(YZF_DMA_POINTER dma,uint8_t channel);

/**
 * @description: 半传输完成标志清除
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_clear_flag_HTIF(YZF_DMA_POINTER dma,uint8_t channel);

/**
 * @description: 传输完成标志清除
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_clear_flag_TCIF(YZF_DMA_POINTER dma,uint8_t channel);

/**
 * @description: 直接传输错误标志清除
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_clear_flag_DMEIF(YZF_DMA_POINTER dma,uint8_t channel);

/**
 * @description: 全部标志清除
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_clear_all_flag(YZF_DMA_POINTER dma,uint8_t channel);

/**
 * @description: 传输错误标志
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_dma_flag_TE(YZF_DMA_POINTER dma,uint8_t channel);

/**
 * @description: 半传输标志
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_dma_flag_HT(YZF_DMA_POINTER dma,uint8_t channel);

/**
 * @description: 传输完成标志
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_dma_flag_TC(YZF_DMA_POINTER dma,uint8_t channel);


/**
 * @description: 直接传输错误标志
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_dma_flag_DME(YZF_DMA_POINTER dma,uint8_t channel);

/**
 * @description: 开始DMA
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_enable(YZF_DMA_CHANNEL_POINTER channel);

/**
 * @description: 停止DMA
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_disable(YZF_DMA_CHANNEL_POINTER channel);

/**
 * @description: 是否停止标志
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_dma_isDisable(YZF_DMA_CHANNEL_POINTER channel);

/**
 * @description 传输数量
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_dma_transmit_count(YZF_DMA_CHANNEL_POINTER channel,uint16_t count);

#ifdef __cplusplus
}
#endif
#endif //YZFRAME_YZF_DMA_H
