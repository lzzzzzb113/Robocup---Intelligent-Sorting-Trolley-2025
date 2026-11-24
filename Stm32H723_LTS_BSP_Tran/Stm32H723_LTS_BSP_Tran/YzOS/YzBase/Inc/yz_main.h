//
// Created by 32827 on 2023/11/23.
//

#ifndef YZ_MAIN_H
#define YZ_MAIN_H
#include "yz.h"
#include "yz_log.h"
#include "yz_status.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * 需要在自己的应用中实现这两个函数
 * */
extern int user_main();
extern void user_error_handler(YZF_RESULT error);
int core_main(void);
#ifdef __cplusplus
};
#endif
#endif //YZ_MAIN_H
