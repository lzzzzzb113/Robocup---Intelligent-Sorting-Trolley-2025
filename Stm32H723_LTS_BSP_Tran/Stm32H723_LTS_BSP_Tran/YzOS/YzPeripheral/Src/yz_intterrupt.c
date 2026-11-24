//
// Created by 32827 on 2023/11/23.
//
#include "yz_interrupt.h"

YZ_INT_HANDLER EXTI0_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX EXTI0_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER EXTI4_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX EXTI4_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER EXTI6_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX EXTI6_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER USART1_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX USART1_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER USART2_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX USART2_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER SysTick_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX SysTick_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER TIM1_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX TIM1_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER TIM10_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX TIM10_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER SPI1_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX SPI1_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER SPI2_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX SPI2_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER SPI3_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX SPI3_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA1_1_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA1_1_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA1_2_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA1_2_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA1_3_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA1_3_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA1_4_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA1_4_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA1_5_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA1_5_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA1_6_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA1_6_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA1_7_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA1_7_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA2_1_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA2_1_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA2_2_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA2_2_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA2_3_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA2_3_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

YZ_INT_HANDLER DMA2_4_5_iHandler=NULL_PTR;
YZF_GLOBAL_INDEX DMA2_4_5_Index=YZF_GLOBAL_SHEET_ERROR_INDEX;

void yz_int_set_EXTI0(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    EXTI0_iHandler=handler;
    EXTI0_Index=index;
}
void yz_int_set_EXTI4(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    EXTI4_iHandler=handler;
    EXTI4_Index=index;
}
void yz_int_set_EXTI6(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    EXTI6_iHandler=handler;
    EXTI6_Index=index;
}
void yz_int_set_USART1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    USART1_iHandler=handler;
    USART1_Index=index;
}
void yz_int_set_USART2(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    USART2_iHandler=handler;
    USART2_Index=index;
}
void yz_int_set_SysTick(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    SysTick_iHandler=handler;
    SysTick_Index=index;
}
void yz_int_set_TIM1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    TIM1_iHandler=handler;
    TIM1_Index=index;
}
void yz_int_set_TIM10(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    TIM10_iHandler=handler;
    TIM10_Index=index;
}
void yz_int_set_SPI1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    SPI1_iHandler=handler;
    SPI1_Index=index;
}
void yz_int_set_SPI2(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    SPI2_iHandler=handler;
    SPI2_Index=index;
}
void yz_int_set_SPI3(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    SPI3_iHandler=handler;
    SPI3_Index=index;
}
void yz_int_set_DMA1_1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA1_1_iHandler=handler;
    DMA1_1_Index=index;
}
void yz_int_set_DMA1_2(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA1_2_iHandler=handler;
    DMA1_2_Index=index;
}
void yz_int_set_DMA1_3(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA1_3_iHandler=handler;
    DMA1_3_Index=index;
}
void yz_int_set_DMA1_4(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA1_4_iHandler=handler;
    DMA1_4_Index=index;
}
void yz_int_set_DMA1_5(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA1_5_iHandler=handler;
    DMA1_5_Index=index;
}
void yz_int_set_DMA1_6(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA1_6_iHandler=handler;
    DMA1_6_Index=index;
}
void yz_int_set_DMA1_7(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA1_7_iHandler=handler;
    DMA1_7_Index=index;
}
void yz_int_set_DMA2_1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA2_1_iHandler=handler;
    DMA2_1_Index=index;
}
void yz_int_set_DMA2_2(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA2_2_iHandler=handler;
    DMA2_2_Index=index;
}
void yz_int_set_DMA2_3(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA2_3_iHandler=handler;
    DMA2_3_Index=index;
}
void yz_int_set_DMA2_4_5(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index){
    DMA2_4_5_iHandler=handler;
    DMA2_4_5_Index=index;
}

void EXTI9_5_IRQHandle(void){
    if(yzf_exti_interrupt_flag_get(6)){
        if(EXTI6_iHandler != NULL_PTR){
            EXTI6_iHandler(EXTI6_Index);
        }
        yzf_exti_interrupt_flag_clear(6);
    }
}
//void EXTI0_IRQHandler(void){
//    if(EXTI0_iHandler != NULL_PTR){
//        EXTI0_iHandler(EXTI0_Index);
//    }
//    yzf_exti_interrupt_flag_clear(0);
//}
//void EXTI4_IRQHandler(void){
//    if(EXTI4_iHandler != NULL_PTR){
//        EXTI4_iHandler(EXTI0_Index);
//    }
//    yzf_exti_interrupt_flag_clear(4);
//}
//void USART1_IRQHandler(void){
//    if(USART1_iHandler !=NULL_PTR){
//        USART1_iHandler(USART1_Index);
//    }
//}
void USART2_IRQHandler(void){
    if(USART2_iHandler !=NULL_PTR){
        USART2_iHandler(USART2_Index);
    }
}
//void SysTick_Handler(void){
//    if(SysTick_iHandler !=NULL_PTR){
//        SysTick_iHandler(SysTick_Index);
//    }else{
//        yzf_sys_tick_countFlag();
//    }
//}
void TIM1_UP_TIM10_IRQHandler(void){
    if(TIM1_iHandler !=NULL_PTR){
        TIM1_iHandler(TIM1_Index);
    }
    if(TIM10_iHandler !=NULL_PTR){
        TIM10_iHandler(TIM10_Index);
    }
}
void SPI1_IRQHandler(void){
    if(SPI1_iHandler !=NULL_PTR){
        SPI1_iHandler(SPI1_Index);
    }
}

void SPI2_IRQHandler(void){
    if(SPI2_iHandler !=NULL_PTR){
        SPI2_iHandler(SPI2_Index);
    }
}

void SPI3_IRQHandler(void){
    if(SPI3_iHandler !=NULL_PTR){
        SPI3_iHandler(SPI2_Index);
    }
}
void DMA1_Channel1_IRQHandler(void){
    if(DMA1_1_iHandler !=NULL_PTR){
        DMA1_1_iHandler(DMA1_1_Index);
    } else{
        yzf_dma_clear_all_flag(DMA1,1);
    }
}
void DMA1_Channel2_IRQHandler(void){
    if(DMA1_2_iHandler !=NULL_PTR){
        DMA1_2_iHandler(DMA1_2_Index);
    } else{
        yzf_dma_clear_all_flag(DMA1,2);
    }
}
void DMA1_Channel3_IRQHandler(void){
    if(DMA1_3_iHandler !=NULL_PTR){
        DMA1_3_iHandler(DMA1_3_Index);
    } else{
        yzf_dma_clear_all_flag(DMA1,3);
    }
}
void DMA1_Channel4_IRQHandler(void){
    if(DMA1_4_iHandler !=NULL_PTR){
        DMA1_4_iHandler(DMA1_4_Index);
    } else{
        yzf_dma_clear_all_flag(DMA1,4);
    }
}
void DMA1_Channel5_IRQHandler(void){
    if(DMA1_5_iHandler !=NULL_PTR){
        DMA1_5_iHandler(DMA1_5_Index);
    } else{
        yzf_dma_clear_all_flag(DMA1,5);
    }
}
void DMA1_Channel6_IRQHandler(void){
    if(DMA1_6_iHandler !=NULL_PTR){
        DMA1_6_iHandler(DMA1_6_Index);
    } else{
        yzf_dma_clear_all_flag(DMA1,6);
    }
}
void DMA1_Channel7_IRQHandler(void){
    if(DMA1_7_iHandler !=NULL_PTR){
        DMA1_7_iHandler(DMA1_7_Index);
    } else{
        yzf_dma_clear_all_flag(DMA1,7);
    }
}
void DMA2_Channel1_IRQHandler(void){
    if(DMA2_1_iHandler !=NULL_PTR){
        DMA2_1_iHandler(DMA2_1_Index);
    } else{
        yzf_dma_clear_all_flag(DMA2,1);
    }
}
void DMA2_Channel2_IRQHandler(void){
    if(DMA2_2_iHandler !=NULL_PTR){
        DMA2_2_iHandler(DMA2_2_Index);
    } else{
        yzf_dma_clear_all_flag(DMA2,2);
    }
}
void DMA2_Channel3_IRQHandler(void){
    if(DMA2_3_iHandler !=NULL_PTR){
        DMA2_3_iHandler(DMA2_3_Index);
    } else{
        yzf_dma_clear_all_flag(DMA2,3);
    }
}
void DMA2_Channel4_5_IRQHandler(void){
    if(DMA2_4_5_iHandler !=NULL_PTR){
        DMA2_4_5_iHandler(DMA2_4_5_Index);
    } else{
        yzf_dma_clear_all_flag(DMA2,4);

        yzf_dma_clear_all_flag(DMA2,5);
    }
}