//
// Created by 32827 on 2024/3/3.
//
#include "widget/yzl_ui_widget_pp_progress_touch.hpp"
#include <cmath>
YZF_BOOL WidgetProgressTouch::touchP(uint16_t x, uint16_t y, YZL_UI_CTR_EVENT event) {
    WidgetBase::touchP(x, y, event);
    if(instance->status==YZL_UI_CTR_EVENT_TOUCH_UP&& event == YZL_UI_CTR_EVENT_TOUCH_DOWN){
        instance->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
        DownPoint={x,y};
        if(listener!=YZF_NULL_PTR){
            listener(instance,YZL_UI_CTR_EVENT_TOUCH_DOWN);
        }
        return YZF_TRUE;
    }else if(instance->status==YZL_UI_CTR_EVENT_TOUCH_DOWN&& event == YZL_UI_CTR_EVENT_TOUCH_UP){
        instance->status=YZL_UI_CTR_EVENT_TOUCH_UP;
        if(yzl_ui_point_check(instance,x,y)){
            UpPoint={x,y};
            setValue(static_cast<int32_t>(round(((UpPoint.x-instance->x)/(float)instance->width)*maxValue)));
            //设置成功，进行回调
            if(listener!=YZF_NULL_PTR){
                listener(instance,YZL_UI_CTR_EVENT_TOUCH_UP);
            }
            return YZF_TRUE;
        }else{
            return YZF_FALSE;
        }
    }
    return YZF_FALSE;
}

WidgetProgressTouch::WidgetProgressTouch(YZL_WIDGET *Ram, int x, int y, int z, int width, int height, Yz_Color barColor,
                                         Yz_Color backgroundColor, int32_t border, int32_t maxValue, int32_t value)
        : WidgetProgress(Ram, x, y, z, width, height, barColor, backgroundColor, border, maxValue, value) {

}

WidgetProgressTouch::WidgetProgressTouch(YZL_WIDGET *Ram, UI_Rect *rect, int z, Yz_Color barColor,
                                         Yz_Color backgroundColor, int32_t border, int32_t maxValue, int32_t value)
        : WidgetProgress(Ram, rect, z, barColor, backgroundColor, border, maxValue, value) {

}
