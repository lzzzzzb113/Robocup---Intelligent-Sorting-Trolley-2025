//
// Created by 32827 on 2024/1/10.
//

#ifndef YZL_ICONV_H
#define YZL_ICONV_H
#include "yzl.h"


#if USE_FONT
typedef unsigned short ucs2; //Unicode2 16bits.
typedef unsigned char utf8;  // utf-8 8bits.
//https://github.com/smoothwind/ucs2-utf8
#ifdef __cplusplus
extern "C" {
#endif

#include "iconv.h"
#include "string.h"
    
extern utf8 yzl_iconv_utf8_buf[YZL_ICONV_UTF8_BUF_SIZE];
extern ucs2 yzl_iconv_ucs2_buf[YZL_ICONV_UCS2_BUF_SIZE];

void yzl_iconv_clear_ucs2_buf();

void yzl_iconv_clear_utf8_buf();

uint16_t yzl_iconv_utf8_strlen(const utf8 *str);

uint16_t yzl_iconv_ucs2_strlen(const ucs2 *str);

ucs2 *utf2ucs(ucs2 *dst, utf8 *src);

utf8 *ucs2utf(utf8 *dst, ucs2 *src);

char * yzl_str_format(const char *fmt, ...);
#ifdef __cplusplus
}
#endif

#endif

#endif //YZL_ICONV_H
