//
// Created by 32827 on 2023/11/17.
//
#include "yzf_global_sheet.h"

void* yzf_global_sheet_handler[YZF_BASE_GLOBAL_SHEET_HANDLER_SIZE]={YZF_NULL_PTR};
void* yzf_global_sheet_data[YZF_BASE_GLOBAL_SHEET_DATA_SIZE]={YZF_NULL_PTR};
uint16_t yzf_global_sheet_data_ref[YZF_BASE_GLOBAL_SHEET_DATA_SIZE]={0};
YZF_GLOBAL_INDEX yzf_global_handler_add(YZF_RESULT (*process)()){
    for (YZF_GLOBAL_INDEX i = 0; i < YZF_GLOBAL_SHEET_HANDLER_SIZE; i++) {
        if(yzf_global_sheet_handler[i]==YZF_NULL_PTR){
            yzf_global_sheet_handler[i]=process;
            return i;
        }
    }
    return YZF_GLOBAL_SHEET_ERROR_INDEX;
}
YZF_RESULT yzf_global_loop(YZF_GLOBAL_INDEX *re_index){
    YZF_RESULT rk=YZF_OK;

    for (YZF_GLOBAL_INDEX i = 0; i < YZF_GLOBAL_SHEET_HANDLER_SIZE; i++) {
        if(yzf_global_sheet_handler[i]!=YZF_NULL_PTR){
            YZF_RESULT re=((YZF_RESULT (*)())yzf_global_sheet_handler[i])();
            if(re==YZF_OK){
                ///函数处理结束清除
                yzf_global_sheet_handler[i]=YZF_NULL_PTR;
            }else if(re==YZF_NOTHING&&rk!=YZF_HANDLER_NOT_FINISH){
                //循环空闲
                rk=YZF_NOTHING; //返回这个在错误处理中可以，添加放弃抢夺CPU
            }else if(re==YZF_HANDLER_NOT_FINISH){
                rk=YZF_HANDLER_NOT_FINISH;
            } else if(re!=YZF_HANDLER_NOT_FINISH){
                ///报错处理
                *re_index=i;
                return re;
            }
        }
    }

    if(rk==YZF_HANDLER_NOT_FINISH){
        rk=YZF_OK;
    }
    return rk;
}
YZF_GLOBAL_INDEX yzf_global_data_add(YZF_GLOBAL_DATA_POINTER dataPointer){
    for (YZF_GLOBAL_INDEX i = 0; i < YZF_GLOBAL_SHEET_DATA_SIZE; i++) {
        if(yzf_global_sheet_data[i]==YZF_NULL_PTR){
            yzf_global_sheet_data[i]=dataPointer;
            yzf_global_data_addRef(i);
            return i;
        }
    }
    return YZF_GLOBAL_SHEET_ERROR_INDEX;
}
YZF_GLOBAL_DATA_POINTER yzf_global_data_get(YZF_GLOBAL_INDEX dataIndex){
    if(dataIndex==-1){
        return YZF_NULL_PTR;
    }
    return yzf_global_sheet_data[dataIndex];
}
YZF_RESULT yzf_global_data_addRef(YZF_GLOBAL_INDEX dataIndex){
    ///数据存取错误
    if(dataIndex==YZF_GLOBAL_SHEET_ERROR_INDEX){
        return YZF_ERROR;
    }
    yzf_global_sheet_data_ref[dataIndex]+=1;
    return YZF_OK;
}
YZF_RESULT yzf_global_data_delRef(YZF_GLOBAL_INDEX dataIndex){
    if(dataIndex==YZF_GLOBAL_SHEET_ERROR_INDEX||yzf_global_sheet_data_ref[dataIndex]==0){
        return YZF_ERROR;
    }
    yzf_global_sheet_data_ref[dataIndex]-=1;
    if(yzf_global_sheet_data_ref[dataIndex]==0){
        yzf_global_sheet_data[dataIndex]=YZF_NULL_PTR;
    }
    return YZF_OK;
}