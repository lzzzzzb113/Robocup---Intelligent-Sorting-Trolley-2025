//
// Created by 32827 on 2024/1/10.
//

#include "yzl_iconv.h"
#include <stdarg.h>
#if  USE_FONT
utf8 yzl_iconv_utf8_buf[YZL_ICONV_UTF8_BUF_SIZE]={0};
ucs2 yzl_iconv_ucs2_buf[YZL_ICONV_UCS2_BUF_SIZE]={0};
void yzl_iconv_clear_ucs2_buf(){
    memset(yzl_iconv_ucs2_buf,0,sizeof(yzl_iconv_ucs2_buf));
}
void yzl_iconv_clear_utf8_buf(){
    memset(yzl_iconv_utf8_buf,0,sizeof(yzl_iconv_utf8_buf));
}
uint16_t yzl_iconv_utf8_strlen(const utf8 *str){
    for(int i=0;i<512;i++){
        if(str[i]==0){
            return i;
        }
    }
    return  0;
}
uint16_t yzl_iconv_ucs2_strlen(const ucs2 *str){
    for (int i = 0; i < 256;i++) {
        if (str[i] == 0) {
            return i;
        }
    }
    return 0;
}
ucs2 *utf2ucs (ucs2 *dst, utf8 *src)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int next = 0;

    while (src[i] != 0)
    {
        ucs2 temp = 0;
        if (src[i] & 0x80 && src[i+1] & 0x80)
        {

            next = 3;
            temp |= ((src[i] & 0xF) << 12);
            temp |= ((src[i+1] & 0x3F) << 6);
            temp |= ((src[i+2] & 0x3F) << 0);

        }
        else if(src[i] & 0x80 && src[i+1] & 0xC0)
        {
            next = 2;

            temp |= (src[i] & 0x1F) << 6;
            temp |= (src[i+1] & 0x3F) << 0;

        }
        else
        {
            next = 1;
            temp = src[i];
        }
        dst[j++] = temp;
        i += next;
    }
    dst[j] = 0;
    return dst;
};

utf8 *ucs2utf (utf8 *dst, ucs2 *src)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int next = 0;

    while (src[i] != 0)
    {
        if (src[i] < 0x80)
        {
            next = 1;
            dst[j] = 0;
            dst[j] = src[i];
        }
        else if(src[i] < 0x800)
        {
            next = 2;
            dst[j] = 0;
            dst[j+1] = 0;

            dst[j+1] = (utf8)((src[i] & 0x3F) | 0x80);

            dst[j] = (utf8)(((src[i] & 0x3F) & 0x1F) | 0xC0);
        }
        else
        {
            next = 3;
            dst[j] = 0;
            dst[j+1] = 0;
            dst[j+2] = 0;

            dst[j] |= ((((utf8)(src[i] >> 12)) & 0xF) | 0xE0);


            dst[j+1] |= (((utf8)(src[i] >> 6) & 0x3F) | 0x80);


            dst[j+2] |= (((utf8)(src[i] >> 0) & 0x3F) | 0x80);

        }

        j += next;
        i++;
    }
    dst[j] = 0;
    return dst;
}
uint8_t yzl_str_format_temp[YZL_STR_FORMAT_BUF_SIZE]={0};
char * yzl_str_format(const char *fmt, ...){
    memset(yzl_str_format_temp,0,sizeof(yzl_str_format_temp));
    va_list args;
    va_start(args, fmt);
    vsprintf((char *)yzl_str_format_temp, fmt, args);
    va_end(args);
    return (char *)yzl_str_format_temp;
}
#endif