//
// Created by 32827 on 2024/12/22.
//

#ifndef STM32H723ZGTXCOVER_YZL_SPI_W25Q128_H
#define STM32H723ZGTXCOVER_YZL_SPI_W25Q128_H

#include "yzx_base.h"
#include "yzl.h"
#define W25Q128_CS(x)   do{ x ? \
                                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET): \
                                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); \
                        }while(0)

/* 宏定义指令 */
#define FLASH_ManufactDeviceID                  0x90
#define FLASH_WriteEnable                       0x06
#define FLASH_ReadStatusReg1                    0x05
#define FLASH_ReadData                          0x03
#define FLASH_PageProgram                       0x02
#define FLASH_SectorErase                       0x20
#define FLASH_DummyByte                         0xFF

void w25q128_init(void);
void w25q128_read_data(uint32_t address, uint8_t *data, uint32_t size);
void w25q128_write_page(uint32_t address, uint8_t *data, uint16_t size);
void w25q128_erase_sector(uint32_t address);
void get_w25q128_id(void);

#endif //STM32H723ZGTXCOVER_YZL_SPI_W25Q128_H
