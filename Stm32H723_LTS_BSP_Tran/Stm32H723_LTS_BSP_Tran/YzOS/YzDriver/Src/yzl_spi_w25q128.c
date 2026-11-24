//
// Created by 32827 on 2024/12/22.
//
#include "yzl_spi_w25q128.h"
#include "yz_hal.h"
SPI_HandleTypeDef spi_handle = {0};
void w25q128_spi_init(void)
{
    spi_handle.Instance = SPI1;
    spi_handle.Init.Mode = SPI_MODE_MASTER;
    spi_handle.Init.Direction = SPI_DIRECTION_2LINES;
    spi_handle.Init.DataSize = SPI_DATASIZE_8BIT;
    spi_handle.Init.CLKPolarity = SPI_POLARITY_LOW;              /* CPOL = 0 */
    spi_handle.Init.CLKPhase = SPI_PHASE_1EDGE;                  /* CPHA = 0 */
    spi_handle.Init.NSS = SPI_NSS_SOFT;
    spi_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    spi_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi_handle.Init.TIMode = SPI_TIMODE_DISABLE;
    spi_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi_handle.Init.CRCPolynomial = 7;
    HAL_SPI_Init(&spi_handle);
}

/*
    __weak void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi) 为可重写的弱函数
    在 HAL_SPI_Init 中被调用
*/
//void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//{
//    if(hspi->Instance == SPI1)
//    {
//        GPIO_InitTypeDef gpio_initstruct;
//        //打开时钟
//        __HAL_RCC_GPIOA_CLK_ENABLE();
//        __HAL_RCC_SPI1_CLK_ENABLE();
//
//        //调用GPIO初始化函数
//        gpio_initstruct.Pin = GPIO_PIN_4;
//        gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
//        gpio_initstruct.Pull = GPIO_PULLUP;
//        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
//        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
//
//        gpio_initstruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
//        gpio_initstruct.Mode = GPIO_MODE_AF_PP;
//        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
//
//        gpio_initstruct.Pin = GPIO_PIN_6;
//        gpio_initstruct.Mode = GPIO_MODE_INPUT;
//        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
//    }
//}


/*
    HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t
                    *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
    hspi：   指向SPI外设的句柄（handle）。
    pTxData：要发送的数据缓冲区指针。
    pRxData：接收数据的缓冲区指针。
    Size：   要发送/接收的数据字节数。
    Timeout：超时时间，以毫秒为单位。
*/
uint8_t w25q128_spi_swap_byte(uint8_t data)
{
    uint8_t recv_data = 0;
    HAL_SPI_TransmitReceive(&spi_handle, &data, &recv_data, 1, 1000);
    return recv_data;
}

uint16_t w25q128_read_id(void)
{
    uint16_t device_id = 0;
    W25Q128_CS(0);

    w25q128_spi_swap_byte(FLASH_ManufactDeviceID);
    w25q128_spi_swap_byte(0x00);
    w25q128_spi_swap_byte(0x00);
    w25q128_spi_swap_byte(0x00);
    device_id = w25q128_spi_swap_byte(FLASH_DummyByte) << 8;
    device_id |= w25q128_spi_swap_byte(FLASH_DummyByte);

    W25Q128_CS(1);
    return device_id;
}

void get_w25q128_id(void)
{
    spi_handle=*yz_hal_get_spi3();
    uint16_t flash_type;
    w25q128_spi_swap_byte(0xFF);         /* 清除DR的作用 */
    W25Q128_CS(1);                       /* 拉高片选 */
    flash_type = w25q128_read_id();      /* 读取FLASH ID. */
    if (flash_type == 0XEF17)            /* FLASH芯片号0XEF17 */
        yz_printf("型号为W25Q128芯片 0XEF17\r\n");
}


void w25q128_init(void)
{
//    w25q128_spi_init();  //再封装，不暴露接口
}

void w25q128_writ_enable(void)
{
    W25Q128_CS(0);
    w25q128_spi_swap_byte(FLASH_WriteEnable);
    W25Q128_CS(1);
}

uint8_t w25q128_read_sr1(void)
{
    uint8_t recv_data = 0;

    W25Q128_CS(0);
    w25q128_spi_swap_byte(FLASH_ReadStatusReg1);
    recv_data = w25q128_spi_swap_byte(FLASH_DummyByte);
    W25Q128_CS(1);

    return recv_data;
}

/* 等待BUSY位为0 */
void w25q128_wait_busy(void)
{
    while((w25q128_read_sr1() & 0x01) == 0x01);
}

void w25q128_send_address(uint32_t address)
{
    w25q128_spi_swap_byte(address >> 16);  /* 发送 bit23 ~ bit16 地址 */
    w25q128_spi_swap_byte(address >> 8);   /* 发送 bit15 ~ bit8 地址 */
    w25q128_spi_swap_byte(address);        /* 发送 bit7 ~ bit0 地址 */
}

void w25q128_read_data(uint32_t address, uint8_t *data, uint32_t size)
{
    uint32_t i = 0;
    W25Q128_CS(0);
    w25q128_spi_swap_byte(FLASH_ReadData);
    w25q128_send_address(address);

    for(i = 0; i < size; i++)
        data[i] = w25q128_spi_swap_byte(FLASH_DummyByte);
    W25Q128_CS(1);
}

void w25q128_write_page(uint32_t address, uint8_t *data, uint16_t size)
{
    uint16_t i = 0;
    w25q128_writ_enable();

    W25Q128_CS(0);
    w25q128_spi_swap_byte(FLASH_PageProgram);
    w25q128_send_address(address);

    for(i = 0; i < size; i++)
        w25q128_spi_swap_byte(data[i]);

    W25Q128_CS(1);
    //等待空闲
    w25q128_wait_busy();
}

void w25q128_erase_sector(uint32_t address)
{
    //写使能
    w25q128_writ_enable();
    //等待空闲
    w25q128_wait_busy();
    //拉低片选
    W25Q128_CS(0);
    //发送扇区擦除指令
    w25q128_spi_swap_byte(FLASH_SectorErase);
    //发送地址
    w25q128_send_address(address);
    //拉高片选
    W25Q128_CS(1);
    //等待空闲
    w25q128_wait_busy();
}