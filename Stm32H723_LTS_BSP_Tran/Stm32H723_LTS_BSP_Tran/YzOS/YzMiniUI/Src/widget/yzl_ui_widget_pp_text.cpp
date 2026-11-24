//
// Created by 32827 on 2024/2/15.
//
#include "widget/yzl_ui_widget_pp_text.hpp"
#include "yzl.h"
#include "yzl_softport.h"
#include "utils/yzl_ui_font_utils.h"

WidgetText::WidgetText(YZL_WIDGET *Ram, int x, int y, int z, int width, int height, utf8 *text) : WidgetBase(Ram, x, y, z, width, height) {
    isViewReset = YZF_TRUE;
//    统一文字绘制裸机到setText
    yzl_ui_font_data_init(&fontPixel,&this->text,&textLen,text);
    uint32_t size= yzl_ui_get_string_width(fontPixel,this->text, textLen);  //调整控件大小
    uint16_t nWidth=*((uint16_t *)(&size)+1);
    uint16_t nHeight=*(uint16_t *)(&size);
    if(width<nWidth){
        instance->width=nWidth;
    }
    if(height<nHeight){
        instance->height=nHeight;
    }
    this->show_bar = YZF_FALSE;
}

WidgetText::WidgetText(YZL_WIDGET *Ram, UI_Rect *rect, int z, utf8 *text,YZ_COLOR textColor) : WidgetText(Ram, rect->x, rect->y, z, rect->width, rect->height,text,textColor) {

}

void WidgetText::drawP() {
    WidgetBase::drawP();

    if(instance->status==YZL_UI_CTR_EVENT_TOUCH_UP){
        uint32_t size= yzl_ui_get_string_width(fontPixel,text, textLen);
        uint16_t width=(size>>16);
        uint16_t height=(size&0xffff);
        RollBack(instance->x,instance->y,instance->width,instance->height);
        if(show_bar){
            yzl_ui_draw_rect(instance->x,instance->y,instance->width,instance->height,YZF_TRUE,WHITE);
        }
        yzl_ui_draw_string(instance->x+(instance->width-width)/2,instance->y+(instance->height-height)/2,instance->x+instance->width,
                           text,textLen,RED,text_color);
    }else if(instance->status==YZL_UI_CTR_EVENT_TOUCH_DOWN){
        uint32_t size= yzl_ui_get_string_width(fontPixel,text, textLen);
        uint16_t width=(size>>16);
        uint16_t height=(size&0xffff);
        RollBack(instance->x,instance->y,instance->width,instance->height);
        if(show_bar){
            yzl_ui_draw_rect(instance->x,instance->y,instance->width,instance->height,YZF_TRUE,WHITE);
        }
        yzl_ui_draw_string(instance->x+(instance->width-width)/2,instance->y+(instance->height-height)/2,instance->x+instance->width,
                           text,textLen,RED,text_color);
    }
    instance->isRender=YZF_FALSE;
}

void WidgetText::disposeP() {
    clearTextCache();
    WidgetBase::disposeP();
}

void WidgetText::setText(utf8 *srcText) {
    yzl_iconv_clear_ucs2_buf();
    utf2ucs(yzl_iconv_ucs2_buf, srcText);
    uint16_t len= yzl_iconv_ucs2_strlen(yzl_iconv_ucs2_buf);
    if(this->fontPixel!=YZF_NULL_PTR){
        YZL_MEM_MANAGER.pFree(this->fontPixel);
    }
    if(this->text!=YZF_NULL_PTR){
        YZL_MEM_MANAGER.pFree(this->text);
    }
    this->text=(ucs2 *)YZL_MEM_MANAGER.pMalloc(len*2+1);
    this->textLen = len;
    memcpy(text, yzl_iconv_ucs2_buf, len*2+1);

    this->fontPixel = (struct FontPixel*)YZL_MEM_MANAGER.pMalloc(len*sizeof(struct FontPixel));
    while (yzl_font_get_pixels(this->text,this->fontPixel,len)!=YZF_OK){
        yzl_softport_delayMS(200);
    }

    instance->isRender=YZF_TRUE;
}

void WidgetText::clearTextCache() {
    YZL_MEM_MANAGER.pFree(fontPixel);
    YZL_MEM_MANAGER.pFree(text);
}

void WidgetText::showBar(YZF_BOOL isShow) {
    show_bar=isShow;
    instance->isRender=YZF_TRUE;
}

void WidgetText::setTextColor(YZ_COLOR color) {
    this->text_color=color;
}

WidgetText::WidgetText(YZL_WIDGET *Ram, int x, int y, int z, int width, int height, utf8 *text, YZ_COLOR textColor):WidgetText(Ram, x,y,  z,width,  height, text) {
    this->text_color = textColor;
}

WidgetText::WidgetText(YZL_WIDGET *Ram, UI_Rect *rect, int z, utf8 *text):WidgetText(Ram, rect->x, rect->y, z, rect->width, rect->height,text) {

}
