//
// Created by 32827 on 2025/5/11.
//

#include "yzl_space_sensor_camera.hpp"
#include "yz_uart.h"
#include "yz_heart.h"

uint32_t CameraInstance::CameraTick = 0;

CameraInstance::CameraInstance(YZF_RECV_AREA *recArea) {
    RecArea = recArea;
    BufArea = (YZF_RECV_AREA *)YZL_MEM_MANAGER.pMalloc(sizeof (YZF_RECV_AREA));
    yzf_area_recv_init(BufArea,YZF_NULL_PTR);
    cameraStatus = DISCONNECT;
    cameraRequestStatus = REQUEST_IDLE;
    cameraReceiveStatus = RECEIVE_END;
    CameraTick = 0;
    yz_heart_process_add(CameraTickHandler);
}

void CameraInstance::act() {
    if(cameraStatus == CONNECT_CHECKING){                       //连接确定状态
        if((yzf_area_recv_get_size(RecArea)==0)&&((CameraTick-CheckStartTick))>200){    //超时无数据检测
            if(CameraStatusListener!=YZF_NULL_PTR){
                CameraStatusListener(ListenerOwner,DISCONNECT);       //连接失败
                cameraStatus = DISCONNECT;
            }else{
                cameraStatus = DISCONNECT;
            }
        }else if(yzf_area_recv_get_size(RecArea)!=0){   //取出数据确认
            while(yzf_area_recv_get_size(RecArea)!=0){
                uint8_t dat= yzf_area_recv_get(RecArea);
                if(dat==ASCII_ACK){
                    if(CameraStatusListener!=YZF_NULL_PTR){
                        CameraStatusListener(ListenerOwner,CONNECTING); //得到回应状态更新
                        cameraStatus = CONNECTING;
                        return;
                    }else{
                        cameraStatus = CONNECTING;
                        return;
                    }
                }
            }
        }
    }else if(cameraStatus == CONNECTING&&cameraRequestStatus == REQUEST_WAITING){
        if((CameraTick-RequestStartTick)>3000){
            if(CameraRequestListener!=YZF_NULL_PTR){        //大于3秒未回复返回失败
                CameraRequestListener(ListenerOwner,REQUEST_FAIL,YZF_NULL_PTR);
                cameraRequestStatus = REQUEST_IDLE;
            }else{
                cameraRequestStatus = REQUEST_IDLE;
            }
        }else if(yzf_area_recv_get_size(RecArea)!=0) {
            while (yzf_area_recv_get_size(RecArea) != 0) {
                uint8_t dat = yzf_area_recv_get(RecArea);
                if(dat==ASCII_STX&&cameraReceiveStatus==RECEIVE_WAIT_START){
                    cameraReceiveStatus = RECEIVE_START;
                }
                if(cameraReceiveStatus == RECEIVE_START&&dat!=ASCII_ETX&&dat!=ASCII_STX){
                    yzf_area_recv_add(BufArea,dat);
                }else if(cameraReceiveStatus == RECEIVE_START&&dat!=ASCII_STX){                         //解释即接收到ASCII_ETX停止接收
                    cameraReceiveStatus = RECEIVE_END;
                    if(CameraRequestListener!=YZF_NULL_PTR){
                        CameraRequestListener(ListenerRequestOwner,REQUEST_SUCCESS,BufArea);  //调用请求停止
                        cameraRequestStatus = REQUEST_IDLE;
                    }else{
                        cameraRequestStatus = REQUEST_IDLE;
                    }
                }
            }
        }
    }else if(cameraStatus == DISCONNECT){
        UpdateCamera();
    }
}

void CameraInstance::UpdateCamera() {
    cameraStatus = CONNECT_CHECKING;
    CheckStartTick = CameraTick;
    if(yzf_area_recv_get_size(RecArea)!=0){
        yzf_area_recv_del(RecArea,yzf_area_recv_get_size(RecArea));
    }
    uint8_t dat=ASCII_SYN;//SYN
    yz_uart_transmit(USART1,&dat,1);
}

void CameraInstance::setStatusListener(void *pListenerOwner,YZF_RESULT (*pCameraStatusListener)(void *, CameraStatus)) {
    this->CameraStatusListener=pCameraStatusListener;
    this->ListenerOwner=pListenerOwner;
}

void CameraInstance::RequestCamera(int ReqCode) {
    uint8_t text[3]={ASCII_STX,(uint8_t)ReqCode,ASCII_ETX};
    if(cameraStatus == CONNECTING){
        RequestStartTick = CameraTick;
        cameraRequestStatus = REQUEST_WAITING;
        cameraReceiveStatus = RECEIVE_WAIT_START;
        yz_uart_transmit(USART1,text,3);
        yzf_area_recv_del(BufArea, yzf_area_recv_get_size(BufArea));
    }
}

void CameraInstance::setRequestListener(void *ListenerOwner,
                                        YZF_RESULT (*pCameraRequestListener)(void *, CameraRequestStatus,YZF_RECV_AREA *data)) {
    this->CameraRequestListener=pCameraRequestListener;
    this->ListenerRequestOwner=ListenerOwner;
}
CameraDetectResult *CameraInstance::CameraInfoDecode(char *data, int *count) {
    CameraInfoDecodeStatus status = DECODE_IDLE;
    int result_index=0;
    for(uint32_t i = 0;i< strlen(data);i++){
        if(status==DECODE_IDLE&&data[i]=='['){
            status = DECODE_LEVEL_1;
        }else if(status==DECODE_LEVEL_1&&data[i]==']'){
            status = DECODE_SUCCESS;
        }else if(status==DECODE_LEVEL_1&&data[i]=='['){
            memset(decodeBuf,0,sizeof(decodeBuf));
            decodeBufIndex = 0;
            status = DECODE_LEVEL_2;
        }else if(status==DECODE_LEVEL_2&&data[i]==']'){
            decodeBuf[decodeBufIndex] = '\0';
            sscanf(decodeBuf,"%d,%d,%d,%d",&result[result_index].x,&result[result_index].y,&result[result_index].w,&result[result_index].h);
            int c=0;
            int p=0;
            float scale=1.0f;
            result[result_index].confidence = 0;
            for(uint32_t j = 0;j < strlen(data); j++){
                if(c==5&&data[j]<='9'&&data[j]>='0'){
                    result[result_index].confidence += ((float )(data[j]-'0'))*scale;
                    scale = scale/10.0f;
                }
                if(c==4&&data[j]!=':'){
                    result[result_index].tag[p] = data[j];
                    p++;
                }else if(c==4){
                    c++;
                    result[result_index].tag[p] = '\0';
                }
                if(data[j]==','&&c<4){
                    c++;
                }
            }
            result_index++;
            status = DECODE_LEVEL_1;
        }else if(status==DECODE_LEVEL_2){
            decodeBuf[decodeBufIndex] = data[i];
            decodeBufIndex++;
        }
    }
    if(status != DECODE_SUCCESS){
        status = DECODE_FAIL;
    }else{
        *count = result_index;
    }
    return result;
}

CameraInstance::~CameraInstance(){
    YZL_MEM_MANAGER.pFree(BufArea);
}

 YZF_RESULT CameraInstance::CameraTickHandler(uint32_t tick) {
    CameraTick += tick;
    return YZF_HANDLER_NOT_FINISH;
}
