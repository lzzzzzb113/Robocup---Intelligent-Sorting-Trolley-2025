//
// Created by 32827 on 2024/2/7.
//
#include "yzl_softport_i2c.h"

#if USE_SOFT_PORT && YZL_SOFT_PORT_IIC

#if YZL_USE_GPIO_WITH_HAL
GPIO_InitTypeDef GPIO_sda;
#endif

YZF_RESULT yzl_softport_i2c_sda_out(YZL_Soft_I2C *i2c){
#if YZL_USE_GPIO_WITH_HAL
    GPIO_sda.Mode=GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(i2c->SDA.port,&GPIO_sda);
#else
    yzf_gpio_set_PP(i2c->SDA.port,i2c->SDA.pin);
#endif
    return YZF_OK;
}
YZF_RESULT yzl_softport_i2c_sda_in(YZL_Soft_I2C *i2c){
#if YZL_USE_GPIO_WITH_HAL
    GPIO_sda.Mode=GPIO_MODE_INPUT;
    HAL_GPIO_Init(i2c->SDA.port,&GPIO_sda);
#else
    yzf_gpio_set_IN_PULL_UP(i2c->SDA.port,i2c->SDA.pin);
#endif
    return YZF_OK;
}
void yzl_softport_i2c_delay(YZL_Soft_I2C *i2c){
    if(i2c->MODE==YZL_Soft_I2C_MODE_100){
        delay_us(5);
    }else if(i2c->MODE==YZL_Soft_I2C_MODE_400){
        delay_us(2);
    }
}
/**
 *
 * __?__       ?
 *       _____
 * _____/     \
 * */
void yzl_softport_i2c_bit(YZL_Soft_I2C *i2c,YZF_BOOL bit){
    yzl_softport_i2c_delay(i2c);
    if(bit){
        YLHIGH(i2c->SDA);
    }else{
        YLLOW(i2c->SDA);
    }
    yzl_softport_i2c_delay(i2c);
    YLHIGH(i2c->SCL);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    YLLOW(i2c->SCL);
    YLLOW(i2c->SDA);
}
void yzl_softport_i2c_byte(YZL_Soft_I2C *i2C,uint8_t data){
    for(uint8_t i=0;i<8;i++){
        yzl_softport_i2c_bit(i2C,(data&0xF0)>>7);
        data<<=1;
    }
}

/**
 *
 * _____   ?  _
 *       _____
 * _____/     \
 * */
YZF_BOOL yzl_softport_i2c_read_bit(YZL_Soft_I2C *i2c,YZF_BOOL bit){
    YZF_BOOL temp;
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    YLHIGH(i2c->SCL);
    yzl_softport_i2c_delay(i2c);
#if YZL_USE_GPIO_WITH_HAL
    if(HAL_GPIO_ReadPin(i2c->SDA.port,i2c->SDA.pin)==GPIO_PIN_SET){
        temp=YZF_TRUE;
    }else{
        temp=YZF_FALSE;
    }
#else
    if(yzf_gpio_get(i2c->SDA.port,i2c->SDA.pin)){
        temp=YZF_TRUE;
    }else{
        temp=YZF_FALSE;
    }
#endif
    yzl_softport_i2c_delay(i2c);
    YLLOW(i2c->SCL);
    return temp;
}
uint8_t yzl_softport_i2c_byte_in(YZL_Soft_I2C *i2C){
    uint8_t data=0;
    for(uint8_t i=0;i<8;i++){
        data<<=1;
        data|= yzl_softport_i2c_read_bit(i2C,0);
    }
    return data;
}
/**
 * _
 *  \ __
 * _____
 *      \
 * */
YZF_RESULT yzl_softport_i2c_start(YZL_Soft_I2C *i2c){
    YLHIGH(i2c->SDA);
    YLHIGH(i2c->SCL);
    yzl_softport_i2c_delay(i2c);
    YLLOW(i2c->SDA);
    yzl_softport_i2c_delay(i2c);
    YLLOW(i2c->SCL);
    return YZF_OK;
}
/**
 *      __
 * ____/
 *   ______
 * /
 * */
YZF_RESULT yzl_softport_i2c_stop(YZL_Soft_I2C *i2c){
    YLHIGH(i2c->SCL);
    yzl_softport_i2c_delay(i2c);
    YLHIGH(i2c->SDA);
    yzl_softport_i2c_delay(i2c);
    return YZF_OK;
}
/**
 *
 *  __?__
 * /     \
 * */
YZF_BOOL yzl_softport_i2c_wait_ack(YZL_Soft_I2C *i2c){
    YZF_BOOL temp;
    yzl_softport_i2c_sda_in(i2c);
    YLHIGH(i2c->SCL);
    yzl_softport_i2c_delay(i2c);
#if YZL_USE_GPIO_WITH_HAL
    if(HAL_GPIO_ReadPin(i2c->SDA.port,i2c->SDA.pin)==GPIO_PIN_SET){
        temp=YZF_FALSE;
    }else{
        temp=YZF_TRUE;
    }
#else
    if(yzf_gpio_get(i2c->SDA.port,i2c->SDA.pin)){
        temp=YZF_FALSE;
    }else{
        temp=YZF_TRUE;
    }
#endif
    yzl_softport_i2c_delay(i2c);
    YLLOW(i2c->SCL);
    yzl_softport_i2c_sda_out(i2c);
    return temp;
}
/**
 *
 * \ ______ /
 *    ____
 *  /      \
 * */
YZF_RESULT yzl_softport_i2c_ack(YZL_Soft_I2C *i2c){
    yzl_softport_i2c_sda_out(i2c);
    YLLOW(i2c->SDA);
    YLHIGH(i2c->SCL);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    YLLOW(i2c->SCL);
    YLHIGH(i2c->SDA);
    yzl_softport_i2c_sda_in(i2c);
    return YZF_OK;
}
/**
 * ___________
 *
 *   _______
 * /         \
 * */
YZF_RESULT yzl_softport_i2c_no_ack(YZL_Soft_I2C *i2c){
    yzl_softport_i2c_sda_out(i2c);
    YLHIGH(i2c->SDA);
    YLHIGH(i2c->SCL);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    YLLOW(i2c->SCL);
    YLHIGH(i2c->SDA);
    yzl_softport_i2c_sda_in(i2c);
    return YZF_OK;
}
/**
 * ________
 *
 * ________
 *
 * */
YZF_RESULT yzl_softport_i2c_init(YZL_Soft_I2C *i2c){
#if YZL_USE_GPIO_WITH_HAL
    GPIO_sda.Mode= GPIO_MODE_OUTPUT_PP;
    GPIO_sda.Pull= GPIO_PULLUP;
    GPIO_sda.Speed= GPIO_SPEED_FREQ_HIGH;
    GPIO_sda.Pin = i2c->SCL.pin;
    HAL_GPIO_Init(i2c->SCL.port,&GPIO_sda);
    YLHIGH(i2c->SCL);
    GPIO_sda.Pin = i2c->SDA.pin;
    HAL_GPIO_Init(i2c->SDA.port,&GPIO_sda);
    YLHIGH(i2c->SDA);
#else
    YLGPIO(i2c->SCL);
    yzf_gpio_open_clock_();
    yzf_gpio_set_PP_();
    yzf_gpio_set_HIGH_();
    yzf_gpio_set_1_();
    YLGPIO(i2c->SDA);
    yzf_gpio_open_clock_();
    yzl_softport_i2c_sda_out(i2c);
    yzf_gpio_set_HIGH_();
    yzf_gpio_set_1_();
#endif
    return YZF_OK;
}
YZF_RESULT yzl_softport_i2c_write(YZL_Soft_I2C *i2c,uint8_t addr,uint8_t *data,uint16_t len){

    yzl_softport_i2c_sda_out(i2c);
    yzl_softport_i2c_start(i2c);
    yzl_softport_i2c_byte(i2c,(addr<<1)+0);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    YZF_BOOL temp= yzl_softport_i2c_wait_ack(i2c);
    if(temp==YZF_FALSE){
        return YZF_ERROR;
    }
    for (int i = 0; i < len; ++i) {
        yzl_softport_i2c_byte(i2c,data[i]);
        yzl_softport_i2c_delay(i2c);
        yzl_softport_i2c_delay(i2c);
        temp= yzl_softport_i2c_wait_ack(i2c);
        if(temp==YZF_FALSE){
            return YZF_ERROR;
        }
    }
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_stop(i2c);
    return YZF_OK;
}
YZF_RESULT yzl_softport_i2c_param_write(YZL_Soft_I2C *i2c,uint8_t addr,uint8_t *sendData,uint8_t sendLen,uint8_t *data,uint16_t len){
    yzl_softport_i2c_sda_out(i2c);
    yzl_softport_i2c_start(i2c);
    yzl_softport_i2c_byte(i2c,(addr<<1)+0);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    YZF_BOOL temp= yzl_softport_i2c_wait_ack(i2c);
    if(temp==YZF_FALSE){
        return YZF_ERROR;
    }
    for (int i = 0; i < sendLen; i++) {
        yzl_softport_i2c_byte(i2c,sendData[i]);
        yzl_softport_i2c_delay(i2c);
        yzl_softport_i2c_delay(i2c);
        temp= yzl_softport_i2c_wait_ack(i2c);
        if(temp==YZF_FALSE){
            return YZF_ERROR;
        }
    }
    for (int i = 0; i < len; i++) {
        yzl_softport_i2c_byte(i2c,data[i]);
        yzl_softport_i2c_delay(i2c);
        yzl_softport_i2c_delay(i2c);
        temp= yzl_softport_i2c_wait_ack(i2c);
        if(temp==YZF_FALSE){
            return YZF_ERROR;
        }
    }
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_stop(i2c);
    return YZF_OK;
}
YZF_RESULT yzl_softport_i2c_read(YZL_Soft_I2C *i2c,uint8_t addr,uint8_t *sendData,uint8_t sendLen,uint8_t *data,uint16_t len){
    yzl_softport_i2c_sda_out(i2c);
    yzl_softport_i2c_start(i2c);
    yzl_softport_i2c_byte(i2c,(addr<<1)+0);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    YZF_BOOL temp= yzl_softport_i2c_wait_ack(i2c);
    if(temp==YZF_FALSE){
        return YZF_ERROR;
    }

    for (int i = 0; i < sendLen; i++) {
        yzl_softport_i2c_byte(i2c,sendData[i]);
        yzl_softport_i2c_delay(i2c);
        yzl_softport_i2c_delay(i2c);
        temp= yzl_softport_i2c_wait_ack(i2c);
        if(temp==YZF_FALSE){
            return YZF_ERROR;
        }
    }

    yzl_softport_i2c_start(i2c);
    yzl_softport_i2c_byte(i2c,(addr<<1)+1);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    temp= yzl_softport_i2c_wait_ack(i2c);
    if(temp==YZF_FALSE){
        return YZF_ERROR;
    }
    yzl_softport_i2c_sda_in(i2c);
    for (int i = 0; i < len; i++) {
        data[i]=yzl_softport_i2c_byte_in(i2c);
        yzl_softport_i2c_delay(i2c);
        yzl_softport_i2c_delay(i2c);
        if(i!=i-1){
            yzl_softport_i2c_ack(i2c);
        }else{
            yzl_softport_i2c_no_ack(i2c);
        }
    }
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_delay(i2c);
    yzl_softport_i2c_stop(i2c);
    return YZF_OK;
}

#endif