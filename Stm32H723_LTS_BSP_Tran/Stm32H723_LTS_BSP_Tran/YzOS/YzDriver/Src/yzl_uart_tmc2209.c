//
// Created by 32827 on 2025/7/15.
//
#include "yzl_uart_tmc2209.h"
#include "yz_uart.h"
#include "yzl_softport.h"

YZF_RESULT yzl_uart_tmc2209_get_next_response(YZF_UART_POINTER uart,TMC2209Response *response){
    uint8_t insert_index=0;
    uint8_t step=0;
    while(yzf_area_recv_get_size(yz_uart_receive_IT_RECV_get(uart))>0 || step != 0){
        switch (step) {
            case 0: //Check Start
                if(yzf_area_recv_get(yz_uart_receive_IT_RECV_get(uart))==0x05){
                    response->raw[insert_index] = 0x05;
                    insert_index++;
                    step++;
                }
                break;
            case 1: //Check Address is Master
                if(yzf_area_recv_get_size(yz_uart_receive_IT_RECV_get(uart))>0){
                    if(yzf_area_recv_get(yz_uart_receive_IT_RECV_get(uart))==0xff){//for Master
                        response->raw[insert_index] = 0xff;
                        insert_index++;
                        step++;
                    }else{
                        step=0;
                        insert_index=0;
                    }
                }else{ // Wait for more data
                    delay_ms(1);
                }
                break;
            case 2: //Check Size And Copy Data
                if(yzf_area_recv_get_size(yz_uart_receive_IT_RECV_get(uart))>=0x06){//至少还有6个字节
                    for(;insert_index<8;insert_index++){
                        response->raw[insert_index] = yzf_area_recv_get(yz_uart_receive_IT_RECV_get(uart));
                    }
                    response->data = response->raw[3]<<24 | response->raw[4]<<16 | response->raw[5]<<8 | response->raw[6];
                    return YZF_OK;
                }else{ // Wait for more data
                    delay_ms(1);
                }
                break;
            default:
                break;
        }
    }
    return YZF_ERROR;
}
uint8_t yzl_uart_tmc2209_crc(uint8_t *data, uint8_t len){
    int i, j;
    uint8_t crc = 0; // CRC 存储在数据包的最后一个字节
    uint8_t currentByte;
    for (i = 0; i < (len-1); i++) { // 处理除最后一个字节外的所有字节
        currentByte = data[i];
        for (j = 0; j < 8; j++) { // 处理当前字节的每一位
            if ((crc >> 7) ^ (currentByte & 0x01)) {
                crc = (crc << 1) ^ 0x07; // 如果 CRC 高位与当前字节最低位异或结果为 1，则 CRC 左移并异或多项式 0x07
            } else {
                crc = (crc << 1); // 否则，CRC 仅左移
            }
            currentByte = currentByte >> 1; // 当前字节右移处理下一位
        }
    }
    data[len-1] = crc; // 将计算得到的 CRC 值写入最后一个字节
    return crc;
}
YZF_RESULT yzl_uart_tmc2209_init(YZF_UART_POINTER uart,uint8_t address){
    //TODO: remove hal and use native
    uint8_t regWriteCmd[8]={0x05,address,0x00|0x80,0x00,0x00,0x00,0x81,0x00};
    yzl_uart_tmc2209_crc(regWriteCmd,8);
    yz_uart_transmit(uart,regWriteCmd,8);

    HAL_Delay(100);

    regWriteCmd[2] = 0x00;
    regWriteCmd[3] = 0x00;
    yzl_uart_tmc2209_crc(regWriteCmd,4);
    yz_uart_transmit(uart,regWriteCmd,4);
    TMC2209Response regData;
    while(yzl_uart_tmc2209_get_next_response(uart,&regData)!=YZF_OK);

    HAL_Delay(100);

    regWriteCmd[2] = 0x6C;
    regWriteCmd[3] = 0x00;
    yzl_uart_tmc2209_crc(regWriteCmd,4);
    yz_uart_transmit(uart,regWriteCmd,4);
    while(yzl_uart_tmc2209_get_next_response(uart,&regData)!=YZF_OK);

    regData.raw[3] |= 0x00;
    regData.raw[2] |= 0x80;
    regData.raw[1] = address;
    yzl_uart_tmc2209_crc(regData.raw,8);
    yz_uart_transmit(uart,regData.raw,8);

    return YZF_OK;
}