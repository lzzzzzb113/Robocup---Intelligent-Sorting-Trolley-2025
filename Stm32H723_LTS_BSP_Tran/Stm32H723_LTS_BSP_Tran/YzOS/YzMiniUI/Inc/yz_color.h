//
// Created by 32827 on 2024/1/11.
//

#ifndef YZ_COLOR_H
#define YZ_COLOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "yz.h"

#if YZ_COLOR_MODE == YZ_COLOR_MODE_RGB565

typedef struct Yz_Color {
    uint16_t data;
} YZ_COLOR;

#define YZ_COLOR_Read_R(color)   ((((color.data >> 11) & 0x1F))*8)
#define YZ_COLOR_Read_G(color)   (((color.data >> 5) & 0x3F)*4)
#define YZ_COLOR_Read_B(color)   ((color.data & 0x1F)*8)
#define YZ_COLOR_Read_A(color)   0xFF
#define YZ_COLOR_Set_R(color, r)   (color.data = (color.data & ~0xF800) | ((((r)/8) & 0x1F) << 11))
#define YZ_COLOR_Set_G(color, g)   (color.data = (color.data & ~0x07E0) | ((((g)/4) & 0x3F) << 5))
#define YZ_COLOR_Set_B(color, b)   (color.data = (color.data & ~0x001F) | ((((b)/8) & 0x1F) << 0))
#define YZ_COLOR_Set_A(color, a)   ;
#define YZ_COLOR_CREATE(r, g, b, a)  (YZ_COLOR){((((((r)/8) & 0x1F) << 11)|((((g)/4) & 0b111111) << 5)|((((b)/8) & 0x1F))))}
#define YZ_COLOR_CONV(r,g,b,a) ((((((r)/8) & 0x1F) << 11)|((((g)/4) & 0b111111) << 5)|((((b)/8) & 0x1F))))

#elif YZ_COLOR_MODE == YZ_COLOR_MODE_RGB888

typedef struct Yz_Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} YZ_COLOR;
#define YZ_COLOR_Read_R(color)   color.r
#define YZ_COLOR_Read_G(color)   color.g
#define YZ_COLOR_Read_B(color)   color.b
#define YZ_COLOR_Read_A(color)   0xFF
#define YZ_COLOR_Set_R(color,r)   color.r = r
#define YZ_COLOR_Set_G(color,g)   color.g = g
#define YZ_COLOR_Set_B(color,b)   color.b = b
#define YZ_COLOR_Set_A(color,a)   ;
#define YZ_COLOR_CREATE(r,g,b,a)   (YZ_COLOR){r,g,b}
#define YZ_COLOR_CONV(r,g,b,a) (r<<16|g<<8|b)

#elif YZ_COLOR_MODE == YZ_COLOR_MODE_RGBA8888

typedef struct Yz_Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} YZ_COLOR;
#define  YZ_COLOR_Read_R(color)   color.r
#define  YZ_COLOR_Read_G(color)   color.g
#define  YZ_COLOR_Read_B(color)   color.b
#define  YZ_COLOR_Read_A(color)   color.a
#define  YZ_COLOR_Set_R(color,r)   color.r = r
#define  YZ_COLOR_Set_G(color,g)   color.g = g
#define  YZ_COLOR_Set_B(color,b)   color.b = b
#define  YZ_COLOR_Set_A(color,a)   color.a = a
#define YZ_COLOR_CREATE(r,g,b,a)   (YZ_COLOR){r,g,b,a}
#define YZ_COLOR_CONV(r,g,b,a) (r<<24|g<<16|b<<8|a)

#elif  YZ_COLOR_MODE == YZ_COLOR_MODE_BlackAndWhite

typedef struct Yz_Color{
    uint8_t v;
} YZ_COLOR;

#define  YZ_COLOR_Read_R(color)   color.v
#define  YZ_COLOR_Read_G(color)   color.v
#define  YZ_COLOR_Read_B(color)   color.v
#define  YZ_COLOR_Read_A(color)   color.v
#define  YZ_COLOR_Set_R(color,r)   color.v = (r>0x7F?0xFF:0)
#define  YZ_COLOR_Set_G(color,g)   color.v = (g>0x7F?0xFF:0)
#define  YZ_COLOR_Set_B(color,b)   color.v = (b>0x7F?0xFF:0)
#define  YZ_COLOR_Set_A(color,a)   color.v = (a>0x7F?0xFF:0)
#define YZ_COLOR_CREATE(r,g,b,a)   (YZ_COLOR){a}
#define YZ_COLOR_CONV(r,g,b,a) (a)
#endif

#define YZ_COLOR_Value(v)   YZ_COLOR_CREATE((v&0xFF0000)>>16,(v&0xFF00)>>8,(v&0xFF)>>0,(v&0xFF000000)>>24)

extern YZ_COLOR WHITE;  //白色
extern YZ_COLOR BLACK; //黑色
extern YZ_COLOR RED;   //红色
extern YZ_COLOR GREEN; //绿色
extern YZ_COLOR CYAN;  //蓝绿色，青色
extern YZ_COLOR YELLOW; //黄色
extern YZ_COLOR ALPHA; //透明

///----------------- image def ---------------------
typedef struct {
    uint32_t width;
    uint32_t height;
    uint16_t alphaColor;
}YZ_IMAGE_565A_Header;

typedef struct {
    uint32_t width;
    uint32_t height;
}YZ_IMAGE_BlackAndWhite_Header;

#ifdef __cplusplus
}
#endif

#endif //STM32OSCOVER_YZ_COLOR_H
