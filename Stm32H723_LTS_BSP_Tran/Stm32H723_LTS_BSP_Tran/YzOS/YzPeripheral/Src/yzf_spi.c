//
// Created by 32827 on 2023/11/29.
//
#include "yzf_spi.h"
YZF_RESULT yzf_spi_open_source_clock(YZF_SPI_POINTER spi){
    switch ((uint32_t)spi) {
        case (uint32_t)SPI1:
            RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
            break;
        case (uint32_t)SPI2:
            RCC->APB1LENR |= RCC_APB1LENR_SPI2EN;
            break;
        case (uint32_t)SPI3:
            RCC->APB1LENR |= RCC_APB1LENR_SPI3EN;
            break;
        case (uint32_t) SPI4:
            RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
            break;
        case (uint32_t) SPI5:
            RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
            break;
        case (uint32_t) SPI6:
            RCC->APB4ENR |= RCC_APB4ENR_SPI6EN;
            break;
        default:
            return YZF_NOT_FOUND;
    }
    return YZF_OK;
}
//在改变CPOL/CPHA位之前，必须清除SPE位将SPI禁止。
//时钟极性置1，时钟空闲为高电平
YZF_RESULT yzf_spi_set_cpol_HIGH(YZF_SPI_POINTER spi){
    spi->CFG2 |= 0b1 << SPI_CFG2_CPOL_Pos;
    return YZF_OK;
}
//时钟极性清0，时钟空闲为低电平
YZF_RESULT yzf_spi_set_cpol_LOW(YZF_SPI_POINTER spi){
    spi->CFG2 &= ~(0b1 << SPI_CFG2_CPOL_Pos);
    return YZF_OK;
}
//时钟相位置1 在第二个边沿采样
YZF_RESULT yzf_spi_set_cpha_second(YZF_SPI_POINTER spi){
    spi->CFG2 |= 0b1 << SPI_CFG2_CPHA_Pos;
    return YZF_OK;
}
//时钟相位清0 在第一个边沿采样
YZF_RESULT yzf_spi_set_cpha_first(YZF_SPI_POINTER spi){
    spi->CFG2 &= ~(0b1 << SPI_CFG2_CPHA_Pos);
    return YZF_OK;
}
//数据高有效位先
YZF_RESULT yzf_spi_set_MSBFIRST(YZF_SPI_POINTER spi){
    spi->CFG2 &= ~(0b1 << SPI_CFG2_LSBFRST_Pos);
    return YZF_OK;
}
//数据低有效位先
YZF_RESULT yzf_spi_set_LSBFIRST(YZF_SPI_POINTER spi){
    spi->CFG2 |= 0b1 << SPI_CFG2_LSBFRST_Pos;
    return YZF_OK;
}
//8位数据帧
YZF_RESULT yzf_spi_set_DFF_8bits(YZF_SPI_POINTER spi){
    spi->CFG1 = (spi->CFG1&(~SPI_CFG1_DSIZE))|(7 << SPI_CFG1_DSIZE_Pos);
    return YZF_OK;
}
//16位数据帧
YZF_RESULT yzf_spi_set_DFF_16bits(YZF_SPI_POINTER spi){
    spi->CFG1 = (spi->CFG1&(~SPI_CFG1_DSIZE))|(15 << SPI_CFG1_DSIZE_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_set_DFF_bits(YZF_SPI_POINTER spi,uint8_t datSize){
    YZF_MODIFY_REG(spi->CFG1,SPI_CFG1_DSIZE,datSize,SPI_CFG1_DSIZE_Pos);
    return YZF_OK;
}
//TXE中断使能
YZF_RESULT yzf_spi_enable_txe_interrupt(YZF_SPI_POINTER spi){
    spi->IER |= 0b1 << SPI_IER_EOTIE_Pos;
    return YZF_OK;
}
//TXE中断失效
YZF_RESULT yzf_spi_disable_txe_interrupt(YZF_SPI_POINTER spi){
    spi->IER &= ~(0b1 << SPI_IER_EOTIE_Pos);
    return YZF_OK;
}
//TXE FLAG获取
YZF_BOOL yzf_spi_flag_txe(YZF_SPI_POINTER spi){
    return (spi->SR & (0b1 << SPI_SR_TXC_Pos)) == 0 ? YZF_FALSE :YZF_TRUE;
}
//RXNE中断使能
YZF_RESULT yzf_spi_enable_rxne_interrupt(YZF_SPI_POINTER spi){
   spi->IER |= 0b1 << SPI_IER_RXPIE_Pos;
    return YZF_OK;
}
//RXNE中断失效
YZF_RESULT yzf_spi_disable_rxne_interrupt(YZF_SPI_POINTER spi){
    spi->IER &= ~(0b1 << SPI_IER_RXPIE_Pos);
    return YZF_OK;
}
//RXNE FLAG获取
YZF_BOOL yzf_spi_flag_rxne(YZF_SPI_POINTER spi){
    return (spi->SR & (0b1 << SPI_SR_RXP_Pos)) == 0 ? YZF_FALSE :YZF_TRUE;
}

//错误中断使能
YZF_RESULT yzf_spi_enable_err_interrupt(YZF_SPI_POINTER spi){
    spi->IER |= 0b1 << SPI_IER_MODFIE_Pos;
    return YZF_OK;
}
//错误中断失效
YZF_RESULT yzf_spi_disable_err_interrupt(YZF_SPI_POINTER spi){
    spi->IER &= ~(0b1 << SPI_IER_MODFIE_Pos);
    return YZF_OK;
}

//BSY FLAG获取
YZF_BOOL yzf_spi_flag_bsy(YZF_SPI_POINTER spi){
    return (spi->CR1 & (0b1 << SPI_CR1_CSTART_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//OVR FLAG获取
YZF_BOOL yzf_spi_flag_ovr(YZF_SPI_POINTER spi){
    return (spi->SR & (0b1 << SPI_SR_OVR_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//MODF FLAG模式错误获取
YZF_BOOL yzf_spi_flag_modf(YZF_SPI_POINTER spi){
    return (spi->SR & (0b1 << SPI_SR_MODF_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//CRCERR FLAG获取
YZF_BOOL yzf_spi_flag_crcerr(YZF_SPI_POINTER spi){
    return (spi->SR & (0b1 << SPI_SR_CRCE_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//UDR FLAG获取 下溢标志
YZF_BOOL yzf_spi_flag_udr(YZF_SPI_POINTER spi){
    return (spi->SR & (0b1 << SPI_SR_UDR_Pos)) == 0 ? YZF_FALSE : YZF_TRUE;
}
//CHSIDE FLAG获取 声道
YZF_BOOL yzf_spi_flag_chside(YZF_SPI_POINTER spi){
    return YZF_FALSE ;
}


//读取数据 会清除RXNE位
uint8_t yzf_spi_read_byte(YZF_SPI_POINTER spi){
    return *((volatile  uint8_t *)&spi->RXDR);
}
uint16_t yzf_spi_read_word(YZF_SPI_POINTER spi){
    return *((volatile  uint16_t *)&spi->RXDR);
}
//写入数据 会清除TXE位
YZF_RESULT yzf_spi_write_byte(YZF_SPI_POINTER spi,uint8_t byte){
    *((volatile  uint8_t *)&spi->TXDR) = byte;
    return YZF_OK;
}
YZF_RESULT yzf_spi_write_word(YZF_SPI_POINTER spi,uint16_t word){
    *((volatile  uint16_t *)&spi->TXDR) = word;
    return YZF_OK;
}

//1条时钟线和1条双向数据线 使能
YZF_RESULT yzf_spi_enable_BIDI(YZF_SPI_POINTER spi){
    spi->CFG2 |= (0b11 << SPI_CFG2_COMM_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_disable_BIDI(YZF_SPI_POINTER spi){
    spi->CFG2 &= ~(0b11 << SPI_CFG2_COMM_Pos);
    return YZF_OK;
}
//BIDI发送使能
YZF_RESULT yzf_spi_enable_BIDIO(YZF_SPI_POINTER spi){
    spi->CR1 |= (0b1 << SPI_CR1_HDDIR_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_disable_BIDIO(YZF_SPI_POINTER spi){
    spi->CR1 &= ~(0b1 << SPI_CR1_HDDIR_Pos);
    return YZF_OK;
}
//单线单向 接收 只接收
YZF_RESULT yzf_spi_enable_RXONLY(YZF_SPI_POINTER spi){
    spi->CFG2 |= (0b10 << SPI_CFG2_COMM_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_disable_RXONLY(YZF_SPI_POINTER spi){
    spi->CFG2 &= ~(0b10 << SPI_CFG2_COMM_Pos);
    return YZF_OK;
}

//spi使能
YZF_RESULT yzf_spi_enable(YZF_SPI_POINTER spi){
    spi->CR1 |= (0b1 << SPI_CR1_SPE_Pos);
    return YZF_OK;
}
//spi失效
YZF_RESULT yzf_spi_disable(YZF_SPI_POINTER spi){
    spi->CR1 &= ~(0b1 << SPI_CR1_SPE_Pos);
    return YZF_OK;
}
YZF_BOOL  yzf_spi_is_enabled(YZF_SPI_POINTER spi){
    return (spi->CR1 & (0b1 << SPI_CR1_SPE_Pos)) ? YZF_TRUE : YZF_FALSE;
}

//硬件CRC使能
YZF_RESULT yzf_spi_crc_enable(YZF_SPI_POINTER spi){
    spi->CFG1 |= (0b1 << SPI_CFG1_CRCEN_Pos);
    return YZF_OK;
}
//硬件CRC失效
YZF_RESULT yzf_spi_crc_disable(YZF_SPI_POINTER spi){
    spi->CFG1 &= ~(0b1 << SPI_CFG1_CRCEN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_crc_data_size(YZF_SPI_POINTER spi,uint8_t datSize){
    YZF_MODIFY_REG(spi->CFG1, SPI_CFG1_CRCSIZE, datSize,SPI_CFG1_CRCSIZE_Pos);
    return YZF_OK;
}
//下一个输出CRC
YZF_RESULT yzf_spi_crc_next(YZF_SPI_POINTER spi){
//    spi->CR1 |= (0b1 << SPI_CR1_CRCNEXT_Pos);
    return YZF_OK;
}
//CRC公式
YZF_RESULT yzf_spi_set_crc_poly(YZF_SPI_POINTER spi,uint16_t poly){
    spi->CRCPOLY = poly;
    return YZF_OK;
}
//CRC接收寄存器
uint16_t yzf_spi_get_crc_rx(YZF_SPI_POINTER spi){
    return spi->RXCRC;
}
//CRC发送寄存器
YZF_RESULT yzf_spi_set_crc_tx(YZF_SPI_POINTER spi,uint16_t crc){
    spi->TXCRC &= crc;
    return YZF_OK;
}


//软件nss管理
YZF_RESULT yzf_spi_enable_ssm(YZF_SPI_POINTER spi){
    spi->CFG2 |= (0b1 << SPI_CFG2_SSM_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_disable_ssm(YZF_SPI_POINTER spi){
    spi->CFG2 &= ~(0b1 << SPI_CFG2_SSM_Pos);
    return YZF_OK;
}
//内部从设备选择
YZF_RESULT yzf_spi_select_ssi(YZF_SPI_POINTER spi){
    spi->CR1 |= (0b1 << SPI_CR1_SSI_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_disSelect_ssi(YZF_SPI_POINTER spi){
    spi->CR1 &= ~(0b1 << SPI_CR1_SSI_Pos);
    return YZF_OK;
}

YZF_BOOL  yzf_spi_ssi_status(YZF_SPI_POINTER spi){
    return spi->CR1 & SPI_CR1_SSI ? YZF_TRUE : YZF_FALSE;
}
//波特控制
YZF_RESULT yzf_spi_set_br(YZF_SPI_POINTER spi,YZF_SPI_BR br){
    spi->CFG1 &= ~(0xF << SPI_CFG1_MBR_Pos);
    spi->CFG1 |= (br << SPI_CFG1_MBR_Pos);
    return YZF_OK;
}

//NSS输出使能
YZF_RESULT yzf_spi_enable_sso(YZF_SPI_POINTER spi){
    spi->CFG2 |= (0b1 << SPI_CFG2_SSOE_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_disable_sso(YZF_SPI_POINTER spi){
    spi->CFG2 &= ~(0b1 << SPI_CFG2_SSOE_Pos);
    return YZF_OK;
}
//DMA使能
YZF_RESULT yzf_spi_enable_tx_dma(YZF_SPI_POINTER spi){
    spi->CFG1 |= (0b1 << SPI_CFG1_TXDMAEN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_disable_tx_dma(YZF_SPI_POINTER spi){
    spi->CFG1 &= ~(0b1 << SPI_CFG1_TXDMAEN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_enable_rx_dma(YZF_SPI_POINTER spi){
    spi->CFG1 |= (0b1 << SPI_CFG1_RXDMAEN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_disable_rx_dma(YZF_SPI_POINTER spi){
    spi->CFG1 &= ~(0b1 << SPI_CFG1_RXDMAEN_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_set_master(YZF_SPI_POINTER spi){
    spi->CFG2 |= (0b1 << SPI_CFG2_MASTER_Pos);
    return YZF_OK;
}
YZF_RESULT yzf_spi_set_slave(YZF_SPI_POINTER spi){
    spi->CFG2 &= ~(0b1 << SPI_CFG2_MASTER_Pos);
    return YZF_OK;
}


YZF_RESULT yzf_spi_fifo_threshold_level(YZF_SPI_POINTER spi,uint8_t level){
    spi->CFG1 &= ~SPI_CFG1_FTHLV;
    spi->CFG1 |= level << SPI_CFG1_FTHLV_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_spi_write_double_word(YZF_SPI_POINTER spi,uint32_t doubleWord){
    *((volatile  uint32_t *)&spi->TXDR) = doubleWord;
    return YZF_OK;
}
uint32_t yzf_spi_read_double_word(YZF_SPI_POINTER spi){
    return *((volatile  uint32_t *)&spi->RXDR);
}
YZF_RESULT yzf_spi_tran_start(YZF_SPI_POINTER spi){
    spi->CR1 |= 1 << SPI_CR1_CSTART_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_spi_tran_count(YZF_SPI_POINTER spi,uint32_t size){
    spi->CR1 &= SPI_CR2_TSIZE;
    spi->CR2 |= size << SPI_CR2_TSIZE_Pos;
    return YZF_OK;
}
YZF_RESULT yzf_spi_disable_all_interrupt(YZF_SPI_POINTER spi){
    spi->IER = 0x0;
    return YZF_OK;
}
YZF_RESULT yzf_spi_clear_all_flag(YZF_SPI_POINTER spi){
    spi->IFCR = (SPI_IFCR_EOTC | SPI_IFCR_TXTFC | SPI_IFCR_UDRC | SPI_IFCR_OVRC | SPI_IFCR_CRCEC | SPI_IFCR_TIFREC | SPI_IFCR_MODFC | SPI_IFCR_TSERFC | SPI_IFCR_SUSPC );
    return YZF_OK;
}
YZF_BOOL yzf_spi_flag_txp(YZF_SPI_POINTER spi){
    return (spi->SR & (0b1 << SPI_SR_TXP_Pos)) == 0 ? YZF_FALSE :YZF_TRUE;
}
YZF_BOOL yzf_spi_flag_eot(YZF_SPI_POINTER spi){
    return (spi->SR & (0b1 << SPI_SR_EOT_Pos)) == 0 ? YZF_FALSE :YZF_TRUE;
}
YZF_RESULT yzf_spi_tran_stop(YZF_SPI_POINTER spi){
    spi->CR1 |= SPI_CR1_CSUSP;
    return YZF_OK;
}