//
// Created by 32827 on 2023/11/24.
//
#include "yz_uart.h"
#include "yz_interrupt.h"

YZ_UART_TRANSMIT_BLOCK UART1_TRANSMIT_BLOCK={0};
YZ_UART_TRANSMIT_BLOCK UART2_TRANSMIT_BLOCK={0};
YZF_RECV YZ_EXTERN_BLOCK={0};
YZ_RECV_TIME YZ_UART1_IT_RECV_TIME={0};
YZF_RECV YZ_UART2_IT_RECV={0};
YZF_RECV YZ_UART3_IT_RECV={0};
YZF_RECV YZ_UART4_IT_RECV={0};
YZ_RECV_TIME YZ_UART5_IT_RECV_TIME={0};
YZ_RECV_TIME YZ_UART7_IT_RECV_TIME={0};


uint32_t yz_recvCount=0;

uint32_t *yz_uart_get_recv_count(){
    return &yz_recvCount;
}
extern uint32_t SystemTickCNT;
void USART1_Handler(YZF_GLOBAL_INDEX index){
    //接收
//    if(yzf_uart_flag_RXNE(USART1)){
//        yz_recvCount++;
//        //接收
//
//        return;
//    }
    if(yzf_uart_flag_RXNE(USART1)){
        yz_area_recv_time_listener_default(&YZ_UART1_IT_RECV_TIME,yzf_uart_get_data(USART1),SystemTickCNT);
    }
    if(USART_ISR_ORE|USART1->ISR ){
        USART1->ICR |= USART_ICR_ORECF;
    }
    if(USART_ISR_PE|USART1->ISR){
        USART1->ICR |= USART_ICR_PECF;
    }
    if(USART_ISR_FE|USART1->ISR){
        USART1->ICR |= USART_ICR_FECF;
    }
    if(USART_ISR_NE|USART1->ISR){
        USART1->ICR |= USART_ICR_NECF;
    }
    if(USART_ISR_RTOF|USART1->ISR){
        USART1->ICR |= USART_ICR_RTOCF;
    }
//    //发送
//    if(UART1_TRANSMIT_BLOCK.index==UART1_TRANSMIT_BLOCK.len&&yzf_uart_flag_TC(UART1_TRANSMIT_BLOCK.uart)){
//        yzf_uart_te_disable(UART1_TRANSMIT_BLOCK.uart);
//        yzf_uart_txe_interrupt(UART1_TRANSMIT_BLOCK.uart,YZF_FALSE);
//        return;
//    }
//    if(yzf_uart_flag_TXE(UART1_TRANSMIT_BLOCK.uart)){
//        if(UART1_TRANSMIT_BLOCK.index<UART1_TRANSMIT_BLOCK.len){
//            yzf_uart_set_data(UART1_TRANSMIT_BLOCK.uart,*(UART1_TRANSMIT_BLOCK.data+UART1_TRANSMIT_BLOCK.index));
//            UART1_TRANSMIT_BLOCK.index++;
//        }
//    }
}
void USART2_Handler(YZF_GLOBAL_INDEX index){
    //接收
    if(yzf_uart_flag_RXNE(USART2)){
        yz_recvCount++;
        yzf_area_recv_add(&YZ_UART2_IT_RECV,yzf_uart_get_data(USART2));
        return;
    }
    //发送
    if(UART2_TRANSMIT_BLOCK.index==UART2_TRANSMIT_BLOCK.len&&yzf_uart_flag_TC(UART2_TRANSMIT_BLOCK.uart)){
        yzf_uart_te_disable(UART2_TRANSMIT_BLOCK.uart);
        yzf_uart_txe_interrupt(UART2_TRANSMIT_BLOCK.uart,YZF_FALSE);
        return;
    }
    if(yzf_uart_flag_TXE(UART2_TRANSMIT_BLOCK.uart)){
        if(UART2_TRANSMIT_BLOCK.index<UART2_TRANSMIT_BLOCK.len){
            yzf_uart_set_data(UART2_TRANSMIT_BLOCK.uart,*(UART2_TRANSMIT_BLOCK.data+UART2_TRANSMIT_BLOCK.index));
            UART2_TRANSMIT_BLOCK.index++;
        }
    }
}

void UART5_Handler(YZF_GLOBAL_INDEX index){
    //接收
    if(yzf_uart_flag_RXNE(UART5)){
//        yzf_area_recv_add(&YZ_UART5_IT_RECV,yzf_uart_get_data(UART5));
        yz_area_recv_time_listener_default(&YZ_UART5_IT_RECV_TIME,yzf_uart_get_data(UART5),SystemTickCNT);
    }
    if(UART5->ISR|USART_ISR_ORE){
        UART5->ICR |= USART_ICR_ORECF;
    }
    if(UART5->ISR|USART_ISR_PE){
        UART5->ICR |= USART_ICR_PECF;
    }
    if(UART5->ISR|USART_ISR_FE){
        UART5->ICR |= USART_ICR_FECF;
    }
    if(UART5->ISR|USART_ISR_NE){
        UART5->ICR |= USART_ICR_NECF;
    }
    if(UART5->ISR|USART_ISR_RTOF){
        UART5->ICR |= USART_ICR_RTOCF;
    }
}
void UART4_Handler(YZF_GLOBAL_INDEX index){
    //接收
    if(yzf_uart_flag_RXNE(UART4)){
        yzf_area_recv_add(&YZ_UART4_IT_RECV,yzf_uart_get_data(UART4));
    }
}

//TODO: REMOVE

void UART7_Handler(YZF_GLOBAL_INDEX index){
    //接收
    if(yzf_uart_flag_RXNE(UART7)){
        yz_area_recv_time_listener_default(&YZ_UART7_IT_RECV_TIME,yzf_uart_get_data(UART7),SystemTickCNT);
        return;
    }
    if(UART7->ISR|USART_ISR_ORE){
        UART7->ICR |= USART_ICR_ORECF;
    }
    if(UART7->ISR|USART_ISR_PE){
        UART7->ICR |= USART_ICR_PECF;
    }
    if(UART7->ISR|USART_ISR_FE){
        UART7->ICR |= USART_ICR_FECF;
    }
    if(UART7->ISR|USART_ISR_NE){
        UART7->ICR |= USART_ICR_NECF;
    }
    if(UART7->ISR|USART_ISR_RTOF){
        UART7->ICR |= USART_ICR_RTOCF;
    }
}


YZ_INT_HANDLER DMA_TX_EMD=YZF_NULL_PTR; //传输结束回调

void USART1_DMA_TX_Handler(YZF_GLOBAL_INDEX index){
    if(yzf_dma_flag_TC(DMA1,4)){
        if(DMA_TX_EMD!=YZF_NULL_PTR){   //应用于二次传输
            yzf_uart_te_disable(USART1);
            yzf_uart_dma_transmitter_enable(USART1,YZF_FALSE);
//            yzf_dma_disable(DMA1_Channel4);
            yzf_dma_disable(DMA1_Stream4);
            yzf_dma_clear_flag_DMEIF(DMA1,4);
            yzf_dma_clear_flag_TEIF(DMA1,4);
            yzf_dma_clear_flag_TCIF(DMA1,4);
            yzf_dma_clear_flag_HTIF(DMA1,4);

            DMA_TX_EMD(index);

            DMA_TX_EMD=YZF_NULL_PTR;
            return;
        }
        yzf_uart_te_disable(USART1);
        yzf_uart_dma_transmitter_enable(USART1,YZF_FALSE);
//      yzf_dma_disable(DMA1_Channel4);
        yzf_dma_disable(DMA1_Stream4);
    }
    yzf_dma_clear_flag_DMEIF(DMA1,4);
    yzf_dma_clear_flag_TEIF(DMA1,4);
    yzf_dma_clear_flag_TCIF(DMA1,4);
    yzf_dma_clear_flag_HTIF(DMA1,4);
}
void USART2_DMA_TX_Handler(YZF_GLOBAL_INDEX index){
    if(yzf_dma_flag_TC(DMA1,7)){
        if(DMA_TX_EMD!=YZF_NULL_PTR){   //应用于二次传输
            yzf_uart_te_disable(USART2);
            yzf_uart_dma_transmitter_enable(USART2,YZF_FALSE);
//            yzf_dma_disable(DMA1_Channel7);
            yzf_dma_disable(DMA1_Stream7);
            yzf_dma_clear_flag_DMEIF(DMA1,7);
            yzf_dma_clear_flag_TEIF(DMA1,7);
            yzf_dma_clear_flag_TCIF(DMA1,7);
            yzf_dma_clear_flag_HTIF(DMA1,7);

            DMA_TX_EMD(index);

            DMA_TX_EMD=YZF_NULL_PTR;
            return;
        }
        yzf_uart_te_disable(USART2);
        yzf_uart_dma_transmitter_enable(USART2,YZF_FALSE);
//        yzf_dma_disable(DMA1_Channel7);
        yzf_dma_disable(DMA1_Stream7);
    }
    yzf_dma_clear_flag_DMEIF(DMA1,7);
    yzf_dma_clear_flag_TEIF(DMA1,7);
    yzf_dma_clear_flag_TCIF(DMA1,7);
    yzf_dma_clear_flag_HTIF(DMA1,7);
}
/**
 * @ChangeOnAdd
 * */
YZF_RESULT yz_uart_init(YZF_UART_POINTER uart,YZF_UART_WORD_LENGTH length,YZF_UART_DATA stopbits,uint32_t baudrate,YZF_BOOL parity){
    yzf_uart_source_clock_open(uart);
    yzf_uart_word_length(uart,length);
    yzf_uart_stop_bit(uart,stopbits);
#if YZ_USE_WITH_HAL_UART
    uint32_t pclk;
    if(uart==USART1){
        pclk=HAL_RCC_GetPCLK2Freq();
    }else{
        pclk=HAL_RCC_GetPCLK1Freq();
    }
    yzf_uart_baud_rate(uart,UART_BRR_SAMPLING16(pclk, baudrate));
#else
    yzf_uart_baud_rate(uart,baudrate);
#endif
    yzf_uart_set_parity(uart,parity);
    yzf_uart_tx_enable(uart,YZF_TRUE);
    yzf_uart_rx_enable(uart,YZF_TRUE);
    yzf_uart_rxne_interrupt(uart,YZF_TRUE);
    yzf_uart_enable(uart);
    switch ((uint32_t)uart) {
        case (uint32_t)USART1:
            yzf_nvic_irq_enable(USART1_IRQn);
            yzf_nvic_irq_set_priority(USART1_IRQn,0b00100000);
            yz_int_set_USART1(USART1_Handler, YZF_GLOBAL_SHEET_ERROR_INDEX);
            return YZF_OK;
        case (uint32_t)USART2:
            yzf_nvic_irq_enable(USART2_IRQn);
            yzf_nvic_irq_set_priority(USART2_IRQn,0b01000000);
            yz_int_set_USART2(USART2_Handler, YZF_GLOBAL_SHEET_ERROR_INDEX);
            return YZF_OK;
        default:
            return YZF_NOT_FOUND;
    }
}
YZF_RESULT yz_uart_transmit(YZF_UART_POINTER uart,uint8_t* data,uint16_t len){
    yzf_uart_te_enable(uart);
    for(int i=0;i<len;i++){
        while (yzf_uart_flag_TXE(uart)==YZF_FALSE);
        yzf_uart_set_data(uart,*(data+i));
    }
    while (yzf_uart_flag_TXE(uart)==YZF_FALSE);
    while (yzf_uart_flag_TC(uart)==YZF_FALSE);
    return yzf_uart_te_disable(uart);
}
/**
 * @ChangeOnAdd
 * */
YZF_RESULT yz_uart_transmit_IT(YZF_UART_POINTER uart,uint8_t* data,uint16_t len){
    switch ((uint32_t)uart) {
        case (uint32_t)USART1:
            UART1_TRANSMIT_BLOCK.index=0;
            UART1_TRANSMIT_BLOCK.uart=uart;
            UART1_TRANSMIT_BLOCK.data=data;
            UART1_TRANSMIT_BLOCK.len=len;
            yzf_uart_txe_interrupt(uart,YZF_TRUE);
            yzf_uart_te_enable(uart);
            return YZF_OK;
        case (uint32_t)USART2:
            UART2_TRANSMIT_BLOCK.index=0;
            UART2_TRANSMIT_BLOCK.uart=uart;
            UART2_TRANSMIT_BLOCK.data=data;
            UART2_TRANSMIT_BLOCK.len=len;
            yzf_uart_txe_interrupt(uart,YZF_TRUE);
            yzf_uart_te_enable(uart);
            return YZF_OK;
        default:
            return YZF_NOT_FOUND;
    }
}
/**
 * @ChangeOnAdd
 * */
YZF_RESULT yz_uart_transmit_DMA(YZF_UART_POINTER uart,uint8_t* data,uint16_t len){
    switch ((uint32_t)uart) {
        case (uint32_t)USART1:
            yzf_nvic_irq_enable(DMA1_Stream4_IRQn);
            yzf_nvic_irq_set_priority(DMA1_Stream4_IRQn,0b01000000);
            yz_int_set_DMA1_4(USART1_DMA_TX_Handler, YZF_GLOBAL_SHEET_ERROR_INDEX);
            yz_dma_mem_2_per(DMA1,DMA1_Stream4,data,(void*)&USART1->RDR,YZF_DMA_BYTE,YZF_DMA_BYTE,YZF_TRUE,YZF_FALSE,len,YZF_FALSE,YZF_TRUE,YZF_FALSE,YZF_TRUE,YZF_DMA_HIGH);
            yzf_uart_dma_transmitter_enable(USART1,YZF_TRUE);
            yzf_uart_te_enable(uart);
            return YZF_OK;
        case (uint32_t)USART2:
            yzf_nvic_irq_enable(DMA1_Stream7_IRQn);
            yzf_nvic_irq_set_priority(DMA1_Stream7_IRQn,0b01000000);
            yz_int_set_DMA1_7(USART2_DMA_TX_Handler, YZF_GLOBAL_SHEET_ERROR_INDEX);
            yz_dma_mem_2_per(DMA1,DMA1_Stream7,data,(void*)&USART2->RDR,YZF_DMA_BYTE,YZF_DMA_BYTE,YZF_TRUE,YZF_FALSE,len,YZF_FALSE,YZF_TRUE,YZF_FALSE,YZF_TRUE,YZF_DMA_HIGH);
            yzf_uart_dma_transmitter_enable(USART2,YZF_TRUE);
            yzf_uart_te_enable(uart);
            return YZF_OK;
        default:
            return YZF_NOT_FOUND;
    }
}
///不需要自己删除
YZF_RESULT yz_uart_transmit_area_DMA(YZF_UART_POINTER uart,YZF_RECV *area,uint16_t len){
    YZF_RECV_DATA_INDEX most_size=yzf_area_recv_get_end_ptr(area)-yzf_area_recv_get_read_ptr(area);
    if(most_size>=len){
        yz_uart_transmit_DMA(uart, yzf_area_recv_get_read_ptr(area),len);
        yzf_area_recv_del(area,len);
    }
    if(most_size<len){
        yz_uart_transmit(uart, yzf_area_recv_get_read_ptr(area),most_size); //发送第一次
        yzf_area_recv_del(area,most_size);
        most_size=len-most_size;
        yz_uart_transmit_DMA(uart, yzf_area_recv_get_read_ptr(area),most_size);
        yzf_area_recv_del(area,most_size);
    }
    return YZF_OK;
}

void YZ_UART_IT_RECV_listener(YZF_RECV_EVENT event,struct YZF_RECV_AREA* area,YZF_GLOBAL_INDEX dataIndex){
    if(&YZ_UART1_IT_RECV_TIME==area ||&YZ_UART2_IT_RECV==area||&YZ_UART3_IT_RECV==area||&YZ_UART4_IT_RECV==area||&YZ_UART5_IT_RECV_TIME==area||&YZ_UART7_IT_RECV_TIME==area){
        switch (event) {
            case recv_full:
                yzf_area_recv_add(&YZ_EXTERN_BLOCK, *(YZF_RECV_DATA *)yzf_global_data_get(dataIndex));
                return;
            case recv_get:
                *(YZF_RECV_DATA_INDEX *)yzf_global_data_get(dataIndex)=yzf_area_recv_get(&YZ_EXTERN_BLOCK);
                return;
            case recv_read_ptr:
                *(YZF_RECV_DATA **)yzf_global_data_get(dataIndex)= yzf_area_recv_get_read_ptr(&YZ_EXTERN_BLOCK);
                return;
            case recv_end_ptr:
                *(YZF_RECV_DATA **)yzf_global_data_get(dataIndex)= yzf_area_recv_get_end_ptr(&YZ_EXTERN_BLOCK);
                return;
            case recv_del:
                yzf_area_recv_del(&YZ_EXTERN_BLOCK, *(YZF_RECV_DATA *)yzf_global_data_get(dataIndex));
                return;
        }
    }
}
YZF_RESULT yz_uart_receive(YZF_UART_POINTER uart,uint8_t* data,uint16_t len){
    yzf_uart_re_enable(uart);
    for(int i=0;i<len;i++){
        while (yzf_uart_flag_RXNE(uart)==YZF_FALSE);
        *(data+i)=yzf_uart_get_data(uart);
    }
    return YZF_OK;
}

YZF_RESULT yz_uart_receive_IT_init(YZF_UART_POINTER uart){
    yzf_area_recv_init(yz_uart_receive_IT_RECV_get(uart), YZ_UART_IT_RECV_listener);
    yzf_uart_rxne_interrupt(uart,YZF_TRUE);
    yzf_uart_re_enable(uart);
    return YZF_OK;
}
YZF_RECV_DATA_INDEX yz_uart_receive_IT_size(YZF_UART_POINTER uart){
    return yzf_area_recv_get_size(yz_uart_receive_IT_RECV_get(uart));
}
/**
 * @ChangeOnAdd
 * */
YZF_RECV * yz_uart_receive_IT_RECV_get(YZF_UART_POINTER uart){
    switch ((uint32_t)uart) {
        case (uint32_t) USART1:
            return (YZF_RECV *)&YZ_UART1_IT_RECV_TIME;
        case (uint32_t) USART2:
            return &YZ_UART2_IT_RECV;
        case (uint32_t) USART3:
            return &YZ_UART3_IT_RECV;
        case (uint32_t) UART4:
            return &YZ_UART4_IT_RECV;
        case (uint32_t) UART5:
            return (YZF_RECV *)&YZ_UART5_IT_RECV_TIME;
        case (uint32_t) UART7:
            return (YZF_RECV *)&YZ_UART7_IT_RECV_TIME;
        default:
            return YZF_NULL_PTR;
    }
}
YZF_RESULT yz_uart_receive_IT(YZF_UART_POINTER uart,uint8_t* data,uint16_t len){
    for(int i=0;i<len;i++){
        *(data+i)=yzf_area_recv_get(yz_uart_receive_IT_RECV_get(uart));
    }
    return YZF_OK;
}