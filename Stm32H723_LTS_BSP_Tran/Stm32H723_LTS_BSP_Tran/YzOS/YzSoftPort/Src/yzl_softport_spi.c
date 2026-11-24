//
// Created by 32827 on 2024/1/10.
//
#include "yzl_softport_spi.h"
#if USE_SOFT_PORT && YZL_SOFT_PORT_SPI
YZF_RESULT yzl_softport_spi_init(YZL_Soft_SPI *spi){
#if YZL_USE_GPIO_WITH_HAL
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = spi->mosi.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(spi->mosi.port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = spi->clk.pin;
    HAL_GPIO_Init(spi->clk.port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = spi->cs.pin;
    HAL_GPIO_Init(spi->cs.port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = spi->miso.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(spi->miso.port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(spi->cs.port, spi->cs.pin, GPIO_PIN_SET);//nss
    if((spi->mode&0b10)!=0){
        HAL_GPIO_WritePin(spi->clk.port, spi->clk.pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(spi->clk.port, spi->clk.pin, GPIO_PIN_RESET);
    }
#else
    YLGPIO(spi->mosi)
    yzf_gpio_open_clock_();
    yzf_gpio_set_PP_();
    yzf_gpio_set_HIGH_();
    YLGPIO(spi->clk)
    yzf_gpio_open_clock_();
    yzf_gpio_set_PP_();
    yzf_gpio_set_HIGH_();
    YLGPIO(spi->cs)
    yzf_gpio_open_clock_();
    yzf_gpio_set_PP_();
    yzf_gpio_set_HIGH_();
    YLGPIO(spi->miso)
    yzf_gpio_open_clock_();
    yzf_gpio_set_IN_PULL_UP_();

    YLGPIO(spi->cs)
    yzf_gpio_set_1_();
    YLGPIO(spi->clk)
    if((spi->mode&0b10)!=0){
        yzf_gpio_set_1_();
    }else{
        yzf_gpio_set_0_();
    }
#endif
    return YZF_OK;
}
YZF_RESULT yzl_softport_spi_start(YZL_Soft_SPI *spi){
    //发送开始信号
#if YZL_USE_GPIO_WITH_HAL
    HAL_GPIO_WritePin(spi->cs.port, spi->cs.pin, GPIO_PIN_RESET);
#else
    YLGPIO(spi->cs)
    yzf_gpio_set_0_();
#endif
    return YZF_OK;
}
YZF_RESULT yzl_softport_spi_end(YZL_Soft_SPI *spi){
    //发送开始信号
#if YZL_USE_GPIO_WITH_HAL
    HAL_GPIO_WritePin(spi->cs.port, spi->cs.pin, GPIO_PIN_SET);
#else
    YLGPIO(spi->cs)
    yzf_gpio_set_1_();
#endif
    return YZF_OK;
}
YZF_RESULT yzl_softport_spi_clk_s_line(YZL_Soft_SPI *spi){
#if YZL_USE_GPIO_WITH_HAL
    if((spi->mode&0b10)!=0){
        HAL_GPIO_WritePin(spi->clk.port, spi->clk.pin, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(spi->clk.port, spi->clk.pin, GPIO_PIN_SET);
    }
#else
    YLGPIO(spi->clk)
    if((spi->mode&0b10)!=0){
        yzf_gpio_set_0_();
    }else{
        yzf_gpio_set_1_();
    }
#endif
    return YZF_OK;
}
YZF_RESULT yzl_softport_spi_clk_d_line(YZL_Soft_SPI *spi){
#if YZL_USE_GPIO_WITH_HAL
    if((spi->mode&0b10)!=0){
        HAL_GPIO_WritePin(spi->clk.port, spi->clk.pin, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(spi->clk.port, spi->clk.pin, GPIO_PIN_RESET);
    }
#else
    YLGPIO(spi->clk)
    if((spi->mode&0b10)!=0){
        yzf_gpio_set_1_();
    }else{
        yzf_gpio_set_0_();
    }
#endif
    return YZF_OK;
}
YZF_RESULT yzl_softport_spi_set_data8(YZL_Soft_SPI *spi,uint8_t data,uint8_t index){
#if YZL_USE_GPIO_WITH_HAL
    if(spi->MSB==YZF_TRUE){
        if ((data & 0b1<<(7-index)) != 0) {   //跳变
            HAL_GPIO_WritePin(spi->mosi.port, spi->mosi.pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(spi->mosi.port, spi->mosi.pin, GPIO_PIN_RESET);
        }
    }else{
        if ((data & 0b1<<index) != 0) {   //跳变
            HAL_GPIO_WritePin(spi->mosi.port, spi->mosi.pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(spi->mosi.port, spi->mosi.pin, GPIO_PIN_RESET);
        }
    }
#else
    YLGPIO(spi->mosi)
    if(spi->MSB==YZF_TRUE){
        if ((data & 0b1<<(7-index)) != 0) {   //跳变
            yzf_gpio_set_1_();
        } else {
            yzf_gpio_set_0_();
        }
    }else{
        if ((data & 0b1<<index) != 0) {   //跳变
            yzf_gpio_set_1_();
        } else {
            yzf_gpio_set_0_();
        }
    }
#endif
    return YZF_OK;
}
YZF_RESULT yzl_softport_spi_set_data16(YZL_Soft_SPI *spi,uint8_t data,uint16_t index){
#if YZL_USE_GPIO_WITH_HAL
    if(spi->MSB==YZF_TRUE){
        if ((data & 0b1<<(15-index)) != 0) {   //跳变
            HAL_GPIO_WritePin(spi->mosi.port, spi->mosi.pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(spi->mosi.port, spi->mosi.pin, GPIO_PIN_RESET);
        }
    }else{
        if ((data & 0b1<<index) != 0) {   //跳变
            HAL_GPIO_WritePin(spi->mosi.port, spi->mosi.pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(spi->mosi.port, spi->mosi.pin, GPIO_PIN_RESET);
        }
    }
#else
    YLGPIO(spi->mosi)
    if(spi->MSB==YZF_TRUE){
        if ((data & 0b1<<(15-index)) != 0) {   //跳变
            yzf_gpio_set_1_();
        } else {
            yzf_gpio_set_0_();
        }
    }else{
        if ((data & 0b1<<index) != 0) {   //跳变
            yzf_gpio_set_1_();
        } else {
            yzf_gpio_set_0_();
        }
    }
#endif
    return YZF_OK;
}
uint8_t yzl_softport_spi_transmit_byte8(YZL_Soft_SPI *spi,uint8_t data){
    uint8_t data_temp=0;
    yzl_softport_delayUS(5);
    if((spi->mode&0b01)!=0){
        for (int i = 0; i < 8; i++) {
            yzl_softport_spi_set_data8(spi,data,i);//数据
            yzl_softport_spi_clk_s_line(spi);//奇数
            yzl_softport_delayUS(5);
            yzl_softport_spi_clk_d_line(spi);//偶数
            yzl_softport_delayUS(5);
#if YZL_USE_GPIO_WITH_HAL
            data_temp |=(HAL_GPIO_ReadPin(spi->miso.port, spi->miso.pin)==GPIO_PIN_SET?1:0)<<(7-i);//采集
#else
            YLGPIO(spi->miso)
            data_temp |=(yzf_gpio_get_()==YZF_TRUE?1:0)<<(7-i);//采集
#endif
        }
    }else {
        for (int i = 0; i < 8; i++) {
            yzl_softport_spi_set_data8(spi,data,i);//数据
            yzl_softport_delayUS(5);
            yzl_softport_spi_clk_s_line(spi);//奇数
            yzl_softport_delayUS(5);
#if YZL_USE_GPIO_WITH_HAL
            data_temp |=(HAL_GPIO_ReadPin(spi->miso.port, spi->miso.pin)==GPIO_PIN_SET?1:0)<<(7-i);//采集
#else
            YLGPIO(spi->miso)
            data_temp |=(yzf_gpio_get_()==YZF_TRUE?1:0)<<(7-i);//采集
#endif
            yzl_softport_spi_clk_d_line(spi);//偶数
        }
    }
    yzl_softport_delayUS(5);

    return data_temp;
}
uint16_t yzl_softport_spi_transmit_byte16(YZL_Soft_SPI *spi,uint16_t data){

    uint16_t data_temp=0;
    yzl_softport_delayUS(5);
    if((spi->mode&0b01)!=0){
        for (int i = 0; i < 16; i++) {
            yzl_softport_spi_clk_s_line(spi);//奇数
            yzl_softport_spi_set_data16(spi,data,i);//数据
            yzl_softport_delayUS(5);
            yzl_softport_spi_clk_d_line(spi);//偶数
            yzl_softport_delayUS(5);
#if YZL_USE_GPIO_WITH_HAL
            data_temp |=(HAL_GPIO_ReadPin(spi->miso.port, spi->miso.pin)==GPIO_PIN_SET?1:0)<<(15-i);//采集
#else
            YLGPIO(spi->miso)
            data_temp |=(yzf_gpio_get_()==YZF_TRUE?1:0)<<(15-i);//采集
#endif
        }
    }else {
        for (int i = 0; i < 16; i++) {
            yzl_softport_spi_set_data16(spi,data,i);//数据
            yzl_softport_delayUS(5);
            yzl_softport_spi_clk_s_line(spi);//奇数
            yzl_softport_delayUS(5);
#if YZL_USE_GPIO_WITH_HAL
            data_temp |=(HAL_GPIO_ReadPin(spi->miso.port, spi->miso.pin)==GPIO_PIN_SET?1:0)<<(15-i);//采集
#else
            YLGPIO(spi->miso)
            data_temp |=(yzf_gpio_get_()==YZF_TRUE?1:0)<<(15-i);//采集
#endif
            yzl_softport_spi_clk_d_line(spi);//偶数
        }
    }
    yzl_softport_delayUS(5);
    return data_temp;
}
YZF_RESULT yzl_softport_spi_slave_init(YZL_Soft_SPI *spi){
#if YZL_USE_GPIO_WITH_HAL
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin= spi->mosi.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(spi->mosi.port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin= spi->clk.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(spi->clk.port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin= spi->cs.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(spi->cs.port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin= spi->miso.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(spi->miso.port, &GPIO_InitStruct);
    return YZF_OK;
#else
    YLGPIO(spi->mosi)
    yzf_gpio_open_clock_();
    yzf_gpio_set_IN_PULL_UP_();
    yzf_gpio_set_HIGH_();
    YLGPIO(spi->clk)
    yzf_gpio_open_clock_();
    yzf_gpio_set_IN_PULL_UP_();
    yzf_gpio_set_HIGH_();
    YLGPIO(spi->cs)
    yzf_gpio_open_clock_();
    yzf_gpio_set_IN_PULL_UP_();
    yzf_gpio_set_HIGH_();
    YLGPIO(spi->miso)
    yzf_gpio_open_clock_();
    yzf_gpio_set_Pull_Up_();
    yzf_gpio_set_PP_();
    yzf_gpio_set_HIGH_();
    yzf_gpio_set_1_();
    return YZF_OK;
#endif
}
uint8_t yzl_softport_spi_slave_transmit_byte8(YZL_Soft_SPI *spi, uint8_t data){
    uint8_t recvData;
#if YZL_USE_GPIO_WITH_HAL
    while (!HAL_GPIO_ReadPin(spi->cs.port, spi->cs.pin));
    for (int i = 0; i < 8; i++) {
        while (!HAL_GPIO_ReadPin(spi->clk.port, spi->clk.pin));
        if(data&0x80){
            HAL_GPIO_WritePin(spi->miso.port, spi->miso.pin, GPIO_PIN_SET);
        }else{
            HAL_GPIO_WritePin(spi->miso.port, spi->miso.pin, GPIO_PIN_RESET);
        }
        while (HAL_GPIO_ReadPin(spi->clk.port, spi->clk.pin));
        recvData = HAL_GPIO_ReadPin(spi->mosi.port, spi->mosi.pin);
        data <<= 1;
    }
#else
    YLGPIO(spi->cs)
    while (!yzf_gpio_get_());
    YLGPIO(spi->clk)
    for(int i=0;i<8;i++){
        while (yzf_gpio_get_());
        if(data&0x80){
            yzf_gpio_set_1(spi->miso.port,spi->miso.pin);
        }else{
            yzf_gpio_set_0(spi->miso.port,spi->miso.pin);
        }
        while (!yzf_gpio_get_());
        recvData = yzf_gpio_get(spi->mosi.port,spi->mosi.pin);
        data <<= 1;
    }
#endif
    return recvData;
}
#endif