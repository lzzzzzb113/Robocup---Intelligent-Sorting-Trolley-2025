//
// Created by 32827 on 2024/1/10.
//

#ifndef YZ_CONF_H
#define YZ_CONF_H
#include "yzdef.h"

#define YZ_CONF_CLOCK_FREQ (550*1000*1000)
#define YZ_USE_DEFAULT_CLOCK YZF_OFF    //是否已经通过Yzf配置系统时钟
#define YZ_USE_TICK_WITH_HAL YZF_OFF     //是否使用HAL库的Tick,进行延时

//Color Mode
#define YZ_COLOR_MODE YZ_COLOR_MODE_RGB565

#define YZ_RECV_TRANSMIT_LEW_LIGHT yzf_gpio_set_1(GPIOA,YZF_PIN_8)
#define YZ_RECV_TRANSMIT_LEW_DARK yzf_gpio_set_0(GPIOA,YZF_PIN_8)

//Yzl_MEM Running Config
#define YZL_MEMORY_MANAGER_DEBUG YZF_OFF
//Yzl_FatFs Running Config
#define YZFATFS ON
#define YZFATFS_SD_DRIVER_PORT MicroSD_SPI
#define YZFATFS_MEMORY_MALLOC_DEBUG YZF_OFF

#endif //YZ_CONF_H
