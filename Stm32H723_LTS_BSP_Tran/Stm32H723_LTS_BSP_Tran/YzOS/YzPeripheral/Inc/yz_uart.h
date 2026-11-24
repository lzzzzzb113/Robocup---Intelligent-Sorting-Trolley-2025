//
// Created by 32827 on 2023/11/24.
//

#ifndef YZFRAME_YZ_UART_H
#define YZFRAME_YZ_UART_H
#include "yz.h"
#include "yzf_uart.h"
#include "yzf_nvic.h"
#include "yz_dma.h"
#include "yz_time_area.h"

#ifdef __cplusplus
extern "C" {
#endif
struct YZ_UART_TRANSMIT_BLOCK{
    YZF_UART_POINTER uart;
    uint8_t* data;
    uint16_t len;
    uint16_t index;
};

extern YZF_RECV YZ_UART1_IT_RECV;
extern YZF_RECV YZ_UART2_IT_RECV;
extern YZF_RECV YZ_UART3_IT_RECV;
extern YZF_RECV YZ_UART4_IT_RECV;
extern YZF_RECV YZ_UART5_IT_RECV;


typedef struct YZ_UART_TRANSMIT_BLOCK YZ_UART_TRANSMIT_BLOCK;
uint32_t *yz_uart_get_recv_count();

YZF_RESULT yz_uart_init(YZF_UART_POINTER uart,YZF_UART_WORD_LENGTH length,YZF_UART_DATA stopbits,uint32_t baudrate,YZF_BOOL parity);
YZF_RESULT yz_uart_transmit(YZF_UART_POINTER uart,uint8_t* data,uint16_t len);
YZF_RESULT yz_uart_transmit_IT(YZF_UART_POINTER uart,uint8_t* data,uint16_t len);
YZF_RESULT yz_uart_transmit_DMA(YZF_UART_POINTER uart,uint8_t* data,uint16_t len);
YZF_RESULT yz_uart_transmit_area_DMA(YZF_UART_POINTER uart,YZF_RECV *area,uint16_t len);

YZF_RESULT yz_uart_receive(YZF_UART_POINTER uart,uint8_t* data,uint16_t len);
YZF_RESULT yz_uart_receive_IT_init(YZF_UART_POINTER uart);
YZF_RECV_DATA_INDEX yz_uart_receive_IT_size(YZF_UART_POINTER uart);
YZF_RECV * yz_uart_receive_IT_RECV_get(YZF_UART_POINTER uart);
YZF_RESULT yz_uart_receive_IT(YZF_UART_POINTER uart,uint8_t* data,uint16_t len);
#ifdef __cplusplus
}
#endif
#endif //YZFRAME_YZ_UART_H
