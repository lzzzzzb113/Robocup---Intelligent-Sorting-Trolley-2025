//
// Created by 32827 on 2023/11/29.
//

#ifndef YZF_SPI_H
#define YZF_SPI_H
#include "yzf.h"

enum YZF_SPI_BR{
    YZF_SPI_PLCK_2=0,
    YZF_SPI_PLCK_4=1,
    YZF_SPI_PLCK_8=2,
    YZF_SPI_PLCK_16=3,
    YZF_SPI_PLCK_32=4,
    YZF_SPI_PLCK_64=5,
    YZF_SPI_PLCK_128=6,
    YZF_SPI_PLCK_256=7
};
typedef enum YZF_SPI_BR YZF_SPI_BR;


/**
 * enable内部ssi选择
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_select_ssi(YZF_SPI_POINTER spi);

/**
 * disable内部ssi选择
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disSelect_ssi(YZF_SPI_POINTER spi);

/**
 * 内部ssi状态
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL  yzf_spi_ssi_status(YZF_SPI_POINTER spi);

/**
 * 时钟开关
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_open_source_clock(YZF_SPI_POINTER spi);

/**
 * 单线发送使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_BIDIO(YZF_SPI_POINTER spi);

/**
 * 单线接收使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_BIDIO(YZF_SPI_POINTER spi);

/**
 * Master传输预停止
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_tran_stop(YZF_SPI_POINTER spi);

/**
 * Master传输开始
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_tran_start(YZF_SPI_POINTER spi);

/**
 * spi使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable(YZF_SPI_POINTER spi);

/**
 * spi关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable(YZF_SPI_POINTER spi);

/**
 * spi是否使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL  yzf_spi_is_enabled(YZF_SPI_POINTER spi);

/**
 * spi传输数量
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_tran_count(YZF_SPI_POINTER spi,uint32_t size);

/**
 * spi传输速率
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_br(YZF_SPI_POINTER spi,YZF_SPI_BR br);

/**
 * 硬件CRC使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_crc_enable(YZF_SPI_POINTER spi);

/**
 * 硬件CRC失效
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_crc_disable(YZF_SPI_POINTER spi);

/**
 * 硬件CRC数据大小
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_crc_data_size(YZF_SPI_POINTER spi,uint8_t datSize);

/**
 * DMA发送使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_tx_dma(YZF_SPI_POINTER spi);

/**
 * DMA发送关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_tx_dma(YZF_SPI_POINTER spi);

/**
 * DMA接收使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_rx_dma(YZF_SPI_POINTER spi);

/**
 * DMA接收关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_rx_dma(YZF_SPI_POINTER spi);

/**
 * spi fifo阈值设置
 *
 * @param level 0-15(+1)
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_fifo_threshold_level(YZF_SPI_POINTER spi,uint8_t level);

/**
 * 8位数据帧
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_DFF_8bits(YZF_SPI_POINTER spi);

/**
 * 16位数据帧
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_DFF_16bits(YZF_SPI_POINTER spi);

/**
 * 设置数据帧大小
 *
 * @param datSize 3-31(+1)
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_DFF_bits(YZF_SPI_POINTER spi,uint8_t datSize);

/**
 * 软件ssm管理使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_ssm(YZF_SPI_POINTER spi);

/**
 * 软件ssm管理关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_ssm(YZF_SPI_POINTER spi);

/**
 * 主sso输出使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_sso(YZF_SPI_POINTER spi);

/**
 * 主sso输出关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_sso(YZF_SPI_POINTER spi);

/**
 * 时钟极性置1，时钟空闲为高电平
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_cpol_HIGH(YZF_SPI_POINTER spi);

/**
 * 时钟极性清0，时钟空闲为低电平
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_cpol_LOW(YZF_SPI_POINTER spi);

/**
 * 时钟相位置1 在第二个边沿采样
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_cpha_second(YZF_SPI_POINTER spi);
/**
 * 时钟相位清0 在第一个边沿采样
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_cpha_first(YZF_SPI_POINTER spi);

/**
 * 数据高有效位先
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_MSBFIRST(YZF_SPI_POINTER spi);

/**
 * 数据低有效位先
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_LSBFIRST(YZF_SPI_POINTER spi);

/**
 * 主模式
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_master(YZF_SPI_POINTER spi);

/**
 * 从模式
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_slave(YZF_SPI_POINTER spi);

/**
 * 发送完成中断使能 EOT/SUSP/TXC
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_txe_interrupt(YZF_SPI_POINTER spi);

/**
 * 发送完成中断关闭 EOT/SUSP/TXC
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_txe_interrupt(YZF_SPI_POINTER spi);

/**
 * 发送完成(TXC)flag获取
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_spi_flag_txe(YZF_SPI_POINTER spi);

/**
 * 接收不为空中断使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_rxne_interrupt(YZF_SPI_POINTER spi);

/**
 * 接收不为空中断关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_rxne_interrupt(YZF_SPI_POINTER spi);

/**
 * 接收不为空中断flag获取
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_spi_flag_rxne(YZF_SPI_POINTER spi);

/**
 * 模式错误中断使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_err_interrupt(YZF_SPI_POINTER spi);

/**
 * 模式错误中断关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_err_interrupt(YZF_SPI_POINTER spi);

/**
 * 写入数据 会清除TXE位 8位
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_write_byte(YZF_SPI_POINTER spi,uint8_t byte);

/**
 * 写入数据 会清除TXE位 16位
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_write_word(YZF_SPI_POINTER spi,uint16_t word);

/**
 * 写入数据 会清除TXE位 32位
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_write_double_word(YZF_SPI_POINTER spi,uint32_t doubleWord);

/**
 * 读取数据 会清除RxNE位 8位
 *
 * @CheckPlatform STM32H723
 * */
uint8_t yzf_spi_read_byte(YZF_SPI_POINTER spi);

/**
 * 读取数据 会清除RxNE位 16位
 *
 * @CheckPlatform STM32H723
 * */
uint16_t yzf_spi_read_word(YZF_SPI_POINTER spi);

/**
 * 读取数据 会清除RxNE位 32位
 *
 * @CheckPlatform STM32H723
 * */
uint32_t yzf_spi_read_double_word(YZF_SPI_POINTER spi);

/**
 * CRC 公式设置
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_crc_poly(YZF_SPI_POINTER spi,uint16_t poly);

/**
 * CRC 计算值获取
 *
 * @CheckPlatform STM32H723
 * */
uint16_t yzf_spi_get_crc_rx(YZF_SPI_POINTER spi);

/**
 * CRC 计算值设置
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_set_crc_tx(YZF_SPI_POINTER spi,uint16_t crc);

/**
 * 半双工使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_BIDI(YZF_SPI_POINTER spi);

/**
 * 半双工关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_BIDI(YZF_SPI_POINTER spi);

/**
 * 只接收使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_enable_RXONLY(YZF_SPI_POINTER spi);

/**
 * 只接收关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_spi_disable_RXONLY(YZF_SPI_POINTER spi);

//BSY FLAG获取
YZF_BOOL yzf_spi_flag_bsy(YZF_SPI_POINTER spi);
//OVR FLAG获取
YZF_BOOL yzf_spi_flag_ovr(YZF_SPI_POINTER spi);
//MODF FLAG模式错误获取
YZF_BOOL yzf_spi_flag_modf(YZF_SPI_POINTER spi);
//CRCERR FLAG获取
YZF_BOOL yzf_spi_flag_crcerr(YZF_SPI_POINTER spi);
//UDR FLAG获取 下溢标志
YZF_BOOL yzf_spi_flag_udr(YZF_SPI_POINTER spi);
//CHSIDE FLAG获取 声道
YZF_BOOL yzf_spi_flag_chside(YZF_SPI_POINTER spi);
//下一个输出CRC
YZF_RESULT yzf_spi_crc_next(YZF_SPI_POINTER spi);
YZF_RESULT yzf_spi_disable_all_interrupt(YZF_SPI_POINTER spi);
YZF_RESULT yzf_spi_clear_all_flag(YZF_SPI_POINTER spi);
YZF_BOOL yzf_spi_flag_txp(YZF_SPI_POINTER spi);
YZF_BOOL yzf_spi_flag_eot(YZF_SPI_POINTER spi);
//TODO: 完善I2S操作
#endif //YZFRAME_YZF_SPI_H