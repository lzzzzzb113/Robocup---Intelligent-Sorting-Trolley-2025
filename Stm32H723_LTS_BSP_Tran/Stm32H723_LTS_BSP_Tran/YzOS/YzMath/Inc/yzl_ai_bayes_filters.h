//
// Created by 32827 on 2024/11/23.
//

#ifndef YZL_AI_BAYES_FILTERS_H
#define YZL_AI_BAYES_FILTERS_H

#include "yzx_base.h"
#include "yzl_math.h"

typedef struct
{
    y_normal_distribution  prior;
    y_normal_distribution  likelihood;
    y_normal_distribution  posterior;
} y_bayes_filter;

void yzl_bayes_filter_update(y_bayes_filter * filter);
#endif //YZL_AI_BAYES_FILTERS_H
