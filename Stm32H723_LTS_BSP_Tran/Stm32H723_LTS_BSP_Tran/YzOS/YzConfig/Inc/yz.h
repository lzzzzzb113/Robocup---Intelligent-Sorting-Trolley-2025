//
// Created by 32827 on 2023/11/23.
//

#ifndef YZ_CONFIG_H
#define YZ_CONFIG_H
#include "yzf.h"
#include "yz_include_control.h"

#if YZF_USE_WITH_HAL
#define YZ_USE_WITH_HAL ON
#include "yz_hal.h"
#else
#define YZ_USE_WITH_HAL OFF
#endif

#if YZ_USE_WITH_HAL
#define YZ_USE_WITH_HAL_UART OFF
#endif

#endif //YZFRAME_YZ_CONFIG_H
