//
// Created by 32827 on 2024/11/22.
//

#ifndef LINEAR_MODEL_H
#define LINEAR_MODEL_H

#include "yzl_math.h"
#include "yzl_mem.h"

typedef struct {
    y_f32 x;
    y_f32 y;
} linear_model_point;

typedef struct {
    y_f32 w;
    y_f32 b;
} linear_model_result;

typedef struct {
    y_i32 width;
    y_i32 height;
    linear_model_point *points; //A[width|height]矩阵
    linear_model_result *results;
} linear_model;

void yzl_linear_model_init(linear_model *model);
void yzl_linear_model_complete(linear_model *model);
void yzl_linear_model_deinit(linear_model *model);

#endif //LINEAR_MODEL_H
