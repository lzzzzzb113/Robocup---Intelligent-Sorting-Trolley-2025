//
// Created by 32827 on 2025/7/9.
//
#include "yzl_i2c_tcs34727.h"
#include "yz_log.h"

YZF_RESULT yzl_i2c_tcs34727_init(YZF_I2C_POINTER i2c){
    uint8_t dev_id=0;
    yz_i2c_add7_mem_receive(i2c, TCS34725_ADDRESS, TCS34725_COMMAND_BIT|TCS34725_ID,(uint8_t *) &dev_id, 1);
    if(dev_id==0x4D){
        yz_info("found TCS34727.\n",dev_id);

        dev_id=TCS34725_INTEGRATIONTIME_700MS; //ATIME = 50ms
        yz_i2c_add7_mem_transmit(i2c,TCS34725_ADDRESS,TCS34725_COMMAND_BIT|TCS34725_ATIME,&dev_id,1);

        dev_id=TCS34725_GAIN_1X;
        yz_i2c_add7_mem_transmit(i2c,TCS34725_ADDRESS,TCS34725_COMMAND_BIT|TCS34725_CONTROL,&dev_id,1);

        dev_id=TCS34725_ENABLE_PON;
        yz_i2c_add7_mem_transmit(i2c,TCS34725_ADDRESS,TCS34725_COMMAND_BIT|TCS34725_ENABLE,&dev_id,1);

        dev_id=TCS34725_ENABLE_PON|TCS34725_ENABLE_AEN;
        yz_i2c_add7_mem_transmit(i2c,TCS34725_ADDRESS,TCS34725_COMMAND_BIT|TCS34725_ENABLE,&dev_id,1);
        return YZF_OK;
    }else{
        yz_error("not found TCS34727.\n",dev_id);
        return YZF_ERROR;
    }
}

YZF_RESULT yzl_i2c_tcs34727_get_rgb(YZF_I2C_POINTER i2c,YZLSensorDataCRGB *rgb){
    yz_i2c_add7_mem_receive(i2c, TCS34725_ADDRESS, TCS34725_COMMAND_BIT|0x20|TCS34725_CDATAL,(uint8_t *) rgb, 8);
    return YZF_OK;
}