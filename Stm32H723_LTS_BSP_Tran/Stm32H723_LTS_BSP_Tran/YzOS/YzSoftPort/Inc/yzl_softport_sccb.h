//
// Created by 32827 on 2024/6/27.
//

#ifndef STM32F407RTOS_YZL_SOFTPORT_SCCB_H
#define STM32F407RTOS_YZL_SOFTPORT_SCCB_H
#include "yzl_softport.h"
typedef struct {
    YZL_GPIO SDA;
    YZL_GPIO SCL;
} YZL_Soft_SCCB;

#ifdef __cplusplus
extern "C" {
#endif

#if USE_SOFT_PORT && YZL_SOFT_PORT_SCCB
YZF_RESULT yzl_softport_sccb_init(YZL_Soft_SCCB *sccb);
YZF_RESULT yzl_softport_sccb_sda_out(YZL_Soft_SCCB *sccb);
YZF_RESULT yzl_softport_sccb_sda_in(YZL_Soft_SCCB *sccb);
YZF_RESULT yzl_softport_sccb_start(YZL_Soft_SCCB *sccb);
YZF_RESULT yzl_softport_sccb_stop(YZL_Soft_SCCB *sccb);
YZF_RESULT yzl_softport_sccb_NA(YZL_Soft_SCCB *sccb);
uint8_t yzl_softport_sccb_read_byte(YZL_Soft_SCCB *sccb);
YZF_RESULT yzl_softport_sccb_write_byte(YZL_Soft_SCCB *sccb,uint8_t dat);
YZF_RESULT yzl_softport_sccb_write_register(YZL_Soft_SCCB *sccb,uint8_t address,uint8_t reg,uint8_t data);
uint8_t yzl_softport_sccb_read_register(YZL_Soft_SCCB *sccb,uint8_t address,uint8_t reg);

#endif
#ifdef __cplusplus
}
#endif
#endif //STM32F407RTOS_YZL_SOFTPORT_SCCB_H
