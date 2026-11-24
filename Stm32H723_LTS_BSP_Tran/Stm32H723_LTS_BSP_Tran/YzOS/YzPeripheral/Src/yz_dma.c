//
// Created by 32827 on 2023/11/25.
//
#include "yz_dma.h"

void yz_dma_mem_2_per(YZF_DMA_POINTER dma,YZF_DMA_CHANNEL_POINTER channel,void *src,void *dest,
                      YZF_DMA_SIZE s_src,YZF_DMA_SIZE s_dest,YZF_BOOL i_src,YZF_BOOL i_dest,uint16_t size,
                      YZF_BOOL isCir,YZF_BOOL TCI,YZF_BOOL HTI,YZF_BOOL TEI,YZF_DMA_PRIORITY priority){
    //设置传输
    yzf_dma_clock_enable(dma);
    yzf_dma_mode_mem_per(channel);
//    yzf_dma_mode_mem_read(channel);
    yzf_dma_transmit_count(channel,size);
    yzf_dma_mode_circular(channel,isCir);
    yzf_dma_set_priority(channel,priority);

    yzf_dma_interrupt_HT(channel,HTI);
    yzf_dma_interrupt_TC(channel,TCI);
    yzf_dma_interrupt_TE(channel,TEI);

    //设置源
    yzf_dma_mem0_address(channel,(uint32_t)src);
    yzf_dma_mode_mem_inc(channel,i_src);
    yzf_dma_mem_size(channel,s_src);

    //设置目标
    yzf_dma_per_address(channel,(uint32_t)dest);
    yzf_dma_mode_per_inc(channel,i_dest);
    yzf_dma_per_size(channel,s_dest);

    yzf_dma_enable(channel);
}
void yz_dma_mem_2_mem(YZF_DMA_POINTER dma,YZF_DMA_CHANNEL_POINTER channel,void *src,void *dest,
                      YZF_DMA_SIZE s_src,YZF_DMA_SIZE s_dest,YZF_BOOL i_src,YZF_BOOL i_dest,uint16_t size,
                      YZF_BOOL isCir,YZF_BOOL TCI,YZF_BOOL HTI,YZF_BOOL TEI,YZF_DMA_PRIORITY priority){
    //设置传输
    YZF_CHECK_RETURN(yzf_dma_clock_enable(dma))

    YZF_CHECK_RETURN(yzf_dma_per_address(channel,(uint32_t)src))
    YZF_CHECK_RETURN(yzf_dma_mem0_address(channel,(uint32_t)dest))
    YZF_CHECK_RETURN(yzf_dma_transmit_count(channel,size))
    YZF_CHECK_RETURN(yzf_dma_set_priority(channel,priority))
//    YZF_CHECK_RETURN(yzf_dma_mode_mem_read(channel))
    YZF_CHECK_RETURN(yzf_dma_mode_circular(channel,isCir))
    YZF_CHECK_RETURN(yzf_dma_mode_per_inc(channel,i_dest))
    YZF_CHECK_RETURN(yzf_dma_mode_mem_inc(channel,i_src))
    YZF_CHECK_RETURN(yzf_dma_per_size(channel,s_src))
    YZF_CHECK_RETURN(yzf_dma_mem_size(channel,s_dest))
    YZF_CHECK_RETURN(yzf_dma_mode_mem_mem(channel))

    YZF_CHECK_RETURN(yzf_dma_interrupt_HT(channel,HTI))
    YZF_CHECK_RETURN(yzf_dma_interrupt_TC(channel,TCI))
    YZF_CHECK_RETURN(yzf_dma_interrupt_TE(channel,TEI))

    yzf_dma_enable(channel);
}