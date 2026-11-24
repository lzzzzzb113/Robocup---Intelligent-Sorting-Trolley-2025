//
// Created by 32827 on 2023/11/17.
//

#ifndef YZF_GLOBAL_SHEET_H
#define YZF_GLOBAL_SHEET_H
#include "yzf.h"
#ifdef __cplusplus
extern "C" {
#endif
#define YZF_GLOBAL_SHEET_HANDLER_SIZE 32
#define YZF_GLOBAL_SHEET_DATA_SIZE 128
#define YZF_GLOBAL_SHEET_ERROR_INDEX (-1)
    typedef int16_t YZF_GLOBAL_INDEX;
    typedef void* YZF_GLOBAL_DATA_POINTER;

    /**
     * @return 返回索引，当为-1时，表示表已满
     * */
    YZF_GLOBAL_INDEX yzf_global_handler_add(YZF_RESULT (*process)());

    /**
     * 全局事件循环，请在程序循环中调用
     * @param re_index 当有错误返回时，返回报错的处理函数指针
     * @return 返回处理函数报错或顺利结束标志(HAL_OK)
     * */
    YZF_RESULT yzf_global_loop(YZF_GLOBAL_INDEX *re_index);

    YZF_GLOBAL_INDEX yzf_global_data_add(YZF_GLOBAL_DATA_POINTER dataPointer);
    YZF_GLOBAL_DATA_POINTER yzf_global_data_get(YZF_GLOBAL_INDEX dataIndex);
    ///@return 返回被替换的数据指针
    YZF_GLOBAL_DATA_POINTER yzf_global_data_change(YZF_GLOBAL_INDEX dataIndex,YZF_GLOBAL_DATA_POINTER newData);
    YZF_RESULT yzf_global_data_addRef(YZF_GLOBAL_INDEX dataIndex);
    YZF_RESULT yzf_global_data_delRef(YZF_GLOBAL_INDEX dataIndex);
#ifdef __cplusplus
}
#endif
#endif //YZF_GLOBAL_SHEET_H
