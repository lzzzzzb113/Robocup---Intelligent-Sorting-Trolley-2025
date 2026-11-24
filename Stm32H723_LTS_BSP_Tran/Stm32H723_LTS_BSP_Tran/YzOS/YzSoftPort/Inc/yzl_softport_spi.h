//
// Created by 32827 on 2024/1/10.
//

#ifndef STM32OSCOVER_YZL_SOFTPORT_SPI_H
#define STM32OSCOVER_YZL_SOFTPORT_SPI_H
#include "yzl_softport.h"

#if USE_SOFT_PORT && YZL_SOFT_PORT_SPI
enum yzl_softport_spi_mode{
    YZL_SOFTPORT_SPI_MODE_0=0b00,
    YZL_SOFTPORT_SPI_MODE_1=0b01,
    YZL_SOFTPORT_SPI_MODE_2=0b10,
    YZL_SOFTPORT_SPI_MODE_3=0b11
};
typedef struct {
    enum yzl_softport_spi_mode mode;
    YZF_BOOL MSB;
    YZL_GPIO cs;
    YZL_GPIO clk;
    YZL_GPIO mosi;
    YZL_GPIO miso;
} YZL_Soft_SPI;

#ifdef __cplusplus
extern "C" {
#endif

YZF_RESULT yzl_softport_spi_init(YZL_Soft_SPI *spi);

YZF_RESULT yzl_softport_spi_start(YZL_Soft_SPI *spi);

YZF_RESULT yzl_softport_spi_end(YZL_Soft_SPI *spi);

YZF_RESULT yzl_softport_spi_clk_s_line(YZL_Soft_SPI *spi);

YZF_RESULT yzl_softport_spi_clk_d_line(YZL_Soft_SPI *spi);

YZF_RESULT yzl_softport_spi_set_data8(YZL_Soft_SPI *spi, uint8_t data, uint8_t index);

YZF_RESULT yzl_softport_spi_set_data16(YZL_Soft_SPI *spi, uint8_t data, uint16_t index);

uint8_t yzl_softport_spi_transmit_byte8(YZL_Soft_SPI *spi, uint8_t data);

uint16_t yzl_softport_spi_transmit_byte16(YZL_Soft_SPI *spi, uint16_t data);

YZF_RESULT yzl_softport_spi_slave_init(YZL_Soft_SPI *spi);

uint8_t yzl_softport_spi_slave_transmit_byte8(YZL_Soft_SPI *spi, uint8_t data);
#ifdef __cplusplus
}
#endif

#endif
#endif //STM32OSCOVER_YZL_SOFTPORT_SPI_H
