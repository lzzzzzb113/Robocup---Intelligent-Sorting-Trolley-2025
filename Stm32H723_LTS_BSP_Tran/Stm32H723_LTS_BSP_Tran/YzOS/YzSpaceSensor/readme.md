# YzSpaceSensor

空间计算库，目标应用于机械臂运动学解算，将以C++为主开发
依赖于 YzCWithClassSupport,YzMath及其子依赖

---

## Camera

---
设计用于解析Uart串口传递过来的摄像头识别数据

数据格式 [["x","y","w","h"],fang:"0.8889",[...],yuan:"..."]

由CameraInstance::CameraInfoDecode处理

### 请求发送

 CameraInstance::RequestCamera(int code)发送

 请求数据格式{ASCII_STX,(uint8_t)ReqCode,ASCII_ETX}
 
 回复数据格式{ASCII_STX,...,ASCII_ETX} 时间<3000ms
 
### 连接确认格式

 CameraInstance::UpdateCamera() 函数处理

 请求数据格式{ASCII_SYN}

 回复数据格式{ASCII_ACK} 时间<200ms
 
### 注意事项
 + 需要在主循环中调用CameraInstance::act()函数来实现处理函数。
 + 当前版本进行了诸多更改，请仔细检查，但协议格式未变。

### 使用实例
初始化
```c
    cameraInstance = new CameraInstance(armGroup);//使用armGroup提供全局时钟
    cameraInstance->setStatusListener(this,camera_listener);
```