//
// Created by 32827 on 2024/1/11.
//
#include "widget/yzl_ui_button.h"
#include "yzl.h"
#include "yzl_ui_font_utils.h"

void yzl_ui_button_dispose(void *widget){
    YZL_MEM_MANAGER.pFree(YZL_BUTTON_DATA_VALUE(widget)->text);
}
void yzl_ui_button_default_listener(void *widget,enum YZL_BUTTON_EVENT event){

}
void yzl_ui_button_draw(void* widget){
    YZL_WIDGET *p=widget;
    if(p->status==YZL_BUTTON_UN_PRESS){
        yzl_ui_draw_rect(p->x,p->y,p->width,p->height,YZF_TRUE, YZL_BUTTON_DATA_VALUE(widget)->up_color);
        uint16_t len=YZL_BUTTON_DATA_VALUE(widget)->textLen;
        yzl_ui_draw_string(p->x+p->width/2-YZL_FONT_SIZE*len/2-len,p->y+p->height/2-YZL_FONT_LINE_HEIGHT/2,p->x+p->width,
                           YZL_BUTTON_DATA_VALUE(widget)->text,len,WHITE, YZL_BUTTON_DATA_VALUE(widget)->text_color);
    }else if(p->status==YZL_BUTTON_PRESS){
        yzl_ui_draw_rect(p->x,p->y,p->width,p->height,YZF_TRUE,YZL_BUTTON_DATA_VALUE(widget)->down_color);
    }
    p->isRender=YZF_FALSE;
}
YZF_BOOL yzl_ui_button_touch(uint16_t x,uint16_t y,YZL_UI_CTR_EVENT event,void *widget){
    if(((YZL_WIDGET *)widget)->status==YZL_BUTTON_UN_PRESS&& event == YZL_UI_CTR_EVENT_TOUCH_DOWN){
        ((YZL_WIDGET *)widget)->status=YZL_BUTTON_PRESS;
        YZL_BUTTON_DATA_VALUE(widget)->listener(widget,YZL_BUTTON_PRESS);
        ((YZL_WIDGET *)widget)->isRender=YZF_TRUE;
        return YZF_TRUE;
    }else if(((YZL_WIDGET *)widget)->status==YZL_BUTTON_PRESS&& event == YZL_UI_CTR_EVENT_TOUCH_UP){
        ((YZL_WIDGET *)widget)->status=YZL_BUTTON_UN_PRESS;
        YZL_BUTTON_DATA_VALUE(widget)->listener(widget,YZL_BUTTON_UN_PRESS);
        ((YZL_WIDGET *)widget)->isRender=YZF_TRUE;
        if(yzl_ui_point_check(widget,x,y)){
            return YZF_TRUE;
        }else{
            return YZF_FALSE;
        }
    }
    return YZF_FALSE;
}
void yzl_ui_button_create(YZL_WIDGET *ButtonRam,int x, int y,int z, int width, int height,YZ_COLOR up,YZ_COLOR down,YZ_COLOR text_color,const utf8 *text){
    ButtonRam->x=x;
    ButtonRam->y=y;
    ButtonRam->z=(int16_t)z;
    ButtonRam->height=height;
    ButtonRam->width=width;
    YZL_BUTTON_DATA_VALUE(ButtonRam)->up_color=up;
    YZL_BUTTON_DATA_VALUE(ButtonRam)->down_color=down;
    YZL_BUTTON_DATA_VALUE(ButtonRam)->text_color=text_color;
    YZL_BUTTON_DATA_VALUE(ButtonRam)->listener=yzl_ui_button_default_listener;

    yzl_ui_font_data_init(YZF_NULL_PTR,&YZL_UI_WIDGET_DATA_VALUE(YZL_BUTTON_DATA, ButtonRam)->text,&YZL_UI_WIDGET_DATA_VALUE(YZL_BUTTON_DATA, ButtonRam)->textLen,(unsigned char *)text);

    ButtonRam->dispose=yzl_ui_button_dispose;
    ButtonRam->draw=yzl_ui_button_draw;
    ButtonRam->touch=yzl_ui_button_touch;
    ButtonRam->status=YZL_BUTTON_UN_PRESS;
    ButtonRam->isRender=YZF_TRUE;
}
void yzl_ui_button_set_listener(void *widget,void (*p)(void *widget, enum YZL_BUTTON_EVENT event)){
    YZL_BUTTON_DATA_VALUE(widget)->listener=p;
}