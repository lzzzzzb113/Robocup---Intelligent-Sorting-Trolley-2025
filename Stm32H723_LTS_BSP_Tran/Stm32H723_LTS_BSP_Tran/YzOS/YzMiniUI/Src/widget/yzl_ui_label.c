//
// Created by 32827 on 2024/1/26.
//
#include "widget/yzl_ui_label.h"
#include "utils/yzl_ui_font_utils.h"
#include "yzl.h"
void yzl_ui_label_dispose(void *widget){
    YZL_MEM_MANAGER.pFree(YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, widget)->text);
}
void yzl_ui_label_default_listener(void *widget,YZL_UI_CTR_EVENT event){
    yz_info("[Label]");
}
void yzl_ui_label_draw(void* widget){
    YZL_WIDGET *p=widget;
    if(p->status==YZL_UI_CTR_EVENT_TOUCH_UP){
        yzl_ui_draw_rect(p->x,p->y,p->width,p->height,YZF_FALSE,YELLOW);
        uint16_t len=YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, widget)->textLen;
        yzl_ui_draw_string(p->x+p->width/2-YZL_FONT_SIZE*len/2,p->y+p->height/2-YZL_FONT_LINE_HEIGHT/2,p->x+p->width,
                           YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, widget)->text,len,WHITE, YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, widget)->text_color);
    }else if(p->status==YZL_UI_CTR_EVENT_TOUCH_DOWN){
        uint16_t len=YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, widget)->textLen;
        yzl_ui_draw_string(p->x+p->width/2-YZL_FONT_SIZE*len/2,p->y+p->height/2-YZL_FONT_LINE_HEIGHT/2,p->x+p->width,
                           YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, widget)->text,len,WHITE,RED);
    }
    p->isRender=YZF_FALSE;
}
YZF_BOOL yzl_ui_label_touch(uint16_t x,uint16_t y,YZL_UI_CTR_EVENT event,void *widget){
    if(((YZL_WIDGET *)widget)->status==YZL_UI_CTR_EVENT_TOUCH_UP&& event == YZL_UI_CTR_EVENT_TOUCH_DOWN){
        ((YZL_WIDGET *)widget)->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
        YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, widget)->listener(widget,YZL_UI_CTR_EVENT_TOUCH_DOWN);
        ((YZL_WIDGET *)widget)->isRender=YZF_TRUE;
        return YZF_TRUE;
    }else if(((YZL_WIDGET *)widget)->status==YZL_UI_CTR_EVENT_TOUCH_DOWN&& event == YZL_UI_CTR_EVENT_TOUCH_UP){
        ((YZL_WIDGET *)widget)->status=YZL_UI_CTR_EVENT_TOUCH_UP;
        YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, widget)->listener(widget,YZL_UI_CTR_EVENT_TOUCH_UP);
        ((YZL_WIDGET *)widget)->isRender=YZF_TRUE;
        if(yzl_ui_point_check(widget,x,y)){
            return YZF_TRUE;
        }else{
            return YZF_FALSE;
        }
    }
    return YZF_FALSE;
}
void yzl_ui_label_create(YZL_WIDGET *labelRam,int x, int y,int z, int width, int height,YZ_COLOR text_color,YZ_COLOR back_color,const utf8 *text) {
    labelRam->x = x;
    labelRam->y = y;
    labelRam->z = (int16_t)z;
    labelRam->width = width;
    labelRam->height = height;
    labelRam->status = YZL_UI_CTR_EVENT_TOUCH_UP;
    YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, labelRam)->text_color = text_color;
    YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, labelRam)->back_color = back_color;

    yzl_ui_font_data_init(YZF_NULL_PTR,&YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, labelRam)->text,&YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, labelRam)->textLen,(unsigned char *)text);

    YZL_UI_WIDGET_DATA_VALUE(YZL_LABEL_DATA, labelRam)->listener = yzl_ui_label_default_listener;
    labelRam->dispose=yzl_ui_label_dispose;
    labelRam->draw=yzl_ui_label_draw;
    labelRam->touch=yzl_ui_label_touch;
    labelRam->isRender=YZF_TRUE;
}