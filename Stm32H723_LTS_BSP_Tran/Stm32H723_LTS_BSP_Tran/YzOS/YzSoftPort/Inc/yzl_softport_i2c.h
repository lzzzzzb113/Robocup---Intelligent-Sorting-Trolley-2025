//
// Created by 32827 on 2024/2/7.
//

#ifndef YZGD32_YZL_SOFTPORT_I2C_H
#define YZGD32_YZL_SOFTPORT_I2C_H
#include "yzl_softport.h"

#if USE_SOFT_PORT && YZL_SOFT_PORT_IIC
enum YZL_Soft_I2C_MODE{
    YZL_Soft_I2C_MODE_100,
    YZL_Soft_I2C_MODE_400
};

typedef struct {
    enum YZL_Soft_I2C_MODE MODE;
    YZL_GPIO SDA;
    YZL_GPIO SCL;
}YZL_Soft_I2C;

#ifdef __cplusplus
extern "C" {
#endif

YZF_RESULT yzl_softport_i2c_init(YZL_Soft_I2C *i2c);

YZF_RESULT yzl_softport_i2c_sda_out(YZL_Soft_I2C *i2c);

YZF_RESULT yzl_softport_i2c_sda_in(YZL_Soft_I2C *i2c);

void yzl_softport_i2c_delay(YZL_Soft_I2C *i2c);

YZF_RESULT yzl_softport_i2c_start(YZL_Soft_I2C *i2c);

YZF_RESULT yzl_softport_i2c_stop(YZL_Soft_I2C *i2c);

YZF_BOOL yzl_softport_i2c_wait_ack(YZL_Soft_I2C *i2c);

YZF_RESULT yzl_softport_i2c_ack(YZL_Soft_I2C *i2c);

YZF_RESULT yzl_softport_i2c_no_ack(YZL_Soft_I2C *i2c);

YZF_RESULT yzl_softport_i2c_write(YZL_Soft_I2C *i2c, uint8_t addr, uint8_t *data, uint16_t len);

YZF_RESULT
yzl_softport_i2c_param_write(YZL_Soft_I2C *i2c, uint8_t addr, uint8_t *sendData, uint8_t sendLen, uint8_t *data,
                             uint16_t len);

YZF_RESULT
yzl_softport_i2c_read(YZL_Soft_I2C *i2c, uint8_t addr, uint8_t *sendData, uint8_t sendLen, uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif
#endif //YZGD32_YZL_SOFTPORT_I2C_H
