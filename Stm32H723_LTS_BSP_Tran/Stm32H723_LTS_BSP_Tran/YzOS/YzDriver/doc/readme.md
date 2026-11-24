# ICM42688 SPI 驱动

```c
//使用列子
yzl_icm42688_handle icm42688={
    0,
    {
        YZL_SOFTPORT_SPI_MODE_0,
        YZF_TRUE,
        {GPIO_PIN_6,GPIOB},
        {GPIO_PIN_3,GPIOB},
        {GPIO_PIN_5,GPIOB},
        {GPIO_PIN_4,GPIOB}
    },
    ICM42688_AFS_4G,
    ICM42688_AODR_1000HZ,
    ICM42688_GFS_125DPS,
    ICM42688_GODR_1000HZ
};

void init(){
    icm42688.hard_spi=yz_hal_get_spi3(); // use with hal
    icm42688.hard_spi=SPI3; // use with YzFrame
    icm42688.hard_spi=0;    //don't care.use with soft spi
    
    yzl_icm42688_init(&icm42688);
    
    //another code
}
```

# TCS34727 I2C 驱动

```c
YZLSensorDataCRGB sensor;
void init(){
    yzl_i2c_tcs34727_init(I2C4);
    yzl_i2c_tcs34727_get_rgb(I2C4,&sensor)
}
```

# TMC2209 UART 驱动

```c
void init(){
    yz_uart_receive_IT_init(UART5);
    yzl_uart_tmc2209_init(UART5,0x0);   
}
```