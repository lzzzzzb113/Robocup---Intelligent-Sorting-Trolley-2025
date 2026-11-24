//
// Created by 32827 on 2023/11/23.
//
#include "yz_status.h"

YZF_GLOBAL_INDEX yz_status_sheet[YZ_BASE_PROGRAM_STATUS_SHEET_SIZE]={YZF_NULL_PTR};

YZF_GLOBAL_INDEX yz_status_sheet_get(YZ_PROGRAM_FLAG index){
    return yz_status_sheet[index];
}
void yz_status_sheet_set(YZ_PROGRAM_FLAG index,YZF_GLOBAL_INDEX data){
    yz_status_sheet[index]=data;
}
YZF_GLOBAL_INDEX* yz_status_sheet_get_ptr(YZ_PROGRAM_FLAG index){
    return &yz_status_sheet[index];
}