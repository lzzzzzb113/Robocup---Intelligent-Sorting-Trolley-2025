//
// Created by 32827 on 2023/11/29.
//
#include "yz_spi.h"
#include "yz_log.h"

void SPI1_Handler(YZF_GLOBAL_INDEX index){
    if(yzf_spi_flag_rxne(SPI1)){

    }
    if(yzf_spi_flag_txe(SPI1)){

    }
    if (yzf_spi_flag_ovr(SPI1)){
        yz_error("SPI 溢出错误\n");
    }
    if(yzf_spi_flag_crcerr(SPI1)){
        yz_error("SPI CRC错误标志\n");
    }
    if(yzf_spi_flag_modf(SPI1)){
        yz_error("SPI 主模式失效\n");
    }
}

YZF_RESULT yz_spi_init_bidi(YZF_SPI_POINTER spi){
    yzf_spi_open_source_clock(spi);

    yzf_spi_set_br(spi,YZF_SPI_PLCK_4);

    yzf_spi_set_cpol_HIGH(spi);
    yzf_spi_set_cpha_first(spi);

    yzf_spi_enable_ssm(spi);
    yzf_spi_select_ssi(spi);

    yzf_spi_set_MSBFIRST(spi);
    yzf_spi_crc_disable(spi);

    yzf_spi_set_DFF_8bits(spi);
    yzf_spi_set_crc_poly(spi,10);

    yzf_spi_disable_err_interrupt(spi);
//    yz_int_set_SPI1( SPI1_Handler,YZF_GLOBAL_SHEET_ERROR_INDEX);
    yzf_spi_disable_rxne_interrupt(spi);
    yzf_spi_disable_txe_interrupt(spi);

    yzf_spi_disable_RXONLY(spi);
    yzf_spi_enable_BIDI(spi);
    yzf_spi_set_master(spi);
    return YZF_OK;
}
YZF_RESULT yz_spi_transmit_bidi_ex(YZF_SPI_POINTER spi,uint8_t data){
    while (yzf_spi_flag_txp(spi)==YZF_FALSE);
    yzf_spi_write_byte(spi,data);
    return YZF_OK;
}
YZF_RESULT yz_spi_transmit_bidi_exn(YZF_SPI_POINTER spi,uint8_t *data,uint16_t len){
    while(len--){
        while (yzf_spi_flag_txp(spi)==YZF_FALSE);
        yzf_spi_write_byte(spi,*(data++));
    }
    return YZF_OK;
}
uint8_t yz_spi_recive_bidi_ex(YZF_SPI_POINTER spi){
    while (yzf_spi_flag_rxne(spi)==YZF_FALSE);
    return yzf_spi_read_byte(spi);
}
YZF_RESULT yz_spi_transmit_bidi(YZF_SPI_POINTER spi,uint8_t* data,uint16_t len){
    yzf_spi_enable_BIDIO(spi);
    yzf_spi_enable(spi);

    while(yzf_spi_flag_bsy(spi));
    yzf_spi_clear_all_flag(spi);
    yzf_spi_tran_count(spi,len);
    yzf_spi_tran_start(spi);

    for(uint16_t i=0;i<len;i++){
        while (yzf_spi_flag_txp(spi)==YZF_FALSE);
        yzf_spi_write_byte(spi,data[i]);
    }

    while (yzf_spi_flag_txe(spi)==YZF_FALSE);
    while (yzf_spi_flag_bsy(spi)==YZF_TRUE);
    yzf_spi_disable(spi);
    yzf_spi_disable_BIDIO(spi);
    return YZF_OK;
}
YZF_RESULT yz_spi_recive_bidi(YZF_SPI_POINTER spi,uint8_t* data,uint16_t len){
    yzf_spi_enable_RXONLY(spi);
    yzf_spi_enable(spi);
    while(yzf_spi_flag_bsy(spi));
    yzf_spi_clear_all_flag(spi);
    yzf_spi_tran_count(spi,len);
    yzf_spi_tran_start(spi);
    for(uint16_t i=0;i<len;i++){
        while (yzf_spi_flag_rxne(spi)==YZF_FALSE);
        *(data+i) = yzf_spi_read_byte(spi);
    }
    while(yzf_spi_flag_bsy(spi));
    yzf_spi_disable(spi);
    yzf_spi_disable_RXONLY(spi);
    return YZF_OK;
}


/// ------------------------- REWRITE -------------------------------
uint32_t spi_conv_count;
YZF_RESULT yz_spi_transmit_full_lines_dma(YZF_SPI_POINTER spi,YZF_DMA_POINTER dma,YZF_DMA_CHANNEL_POINTER channel,
                                          uint8_t channel_id,YZF_DMAMUX_CHANNEL_POINTER dmaMuxChannel,
                                          YZF_DMAMUX_STATUS_POINTER dmaMuxStatus,uint8_t muxReqId,uint8_t *data,uint16_t len){
    yzf_dma_clock_enable(dma);
    yzf_spi_disable_tx_dma(spi);
    yzf_dma_disable(channel);

    YZF_MODIFY_REG(dmaMuxChannel->CCR,DMAMUX_CxCR_DMAREQ_ID,muxReqId,DMAMUX_CxCR_DMAREQ_ID_Pos);
    dmaMuxStatus->CFR = 0x1UL <<  channel_id;



    yzf_dma_clear_all_flag(dma, channel_id);

    yzf_dma_transmit_count(channel,len);
    yzf_dma_per_size(channel,YZF_DMA_BYTE);
    yzf_dma_mem_size(channel,YZF_DMA_BYTE);
    yzf_dma_per_address(channel,(uint32_t)&spi->TXDR);
    yzf_dma_mem0_address(channel,(uint32_t)data);
    yzf_dma_set_priority(channel,YZF_DMA_HIGH);
    yzf_dma_mode_circular(channel,YZF_FALSE);
    yzf_dma_mode_per_inc(channel,YZF_FALSE);
    yzf_dma_mode_mem_inc(channel,YZF_TRUE);
    yzf_dma_mode_mem_per(channel);
    yzf_dma_interrupt_HT(channel,YZF_FALSE);
    yzf_dma_interrupt_TC(channel,YZF_FALSE);
    yzf_dma_interrupt_TE(channel,YZF_FALSE);

    yzf_dma_enable(channel);

    yzf_spi_set_DFF_8bits(spi);
    yzf_spi_enable_tx_dma(spi);
    yzf_spi_enable(spi);
    yzf_spi_tran_start(spi);
    return YZF_OK;
}

YZF_RESULT yz_spi_full_lines_init(YZF_SPI_POINTER spi,YZF_SPI_BR br,uint8_t fifoThreshold,
                                  uint8_t dataSize,YZF_BOOL cpol_high,YZF_BOOL cpha_sec,
                                  YZF_BOOL master,YZF_BOOL msb){
    yzf_spi_open_source_clock(spi);

    yzf_spi_disable(spi);
    yzf_spi_select_ssi(spi);//内部ss电平从而忽视IO电平

    yzf_spi_set_br(spi,br);
    yzf_spi_fifo_threshold_level(spi,fifoThreshold);
    yzf_spi_set_DFF_bits(spi,dataSize);
    yzf_spi_crc_disable(spi);//不使用 spi crc

    yzf_spi_enable_ssm(spi);//软件管理ss

    if (cpol_high) {
        yzf_spi_set_cpol_HIGH(spi);
    } else {
        yzf_spi_set_cpol_LOW(spi);
    }

    if (cpha_sec) {
        yzf_spi_set_cpha_second(spi);
    } else {
        yzf_spi_set_cpha_first(spi);
    }

    if(master){
        yzf_spi_set_master(spi);
    }else{
        yzf_spi_set_slave(spi);
    }

    if(msb){
        yzf_spi_set_MSBFIRST(spi);
    }else{
        yzf_spi_set_LSBFIRST(spi);
    }

    return YZF_OK;
}
YZF_RESULT yz_spi_bidi_init(YZF_SPI_POINTER spi,YZF_SPI_BR br,uint8_t fifoThreshold,
                            uint8_t dataSize,YZF_BOOL cpol_high,YZF_BOOL cpha_sec,YZF_BOOL master,
                            YZF_BOOL msb,YZF_BOOL isTx){
    yz_spi_full_lines_init(spi,br,fifoThreshold,dataSize,cpol_high,cpha_sec,master,msb);
    yzf_spi_enable_BIDI(spi);
    if(isTx){
        yzf_spi_enable_BIDIO(spi);
    }else{
        yzf_spi_disable_BIDIO(spi);
    }
    return YZF_OK;
}
YZF_RESULT yz_spi_full_lines_begin(YZF_SPI_POINTER spi){
    yzf_spi_enable(spi);
    while(yzf_spi_flag_bsy(spi));
    yzf_spi_clear_all_flag(spi);
    yzf_spi_tran_start(spi);
    return YZF_OK;
}

YZF_RESULT yz_spi_full_lines_end(YZF_SPI_POINTER spi){
    spi_conv_count=0;
    while (yzf_spi_flag_txe(spi)==YZF_FALSE||spi_conv_count>10000) {spi_conv_count++;}
    spi_conv_count=0;
    if( yzf_spi_flag_eot(spi)|| yzf_spi_flag_bsy(spi)){
        yzf_spi_tran_stop(spi);
    }
    while (yzf_spi_flag_bsy(spi)==YZF_TRUE||spi_conv_count>10000) {spi_conv_count++;}
    yzf_spi_disable(spi);
    return YZF_OK;
}
uint8_t yz_spi_full_lines_conv8(YZF_SPI_POINTER spi,uint8_t data){
    spi_conv_count=0;
    while (yzf_spi_flag_txp(spi)==YZF_FALSE||spi_conv_count>10000) {spi_conv_count++;}
    yzf_spi_write_byte(spi,data);
    while (yzf_spi_flag_rxne(spi)==YZF_FALSE);
    data = yzf_spi_read_byte(spi);
    return data;
}
uint16_t yz_spi_full_lines_conv16(YZF_SPI_POINTER spi,uint16_t data){
    spi_conv_count=0;
    while (yzf_spi_flag_txp(spi)==YZF_FALSE||spi_conv_count>10000) {spi_conv_count++;}
    yzf_spi_write_word(spi,data);
    while (yzf_spi_flag_rxne(spi)==YZF_FALSE);
    data = yzf_spi_read_word(spi);
    return data;
}
YZF_RESULT yz_spi_bidi_transmit(YZF_SPI_POINTER spi,uint8_t *data,uint16_t len){
    yzf_spi_enable_BIDIO(spi);
    while(len--){
        while (yzf_spi_flag_txp(spi)==YZF_FALSE);
        yzf_spi_write_byte(spi,*(data++));
    }
    return YZF_OK;
}