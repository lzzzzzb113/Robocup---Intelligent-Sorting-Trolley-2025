//
// Created by 32827 on 2024/5/17.
//

#ifndef STM32F407VET6_USER_H
#define STM32F407VET6_USER_H
#include "yzx_base.h"
extern YZF_GLOBAL_INDEX ui_handler; //ui 循环线程ID
int user_main();
void user_error_handler(YZF_RESULT error);
#endif //STM32F407VET6_USER_H
