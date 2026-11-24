//
// Created by 32827 on 2023/11/25.
//

#ifndef YZFRAME_YZ_DMA_H
#define YZFRAME_YZ_DMA_H
#include "yz.h"
#include "yzf_dma.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 *  @Note 大小: 0b00 Bit8 0b01 Bit16 0b10 Bit32<br>
 *  优先级: 0b00低 0b01中 0b10高 0b11极高s<br>
 *  @param dma 使用的dma
 *  @param channel 使用的通道
 *  @param src 源地址
 *  @param dest 目的地址
 *  @param s_src 源地址大小
 *  @param s_dest 目的地址大小
 *  @param i_src 源地址是否递增
 *  @param i_dest 目的地址是否递增
 *  @param size 传输大小
 *  @param isCir 是否循环
 *  @param TCI 传输完成中断
 *  @param HTI 半传输完成中断
 *  @param TEI 传输错误中断
 *  @param priority 通道优先级
 * */
void yz_dma_mem_2_per(YZF_DMA_POINTER dma,YZF_DMA_CHANNEL_POINTER channel,void *src,void *dest,
                      YZF_DMA_SIZE s_src,YZF_DMA_SIZE s_dest,YZF_BOOL i_src,YZF_BOOL i_dest,uint16_t size,
                      YZF_BOOL isCir,YZF_BOOL TCI,YZF_BOOL HTI,YZF_BOOL TEI,YZF_DMA_PRIORITY priority);
void yz_dma_mem_2_mem(YZF_DMA_POINTER dma,YZF_DMA_CHANNEL_POINTER channel,void *src,void *dest,
                      YZF_DMA_SIZE s_src,YZF_DMA_SIZE s_dest,YZF_BOOL i_src,YZF_BOOL i_dest,uint16_t size,
                      YZF_BOOL isCir,YZF_BOOL TCI,YZF_BOOL HTI,YZF_BOOL TEI,YZF_DMA_PRIORITY priority);

#ifdef __cplusplus
}
#endif
#endif //YZFRAME_YZ_DMA_H
