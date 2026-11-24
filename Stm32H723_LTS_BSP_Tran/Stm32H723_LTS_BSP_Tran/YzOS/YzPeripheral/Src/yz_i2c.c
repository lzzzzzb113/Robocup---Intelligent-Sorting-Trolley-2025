//
// Created by 32827 on 2023/11/26.
//
#include "yz_i2c.h"
#include "yzf_i2c.h"
YZF_RESULT yz_i2c_add7_high_open(YZF_I2C_POINTER i2c,uint8_t address,uint8_t clockFreq){
//    yzf_i2c_open(i2c);
//    yzf_i2c_soft_reset(i2c);
//    yzf_i2c_soft_reset_clear(i2c);
//
//    yzf_i2c_set_high_mode(i2c);
//    yzf_i2c_duty_cycle_2(i2c);
//    yzf_i2c_source_clock_freq(i2c,clockFreq);
//    yzf_i2c_set_CCR(i2c,(clockFreq*1000)/(3*400));//36*1000khz/400*3khz
//    yzf_i2c_trise(i2c,(3*clockFreq/10)+1);
//    yzf_i2c_set_address_7(i2c,address);
//
//    yzf_i2c_ack_enable(i2c);
//    yzf_i2c_enable(i2c);
    return YZF_OK;
}
YZF_RESULT yz_i2c_add7_normal_open(YZF_I2C_POINTER i2c,uint8_t address,uint8_t clockFreq){
//    yzf_i2c_open(i2c);
//    yzf_i2c_soft_reset(i2c);
//    yzf_i2c_soft_reset_clear(i2c);
//
//    yzf_i2c_set_normal_mode(i2c);
//    yzf_i2c_duty_cycle_2(i2c);
//    yzf_i2c_source_clock_freq(i2c,clockFreq);
//    yzf_i2c_set_CCR(i2c,(clockFreq*1000)/(2*100));
//    yzf_i2c_trise(i2c,(10*clockFreq/10)+1);
//    yzf_i2c_set_address_7(i2c,address);
//
//    yzf_i2c_ack_enable(i2c);
//    yzf_i2c_enable(i2c);
    return YZF_OK;
}
YZF_RESULT yz_i2c_add7_transmit(YZF_I2C_POINTER i2c,uint8_t address,uint8_t* data,uint16_t length){
    uint16_t len=0;

    yzf_i2c_ack_enable(i2c);
    while (yzf_i2c_flag_BUSY(i2c)==YZF_TRUE);

    yzf_i2c_send_address_7(i2c,address);
    yzf_i2c_set_cnt(i2c,length);
    yzf_i2c_mode_write(i2c);
    yzf_i2c_start(i2c);

    while(length--){
        while(yzf_i2c_flag_TxISE(i2c)==YZF_FALSE);
        yzf_i2c_write_data(i2c,data[len]);
        len++;
    }
    while(yzf_i2c_flag_TxE(i2c)==YZF_FALSE);
    yzf_i2c_stop(i2c);
    yzf_i2c_ack_disable(i2c);
    while (yzf_i2c_flag_STOPF(i2c)==YZF_FALSE);

    yzf_i2c_flag_clear_STOPF(i2c);
    return YZF_OK;
}

YZF_RESULT yz_i2c_add7_receive(YZF_I2C_POINTER i2c,uint8_t address,uint8_t* data,uint16_t length){
    uint16_t len=0;

    yzf_i2c_ack_enable(i2c);
    yzf_i2c_flag_clear_AF(i2c);
    while (yzf_i2c_flag_BUSY(i2c)==YZF_TRUE);

    yzf_i2c_send_address_7(i2c,address);
    yzf_i2c_set_cnt(i2c,length);
    yzf_i2c_mode_read(i2c);
    yzf_i2c_start(i2c);

    while(length--){
        while(yzf_i2c_flag_RxNE(i2c)==YZF_FALSE){
            if(yzf_i2c_flag_AF(i2c)==YZF_TRUE){
                yzf_i2c_stop(i2c);
                while (yzf_i2c_flag_STOPF(i2c)==YZF_FALSE);
                yzf_i2c_flag_clear_STOPF(i2c);
                yzf_i2c_flag_clear_AF(i2c);
                return YZF_ERROR;
            }
        }
        data[len]= yzf_i2c_read_data(i2c);
        len++;
        if(length==1){
            yzf_i2c_ack_disable(i2c);
            yzf_i2c_stop(i2c);
        }
    }

    while (yzf_i2c_flag_STOPF(i2c)==YZF_FALSE);

    yzf_i2c_flag_clear_STOPF(i2c);
    return YZF_OK;
}
YZF_RESULT yz_i2c_add7_mem_receive(YZF_I2C_POINTER i2c,uint8_t address,uint8_t memAddress,uint8_t* data,uint16_t length){
    uint16_t len=0;

    yzf_i2c_ack_enable(i2c);
    while (yzf_i2c_flag_BUSY(i2c)==YZF_TRUE);

    yzf_i2c_send_address_7(i2c,address);
    yzf_i2c_set_cnt(i2c,1);
    yzf_i2c_mode_write(i2c);
    yzf_i2c_disable_autoEnd(i2c);
    yzf_i2c_start(i2c);

    while(yzf_i2c_flag_TxISE(i2c)==YZF_FALSE);
    yzf_i2c_write_data(i2c,memAddress);
    while(yzf_i2c_flag_TC(i2c)==YZF_FALSE);


    yzf_i2c_set_cnt(i2c,length);
    yzf_i2c_mode_read(i2c);
    yzf_i2c_start(i2c);
    yzf_i2c_enable_autoEnd(i2c);

    while(length--){
        while(yzf_i2c_flag_RxNE(i2c)==YZF_FALSE);
        data[len]= yzf_i2c_read_data(i2c);
        len++;
        if(length==1){
            yzf_i2c_ack_disable(i2c);
            yzf_i2c_stop(i2c);
        }
    }
    while (yzf_i2c_flag_STOPF(i2c)==YZF_FALSE);

    yzf_i2c_flag_clear_STOPF(i2c);

    return YZF_OK;
}
YZF_RESULT yz_i2c_add7_mem_transmit(YZF_I2C_POINTER i2c,uint8_t address,uint8_t memAddress,uint8_t* data,uint16_t length){
    uint16_t len=0;

    yzf_i2c_ack_enable(i2c);
    while (yzf_i2c_flag_BUSY(i2c)==YZF_TRUE);

    yzf_i2c_send_address_7(i2c,address);
    yzf_i2c_set_cnt(i2c,length+1);
    yzf_i2c_mode_write(i2c);
    yzf_i2c_start(i2c);

    while(yzf_i2c_flag_TxISE(i2c)==YZF_FALSE);
    yzf_i2c_write_data(i2c,memAddress);

    while(length--){
        while(yzf_i2c_flag_TxISE(i2c)==YZF_FALSE);
        yzf_i2c_write_data(i2c,data[len]);
        len++;
    }

    while(yzf_i2c_flag_TxE(i2c)==YZF_FALSE);
    yzf_i2c_stop(i2c);
    yzf_i2c_ack_disable(i2c);
    while (yzf_i2c_flag_STOPF(i2c)==YZF_FALSE);

    yzf_i2c_flag_clear_STOPF(i2c);
    return YZF_OK;
}
YZF_RESULT yz_i2c_add7_cmd_receive(YZF_I2C_POINTER i2c,uint8_t address,uint8_t memAddress,uint8_t* data,uint16_t length){
    uint16_t len=0;
    yzf_i2c_ack_enable(i2c);
    while (yzf_i2c_flag_BUSY(i2c)==YZF_TRUE);

    yzf_i2c_send_address_7(i2c,address);
    yzf_i2c_mode_write(i2c);
    yzf_i2c_set_cnt(i2c,1);
    yzf_i2c_disable_autoEnd(i2c);
    yzf_i2c_start(i2c);

    while(yzf_i2c_flag_TxISE(i2c)==YZF_FALSE){
        if(yzf_i2c_flag_AF(i2c)==YZF_TRUE){
            yzf_i2c_stop(i2c);
            while (yzf_i2c_flag_STOPF(i2c)==YZF_FALSE);
            yzf_i2c_flag_clear_STOPF(i2c);
            yzf_i2c_flag_clear_AF(i2c);
            return YZF_ERROR;
        }
    }
    yzf_i2c_write_data(i2c,memAddress);
    while(yzf_i2c_flag_TC(i2c)==YZF_FALSE){
        if(yzf_i2c_flag_STOPF(i2c)){
            yzf_i2c_flag_clear_STOPF(i2c);
            return YZF_ERROR;
        }
    }


    yzf_i2c_set_cnt(i2c,length);
    yzf_i2c_mode_read(i2c);
    yzf_i2c_start(i2c);
    yzf_i2c_enable_autoEnd(i2c);

    while(length--){
        while(yzf_i2c_flag_RxNE(i2c)==YZF_FALSE);
        data[len]= yzf_i2c_read_data(i2c);
        len++;
        if(length==1){
            yzf_i2c_ack_disable(i2c);
            yzf_i2c_stop(i2c);
        }
    }
    while (yzf_i2c_flag_STOPF(i2c)==YZF_FALSE);

    yzf_i2c_flag_clear_STOPF(i2c);

    return YZF_OK;
}