//
// Created by 32827 on 2023/11/26.
//

#ifndef YZFRAME_YZ_I2C_H
#define YZFRAME_YZ_I2C_H
#include "yz.h"

#ifdef __cplusplus
extern "C" {
#endif

#if YZ_USE_WITH_HAL
#define YZ_I2C123_Freq HAL_RCC_GetPCLK1Freq()/1000000
#else
#define YZ_I2C123_Freq 36
#endif
YZF_RESULT yz_i2c_add7_high_open(YZF_I2C_POINTER i2c,uint8_t address,uint8_t clockFreq);
YZF_RESULT yz_i2c_add7_normal_open(YZF_I2C_POINTER i2c,uint8_t address,uint8_t clockFreq);
YZF_RESULT yz_i2c_add7_transmit(YZF_I2C_POINTER i2c,uint8_t address,uint8_t* data,uint16_t length);
YZF_RESULT yz_i2c_add7_mem_transmit(YZF_I2C_POINTER i2c,uint8_t address,uint8_t memAddress,uint8_t* data,uint16_t length);
YZF_RESULT yz_i2c_add7_receive(YZF_I2C_POINTER i2c,uint8_t address,uint8_t* data,uint16_t length);
YZF_RESULT yz_i2c_add7_mem_receive(YZF_I2C_POINTER i2c,uint8_t address,uint8_t memAddress,uint8_t* data,uint16_t length);
YZF_RESULT yz_i2c_add7_cmd_receive(YZF_I2C_POINTER i2c,uint8_t address,uint8_t memAddress,uint8_t* data,uint16_t length);

#ifdef __cplusplus
}
#endif

#endif //YZFRAME_YZ_I2C_H
