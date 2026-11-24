//
// Created by 32827 on 2024/11/23.
//
#include "yzl_ai_bayes_filters.h"
void yzl_bayes_filter_update(y_bayes_filter * filter){
    yzl_math_normal_distribution_mul(&filter->posterior, &filter->prior, &filter->likelihood);
}