//
// Created by 32827 on 2024/6/27.
//
#include "yzl_softport_sccb.h"

#if USE_SOFT_PORT && YZL_SOFT_PORT_SCCB
YZF_RESULT yzl_softport_sccb_init(YZL_Soft_SCCB *sccb){
    YLGPIO(sccb->SCL);
    yzf_gpio_open_clock_();
    yzf_gpio_set_PP_();
    yzf_gpio_set_HIGH_();
    yzf_gpio_set_1_();
    yzf_gpio_set_af_(0);
    YLGPIO(sccb->SDA);
    yzf_gpio_open_clock_();
    yzl_softport_sccb_sda_out(sccb);
    yzf_gpio_set_HIGH_();
    yzf_gpio_set_1_();
    yzf_gpio_set_af_(0);
    return YZF_OK;
}
YZF_RESULT yzl_softport_sccb_sda_out(YZL_Soft_SCCB *sccb){
    yzf_gpio_set_PP(sccb->SDA.port,sccb->SDA.pin);
    return YZF_OK;
}
YZF_RESULT yzl_softport_sccb_sda_in(YZL_Soft_SCCB *sccb){
    yzf_gpio_set_IN_PULL_UP(sccb->SDA.port,sccb->SDA.pin);
    return YZF_OK;
}
YZF_RESULT yzl_softport_sccb_start(YZL_Soft_SCCB *sccb){
    yzl_softport_sccb_sda_out(sccb);
    YLHIGH(sccb->SDA);
    delay_us(50);

    YLHIGH(sccb->SCL);
    delay_us(50);

    YLLOW(sccb->SDA);
    delay_us(50);

    YLLOW(sccb->SCL);
    delay_us(50);
    return YZF_OK;
}
YZF_RESULT yzl_softport_sccb_stop(YZL_Soft_SCCB *sccb){
    yzl_softport_sccb_sda_out(sccb);
    YLLOW(sccb->SDA);
    delay_us(50);

    YLHIGH(sccb->SCL);
    delay_us(50);

    YLHIGH(sccb->SDA);
    delay_us(50);
    return YZF_OK;
}
//SCCB_D先拉高，再把SCCB_C拉高，后把SCCB_C拉低，最后把SCCB_D拉低
YZF_RESULT yzl_softport_sccb_NA(YZL_Soft_SCCB *sccb){
    yzl_softport_sccb_sda_out(sccb);
    YLHIGH(sccb->SDA);
    delay_us(50);

    YLHIGH(sccb->SCL);
    delay_us(50);

    YLLOW(sccb->SCL);
    delay_us(50);

    YLLOW(sccb->SDA);
    delay_us(50);
    return YZF_OK;
}
uint8_t yzl_softport_sccb_read_byte(YZL_Soft_SCCB *sccb){
    uint8_t read,j;
    read=0x00;

    yzl_softport_sccb_sda_in(sccb);			//设置SDA为输入
    delay_us(50);
    for(j=8;j>0;j--)
    {
        delay_us(50);
        YLHIGH(sccb->SCL);

        read=read<<1;
        if(yzf_gpio_get(sccb->SDA.port,sccb->SDA.pin)) read++;		//左移一位，若读取到高电平 read相应位写1

        delay_us(50);
        YLLOW(sccb->SCL);
    }

    yzl_softport_sccb_sda_out(sccb);
    return (read);
}
YZF_RESULT yzl_softport_sccb_write_byte(YZL_Soft_SCCB *sccb,uint8_t dat){
    YZF_RESULT temp=0;
    uint8_t  j;

    for(j=0;j<8;j++)
    {
        if((dat<<j)&0x80)	                //高位先发送
        {
            YLHIGH(sccb->SDA);
        }
        else
        {
            YLLOW(sccb->SDA);
        }
        delay_us(50);
        YLHIGH(sccb->SCL);
        delay_us(50);
        YLLOW(sccb->SCL);
    }

    yzl_softport_sccb_sda_in(sccb);			//设置SDA为输入
    delay_us(50);
    YLHIGH(sccb->SCL);				        //释放SCL 准备读取SDA的状态
    delay_us(50);
    if(yzf_gpio_get(sccb->SDA.port,sccb->SDA.pin))		//SDA=1 发送失败
    {
        temp=YZF_ERROR;
    }
    else
    {
        temp=YZF_OK;
    }
    YLLOW(sccb->SCL);				            //写完字节后 SCL拉低 方便继续操作
    yzl_softport_sccb_sda_out(sccb);			//设置SDA为输出
    return (temp);
}
YZF_RESULT yzl_softport_sccb_write_register(YZL_Soft_SCCB *sccb,uint8_t address,uint8_t reg,uint8_t data){
    YZF_RESULT res=YZF_OK;
    yzl_softport_sccb_start(sccb);						                //启动SCCB传输

    if(yzl_softport_sccb_write_byte(sccb,address))	res=YZF_ERROR;	//写器件地址 失败返回1
    delay_us(100);

    if(yzl_softport_sccb_write_byte(sccb,reg)) res=YZF_ERROR;		//写寄存器地址 失败返回1
    delay_us(100);

    if(yzl_softport_sccb_write_byte(sccb,data)) res=YZF_ERROR;		//写数据	  失败返回1
    yzl_softport_sccb_stop(sccb);						                //停止
    return(res);
}
uint8_t yzl_softport_sccb_read_register(YZL_Soft_SCCB *sccb,uint8_t address,uint8_t reg){
    uint8_t val=0;
    yzl_softport_sccb_start(sccb);				            //启动SCCB传输

    yzl_softport_sccb_write_byte(sccb,address);		//写器件ID
    delay_us(100);

    yzl_softport_sccb_write_byte(sccb,reg);			//写寄存器地址
    delay_us(100);

    yzl_softport_sccb_stop(sccb);
    delay_us(100);

    yzl_softport_sccb_start(sccb);				//设置完寄存器后才是读
    yzl_softport_sccb_write_byte(sccb,address|0x01);	//发送读命令
    delay_us(100);

    val=yzl_softport_sccb_read_byte(sccb);		//读取命令
    yzl_softport_sccb_NA(sccb);					//发送NA信号
    yzl_softport_sccb_stop(sccb);
    return (val);
}
#endif