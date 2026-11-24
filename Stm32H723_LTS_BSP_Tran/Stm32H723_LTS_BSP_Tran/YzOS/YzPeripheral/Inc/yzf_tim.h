//
// Created by 32827 on 2024/6/24.
//

#ifndef STM32F407RTOS_YZF_TIM_H
#define STM32F407RTOS_YZF_TIM_H
#include "yzf.h"
#ifdef __cplusplus
extern "C" {
#endif
/**
 * 开启时钟
 * @param p_tim 例如TIM1,TIM2
 * */
YZF_RESULT yzf_tim_open_clock(YZF_TIM_POINTER p_tim);

/**
 * @note 全部支持
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_enable(YZF_TIM_POINTER p_tim);
YZF_RESULT yzf_tim_disable(YZF_TIM_POINTER p_tim);

/**
 * @note 全部支持
 * 此位由软件置 1 和清零，用以选择 UEV 事件源。
 * 0：使能时，所有以下事件都会产生更新中断或 DMA 请求。此类事件包括：
 * – 计数器上溢/下溢
 * – 将 UG 位置 1
 * – 通过从模式控制器生成的更新事件
 * 1：使能时，只有计数器上溢/ 下溢会生成更新中断或 DMA 请求。
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_update_event_disable(YZF_TIM_POINTER p_tim);
YZF_RESULT yzf_tim_update_event_enable(YZF_TIM_POINTER p_tim);

/**
 * 更新中断使能
 *
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_update_interrupt_enable(YZF_TIM_POINTER p_tim,YZF_BOOL isEnable);

/**
 * @note 全部支持
 *
 * 0：使能时，所有以下事件都会产生更新中断或 DMA 请求。此类事件包括：
 * – 计数器上溢/下溢
 * – 将 UG 位置 1
 * – 通过从模式控制器生成的更新事件
 * 1：使能时，只有计数器上溢/ 下溢会生成更新中断或 DMA 请求。
 *
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_update_source(YZF_TIM_POINTER p_tim, uint8_t source);

/**
 * 递增方向
 * @param isSub 是否递减
 * @note 基本时钟不支持
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_set_dir(YZF_TIM_POINTER p_tim, YZF_BOOL isSub);

/**
 * 单脉冲模式
 * @note 全部支持
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_set_one_pulse_mode(YZF_TIM_POINTER p_tim,YZF_BOOL isOne);

/**
 * 设置时钟分频 f(out) = f(APB)/[(psc+1)*(arr)*(clk_division)]
 * @note 基本时钟不支持
 * */
YZF_RESULT yzf_tim_set_clock_division(YZF_TIM_POINTER p_tim, uint8_t division);

/**
 * @note 全部支持
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_auto_reload_enable(YZF_TIM_POINTER p_tim);
YZF_RESULT yzf_tim_auto_reload_disable(YZF_TIM_POINTER p_tim);


/**
 * 中心对齐模式选择
 *
 * 00：边沿对齐模式。计数器根据方向位 (DIR) 递增计数或递减计数。
 * 01：中心对齐模式 1。计数器交替进行递增计数和递减计数。仅当计数器递减计数时，配置
 * 为输出的通道（TIMx_CCMRx 寄存器中的 CxS=00）的输出比较中断标志才置 1。
 * 10：中心对齐模式 2。计数器交替进行递增计数和递减计数。仅当计数器递增计数时，配置
 * 为输出的通道（TIMx_CCMRx 寄存器中的 CxS=00）的输出比较中断标志才置 1。
 * 11：中心对齐模式 3。计数器交替进行递增计数和递减计数。当计数器递增计数或递减计
 * 数时，配置为输出的通道（TIMx_CCMRx 寄存器中的 CxS=00）的输出比较中断标志都会
 * 置 1。
 *
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_center_align_mode_select(YZF_TIM_POINTER p_tim,uint8_t mode);

/**
 * 获取时钟更新中断标志
 * @note 全部支持
 *
 * @checked STM32H723
 * */
YZF_BOOL yzf_tim_get_update_interrupt_flag(YZF_TIM_POINTER p_tim,YZF_BOOL isClear);

/**
 * 生成时钟更新事件
 * @note 全部支持
 *
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_create_update_event(YZF_TIM_POINTER p_tim);

/**
 * 计数器 获取/设置
 * @note 全部支持
 *
 * @checked STM32H723k
 * */
YZF_RESULT yzf_tim_set_cnt(YZF_TIM_POINTER p_tim, uint32_t cnt);
YZF_RESULT yzf_tim_get_cnt(YZF_TIM_POINTER p_tim, uint32_t *cnt);

/**
 * 预分频 获取/设置
 * f(out) = f(APB)/[(psc+1)*(arr)*(clk_division)]
 * @note 全部支持
 * */
YZF_RESULT yzf_tim_set_prescaler(YZF_TIM_POINTER p_tim, uint16_t prescaler);
YZF_RESULT yzf_tim_get_prescaler(YZF_TIM_POINTER p_tim, uint16_t *prescaler);

/**
 * 自动加载寄存器 获取/设置
 * @note 全部支持
 *
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_set_auto_reload_number(YZF_TIM_POINTER p_tim,uint16_t arr);
YZF_RESULT yzf_tim_set_auto_reload_number32(YZF_TIM_POINTER p_tim,uint32_t arr);
YZF_RESULT yzf_tim_get_auto_reload_number(YZF_TIM_POINTER p_tim,uint16_t *arr);

/**
 * 主模式选择
 * 这些位可选择主模式下将要发送到从定时器以实现同步的信息 (TRGO)。这些位的组合如下：
 * <br000：复位——TIMx_EGR 寄存器中的 UG 位用作触发输出 (TRGO)。如果复位由触发输入
 * 生成（从模式控制器配置为复位模式），则 TRGO 上的信号相比实际复位会有延迟。
 * <br001：使能—— 计数器使能信号 CNT_EN 用作触发输出 (TRGO)。该触发输出可用于同时启
 * 动多个定时器，或者控制在一段时间内使能从定时器。计数器使能信号由 CEN 控制位与门
 * 控模式下的触发输入的逻辑或运算组合而成。
 * 当计数器使能信号由触发输入控制时，TRGO 上会存在延迟，选择主/从模式时除外（请参见
 * TIMx_SMCR 寄存器中 MSM 位的说明）。
 * <br010：更新——选择更新事件作为触发输出 (TRGO)。例如，主定时器可用作从定时器的预分
 * 频器。
 * <br011：比较脉冲——一旦发生输入捕获或比较匹配事件，当 CC1IF 标志被置 1 时（即使已为
 * 高电平），触发输出都会发送一个正脉冲。(TRGO)
 * <br100：比较——OC1REF 信号用作触发输出 (TRGO)
 * <br101：比较——OC2REF 信号用作触发输出 (TRGO)
 * <br110：比较——OC3REF 信号用作触发输出 (TRGO)
 * <br111：比较——OC4REF 信号用作触发输出 (TRGO)
 * @note for STM32H723 only TIM1 and TIM8
 * @cheked STM32H723
 * */
YZF_RESULT yzf_tim_master_mode_select(YZF_TIM_POINTER p_tim,uint16_t mms);

/**
 * 出发输入选择
 *
 * <br>00000：内部触发 0 (ITR0)
 * <br>00001：内部触发 1 (ITR1)
 * <br>00010：内部触发 2 (ITR2)
 * <br>00011：内部触发 3 (ITR3)
 * <br>00100：TI1 边沿检测器 (TI1F_ED)
 * <br>00101：滤波后的定时器输入 1 (TI1FP1)
 * <br>00110：滤波后的定时器输入 2 (TI2FP2)
 * <br>00111：外部触发输入 (ETRF)
 * <br>01000：内部触发 4 (ITR4)
 * <br>01001：内部触发 5 (ITR5)
 * <br>01010：内部触发 6 (ITR6)
 * <br>01011：内部触发 7 (ITR7)
 * <br>01100：内部触发 8 (ITR8)
 *
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_trigger_select(YZF_TIM_POINTER p_tim,uint16_t trigger);

/**
 * 从模式选择
 *
 * <br>0000：禁止从模式——如果 CEN =“1”，预分频器时钟直接由内部时钟提供。
 * <br>0001：编码器模式 1——计数器根据 TI2FP2 电平在 TI1FP1 边沿递增/ 递减计数。
 * <br>0010：编码器模式 2——计数器根据 TI1FP1 电平在 TI2FP2 边沿递增/ 递减计数。
 * <br>0011：编码器模式 3—— 计数器在 TI1FP1 和 TI2FP2 的边沿计数，计数的方向取决于另外
 * 一个输入的电平。
 * <br>0100：复位模式—— 在出现所选触发输入 (TRGI) 上升沿时，重新初始化计数器并生成一个
 * 寄存器更新事件。
 * <br>0101：门控模式—— 触发输入 (TRGI) 为高电平时使能计数器时钟。只要触发输入变为低电
 * 平，计数器立即停止计数（但不复位）。计数器的启动和停止都被控制。
 * <br>0110：触发模式 ——触发信号 TRGI 出现上升沿时启动计数器（但不复位）。只控制计数器
 * 的启动。
 * <br>0111：外部时钟模式 1——由所选触发信号 (TRGI) 的上升沿提供计数器时钟。
 * <br>1000：组合复位 + 触发模式—— 在出现所选触发输入 (TRGI) 上升沿时，重新初始化计数
 * 器，生成一个寄存器更新事件并启动计数器。
 *
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_slave_mode_select(YZF_TIM_POINTER p_tim,uint16_t sms);

/**
 * 主从模式开启
 * <br>0: 无
 * <br>1： 当前定时器的触发输入事件 (TRGI) 的动作被推迟，以使当前定时器与其从定时器实现完
 * 美同步（通过 TRGO）。此设置适用于由单个外部事件对多个定时器进行同步的情况。
 *
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_master_slave_mode_enable(YZF_TIM_POINTER p,uint16_t enable);

/**
 *  TIMx 捕获/比较模式寄存器 TIMx capture/compare mode register
 * @note
 * 这些位定义提供 OC1 和 OC1N 的输出参考信号 OC1REF 的行为。OC1REF 为高电平有
 * 效，而 OC1 和 OC1N 的有效电平则取决于 CC1P 位和 CC1NP 位。
 * <br>0000：冻结—— 输出比较寄存器 TIMx_CCR1 与计数器 TIMx_CNT 进行比较不会对输出造
 * 成任何影响。（该模式用于生成时基）。
 * <br>0001：将通道 1 设置为匹配时输出有效电平。当计数器 TIMx_CNT 与捕获/ 比较寄存器 1
 * (TIMx_CCR1) 匹配时，OC1REF 信号强制变为高电平。
 * <br>0010：将通道 1 设置为匹配时输出无效电平。当计数器 TIMx_CNT 与捕获/ 比较寄存器 1
 * (TIMx_CCR1) 匹配时，OC1REF 信号强制变为低电平。
 * <br>0011：翻转——TIMx_CNT=TIMx_CCR1 时，OC1REF 发生翻转。
 * <br>0100：强制变为无效电平——OC1REF 强制变为低电平。
 * <br>0101：强制变为有效电平——OC1REF 强制变为高电平。
 * <br>0110：PWM 模式 1——在递增计数模式下，只要 TIMx_CNT<TIMx_CCR1，通道 1 便为有
 * 效状态，否则为无效状态。在递减计数模式下，只要 TIMx_CNT>TIMx_CCR1，通道 1 便为
 * 无效状态 (OC1REF=0)，否则为有效状态 (OC1REF=1)。
 * <br>0111：PWM 模式 2—— 在递增计数模式下，只要 TIMx_CNT<TIMx_CCR1，通道 1 便为无
 * 效状态，否则为有效状态。在递减计数模式下，只要 TIMx_CNT>TIMx_CCR1，通道 1 便为
 * 有效状态，否则为无效状态。
 * <br>1000：可再触发 OPM 模式 1—— 在递增计数模式下，通道为有效状态，直至（在 TRGI 信
 * 号上）检测到触发事件。然后，在 PWM 模式 1 下进行比较，通道会在下一次更新时再次变
 * 为无效状态。在递减计数模式下，通道为无效状态，直至（在 TRGI 信号上）检测到触发事
 * 件。然后，在 PWM 模式 1 下进行比较，通道会在下一次更新时再次变为无效状态。
 * <br>1001：可再触发 OPM 模式 2—— 在递增计数模式下，通道为无效状态，直至（在 TRGI 信
 * 号上）检测到触发事件。然后，在 PWM 模式 2 下进行比较，通道会在下一次更新时再次变
 * 为无效状态。在递减计数模式下，通道为有效状态，直至（在 TRGI 信号上）检测到触发事
 * 件。然后，在 PWM 模式 2 下进行比较，通道会在下一次更新时再次变为有效状态。
 * <br>1010：保留。
 * <br>1011：保留。
 * <br>1100：组合 PWM 模式 1——OC1REF 与在 PWM 模式 1 下的行为相同。OC1REFC 是
 * OC1REF 和 OC2REF 的逻辑或运算结果。
 * <br>1101：组合 PWM 模式 2——OC1REF 与在 PWM 模式 2 下的行为相同。OC1REFC 是
 * OC1REF 和 OC2REF 的逻辑与运算结果。
 * <br>1110：不对称 PWM 模式 1——OC1REF 与在 PWM 模式 1 下的行为相同。计数器递增计数
 * 时，OC1REFC 输出 OC1REF；计数器递减计数时，OC1REFC 输出 OC2REF。
 * <br>1111：不对称 PWM 模式 2——OC1REF 与在 PWM 模式 2 下的行为相同。计数器递增计数
 * 时，OC1REFC 输出 OC1REF；计数器递减计数时，OC1REFC 输出 OC2REF。
 *
 * @cheked STM32H723
 * */
YZF_RESULT yzf_tim_out_compare_mode_set(YZF_TIM_POINTER p,uint16_t ch_id,uint16_t mode);


/**
 * 主输出使能
 * @checked STM32H723
 * */
YZF_RESULT yzf_tim_main_out_enable(YZF_TIM_POINTER p,YZF_BOOL isEnable);

YZF_RESULT yzf_tim_break_enable(YZF_TIM_POINTER p,YZF_BOOL isEnable);

/**
 * TIMx 捕获/比较使能寄存器
 *
 * @cheked STM32H723
 * */
YZF_RESULT yzf_tim_capture_compare_enable(YZF_TIM_POINTER p_tim,uint16_t ch_id,YZF_BOOL isEnable);
YZF_RESULT yzf_tim_capture_compare_preload_enable(YZF_TIM_POINTER p_tim,uint16_t ch_id,YZF_BOOL isEnable);
YZF_RESULT yzf_tim_capture_compare_data_set(YZF_TIM_POINTER p_tim,uint16_t ch_id,uint32_t data);
#ifdef __cplusplus
}
#endif
#endif //STM32F407RTOS_YZF_TIM_H
