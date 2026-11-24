//
// Created by 32827 on 2023/11/21.
//

#ifndef YZFRAME_YZF_I2C_H
#define YZFRAME_YZF_I2C_H
#include "yzf.h"
#define YZF_I2C_Write 0
#define YZF_I2C_Read 1
#define YZF_I2C_PEC_DATA uint8_t
typedef uint8_t YZF_I2C_DATA;

/**
 *
 * 开启i2c
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_open(YZF_I2C_POINTER i2c);

/**
 *
 * 设置起始位
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_start(YZF_I2C_POINTER i2c);

/**
 *
 * 发送数据
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_write_data(YZF_I2C_POINTER i2c,YZF_I2C_DATA data);

/**
 *
 * 读取数据
 *
 * @CheckPlatform STM32H723
 * */
YZF_I2C_DATA yzf_i2c_read_data(YZF_I2C_POINTER i2c);

/**
 *
 * 设置10位地址
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_set_address_10(YZF_I2C_POINTER i2c,uint16_t address,YZF_BOOL EnableCall);

/**
 *
 * 设置7位地址
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_set_address_7(YZF_I2C_POINTER i2c,uint8_t address,YZF_BOOL EnableCall);

/**
 *
 * 发送从设备10位地址
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_send_address_10(YZF_I2C_POINTER i2c,uint16_t address);

/**
 *
 * 发送从设备7位地址
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_send_address_7(YZF_I2C_POINTER i2c,uint8_t address);

/**
 *
 * 禁止时钟延长（从模式）
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_disable_clock_stretching(YZF_I2C_POINTER i2c);

/**
 *
 * 广播回应使能(0x00)
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_call_enable(YZF_I2C_POINTER i2c);

/**
 *
 * 广播回应关闭(0x00)
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_call_disable(YZF_I2C_POINTER i2c);

/**
 *
 * 主模式读
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_mode_read(YZF_I2C_POINTER i2c);

/**
 *
 * 主模式写
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_mode_write(YZF_I2C_POINTER i2c);
/**
 *
 * PEC使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_pec_enable(YZF_I2C_POINTER i2c);
/**
 *
 * PEC关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_pec_disable(YZF_I2C_POINTER i2c);

/**
 *
 * I2C 使能 控制IO
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_enable(YZF_I2C_POINTER i2c);
/**
 *
 * I2C 关闭 释放IO
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_disable(YZF_I2C_POINTER i2c);

/**
 *
 * DMA RX 使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_rx_dma_enable(YZF_I2C_POINTER i2c);
/**
 *
 * DMA RX 关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_rx_dma_disable(YZF_I2C_POINTER i2c);

/**
 *
 * DMA TX 使能
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_tx_dma_enable(YZF_I2C_POINTER i2c);

/**
 *
 * DMA TX 关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_tx_dma_disable(YZF_I2C_POINTER i2c);

/**
 *
 * 待发送（接收）的数量
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_set_cnt(YZF_I2C_POINTER i2c,uint8_t cnt);

/**
 *
 * 发送ACK
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_ack_enable(YZF_I2C_POINTER i2c);

/**
 *
 * 发送NACK
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_ack_disable(YZF_I2C_POINTER i2c);

/**
 *
 * 当前字节发送后，发送stop
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_stop(YZF_I2C_POINTER i2c);

/**
 *
 * 当前字节发送后，等待重新发送开启
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_enable_reload(YZF_I2C_POINTER i2c);
/**
 *
 * 当前字节发送后，等待重新发送关闭
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_disable_reload(YZF_I2C_POINTER i2c);


/**
 *
 * 开启自动结束
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_enable_autoEnd(YZF_I2C_POINTER i2c);

/**
 *
 * 关闭自动结束
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_disable_autoEnd(YZF_I2C_POINTER i2c);

/**
 *
 * 使能地址二
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_address2_enable(YZF_I2C_POINTER i2c);
/**
 *
 * 关闭地址二
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_address2_disable(YZF_I2C_POINTER i2c);
/**
 *
 * 设置地址二
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_set_address2(YZF_I2C_POINTER i2c,uint8_t address);

/**
 *
 * FLAG Timeout
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_timeout(YZF_I2C_POINTER i2c);

/**
 *
 * FLAG PECERR PEC错误
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_PECERR(YZF_I2C_POINTER i2c);

/**
 *
 * FLAG OVR 过载或者欠载
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_OVR(YZF_I2C_POINTER i2c);

/**
 *
 * FLAG AF 应答失败
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_AF(YZF_I2C_POINTER i2c);

/**
 * FLAG Clear AF
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_flag_clear_AF(YZF_I2C_POINTER i2c);

/**
 *
 * 仲裁丢失
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_ARLO(YZF_I2C_POINTER i2c);

/**
 *
 * 总线出错
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_BERR(YZF_I2C_POINTER i2c);

/**
 *
 * 数据寄存器为空(发送时)
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_TxE(YZF_I2C_POINTER i2c);

/**
 *
 * 传输结束
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_TC(YZF_I2C_POINTER i2c);

/**
 *
 * 数据寄存器为空(发送时)
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_TxISE(YZF_I2C_POINTER i2c);
/**
 *
 * 数据寄存器非空(发送时)
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_RxNE(YZF_I2C_POINTER i2c);

/**
 *
 * 停止条件检测为
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_STOPF(YZF_I2C_POINTER i2c);
/**
 *
 * 清除停止标志
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_clear_STOPF(YZF_I2C_POINTER i2c);

/**
 *
 * 地址已发送/地址匹配
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_ADDR(YZF_I2C_POINTER i2c);

/**
 *
 * busy
 *
 * @CheckPlatform STM32H723
 * */
YZF_BOOL yzf_i2c_flag_BUSY(YZF_I2C_POINTER i2c);

/**
 *
 * 分频系数
 * t PRESC = (PRESC+1) x t I2CCLK
 *
 * @param ccr [3:0]
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_set_CCR(YZF_I2C_POINTER i2c,uint16_t ccr);

/**
 *
 * 数据建立时间
 * t SCLDEL = (SCLDEL+1) x t PRESC
 *
 * @param dataSetTime [3:0]
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_data_set_time(YZF_I2C_POINTER i2c,uint16_t dataSetTime);

/**
 *
 * 数据保持时间
 * t SDADEL = SDADEL x t PRESC
 *
 * @param dataHoldTime [3:0]
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_data_hold_time(YZF_I2C_POINTER i2c,uint16_t dataHoldTime);

/**
 *
 * 高电平时间STM32CubeMX会展示
 * t SCLH = (SCLH+1) x tPRESC
 *
 * @param highTime [7:0]
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_high_time(YZF_I2C_POINTER i2c,uint16_t highTime);

/**
 *
 * 低电平时间STM32CubeMX会展示
 * t SCLL = (SCLL+1) x t PRESC
 *
 * @param lowTime [7:0]
 *
 * @CheckPlatform STM32H723
 * */
YZF_RESULT yzf_i2c_low_time(YZF_I2C_POINTER i2c,uint16_t lowTime);
#endif //YZFRAME_YZF_I2C_H