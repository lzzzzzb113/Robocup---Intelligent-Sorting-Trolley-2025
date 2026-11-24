//
// Created by 32827 on 2024/1/27.
//
#include "utils/yzl_ui_font_utils.h"
#include "yzl.h"
uint32_t yzl_ui_get_string_width(struct FontPixel *fontPixel,ucs2 *text,uint16_t len){
    uint16_t maxWidth=0;
    uint16_t width=0;
    uint16_t line=1;
    for (int i = 0; i < len; i++) {
        if(text[i]=='\r'||text[i]=='\n'){
            width=0;
            line++;
        }
        if(i!=len-1){
            width+=fontPixel[i].width;
        }else{
            width+=fontPixel[i].width+fontPixel->xAdvance;
        }
        if(maxWidth<width){
            maxWidth=width;
        }
    }
    return (maxWidth<<16)+(line*YZL_FONT_LINE_HEIGHT);
}
YZF_BOOL yzl_ui_font_data_init(struct FontPixel **pFontPixel,ucs2 **dst_text,uint16_t *textLen,utf8 *src_text){
    yzl_iconv_clear_ucs2_buf();
    utf2ucs(yzl_iconv_ucs2_buf, (unsigned char *)src_text);
    uint16_t len= yzl_iconv_ucs2_strlen(yzl_iconv_ucs2_buf);
    *dst_text = YZL_MEM_MANAGER.pMalloc(len*2+1);
    *textLen = len;
    memcpy(*dst_text, yzl_iconv_ucs2_buf, len*2+1);

    if(pFontPixel!=YZF_NULL_PTR){
        *pFontPixel = YZL_MEM_MANAGER.pMalloc(len*sizeof(struct FontPixel));
        if(yzl_font_get_pixels(*dst_text,*pFontPixel,len)==YZF_OK){
            return YZF_TRUE;
        }else{
            return YZF_FALSE;
        }
    }
    return YZF_TRUE;
}