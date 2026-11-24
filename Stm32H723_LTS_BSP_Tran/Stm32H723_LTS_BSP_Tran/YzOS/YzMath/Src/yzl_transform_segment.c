//
// Created by 32827 on 2025/4/25.
//

#include "../Inc/yzl_transform_segment.h"

y_f32 yzl_math_transform_a2(y_f32 t){
    if(t<0){
        t=0;
    }
    if(t>1.0f){
        t=1.0f;
    }
    return -2.0f * powf(t,3) + 3.0f * powf(t,2);
}

y_f32 yzl_math_transform_sigmoid(y_f32 t,y_f32 k){
    if(t<0){
        t=0;
    }
    if(t>1.0f){
        t=1.0f;
    }
    return 1.0f / (1.0f + expf(-k * (t - 0.5f)));
}