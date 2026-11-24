//
// Created by 32827 on 2025/9/17.
//

#ifndef YZ_TIME_AREA_H
#define YZ_TIME_AREA_H

#include "yzf_area.h"

#define YZ_RECV_AREA_TIME_TEXT_BUF_SIZE 256
/**
 * @brief 在普通area中加入按时间分段数据
 *
 * */
#ifdef __cplusplus
extern "C" {
#endif


    typedef struct  {   //兼容YZF_RECV
        YZF_RECV base;
        YZF_BOOL inRecv;
        YZF_BOOL lockRecv;      //锁定接收
        uint32_t outDateTime;
        uint32_t lastRecvTime;
        uint32_t recvStartIndex;
        uint8_t textBuf[YZ_RECV_AREA_TIME_TEXT_BUF_SIZE];
        uint32_t recvLen;
        void (*yz_recv_listener)(void *recvTime,char ch, uint32_t time);//处理输入
        void (*yz_recv_callback)(char *text);                           //回调函数
    } YZ_RECV_TIME;

    void yz_area_recv_time_listener_default(void *recvTime,char ch, uint32_t time);
    void yz_area_recv_time_init(YZ_RECV_TIME *recvTime,uint32_t outDateTime, void (*yz_recv_listener)(void *recvTime,char ch, uint32_t time), void (*yz_recv_callback)(char *text));
    void yz_area_recv_time_update(YZ_RECV_TIME *recvTime,uint32_t time);
    void yz_area_recv_time_check(YZ_RECV_TIME *recvTime,uint32_t time);
    void yz_area_recv_time_lock(YZ_RECV_TIME *recvTime);
    void yz_area_recv_time_unlock(YZ_RECV_TIME *recvTime);
#ifdef __cplusplus
}
#endif

#endif //YZ_TIME_AREA_H
