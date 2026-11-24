//
// Created by 32827 on 2023/12/28.
//

#ifndef YZ_LOG_H
#define YZ_LOG_H


#include "yz.h"
#include "stdarg.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * 可自行在其他地方进行重写
 * */
extern char transmit_buf[YZ_APPLICATION_TRANSMIT_BUF_SIZE];;
void yz_error(const char *fmt, ...);
void yz_info(const char *fmt, ...);
void yz_debug(const char *fmt, ...);
void yz_ok(const char *fmt, ...);
void yz_printf(const char *fmt, ...);
void yz_shell_send(void *file,uint8_t *str,  size_t len);

#ifdef __cplusplus
};
#endif
#endif //YZ_LOG_H
