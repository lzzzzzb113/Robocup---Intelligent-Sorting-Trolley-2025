//
// Created by 32827 on 2023/11/17.
//
#include "yzf_uart.h"
YZF_RESULT yzf_uart_source_clock_open(YZF_UART_POINTER uart){
    switch ((uint32_t) uart) {
        case (uint32_t)USART1:
            RCC->APB2ENR |=RCC_APB2ENR_USART1EN;
            break;
        case (uint32_t)USART2:
            RCC->APB1LENR |=RCC_APB1LENR_USART2EN;
            break;
        case (uint32_t)USART3:
            RCC->APB1LENR |=RCC_APB1LENR_USART3EN;
            break;
        case (uint32_t)UART4:
            RCC->APB1LENR |=RCC_APB1LENR_UART4EN;
            break;
        case (uint32_t)UART5:
            RCC->APB1LENR |=RCC_APB1LENR_UART5EN;
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}
//串口使能
YZF_RESULT yzf_uart_enable(YZF_UART_POINTER uart){
    uart->CR1|=0b1<<USART_CR1_UE_Pos;
    return YZF_OK;
}
//发送数据寄存器空
YZF_BOOL yzf_uart_flag_TXE(YZF_UART_POINTER uart){
    return (uart->ISR&0b1<<USART_ISR_TXE_TXFNF_Pos) ? YZF_TRUE : YZF_FALSE;
}
//接收数据寄存器非空
YZF_BOOL yzf_uart_flag_RXNE(YZF_UART_POINTER uart){
    return (uart->ISR&0b1<<USART_ISR_RXNE_RXFNE_Pos) ? YZF_TRUE : YZF_FALSE;
}
//发送完成
YZF_BOOL yzf_uart_flag_TC(YZF_UART_POINTER uart){
    return (uart->ISR&0b1<<USART_ISR_TC_Pos) ? YZF_TRUE : YZF_FALSE;
}
//监测到总线空闲 一次性发送了8个字节，就会产生8次RXNE中断，1次IDLE中断
YZF_BOOL yzf_uart_flag_IDLE(YZF_UART_POINTER uart){
    return (uart->ISR&0b1<<USART_ISR_IDLE_Pos) ? YZF_TRUE : YZF_FALSE;
}
//过载位 当前数据未被读取，再次接收到数据时
YZF_BOOL  yzf_uart_flag_ORE(YZF_UART_POINTER uart){
    return (uart->ISR&0b1<<USART_ISR_ORE_Pos) ? YZF_TRUE : YZF_FALSE;
}
//噪声错误
YZF_BOOL yzf_uart_flag_NE(YZF_UART_POINTER uart){
    return (uart->ISR&0b1<<USART_ISR_NE_Pos) ? YZF_TRUE : YZF_FALSE;
}
//帧错误
YZF_BOOL yzf_uart_flag_FE(YZF_UART_POINTER uart){
    return (uart->ISR&0b1<<USART_ISR_FE_Pos) ? YZF_TRUE : YZF_FALSE;
}
//校验错位
YZF_BOOL yzf_uart_flag_PE(YZF_UART_POINTER uart){
    return  (uart->ISR&0b1<<USART_ISR_PE_Pos) ? YZF_TRUE : YZF_FALSE;
}
//获取数据寄存器值
YZF_UART_DATA yzf_uart_get_data(YZF_UART_POINTER uart){
    return uart->RDR;
}
//设置数据寄存器值
YZF_RESULT yzf_uart_set_data(YZF_UART_POINTER uart, YZF_UART_DATA data){
    uart->TDR = data;
    return YZF_OK;
}
//设置波特率
YZF_RESULT yzf_uart_baud_rate(YZF_UART_POINTER uart, uint16_t data){
    uart->BRR = data;
    return YZF_OK;
}
//设置字长
YZF_RESULT yzf_uart_word_length(YZF_UART_POINTER uart, YZF_UART_WORD_LENGTH length){
    uart->CR1 &= ~(0b1<<USART_CR1_M_Pos);
    uart->CR1 |= (length<<USART_CR1_M_Pos);
    return YZF_OK;
}
//当总线空闲时唤醒
YZF_RESULT yzf_uart_set_wakeup_Idle(YZF_UART_POINTER uart){
    uart->CR1 &= ~(1<<USART_CR1_WAKE_Pos);
    return YZF_OK;
}
//当地址标记唤醒
YZF_RESULT yzf_uart_set_wakeup_Address(YZF_UART_POINTER uart){
    uart->CR1 |= 1<<USART_CR1_WAKE_Pos;
    return YZF_OK;
}
//开启/关闭校验
YZF_RESULT yzf_uart_set_parity(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR1 &=~(1<<USART_CR1_PS_Pos);
    uart->CR1 |= enable<<USART_CR1_PS_Pos;
    return YZF_OK;
}
//奇校验
YZF_RESULT yzf_uart_set_parity_odd(YZF_UART_POINTER uart){
    uart->CR1 |= 1<<USART_CR1_PS_Pos;
    return YZF_OK;
}
//偶校验
YZF_RESULT yzf_uart_set_parity_even(YZF_UART_POINTER uart){
    uart->CR1 &=~(1<<USART_CR1_PS_Pos);
    return YZF_OK;
}
//PE校验中断使能
YZF_RESULT yzf_uart_pe_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR1 &=~(1<<USART_CR1_PEIE_Pos);
    uart->CR1 |= enable<<USART_CR1_PEIE_Pos;
    return YZF_OK;
}
//发送缓冲区空中断使能
YZF_RESULT yzf_uart_txe_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR1 &=~(1<<USART_CR1_TXEIE_TXFNFIE_Pos);
    uart->CR1 |= enable<<USART_CR1_TXEIE_TXFNFIE_Pos;
    return YZF_OK;
}
//接收缓冲区空中断使能
YZF_RESULT yzf_uart_rxne_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR1 &=~(1<<USART_CR1_RXNEIE_RXFNEIE_Pos);
    uart->CR1 |= enable<<USART_CR1_RXNEIE_RXFNEIE_Pos;
    return YZF_OK;
}
//发送完成中断使能
YZF_RESULT yzf_uart_tc_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR1 &=~(1<<USART_CR1_TCIE_Pos);
    uart->CR1 |= enable<<USART_CR1_TCIE_Pos;
    return YZF_OK;
}
//IDLE中断使能,一帧发送完毕
YZF_RESULT yzf_uart_idle_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR1 &=~(1<<USART_CR1_IDLEIE_Pos);
    uart->CR1 |= enable<<USART_CR1_IDLEIE_Pos;
    return YZF_OK;
}
//TE 发送使能
YZF_RESULT yzf_uart_te_enable(YZF_UART_POINTER uart){
    uart->CR1 |= (1<<USART_CR1_TE_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_uart_te_disable(YZF_UART_POINTER uart){
    uart->CR1 &= ~(1<<USART_CR1_TE_Pos);
    return YZF_OK;
}
//RE 接收使能 当为1时位静默模式
YZF_RESULT yzf_uart_re_enable(YZF_UART_POINTER uart){
    uart->CR1 |= (1<<USART_CR1_RE_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_uart_re_disable(YZF_UART_POINTER uart){
    uart->CR1 &= ~(1<<USART_CR1_RE_Pos);
    return YZF_OK;
}
//接受唤醒
YZF_RESULT yzf_uart_re_wakeup(YZF_UART_POINTER uart){
    uart->CR1 &=~(1<<USART_CR1_RE_Pos);
    return YZF_OK;
}
//发送断开帧
YZF_RESULT yzf_uart_send_disconnect_frame(YZF_UART_POINTER uart){
    uart->RQR |= (1<<USART_RQR_SBKRQ_Pos);
    return YZF_OK;
}
//LIN模式使能
YZF_RESULT yzf_uart_lin(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR2 &=~(1<<USART_CR2_LINEN_Pos);
    return YZF_OK;
}
//停止位 0-1 1-0.5 2-2 3-1.5
YZF_RESULT yzf_uart_stop_bit(YZF_UART_POINTER uart,YZF_UART_DATA stopbits){
    uart->CR2 &=~(0b11<<USART_CR2_STOP_Pos);
    uart->CR2 |= (stopbits<<USART_CR2_STOP_Pos);
    return YZF_OK;
}
//时钟使能
YZF_RESULT yzf_uart_clock(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR2 &=~(1<<USART_CR2_CLKEN_Pos);
    uart->CR2 |= enable<<USART_CR2_CLKEN_Pos;
    return YZF_OK;
}
//设置时钟极性 isHigh空闲时是否保持高电位
YZF_RESULT yzf_uart_clock_polarity(YZF_UART_POINTER uart,YZF_BOOL isHigh){
    uart->CR2 &=~(1<<USART_CR2_CPOL_Pos);
    uart->CR2 |= isHigh<<USART_CR2_CPOL_Pos;
    return YZF_OK;
}
//设置时钟相位 isSecond是否在第二个边沿捕获
YZF_RESULT yzf_uart_clock_phase(YZF_UART_POINTER uart,YZF_BOOL isFirst){
    uart->CR2 &=~(1<<USART_CR2_CPHA_Pos);
    uart->CR2 |= isFirst<<USART_CR2_CPHA_Pos;
    return YZF_OK;
}
//LIN断开符中断使能
YZF_RESULT yzf_uart_lin_disconnect_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR2 &= ~(1<<USART_CR2_LBDIE_Pos);
    uart->CR2 |= enable<<USART_CR2_LBDIE_Pos;
    return YZF_OK;
}
//LIN断开符检测长度 true 11位检测 false 10位检测
YZF_RESULT yzf_uart_lin_disconnect_length(YZF_UART_POINTER uart,YZF_BOOL is11bits){
    uart->CR2 &=~(1<<USART_CR2_LBCL_Pos);
    uart->CR2 |= is11bits<<USART_CR2_LBCL_Pos;
    return YZF_OK;
}
//设备节点地址 0b0000 4位
YZF_RESULT yzf_uart_node_address(YZF_UART_POINTER uart,YZF_UART_DATA address){
    uart->CR2 &=~(0b1111<<USART_CR2_ADD_Pos);
    uart->CR2 |= address<<USART_CR2_ADD_Pos;
    return YZF_OK;
}
//CTS中断使能
YZF_RESULT yzf_uart_cts_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR3 &=~(1<<USART_CR3_CTSIE_Pos);
    uart->CR3 |= enable<<USART_CR3_CTSIE_Pos;
    return YZF_OK;
}
//CTS使能
YZF_RESULT yzf_uart_cts_enable(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR3 &=~(1<<USART_CR3_CTSE_Pos);
    uart->CR3 |= enable<<USART_CR3_CTSE_Pos;
    return YZF_OK;
}
//RTS中断使能 当有空闲时才请求下一个数据
YZF_RESULT yzf_uart_rts_enable(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR3 &=~(1<<USART_CR3_RTSE_Pos);
    uart->CR3 |= enable<<USART_CR3_RTSE_Pos;
    return YZF_OK;
}
//DMA发送使能
YZF_RESULT yzf_uart_dma_transmitter_enable(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR3 &=~(1<<USART_CR3_DMAT_Pos);
    uart->CR3 |= enable<<USART_CR3_DMAT_Pos;
    return YZF_OK;
}
//DMA接收使能
YZF_RESULT yzf_uart_dma_receiver_enable(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR3 &=~(1<<USART_CR3_DMAR_Pos);
    uart->CR3 |= enable<<USART_CR3_DMAR_Pos;
    return YZF_OK;
}
//半双工模式
YZF_RESULT yzf_uart_half_duplex(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR3 &=~(1<<USART_CR3_HDSEL_Pos);
    uart->CR3 |= enable<<USART_CR3_HDSEL_Pos;
    return YZF_OK;
}
//错误中断使能
YZF_RESULT yzf_uart_error_interrupt(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR3 &=~(1<<USART_CR3_EIE_Pos);
    uart->CR3 |= enable<<USART_CR3_EIE_Pos;
    return YZF_OK;
}
//TX ENABLE
YZF_RESULT yzf_uart_tx_enable(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR1 &=~(1<<USART_CR1_TE_Pos);
    uart->CR1 |= enable<<USART_CR1_TE_Pos;
    return YZF_OK;
}
//RX ENABLE
YZF_RESULT yzf_uart_rx_enable(YZF_UART_POINTER uart,YZF_BOOL enable){
    uart->CR1 &=~(1<<USART_CR1_RE_Pos);
    uart->CR1 |= enable<<USART_CR1_RE_Pos;
    return YZF_OK;
}