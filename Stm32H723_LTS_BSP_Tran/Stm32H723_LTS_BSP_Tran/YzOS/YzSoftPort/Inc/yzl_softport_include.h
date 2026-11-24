//
// Created by 32827 on 2024/1/10.
//

#ifndef STM32OSCOVER_YZL_SOFTPORT_INCLUDE_H
#define STM32OSCOVER_YZL_SOFTPORT_INCLUDE_H
#include "yzl_softport.h"

#if YZL_SOFT_PORT_SPI
#include "yzl_softport_spi.h"
#endif

#if YZL_SOFT_PORT_IIC
#include "yzl_softport_i2c.h"
#endif
#endif //STM32OSCOVER_YZL_SOFTPORT_INCLUDE_H
