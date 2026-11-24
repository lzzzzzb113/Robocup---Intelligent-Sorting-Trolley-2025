//
// Created by 32827 on 2025/4/25.
//

#ifndef YZL_TRANSFORM_SEGMENT_H
#define YZL_TRANSFORM_SEGMENT_H
#include "yzl_math.h"


#ifdef   __cplusplus
extern "C"
{
#endif
/**
 * 变化曲线，可用于动作渐变，或者动画效果
 * */

/**
 * f(x) = -2t^3 + 3t^2
 * 先快后慢
 * @param t [0,1]
 * @return [0,1]
 * */
y_f32 yzl_math_transform_a2(y_f32 t);

/**
 * f(x) = 1/(1+e^(-k(t-0.5)))
 * Sigmoid函数，将变量映射到[0,1]之间，k与曲线平滑，增减有关。
 * @tparam t [0,1]
 * @tparam k [0,1]
 * */

y_f32 yzl_math_transform_sigmoid(y_f32 t,y_f32 k);

#ifdef   __cplusplus
}
#endif
#endif //YZL_TRANSFORM_SEGMENT_H
