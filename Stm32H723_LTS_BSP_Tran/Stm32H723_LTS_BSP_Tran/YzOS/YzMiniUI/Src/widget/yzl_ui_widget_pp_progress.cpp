//
// Created by 32827 on 2024/3/3.
//
#include "widget/yzl_ui_widget_pp_progress.hpp"
#include <cmath>
WidgetProgress::WidgetProgress(YZL_WIDGET *Ram, int x, int y, int z, int width, int height, Yz_Color barColor,
                               Yz_Color backgroundColor,int32_t border,int32_t maxValue, int32_t value) : WidgetBase( Ram, x, y, z, width,height){
    this->barColor=barColor;
    this->backgroundColor=backgroundColor;
    this->border=border;
    this->maxValue=maxValue;
    this->value=value;
}
WidgetProgress::WidgetProgress(YZL_WIDGET *Ram, UI_Rect *rect, int z, Yz_Color barColor, Yz_Color backgroundColor,
                               int32_t border, int32_t maxValue, int32_t value) : WidgetBase(Ram, rect->x,rect->y, z, rect->width, rect->height){
    this->barColor=barColor;
    this->backgroundColor=backgroundColor;
    this->border=border;
    this->maxValue=maxValue;
    this->value=value;
}
void WidgetProgress::drawP() {
    WidgetBase::drawP();
    if(instance->isRender){
        yzl_ui_draw_rect(instance->x,instance->y,instance->width,instance->height,YZF_TRUE,backgroundColor);
        double percent=value/(double )maxValue;
        int32_t barWidth=static_cast<int32_t>(round((percent*instance->width)));
        yzl_ui_draw_rect(instance->x,instance->y+border,barWidth,instance->height-border*2,YZF_TRUE,barColor);
    }
    instance->isRender=YZF_FALSE;
}

void WidgetProgress::setValue(int32_t value) {
    this->value=value;
    instance->isRender=YZF_TRUE;    //刷新显示
}
int32_t WidgetProgress::getValue(){
    return this->value;
}


