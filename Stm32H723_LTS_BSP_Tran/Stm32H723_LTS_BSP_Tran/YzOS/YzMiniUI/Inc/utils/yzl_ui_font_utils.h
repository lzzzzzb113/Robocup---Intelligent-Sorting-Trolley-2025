//
// Created by 32827 on 2024/1/27.
//

#ifndef YZGD32_YZL_UI_FONT_UTILS_H
#define YZGD32_YZL_UI_FONT_UTILS_H
#include "yzl_ui.h"
typedef struct {
    uint16_t textLen;
    ucs2 *text;
    struct FontPixel *fontPixel;
} YZL_UI_FONT_DATA;
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @return [32:16] width [15:0] height
 * */
uint32_t yzl_ui_get_string_width(struct FontPixel *fontPixel, ucs2 *text, uint16_t len);

/**
 * 用于初始化字体
 * @param pFontPixel 要初始化的字体数据指针
 * @param dst_text 要初始化的目标文本指针
 * @param textLen 要初始化的文本长度指针
 * @param src_text 源文本
 * @return 初始化成功返回YZF_TRUE,否则返回YZF_FALSE
 * @notes 记得销毁指向 pFontPixel,dst_text 的指针的数据
 * */
YZF_BOOL yzl_ui_font_data_init(struct FontPixel **pFontPixel, ucs2 **dst_text, uint16_t *textLen, utf8 *src_text);

#ifdef __cplusplus
}
#endif
#endif //YZGD32_YZL_UI_FONT_UTILS_H
