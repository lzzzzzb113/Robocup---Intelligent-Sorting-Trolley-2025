//
// Created by 32827 on 2023/11/23.
//

#ifndef YZFRAME_YZ_INTERRUPT_H
#define YZFRAME_YZ_INTERRUPT_H
#include "yz.h"
#include "yzf_global_sheet.h"
#include "yzf_dma.h"
#include "yzf_exti.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*YZ_INT_HANDLER)(YZF_GLOBAL_INDEX index);

void yz_int_set_EXTI0(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_EXTI4(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_EXTI6(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_USART1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_USART2(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_SysTick(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_TIM1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_TIM10(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_SPI1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_SPI2(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_SPI3(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA1_1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA1_2(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA1_3(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA1_4(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA1_5(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA1_6(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA1_7(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA2_1(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA2_2(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA2_3(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);
void yz_int_set_DMA2_4_5(YZ_INT_HANDLER handler,YZF_GLOBAL_INDEX index);

#ifdef __cplusplus
}
#endif
#endif //YZFRAME_YZ_INTERRUPT_H
