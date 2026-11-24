//
// Created by 32827 on 2023/11/23.
//
#include "yz_main.h"
//yz全局状态表

int core_main(void){
    yz_status_sheet_set(YZ_FLAG_STOP,YZF_FALSE);
    int re=user_main();
    //当返回值不为0时,程序出错，退出程序
    if(re!=0){
        yz_error("[Core] user_main return code is %d\n",re);
        return re;
    }
    //事件循环
    while (!yz_status_sheet_get(YZ_FLAG_STOP)){
        //错误类型将被保存于 YZ_FLAG_ERROR_TYPE
        //错误句柄将被保存于 YZ_FLAG_ERROR_HANDLER_INDEX
        yz_status_sheet_set(YZ_FLAG_ERROR_TYPE,yzf_global_loop(yz_status_sheet_get_ptr(YZ_FLAG_ERROR_HANDLER_INDEX)));
        YZF_CHECK_RETURN(yz_status_sheet_get(YZ_FLAG_ERROR_TYPE)) //--> YZF_ERROR_HANDLE(YZF_RESULT error)
    }
    //循环结束后处理
    return 0;
}
void YZF_ERROR_HANDLE(YZF_RESULT error){
    user_error_handler(error);
}