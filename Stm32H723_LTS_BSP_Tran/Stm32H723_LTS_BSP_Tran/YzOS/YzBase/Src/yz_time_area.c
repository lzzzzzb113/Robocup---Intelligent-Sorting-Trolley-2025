//
// Created by 32827 on 2025/9/17.
//

#include "yz_time_area.h"

void yz_area_recv_time_listener_default(void *recvTime,char ch, uint32_t time){
    YZ_RECV_TIME *recvTimeTemp = (YZ_RECV_TIME *)recvTime;
    yz_area_recv_time_check(recvTimeTemp,time);
    if(!recvTimeTemp->lockRecv){
        if(recvTimeTemp->inRecv&&(time-recvTimeTemp->lastRecvTime)<=recvTimeTemp->outDateTime){
            yzf_area_recv_add(&recvTimeTemp->base,ch);
            recvTimeTemp->recvLen++;
            recvTimeTemp->lastRecvTime=time;
        }else if(recvTimeTemp->inRecv==YZF_FALSE){
            yzf_area_recv_add(&recvTimeTemp->base,ch);
            recvTimeTemp->recvLen++;
            recvTimeTemp->inRecv=YZF_TRUE;
            recvTimeTemp->lastRecvTime=time;
        }
    }else{
        //锁住时清除所有数据
        recvTimeTemp->inRecv=YZF_FALSE;
        yzf_area_recv_del(&recvTimeTemp->base,yzf_area_recv_get_size(&recvTimeTemp->base));
    }
}
void yz_area_recv_time_init(YZ_RECV_TIME *recvTime,uint32_t outDateTime, void (*yz_recv_listener)(void *recvTime,char ch, uint32_t time), void (*yz_recv_callback)(char *text)){
    recvTime->outDateTime = outDateTime;
    recvTime->yz_recv_listener = yz_recv_listener;
    recvTime->yz_recv_callback = yz_recv_callback;
    recvTime->inRecv=YZF_FALSE;
    recvTime->lastRecvTime = 0;
    recvTime->lockRecv=YZF_FALSE;
    yzf_area_recv_init(&recvTime->base,NULL);
}
void yz_area_recv_time_check(YZ_RECV_TIME *recvTime,uint32_t time){
    YZ_RECV_TIME *recvTimeTemp = (YZ_RECV_TIME *)recvTime;
    if(recvTimeTemp->inRecv&&(time-recvTimeTemp->lastRecvTime)>recvTimeTemp->outDateTime){
        for (int i = 0; i < recvTimeTemp->recvLen; i++) {
            recvTimeTemp->textBuf[i]= yzf_area_recv_get(&recvTimeTemp->base);
        }
        recvTimeTemp->textBuf[recvTimeTemp->recvLen]=0;
        recvTimeTemp->yz_recv_callback((char *)recvTimeTemp->textBuf);
        recvTimeTemp->recvLen=0;
        recvTimeTemp->inRecv=YZF_FALSE;
    }
}
void yz_area_recv_time_update(YZ_RECV_TIME *recvTime,uint32_t time){
    yz_area_recv_time_check(recvTime,time);
}
void yz_area_recv_time_lock(YZ_RECV_TIME *recvTime){
    recvTime->lockRecv=YZF_TRUE;
}
void yz_area_recv_time_unlock(YZ_RECV_TIME *recvTime){
    recvTime->lockRecv=YZF_FALSE;
}