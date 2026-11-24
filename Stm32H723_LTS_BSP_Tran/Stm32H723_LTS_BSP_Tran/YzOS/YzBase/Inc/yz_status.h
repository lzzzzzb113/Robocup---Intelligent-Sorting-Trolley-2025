//
// Created by 32827 on 2023/11/23.
//

#ifndef YZ_STATUS_H
#define YZ_STATUS_H
#include "yz.h"
#include "yzf_global_sheet.h"

#ifdef __cplusplus
extern "C" {
#endif

enum YZ_PROGRAM_FLAG{
    YZ_FLAG_STOP=0,
    YZ_FLAG_ERROR_HANDLER_INDEX=1,//to suit YZF_GLOBAL_INDEX
    YZ_SHEET_POINTER_FOR_UI_ROOT,//Set By System,use to find ui root in global_sheet index
    YZ_SHEET_POINTER_FOR_UI_VIEW,//Set By User boot view's index in global_sheet index
    YZ_SHEET_POINTER_FOR_UI_VIEW_INIT_DATA,//Set By User boot view's init data in global_sheet index
    YZ_FLAG_ERROR_TYPE,
};
typedef enum YZ_PROGRAM_FLAG YZ_PROGRAM_FLAG;

YZF_GLOBAL_INDEX yz_status_sheet_get(YZ_PROGRAM_FLAG index);
YZF_GLOBAL_INDEX* yz_status_sheet_get_ptr(YZ_PROGRAM_FLAG index);
void yz_status_sheet_set(YZ_PROGRAM_FLAG index,YZF_GLOBAL_INDEX data);

#ifdef __cplusplus
};
#endif
#endif //YZ_STATUS_H
