//
// Created by 32827 on 2024/11/22.
//

#ifndef YZ_HEART_H
#define YZ_HEART_H

#include "yzf_global_sheet.h"

#ifdef __cplusplus
extern "C" {
#endif

void yz_heart_handler(uint32_t tick);

YZF_GLOBAL_INDEX yz_heart_process_add(YZF_RESULT (*process)(uint32_t tick));

#ifdef __cplusplus
};
#endif

#endif //YZ_HEART_H
