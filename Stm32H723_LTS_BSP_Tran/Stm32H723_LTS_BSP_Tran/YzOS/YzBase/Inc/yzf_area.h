//
// Created by 32827 on 2023/11/17.
//

#ifndef YZF_AREA_H
#define YZF_AREA_H
#include "yzf.h"
#include "yzf_global_sheet.h"
#ifdef __cplusplus
extern "C" {
#endif
#define YZF_AREA_RECV_SIZE 1024
    /**
    * 数据未超出部分由函数处理
    * 超出部分交予事件监听器处理，未设置会丢失数据
    * */
    /**
     * 传输协议 用GLOBAL_SHEET_DATA传递参数,返回值保存到GLOBAL_SHEET_DATA
     * */
    enum yzf_recv_event{
        recv_full,  ///区域超出 @param (YZF_GLOBAL_INDEX:YZF_RECV_DATA data) 数据 @return (YZF_GLOBAL_INDEX:void)
        recv_get,   ///区域获取 @param (YZF_GLOBAL_INDEX:YZF_RECV_DATA_INDEX index) 超出数据的索引 @return (YZF_GLOBAL_INDEX:YZF_RECV_DATA data) 数据
        recv_read_ptr, ///区域获取 @param (YZF_GLOBAL_INDEX:YZF_RECV_DATA* index) 返回数据的保存地址 @return (YZF_GLOBAL_INDEX:YZF_RECV_DATA* read_ptr) 读取指针
        recv_end_ptr,  ///区域获取 @param (YZF_GLOBAL_INDEX:YZF_RECV_DATA* index) 返回数据的线性结束地址 @return (YZF_GLOBAL_INDEX:YZF_RECV_DATA* read_ptr) 结束地址指针
        recv_del       ///区域删除  @param (YZF_GLOBAL_INDEX:YZF_RECV_DATA len) 要删除的长度 @return (YZF_GLOBAL_INDEX:void)
    };
    typedef enum yzf_recv_event YZF_RECV_EVENT;

    typedef uint8_t YZF_RECV_DATA;
    typedef uint16_t YZF_RECV_DATA_INDEX;

    struct YZF_RECV_AREA {
        YZF_RECV_DATA yzf_recv[YZF_AREA_RECV_SIZE];         //数据保存
        YZF_RECV_DATA_INDEX yzf_recv_write_ptr;            //写指针
        YZF_RECV_DATA_INDEX yzf_recv_read_ptr;             //读指针
        YZF_RECV_DATA_INDEX yzf_recv_size;                 //数据数量
        uint32_t yzf_area_recv_add_count;
        uint32_t yzf_area_recv_del_count;
        void (*yzf_recv_listener)(YZF_RECV_EVENT event,struct YZF_RECV_AREA* area,YZF_GLOBAL_INDEX dataIndex); //事件回调函数
    };
    typedef struct YZF_RECV_AREA YZF_RECV;

    /**
     * 接收区域初始化
     * */
    void yzf_area_recv_init(YZF_RECV *area,void (*listener)(YZF_RECV_EVENT event,struct YZF_RECV_AREA* area,YZF_GLOBAL_INDEX dataIndex));
    ///提取数据(自动删除) 提取失败返回EOF
    YZF_RECV_DATA yzf_area_recv_get(YZF_RECV *area);
    ///填入数据
    void yzf_area_recv_add(YZF_RECV *area,YZF_RECV_DATA t);
    ///获取数据长度
    YZF_RECV_DATA_INDEX yzf_area_recv_get_size(YZF_RECV *area);
    ///获取读取指针 用于其他函数处理循环 分段线性传输
    YZF_RECV_DATA * yzf_area_recv_get_read_ptr(YZF_RECV *area);
    ///@return 本次线性传输能到达的结尾
    YZF_RECV_DATA * yzf_area_recv_get_end_ptr(YZF_RECV *area);
//    ///@return 数据区域的起始地址
//    YZF_RECV_DATA * yzf_area_recv_get_std_ptr(YZF_RECV *area);
    ///删除数据
    void yzf_area_recv_del(YZF_RECV *area,YZF_RECV_DATA_INDEX len);
    uint32_t yzf_area_recv_add_count(YZF_RECV *area);
    uint32_t yzf_area_recv_del_count(YZF_RECV *area);
    YZF_RECV_DATA_INDEX yzf_area_line_lenght(YZF_RECV *area);
#ifdef __cplusplus
}
#endif
#endif //YZF_AREA_H
