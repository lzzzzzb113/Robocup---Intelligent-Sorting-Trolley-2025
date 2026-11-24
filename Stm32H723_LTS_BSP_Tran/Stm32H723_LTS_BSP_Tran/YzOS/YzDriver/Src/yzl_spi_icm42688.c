//
// Created by 32827 on 2024/10/26.
//
#include "yzl_spi_icm42688.h"
#if ICM42688_SPI_SOFT==OFF


YZF_RESULT yzl_icm42688_init(yzl_icm42688_handle* spi){
#if YZL_USE_SPI_WITH_HAL
    YLHIGH(spi->spi.cs);
#else
#endif
    uint8_t icm52688_check;
    uint8_t time=50;
    while(time--){
        yzl_icm42688_read_regs(spi, ICM42688_WHO_AM_I, &icm52688_check, 1);
        if(icm52688_check==0x47){
            yz_info("找到ICM42688。\n");
            //TODO: Init Regs

            uint8_t dataParam[4]={0x0};
            //复位
            yzl_icm42688_write_regs(spi, ICM42688_PWR_MGMT0, dataParam, 1);
            yzl_softport_delayMS(10);

            //设置加速度
//            icm42688_afs afs= ICM42688_AFS_4G;
//            icm42688_aodr aodr= ICM42688_AODR_1000HZ;
            dataParam[0] = (spi->afs << 5) | (spi->aodr + 1);
            yzl_icm42688_write_regs(spi, ICM42688_ACCEL_CONFIG0, dataParam, 1);

            //设置角速度
//            icm42688_gfs gfs= ICM42688_GFS_125DPS;
//            icm42688_godr godr= ICM42688_GODR_1000HZ;

            dataParam[0] = (spi->gfs << 5) | (spi->godr + 1);
            yzl_icm42688_write_regs(spi, ICM42688_GYRO_CONFIG0, dataParam, 1);

            //设置为低噪声模式
            dataParam[0] = 0x0f;
            yzl_icm42688_write_regs(spi, ICM42688_PWR_MGMT0, dataParam, 1);
            yzl_softport_delayMS(10);
            return YZF_OK;
        }else{
            yz_error("未找到ICM42688，请检查硬件连接。\n");
            yzl_softport_delayMS(10);
        }
    }
    return YZF_ERROR;
}
YZF_RESULT yzl_icm42688_set_gyro(yzl_icm42688_handle* spi){
    uint8_t dataParam = (spi->gfs << 5) | (spi->godr + 1);
    yzl_icm42688_write_regs(spi, ICM42688_GYRO_CONFIG0, &dataParam, 1);
    return YZF_OK;
}
YZF_RESULT yzl_icm42688_read_regs(yzl_icm42688_handle* spi, uint8_t reg, uint8_t *data, uint8_t len){

#if YZL_USE_SPI_WITH_HAL
    YLLOW(spi->spi.cs);
    reg = reg|0x80;
    HAL_SPI_Transmit(spi->hard_spi, &reg, 1, 100);
    HAL_SPI_Receive(spi->hard_spi, data,  len, 100);
    YLHIGH(spi->spi.cs);
#else
    YLGPIO(spi->spi.cs)
    yz_spi_full_lines_begin(spi->hard_spi);
    yzf_gpio_set_0_();

    yz_spi_full_lines_conv8(spi->hard_spi, reg|0x80);

    for(int i=0;i<len;i++){
        data[i]=yz_spi_full_lines_conv8(spi->hard_spi, 0xff);
    }

    yzf_gpio_set_1_();
    yz_spi_full_lines_end(spi->hard_spi);
#endif
    return YZF_OK;
}
YZF_RESULT yzl_icm42688_write_regs(yzl_icm42688_handle* spi, uint8_t reg, uint8_t *data, uint8_t len){
#if YZL_USE_SPI_WITH_HAL
    YLLOW(spi->spi.cs);
    reg = reg&0x7f;
    HAL_SPI_Transmit(spi->hard_spi, &reg, 1, 100);
    HAL_SPI_Transmit(spi->hard_spi, data,  len, 100);
    YLHIGH(spi->spi.cs);
#else
    YLGPIO(spi->spi.cs)
    yz_spi_full_lines_begin(spi->hard_spi);
    yzf_gpio_set_0_();

    yz_spi_full_lines_conv8(spi->hard_spi, reg&0x7f);

    for(int i=0;i<len;i++){
        yz_spi_full_lines_conv8(spi->hard_spi, data[i]);
    }

    yzf_gpio_set_1_();
    yz_spi_full_lines_end(spi->hard_spi);
#endif
    return YZF_OK;
}
YZF_RESULT yzl_icm42688_get_acc(yzl_icm42688_handle* spi, int16_t *acc){
    uint8_t data[6];

    yzl_icm42688_read_regs(spi, ICM42688_ACCEL_DATA_X1, data, 6);
    acc[0] = (short int)(((short int)data[0] << 8) | data[1]);
    acc[1] = (short int)(((short int)data[2] << 8) | data[3]);
    acc[2] = (short int)(((short int)data[4] << 8) | data[5]);
    return YZF_OK;
}
YZF_RESULT yzl_icm42688_get_gyro(yzl_icm42688_handle* spi, int16_t *gyro){
    uint8_t data[6];

    yzl_icm42688_read_regs(spi, ICM42688_GYRO_DATA_X1, data, 6);
    gyro[0] = (short int)(((short int)data[0] << 8) | data[1]);
    gyro[1] = (short int)(((short int)data[2] << 8) | data[3]);
    gyro[2] = (short int)(((short int)data[4] << 8) | data[5]);
    return YZF_OK;
}
#else
//TODO: USE SOFT SPI
#endif