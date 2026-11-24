//
// Created by 32827 on 2023/11/17.
//

#ifndef YZFRAME_YZF_UART_H
#define YZFRAME_YZF_UART_H
#include "yzf.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef uint8_t YZF_UART_DATA;
enum YZF_UART_WORD_LENGTH{
    YZF_UART_LENGTH_8,
    YZF_UART_LENGTH_9
};
#if YZF_USE_WITH_HAL
#define YZF_UART1_BAUDRATE_2400 2400
#define YZF_UART1_BAUDRATE_9600 9600
#define YZF_UART1_BAUDRATE_19200 19200
#define YZF_UART1_BAUDRATE_57600 57600
#define YZF_UART1_BAUDRATE_115200 115200

#define YZF_UART2345_BAUDRATE_2400 2400
#define YZF_UART2345_BAUDRATE_9600 9600
#define YZF_UART2345_BAUDRATE_19200 19200
#define YZF_UART2345_BAUDRATE_57600 57600
#define YZF_UART2345_BAUDRATE_115200 115200
#else
#define YZF_UART1_BAUDRATE_2400 ((1875<<4)+0b0000)
#define YZF_UART1_BAUDRATE_9600 ((468<<4)+0b1100)
#define YZF_UART1_BAUDRATE_19200 ((234<<4)+0b0110)
#define YZF_UART1_BAUDRATE_57600 ((78<<4)+0b0010)
//#define YZF_UART1_BAUDRATE_115200 ((39<<4)+0b0001)
#define YZF_UART1_BAUDRATE_115200 ((45<<4)+0b1001)

#define YZF_UART2345_BAUDRATE_2400 ((937<<4)+0b1000)
#define YZF_UART2345_BAUDRATE_9600 ((234<<4)+0b0110)
#define YZF_UART2345_BAUDRATE_19200 ((117<<4)+0b0011)
#define YZF_UART2345_BAUDRATE_57600 ((39<<4)+0b0001)
#define YZF_UART2345_BAUDRATE_115200 ((19<<4)+0b1000)
#endif
typedef enum YZF_UART_WORD_LENGTH YZF_UART_WORD_LENGTH;
YZF_RESULT yzf_uart_source_clock_open(YZF_UART_POINTER uart);
//串口使能
YZF_RESULT yzf_uart_enable(YZF_UART_POINTER uart);
//发送数据寄存器空
YZF_BOOL yzf_uart_flag_TXE(YZF_UART_POINTER uart);
//发送完成
YZF_BOOL yzf_uart_flag_TC(YZF_UART_POINTER uart);
//读数据寄存器非空
YZF_BOOL yzf_uart_flag_RXNE(YZF_UART_POINTER uart);
//监测到总线空闲 一次性发送了8个字节，就会产生8次RXNE中断，1次IDLE中断
YZF_BOOL yzf_uart_flag_IDLE(YZF_UART_POINTER uart);
//过载位 当前数据未被读取，再次接收到数据时
YZF_BOOL yzf_uart_flag_ORE(YZF_UART_POINTER uart);
//噪声错误
YZF_BOOL yzf_uart_flag_NE(YZF_UART_POINTER uart);
//帧错误
YZF_BOOL yzf_uart_flag_FE(YZF_UART_POINTER uart);
//校验错位
YZF_BOOL yzf_uart_flag_PE(YZF_UART_POINTER uart);
//获取数据寄存器值
YZF_UART_DATA yzf_uart_get_data(YZF_UART_POINTER uart);
//设置数据寄存器值
YZF_RESULT yzf_uart_set_data(YZF_UART_POINTER uart, YZF_UART_DATA data);
//设置波特率
YZF_RESULT yzf_uart_baud_rate(YZF_UART_POINTER uart, uint16_t data);
//设置字长
YZF_RESULT yzf_uart_word_length(YZF_UART_POINTER uart, YZF_UART_WORD_LENGTH length);
//当总线空闲时唤醒
YZF_RESULT yzf_uart_set_wakeup_Idle(YZF_UART_POINTER uart);
//当地址标记唤醒
YZF_RESULT yzf_uart_set_wakeup_Address(YZF_UART_POINTER uart);
//开启/关闭校验
YZF_RESULT yzf_uart_set_parity(YZF_UART_POINTER uart,YZF_BOOL enable);
//奇校验
YZF_RESULT yzf_uart_set_parity_odd(YZF_UART_POINTER uart);
//偶校验
YZF_RESULT yzf_uart_set_parity_even(YZF_UART_POINTER uart);
//PE校验中断使能
YZF_RESULT yzf_uart_pe_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable);
//发送缓冲区空中断使能
YZF_RESULT yzf_uart_txe_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable);
//发送完成中断使能
YZF_RESULT yzf_uart_tc_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable);
//接收缓冲区非空中断使能
YZF_RESULT yzf_uart_rxne_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable);
//IDLE中断使能,一帧发送完毕
YZF_RESULT yzf_uart_idle_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable);
//TE 发送使能
YZF_RESULT yzf_uart_te_enable(YZF_UART_POINTER uart);
YZF_RESULT yzf_uart_te_disable(YZF_UART_POINTER uart);
//RE 接收使能 当为1时位静默模式
YZF_RESULT yzf_uart_re_enable(YZF_UART_POINTER uart);
YZF_RESULT yzf_uart_re_disable(YZF_UART_POINTER uart);
//接受唤醒
YZF_RESULT yzf_uart_re_wakeup(YZF_UART_POINTER uart);
//发送断开帧
YZF_RESULT yzf_uart_send_disconnect_frame(YZF_UART_POINTER uart);
//LIN模式使能
YZF_RESULT yzf_uart_lin(YZF_UART_POINTER uart,YZF_BOOL enable);
//停止位 0-1 1-0.5 2-2 3-1.5
YZF_RESULT yzf_uart_stop_bit(YZF_UART_POINTER uart,YZF_UART_DATA stopbits);
//时钟使能
YZF_RESULT yzf_uart_clock(YZF_UART_POINTER uart,YZF_BOOL enable);
//设置时钟极性 isHigh空闲时是否保持高电位
YZF_RESULT yzf_uart_clock_polarity(YZF_UART_POINTER uart,YZF_BOOL isHigh);
//设置时钟相位 isSecond是否在第二个边沿捕获
YZF_RESULT yzf_uart_clock_phase(YZF_UART_POINTER uart,YZF_BOOL isSecond);
//LIN断开符中断使能
YZF_RESULT yzf_uart_lin_disconnect_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable);
//LIN断开符检测长度 true 11位检测 false 10位检测
YZF_RESULT yzf_uart_lin_disconnect_length(YZF_UART_POINTER uart,YZF_BOOL is11bits);
//设备节点地址 0b0000 4位
YZF_RESULT yzf_uart_node_address(YZF_UART_POINTER uart,YZF_UART_DATA address);
//CTS中断使能
YZF_RESULT yzf_uart_cts_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable);
//CTS使能
YZF_RESULT yzf_uart_cts_enable(YZF_UART_POINTER uart,YZF_BOOL enable);
//RTS中断使能 当有空闲时才请求下一个数据
YZF_RESULT yzf_uart_rts_enable(YZF_UART_POINTER uart,YZF_BOOL enable);
//DMA发送使能
YZF_RESULT yzf_uart_dma_transmitter_enable(YZF_UART_POINTER uart,YZF_BOOL enable);
//DMA接收使能
YZF_RESULT yzf_uart_dma_receiver_enable(YZF_UART_POINTER uart,YZF_BOOL enable);
//半双工模式
YZF_RESULT yzf_uart_half_duplex(YZF_UART_POINTER uart,YZF_BOOL enable);
//错误中断使能
YZF_RESULT yzf_uart_error_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable);
//TX ENABLE
YZF_RESULT yzf_uart_tx_enable(YZF_UART_POINTER uart,YZF_BOOL enable);
//RX ENABLE
YZF_RESULT yzf_uart_rx_enable(YZF_UART_POINTER uart,YZF_BOOL enable);
#ifdef __cplusplus
}
#endif
#endif //YZFRAME_YZF_UART_H
