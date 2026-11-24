//
// Created by 32827 on 2024/1/27.
//
#include "widget/yzl_ui_dialog.h"
#include "yzl.h"
#include "yzl_ui_font_utils.h"
#include "yzl_ui_scn_utils.h"

void yzl_ui_dialog_dispose(void *widget){
    YZL_WIDGET *yzlWidget=widget;
    yzl_ui_scn_ram_Restore(YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, widget)->recover,yzlWidget->x,yzlWidget->y,yzlWidget->width,yzlWidget->height);
    YZL_MEM_MANAGER.pFree(YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, widget)->text);
    YZL_MEM_MANAGER.pFree(YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, widget)->fontPixel);
    YZL_MEM_MANAGER.pFree(YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, widget)->recover);
}
void yzl_ui_dialog_default_listener(void *widget,YZL_UI_CTR_EVENT event){
    yz_info("[dialog]\n");
}
void yzl_ui_dialog_draw(void* widget){
    YZL_WIDGET *p=widget;
    YZL_DIALOG_DATA *data=YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, widget);
    if(p->status==YZL_UI_CTR_EVENT_TOUCH_UP){
        uint32_t size= yzl_ui_get_string_width(data->fontPixel,data->text, data->textLen);
        uint16_t width=(size>>16);
        uint16_t height=(size&0xffff);
        uint16_t len=data->textLen;
        yzl_ui_draw_rect(p->x,p->y,p->width,p->height,YZF_TRUE,data->back_color);
        yzl_ui_draw_string(p->x+(p->width-width)/2,p->y+(p->height-height)/2,p->x+p->width,
                           data->text,len,WHITE,data->text_color);
    }else if(p->status==YZL_UI_CTR_EVENT_TOUCH_DOWN){
        uint32_t size= yzl_ui_get_string_width(data->fontPixel,data->text, data->textLen);
        uint16_t width=(size>>16);
        uint16_t height=(size&0xffff);
        uint16_t len=data->textLen;
        yzl_ui_scn_ram_Restore(data->recover,p->x,p->y,p->width,p->height);
        yzl_ui_draw_string(p->x+(p->width-width)/2,p->y+(p->height-height)/2,p->x+p->width,
                           data->text,len,WHITE,RED);
    }
    p->isRender=YZF_FALSE;
}
YZF_BOOL yzl_ui_dialog_touch(uint16_t x,uint16_t y,YZL_UI_CTR_EVENT event,void *widget){
    YZL_WIDGET *p=((YZL_WIDGET *)widget);
    if(p->status==YZL_UI_CTR_EVENT_TOUCH_UP&& event == YZL_UI_CTR_EVENT_TOUCH_DOWN){
        yzl_ui_draw_rect(p->x,p->y,p->width,p->height,YZF_TRUE,RED);
        p->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
        p->isRender=YZF_TRUE;
        YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, widget)->listener(widget,YZL_UI_CTR_EVENT_TOUCH_DOWN);
        return YZF_TRUE;
    }else if(p->status==YZL_UI_CTR_EVENT_TOUCH_DOWN&& event == YZL_UI_CTR_EVENT_TOUCH_UP){
        p->status=YZL_UI_CTR_EVENT_TOUCH_UP;
        p->isRender=YZF_TRUE;
        if(yzl_ui_point_check(widget,x,y)){
            YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, widget)->listener(widget,YZL_UI_CTR_EVENT_TOUCH_UP);
            return YZF_TRUE;
        }else{
            YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, widget)->listener(widget,YZL_UI_CTR_EVENT_TOUCH_UP);
            return YZF_FALSE;
        }
    }
    return YZF_FALSE;
}
//0x200032a2
//0x200032e2
//0x20003322
void yzl_ui_dialog_create(YZL_WIDGET *dialogRam,int x, int y,int z, int maxWidth, int maxHeight,YZ_COLOR text_color,YZ_COLOR back_color,const utf8 *text){
    dialogRam->x = x;
    dialogRam->y = y;
    dialogRam->z = (int16_t)z;
    dialogRam->width = maxWidth;
    dialogRam->height = maxHeight;
    dialogRam->status = YZL_UI_CTR_EVENT_TOUCH_UP;
    dialogRam->isRender = YZF_TRUE;

    YZL_DIALOG_DATA *data=YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, dialogRam);
    data->text_color = text_color;
    data->back_color = back_color;
    data->listener = yzl_ui_dialog_default_listener;
    yzl_ui_font_data_init(&data->fontPixel,
                          &data->text,
                          &data->textLen,
                          (unsigned char *)text);


    uint32_t size= yzl_ui_get_string_width(data->fontPixel,data->text, data->textLen);  //调整控件大小
    uint16_t width=(size>>16);
    uint16_t height=(size&0xffff);
    if(dialogRam->width<width){
        dialogRam->width=width+2;//add padding
    }
    if(dialogRam->height<height){
        dialogRam->height=height+2;
    }

    YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, dialogRam)->recover = yzl_ui_scn_ram_Backup(x,y,maxWidth,maxHeight);
    dialogRam->dispose=yzl_ui_dialog_dispose;
    dialogRam->draw=yzl_ui_dialog_draw;
    dialogRam->touch=yzl_ui_dialog_touch;
}
void yzl_ui_dialog_set_listener(YZL_WIDGET *dialogRam,void (*listener)(void *widget, YZL_UI_CTR_EVENT event)){
    YZL_UI_WIDGET_DATA_VALUE(YZL_DIALOG_DATA, dialogRam)->listener = listener;
}