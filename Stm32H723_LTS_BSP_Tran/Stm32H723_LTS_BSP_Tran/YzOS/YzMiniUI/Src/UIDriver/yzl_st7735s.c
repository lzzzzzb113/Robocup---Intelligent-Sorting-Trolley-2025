#include "yzl_st7735s.h"
#include "yzx_base.h"

struct ST7735_cmdBuf {
    uint8_t command;   // ST7735 command byte
    uint8_t delay;     // ms delay after
    uint8_t len;       // length of parameter data
    uint8_t data[16];  // parameter data
};
static const struct ST7735_cmdBuf initializers[] = {
        // SWRESET Software reset
        { 0x01, 150, 0, {0}},
        // SLPOUT Leave sleep mode
        { 0x11,  150, 0, {0}},
        // FRMCTR1, FRMCTR2 Frame Rate configuration -- Normal mode, idle
        // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
        { 0xB1, 0, 3, { 0x01, 0x2C, 0x2D }},
        { 0xB2, 0, 3, { 0x01, 0x2C, 0x2D }},
        // FRMCTR3 Frame Rate configureation -- partial mode
        { 0xB3, 0, 6, { 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D }},
        // INVCTR Display inversion (no inversion)
        { 0xB4,  0, 1, { 0x07 }},
        // PWCTR1 Power control -4.6V, Auto mode
        { 0xC0,  0, 3, { 0xA2, 0x02, 0x84}},
        // PWCTR2 Power control VGH25 2.4C, VGSEL -10, VGH = 3 * AVDD
        { 0xC1,  0, 1, { 0xC5}},
        // PWCTR3 Power control, opamp current smal, boost frequency
        { 0xC2,  0, 2, { 0x0A, 0x00 }},
        // PWCTR4 Power control, BLK/2, opamp current small and medium low
        { 0xC3,  0, 2, { 0x8A, 0x2A}},
        // PWRCTR5, VMCTR1 Power control
        { 0xC4,  0, 2, { 0x8A, 0xEE}},
        { 0xC5,  0, 1, { 0x0E }},
        // INVOFF Don't invert display
        { 0x20,  0, 0, {0}},
        // Memory access directions. row address/col address, bottom to top refesh (10.1.27)
        { 0x36,  0, 1, {0xC8}},//0xC8 BGR 0xC0 RGB
        // Color mode 16 bit (10.1.30
        { 0x3a,   0, 1, {0x05}},
        // Column address set 0..127
        { 0x2a,   0, 4, {0x00, 0x02, 0x00, 0x7F+0x02 }},
        // Row address set 0..159
        { 0x2b,   0, 4, {0x00, 0x02, 0x00, 0x7F+0x02 }},
        // GMCTRP1 Gamma correction
        { 0xE0, 0, 16, {0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D,
                                0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10 }},
        // GMCTRP2 Gamma Polarity corrction
        { 0xE1, 0, 16, {0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,
                                0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10 }},
        // DISPON Display on
        { 0x29, 100, 0, {0}},
        // NORON Normal on
        { 0x13,  10, 0, {0}},
        // End
        { 0, 0, 0, {0}}
};

#ifdef YZL_UI_ST7735S

#if USE_LVGL
extern SPI_HandleTypeDef hspi3;
#define W YZ_SCREEN_WIDTH
#define H YZ_SCREEN_HEIGHT

#define SPI1_CS_GPIO_Port GPIOG
#define SPI1_CS_Pin GPIO_PIN_13
#define TFT_RESET_GPIO_Port  GPIOG
#define TFT_RESET_Pin  GPIO_PIN_15
#define TFT_A0_GPIO_Port GPIOG
#define TFT_A0_Pin  GPIO_PIN_14



void lcd_write(uint8_t dc, uint8_t *data, int n)
{
#if YZL_USE_HAL
	HAL_GPIO_WritePin(TFT_A0_GPIO_Port,TFT_A0_Pin,(GPIO_PinState)dc);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi3,data,n,50000);
    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
#else
    if(dc){
        YLHIGH( YZ_SCREEN_DRIVER_PORT.dc);
    }else{
        YLLOW( YZ_SCREEN_DRIVER_PORT.dc);
    }
    YLLOW( YZ_SCREEN_DRIVER_PORT.spi_soft.cs);
    yz_spi_full_lines_begin(YZ_SCREEN_DRIVER_PORT.spi_hard);
    yz_spi_bidi_transmit(YZ_SCREEN_DRIVER_PORT.spi_hard,data,n);
    yz_spi_full_lines_end(YZ_SCREEN_DRIVER_PORT.spi_hard);
    YLHIGH( YZ_SCREEN_DRIVER_PORT.spi_soft.cs);
#endif
}
void lcd_set_window(uint16_t xs, uint16_t ys,uint16_t xe,uint16_t ye)
{
    xs+=2;
    xe+=2;
    ys+=3;
    ye+=3;
	uint8_t xram[]={0x2a,xs>>8,xs&0xff,xe>>8,xe&0xff};
	uint8_t yram[]={0x2b,ys>>8,ys&0xff,ye>>8,ye&0xff};
	lcd_write(0,&xram[0],1);
	lcd_write(1,(uint8_t*)&xram[1],4);
	lcd_write(0,&yram[0],1);
	lcd_write(1,(uint8_t*)&yram[1],4); //set window
}
void lcd_show(uint8_t* sbuf,uint32_t size)
{
	uint8_t gram=0x2c;
	lcd_write(0,&gram,1);
	lcd_write(1,sbuf,size);
}

void lcd_init()
{
    const struct ST7735_cmdBuf *cmd;
#if YZL_USE_HAL
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(TFT_RESET_GPIO_Port,TFT_RESET_Pin,GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(TFT_RESET_GPIO_Port,TFT_RESET_Pin,GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(TFT_RESET_GPIO_Port,TFT_RESET_Pin,GPIO_PIN_SET);
	for (cmd = initializers; cmd->command; cmd++)
	{
		lcd_write(0, (uint8_t*)&(cmd->command), 1);
		if (cmd->len)
		{
			lcd_write(1, (uint8_t*)cmd->data, cmd->len);
		}
		if (cmd->delay)
		{
			HAL_Delay(cmd->delay);
		}
	}
#else
    yzf_spi_disable_all_interrupt(YZ_SCREEN_DRIVER_PORT.spi_hard);
    yzf_spi_tran_count(YZ_SCREEN_DRIVER_PORT.spi_hard,0);

    YLHIGH(YZ_SCREEN_DRIVER_PORT.spi_soft.cs);
    YLHIGH(YZ_SCREEN_DRIVER_PORT.rst);
    delay_ms(10);
    YLLOW(YZ_SCREEN_DRIVER_PORT.rst);
    delay_ms(10);
    YLHIGH(YZ_SCREEN_DRIVER_PORT.rst);
    for (cmd = initializers; cmd->command; cmd++){
        lcd_write(0, (uint8_t*)&(cmd->command), 1);
        if (cmd->len){
            lcd_write(1, (uint8_t*)cmd->data, cmd->len);
        }
        if (cmd->delay) {
            delay_ms(cmd->delay);
        }
    }
#endif
}
#endif
///-------------------------------------------------------------------------
YZ_COLOR scn_ram[YZ_SCREEN_WIDTH*YZ_SCREEN_HEIGHT];
YZ_COLOR scn_background;
YZF_RESULT yzl_ui_init(YZ_COLOR background){
    lcd_init();
    scn_background=background;
    yzl_ui_clear_screen();
    return YZF_OK;
}
YZF_RESULT yzl_ui_clear_screen(void){
    yzl_ui_fill_screen(scn_background);
    yzl_ui_refresh();
    return YZF_OK;
}
YZF_RESULT yzl_ui_fill_screen(YZ_COLOR color){
    for(int i=0;i<YZ_SCREEN_WIDTH*YZ_SCREEN_HEIGHT;i++){
        scn_ram[i]=color;
    }
    return YZF_OK;
}
YZF_RESULT yzl_ui_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, YZF_BOOL isFill, YZ_COLOR color){
    if(x<0|| y <0 || x+width>YZ_SCREEN_WIDTH || y+height>YZ_SCREEN_HEIGHT ){
        return YZF_ERROR;
    }

    if ( isFill )
    {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                scn_ram[(x + i) + (y + j) * YZ_SCREEN_WIDTH]= color;
            }
        }
    }
    else
    {
        yzl_ui_draw_line(x, y, x+width - 1, y, color);
        yzl_ui_draw_line(x, y + height - 1, x + width - 1, y + height - 1,
                         color);
        yzl_ui_draw_line(x, y, x, y + height - 1, color);
        yzl_ui_draw_line(x + width - 1, y, x + width - 1, y + height - 1,
                         color);
    }
    return YZF_OK;
}
YZF_RESULT yzl_ui_draw_circle(uint16_t x, uint16_t y, uint16_t radius, YZF_BOOL isFill, YZ_COLOR color){
    int16_t sCurrentX, sCurrentY;
    int16_t sError;


    sCurrentX = 0; sCurrentY = radius;

    sError = 3 - ( radius << 1 );     //判断下个点位置的标志


    while ( sCurrentX <= sCurrentY )
    {
        int16_t sCountY;


        if ( isFill )
            for ( sCountY = sCurrentX; sCountY <= sCurrentY; sCountY ++ )
            {
                yzl_ui_draw_pixel(x + sCurrentX, y + sCountY, color);           //1，研究对象
                yzl_ui_draw_pixel(x - sCurrentX, y + sCountY, color);           //2
                yzl_ui_draw_pixel(x - sCountY, y + sCurrentX, color);           //3
                yzl_ui_draw_pixel(x - sCountY, y - sCurrentX, color);           //4
                yzl_ui_draw_pixel(x - sCurrentX, y - sCountY, color);           //5
                yzl_ui_draw_pixel(x + sCurrentX, y - sCountY, color);           //6
                yzl_ui_draw_pixel(x + sCountY, y - sCurrentX, color);           //7
                yzl_ui_draw_pixel(x + sCountY, y + sCurrentX, color);           //0
            }

        else
        {
            yzl_ui_draw_pixel(x + sCurrentX, y + sCurrentY, color);             //1，研究对象
            yzl_ui_draw_pixel(x - sCurrentX, y + sCurrentY, color);             //2
            yzl_ui_draw_pixel(x - sCurrentY, y + sCurrentX, color);             //3
            yzl_ui_draw_pixel(x - sCurrentY, y - sCurrentX, color);             //4
            yzl_ui_draw_pixel(x - sCurrentX, y - sCurrentY, color);             //5
            yzl_ui_draw_pixel(x + sCurrentX, y - sCurrentY, color);             //6
            yzl_ui_draw_pixel(x + sCurrentY, y - sCurrentX, color);             //7
            yzl_ui_draw_pixel(x + sCurrentY, y + sCurrentX, color);             //0
        }


        sCurrentX ++;


        if ( sError < 0 )
            sError += 4 * sCurrentX + 6;

        else
        {
            sError += 10 + 4 * ( sCurrentX - sCurrentY );
            sCurrentY --;
        }
    }
    return YZF_OK;
}
YZF_RESULT yzl_ui_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, YZ_COLOR color){
    if(x1<0 || x2 <0 || y1<0 ||y2<0){
        return YZF_ERROR;
    }
    if(x1>YZ_SCREEN_WIDTH-1|| x2 >YZ_SCREEN_WIDTH-1 || y1>YZ_SCREEN_HEIGHT-1 ||y2>YZ_SCREEN_HEIGHT-1){
        return YZF_ERROR;
    }
    uint32_t us;
    uint16_t usX_Current, usY_Current;

    int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance;
    int32_t lIncrease_X, lIncrease_Y;


    lDelta_X = x2 - x1; //计算坐标增量
    lDelta_Y = y2 - y1;

    usX_Current = x1;
    usY_Current = y1;


    if ( lDelta_X > 0 )
        lIncrease_X = 1; //设置单步方向

    else if ( lDelta_X == 0 )
        lIncrease_X = 0;//垂直线

    else
    {
        lIncrease_X = -1;
        lDelta_X = - lDelta_X;
    }


    if ( lDelta_Y > 0 )
        lIncrease_Y = 1;

    else if ( lDelta_Y == 0 )
        lIncrease_Y = 0;//水平线

    else
    {
        lIncrease_Y = -1;
        lDelta_Y = - lDelta_Y;
    }


    if (  lDelta_X > lDelta_Y )
        lDistance = lDelta_X; //选取基本增量坐标轴

    else
        lDistance = lDelta_Y;


    for ( us = 0; us <= lDistance + 1; us ++ )//画线输出
    {
        scn_ram[usX_Current+usY_Current*YZ_SCREEN_WIDTH]=color;

        lError_X += lDelta_X ;
        lError_Y += lDelta_Y ;

        if ( lError_X > lDistance )
        {
            lError_X -= lDistance;
            usX_Current += lIncrease_X;
        }

        if ( lError_Y > lDistance )
        {
            lError_Y -= lDistance;
            usY_Current += lIncrease_Y;
        }

    }
    return YZF_OK;
}
YZF_RESULT yzl_ui_draw_pixel(uint16_t x1, uint16_t y1, YZ_COLOR color){
    scn_ram[x1+y1*YZ_SCREEN_WIDTH]=color;
    return YZF_OK;
}
/////@param alphaColor 被屏蔽的颜色
YZF_RESULT yzl_ui_draw_pixels_ex(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, YZ_COLOR *img, YZ_COLOR alphaColor){
    for(uint16_t i=0;i<width;i++) {
        for (uint16_t j = 0; j < height; j++) {
            if (img[i + j * width].data != alphaColor.data) {
                scn_ram[x1 + i + (y1 + j) * YZ_SCREEN_WIDTH] = img[i + j * width];
            }
        }
    }
    return YZF_OK;
}
YZF_RESULT yzl_ui_draw_pixels(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, YZ_COLOR *img){
    for(int i=0;i<width;i++) {
        for (int j = 0; j < height; j++) {
            scn_ram[x1 + i + (y1 + j) * YZ_SCREEN_WIDTH] = img[i + j * width];
        }
    }
    return YZF_OK;
}

//YZF_RESULT yzl_ui_draw_string(uint16_t x, uint16_t y, uint16_t limitX, uint16_t *str, uint16_t len, YZ_COLOR back_color,
//                              YZ_COLOR text_color);
//

YZF_RESULT yzl_ui_get_pixel(uint16_t x, uint16_t y, YZ_COLOR *color){
    *color = scn_ram[x+y*YZ_SCREEN_WIDTH];
    return YZF_OK;
}

YZF_RESULT yzl_ui_get_pixels_line(uint16_t x, uint16_t y, uint16_t width, YZ_COLOR *color){
    memcpy(color,scn_ram+x+y*YZ_SCREEN_WIDTH,width*sizeof(YZ_COLOR));
    return YZF_OK;
}

YZF_RESULT yzl_ui_refresh(){
    lcd_set_window(0,0,YZ_SCREEN_WIDTH-1,YZ_SCREEN_HEIGHT-1);
    uint8_t gram=0x2c;
    lcd_write(0,&gram,1);
    #if YZL_USE_HAL

    #else
        YLHIGH( YZ_SCREEN_DRIVER_PORT.dc);
        YLLOW( YZ_SCREEN_DRIVER_PORT.spi_soft.cs);
        yz_spi_full_lines_begin(YZ_SCREEN_DRIVER_PORT.spi_hard);
        uint8_t* pData=(uint8_t *)scn_ram;
        uint32_t tCount=YZ_SCREEN_WIDTH*YZ_SCREEN_HEIGHT*sizeof (YZ_COLOR);
        while(tCount){
            while (yzf_spi_flag_txp(YZ_SCREEN_DRIVER_PORT.spi_hard)==YZF_FALSE);
            yzf_spi_write_byte(YZ_SCREEN_DRIVER_PORT.spi_hard,*(pData+1));
            while (yzf_spi_flag_txp(YZ_SCREEN_DRIVER_PORT.spi_hard)==YZF_FALSE);
            yzf_spi_write_byte(YZ_SCREEN_DRIVER_PORT.spi_hard,*(pData));
            tCount-=2;
            pData+=2;
        }
        yz_spi_full_lines_end(YZ_SCREEN_DRIVER_PORT.spi_hard);
        YLHIGH( YZ_SCREEN_DRIVER_PORT.spi_soft.cs);
    #endif
    return YZF_OK;
}

#endif