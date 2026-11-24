//
// Created by 32827 on 2025/7/15.
//

#ifndef STM32H723_LTS_BSP_YZL_UART_TMC2209_H
#define STM32H723_LTS_BSP_YZL_UART_TMC2209_H
#include "yzx_base.h"
#include "yzl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t raw[8];
    uint32_t data;
} TMC2209Response;

YZF_RESULT yzl_uart_tmc2209_get_next_response(YZF_UART_POINTER uart,TMC2209Response *response);
YZF_RESULT yzl_uart_tmc2209_init(YZF_UART_POINTER uart,uint8_t address);
uint8_t yzl_uart_tmc2209_crc(uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif //STM32H723_LTS_BSP_YZL_UART_TMC2209_H
