//
// Created by 32827 on 2024/1/9.
//

#ifndef YZL_FONT_H
#define YZL_FONT_H

#include "yzl.h"
#include "yz_log.h"
#include <stdio.h>

#if USE_FONT

#ifdef YZFATFS
#include "yzl_fatfs_include.h"
#define YZL_FONT_FILE_SYSTEM FATFS
#define YZL_FONT 16
#endif

#if YZL_FONT==32
#define YZL_FONT_SIZE 32
#define YZL_FONT_LINE_HEIGHT 37
#define YZL_DEFAULT_DIR "FontBin32"
#endif

#if YZL_FONT==16
#define YZL_FONT_SIZE 16
#define YZL_FONT_LINE_HEIGHT 19
#define YZL_DEFAULT_DIR "FontBin16"
#endif

#define YZL_FONT_FF_DRIVER "/MMC/"
#define YZL_FONT_DATA_TYPE uint8_t
#define YZL_FONT_COUNT 8239
#define YZL_FONT_INDEX_PAGE_SIZE 512

#ifdef __cplusplus
extern "C" {
#endif
struct FontSoftIndex {
    uint16_t page_start_char_id;
};
struct FontIndexConvert {
    uint16_t char_id;
    uint16_t fnt_id;
};
struct FontPixel {
    uint8_t width;
    uint8_t height;
    int8_t xOffset;
    int8_t yOffset;
    int8_t xAdvance;
    uint8_t pixel[YZL_FONT_SIZE * YZL_FONT_SIZE / (sizeof(YZL_FONT_DATA_TYPE) * 8)];
};
extern YZF_BOOL Yz_FontInitFlag;
extern struct FontPixel yzl_font_sram[YZL_FONT_SRAM_SIZE];
//计算SOFT_INDEX数量 永远+1 +1用于设置结尾为0xFF
#define YZL_FONT_SOFT_INDEX_NUMBER (YZL_FONT_COUNT/(YZL_FONT_INDEX_PAGE_SIZE/sizeof(struct FontIndexConvert))+(YZL_FONT_COUNT%(YZL_FONT_INDEX_PAGE_SIZE/sizeof(struct FontIndexConvert))==0?0:1)+1)
#define YZL_FONT_INDEX_NUMBER (YZL_FONT_INDEX_PAGE_SIZE / sizeof(struct FontIndexConvert))


YZF_RESULT yzl_font_init(const char *fontDir);

YZF_RESULT yzl_font_get_pixel(uint16_t char_id, struct FontPixel *pixel);

YZF_RESULT yzl_font_get_fnt_id(uint16_t char_id, uint16_t *fnt_id);

YZF_RESULT yzl_font_get_fnt_ids(uint16_t *char_id, uint16_t *fnt_id, uint16_t size);

YZF_RESULT yzl_font_get_pixels(uint16_t *char_id, struct FontPixel *pixel, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif
#endif //YZL_FONT_H
