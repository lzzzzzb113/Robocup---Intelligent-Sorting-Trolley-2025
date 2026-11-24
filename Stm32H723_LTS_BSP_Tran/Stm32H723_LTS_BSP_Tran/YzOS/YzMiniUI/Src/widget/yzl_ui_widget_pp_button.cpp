//
// Created by 32827 on 2024/2/1.
//
#include "widget/yzl_ui_widget_pp_text_button.hpp"
#include "yzl.h"
#include "utils/yzl_ui_font_utils.h"
#include "yzl_softport.h"

WidgetTextButton::~WidgetTextButton()= default;

WidgetTextButton::WidgetTextButton(YZL_WIDGET *Ram, int x, int y, int z, int width, int height, utf8 *text) : WidgetBase(Ram, x, y, z, width, height) {
    text_color = RED;
    up_color = ALPHA;
    down_color = WHITE;
    listener = default_listener;

    yzl_ui_font_data_init(&fontPixel,&this->text,&textLen,text);

    uint32_t size= yzl_ui_get_string_width(fontPixel,this->text, textLen);  //调整控件大小
    uint16_t nWidth=*((uint16_t *)(&size)+1);
    uint16_t nHeight=*(uint16_t *)(&size);
    if(width-2<nWidth){
        width=nWidth+2;
    }
    if(height-2<nHeight){
        height=nHeight+2;
    }
    instance->width=width;
    instance->height=height;
}
WidgetTextButton::WidgetTextButton(YZL_WIDGET *Ram, UI_Rect *rect, int z, utf8 *text) : WidgetTextButton(Ram, rect->x, rect->y, z, rect->width, rect->height, text){

}
void WidgetTextButton::default_listener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
        yz_info("C++ default_listener\n");
    }
}

void WidgetTextButton::drawP() {
    WidgetBase::drawP();
    if(instance->status==YZL_UI_CTR_EVENT_TOUCH_UP){
        uint32_t size= yzl_ui_get_string_width(fontPixel,text, textLen);
        uint16_t width=(size>>16);
        uint16_t height=(size&0xffff);
        if(up_color.data!=ALPHA.data){
            yzl_ui_draw_rect(instance->x,instance->y,instance->width,instance->height,YZF_TRUE,up_color);
        }else{
            RollBack(instance->x,instance->y,instance->width,instance->height);
        }
        yzl_ui_draw_string(instance->x+(instance->width-width)/2,instance->y+(instance->height-height)/2,instance->x+instance->width,
                           text,textLen,ALPHA,text_color);
    }else if(instance->status==YZL_UI_CTR_EVENT_TOUCH_DOWN){
        uint32_t size= yzl_ui_get_string_width(fontPixel,text, textLen);
        uint16_t width=(size>>16);
        uint16_t height=(size&0xffff);
        if(down_color.data!=ALPHA.data){
            yzl_ui_draw_rect(instance->x,instance->y,instance->width,instance->height,YZF_TRUE,down_color);
        }else{
            RollBack(instance->x,instance->y,instance->width,instance->height);
        }
        yzl_ui_draw_string(instance->x+(instance->width-width)/2,instance->y+(instance->height-height)/2,instance->x+instance->width,
                           text,textLen,ALPHA,text_color);
    }
    instance->isRender=YZF_FALSE;
}

YZF_BOOL WidgetTextButton::touchP(uint16_t x, uint16_t y, YZL_UI_CTR_EVENT event) {
    WidgetBase::touchP(x, y, event);
    if(instance->status==YZL_UI_CTR_EVENT_TOUCH_UP&& event == YZL_UI_CTR_EVENT_TOUCH_DOWN){
        instance->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
        instance->isRender=YZF_TRUE;
        listener(instance,YZL_UI_CTR_EVENT_TOUCH_DOWN);
        return YZF_TRUE;
    }else if(instance->status==YZL_UI_CTR_EVENT_TOUCH_DOWN&& event == YZL_UI_CTR_EVENT_TOUCH_UP){
        instance->status=YZL_UI_CTR_EVENT_TOUCH_UP;
        instance->isRender=YZF_TRUE;
        if(yzl_ui_point_check(instance,x,y)){
            listener(instance,YZL_UI_CTR_EVENT_TOUCH_UP);
            return YZF_TRUE;
        }else{
            listener(instance,YZL_UI_CTR_EVENT_TOUCH_UP);
            return YZF_FALSE;
        }
    }else if(event == YZL_UI_CTR_EVENT_SELECTED){
        listener(instance,YZL_UI_CTR_EVENT_SELECTED);
        return YZF_TRUE;
    }
    return YZF_FALSE;
}

void WidgetTextButton::disposeP() {
    YZL_MEM_MANAGER.pFree(text);
    YZL_MEM_MANAGER.pFree(fontPixel);
    WidgetBase::disposeP();
}

void WidgetTextButton::setListener(void (*listener)(void *, YZL_UI_CTR_EVENT)) {
    this->listener=listener;
}

void WidgetTextButton::setText(utf8 *srcText) {
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

void WidgetTextButton::setTextF(utf8 *format, ...) {
    int i;

    va_list arg;
    va_start(arg, format);
    memset(transmit_buf,0,sizeof(transmit_buf));
    i = vsprintf(transmit_buf, (const char *)format, arg);
    va_end(arg);

    transmit_buf[i] = 0;
    setText((utf8 *)transmit_buf);
}

void WidgetTextButton::setTextColor(YZ_COLOR color) {
    text_color=color;
    instance->isRender=YZF_TRUE;
}
