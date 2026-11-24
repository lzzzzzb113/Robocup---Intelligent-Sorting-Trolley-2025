//
// Created by 32827 on 2023/11/29.
//

#ifndef YZFRAME_YZ_SPI_H
#define YZFRAME_YZ_SPI_H
#include "yzf_spi.h"
#include "yzf_global_sheet.h"
#include "yzf_dma.h"
/**
 * spi dma tx传输
 *
 * @param spi SPI1,SPI2...
 * @param dma DMA1,DMA2...
 * @param channel DMA1_Stream0,DMA1_Stream1...
 * @param channel_id DMA1_StreamX,this is X.
 * @param dmaMuxChannel DMAMUX1_ChannelX, This X is same for params channel_id.
 * @param dmaMuxStatus DMAMUX1_ChannelStatus, DMAMUX2_ChannelStatus.
 * @param muxReqId DMA Mux selected ID. range in 1-115
 * @param data send data pointer
 * @param len The length of send data
 *
 * @return YZF_OK or YZF_ERROR
 * */
YZF_RESULT yz_spi_transmit_full_lines_dma(YZF_SPI_POINTER spi,YZF_DMA_POINTER dma,YZF_DMA_CHANNEL_POINTER channel,
                                          uint8_t channel_id,YZF_DMAMUX_CHANNEL_POINTER dmaMuxChannel,
                                          YZF_DMAMUX_STATUS_POINTER dmaMuxStatus,uint8_t muxReqId,uint8_t *data,uint16_t len);

/**
 * spi 双线传输 初始化
 *
 * @param spi SPI1,SPI2...
 * @param br  YZF_SPI_BR 分频
 * @param fifoThreshold level 0-15(+1)
 * @param dataSize 3-31(+1)
 * @param cpol_high 高
 * @param cpha_sec 二次
 * @param master 主
 * @param msb 先发送高位
 *
 * @return YZF_OK or YZF_ERROR
 * */
YZF_RESULT yz_spi_full_lines_init(YZF_SPI_POINTER spi,YZF_SPI_BR br,uint8_t fifoThreshold,
                                  uint8_t dataSize,YZF_BOOL cpol_high,YZF_BOOL cpha_sec,YZF_BOOL master,
                                  YZF_BOOL msb);
/**
 * spi 半双工 初始化
 *
 * @param spi SPI1,SPI2...
 * @param br  YZF_SPI_BR 分频
 * @param fifoThreshold level 0-15(+1)
 * @param dataSize 3-31(+1)
 * @param cpol_high 高
 * @param cpha_sec 二次
 * @param master 主
 * @param msb 先发送高位
 * @param isTx 是否为发送模式
 *
 * @return YZF_OK or YZF_ERROR
 * */
YZF_RESULT yz_spi_bidi_init(YZF_SPI_POINTER spi,YZF_SPI_BR br,uint8_t fifoThreshold,
                                  uint8_t dataSize,YZF_BOOL cpol_high,YZF_BOOL cpha_sec,YZF_BOOL master,
                                  YZF_BOOL msb,YZF_BOOL isTx);
/**
 * spi 双线传输开始
 * */
YZF_RESULT yz_spi_full_lines_begin(YZF_SPI_POINTER spi);
/**
 * spi 双线传输结束
 * */
YZF_RESULT yz_spi_full_lines_end(YZF_SPI_POINTER spi);
/**
 * spi 双线传输数据
 *
 * @param spi SPI1,SPI2...
 * @param data 8bits
 *
 * @return 8bits
 * */
uint8_t yz_spi_full_lines_conv8(YZF_SPI_POINTER spi,uint8_t data);
/**
 * spi 双线传输数据
 *
 * @param spi SPI1,SPI2...
 * @param data 16bits
 *
 * @return 16bits
 * */
uint16_t yz_spi_full_lines_conv16(YZF_SPI_POINTER spi,uint16_t data);
/**
 * 半双线发送
 * */
YZF_RESULT yz_spi_bidi_transmit(YZF_SPI_POINTER spi,uint8_t *data,uint16_t len);
#endif //YZFRAME_YZ_SPI_H
