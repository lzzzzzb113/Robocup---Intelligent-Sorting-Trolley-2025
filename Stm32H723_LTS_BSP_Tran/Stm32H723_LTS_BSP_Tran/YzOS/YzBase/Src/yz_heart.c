//
// Created by 32827 on 2024/11/22.
//
#include "yz_heart.h"

void* yz_heart_process_sheet[YZ_BASE_HEART_PROCESS_NUM]={YZF_NULL_PTR};

void yz_heart_handler(uint32_t tick){;
    for (YZF_GLOBAL_INDEX i = 0; i < YZ_BASE_HEART_PROCESS_NUM; i++) {
        if(yz_heart_process_sheet[i]!=YZF_NULL_PTR){
            YZF_RESULT re=((YZF_RESULT (*)(uint32_t tick))yz_heart_process_sheet[i])(tick);
            if(re==YZF_OK){
                ///函数处理结束清除
                yz_heart_process_sheet[i]=YZF_NULL_PTR;
            }else if(re!=YZF_HANDLER_NOT_FINISH){
                YZF_ERROR_HANDLE(re);
            }
        }
    }
}

YZF_GLOBAL_INDEX yz_heart_process_add(YZF_RESULT (*process)(uint32_t tick)){
    for (YZF_GLOBAL_INDEX i = 0; i < YZ_BASE_HEART_PROCESS_NUM; i++) {
        if(yz_heart_process_sheet[i]==YZF_NULL_PTR){
            yz_heart_process_sheet[i]=process;
            return i;
        }
    }
    return YZF_GLOBAL_SHEET_ERROR_INDEX;
}