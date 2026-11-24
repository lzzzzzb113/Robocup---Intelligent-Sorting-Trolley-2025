#ifndef YZL_ST7735s_h
#define YZL_ST7735s_h
#include "yzl_ui.h"
#include "yzl_softport_spi.h"

#if YZL_USE_HAL == OFF
#include "yz_spi.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    YZF_BOOL isHard;
    YZL_Soft_SPI spi_soft;
    YZF_SPI_POINTER spi_hard;
    YZL_GPIO rst;
    YZL_GPIO dc;
} Yz_ST7735S_Handler;

#ifdef YZL_UI_ST7735S

#if USE_UI_PORT
#include "inttypes.h"
void lcd_init(void);
void lcd_show(uint8_t* sbuf,uint32_t size);
void lcd_set_window(uint16_t xs, uint16_t ys,uint16_t xe,uint16_t ye);
//void yzl_ui_draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
#endif

//Screen UI Port
extern Yz_ST7735S_Handler YZ_SCREEN_DRIVER_PORT;
#endif

#ifdef __cplusplus
}
#endif

#endif
