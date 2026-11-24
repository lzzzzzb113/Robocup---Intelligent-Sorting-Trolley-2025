//
// Created by 32827 on 2024/5/17.
//

#include "user.h"
#include "yzl_mem.h"
#include "yzl_fatfs_include.h"
#include "yzl_font.h"
#include "yzf_global_sheet.h"
#include "yzl_ui_view_demo.h"

#include "lv_port_disp.h"
#include "lv_port_indev.h"

#include "yzl_st7735s.h"
#include "yzl_ui_thread.h"
#include "user_cxx.h"
#include "yzl_math.h"
#include "yzl_i2c_tcs34727.h"
#include "yz_uart.h"
#include "yzl_uart_tmc2209.h"
#include "yz_tim.h"
#include "yzl_i2c_bno085.h"

//D1_RAM 240K RAM
YZ_MemManger yzlMem={
        0x24000000+80*1024,240*1024,YZF_NULL_PTR, YZF_NULL_PTR
};

//文件初始化函数
YZF_RESULT file_init(void){
    uint8_t *dsdata=(uint8_t *)yzlMem.pMalloc(2048);
    FRESULT res_sd= f_mount(&yzl_fs,"/MMC/",1);
    if (res_sd == FR_NO_FILESYSTEM) {
        yz_info("》SD卡还没有文件系统，即将进行格式化...\n");
        res_sd=f_mkfs("/MMC/",0,dsdata,2048);
        if (res_sd == FR_OK) {
            yz_info("》SD卡已成功格式化文件系统。\n");
            res_sd = f_mount(&yzl_fs,"/MMC/",1);
            yzlMem.pFree(dsdata);
            return YZF_OK;
        } else {
            yz_error("《《格式化失败。》》\n");
            yzlMem.pFree(dsdata);
            return YZF_ERROR;
        }
    } else if (res_sd!=FR_OK) {
        yz_error("！！SD卡挂载文件系统失败。(%d)\n",res_sd);
        yz_error("！！可能原因：SD卡初始化不成功。\n");
        yzlMem.pFree(dsdata);
        return YZF_ERROR;
    }else{
        yz_info("文件挂载成功\n");
        yzlMem.pFree(dsdata);
        return YZF_OK;
    }
}

Yz_ST7735S_Handler YZ_SCREEN_DRIVER_PORT=
        {
        YZF_TRUE,
        {
                YZL_SOFTPORT_SPI_MODE_0,
                YZF_TRUE,
                {YZF_PIN_13, GPIOG},
                {YZF_PIN_3, GPIOB},
                {YZF_PIN_5, GPIOB},
                {YZF_PIN_UNKnow, NULL},
                },
        SPI3,
            {YZF_PIN_15,GPIOG},
            {YZF_PIN_14,GPIOG}
        };

extern void testPrint(char *text);
extern void usart1_time(char *text);
int user_main(){
    yz_info("Boot UP!\n");
    yzl_mem_init(&yzlMem);

    //------------------- SPI 屏幕初始化 ---------------------
    YLGPIO(YZ_SCREEN_DRIVER_PORT.spi_soft.clk)
    yzf_gpio_set_AFPP_();
    yzf_gpio_set_HIGH_();
    yzf_gpio_set_af_(GPIO_AF6_SPI3);

    YLGPIO(YZ_SCREEN_DRIVER_PORT.spi_soft.mosi)
    yzf_gpio_set_AFPP_();
    yzf_gpio_set_HIGH_();
    yzf_gpio_set_af_(GPIO_AF7_SPI3);

    yz_spi_full_lines_init(SPI3,YZF_SPI_PLCK_4,0,7,0,0,1,1);
    //------------------- SPI 屏幕初始化 ---------------------

    //----------------- 文件系统 --------------------
    if(yz_hal_get_sdmmc1()->State==HAL_SD_STATE_READY){
        yz_info("SD Card is Ready.\r\n");
    }

    if(file_init()==YZF_OK){
        yz_info("File Init OK.\r\n");
    }else{
        yz_error("File Init Error.\r\n");
    }

    if(yzl_font_init(YZL_DEFAULT_DIR)==YZF_OK){
        yz_info("Font Init OK.\r\n");
    }else{
        yz_error("Font Init Error.\r\n");
    }

    //----------------- 文件系统 --------------------
//    yz_uart_receive_IT_init(USART1);
    YZ_RECV_TIME *area_time= (YZ_RECV_TIME *) yz_uart_receive_IT_RECV_get(USART1);
    yz_area_recv_time_init(area_time,50,yz_area_recv_time_listener_default,usart1_time);
    yz_uart_receive_IT_init(USART1);
    USART1->CR3 |= USART_CR3_OVRDIS;
    area_time = (YZ_RECV_TIME *) yz_uart_receive_IT_RECV_get(UART7);
    yz_area_recv_time_init(area_time,50,yz_area_recv_time_listener_default,testPrint);
    yz_uart_receive_IT_init(UART7);
    UART7->CR3 |= USART_CR3_OVRDIS;
    area_time = (YZ_RECV_TIME *) yz_uart_receive_IT_RECV_get(UART5);
    yz_area_recv_time_init(area_time,50,yz_area_recv_time_listener_default,testPrint);
    yz_uart_receive_IT_init(UART5);
    UART5->CR3 |= USART_CR3_OVRDIS;
    yz_area_recv_time_lock((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART7));
    yz_area_recv_time_lock((YZ_RECV_TIME *)yz_uart_receive_IT_RECV_get(UART5));


    //-------------- TCS34727 测试 -----------------
//    yzl_i2c_tcs34727_init(I2C4);o
//    yz_i2c_add7_receive(I2C4,0x49,(uint8_t *) &dev_id, 3);

//    uint8_t dev_id=0xC0;
//    yz_i2c_add7_transmit(I2C4,0x49,&dev_id, 1);
//    HAL_Delay(200);
//    yz_i2c_add7_mem_receive(I2C4,0x49,0xAA,(uint8_t *) &dev_id, 1);
//    while(dev_id!=0x66){
//        HAL_Delay(200);
//        yz_i2c_add7_mem_receive(I2C4,0x49,0xAA,(uint8_t *) &dev_id, 1);
//    }
    //-------------- TCS34727 测试 -----------------

    yz_info("初始化Fast Atan2...\r\n");
    yzl_atan2_tab_init();


    yzl_i2c_bno085_soft_reset(I2C1);

//    yzl_i2c_bno085_enable_linear_accelerometer(I2C1,50);

    yzl_i2c_bno085_enable_accelerometer(I2C1,250);
    yzl_i2c_bno085_enable_gyro(I2C1,250);
    yzl_i2c_bno085_enable_magnetometer(I2C1,250);
//    yzl_i2c_bno085_enable_rotation_vector(I2C1,250);
    yzl_i2c_bno085_enable_game_rotation_vector(I2C1,250);


    YZ_COLOR background={0b1111100000000000};
    yzl_ui_init(background);
    yzf_global_handler_add(yzl_ui_boot);
    yzf_global_handler_add(yzl_ui_main_view_boot);
    return 0;
}
YZF_BOOL OutError=YZF_FALSE;
//跳出错误函数
void user_OutError(){
    OutError=YZF_TRUE;
}

void user_error_handler(YZF_RESULT error){
    switch (error) {
        case YZF_NOT_FOUND:
            yz_error("[GlobalSheet: %hd] 参数未找到.\n",yz_status_sheet_get(YZ_FLAG_ERROR_HANDLER_INDEX));
            break;
        case YZF_ERROR:
            yz_error("[GlobalSheet: %hd] 未知错误.\n",yz_status_sheet_get(YZ_FLAG_ERROR_HANDLER_INDEX));
            break;
        case YZF_NOT_INIT:
            yz_error("[GlobalSheet: %hd] 使用的函数，所需对象未被初始化.\n",yz_status_sheet_get(YZ_FLAG_ERROR_HANDLER_INDEX));
            break;
        case YZF_CRC_ERROR:
            yz_error("[GlobalSheet: %hd] CRC校验错误.\n",yz_status_sheet_get(YZ_FLAG_ERROR_HANDLER_INDEX));
            break;
        case YZF_CLOCK_NOT_READY:
            yz_error("[GlobalSheet: %hd] 时钟未就绪.\n",yz_status_sheet_get(YZ_FLAG_ERROR_HANDLER_INDEX));
            break;
        case YZF_NOTHING:
#ifdef osCMSIS
            osDelay(1);
#endif
#ifdef GD32F470
            vTaskDelay(1);
#endif
            user_OutError();
            break;
        default:
            yz_error("[GlobalSheet: %hd] 未被识别的错误类型. Code: %d\n",yz_status_sheet_get(YZ_FLAG_ERROR_HANDLER_INDEX),error);
    }
    while (!OutError){
        __asm__("nop");
    }
    OutError=YZF_FALSE;
}
char transmit_buf[YZ_APPLICATION_TRANSMIT_BUF_SIZE];
void yz_error(const char *fmt, ...){
    char *str_error="[ERROR]";
    int i;

    va_list arg;
    va_start(arg, fmt);
    memset(transmit_buf,0,sizeof(transmit_buf));
    i = vsprintf(transmit_buf, fmt, arg);
    va_end(arg);

    yz_shell_send(USART1,(uint8_t *)str_error, strlen(str_error));
    yz_shell_send(USART1,(uint8_t *)transmit_buf,i);
}
void yz_info(const char *fmt, ...){
    char *str_error="[INFO]";
    int i;

    va_list arg;
    va_start(arg, fmt);
    memset(transmit_buf,0,sizeof(transmit_buf));
    i = vsprintf(transmit_buf, fmt, arg);
    va_end(arg);

    yz_shell_send(USART1,(uint8_t *)str_error, strlen(str_error));
    yz_shell_send(USART1,(uint8_t *)transmit_buf,i);
}
void yz_debug(const char *fmt, ...){
    char *str_error="[DEBUG]";
    int i;

    va_list arg;
    va_start(arg, fmt);
    memset(transmit_buf,0,sizeof(transmit_buf));
    i = vsprintf(transmit_buf, fmt, arg);
    va_end(arg);

    yz_shell_send(USART1,(uint8_t *)str_error, strlen(str_error));
    yz_shell_send(USART1,(uint8_t *)transmit_buf,i);
}
void yz_ok(const char *fmt, ...){
    char *str_error="[SUCCESS]";
    int i;

    va_list arg;
    va_start(arg, fmt);
    memset(transmit_buf,0,sizeof(transmit_buf));
    i = vsprintf(transmit_buf, fmt, arg);
    va_end(arg);

    yz_shell_send(USART1,(uint8_t *)str_error, strlen(str_error));
    yz_shell_send(USART1,(uint8_t *)transmit_buf,i);
}
void yz_printf(const char *fmt, ...){
    int i;

    va_list arg;
    va_start(arg, fmt);
    memset(transmit_buf,0,sizeof(transmit_buf));
    i = vsprintf(transmit_buf, fmt, arg);
    va_end(arg);

    yz_shell_send(USART1,(uint8_t *)transmit_buf,i);
}
void yz_shell_send(void *file,uint8_t *str,  size_t len){
//    yz_uart_transmit(USART1, (uint8_t*)str, len);
}